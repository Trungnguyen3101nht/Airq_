<a href="https://github.com/ACLAB-HCMUT"><img src="https://raw.githubusercontent.com/ACLAB-HCMUT/Common/main/Assets/ACLAB_IMG_1.png" alt="ACLAB logo" title="ACLAB" align="right" height="100" /></a>

[![PlatformIO Registry](https://badges.registry.platformio.org/packages/luos/library/luos_engine.svg)](https://registry.platformio.org/libraries/luos/luos_engine)

<br>

# Air Quality Kit M5StampS3

---

**Stamp-S3** is a highly integrated embedded main control core module. It uses `the Espressif **ESP32-S3FN8**` main control chip, equipped with `8M SPI flash memory`, and features a high-performance Xtensa 32-bit LX7 dual-core processor with a main frequency of up to 240MHz. It integrates a `highly integrated` _5V to 3.3V circuit_, _RGB status indicator_, and _programmable button_.

The module exposes **23 GPIOs** from the ESP32-S3 and presents them in `1.27MM/2.54MM` spacing, supporting `SMT, DIP pin headers, DIP sockets, and flying leads` for various usage scenarios.

**Air Quality Kit** is an integrated, low-power air quality monitoring device designed to provide comprehensive air quality monitoring solutions. It features multiple components, including `the SEN55 air quality sensor` and `the SCD40 CO2 sensor`, enabling the monitoring of `PM1.0, PM2.5, PM4, PM10 particles, temperature, humidity, VOC, and CO2` concentrations.

[![](https://shop.m5stack.com/cdn/shop/files/1_be1591f0-8734-4fe2-98ac-30c8ce03c204_1200x1200.webp?v=1704436371)](https://shop.m5stack.com/products/air-quality-kit-w-m5stamps3-sen55-scd40?srsltid=AfmBOooXFmKYJ68EszVbzXEL1lGMqMfrkwJxI8Os7_GjeZNx7Wlcl-kJ)

# Table of Contents

---

- [M5StampS3 Airq Control](#esp32-6-channel-relay-control)
- [Table of Contents](#table-of-contents)
- [Manual](#manual)
  - [1. Device Description](#1-device-description)
  - [2. Hardware Connections](#2-hardware-connections)
  - [3. Programming Instructions](#3-programming-instructions)
    - [3.1. Library Setup](#31-library-setup)
    - [3.2. Setup Procedure](#32-setup-procedure)
  - [4. Usage Instructions](#4-usage-instructions)
- [Question?](#question)

---

# Manual

---

## 1. Device Description

---

> :star2: **Key Features:**

:white_check_mark: **SEN55** and **SCD40** sensors

:white_check_mark: `1.54 inch` ink screen (resolution `200\*200`)

:white_check_mark: Built-in 450mAh battery

:white_check_mark: Grove interface

:white_check_mark: Access the EZDATA cloud platform

:white_check_mark: The RTC wakes up periodically

:white+check_mark: Development Platform:

    - Arduino IDE

    - ESP-IDF

    - Platform.IO

> :star2: **Includes:**

:white_check_mark: 1x Air Quality

:white_check_mark: 1x Operating Instructions

## 2. Hardware Connections

---

> **Specification**

| <strong>Resources</strong>   | <strong>Parameters</strong>                                                                                              |
| ---------------------------- | ------------------------------------------------------------------------------------------------------------------------ |
| MCU                          | StampS3（ESP32S3FN8@8M Flash，240Mhz，2.4GHz Wi-Fi）                                                                     |
| Screen                       | GDEW0154M091, 200×200 @1.54", SPI interface, Dpi:184, 1-bit Black/White (Gray scale: 2), FOV: 27.6×27.6mm, 0.82s refresh |
| Resolution                   | 200×200 px                                                                                                               |
| SEN55                        | I2C address: 0x69                                                                                                        |
| SCD40                        | I2C address: 0x62                                                                                                        |
| Environmental detection type | PM1.0, PM2.5, PM4, PM10 particles, temperature, humidity, VOC, and CO₂ concentrations                                    |
| RTC                          | RTC8563                                                                                                                  |
| Battery                      | 600mAh @ 3.7V                                                                                                            |
| Button                       | Key A (G0), Key B (G8), Start, Reset, Shutdown                                                                           |
| Grove interface              | HY2.0-4P                                                                                                                 |
| Buzzer                       | Onboard passive buzzer                                                                                                   |
| Fixed Structure              | LEGO mounting holes, magnets, 4×M3 plug-in mounting ears                                                                 |
| Operating Temperature        | 0–40°C                                                                                                                   |
| Product Size                 | 72×56×24.1 mm                                                                                                            |
| Package Size                 | 103×75×30 mm                                                                                                             |
| Product Weight               | 91.1 g                                                                                                                   |
| Package Weight               | 119.3 g                                                                                                                  |

## 3. Programming Instructions

---

Ensure the following libraries are installed in your development environment, such as PlatformIO.

### 3.1. Library Setup

    - https://github.com/m5stack/M5Unified.git#develop
    - https://github.com/m5stack/M5GFX.git#develop
    - https://github.com/me-no-dev/ESPAsyncWebServer.git
    - https://github.com/RobTillaart/DHT20
    - bblanchon/ArduinoJson@^7.1.0
    - AsyncTCP
    - mikalhart/TinyGPSPlus@^1.1.0
    - plerup/EspSoftwareSerial@^8.2.0
    - sensirion/Sensirion I2C SEN5X@^0.3.0
    - sensirion/Sensirion I2C SCD4x@^0.4.0
    - mathertel/OneButton@^2.0.3

### 3.2. Setup Procedure

After installing the PlatformIO extension, clone the project repository from Git. Choose the appropriate board for your project, such as `M5 Stamp S3` ,`yolo uno`, `esp32s3relay`, or any other compatible board, and select the corresponding port that connects your computer to the device.

<!-- - On the board:
  - Enter Bootloader mode by following these steps:
  - Hold the Boot button.
  - Press and hold the Reset button.
  - Release the Reset button.
  - Finally, release the Boot button.
- In the PlatformIO interface:

  - Upload the Filesystem Image using PlatformIO.
  - Flash the Firmware onto the device.
  - Exit Bootloader mode by pressing the Reset button. -->

## 4. Usage Instructions

---

> After successfully connecting, you can control the relays via a web interface. You can retrieve the `IP address` of the _M5 Stamp S3_ from the **_Serial Monitor_** in your development environment.
> Access the M5StampS3 server using its `IP address`, and manage the relays.

# Congratulation !

---

:confetti_ball: You have finished reading the introduction and user manual of the **Air Quality Kit M5StampS3**. In the future, we will continue to improve and upgrade to provide you with the best values.:confetti_ball:

> Anything **_unclear_** or **_buggy_** in this tutorial? [Please report it!](https://www.facebook.com/groups/aclabhcmut?locale=vi_VN)
