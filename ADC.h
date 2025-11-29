/*
 * File Name: ADC.h
 * Assignment: Assignment 4
 * Lab Section: B02
 * Completed by: Stephen Ravelo, Aaron Lauang, Alexa Gonzalez
 * Submission Date: November 7, 2025
 */

#ifndef ADC_H
#define	ADC_H

#include "UART2.h"

extern uint16_t _AD1_interrupt;

uint16_t do_ADC(void);
void read_ADC();

#endif	/* ADC_H */

