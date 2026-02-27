## Smart Solutions: Lab 1

**Objective** Create a web server on the M5Stack Atom Lite microcontroller that serves a single web page as the user interface and provides two service endpoints (WEB API endpoints). The first version changes the built-in LED color according to the input.

**Functionality**

The Atom has one built-in RGB SK series LED. We use it as a demonstration functionality, controlled remotely via the web interface using REST-based API endpoints:

* **GET /get** – returns the current color as an 8-bit RGB value in HEX encoding, where `#000000` is black and `#FFFFFF` is white. The color order is red, green, blue.
* **GET /set?value=\<value\>** – sets the LED color according to the received value. The value is a string that starts with the \# character and is a HEX-encoded RGB value.

The served web page is a simple JavaScript-enriched application that displays the LED's current value, contains a color wheel for setting a new value, and allows the user to change the WiFi network SSID and password via a settings button.

**Security**: The first version works only in AP mode, so we assume that physical proximity equals authorized access to the device. When adding WiFi infrastructure and VPN, packets must also be signed for user authorization verification.

**Development principles**: Develop in small steps, use the print function for debugging. When small parts work, start combining them into a complete project. Use a git repository.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

### Background Information

* **M5 Atom**
  Device specification, Arduino-ready code examples
  [https://shop.m5stack.com/products/atom-lite-esp32-development-kit](https://shop.m5stack.com/products/atom-lite-esp32-development-kit)
* **Arduino development environment**
  IDE (Integrated Development Environment) where we develop and test software running on the M5 Atom
  [https://docs.m5stack.com/en/arduino/arduino\_ide](https://docs.m5stack.com/en/arduino/arduino_ide)
* **Print debug**
  Since ESP32 requires a separate debugger and Atom doesn't have those pins exposed, the most practical solution is to use the serial terminal for error finding during development.
  [https://docs.arduino.cc/language-reference/en/functions/communication/serial/print/](https://docs.arduino.cc/language-reference/en/functions/communication/serial/print/)
* **WiFi AP and HTTP server**
  How to set up WiFi AP and example code for creating an HTTP server
  [https://randomnerdtutorials.com/esp32-web-server-beginners-guide/](https://randomnerdtutorials.com/esp32-web-server-beginners-guide/)
* **VS Code and Jupyter Lab**
  Tools for creating a QR generator and automated tests
  [https://code.visualstudio.com/docs/datascience/jupyter-notebooks](https://code.visualstudio.com/docs/datascience/jupyter-notebooks)
* **Git**
  How to create a development project repository that multiple people can use
  [https://www.youtube.com/watch?v=fK6jAzQvfRg](https://www.youtube.com/watch?v=fK6jAzQvfRg)
  And how to use it in VS Code
  [https://code.visualstudio.com/docs/sourcecontrol/overview](https://code.visualstudio.com/docs/sourcecontrol/overview)
* **Maybe this has happened to you too**
  Different problems and solutions when working with ESP development
  [https://randomnerdtutorials.com/esp32-troubleshooting-guide/](https://randomnerdtutorials.com/esp32-troubleshooting-guide/)

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

### Tools

1. M5 Atom
2. Arduino IDE
3. VS Code
4. Git

*If the plan changes, update the tools too, or make a [draw.io](http://draw.io) diagram showing how things are functionally related.*

### Project Breakdown

- [ ] Arduino development environment for M5Stack products
- [ ] WiFi connection
- [ ] HTTP and JS web page
- [ ] get/set functionality
- [ ] Jupyter lab QR generator

*How far along are you? When will you be done? How could you go faster? — the usual questions*

### Simulation

Since simulating a real solenoid valve is complex, a small **tool for generating QR codes** (in the Jupyter Lab environment) has been created for this project.

The tool's purpose is to simplify getting started with the device:

1. When **Atom is directly connected to a computer** (via USB or WiFi), the tool can automatically detect and display the necessary settings:
* WiFi network name (SSID)
* WiFi password
* Cryptographic key (for authentication)
2. If automatic detection doesn't work, these values must be entered manually.
3. The tool generates a QR code based on the entered data.
4. The user can scan this QR code with their phone, which automatically connects the phone to the WiFi network created by the Atom and opens the web page for valve control.

After that, the valve can be controlled directly from the phone's browser.

### Testing

#### Test Example 1: LED Color Update Visual Smoothness Test

This test determines the optimal color change frequency based on user feedback to ensure a smooth user experience.

The test works interactively and evaluates the impact of full-chain limitations on visual quality. It starts at a low frequency and gradually increases until the user notices quality degradation.

**Process:** The test starts a cyclical color change (red → green → blue → red) and shows it for 5 seconds at each frequency. Starts from 1 Hz (one change per second) and gradually increases: 2Hz → 5Hz → 10Hz → 20Hz → 50Hz. After each 5-second period it asks: "Were the color changes smooth and clearly distinguishable? (yes/no)". Continues until the user answers "no" — this marks the point where the LED starts flickering too fast or skipping colors.

**Result:** The last "good" frequency is saved as the optimal color change speed for the web interface. This provides a practical upper limit to use for throttling settings — when the user drags quickly on the color wheel, send color change commands no more than the found optimal frequency.

Make a video of the test showing the M5 Atom LED and what's happening on screen

#### Test Example 2: ESP32 Overload and Stability Test

The test checks system behavior under extreme conditions and determines when ESP32 starts dropping commands or completely freezes.

The testing purpose is to find practical limits so the web interface can prevent system overload and ensure graceful degradation during intensive use.

**Escalating load test:** Starts with 10 SET commands per second, sending random RGB values. Gradually increases up to 100+ commands per second. Monitors HTTP response times and notes when responses become slower (\>500ms) or drop out entirely. Checks with GET commands (verify in the program code that the LED state is updated after the LED itself is updated) whether set colors actually reach the LED or some commands are skipped. Determines the critical point where the device starts behaving unstably.

**Recovery test:** When the device is overloaded, stops sending commands completely. Checks whether the system recovers automatically and how quickly. Tests whether the last sent color remains correctly on the LED. Verifies that the API responds normally again after recovery.

**Practical value:** Provides concrete numbers for the web interface — how fast the user can drag the color wheel before the system starts lagging behind. Enables implementing intelligent throttling that keeps the system stable even during intensive use.

*These are the first two examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go\!*

### Development Log

### Results

Git repo:
Readme:
Development log:
Jupyter QR generator file:
Test log:

### Feedback
