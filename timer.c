#include "timer.h"

void timer0_init(void) {
    TCCR0B |= (1 << CS02) | (1 << CS00);
    TIMSK0 |= (1 << TOIE0);
}

void timer1_init(void) {
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1);
    TCCR1A |= (1 << WGM10);
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS12) | (1 << CS10);
    OCR1A = 0;
    OCR1B = 0;
}

void timer3_init(void) {
    TCCR3B |= (1 << WGM32); 
    TCCR3B |= (1 << CS32) | (1 << CS30);
    OCR3A = 156;
    TIMSK3 |= (1 << OCIE3A);
}