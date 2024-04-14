#ifndef MICROS_H
#define MICROS_H

#include <avr/io.h>
#include <avr/interrupt.h>

/*
Microsecond timer accurate to 1us using counter 0.
Counter 0 configuration:
 - fast PWM mode (TOP = 255)
 - prescaler = 8x
 - overflow interrupt enabled

Usage:
 - Call startMicros() to start the counter
 - Call micros() to get microseconds since starting
 - !! Disabling interrupts will stop the timer from counting properly !!
*/

uint32_t _micros = 0;

// Increment _micros when timer overflows
ISR(TIMER0_OVF_vect) { _micros += 128; }

void startMicros() {
    // set fast PWM Mode (TOP=255)
	TCCR0A |= (1 << WGM01) | (1 << WGM00);

    // enable overflow interrupt
    sei();
    TIMSK0 |= (1 << TOIE0);

    // start clock (8x prescale -> 128us per overflow)
    TCCR0B |= (1 << CS01);
}

inline
uint32_t micros() {
    return _micros + (TCNT0 >> 1);
}

#endif
