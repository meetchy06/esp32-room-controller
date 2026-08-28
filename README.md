# esp32-room-controller
This project is an ESP32-based automation system that I built to monitor the light and temperature in my room and automatically adjust the environment using my fan and lamps. It combines environmental sensors for real-time measurements with 433.92 MHz RF communication and an optocoupler interface to control the different devices. Once the firmware is uploaded, the ESP32 can run continuously from a USB-C power source without needing to stay connected to a computer.

## Features
- ambient light monitoring using a BH1750 sensor
- temperature and humidity monitoring using a BME280 sensor
- ESP32-based embedded control
- 433.92 MHz RF signal capture and replay
- wireless control of multiple room devices
- electronic button control of an adjustable lamp remote
- configurable temperature and lighting thresholds
- hysteresis and state tracking to avoid unnecessary repeated commands
- separate hardware test programs for each subsystem

## Hardware

- ESP32 development board
- BH1750 / GY-302 ambient light sensor
- BME280 temperature and humidity sensor
- QIACHIP 433 MHz receiver
- QIACHIP 433 MHz transmitter
- 433 MHz antennas
- two 433.92 MHz wireless outlets
- four-channel optocoupler module
- adjustable lamp and original remote
- solderless breadboards
- jumper and breadboard wiring
- USB-C power supply
- soldering pen and gun

## Software
The firmware is written in C++ using the Arduino ESP32 framework.
Libraries used:
- Wire
- BH1750 by Christopher Laws
- Adafruit BME280
- Adafruit Unified Sensor
- rc-switch by sui77

The `tests` directory contains standalone programs used to test each hardware component before combining the system into the main controller firmware.

## Repository Structure

`firmware/RoomController` contains the main controller firmware and configuration file.

`tests` contains standalone sensor, RF, and optocoupler test programs.

`hardware` contains wiring information and the bill of materials.

`docs/images` contains project photos and documentation media.

## Status
Project completed. Sensor readings, RF communication, automatic control logic, and remote-control interfaces were tested successfully before the prototype was disassembled after documentation.

## Usage
This repository is provided for portfolio and demonstration purposes only.
All rights reserved.
