# C Pico SDK ADXL345 driver
The ADXL345 is a i2c/spi accelerometer. This library let you read accelerometer data through I²C.

## Usage
### Install
```bash
mkdir project-example
cd project-example

git clone https://github.com/aiRCS-Lab/adxl345-pico-driver.git

touch main.c
```
### Implementation
```c
#include "hardware/i2c.h"
#include "adxl345_driver_interface.h"

int main(int argc, const char * const * argv)
{
    static int16_t accelerometer_data[3];
	memset(accelerometer_data, 0, sizeof(accelerometer_data));
	init_adxl345();

    while(1)
    {
        read_adxl345(accelerometer_data);
        //3.9mg/LSB scale factor in 13-bit mode
        uart_print("RAW: %d\t%d\t%d\n",accelerometer_data[0], accelerometer_data[1], accelerometer_data[2]);
        uart_print("ACCEL: %f\t%f\t%f\n",
                        ((float)accelerometer_data[0])*3.9/1000,
                        ((float)accelerometer_data[1])*3.9/1000,
                        ((float)accelerometer_data[2])*3.9/1000);
        sleep_ms(1000);
    }

    return 0;
}
```