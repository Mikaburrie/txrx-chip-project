
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include "txrx_settings.h"
#include "../../tx_digital.h"

// Create data buffer
#define LEN 255
uint8_t buffer[LEN];

int main() {
    // Prepare data
    for (uint8_t i = 0; i < LEN; i++) {
        buffer[i] = i;
    }

    // Turn on built in led
    DDRB |= (1 << DDB5);
    PORTB |= (1 << PORTB5);

    // Send data (pin 5)
    txSend(buffer, LEN, 1);
    
    // Turn off built in led when finished
    PORTB &= ~(1 << PORTB5);

    while (1) {}
}
