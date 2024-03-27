
#include "txrx_settings.h"
#include "../rx.h"

// Receive on pin 2
int main() {
    rxInit();

    DDRB |= (1 << DDB5);

    uint8_t* buffer;
    uint8_t length;

    while (1) {
        if (rxRecv(&buffer, &length) == RX_COMPLETE) {
            if (length) PORTB |= (1 << PORTB5);
            for (uint8_t i = 0; i != length; i++) {
                if (buffer[i] != i) PORTB &= ~(1 << PORTB5);
            }
        }
    }
}
