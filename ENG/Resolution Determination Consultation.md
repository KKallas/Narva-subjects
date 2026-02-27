## **Determining Resolution in Practice**

I made a mistake. I assigned the task of determining the system's resolution. I got back very creative AI-flavored acrobatics, where the same thing was calculated three different ways using the sensor specification and the ADC (analog-to-digital converter) bit count. None of them were actually resolution — in my opinion.

Typically we take the ADC value, multiply it through the voltage divider scaling, use the manufacturer's formula — and get pressure in kPa. Sounds logical? It is. But it doesn't tell you the system's resolution. It only lets you verify whether the formula is implemented correctly.

If you want resolution, you need to find a different logic. You need to look at what the sensor actually does, not what the specification promises. If you set three different pressure points and measure each one ten times, the numbers jump around. How many ADC units do they jump? That jumping is the resolution — the density limit beyond which you cannot see more precisely.

The specification says the sensor can measure 0–700 kPa. The ADC is 12-bit, so 4096 possible values. The math says: 700/4096 \= 0.17 kPa per ADC unit. Dust off my pants and start walking away?

Wait. The supply voltage fluctuates. Resistors aren't really 10kΩ but 9.8kΩ or 10.2kΩ. The crystal drifts with temperature. PCB solder joints start to oxidize. There's moisture inside the sensor housing. All of that together creates noise. Noise eats the resolution away.

## **What Resolution Actually Is**

Resolution is not a specification number. Resolution is two things you measure:

**First:** how many kPa is one ADC unit in your system (not according to the specification, but in reality).

**Second:** how many ADC units the signal jumps while at rest.

If you set the pressure and read 100 measurements, they won't all be the same number. They jump around. For example: 290, 287, 293, 289, 291, 295, 288, 292... That jumping is noise.

If the noise is ±3 ADC units and your conversion is 0.17 kPa per ADC unit, then the practical resolution is 3 × 0.17 \= **0.5 kPa**.

If the noise is ±10 ADC units, then the resolution is 10 × 0.17 \= **1.7 kPa**.

That's the difference between theory and practice. The specification says 0.17 kPa. Your measurement results say 0.5 to 1.7 kPa.

**But don't confuse resolution and accuracy.** Resolution tells you how small a change you can distinguish. Accuracy tells you how close you are to the reality happening on the table. These are two different things.

Resolution is the system's relative density — how finely you can slice the world. Accuracy is how many slices you need so the sandwich doesn't end up half-bare.

*Imagine you know for certain: one sandwich needs four slices of sausage. Four slices. Not three, not five.*

*You go and slice the sausage. You get seven slices. Seven is good resolution — you managed to slice finely. But seven doesn't divide evenly between two sandwiches (since one sandwich needs four slices). One sandwich gets done, three slices remain. That's not accurate.*

*\*father's day explanation*

The MPX5700AP sensor accuracy is ±2.5% according to the specification. This means that even if your resolution is 0.5 kPa, the actual pressure can be off by another ±2.5%.

Example: you measure 100 kPa. Your resolution is 0.5 kPa — you can distinguish between 99.5 kPa and 100.5 kPa. But the sensor accuracy is ±2.5 kPa. So the actual pressure could be anywhere between 97.5 and 102.5 kPa. You see small changes precisely, but the absolute value can be quite inaccurate.

## **How to Measure Resolution**

**Equipment**

You need:

* N100 syringe (10ml)
* Heat shrink tubing to attach the tube to the syringe and sensor
* 4mm pressure tubing
* 4mm quick-connect fittings
* MPX5700AP sensor
* M5 Atom or another microcontroller
* 3D printed holders in three sizes (marked for 8ml, 5ml, 2ml)

The holders are for keeping the plunger in exactly the right position when you push the syringe. Otherwise your hand slips and the measurement is ruined.

**Test Procedure**

1. Pull the syringe plunger to exactly the 10ml mark.
2. Connect the syringe to the sensor with a quick-connect fitting. Check that the connection is airtight. If air leaks, the numbers are meaningless.
3. Start recording. Set 5 measurements per second (200ms intervals). More isn't needed — pressure changes slowly.
4. Push the syringe to the designated range. Use a 3D printed holder — marked for 8ml, 5ml, or 2ml. The holder fixes the plunger for precise measurement.
5. Hold still for 10 seconds. Don't move, don't look at it funny, don't even breathe. Just wait.
6. Release the quick-connect fitting. Remove the 3D printed holder. Stop recording. (now we can assume the recording looks like a tooth with a sharp high edge at the beginning)
7. Repeat the same procedure 10 times for each pressure level. 30 measurements total.

