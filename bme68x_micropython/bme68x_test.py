from machine import Pin, I2C
from bme68x import BME68x
import time

# Define I2C pins and initialize
i2c = I2C(0, scl=Pin(22), sda=Pin(21))  # Adjust pins as per your board
bme688 = BME688(i2c)

# Initialize the sensor
bme688.init_sensor()

# Read and print data in a loop
while True:
    # Read data from the sensor
    data = bme688.get_sensor_data()

    print("Temperature: {:.2f} °C".format(data["temperature"]))
    print("Pressure: {:.2f} hPa".format(data["pressure"]))
    print("Humidity: {:.2f} %".format(data["humidity"]))
    print("Gas Resistance: {:.2f} Ohms".format(data["gas_resistance"]))

    time.sleep(5)  # Read every 5 seconds
