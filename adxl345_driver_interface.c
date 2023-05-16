#include "adxl345_driver_interface.h"

void i2c_write(int addr, uint8_t reg, uint8_t val)
{
    uint8_t data[2];
    data[0] = reg;
    data[1] = val;
    i2c_write_blocking(I2C_PORT, addr, data, sizeof(data), false);
}

void i2c_read(int addr, uint8_t reg, size_t size, uint8_t *val)
{
    i2c_write_blocking(I2C_PORT, addr, &reg, 1, false);
    i2c_read_blocking(I2C_PORT, addr, val, size, false);
}

void init_adxl345()
{

    i2c_init(I2C_PORT, 400*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    uint8_t data = 0;

    i2c_write(ADXL345_ADDRESS, 0x31, 0x0B);   // 13-bit mode  +_ 16g
    i2c_write(ADXL345_ADDRESS, 0x2D, 0x08);   // Power register


    i2c_write(ADXL345_ADDRESS, 0x1E, 0x00);   // x
    i2c_write(ADXL345_ADDRESS, 0x1F, 0x00);   // Y
    i2c_write(ADXL345_ADDRESS, 0x20, 0x05);   // Z

    // Check to see if it worked!
    i2c_read(ADXL345_ADDRESS, 0X00, 1, &data);
    if(data==0xE5)
        printf("Success\n");
    else
        printf("Fail\n");
}

void read_adxl345(uint16_t *accelerometer_data) 
{
    uint8_t bytes[6];
    memset(bytes,0,6);

    // Read 6 bytes from the ADXL345
    i2c_read(ADXL345_ADDRESS, ADXL345_REGISTER_XLSB, 6, bytes);
    // Unpack data
    for (int i=0;i<3;++i) {
        accelerometer_data[i] = (int16_t)bytes[2*i] + (((int16_t)bytes[2*i + 1]) << 8);
    }
}

void uart_print(const char *fmt, ...)
{
    va_list ap;
    char buffer[64];

    va_start(ap, fmt);
    vsprintf(buffer, fmt, ap);
    va_end(ap);

    for (uint8_t i = 0; i < 64; i++)
    {
        if (buffer[i] == 0)
            return;
        uart_putc(uart0, buffer[i]);
    }
    
}