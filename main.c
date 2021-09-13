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


/*
FUSES = {
	.low = 0xFF, // LOW {SUT_CKSEL=EXTXOSC_8MHZ_XX_16KCK_14CK_65MS, CKOUT=CLEAR, CKDIV8=CLEAR}
	.high = 0x99, // HIGH {BOOTRST=CLEAR, BOOTSZ=2048W_3800, EESAVE=CLEAR, WDTON=CLEAR, SPIEN=SET, JTAGEN=SET, OCDEN=CLEAR}
	.extended = 0xF7, // EXTENDED {BODLEVEL=DISABLED, CFD=CFD_DISABLED}
};

LOCKBITS = 0xFF; // {LB=NO_LOCK, BLB0=NO_LOCK, BLB1=NO_LOCK}
*/

volatile int16_t g_x, g_y, g_z;

ISR(USART0_RX_vect) {
    uint8_t command;
    command = usart_receive();
    
    if (command == 0x00) {
        PORTB ^= (1 << SIG_LED);
    }
}

void state(uint8_t batt);

int main(void) {
    
    DDRA &= ~(1 << BATT);
    DDRB |= (1 << STATE_LED) | (1 << SIG_LED);
    DDRB &= ~(1 << FUN_BTN);
    
    //timer0_init();
    usart_init();
    twi_init();
    adc_init();
    
    imu_init();
    
    sei();
    
    while (1) {
        state(ADCH);
        
        //g_x = imu_receive(LSM6DS33_OUTX_L_G) / 29;
        g_y = imu_receive(LSM6DS33_OUTY_L_G) / 29;
        //g_z = imu_receive(LSM6DS33_OUTZ_L_G);
        
        usart_transmit(g_y);
        
        _delay_ms(20);
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
//    usart_transmit(data);
//}
