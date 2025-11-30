/*
 * File Name: brightness.h
 * Assignment: Project 2
 * Lab Section: B02
 * Completed by: Stephen Ravelo, Aaron Lauang, Alexa Gonzalez
 * Submission Date: December 1, 2025
 */

#ifndef brightness_H 
#define brightness_H

#include <stdint.h>

// global variables
extern uint16_t CN_event;
extern uint16_t adc_value;

void setBrightness(void);

#endif /* brightness_H */
