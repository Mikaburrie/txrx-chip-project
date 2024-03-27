
#include "txrx_settings.h"
#include "../tx.h"

#define LEN 255
uint8_t buffer[LEN];

// Transmit on pin 5
int main() {

    DDRB |= (1 << DDB5);
    PORTB |= (1 << PORTB5);

    for (uint8_t i = 0; i < LEN; i++) {
        buffer[i] = i;
    }

    txSend(buffer, LEN, 1);
    
    PORTB &= ~(1 << PORTB5);

    while (1) {}
}
