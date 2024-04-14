
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include "txrx_settings.h"
#include "../../rx_digital.h"

int main() {
    // Receive on analog pin 0
    rxInit(0);

    // Enable built in led
    DDRB |= (1 << DDB5);

    // Variables for message buffer
    uint8_t* buffer;
    uint8_t length;

    // Check message if received, turn on led if data transmitted with no errors 
    while (1) {
        // Check for message
        if (rxRecv(&buffer, &length) == RX_COMPLETE) {
            // Turn on led if length is non zero
            if (length) PORTB |= (1 << PORTB5);

            // Disable led if mismatch is detected
            for (uint8_t i = 0; i != length; i++) {
                if (buffer[i] != i) PORTB &= ~(1 << PORTB5);
            }
        }
    }
}
