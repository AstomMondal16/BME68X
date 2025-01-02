# BME688 Sensor Driver and Example Code

This repository contains Python code for interfacing with the BME688 environmental sensor using the I2C protocol. The code demonstrates how to initialize the sensor, read environmental data, and display it on the console.

---

## Features

- Read **temperature**, **pressure**, **humidity**, and **gas resistance** from the BME688 sensor.
- Simple and clear API for sensor initialization and data retrieval.
- Continuously display sensor readings with configurable intervals.

---

## Prerequisites

### Hardware

- **Microcontroller/Development Board:**
  - Raspberry Pi or another device with an I2C-compatible bus.
- **Sensor Module:**
  - BME688 sensor module.

### Software

- Python 3.6 or later.
- Required Python library:  
  - `smbus2` (for I2C communication)

---

## Installation

### Clone this Repository

1. Clone the repository:

   ```bash
   git clone https://github.com/your_username/bme688_driver.git
   cd bme688_driver
    ```
### Install Dependencies
2. Install the required Python library:
   ```bash
   pip install smbus2
     ```
   ### Wiring the BME688 Sensor to Raspberry Pi

Connect the BME688 sensor to your Raspberry Pi's I2C bus as follows:


| **BME688 Pin** | **Raspberry Pi Pin** | **GPIO Pin Name**       |
|----------------|-----------------------|-------------------------|
| VCC            | Pin 1 or Pin 17      | 3.3V                   |
| GND            | Pin 6                | Ground (GND)           |
| SCL            | Pin 5                | GPIO 3 (I2C Clock - SCL)|
| SDA            | Pin 3                | GPIO 2 (I2C Data - SDA)|

## Enable I2C on Raspberry Pi
  1. Run the Raspberry Pi configuration tool:

    ```bash
    sudo raspi-config```

  2.Navigate to:

    Interfacing Options > I2C
  3. Enable the I2C interface and reboot the Raspberry Pi if prompted.


