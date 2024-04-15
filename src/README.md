# Library Files

## tx_digital.h

Defines a digital transmitter using pwm_output.h.

`uint8_t txSend(uint8_t* buffer, uint8_t length, uint8_t blocking)`

- Transmits data from buffer[0] to buffer[length - 1] (or empty message if length = 0)
- Blocks if non-zero value is passed to blocking
- Returns 0 and does nothing if already transmitting, 1 if transmission occurs  


## rx_digital.h

Defines a digital receiver using pwm_input.h.

`void rxInit(uint8_t adcPin)`

- Starts the receiver on the specified adc pin. (portc)

`uint8_t rxRecv(uint8_t** buffer, uint8_t* length)`

- Checks if the receiver has any data. If yes, buffer is pointed to data[0] and length is set to the payload length
- Returns receiver state (RX_NOISE, RX_SYNC, RX_TRANSFER, RX_COMPLETE, RX_FAILED)
- State can also be retrieved using RX_STATE (to avoid call to rxRecv)


## tx_analog.h

Defines an analog transmitter using pwm_output.h.

`void txStart()`

- Starts the transmitter (default sends 128, 128)

`void txSend(uint8_t a, uint8_t b)`

- Change transmitted values to a and b

`void txStop()`

- Stops the transmitter


## rx_analog.h

Defines an analog receiver using pwm_input.h.

`void rxInit(uint8_t adcPin)`

- Starts the receiver on the specified adc pin. (portc)

`uint8_t rxRecv(uint8_t* a, uint8_t* b)`

- Gets current values from receiver
- Returns receiver state (RX_NOISE, RX_SYNC)


## pwm_output.h

Defines an interface for adjustable PWM on pin 5 using counter 0.

`void setPWM(uint16_t rate, uint8_t duty)`

- Sets the PWM output signal rate and duty
- Duty is mapped 0 -> 0%, 255 -> 100%
- Rate cannot go below 61

`void startPWM()`

- Starts PWM output

`void stopPWM()`

- Stops PWM output

`#define PWM_ON_PERIOD _code_;`

- Called by interrupt after each pulse
- Replace \_code_ with code to execute
- Must be declared before header is included
- Provides precision control of output when combined with setPWM()


## pwm_input.h

Defines an interface for reading a PWM signal on any adc pin (portc) using micros.h.

`void startPWM(uint8_t adcPin)`

- Starts PWM input

`#define PWM_ON_PERIOD(period, duty) _code_;`

- Called by interrupt after each received pulse
- Replace \_code_ with custom code to execute
- Must be declared before header is included
- period: uint32_t (microseconds)
- duty: uint8_t (0 is ~0%, 255 is ~100%)

## micros.h

Defines a microsecond timer using counter 0. Similar to Arduino's micros() function.

`void startMicros()`

- Starts counter for timekeeping

`uint32_t micros()`

- Returns microseconds passed since calling startMicros()
