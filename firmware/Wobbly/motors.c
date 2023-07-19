#include <avr/io.h>
#include "motors.h"

void motors_init(void) {
    DDRC |= (1 << MOTL_F) | (1 << MOTL_R) | (1 << MOTR_F) | (1 << MOTR_R);
    DDRD |= (1 << MOTL_PWM) | (1 << MOTR_PWM);
    
    PORTC &= ~(1 << MOTL_F);
    PORTC &= ~(1 << MOTL_R);
    PORTC &= ~(1 << MOTR_F);
    PORTC &= ~(1 << MOTR_R);
}

void motors_left_speed(uint8_t speed) {
    OCR1B = speed;
}

void motors_right_speed(uint8_t speed) {
    OCR1A = speed;
}

void motors_set_speed(uint8_t left_speed, uint8_t right_speed) {
    motors_left_speed(left_speed);
    motors_right_speed(right_speed);
}