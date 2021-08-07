/*
 * File:   main.c
 * Author: Mateusz Szymiec
 *
 * Created on July 24, 2021, 1:23 AM
 */

#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR (((F_CPU / (16UL * BAUD))) - 1)    //equations for calculating baud rate register setting

#define SIG_LED PB1
#define FUN_BTN PB2
#define BUZZER PD6

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*
FUSES = {
	.low = 0xFF, // LOW {SUT_CKSEL=EXTXOSC_8MHZ_XX_16KCK_14CK_65MS, CKOUT=CLEAR, CKDIV8=CLEAR}
	.high = 0x99, // HIGH {BOOTRST=CLEAR, BOOTSZ=2048W_3800, EESAVE=CLEAR, WDTON=CLEAR, SPIEN=SET, JTAGEN=SET, OCDEN=CLEAR}
	.extended = 0xF7, // EXTENDED {BODLEVEL=DISABLED, CFD=CFD_DISABLED}
};

LOCKBITS = 0xFF; // {LB=NO_LOCK, BLB0=NO_LOCK, BLB1=NO_LOCK}
*/

void timer0_init(void);
void usart_init(void);
void usart_transmit(uint8_t data);
uint8_t usart_receive();

int main(void) {
    
    DDRB = (1 << DDB1);
    
    timer0_init();
    usart_init();
    
    sei();

    while (1) {

    }
    
    return(0);
}

void timer0_init(void) {
    TCCR0B |= (1 << CS02) | (1 << CS00);
    TIMSK0 |= (1<<TOIE0);
}

void usart_init(void) {
    //set baud rate
    UBRR0H = (UBRR >> 8);;
    UBRR0L = UBRR;
    
    //enable transmitter and receiver
    UCSR0B = (1 << RXCIE) | (1 << RXEN) | (1 << TXEN);
    
    //set frame format: 8 data, 1 stop bit
    UCSR0C = (3 << UCSZ0);
}

void usart_transmit(uint8_t data) {
    //wait for empty transmit buffer
    while (!( UCSR0A & (1<<UDRE)));
    //put data into buffer, sends the data
    UDR0 = data;
}

uint8_t usart_receive(void) {
    //get and return received data from buffer
    return UDR0;
}

ISR(TIMER0_OVF_vect) 
{    
    usart_transmit((PINB & (1 << PB1)));
}

ISR(USART0_RX_vect) {
    uint8_t command;
    command = usart_receive();
    
    if (command == 0x00) {
        PORTB ^= (1 << SIG_LED);
    }
}