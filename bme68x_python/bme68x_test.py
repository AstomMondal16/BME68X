from bme688 import BME688
import time

def main():
    # Initialize the BME688 sensor
    sensor = BME688(i2c_bus=1, address=0x77)  # Adjust I2C bus and address as needed
    sensor.init_sensor()

    # Continuously read and print sensor data
    try:
        while True:
            data = sensor.get_sensor_data()
            print(f"Temperature: {data['temperature']:.2f} °C")
            print(f"Pressure: {data['pressure']:.2f} hPa")
            print(f"Humidity: {data['humidity']:.2f} %")
            print(f"Gas Resistance: {data['gas_resistance']:.2f} Ohms")
            print("-" * 40)
            time.sleep(5)  # Delay between readings
    except KeyboardInterrupt:
        print("Exiting program.")

if __name__ == "__main__":
    main()

