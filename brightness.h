/*
 * File Name: brightness.h
 * Assignment: Assignment 4
 * Lab Section: B02
 * Completed by: Stephen Ravelo, Aaron Lauang, Alexa Gonzalez
 * Submission Date: November 7, 2025
 */

#ifndef brightness_H 
#define brightness_H

#include <stdint.h>

// global variables
extern volatile uint16_t adc_value;
extern volatile uint8_t adc_changed;
extern volatile uint8_t curLED;

void setBrightness(void);

#endif /* brightness_H */
