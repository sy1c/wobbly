/* 
 * File:   twi.h
 * Author: matts
 *
 * Created on August 9, 2021, 10:04 PM
 */
#include <avr/io.h>

void twi_init(void);
void twi_start(void);
void twi_stop(void);
void twi_write(uint8_t data);
uint8_t twi_read_ack(void);
uint8_t twi_read_nack(void);
uint8_t twi_status(void);