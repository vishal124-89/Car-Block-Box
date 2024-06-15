#ifndef EEPROM_H
#define EEPROM_H

#define SLAVE_READ		0xA1
#define SLAVE_WRITE		0xA0

void write_ext_eeprom(unsigned char address, unsigned char data); 
unsigned char read_ext_eeprom(unsigned char address);

#endif