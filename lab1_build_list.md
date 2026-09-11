# Lab 1 — what each team actually builds

Draft 10.09.26. The three Lab 1s meet in one demo:

> **Press a letter on the AtomS3 screen → the MG400 draws that letter on paper with a printed pen holder.**

3D Printing makes the holder, Data Acquisition makes the letter UI, Smart Solutions makes the robot move. No team's demo works without the other two.

---

## Day one has no parts

There is nothing on the shelf but the old stuff box and the simulation tools. That is not a reason to wait — it is the first task. Every course starts the same way:

1. **Open the old box and inventory it.** What is in there, what works, what is broken, what is missing. One table, photographed.
2. **Build it where parts are free**: Falstad for the circuit, Fusion and the slicer for the part, the robot's own simulator or a dry jog for the motion.
3. **Write the parts list** from what the simulation says you need — real part numbers, real prices, checked stock — for the 22.09 order.

You find out what you need by starting, not by waiting to be given it.

---

## 3D Printing — build

1. **Tolerance block: a cylinder inside a cube.** One cube with a round hole, one peg to fit it, printed at five clearances (0.0, 0.1, 0.2, 0.3, 0.4 mm on the diameter). Measure every hole and every peg with calipers before trying them.
   - What it teaches: the hole comes out smaller than drawn and the peg comes out bigger. Nominal is not printed. Below about one nozzle width the two internal walls weld together and the gap disappears entirely. The elephant foot at the bottom layer makes the first millimetre tighter than the rest.
   - Output: the clearance number this team's printer needs. Every part in every later lab uses it.

2. **Pen holder for the MG400 flange — with give in it.** The pen must not be rigidly clamped. A printed flexure, a sprung barrel, a foam pad, whatever they design: if the taught Z is 2 mm too low, the holder gives and the pen survives.
   - What it teaches: a rigid tool breaks something — the pen, the paper, or the robot's alarm. Compliance is a design feature, not sloppiness.
   - Test: teach the pen 2 mm too low on purpose. Nothing breaks, the line still draws.

## Data Acquisition — build

3. **AtomS3 as a WiFi access point with a captive portal.** Phone or laptop joins `team-N-tag`, the browser opens the page by itself.

4. **Image upload to the 0.85" screen** through that portal. Pick a file, it appears on the Atom.
   - What it teaches: how much of a picture fits in the device you have. 128×128 pixels, a fixed colour format, a size limit — the first real encounter with a constraint that cannot be argued with.

5. **Letter chooser.** The screen loops through the alphabet; the button (or a tap in the portal) picks the one on screen and sends it out.

6. **First pressure prototype: sensor + syringe.** MPX5700AP from the old box, wired to the ADC, read at 100 Hz, logged over UART. Syringe on the tip as the pressure source.
   - What it teaches: the raw signal is noisy and the range is wrong. Both get fixed in Lab 2, and the difference is only visible because this was measured first.

## Smart Solutions — build

7. **The computer talks to the MG400.** Network, address, connect, enable, clear error, jog, read position. First contact.

8. **The computer talks to the Atom.** Whatever link they choose — the Atom's AP, the LAN, or USB — the letter that was picked on the screen arrives on the computer.

9. **The chain works end to end.** Letter in → the robot draws it. Their code owns the middle: which letter maps to which path, where the paper is, what the pen-down Z is, what happens when the robot is not ready.
   - What it teaches: three boxes that each work are not a system. The system is the part between them, and it is theirs.

---

## The half-baked start

The first session is spent together on the lab description itself: read it, argue with it, fill in what is obviously missing, cross out what makes no sense. Then each team takes their own copy and keeps filling it — their version, in their repository, in their own words, for the rest of the lab.

## Three things to decide before 11.09

1. **How many AtomS3 units are on the shelf?** The letter UI needs the screen, and the plan currently has the AtomS3 batch arriving in December with one unit on the shelf now. If it is one, either it goes on the 22.09 order as the first line, or the letter chooser runs headless on an Atom Lite until the screens arrive and the screen is added afterwards.

2. **Does the tolerance block replace something?** It is a better first print than the round-vs-square tube test currently in the document, which was already the weakest item there.

3. **Who owns the letter paths?** Twenty-six letters as robot motion is a real piece of work. Suggestion: the team defines three letters, their own initials, and the alphabet grows if there is time.
