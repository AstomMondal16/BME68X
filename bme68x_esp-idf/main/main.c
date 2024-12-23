#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "bme68x.h"

#define TAG "BME68x_Test"

// I2C BME688 Configuration
#define BME680_I2C_ADDR 0x77
#define I2CBME680_MASTER_SDA 7
#define I2CBME680_MASTER_SCL 6
#define I2CBME680_MASTER_PORT 0

bme680_t sensor;
bme680_values_float_t values;
uint32_t duration;

void init_bme680(void)
{
    memset(&sensor, 0, sizeof(bme680_t));

    ESP_ERROR_CHECK(bme680_init_desc(&sensor, BME680_I2C_ADDR, I2CBME680_MASTER_PORT, I2CBME680_MASTER_SDA, I2CBME680_MASTER_SCL));

    // Initialize the sensor
    ESP_ERROR_CHECK(bme680_init_sensor(&sensor));

    // Set oversampling rates for temperature, humidity, and pressure
    bme680_set_oversampling_rates(&sensor, BME680_OSR_4X, BME680_OSR_2X, BME680_OSR_2X);

    // Set filter size
    bme680_set_filter_size(&sensor, BME680_IIR_SIZE_7);

    // Set heater profile
    bme680_set_heater_profile(&sensor, 0, 300, 150);
    bme680_use_heater_profile(&sensor, 0);
    

    // Get measurement duration
    bme680_get_measurement_duration(&sensor, &duration);
}

void app_main(void)
{
    ESP_ERROR_CHECK(i2cdev_init());
    init_bme680();
    
    // Trigger the sensor to start one TPHG measurement cycle
    if (bme680_force_measurement(&sensor) == ESP_OK)
    {
        // Passive waiting until measurement results are available
        vTaskDelay(duration);

        // Get the results and print them
        if (bme680_get_results_float(&sensor, &values) == ESP_OK)
        {
            ESP_LOGI(TAG,"BME688 Sensor: %.2f °C, %.2f %%, %.2f hPa, %.2f KOhm\n",
                   values.temperature, values.humidity, values.pressure, values.gas_resistance);
        }
        else
        {
            ESP_LOGE(TAG, "Failed to get results from BME688 sensor");
        }
    }
    else
    {
        ESP_LOGE(TAG, "Failed to trigger measurement on BME688 sensor");
    }

    i2c_driver_delete(I2CBME680_MASTER_PORT);
}
