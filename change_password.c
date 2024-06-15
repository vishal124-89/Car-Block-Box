/*
 * File:   change_password.c
 * Author: Vishal
 *
 * Created on 22 May, 2024, 12:16 PM
 */

#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "ext_eeprom.h"
#include "string.h"

int k;
char pass[5] = {};
char check[5] = {};
static unsigned long int wait;
static unsigned long int count = 0;
extern unsigned char main_f;

int myi_strcmp(char* pass, char* check) {
    int i = 0;
    while (pass[i] || check[i]) {
        if (pass[i] != check[i]) {
            return (pass[i] - check[i]);
        }
        i++;
    }
    return 0;
}

void change_pass(char key) {

    static int i = 0, j = 0;
    int delay; //static delay
    if (delay++ == 1000) {
        CLEAR_DISP_SCREEN;
        delay = 0;
    }

    if (i < 4) {
        clcd_print(" Enter Password ", LINE1(0));

        if (wait++ < 500) //for showing blinking _
        {
            clcd_putch('_', LINE2(i));
        } else if (wait > 500 && wait < 1000) {
            clcd_putch(' ', LINE2(i));
        } else
            wait = 0;

        if (key == MK_SW5) {
            pass[i] = '0';
            clcd_putch('*', LINE2(i));
            i++;
        } else if (key == MK_SW6) {
            pass[i] = '1';
            clcd_putch('*', LINE2(i));
            i++;
        }
        if (i == 4)
            CLEAR_DISP_SCREEN;
    } else if (i == 4) {
        delay = 1000; //delay=0;
        pass[i] = '\0';
        i++;
    } else if (j < 4) {

        clcd_print("Re-Enter Password ", LINE1(0));

        if (wait++ < 500) //for showing blinking
        {
            clcd_putch('_', LINE2(j));
        } else if (wait > 500 && wait < 1000) {
            clcd_putch(' ', LINE2(j));
        } else
            wait = 0;

        if (key == MK_SW5) {
            check[j] = '0';
            clcd_putch('*', LINE2(j));
            j++;
        } else if (key == MK_SW6) {
            check[j] = '1';
            clcd_putch('*', LINE2(j));
            j++;
        }
        if (j == 4)
            CLEAR_DISP_SCREEN;
    } else if (j == 4) {
        delay = 1000;
        pass[j] = '\0';
        j++;
    } else {
        for (unsigned long int i = 50000; i--;);
        if (myi_strcmp(pass, check) == 0) {
            i = j = 0;
            write_ext_eeprom(0xC8, pass[0]);
            write_ext_eeprom(0xC9, pass[1]);
            write_ext_eeprom(0xCA, pass[2]);
            write_ext_eeprom(0xCB, pass[3]);

            clcd_print(" PASSWORD CHANGED ", LINE1(0));
            __delay_us(500000);
            main_f = 2;
        } else {
            i = j = 0;
            clcd_print(" PASSWORD WRONG ", LINE1(0));
            __delay_us(500000);
            main_f = 2;
        }
    }
}









