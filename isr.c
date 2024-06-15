/*
 * File:   isr.c
 * Author: Vishal
 *
 * Created on 14 May, 2024, 3:38 PM
 */


#include <xc.h>
#include "timer0.h"

unsigned char var=180;
int count=0,count1=0;
void __interrupt() isr(void) {
   
    if(TMR0IF)
    {
        TMR0 = TMR0 + 8;
        
        if(count++ == 20000)
        {
            var--;
            count=0;
        }
        TMR0IF = 0;
    }
    if(TMR2IF)
    {
        if(count1++ == 20000)
        {
            var--;
            count1=0;
        }
        TMR2IF = 0;
    }
}
