/* 
 * File:   usart.h
 * Author: matts
 *
 * Created on August 9, 2021, 9:57 PM
 */
#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR (((F_CPU / (16UL * BAUD))) - 1)

#include <avr/io.h>

void usart_init(void);
void usart_transmit(uint8_t data);
uint8_t usart_receive(void);