#include <Wire.h>
#include "bme68x.h"

// Define I2C address and Wire instance
#define BME688_I2C_ADDRESS 0x77
BME688 bme688(BME688_I2C_ADDRESS);

void setup() {
    Serial.begin(115200);
    while (!Serial);

    // Initialize BME688 sensor
    if (!bme688.begin()) {
        Serial.println("Failed to initialize BME688!");
        while (1);
    }
    Serial.println("BME688 initialized successfully.");
}

void loop() {
    float temperature, pressure, humidity, gasResistance;

    // Read sensor data
    if (bme688.readSensorData(temperature, pressure, humidity, gasResistance)) {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" °C");

        Serial.print("Pressure: ");
        Serial.print(pressure);
        Serial.println(" hPa");

        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");

        Serial.print("Gas Resistance: ");
        Serial.print(gasResistance);
        Serial.println(" Ohms");

        Serial.println("--------------------------");
    } else {
        Serial.println("Failed to read data from BME688!");
    }

    delay(5000); // Wait for 5 seconds
}
