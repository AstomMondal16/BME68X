#include "bme68x.h"

BME688::BME688(uint8_t i2cAddress, TwoWire &wirePort)
    : _i2cAddress(i2cAddress), _wire(&wirePort) {}

bool BME688::begin() {
    _wire->begin();
    // Example sensor initialization sequence
    writeRegister(0x74, 0x15); // Set oversampling
    writeRegister(0x75, 0x00); // Set filter
    writeRegister(0x70, 0x20); // Enable gas heater
    delay(100); // Allow time for initialization
    return true;
}

void BME688::writeRegister(uint8_t reg, uint8_t value) {
    _wire->beginTransmission(_i2cAddress);
    _wire->write(reg);
    _wire->write(value);
    _wire->endTransmission();
}

uint8_t BME688::readRegister(uint8_t reg, uint8_t *data, uint8_t length) {
    _wire->beginTransmission(_i2cAddress);
    _wire->write(reg);
    if (_wire->endTransmission() != 0) {
        return 0; // Error
    }

    if (_wire->requestFrom(_i2cAddress, length) != length) {
        return 0; // Error
    }

    for (uint8_t i = 0; i < length; i++) {
        data[i] = _wire->read();
    }
    return 1; // Success
}

bool BME688::readSensorData(float &temperature, float &pressure, float &humidity, float &gasResistance) {
    uint8_t data[15];
    if (!readRegister(0x1D, data, 15)) {
        return false; // Error reading data
    }

    // Process sensor data
    temperature = ((data[0] << 8) | data[1]) / 100.0;
    pressure = ((data[2] << 8) | data[3]) / 100.0;
    humidity = ((data[4] << 8) | data[5]) / 1024.0;
    gasResistance = ((data[6] << 8) | data[7]);

    return true;
}
