/*
 * File Name: timer.c
 * Assignment: Project 2
 * Lab Section: B02
 * Completed by: Stephen Ravelo, Aaron Lauang, Alexa Gonzalez
 * Submission Date: December 1, 2025
 */

#include "timer.h"
#include "IOs.h"
#include "UART2.h"
#include "brightness.h"

uint16_t _skip_delay = 0;

uint16_t _T3_flag = 0;

void timerInit() {
    // TMR2 config
    T2CONbits.T32 = 0;
    T2CONbits.TCKPS = 3;    // set prescalar to 256
    T2CONbits.TCS = 0;
    T2CONbits.TGATE = 0;
    T2CONbits.TSIDL = 0;
    IPC1bits.T2IP = 2;
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1;
    
    // TMR3 config
    T2CONbits.T32 = 0; // operate timer 2 as 16 bit timer
    T3CONbits.TCKPS = 1; // set prescaler to 1:8
    T3CONbits.TCS = 0; // use internal clock
    T3CONbits.TSIDL = 0; //operate in idle mode
    IPC2bits.T3IP = 2; //7 is highest and 1 is lowest pri.
    IFS0bits.T3IF = 0;
    IEC0bits.T3IE = 1; //enable timer interrupt
    PR3 = 15625; // set the count value for 0.5 s (or 500 ms)
    TMR3 = 0;
    T3CONbits.TON = 0;
}

void delay_ms(uint16_t time_ms) {
    PR2 = 1 * time_ms;      // PR2 coefficient: 1 ~= 0.001 * 250000 / 256
    TMR2 = 0;
    
    T2CONbits.TON = 1;
    
    // Idle until timer 2 interrupt or valid input detected
    while (T2CONbits.TON == 1) {
        Idle();
        if (check_IO_finished()) { 
            break; 
        }
        
        if (_T3_flag) {
            Disp2Dec(adc_value);
            XmitUART2(_LED_ON + 0x30, 1);
            XmitUART2('\n', 1);
            _T3_flag = 0;
        }
    }
    
    return;
}
