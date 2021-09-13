#include "timer.h"

void timer0_init(void) {
    TCCR0B |= (1 << CS02) | (1 << CS00);
    TIMSK0 |= (1<<TOIE0);
}