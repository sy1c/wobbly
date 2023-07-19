#include "adc.h"

void adc_init(void) {
    ADCSRA = (1 << ADEN) | (1 << ADATE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    ADMUX = (1 << REFS0) | (1 << ADLAR);
    ADCSRA |= (1 << ADSC);
}
