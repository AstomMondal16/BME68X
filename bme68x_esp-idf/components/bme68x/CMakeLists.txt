idf_component_register(
    SRCS bme68x.c
    INCLUDE_DIRS "include"
    REQUIRES i2cdev log esp_idf_lib_helpers
)
