#ifndef TX_H
#define TX_H

void _onPeriod();
#define PWM_ON_PERIOD _onPeriod();
#include "pwm_output.h"

/*
PWM based transmitter.
Protocol:
 - Send sync pulses (# defined by TX_SYNC_PULSES, min 2)
 - Send start pulse (double PWM period)
 - Send data bits (low/high duty -> 0/1, diff defined by TX_DUTY_RANGE)
 - Send end pulse (double PWM period)

Usage:
 - Call send(uint8_t* data, uint8_t length, uint8_t blocking) to send data
 - #define TX_RATE (default 500)
 - #define TX_DUTY_RANGE (default 100)
 - #define TX_DUTY_BIAS (default 0) to compensate for high frequency loss
 - #define TX_SYNC_PULSES (default 20)
 - !! Disabling interrupts prevents transmission from working properly !!
*/

#ifndef TX_RATE
#define TX_RATE 500
#endif

#ifndef TX_DUTY_RANGE
#define TX_DUTY_RANGE 100
#endif

#ifndef TX_DUTY_BIAS
#define TX_DUTY_BIAS 0
#endif

#ifndef TX_SYNC_PULSES
#define TX_SYNC_PULSES 20
#endif

#define TX_DUTY_0 (127 + TX_DUTY_BIAS - TX_DUTY_RANGE/2)

#define TX_IDLE 0
#define TX_SYNC 1
#define TX_TRANSFER 2
#define TX_END 3

uint8_t* _tx_buffer;
uint8_t _tx_buffer_length = 0;
volatile uint8_t _tx_state = TX_IDLE;
uint8_t _tx_counter = 0;
uint8_t _tx_bit = 0;

uint8_t txSend(uint8_t* buffer, uint8_t length, uint8_t blocking) {
    // Return busy if already sending
    if (_tx_state) return 0;

    // Store parameters
    _tx_buffer = buffer;
    _tx_buffer_length = length;

    // Begin sync
    _tx_state = TX_SYNC;
    _tx_counter = 1;
    setPWM(TX_RATE, 128);
    startPWM();

    // Block if specified and return success when done
    while (blocking && _tx_state) {}
    return 1;
}

void _onPeriod() {
    switch (_tx_state) {
    case TX_IDLE: break;

    case TX_SYNC:
        // Send 20 sync pulses
        _tx_counter++;
        if (_tx_counter >= TX_SYNC_PULSES) {
            // Signal transmission start and begin
            setPWM(TX_RATE/2, 128);
            _tx_state = TX_TRANSFER;
            _tx_counter = 0;
        }
        break;

    case TX_TRANSFER:
        // Send end signal when buffer is empty
        if (_tx_counter >= _tx_buffer_length) {
            setPWM(TX_RATE/2, 128);
            _tx_state = TX_END;
            _tx_counter = 0;
            break;
        }

        // Send bit
        uint8_t i = 1 & (_tx_buffer[_tx_counter] >> _tx_bit);
        setPWM(TX_RATE, TX_DUTY_0 + i*TX_DUTY_RANGE);
        _tx_bit++;
        if (_tx_bit == 8) {
            _tx_counter++;
            _tx_bit = 0;
        }
        break;

    case TX_END:
        // Send 2 end pulses
        _tx_counter++;
        if (_tx_counter == 3) {
            stopPWM();
            _tx_state = TX_IDLE;
            _tx_counter = 0;
        }
        break;
    }
}

#endif
