#include "usart.h"

void usart_init(void) {
    //set baud rate
    UBRR0H = (UBRR >> 8);;
    UBRR0L = UBRR;
    
    //enable transmitter and receiver
    UCSR0B |= (1 << RXCIE) | (1 << RXEN) | (1 << TXEN);
    
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