**What You Get**

For each measurement you have a recording showing how the pressure rises and then stabilizes.

The first few seconds are chaos — the plunger moves, pressure rises, numbers jump around. Then the pressure reaches a maximum and drops back (once the plunger is finally in the 3D printed holder) and starts to stabilize. Wait too long, the system leaks — pressure drops. The best point to measure is right after the peak when the pressure has stabilized.

Take 5 seconds from the middle for analysis — after stabilization but before it starts dropping. Make sure to find the stabilization point, don't just take the average. Look at the graph and find that flat section. If you take too early, there's still growth and overshoot from pushing the syringe into the holder. If you take too late, the error from decline has grown too large.

**Example:**

Recording over 10 seconds (5 Hz, 50 points):
Use only the stable portion (**X**;(**X+5**)s). Average: **X** ADC units.

Do this for each of the 10 measurements. Then you have 10 averages for each pressure level:

For example 2ml compression, averages from 10 measurements (stable portion): \[*285, 292, 288, 295, 290, 287, 293, 289, 291, 294*\]

\*for example random numbers ;) same going forward, please don't use these as baseline or magnitude assumptions

Average: **290.4** ADC units

Standard deviation: **3.1** ADC units

That **3.1** is your practical noise level. The range within which you cannot be sure what the actual measured input value is.

### **Standard Deviation ≠ Noise Amplitude**

Why are they different?

#### **Standard Deviation (σ):**

* Describes data spread around the mean
* Says: "Data is on average ±σ away from the mean"
* Does not directly give the maximum noise amplitude

#### **Noise Amplitude:**

* Maximum possible deviation of noise
* Practical limit: "Noise never exceeds ±X units"

## **Finding the Scaling Factor Independently**

You know that 2ml, 5ml, and 8ml compression are known steps. They are 3ml steps in both directions.

If you have three points in ADC values:

* 8ml position (2ml compression): average \= 290 ADC
* 5ml position (5ml compression): average \= 671 ADC
* 2ml position (8ml compression): average \= 2204 ADC

**First step** (8ml → 5ml): 671 \- 290 \= 381 ADC units per 3ml **Second step** (5ml → 2ml): 2204 \- 671 \= 1533 ADC units per 3ml

They're not equal. The first is 127 ADC/ml, the second is 511 ADC/ml. The system is not linear.

The specification doesn't explain how to check whether your analog section is linear — it just assumes it's already been done, so....

## **Linearity Test**

If the steps aren't equal, then pressure doesn't grow linearly with compression.

Reasons:

