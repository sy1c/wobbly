#include <avr/io.h>
#include <avr/interrupt.h>
#include "general.h"
#include "encoders.h"
#include "usart.h"

ISR(INT0_vect) {
    uint8_t new_right_B = is_high(PINE, ENCR_B);
    uint8_t new_right_A = is_high(PIND, ENCR_XOR) ^ new_right_B;

    right_count += (right_A ^ new_right_B) - (new_right_A ^ right_B);
    
    right_A = new_right_A;
    right_B = new_right_B;
}

ISR(INT1_vect) {
    uint8_t new_left_B = is_high(PINE, ENCL_B);
    uint8_t new_left_A = is_high(PIND, ENCL_XOR) ^ new_left_B;

    left_count += (left_A ^ new_left_B) - (new_left_A ^ left_B);

    left_A = new_left_A;
    left_B = new_left_B;
}

void encoders_init(void) {
    DDRD &= ~((1 << ENCL_XOR) | (1 << ENCR_XOR));
    DDRE &= ~((1 << ENCL_B) | (1 << ENCR_B));
    
    PORTD |= (1 << ENCL_XOR) | (1 << ENCR_XOR);
    PORTE |= (1 << ENCL_B) | (1 << ENCR_B);
    
    EICRA |= (1 << ISC00);
    EICRA |= (1 << ISC10);
    EIMSK |= (1 << INT1) | (1 << INT0);
    
    left_B = is_high(PINE, ENCL_B);
    left_A = is_high(PIND, ENCL_XOR) ^ left_B;
    left_count = 0;

    right_B = is_high(PINE, ENCR_B);
    right_A = is_high(PIND, ENCR_XOR) ^ right_B;
    right_count = 0;
}

int16_t encoders_left_counts(void) {
    cli();
    int16_t counts = left_count;
    left_count = 0;
    sei();
    return counts;
}

int16_t encoders_right_counts(void) {
    cli();
    int16_t counts = right_count;
    right_count = 0;
    sei();
    return counts;
}