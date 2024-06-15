/*
 * File:   clear_log.c
 * Author: Vishal
 *
 * Created on 22 May, 2024, 12:19 PM
 */


#include <xc.h>
#include "main.h"
#include "clcd.h"
extern char overflow;
extern char j,lap;
extern unsigned char main_f;
void clear_log(char key)
{
    overflow=0;
     lap=0;
     
     clcd_print("Cleared log", LINE1(0));
     
     for(long int i=100000;i--;);
     main_f=2;
     
}