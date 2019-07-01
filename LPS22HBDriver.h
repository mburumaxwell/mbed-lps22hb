#ifndef __LPS22HB_DRIVER_H
#define __LPS22HB_DRIVER_H
#include <mbed.h>

class LPS22HBDriver {
public:
    LPS22HBDriver(I2C *driver, int32_t addr = 0xBA)
    {
        this->i2c_driver = driver;
        this->dev_addr = addr;
    }
    int32_t init();
    int32_t read_id(uint8_t *id);
    int32_t read_pressure(float *pressure);
    int32_t read_temperature(float *temperature);

private:
    I2C *i2c_driver;
    int32_t dev_addr;
};

#endif /* __LPS22HB_DRIVER_H */