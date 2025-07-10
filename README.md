# Wake-On-LAN
ESP32 Wake-on-LAN (WOL) Trigger via HTTP This project allows an ESP32 to wake up a computer on the same local network using the Wake-on-LAN (WOL) protocol. The ESP32 listens for HTTP requests and sends a magic WOL packet to a predefined MAC address.
ESP32 Wake-on-LAN (WOL) HTTP Trigger

A complete project to remotely wake your desktop PC using an ESP32, an LED indicator, and Wake-on-LAN over your local network. This guide includes hardware setup, code, and iOS shortcut integration.

📝 Table of Contents

Overview

Hardware Requirements

Software Requirements

Wiring & Circuit

BIOS Configuration

MAC Address Setup

Code Structure

How It Works

iOS Shortcut Integration

Security Note

✅ Overview

This project allows an ESP32 to send a magic Wake-on-LAN packet to a target device's MAC address when it receives an HTTP request (e.g. from a browser or iOS Shortcut). It acts as a simple, local WOL server.

🔧 Hardware Requirements

ESP32 DevKit (e.g. DOIT ESP32-WROOM)

Breadboard + jumper wires

1x Green LED (optional)

1x 220 Ohm resistor (optional)

Optional visual feedback: A green LED connected to GPIO4 to blink when a WOL packet is sent.

💻 Software Requirements

PlatformIO (VS Code extension recommended)

Arduino framework (via PlatformIO)

iOS Shortcuts app (for mobile integration)

🔌 Wiring & Circuit

LED Anode (+): Connect to GPIO4 of ESP32

LED Cathode (-): Connect to one side of resistor

Other side of resistor: Connect to GND

Power the ESP32 via USB.

🧠 BIOS Configuration

To use Wake-on-LAN, make sure your PC supports it and is properly configured:

Enter BIOS Setup (usually by pressing DEL, F2, or F10 at boot).

Navigate to Power Management / Advanced section.

Enable Wake-on-LAN (WOL) or PCI-E Wake options.

Save & Exit.

🔎 MAC Address Setup

Find the MAC address of the PC you want to wake:

On Windows:

open cmd and type getmac /v /fo list

Look for "Physical Address" under your Ethernet adapter. It will look like:

00-1A-2B-3C-4D-5E

Convert it to byte format in code:

byte macAddress[] = { 0x00, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E };

📁 Code Structure

Main logic is in src/main.cpp:

Connects to Wi-Fi

Starts a web server

Listens on /wake endpoint

Sends WOL magic packet using UDP

PlatformIO configuration is handled in platformio.ini, including serial monitor settings.

⚙️ How It Works

ESP32 connects to your Wi-Fi network.

Listens for HTTP requests on /wake

On trigger, sends a 102-byte magic packet (6x 0xFF + 16x MAC address)

Your PC wakes up from sleep or shutdown if WOL is properly configured.

Serial Monitor Output:

Connecting WiFi...
Connected!
192. xxx. xxx. xx
HTTP server started

📱 iOS Shortcut Integration

You can use Apple Shortcuts to trigger your ESP32 WOL server:

Create a new shortcut

Add action: Get contents of URL

URL: http://<esp32-ip>/wake

Add action: Show Notification (e.g. "PC Unlocked")

Run it with Siri or Widget on your phone

🔐 Security Note

This project is designed for local network use. It is not password-protected, so do not expose your ESP32 IP address to the internet without securing the endpoint.

You can improve security by:

Adding a secret token to the endpoint (/wake?token=abc123)

Limiting access via MAC filtering on your router

📸 Project Images

Images/terminal_output.png: Serial log on successful startup

Images/circuit_breadboard.jpg: Breadboard view

Images/shortcuts.jpg: iOS Shortcut setup
