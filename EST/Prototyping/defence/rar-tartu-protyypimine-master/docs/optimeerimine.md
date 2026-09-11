# Potential improvements for AtomS3R-M12 blob detection runtime

## Main bottleneck hypothesis

The blob scan itself is probably not the biggest bottleneck anymore.

The expensive part is likely:

1. Camera capture in JPEG
2. Full `fmt2rgb888()` decode of the whole frame
3. Only then scanning pixels for the blob

At HVGA (`480x320`) with:

* `step = 4`
* `roi = 23%`

you only examine roughly `7,000–7,500` sampled points per frame. That is not tiny, but it is usually much cheaper than decoding the full JPEG into RGB888 first.

## Biggest speed wins

### 1. Go back to RGB565 in runtime, but make tuning use the same pipeline

This is the strongest optimization path.

Right now, JPEG runtime costs:

* JPEG capture
* JPEG decode to RGB888
* then detection

If runtime switches back to `RGB565`, it skips the full JPEG decode. That is likely the biggest single speed gain.

The earlier problem was mismatch between tuning and runtime. The clean fix is:

* tuning mode also uses `RGB565`
* preview becomes slower still-image BMP snapshots
* runtime uses the exact same pixel format and detector

Benefits:

* more truthful tuning
* faster runtime

### 2. Detect directly on RGB565 and do not build a full RGB888 buffer

If runtime is `RGB565`, do not do a whole-frame convert.

The old `detectBlobRGB565()` path is already closer to the desired approach:

* read pixel
* expand just that pixel to approximate RGB888
* test it
* move on

That is much lighter than:

* decode whole JPEG
* store 3 bytes per pixel in a large buffer
* then scan

### 3. Precompute a 65536-entry RGB565 match LUT

This is a very good optimization for this use case.

Because `RGB565` has only `65,536` possible pixel values, a lookup table can be rebuilt whenever:

* target color changes
* thresholds change
* saturation threshold changes

Then runtime detection becomes:

```cpp
if (matchLUT[pixel565]) { ... }
```

instead of:

* unpack RGB565
* compute normalized RGB
* compute saturation
* compare thresholds

Potential advantages:

* much faster per-pixel test
* simpler inner loop

Memory cost:

* `uint8_t matchLUT[65536]` = about `64 KB`

That is reasonable on ESP32-S3 with PSRAM.

## Medium-impact improvements

### 4. Increase `scanStep` adaptively

Current runtime uses `step = 4`.

Possible strategy:

* coarse scan with `step = 6`
* if blob is found, refine around it with `step = 2` or `4`
* if blob is lost, fall back to coarse full-frame scan

Simpler version:

* default runtime `step = 5` or `6`
* if tracking becomes unstable, go back to `4`

### 5. Track around the previous blob instead of rescanning the whole frame

Right now every frame scans the whole ROI.

Better approach:

* if previous frame had a blob, search only in an expanded box around the last bounding box
* if lost, fall back to full ROI scan

Example:

* full scan once
* next frames scan only last bbox ± 40 px margin
* if nothing found for 3 frames, go back to full scan

This is one of the most practical runtime optimizations for smooth motion.

### 6. Narrow ROI further if the application allows it

Current setting is `roi = 23%`, so scanning starts from 23% downwards.

If the target is usually on the floor or lower half, try:

* `roi 30`
* `roi 35`
* maybe `roi 40`

This reduces processed pixels linearly.

### 7. Reduce runtime resolution only as much as needed

Observed so far:

* `QVGA` = fast but ugly
* `HVGA` = about `8.8–9 fps` and acceptable

That suggests `HVGA` is probably the current sweet spot.

Optional further test:

* `FRAMESIZE_CIF` if supported

That would sit roughly between QVGA and HVGA.

## Smaller but still useful gains

### 8. Reduce serial printing

`Serial.printf()` is not free.

If printing full lines every `120 ms`, that adds overhead.

For real runtime, consider:

* print every `250–500 ms`
* print FPS once per second
* print only when direction changes

### 9. Use a compact runtime output format

Instead of verbose output like:

```text
BLOB dir=LEFT cx=... cy=... count=... area1000=...
```

use something shorter, for example:

```text
L,206,135,663
```

or even a binary packet later.

Benefits:

* less serial overhead
* easier downstream parsing

### 10. Replace normalized RGB with a cheaper detector if possible

Current per-pixel work includes:

* normalization
* three comparisons
* saturation check

Normalization involves division, which is expensive on microcontrollers.

If the target color is distinctive enough, simpler tests might work, for example:

* raw RGB565 channel thresholds
* dominance rules such as `B > R + margin` and `B > G + margin`
* `max - min > sat`

This should be tested only after the format/pipeline optimizations.

## Important observation about the current JPEG path

If the project stays on the current JPEG runtime path, the biggest cost is probably not the blob scan itself.

It is likely:

```cpp
fmt2rgb888(...)
```

That means:

* changing `step` from `4` to `5` helps some
* changing `roi` helps some
* switching away from JPEG decode helps much more

So the biggest real jump is likely to come from:

* RGB565 tuning
* RGB565 runtime
* direct detection on RGB565

## Practical optimization roadmap

### Stage 1 — easiest wins

* keep `HVGA`
* reduce runtime debug printing
* test slightly higher ROI
* test `step = 5`
* optionally scan around last blob first

### Stage 2 — bigger win

* make tuning mode also `RGB565`
* preview as BMP snapshots
* runtime `RGB565` direct detection
* remove JPEG decode from runtime

### Stage 3 — smarter detector

* build RGB565 LUT
* optional previous-bbox tracking
* optional coarse-to-fine scan

## Strongest recommendations

Top 3 speed ideas from the current codebase:

1. Use `RGB565` in both tuning and runtime so runtime can skip JPEG decode
2. Track around previous blob bbox instead of full-frame scan every frame
3. Build a `65536`-entry RGB565 match LUT so each tested pixel becomes one table lookup
