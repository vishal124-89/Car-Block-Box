/*
 * File:   menu.c
 * Author: Vishal
 *
 * Created on 22 May, 2024, 12:32 PM
 */


#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"

extern unsigned char main_f,menu_f;
void menu(char key) {
    //clcd_print("menu",LINE1(0));
    char menu[5][17] = {"View Log     ", "Download Log    ", "Clear Log     ", "Set Time       ", "Change Password"};
    static unsigned char star = 0,i = 0,d;

    if (star == 0) {
        clcd_print("*", LINE1(0));
        clcd_print(" ", LINE2(0));
    } else {
        clcd_print(" ", LINE1(0));
        clcd_print("*", LINE2(0));
    }
    clcd_print(menu[i], LINE1(1));
    clcd_print(menu[i + 1], LINE2(1));
    if (key == MK_SW6) {
        if (star == 0) {
            star = 1;
        } else if (i < 3) {
            i++;
            d=i;
        }
    }
    if (key == MK_SW5) {
        if (star == 1) {
            star = 0;
        } else if (i > 0) {
            i--;
            d=i;
        }
    }
    
    if(key == L_15)
    {
        CLEAR_DISP_SCREEN;
        main_f=3;
        menu_f=star +i;
    }
    if(key == L_16)
    {
        CLEAR_DISP_SCREEN;
        main_f=0;
    }
}