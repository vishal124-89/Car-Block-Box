/*
 * File:   password.c
 * Author: Vishal
 *
 * Created on 22 May, 2024, 12:44 PM
 */


#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "ext_eeprom.h"

extern unsigned char key;
extern unsigned char var;
extern unsigned char main_f;

int my_strcmp(char* pass, char* check) {
    int i = 0;
    while ((pass[i] || check[i]) && i<4) {
        if (pass[i] != check[i]) {
            return (pass[i] - check[i]);
        }
        i++;
    }
    return 0;
}

void password(char key) {
    CLEAR_DISP_SCREEN;
    char pass[4] ;
  
        pass[0]=read_ext_eeprom(0xC8);
       pass[1]=read_ext_eeprom(0xC9);
        pass[2]=read_ext_eeprom(0xCA);
        pass[3]=read_ext_eeprom(0xCB);
    

    char check[4];
    int i = 0;
    int chance = 3;
    unsigned long int delay, wait;
    unsigned long int count = 0;

    while (1) {

        key = read_switches(STATE_CHANGE);
        if (i < 4) {
            clcd_print(" Enter Passward ", LINE1(0));

            if (delay++ < 500) //for showing blinking _
            {
                clcd_putch('_', LINE2(i));
            } else if (delay > 500 && delay < 1000) {
                clcd_putch(' ', LINE2(i));
            } else
                delay = 0;

            if (count++ == 10000) {
                CLEAR_DISP_SCREEN;
                count = 0;
                main_f = 0;
                return;
            }
            if (key == MK_SW5) {
                count = 0;
                check[i] = '0';
                clcd_putch('*', LINE2(i));
                i++;
            } else if (key == MK_SW6) {
                count = 0;
                check[i] = '1';
                clcd_putch('*', LINE2(i));
                i++;
            }
        }
        if (i == 4) {
            for (unsigned long int i = 50000; i--;); 
            if (my_strcmp(pass, check) == 0) 
            {
                clcd_print("     SUCCESS     ", LINE1(0));
                main_f = 2;
                CLEAR_DISP_SCREEN;
                return;
            } else {
                CLEAR_DISP_SCREEN;

                if (chance == 1) {

                    TMR0ON = 1;
                    GIE = 1;
                    PEIE = 1;
                    TMR0IE = 1;
                    clcd_print("You are Blocked", LINE1(0));
                    clcd_putch((var / 100) + 48, LINE2(5));
                    clcd_putch((var / 10) % 10 + 48, LINE2(6));
                    clcd_putch((var % 10) + 48, LINE2(7));
                    clcd_print("sec", LINE2(9));

                    if (var == 0) {
                        i = 0;
                        var = 180;
                        chance = 3;
                        TMR0ON = 0;
                        GIE = 0;
                        PEIE = 0;
                        TMR0IE = 0;
                        CLEAR_DISP_SCREEN;
                    }
                }
                else {
                    chance--;
                    i = 0;
                    clcd_print("Password Wrong", LINE1(0));
                    clcd_putch('0' + (chance % 10), LINE2(0)); 
                    clcd_print("Chances Left ", LINE2(3)); 
                    for (unsigned long long int wait = 500000; wait--;);
                    CLEAR_DISP_SCREEN;
                }
            }
        }
    }
}

