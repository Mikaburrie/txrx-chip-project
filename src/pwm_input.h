#ifndef PWM_INPUT_H
#define PWM_INPUT_H

#include "micros.h"

/*
PWM input using timer and interrupt.
 - uses pin interrupt vector (defult d2)
 - callback PWM_ON_PERIOD when period is detected

Usage:
 - Call initPWM() to configure timer and interrupt
 - #define PWM_ON_PERIOD(period, duty) to run code each period
    - period -> uint32_t (microseconds)
    - duty   -> uint8_t (0 is ~0%, 255 is ~100%)
 - !! Disabling interrupts prevent PWM from working properly !!
*/

uint32_t _pwm_last = 0;
uint32_t _pwm_edge = 0;

ISR(INT0_vect) {
    uint8_t val = PIND & (1 << PIND2);
    uint32_t now = micros();

    if (val) {
        uint32_t period = now - _pwm_last;
        uint8_t duty = (_pwm_edge - _pwm_last)*256/period;
        _pwm_last = now;
        #ifdef PWM_ON_PERIOD
        PWM_ON_PERIOD(period, duty)
        #endif
    } else {
        _pwm_edge = now;
    }
}

void initPWM() {
    initMicros();

    // enable int0 (pin2)
    EICRA |= (1 << ISC00);
    EIMSK |= (1 << INT0);
}

#endif
