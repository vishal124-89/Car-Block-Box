/*
 * File:   download_log.c
 * Author: Vishal
 *
 * Created on 22 May, 2024, 12:27 PM
 */

#include <xc.h>
#include "main.h"
#include "uart.h"
#include "clcd.h"
#include "ext_eeprom.h"
#include "clcd.h"
char arr[10];
extern unsigned char demo;
extern unsigned char main_f;
extern char lap;
extern char overflow;
extern char *event[];

void download_log() {
    static int i = 0, j = 0, k = 2;
    static char ch, axis_ind = 0,dem;

    if (overflow == 1)
       dem= lap;
    else
        dem=lap;
    clcd_print("Download Log", LINE1(0));
    
    
    for (j= 0; j < dem; j++) {
        for (int i = 0; i < 5; i++) {
            arr[i] = read_ext_eeprom((axis_ind * 10) + i);
        }
        if(axis_ind < dem)
        {
            axis_ind++;
        putch(arr[0]/10 + 48);
        putch(arr[0]%10 + 48);
        putch(':');
        putch(arr[1]/10 + 48);
        putch(arr[1]%10 + 48);
        putch(':');
        putch(arr[2]/10 + 48);
        putch(arr[2]%10 + 48);
        putch(' ');
        puts(event[arr[3]]);
        putch(' ');
        putch(arr[4]/10 + 48);
        putch(arr[4]%10 + 48);
        puts("\n\r"); 
        }
    }
        __delay_us(900000);
    main_f = 2;

}
