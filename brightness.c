/*
 * File Name: IOs.c
 * Assignment: Project 1
 * Lab Section: B02
 * Completed by: Stephen Ravelo, Aaron Lauang, Alexa Gonzalez
 * Submission Date: October 26, 2025
 */

#include "brightness.h"
#include "IOs.h"
#include "ADC.h"
//timer 1

void setBrightness(void) {

    adc_changed = 0;   // clean flag
    uint16_t dutyC_ms = (uint16_t)((adc_value * 25) / 1024);
    
    while(!adc_changed && !CN_event){ //no adc value update
        //Disp2String("CN event: \n");
        //Disp2Dec(CN_event);
        do_ADC();
        if (dutyC_ms > 0) {
            if(curLED == 0)
            _LATB9 = 1;
            else
            _LATA6 = 1;
            delay_ms(dutyC_ms);
            if (adc_changed) break;

            if(curLED == 0)
            _LATB9 = 0;
            else
            _LATA6 = 0;
            delay_ms(25 - dutyC_ms);
            if (adc_changed) break;
        }
        else {
            if(curLED == 0)
            _LATB9 = 0;
            else
            _LATA6 = 0;
        }
    }
    return;
}
