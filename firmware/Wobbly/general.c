#include <avr/io.h>

uint8_t is_high(uint8_t reg, uint8_t pin) {
    if (reg & (1 << pin)) {
        return 1;
    } else {
        return 0;
    }
}
