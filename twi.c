#include "twi.h"

void twi_init(void) {
    //set SCL to 400kHz
    TWBR0 = 0x0C;
    TWSR0 = 0;
    //enable TWI
    TWCR0 = (1<<TWEN);
}

void twi_start(void) {
    TWCR0 = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while (!(TWCR0 & (1<<TWINT)));
}

void twi_stop(void) {
    TWCR0 = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void twi_write(uint8_t data) {
    TWDR0 = data;
    TWCR0 = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR0 & (1<<TWINT)));
}

uint8_t twi_read_ack(void) {
    TWCR0 = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while (!(TWCR0 & (1<<TWINT)));
    return TWDR0;
}

uint8_t twi_read_nack(void) {
    TWCR0 = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR0 & (1<<TWINT)));
    return TWDR0;
}

uint8_t twi_status(void) {
    uint8_t status;
    //mask status
    status = TWSR0 & 0xF8;
    return status;
}
