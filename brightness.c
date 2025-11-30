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

uint16_t CN_event;
uint16_t adc_value = 0;

void setBrightness(void) {
    adc_value = do_ADC();
    uint16_t dutyC_ms = (uint16_t)((adc_value * 25) / 1024);
   
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
