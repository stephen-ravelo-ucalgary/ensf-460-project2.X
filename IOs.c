/*
 * File Name: IOs.c
 * Assignment: Project 1
 * Lab Section: B02
 * Completed by: Stephen Ravelo, Aaron Lauang, Alexa Gonzalez
 * Submission Date: October 26, 2025
 */

#include "IOs.h"

state_t _state;
uint16_t _IO_finished = 1;

uint16_t curLED = 0;

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
uint16_t IOcheck() {
    if (_state == STATE_OFF) {
        if (PORTBbits.RB7 == 0 && PORTBbits.RB4 == 1 && PORTAbits.RA4 == 1) {
            if (curLED == 0)
                return 1;
            else if (curLED == 1)
                return 2;
        }
    }
    else if (_state == STATE_ON_LED1 || _state == STATE_ON_LED2) {
        uint16_t count = 0;
        if (PORTBbits.RB7 == 0 && PORTBbits.RB4 == 1 && PORTAbits.RA4 == 1) {
            while (PORTBbits.RB7 == 0 && PORTBbits.RB4 == 1 && PORTAbits.RA4 == 1) {
                if (count == 60) {
                    return 2; // TODO: change
                }
                delay_ms(50);
                count++;
            }
            
            if(count < 60) {
                return 1;
            }
            
            count = 0;
        }
    }
    
    _IO_finished = 1;
    return 0;
}

uint16_t check_IO_finished() {
    if (_IO_finished && (PORTBbits.RB7 == 0 || PORTBbits.RB4 == 0 || PORTAbits.RA4 == 0)) {
        _IO_finished = 0;
        return 1;
    }
    
    return 0;
}