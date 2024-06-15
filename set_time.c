/*
 * File:   set_time.c
 * Author: Vishal
 *
 * Created on 22 May, 2024, 12:45 PM
 */


#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "adc.h"
#include "ds1307.h"
#include "i2c.h"
extern int hour,min,sec;
extern unsigned char time[9];
extern unsigned char main_f = 0, menu_f = 0;
void settime(char key)
{
    char dummy;
    static int delay;
    static int field_flag = 0;
    static flag=0;
    unsigned short int d_hour,d_min,d_sec;
    clcd_print("HH:MM:SS", LINE1(0));
    clcd_putch(':', LINE2(2));
    clcd_putch(':', LINE2(5));
    if(flag == 0)
    {
    clcd_putch(48+sec/10, LINE2(6));
    clcd_putch(48+sec%10, LINE2(7));
    clcd_putch(48+hour/10, LINE2(0));
    clcd_putch(48+hour%10, LINE2(1));
    clcd_putch(48+min/10, LINE2(3));
    clcd_putch(48+min%10, LINE2(4));
    flag=1;
    }
        
        if(key == MK_SW6)
        {
            clcd_putch(48+hour/10, LINE2(0));
            clcd_putch(48+hour%10, LINE2(1));
            clcd_putch(48+min/10, LINE2(3));
            clcd_putch(48+min%10, LINE2(4));
            clcd_putch(48+sec/10, LINE2(6));
            clcd_putch(48+sec%10, LINE2(7));
              field_flag ++;
        }
    if(field_flag==4)
        field_flag=1;
    
            if(field_flag == 1)
            { 
                if (delay++ < 1000) 
            { 
                clcd_putch(48+hour/10, LINE2(0));
                clcd_putch(48+hour%10, LINE2(1));
                    
            } else if (delay > 1000 && delay < 2000) {
                clcd_putch(' ', LINE2(0));
                clcd_putch(' ', LINE2(1));
            } else
                delay = 0;
            
                if(key == MK_SW5 )
                    hour++;
                
                if(hour > 23)
                    hour = 0;
                if(hour < 0)
                    hour = 23;
            }
        
            if(field_flag == 2)
            { 
                if (delay++ < 1000) //for showing blinking _
            { 
                clcd_putch(48+min/10, LINE2(3));
                clcd_putch(48+min%10, LINE2(4));
            } else if (delay > 1000 && delay < 2000) {
                clcd_putch(' ', LINE2(3));
                clcd_putch(' ', LINE2(4));
            } else
                delay = 0;
                
                if(key == MK_SW5 )
                    min++;
                
                if(min > 59)
                    min = 0;
                if(min < 0)
                    min = 59;
            }
        
                
            if(field_flag == 3)
            { 
                if (delay++ < 1000) //for showing blinking _
            { 
                clcd_putch(48+sec/10, LINE2(6));
                clcd_putch(48+sec%10, LINE2(7));
            } else if (delay > 1000 && delay < 2000) {
                clcd_putch(' ', LINE2(6));
                clcd_putch(' ', LINE2(7));
            } else
                delay = 0;
                
                if(key == MK_SW5 )
                    sec++;
                
                if(sec > 59)
                    sec = 0;
                if(sec < 0)
                    sec = 59;
            }
        
        if(key == L_15)
        {
            CLEAR_DISP_SCREEN;
            write_ds1307( HOUR_ADDR, ((hour/10 <<4 ) | (hour%10)));
            write_ds1307( MIN_ADDR, ((min/10 <<4)| (min%10)));
            write_ds1307( SEC_ADDR, ((sec/10 <<4) | (sec%10)));
            clcd_print("SET TIME SUCCESS", LINE1(0));
            field_flag=0;
            __delay_us(900000);
            main_f=0;
        }
}    


       
                