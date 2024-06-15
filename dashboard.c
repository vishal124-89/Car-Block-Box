/*
 * File:   dashboard.c
 * Author: Vishal
 *
 * Created on 22 May, 2024, 12:20 PM
 */

#include <xc.h>
#include "main.h"
#include "matrix_keypad.h"
#include "adc.h"
#include "clcd.h"
#include "ds1307.h"
#include "i2c.h"

extern unsigned char key;
unsigned char clock_reg[3];
unsigned char time[9];
int long adc_reg_val;
char j;
char i = 0; //new
unsigned char *event[] = {"ON", "GR", "GN", "G1", "G2", "G3", "G4", "-C"};

void speed_d(void) {
    adc_reg_val = read_adc(CHANNEL4) / 10.33;

    clcd_putch((adc_reg_val / 10 % 10) + 48, LINE2(14));
    clcd_putch((adc_reg_val % 10) + 48, LINE2(15));

}

void event_d(void) {

    unsigned char key;
    int flag = 0;
    key = read_switches(STATE_CHANGE);

    if (key == MK_SW2) {
        store_event();
        if (i < 6) {
            i++;
        }
    } else if (i < 7 && key == MK_SW3) {
        store_event();
        if (i > 1) {
            i--;
        }
    } else if (key == MK_SW1) {
        store_event();
        i = 7;
    }
    if (i == 7 && (key == MK_SW3 || key == MK_SW2)) {
        store_event();
        i = 2;
    }
    j = i;
    clcd_print(event[i], LINE2(10));
}

void get_time(void) {
    clock_reg[0] = read_ds1307(HOUR_ADDR);
    clock_reg[1] = read_ds1307(MIN_ADDR);
    clock_reg[2] = read_ds1307(SEC_ADDR);

    if (clock_reg[0] & 0x40) {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    } else {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    }
    time[2] = ':';
    time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
    time[4] = '0' + (clock_reg[1] & 0x0F);
    time[5] = ':';
    time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
    time[7] = '0' + (clock_reg[2] & 0x0F);
    time[8] = '\0';
}

void display_time(void) {
    clcd_print(time, LINE2(0));
}

void dashboard(char key) {
    clcd_print("TIME      EV  SP", LINE1(0));
    get_time();
    display_time();
    speed_d();
    event_d();
}



