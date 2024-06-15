/*
 * File:   store_event.c
 * Author: Vishal
 *
 * Created on 22 May, 2024, 12:46 PM
 */


#include <xc.h>
#include "main.h"
#include "ext_eeprom.h"
#include "adc.h"

extern unsigned char time[9];
extern unsigned char *event[];
extern int long adc_reg_val;
char arr[10];
char lap = 0, overflow = 0;
extern char j;
extern char i;

void store_event() {
    int hour, min, sec, pot;
    hour = (((time[0] - 48)*10)+(time[1] - 48));
    min = (((time[3] - 48)*10)+(time[4] - 48));
    sec = (((time[6] - 48)*10)+(time[7] - 48));
    pot = adc_reg_val;

    arr[0] = hour;
    arr[1] = min;
    arr[2] = sec;
    arr[3] = j;
    arr[4] = pot;
    for (char i = 0; i < 5; i++) {
        write_ext_eeprom((lap * 10) + i, arr[i]);
    }
    
    lap++;
    if (lap == 10) {
        lap = 0;
        overflow = 1;
    }
}