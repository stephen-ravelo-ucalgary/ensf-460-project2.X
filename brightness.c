/*
 * File Name: brightness.c
 * Assignment: Project 2
 * Lab Section: B02
 * Completed by: Stephen Ravelo, Aaron Lauang, Alexa Gonzalez
 * Submission Date: December 1, 2025
 */

#include "brightness.h"
#include "IOs.h"
#include "ADC.h"
#include "UART2.h"
//timer 1

void setBrightness(void) {
    uint16_t dutyC_ms = (uint16_t)((do_ADC() * 25) / 1024);
   
    if (dutyC_ms > 0) {
        if(_curLED == 0)
            _LATB9 = 1;
        else
            _LATA6 = 1;
        
        delay_ms(dutyC_ms);
        
        if (!CN_event) { 
            if(_curLED == 0)
                _LATB9 = 0;
            else
                _LATA6 = 0;

            delay_ms(25 - dutyC_ms);
        }
    }
    else {
        if(_curLED == 0)
            _LATB9 = 0;
        else
            _LATA6 = 0;
    }
    
    return;
}
