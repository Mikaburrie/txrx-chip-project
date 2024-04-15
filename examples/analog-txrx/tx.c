
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "txrx_settings.h"
#include "../../src/tx_analog.h"

int main() {
    // Enable built in led
    DDRB |= (1 << DDB5);
    
    // Transmit for half of each second
    while (1) {
        // Transmit on pin 5
        txStart();

        // Turn led on and wait 0.5 seconds
        PORTB |= (1 << PORTB5);
       _delay_ms(500);

        // Stop transmitting
        txStop();

        // Turn led on and wait 0.5 seconds
        PORTB &= ~(1 << PORTB5);
        _delay_ms(500);
    }
}
