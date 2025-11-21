/*
 * File Name: IOs.h
 * Assignment: Assignment 4
 * Lab Section: B02
 * Completed by: Stephen Ravelo, Aaron Lauang, Alexa Gonzalez
 * Submission Date: November 7, 2025
 */

#ifndef IOS_H
#define	IOS_H

#include <xc.h>
#include "clkChange.h"
#include "UART2.h"
#include "timer.h"

typedef enum {
    STATE_OFF,
    STATE_ON_LED1,     
    STATE_ON_LED2,     
    STATE_ON_BLINKING_LED1,     
    STATE_ON_BLINKING_LED2,     
    STATE_OFF_BLINKING_LED1,     
    STATE_OFF_BLINKING_LED2
} state_t;

extern state_t _state;

extern uint16_t _IO_finished;

extern uint16_t _PB1_short;
extern uint16_t _PB1_long;
extern uint16_t _PB2_short;
extern uint16_t _PB3_short;

extern uint16_t _curLED;

void IOinit();
void IOcheck();
void IOclear();
uint16_t check_IO_finished();

#endif
