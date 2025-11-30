/*
 * File Name: timer.h
 * Assignment: Project 2
 * Lab Section: B02
 * Completed by: Stephen Ravelo, Aaron Lauang, Alexa Gonzalez
 * Submission Date: December 1, 2025
 */

#ifndef TIMER_H
#define	TIMER_H

#include <xc.h>

extern uint16_t _skip_delay;

extern uint16_t _T3_flag;

void timerInit();
void delay_ms();
void delay_ms_T1();

#endif	/* TIMER_H */

