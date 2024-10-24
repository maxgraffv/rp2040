#include "i2c.h"


int i2c_simple_init( i2c_inst_t* i2c, uint32_t baudrate )
{
    //disable the DW_apb_i2c by writing 0 to IC_ENABLE.ENABLE

    // Write to the IC_CON register to set the maximum speed mode supported [2:1] and desired speed of transfers, either tbit or 10bit addressing (bit 4)
    // Ensure bit 6 IC_SLAVE_DISABLE is written with a 1
    //and bite zero MASTER MODE is written with 1

    i2c->hw->enable = 0;

    uint32_t con = i2c->hw->con;
    con |= (1<<0) | (1<<1) | (1<<6);
    i2c->hw->con = con;

    i2c->hw->enable = 1;
    //Enable DW_apb_i2c




    return 13;
}

int i2c_simple_write( i2c_inst_t* i2c , uint16_t i2c_address, uint8_t* data_tx, uint8_t data_len, uint8_t nostop)
{
    //Write to IC_TAR register the address of the I2C device to be addresses [9:0]
    //Write transfer direction and data to be sent to IC_DATA_CMD register

    i2c->hw->tar = i2c_address;

    uint32_t data_cmd = i2c->hw->data_cmd;
    data_cmd &= 0b11111111111111111111100000000000;

    if(nostop == 0)
        data_cmd |= (1<<9);
    else
        data_cmd |= (1<<10);
    
    data_cmd |= (1<<8);
    

    for(int i = 0; i < data_len; i++)
    {
        while(!(i2c->status & I2C_IC_STATUS_TFNF_BITS ))
        {

        }

        data_cmd |= data_tx[i];
        i2c->hw->data_cmd;

        data_cmd &= 0b11111111111111111111111100000000;
    }


    while(!(i2c->status & I2C_IC_STATUS_TFNF_BITS ))
    {
    }

    return 1;
}

int i2c_simple_read( i2c_inst_t* i2c, uint16_t i2c_address, uint8_t* data_rx, uint8_t data_len, uint8_t nostop)
{
    //Write to IC_TAR register the address of the I2C device to be addresses [9:0]
    // Read ???



}





