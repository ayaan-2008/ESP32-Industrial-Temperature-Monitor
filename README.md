# ESP32 Temperature Alert System

## Overview

This project implements an industrial-style temperature monitoring and alarm system using the ESP32 and DS18B20 temperature sensor.

The system continuously monitors temperature levels and provides graduated responses based on severity:

- Normal Operation
- Warning Condition
- Critical Alarm Condition
- Human Acknowledgement
- Automatic Fail-Safe Acknowledgement

The project demonstrates embedded monitoring, interrupt handling, and safety-critical decision logic.

---

## Features

- Real-Time Temperature Monitoring
- DS18B20 Digital Temperature Sensor
- Multi-Level Alarm System
- Human Acknowledgement Button
- Interrupt-Based Event Detection
- Automatic Fail-Safe Response
- Visual LED Status Indicators

---

## Hardware

- ESP32
- DS18B20 Temperature Sensor
- Push Button
- Warning LED
- Alarm LED
- Auto-Acknowledge LED

---

## Temperature States

### Normal

Temperature below warning threshold.

Action:
- All indicators OFF

### Warning

Temperature exceeds warning range.

Action:
- Warning LED ON
- Warning message displayed

### Critical

Temperature exceeds critical threshold.

Action:
- Alarm LED flashes
- Alarm message generated
- System waits for operator acknowledgement

### Human Acknowledgement

Operator presses acknowledgement button.

Action:
- Interrupt generated
- Alarm cleared
- Human response recorded

### Auto Acknowledgement

No response within timeout period.

Action:
- Automatic recovery activated
- Fail-safe acknowledgement performed

---

## Technologies

- ESP32
- Arduino Framework
- DS18B20 Sensor
- DallasTemperature Library
- OneWire Communication
- Hardware Interrupts
