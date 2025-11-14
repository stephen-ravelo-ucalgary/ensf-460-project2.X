/*
 * File Name: IOs.c
 * Assignment: Project 1
 * Lab Section: B02
 * Completed by: Stephen Ravelo, Aaron Lauang, Alexa Gonzalez
 * Submission Date: October 26, 2025
 */

#include "brightness.h"

void setBrightness(uint16_t ADC_val) {    
    // dutyC in milliseconds (0?25)
    uint16_t dutyC_ms = (uint16_t)((ADC_val * 25) / 1024);

    // total time we want the function to run (1000 ms)
    uint16_t elapsed = 0;

    while (elapsed < 1000) {   // run for 1 second

        if (dutyC_ms > 0) {
            _LATB9 = 1;
            delay_ms(dutyC_ms);
            elapsed += dutyC_ms;

            _LATB9 = 0;
            delay_ms(25 - dutyC_ms);
            elapsed += (25 - dutyC_ms);
        }
        else {
            // duty = 0 ? LED off
            _LATB9 = 0;
            delay_ms(25);
            elapsed += 25;
        }
    }

    return; // returns to main
}

    

