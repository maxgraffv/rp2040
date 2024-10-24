#ifndef I2C_H
#define I2C_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include <stdlib.h>

int i2c_simple_init( i2c_inst_t* i2c, uint32_t baudrate );

int i2c_simple_write( i2c_inst_t* i2c , uint16_t i2c_address, uint8_t* data_tx, uint8_t data_len, uint8_t nostop);

int i2c_simple_read( i2c_inst_t* i2c, uint16_t i2c_address, uint8_t* data_rx, uint8_t data_len, uint8_t nostop);






#endif