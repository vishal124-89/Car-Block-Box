/*
 * File:   main.c
 * Author: Vishal
 *
 * Created on 20 May, 2024, 2:22 PM
 */

#include <xc.h>
#include "main.h"
#include "adc.h"
#include "clcd.h"
#include "ext_eeprom.h"
#include "matrix_keypad.h"
#include "ds1307.h"
#include "i2c.h"
#include "uart.h"

unsigned char key;
unsigned char main_f = 0, menu_f = 0;
int hour = 0, min = 0, sec = 0, delay;
extern unsigned char time[9];
extern char i;

void inti_config(void) {
    init_matrix_keypad();
    init_clcd();
    init_adc();
    TMR0IF = 0;
    T0CS = 0;
    init_i2c();
    init_ds1307();
    init_uart();
    write_ext_eeprom(0xC8, '0');
    write_ext_eeprom(0xC9, '0');
    write_ext_eeprom(0xCA, '0');
    write_ext_eeprom(0xCB, '0');

}

void main(void) {
    inti_config();
    char prev_key;
    int delay = 0;
    int k;
    while (1) {
        key = read_switches(LEVEL_CHANGE);
        if (key != ALL_RELEASED) //long press
        {
            prev_key = key;
            delay++;
            if (delay == 500) {
                key = key + 10;
            } else
                key = 0;   
        }
        else if (delay < 500 && delay != 0) {
            delay = 0;
            key = prev_key;
        } else {
            delay = 0;
        }

        if (main_f == DASHBOARD) {
            dashboard(key);

            if (key == MK_SW5)
                main_f = 1;
        }
        else if (main_f == PASSWORD) {
            password(key);

        }
        else if (main_f == MENU) {
            hour = (((time[0] - 48)*10)+ (time[1] - 48));
            min = (((time[3] - 48)*10)+ (time[4] - 48));
            sec = (((time[6] - 48)*10)+ (time[7] - 48));
            menu(key);
        }
        else if (main_f == MENU_ENTER) {

            if (menu_f == VIEWLOG) {
                view_log(key);
            } else if (menu_f == DOWNLOADLOG) {
                download_log();
            } else if (menu_f == CLEARLOG) {
                clear_log(key);
            } else if (menu_f == SETTIME) {
                settime(key);
            } else if (menu_f == CHANGEPASS) {
                change_pass(key);
            }
        }

    }
    return;
}

