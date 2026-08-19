# TF-Luna Zenoh Scanner

Real-time 2D LiDAR scanner based on an ESP32, Benewake TF-Luna, servo scanning and Eclipse Zenoh.

## Overview

This project implements a small distributed LiDAR scanning system using an ESP32 and a Benewake TF-Luna distance sensor.

The TF-Luna is mounted on a servo motor, allowing the sensor to perform a 2D angular scan.

Measurements are transmitted from the ESP32 to a host PC over Wi-Fi using Eclipse Zenoh and visualized in real time.

## Architecture

<p align="center">
  <img
    src="docs/architecture/system-architecture.svg"
    alt="TF-Luna Zenoh Scanner system architecture"
  />
</p>

## Main Components

- ESP32
- Benewake TF-Luna
- Servo motor
- Eclipse Zenoh / zenoh-pico
- Python host application
- Docker

## Repository Structure

```text
firmware/    ESP32 firmware
host/        PC-side application
hardware/    Wiring and physical setup
docs/        Project documentation
.github/     GitHub configuration and CI
```

## Status

Early development.

## License

MIT
