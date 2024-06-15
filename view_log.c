/*
 * File:   view_log.c
 * Author: Vishal
 *
 * Created on 22 May, 2024, 12:46 PM
 */


#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "ext_eeprom.h"
#include "matrix_keypad.h"

static char arr[10];
extern char lap;
extern char overflow;
extern unsigned char main_f;
extern char overflow;
extern char i;
extern char j;
extern char *event[];

void view_log(char key) {
    static char axis_ind = 0;
    clcd_print("View Log", LINE1(4));
    
    if (axis_ind < lap +1) {
        clcd_putch(axis_ind + 48, LINE2(0));
        for (int i = 0; i < 5; i++) {
            clcd_putch(axis_ind + 48, LINE2(0));
            arr[i] = read_ext_eeprom((axis_ind * 10) + i);
        }

        clcd_putch(arr[0] / 10 + 48, LINE2(2));
        clcd_putch(arr[0] % 10 + 48, LINE2(3));
        clcd_print(":", LINE2(4));
        clcd_putch(arr[1] / 10 + 48, LINE2(5));
        clcd_putch(arr[1] % 10 + 48, LINE2(6));
        clcd_print(":", LINE2(7));
        clcd_putch(arr[2] / 10 + 48, LINE2(8));
        clcd_putch(arr[2] % 10 + 48, LINE2(9));
        clcd_print(event[arr[3]], LINE2(11));
        clcd_putch(arr[4] / 10 + 48, LINE2(14));
        clcd_putch(arr[4] % 10 + 48, LINE2(15));

        if (axis_ind < 10) {
            if (key == MK_SW6) {
                axis_ind++;
            }
        }
    }

    if (axis_ind > 0) {
        if (key == MK_SW5) {
            axis_ind--;
            i--;
        }
    }
    if (key == L_16) {
        main_f = 2;
    }
}
