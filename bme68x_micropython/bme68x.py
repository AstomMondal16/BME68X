from machine import I2C
import time

class BME68x:
    def __init__(self, i2c, address=0x77):
        self.i2c = i2c
        self.address = address

    def write(self, register, data):
        self.i2c.writeto_mem(self.address, register, bytes([data]))

    def read(self, register, length=1):
        return self.i2c.readfrom_mem(self.address, register, length)

    def init_sensor(self):
        # Example initialization based on default configuration
        self.write(0x74, 0x15)  # Set oversampling
        self.write(0x75, 0x00)  # Set filter
        self.write(0x70, 0x20)  # Enable heater
        print("BME688 initialized.")

    def get_sensor_data(self):
        # Trigger measurement
        self.write(0x74, 0x01)
        time.sleep(0.2)  # Wait for measurement to complete

        # Read sensor data
        data = self.read(0x1D, 15)  # Assuming 15 bytes of data
        temperature = ((data[0] << 8) | data[1]) / 100.0
        pressure = ((data[2] << 8) | data[3]) / 100.0
        humidity = ((data[4] << 8) | data[5]) / 1024.0
        gas_resistance = ((data[6] << 8) | data[7])

        return {
            "temperature": temperature,
            "pressure": pressure,
            "humidity": humidity,
            "gas_resistance": gas_resistance,
        }
