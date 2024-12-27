#ifndef BME688_H
#define BME688_H

#include <Arduino.h>
#include <Wire.h>

class BME688 {
public:
    BME688(uint8_t i2cAddress = 0x77, TwoWire &wirePort = Wire);
    bool begin();
    bool readSensorData(float &temperature, float &pressure, float &humidity, float &gasResistance);

private:
    uint8_t _i2cAddress;
    TwoWire *_wire;

    void writeRegister(uint8_t reg, uint8_t value);
    uint8_t readRegister(uint8_t reg, uint8_t *data, uint8_t length);
};

#endif
