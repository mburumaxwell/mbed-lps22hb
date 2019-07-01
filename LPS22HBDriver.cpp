#include "lps22hb_def.h"
#include "LPS22HBDriver.h"
#include "mbed_debug.h"

#define DEBUG_ERR_WRITE(res, reg)  debug_if(res, "LPS22HB write 0x%02X failed with result %ld\r\n", reg, res)
#define DEBUG_ERR_READ(res, reg)   debug_if(res, "LPS22HB read 0x%02X failed with result %ld\r\n", reg, res)
// #define SUCC_FAIL(n) (n ? "failed" : "succeeded")
// #define DEBUG_ERR_WRITE(res, reg)  printf("LPS22HB write 0x%02X %s with result %ld\r\n", reg, SUCC_FAIL(res), res)
// #define DEBUG_ERR_READ(res, reg)   printf("LPS22HB read 0x%02X %s with result %ld\r\n", reg, SUCC_FAIL(res), res)

int32_t LPS22HBDriver::init()
{
    int ret = 0;
    char reg, val;
    char buf[2];
  
    /* Read RES_CONF */
    reg = LPS22HB_REGISTER_RES_CONF;
    ret = i2c_driver->write(dev_addr, &reg, 1);
    DEBUG_ERR_WRITE(ret, reg);
    if (ret) return ret;
    ret = i2c_driver->read(dev_addr, &val, 1);
    DEBUG_ERR_READ(ret, reg);
    if (ret) return ret;
  
    val &= ~LPS22HB_LCEN_MASK;
    val |= (uint8_t)0x01; /* Set low current mode */
  
    /* Apply settings to RES_CONF */
    reg = LPS22HB_REGISTER_RES_CONF;
    buf[0] = reg;
    buf[1] = val;
    ret = i2c_driver->write(dev_addr, buf, 2);
    DEBUG_ERR_WRITE(ret, reg);

    /* Read CTRL_REG1 */
    reg = LPS22HB_REGISTER_CTRL_REG1;
    ret = i2c_driver->write(dev_addr, &reg, 1);
    DEBUG_ERR_WRITE(ret, reg);
    if (ret) return ret;
    ret = i2c_driver->read(dev_addr, &val, 1);
    DEBUG_ERR_READ(ret, reg);
    if (ret) return ret;
  
    /* Set default ODR */
    val &= ~LPS22HB_ODR_MASK;
    val |= (uint8_t)0x30; /* Set ODR to 25Hz */

    /* Enable BDU */
    val &= ~LPS22HB_BDU_MASK;
    val |= ((uint8_t)0x02);
  
    /* Apply settings to CTRL_REG1 */
    reg = LPS22HB_REGISTER_CTRL_REG1;
    buf[0] = reg;
    buf[1] = val;
    ret = i2c_driver->write(dev_addr, buf, 2);
    DEBUG_ERR_WRITE(ret, reg);
    return ret;
}

int32_t LPS22HBDriver::read_id(uint8_t *id)
{  
    int ret = 0;
    char reg, val;
  
    /* Read WHO_AM_I */
    reg = LPS22HB_REGISTER_WHO_AM_I;
    ret = i2c_driver->write(dev_addr, &reg, 1);
    DEBUG_ERR_WRITE(ret, reg);
    if (ret) return ret;
    ret = i2c_driver->read(dev_addr, &val, 1);
    DEBUG_ERR_READ(ret, reg);
    if (ret == 0) *id = (uint8_t)val;
    return ret;
}

int32_t LPS22HBDriver::read_pressure(float *pressure)
{
    int32_t ret, raw;
    char reg, buf[3];
    uint32_t tmp = 0;
    uint8_t i;

    for (i = 0; i < 3; i++)
    {
        reg = LPS22HB_REGISTER_PRESS_OUT_XL + i;
        ret = i2c_driver->write(dev_addr, &reg, 1);
        DEBUG_ERR_WRITE(ret, reg);
        if (ret) return ret;
        ret = i2c_driver->read(dev_addr, &buf[i], 1);
        DEBUG_ERR_READ(ret, reg);
        if (ret) return ret;
    }

    /* Build the raw data */
    tmp = (buf[2] << 16) | (buf[1] << 8) | (buf[0]);

    /* convert the 2's complement 24 bit to 2's complement 32 bit */
    if (tmp & 0x00800000)
        tmp |= 0xFF000000;

    raw = ((int32_t)tmp);
    raw = (raw * 100) / 4096;

    *pressure = (float)((float)raw / 100.0f);

    return ret;
}

int32_t LPS22HBDriver::read_temperature(float *temperature)
{
    int16_t ret, raw;
    char reg, buf[2];
    uint16_t tmp;
    uint8_t i;

    for (i = 0; i < 2; i++)
    {
        reg = LPS22HB_REGISTER_TEMP_OUT_L + i;
        ret = i2c_driver->write(dev_addr, &reg, 1);
        DEBUG_ERR_WRITE(ret, reg);
        if (ret) return ret;
        ret = i2c_driver->read(dev_addr, &buf[i], 1);
        DEBUG_ERR_READ(ret, reg);
        if (ret) return ret;
    }

    /* Build the raw tmp */
    tmp = (((uint16_t)buf[1]) << 8) + (uint16_t)buf[0];

    raw = (tmp * 10) / 100;
    *temperature = ((float)(raw / 10.0f));

    return ret;
}