* Dead volume in the tubing
* Air leak
* Boyle's law doesn't hold exactly (air isn't an ideal gas at high pressure)
* Syringe geometry changes

But you don't know the cause yet. You only know: **the system is not linear**. No system is ideal.

Linear regression gives you the best straight line through all three points:

`from scipy.stats import linregress`

`compression = [2, 5, 8]  # ml`

`adc_values = [290, 671, 2204]  # averages`

`slope, intercept, r_value, p_value, std_err = linregress(compression, adc_values)`

The R² value tells you how well the data fits a straight line. If r² \< 0.99, something is wrong.

## **Practical Resolution**

Now you have:

* **slope** (scaling factor): how many ADC units per ml of compression
* **noise**: standard deviation in ADC units at each pressure level

Resolution is: noise / slope

If slope \= 300 ADC/ml and noise \= 3 ADC units, then:

* Resolution \= 3 / 300 \= **0.01 ml** or 10 microliters

This is the number that tells you: **how small a volume change you can distinguish**.

## **kPa Conversion**

Want to know: how many kPa is one ADC unit?

For this we use Boyle's law as a **baseline principle**. Boyle tells us what we **should** get with an ideal system. Your measurements show what you **actually** get.

Boyle's law for air (gauge pressure):

* 2ml compression: P \= 101.3 × (10/8) \- 101.3 \= **25.3 kPa**
* 5ml compression: P \= 101.3 × (10/5) \- 101.3 \= **101.3 kPa**
* 8ml compression: P \= 101.3 × (10/2) \- 101.3 \= **405.2 kPa**

Boyle's law holds quite accurately for air (±0.5%) up to 5 bar. If your measurements differ more than that, the cause isn't the gas — the cause is the mechanical system.

Now make a table:

| Compression | Theoretical kPa | ADC Average | ADC Noise (std) |
| :---: | :---: | :---: | :---: |
| 2ml | 25.3 | 290 | 3.1 |
| 5ml | 101.3 | 671 | 4.2 |
| 8ml | 405.2 | 2204 | 8.5 |

**kPa per ADC unit** is obtained via linear regression:

kPa\_values \= \[25.3, 101.3, 405.2\]

adc\_values \= \[290, 671, 2204\]

slope\_kPa, intercept\_kPa, r\_value\_kPa, \_, \_ \= linregress(adc\_values, kPa\_values)

slope\_kPa gives you: **how many kPa is one ADC unit**.

For example if slope\_kPa \= 0.19, then one ADC unit \= 0.19 kPa.

## **Noise in kPa**

If the noise is 3.1 ADC units at low pressure and 0.19 kPa per ADC unit, then:

* Noise \= 3.1 × 0.19 \= **0.59 kPa**

If the noise is 8.5 ADC units at high pressure:

* Noise \= 8.5 × 0.19 \= **1.62 kPa**

**Important:** noise may increase with higher pressure. Reasons:

* ESP32 ADC is nonlinear — resolution is worse at the extremes of the range than in the middle
* At higher signal levels, supply voltage fluctuations may have more effect
* The op-amp may approach saturation and behave unstably

If you see noise increasing proportionally with pressure, the main culprit is likely ESP32 ADC nonlinearity, not the sensor itself.

## **The Complete Picture**

You now have two numbers:

**1\. Theoretical resolution:**

* 12-bit ADC gives 4096 possible values
* Sensor range is 0–700 kPa
* Theoretical: 700/4096 \= **0.17 kPa per ADC unit**

This assumes that:

* The sensor uses the full 0–700 kPa range
* The ADC uses the full 0–3.3V range
* The signal is scaled precisely into the correct range
* Everything is ideal

**2\. Practical resolution:**

*Depends on whether you use an op-amp or a voltage divider.*

### **Example A: Op-amp (LM358N)**

Linear regression gives for example **0.19 kPa per ADC unit** (slightly worse than theory, because the op-amp doesn't use the full output range — it's not *rail to rail*).

Noise:

* Low pressure (2ml): 3.1 ADC units → 3.1 × 0.19 \= **0.59 kPa**
* Medium pressure (5ml): 4.2 ADC units → 4.2 × 0.19 \= **0.80 kPa**
* High pressure (8ml): 8.5 ADC units → 8.5 × 0.19 \= **1.62 kPa**

The difference comes from:

* Op-amp doesn't use the full output range (stays between \~0.02V to 3.5V with 5V supply)
* Op-amp adds its own noise
* Two inversion stages amplify noise
* ESP32 ADC nonlinearity eats resolution

### **Example B: With Voltage Divider**

The voltage divider scales the sensor's 0.2V–4.7V signal to the ADC's 0–3.3V range. For example a 2:3 divider (10kΩ \+ 20kΩ) gives:

* 0.2V → 0.13V
* 4.7V → 3.13V

Linear regression gives for example **0.21 kPa per ADC unit** (worse than op-amp, because you use less of the ADC range — only \~0.13V to 3.13V instead of the full 0–3.3V).

Noise:

* Low pressure (2ml): 2.8 ADC units → 2.8 × 0.21 \= **0.59 kPa**
* Medium pressure (5ml): 3.5 ADC units → 3.5 × 0.21 \= **0.74 kPa**
* High pressure (8ml): 4.2 ADC units → 4.2 × 0.21 \= **0.88 kPa**

The difference comes from:

* Voltage divider reduces the signal AND noise equally (SNR stays the same, but you use less ADC range)
* Simpler circuit, fewer components that can add noise
* But: cannot optimally use the full ADC range
* Noise remains smaller than the op-amp version

**Important conclusion:**

The voltage divider gives lower noise (more stable) but a worse kPa/ADC ratio because it doesn't optimally use the full ADC range.

The op-amp gives a better kPa/ADC ratio (more efficient ADC usage) but higher noise, especially at the high end of the pressure range.

## **Effective Number of Bits (ENOB)**

If you want to be professional, calculate ENOB. This is a number that tells you how much your ADC **actually** can do.

**Signal-to-noise ratio (SNR):**

SNR \= signal amplitude / noise amplitude

For example at high pressure:

* Signal: 2204 ADC units
* Noise: 8.5 ADC units
* SNR \= 2204 / 8.5 \= 259

In decibels: SNR\_dB \= 20 × log₁₀(259) \= **48.3 dB**

**ENOB formula:** ENOB \= (SNR\_dB \- 1.76) / 6.02

ENOB \= (48.3 \- 1.76) / 6.02 \= **7.7 bits**

**What this means:**

Although the ADC is 12-bit (4096 levels), due to noise you practically only get **7.7 bits worth of information** (approximately 200 distinguishable levels).

Theory says 12 bits. Practice gives 7.7 bits. You lost **4.3 bits** to noise.

## **How to Use ENOB in Practice**

ENOB is not just a nice number — it tells you concretely **what you can truly achieve**.

### **Example 1: Is it worth using a 16-bit ADC?**

You have a 12-bit ESP32 ADC (actual ENOB \~7.7 bits). You're thinking of buying an external 16-bit ADC (ADS1115).

**Calculation:**

* 16-bit ADC theoretically: 65536 levels
* But if your sensor noise is still 8.5 ADC units, then ENOB remains the same: \~7.7 bits
* Result: **Pointless expense.** Noise is your limitation, not the ADC bit count.

**Solution:** Before upgrading the ADC:

1. Improve the noise level (more stable power supply, filters, shielded cables)
2. Use a low-noise op-amp (e.g. OPA2134)
3. Add an analog low-pass RC filter ([falstad](https://www.falstad.com/circuit/circuitjs.html?ctz=CQAgjCAMB0l3BWEA2aAWB8CcBmSy0AOBBAdkJE0sskoFMBaMMAKAHkQ05xlaEwATD1oiWAc07cBhCl1o4BIqCwBOIAV2GTaYXlHCFSLAMbatc9TM5RY8CAxzQsAgVnzIsCNwIQ5SyGzgISBYwUloNHT1FCl15dR14ahhWAHtrBX0uLAokGHhILH8EZB99ITQQHBZ0+SFabNzA7GLSpAhWAAsq9SqWIA))

Once you've reduced the noise (e.g. to 2 ADC units), THEN it's worth considering a 16-bit ADC.

### **Example 2: How fast can you measure?**

ENOB also tells you **how much averaging you need**.

Single measurement: ENOB \= 7.7 bits (200 levels)

If you average N measurements, noise decreases by √N:

* Average of 4 measurements: noise decreases 2x → ENOB \= 8.7 bits
* Average of 16 measurements: noise decreases 4x → ENOB \= 9.7 bits
* Average of 64 measurements: noise decreases 8x → ENOB \= 10.7 bits

**Practical use:**

If you want ENOB of 10 bits (1024 levels), you need to average **\~50 measurements**.

If you measure at 5 Hz, then 50 measurements \= 10 seconds. That's your system response time.

Can you afford 10 seconds? If not, you need to reduce noise elsewhere, not through averaging.

### **Example 3: Making Design Decisions**

You have two variants:

**Variant A:** Voltage divider \+ 12-bit ADC

* Simpler, cheaper
* ENOB \= 8.2 bits (lower noise, but uses less ADC range)

**Variant B:** Op-amp \+ 12-bit ADC

* More complex, more expensive
* ENOB \= 7.7 bits (more noise, but uses more ADC range)

**Decision:**

If your application only needs 8-bit precision (256 levels), then **Variant A is sufficient**. Simple and cheap.

If you need 10-bit precision (1024 levels), then **Variant B \+ 50x averaging** or an external 16-bit ADC \+ noise reduction.

ENOB makes these decisions numerical, not intuition-based.

### **Example 4: Writing a Specification**

When writing your dispensing system specification, don't say:

"12-bit resolution" \-\> "Effective resolution: 8 bits (ENOB), \~0.6 kPa at low pressure"

That's honest. It tells the client what they ACTUALLY get.

## **Calibration**

If you use an op-amp circuit ([LM358N](https://docs.google.com/document/d/1MqfEIzB4_t980IvLrPW5TXFJ87oD_5Px8io3uTXTt2A/edit?usp=sharing)), then you need to calibrate differently than with a simple voltage divider. However, this process also works for use with a voltage divider.

**Problem:** All kinds of electronics inaccuracy — from the sensor to the digital signal processing — is slightly imprecise. The system needs to be calibrated as independently as possible.

Use only your three points:

* 2ml, 5ml, 8ml compression
* ADC values after the sensor and electronic circuit

Do linear regression. This gives you a new scaling factor and offset. You calculate these independently from the specification.

### **Range Check:**

Then take a **9ml compression** (pressure that should saturate the sensor — 912 kPa, which is above the 700 kPa limit). Read the ADC value. **This should be the sensor's absolute maximum** — the sensor is fully saturated.

Then repeat the same test with **1ml pressure** — this is the system's minimum value (\~11 kPa).

#### **If the maximum voltage is too low:**

Problem: The ADC maximum at 9ml is for example only 2000 units (instead of \~3800). **The sensor is not reaching saturation.**

**Causes and solutions:**

**1\. Op-amp saturates before the sensor**

* Cause: Supply voltage too low or op-amp can't climb high enough in output
* **This is your MAIN problem** — op-amp clips the signal before the sensor saturates
* Check: Measure the op-amp output voltage at 9ml with an oscilloscope. If it's \~3.5V (with 5V supply) or \~1.8V (with 3.3V supply), then the op-amp saturates before the sensor
* Solution:
  * Increase the supply voltage (use 5V, not 3.3V)
  * Reduce the second stage gain
  * Use a rail-to-rail op-amp (e.g. MCP6002)

**2\. Dead volume in tubing is too large**

* Cause: Long/thick tubes, the sensor itself, quick-connect fittings — all add volume
* 10ml syringe \+ 2ml dead volume \= 12ml total initial volume
* 9ml compression: 12ml → 3ml \= only \~405 kPa, not 912 kPa
* Solution: Use shorter/thinner tubes, remove unnecessary quick-connect fittings

**3\. Air leak**

* Cause: Connections not tight, heat shrink has come loose
* Check: Does the pressure drop quickly after pushing?
* Solution: Check all connections, replace heat shrink

**Important:** At 9ml the sensor MUST saturate. If it doesn't, something is wrong and you're not using the sensor's full range.

### **If the maximum voltage is too low:**

Problem: The ADC maximum is for example only 2000 units (instead of \~3800). You lose the upper half of the ADC range.

**Causes and solutions:**

**1\. Op-amp saturates before the sensor**

* Cause: Supply voltage too low or op-amp can't climb high enough in output
* Check: Measure the op-amp output voltage with an oscilloscope. If it's \~3.5V (with 5V supply) or \~1.8V (with 3.3V supply), then it saturates
* Solution:
  * Increase the supply voltage (use 5V instead of 3.3V)
  * Increase the gain (change the op-amp input resistor ratio)
  * Use a rail-to-rail op-amp (e.g. MCP6002)

**2\. Voltage divider incorrectly calculated**

* Cause: The sensor's 4.7V was scaled down too much
* Check: Measure the voltage divider with an oscilloscope — does a 4.7V input give \~3.2V output?
* Solution: Change the resistor ratio (e.g. 10kΩ:15kΩ instead of 10kΩ:20kΩ)

**3\. Sensor doesn't reach 700 kPa**

* Cause: Too much dead volume in tubing or air is leaking
* Check: Does 9ml compression actually give the sensor's maximum output? Measure directly from the sensor.
* Solution: Use the shortest possible tube, or add the tube volume to the syringe scale

### **If the minimum voltage is too high:**

Problem: The ADC minimum is for example 500 units (instead of \~50). You lose the lower portion of the ADC range.

**Causes and solutions:**

**1\. Bias voltage too high**

* Cause: The first stage op-amp bias voltage is too high
* Check: Measure the voltage divider that provides the bias voltage
* Solution: Reduce the bias voltage

**2\. Sensor doesn't go near zero**

* Cause: Atmospheric pressure is already at the base level (gauge pressure sensor)
* This is normal: MPX5700AP measures gauge pressure, not absolute pressure
* Solution: No fix needed — this is by design

\*engineers hide a lot of terrible things behind this excuse

### **Ideal Range:**

Your ADC values should be:

* Minimum (1ml): **\~100-300** ADC units
* Maximum (9ml): **\~3500-3900** ADC units

This uses \~85-95% of the ADC range. Leaves some buffer room for noise and fluctuations.

If your range is smaller than this, it's worth optimizing the circuit. If it's within this range, it's good enough.

## **Python**

The complete analysis in one block:

`import numpy as np`

`from scipy.stats import linregress`

`import matplotlib.pyplot as plt`

`# Raw data (replace with your numbers)`

`compression_ml = np.array([2, 5, 8])`

`theoretical_kPa = np.array([25.3, 101.3, 405.2])`

`# 10 measurements for each level`

`adc_2ml = np.array([285, 292, 288, 295, 290, 287, 293, 289, 291, 294])`

`adc_5ml = np.array([665, 671, 668, 673, 670, 669, 672, 667, 674, 671])`

`adc_8ml = np.array([2198, 2204, 2201, 2207, 2200, 2203, 2206, 2199, 2205, 2202])`

`# Calculate averages and noise`

`mean_adc = np.array([np.mean(adc_2ml), np.mean(adc_5ml), np.mean(adc_8ml)])`

`std_adc = np.array([np.std(adc_2ml), np.std(adc_5ml), np.std(adc_8ml)])`

`print("=== ADC VALUES ===")`

`for i, comp in enumerate(compression_ml):`

   `print(f"{comp}ml compression: average={mean_adc[i]:.1f}, std={std_adc[i]:.2f}")`

`# Linear regression: ml -> ADC`

`slope_ml_to_adc, intercept_ml, r_ml, _, _ = linregress(compression_ml, mean_adc)`

`print(f"\n=== COMPRESSION -> ADC ===")`

`print(f"Scaling factor: {slope_ml_to_adc:.1f} ADC units per ml")`

`print(f"R²: {r_ml**2:.4f}")`

`# Linear regression: ADC -> kPa`

`slope_adc_to_kPa, intercept_kPa, r_kPa, _, _ = linregress(mean_adc, theoretical_kPa)`

`print(f"\n=== ADC -> kPa ===")`

`print(f"Scaling factor: {slope_adc_to_kPa:.4f} kPa per ADC unit")`

`print(f"R²: {r_kPa**2:.4f}")`

`print(f"Theoretical (spec): {700/4096:.4f} kPa per ADC unit")`

`# Resolution`

`print(f"\n=== RESOLUTION ===")`

`for i, comp in enumerate(compression_ml):`

   `res_ml = std_adc[i] / slope_ml_to_adc`

   `res_kPa = std_adc[i] * slope_adc_to_kPa`

   `print(f"{comp}ml: noise={std_adc[i]:.2f} ADC → {res_ml:.4f} ml → {res_kPa:.3f} kPa")`

`# ENOB (take best case - lowest noise)`

`snr = mean_adc[0] / std_adc[0]`

`snr_db = 20 * np.log10(snr)`

`enob = (snr_db - 1.76) / 6.02`

`print(f"\n=== ENOB (at low pressure) ===")`

`print(f"SNR: {snr_db:.1f} dB")`

`print(f"ENOB: {enob:.1f} bits (theoretical 12 bits)")`

`# Plot`

`plt.figure(figsize=(10, 6))`

`plt.errorbar(compression_ml, mean_adc, yerr=std_adc, fmt='o', capsize=5, label='Measured')`

`x_fit = np.linspace(0, 10, 100)`

`y_fit = slope_ml_to_adc * x_fit + intercept_ml`

`plt.plot(x_fit, y_fit, 'r--', label=f'Linear fit (R²={r_ml**2:.4f})')`

`plt.xlabel('Compression (ml)')`

`plt.ylabel('ADC value')`

`plt.legend()`

`plt.grid(True)`

`plt.title('Compression vs ADC Value')`

`plt.show()`

## **Results**

After this analysis you should present:

**1\. One code value equals how many kPa:**

* Example: 0.19 kPa per ADC unit (practical)
* Compare: 0.17 kPa per ADC unit (theoretical from specification)

**2\. How many code values is the noise level:**

* Low pressure (2ml): 3.1 ADC units
* Medium pressure (5ml): 4.2 ADC units
* High pressure (8ml): 8.5 ADC units

**3\. Practical resolution:**

* Low pressure: 0.59 kPa
* Medium pressure: 0.80 kPa
* High pressure: 1.62 kPa

**4\. ENOB:**

* 7-8 bits (depends on pressure)

**5\. Linearity assessment:**

* R² \> 0.99: system is linear
* R² \< 0.99: system is not linear, need to investigate the cause
