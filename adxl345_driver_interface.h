#ifndef ADXL345_DRIVER_H
#define ADXL345_DRIVER_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h> /* memset */
#include <unistd.h> /* close */
#include "pico/stdlib.h"
#include "hardware/i2c.h"


// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9

// Registers for ADXL345
#define ADXL345_ADDRESS         (0xA6 >> 1)
#define ADXL345_REGISTER_XLSB   (0x32)

void i2c_write(int addr, uint8_t reg, uint8_t val);
void i2c_read(int addr, uint8_t reg, size_t size, uint8_t *val);
void init_adxl345();
void read_adxl345(uint16_t *accelerometer_data);
void uart_print(const char *fmt, ...);

#endif