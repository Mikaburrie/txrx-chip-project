#ifndef RX_DIGITAL_H
#define RX_DIGITAL_H

#include <avr/io.h>

void _rx_onPeriod(uint32_t period, uint8_t duty);
#define PWM_ON_PERIOD(p, d) _rx_onPeriod(p, d);
#include "pwm_input.h"

/*
PWM based digital receiver for the protocol described in tx.h

Usage:
 - Call rxInit(uint8_t adcPin) to begin receiving on adcPin
 - Call rxRecv(uint8_t** buffer, uint8_t* length) to get receiving state
    - Returns current state and sets buffer/length if data is available 
 - Use RX_STATE to get the state of the receiver (RX_NOISE, RX_SYNC, etc.)
 - !! Disabling interrupts prevents reception from working properly !!
*/

#ifndef RX_RATE
#define RX_RATE 400
#endif

#ifndef RX_MAX_RATE_ERROR
#define RX_MAX_RATE_ERROR 50
#endif

#ifndef RX_BUFFER_LENGTH
#define RX_BUFFER_LENGTH 255
#endif

#ifndef RX_SYNC_PULSES
#define RX_SYNC_PULSES 10
#endif

#define RX_LOW_RATE (RX_RATE - RX_MAX_RATE_ERROR)
#define RX_HIGH_RATE (RX_RATE + RX_MAX_RATE_ERROR)
#define RX_LOW_PERIOD (1000000/RX_HIGH_RATE)
#define RX_HIGH_PERIOD (1000000/RX_LOW_RATE)

#define RX_NOISE 0
#define RX_SYNC 1
#define RX_TRANSFER 2
#define RX_COMPLETE 3
#define RX_FAILED 4
#define RX_STATE _rx_state

uint8_t _rx_buffer[RX_BUFFER_LENGTH];
volatile uint8_t _rx_state = RX_NOISE;
uint8_t _rx_counter = 0;
uint8_t _rx_bit = 0;
uint16_t _rx_duty = 0;

inline
void rxInit(uint8_t adcPin) {
    // Start pwm input on adc pin 0
    startPWM(adcPin);
}

uint8_t rxRecv(uint8_t** buffer, uint8_t* length) {
    // Return state if in NOISE, SYNC, or TRANSFER
    if (_rx_state < RX_COMPLETE) return _rx_state;

    // Assign buffer/length
    if (_rx_state == RX_COMPLETE) {
        *buffer = _rx_buffer;
        *length = _rx_counter;
    }

    // Reset state and return
    _rx_counter = 0;
    uint8_t tempState = _rx_state;
    _rx_state = RX_NOISE;
    return tempState;
} 

void _rx_onPeriod(uint32_t period, uint8_t duty) {
    if (period < RX_LOW_PERIOD || RX_HIGH_PERIOD < period) {
        uint8_t doublePeriod = (RX_LOW_PERIOD < period/2) && (period/2 < RX_HIGH_PERIOD);
        uint8_t halfDuty = (duty > _rx_duty - 50 && duty < _rx_duty + 50);

        // State transitions for irregular periods
        if (doublePeriod && halfDuty && _rx_state == RX_SYNC) {
            _rx_state = RX_TRANSFER;
            _rx_counter = 0;
            _rx_bit = 0;
        } else if (doublePeriod && halfDuty && _rx_state == RX_TRANSFER) {
            _rx_state = RX_COMPLETE;
        } else if (_rx_state == RX_TRANSFER) {
            _rx_state = RX_FAILED;
        } else if (_rx_state < RX_COMPLETE) {
            _rx_state = RX_NOISE;
            _rx_counter = 0;
            _rx_duty = 0;
        }

    } else switch (_rx_state) {
    case RX_NOISE:
        // Count sync pulses
        _rx_counter++;
        _rx_duty += duty;
        if (_rx_counter == RX_SYNC_PULSES) {
            _rx_duty /= RX_SYNC_PULSES;
            _rx_state = RX_SYNC;
        }
        break;

    case RX_SYNC:
        break;

    case RX_TRANSFER:
        // Fail if no buffer space available
        if (_rx_counter >= RX_BUFFER_LENGTH) {
            _rx_state = RX_FAILED;
            break;
        }

        // Determine bit value and store
        if (_rx_bit == 0) _rx_buffer[_rx_counter] = 0;
        _rx_buffer[_rx_counter] |= (duty > _rx_duty)*(1 << _rx_bit);

        // Increment bit and counter
        _rx_bit++;
        if (_rx_bit == 8) {
            _rx_bit = 0;
            _rx_counter++;
        }
        break;

    case RX_COMPLETE:
    case RX_FAILED:
        break;
    }
}

#endif
