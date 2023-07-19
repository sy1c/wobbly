/*
 * File:   main.c
 * Author: Mateusz Szymiec
 *
 * Created on July 24, 2021, 1:23 AM
 */

#define F_CPU 16000000UL
#define BAUD 9600

#define BATT PA0
#define STATE_LED PB0
#define SIG_LED PB1
#define FUN_BTN PB2
#define BUZZER PD6

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "imu.h"
#include "twi.h"
#include "adc.h"
#include "timer.h"
#include "usart.h"
#include "motors.h"
#include "encoders.h"

/*
FUSES = {
	.low = 0xFF, // LOW {SUT_CKSEL=EXTXOSC_8MHZ_XX_16KCK_14CK_65MS, CKOUT=CLEAR, CKDIV8=CLEAR}
	.high = 0xD9, // HIGH {BOOTRST=CLEAR, BOOTSZ=2048W_3800, EESAVE=CLEAR, WDTON=CLEAR, SPIEN=SET, JTAGEN=CLEAR, OCDEN=CLEAR}
	.extended = 0xF7, // EXTENDED {BODLEVEL=DISABLED, CFD=CFD_DISABLED}
};

LOCKBITS = 0xFF; // {LB=NO_LOCK, BLB0=NO_LOCK, BLB1=NO_LOCK}
*/

uint16_t left_speed, right_speed;

void state(uint8_t batt);

int main(void) {
    
    DDRA &= ~(1 << BATT);
    DDRB |= (1 << STATE_LED) | (1 << SIG_LED);
    DDRB &= ~(1 << FUN_BTN);
    
    timer1_init();
    timer3_init();
    usart_init();
    twi_init();
    adc_init();
    motors_init();
    encoders_init();
    
    imu_init();
    
    imu_calibrate();
   
    _delay_ms(1000);
    
    sei();
    
    while (1) {
        state(ADCH);
        
        if (PINB & (1 << FUN_BTN)) {
            PORTC &= ~(1 << MOTL_F);
            PORTC &= ~(1 << MOTL_R);
            PORTC &= ~(1 << MOTR_F);
            PORTC &= ~(1 << MOTR_R);
        }
        else {
            motors_set_speed(128, 128);
            PORTC |= (1 << MOTL_F) | (1 << MOTR_F);
        }
        
        usart_transmit(right_speed);
    }
    
    return(0);
}


void state(uint8_t batt) {
    if (batt > 198) {
        PORTB |= (1 << STATE_LED);
    }
    else {
        PORTB &= ~(1 << STATE_LED);
    }
}

//ISR(TIMER0_OVF_vect) {    
//    
//}

ISR(TIMER3_COMPA_vect) {
    imu_read();
    imu_integrate_gyro();
    
    right_speed = encoders_right_counts();
}

ISR(USART0_RX_vect) {
    uint8_t command;
    command = usart_receive();
    
    if (command == 0x00) {
        PORTB ^= (1 << SIG_LED);
    }
}
