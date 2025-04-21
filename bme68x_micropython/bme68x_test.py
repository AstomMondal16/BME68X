import time
import machine
from machine import Pin, I2C
from bme68x import BME680_I2C

# Initialize I2C
i2c = I2C(0, scl=Pin(4), sda=Pin(11))  # Adjust the pins according to your setup

# Initialize the BME680 sensor
sensor = BME680_I2C(i2c)

# Set sensor parameters (optional, can be adjusted based on your needs)
sensor.temperature_oversample = 16  # 16x oversampling for temperature
sensor.humidity_oversample = 16     # 16x oversampling for humidity
sensor.pressure_oversample = 16     # 16x oversampling for pressure
sensor.filter_size = 7             # IIR filter size

# Main loop to read and display sensor values
while True:
    try:
        # Read temperature, humidity, pressure, and gas resistance
        temp = sensor.temperature  # Temperature in °C
        hum = sensor.humidity      # Humidity in %
        pres = sensor.pressure     # Pressure in hPa
        gas = sensor.gas           # Gas resistance in ohms

        # Display the sensor data
        print("Temperature: {:.2f} °C".format(temp))
        print("Humidity: {:.2f} %".format(hum))
        print("Pressure: {:.2f} hPa".format(pres))
        print("Gas Resistance: {:d} Ohms".format(gas))

    except Exception as e:
        print("Error reading sensor:", e)

    # Wait before the next reading
    time.sleep(1)

