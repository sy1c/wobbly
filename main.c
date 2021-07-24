/*
 * File:   main.c
 * Author: matts
 *
 * Created on July 24, 2021, 1:23 AM
 */

#define F_CPU 1000000UL

//#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRD = 1 << DDB1;
    
    while (1) {
        PORTB = 1 << PB1;
        _delay_ms(100);
        PORTB = 0 << PB1;
        _delay_ms(100);
    }
}