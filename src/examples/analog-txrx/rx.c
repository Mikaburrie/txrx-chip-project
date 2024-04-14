
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>

#include "txrx_settings.h"
#include "../../rx_analog.h"

int main() {
    // Receive on analog pin 0
    rxInit(0);

    // Enable built in led
    DDRB |= (1 << DDB5);

    // Variables for storing received values
    uint8_t val1 = 128;
    uint8_t val2 = 128;

    // Turn on/off built in led if synchronized or not
    while (1) {
        if (rxRecv(&val1, &val2) == RX_SYNC)
            PORTB |= (1 << PORTB5);
        else
            PORTB &= ~(1 << PORTB5);
    }
}
