/*
 * File Name: IOs.c
 * Assignment: Project 2
 * Lab Section: B02
 * Completed by: Stephen Ravelo, Aaron Lauang, Alexa Gonzalez
 * Submission Date: December 1, 2025
 */

#include "IOs.h"

state_t _state;
uint16_t _IO_finished = 1;

uint16_t _PB1_short = 0;
uint16_t _PB1_long = 0;
uint16_t _PB2_short = 0;
uint16_t _PB3_short = 0;

uint16_t _curLED = 0;
uint16_t _LED_ON = 0;

// Initialize peripheral IO
void IOinit() {
    // LED1
    TRISBbits.TRISB9 = 0;
    
    // LED2
    TRISAbits.TRISA6 = 0;

    // PB1
    TRISBbits.TRISB7 = 1;
    CNPU2bits.CN23PUE = 1;
    CNEN2bits.CN23IE = 1;  
    
    // PB3
    TRISBbits.TRISB4 = 1;
    CNPU1bits.CN1PUE = 1;
    CNEN1bits.CN1IE = 1;
    
    // PB3
    TRISAbits.TRISA4 = 1;
    CNPU1bits.CN0PUE = 1;
    CNEN1bits.CN0IE = 1;
}

// Execute logic for peripheral IO
void IOcheck() {
    uint16_t count = 0;
    if (PORTBbits.RB7 == 0 && PORTBbits.RB4 == 1 && PORTAbits.RA4 == 1) {
        while (PORTBbits.RB7 == 0 && PORTBbits.RB4 == 1 && PORTAbits.RA4 == 1) {
            if (count == 60) {
                _PB1_long = 1;
                break;
            }
            delay_ms(50);
            count++;
        }

        if(count < 60) {
            _PB1_short = 1;
        }

        count = 0;
    }
    
    if (PORTBbits.RB7 == 1 && PORTBbits.RB4 == 0 && PORTAbits.RA4 == 1) {
        _PB2_short = 1;
    }
    
    if (PORTBbits.RB7 == 1 && PORTBbits.RB4 == 1 && PORTAbits.RA4 == 0) {
        _PB3_short = 1;
    }
    
    _IO_finished = 1;
}

void IOclear() {
    _PB1_short = 0;
    _PB1_long = 0;
    _PB2_short = 0;
    _PB3_short = 0;
}

uint16_t check_IO_finished() {
    if (_IO_finished && (PORTBbits.RB7 == 0 || PORTBbits.RB4 == 0 || PORTAbits.RA4 == 0)) {
        _IO_finished = 0;
        return 1;
    }
    
    return 0;
}