
#include <xc.h>
#include "main.h"
#include "i2c.h"
#include "ext_eeprom.h"

/* 
 * A.. Slave address
 * A0  -  Write Mode
 * A1  -  Read Mode
 */

void write_ext_eeprom(unsigned char address, unsigned char data) 
{
	i2c_start();
	i2c_write(SLAVE_WRITE);
	i2c_write(address);
	i2c_write(data);
	i2c_stop();
    for(int i = 3000; i-- ;);  //given in data sheet
}

unsigned char read_ext_eeprom(unsigned char address)
{
	unsigned char data;

	i2c_start();
	i2c_write(SLAVE_WRITE);
	i2c_write(address);
	i2c_rep_start();
	i2c_write(SLAVE_READ);
	data = i2c_read();
	i2c_stop();

	return data;
}