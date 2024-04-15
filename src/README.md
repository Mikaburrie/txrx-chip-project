# Library Files

## tx_digital.h

Defines a digital transmitter using pwm_output.h.

`uint8_t txSend(uint8_t* buffer, uint8_t length, uint8_t blocking)`

- Transmits data from buffer[0] to buffer[length - 1] (or empty message if length = 0)
- Blocks if non-zero value is passed to blocking
- Returns 0 and does nothing if already transmitting, 1 if transmission occurs

`#define TX_RATE 400`

- Sets the transmission rate
- Default 400

`#define TX_DUTY_RANGE 100`

- Sets the range of the duty during data transmission
- Default 100

`#define TX_DUTY_BIAS 0`

- Adds a bias to the transmitted duty to account for loss at higher frequencies
- Default 0

`#define TX_SYNC_PULSES 20`

- Defines the number of synchronization pulses sent before sending data
- Default 20


## rx_digital.h

Defines a digital receiver using pwm_input.h.

`void rxInit(uint8_t adcPin)`

- Starts the receiver on the specified adc pin. (portc)

`uint8_t rxRecv(uint8_t** buffer, uint8_t* length)`

- Checks if the receiver's buffer has any stored data. If yes, buffer is pointed to data[0] and length is set to the payload length.
- Reception pauses when a message is waiting in the buffer
- Returns receiver state (RX_NOISE, RX_SYNC, RX_TRANSFER, RX_COMPLETE, RX_FAILED)
- State can also be retrieved using RX_STATE (to avoid call to rxRecv)

`#define RX_RATE 400`

- Sets the transmission rate
- Default 400

`#define RX_MAX_RATE_ERROR 50`

- Defines the maximum acceptable rate error
- Default 50

`#define RX_BUFFER_LENGTH 255`

- Defines the length of the receiver buffer
- Default 255

`#define RX_SYNC_PULSES 10`

- Defines the number of synchronization pulses needed to change to sync state
- Default 10

## tx_analog.h

Defines an analog transmitter using pwm_output.h.

`void txStart()`

- Starts the transmitter (default sends 128, 128)

`void txSend(uint8_t a, uint8_t b)`

- Change transmitted values to a and b

`void txStop()`

- Stops the transmitter

`#define TX_LOW_RATE 80`

- Defines the lowest rate of the transmission
- Default 80

`#define TX_HIGH_RATE 250`

- Defines the highest rate of the transmission
- Default 250

`#define TX_LOW_DUTY 100`

- Defines the lowest duty of the transmission
- Default 100

`#define TX_HIGH_DUTY 200`

- Defines the highest duty of the transmission
- Default 200


## rx_analog.h

Defines an analog receiver using pwm_input.h.

`void rxInit(uint8_t adcPin)`

- Starts the receiver on the specified adc pin. (portc)

`uint8_t rxRecv(uint8_t* a, uint8_t* b)`

- Gets current values from receiver
- Returns receiver state (RX_NOISE, RX_SYNC)

`#define RX_LOW_RATE 80`

- Defines the lowest rate of the transmission
- Default 80

`#define RX_HIGH_RATE 250`

- Defines the highest rate of the transmission
- Default 250

`#define RX_RATE_MARGIN 20`

- Defines the acceptable rate error margin
- Default 20

`#define RX_LOW_DUTY 100`

- Defines the lowest duty of the transmission
- Default 100

`#define RX_HIGH_DUTY 200`

- Defines the highest duty of the transmission
- Default 200

`#define RX_DUTY_MARGIN 25`

- Defines the acceptable duty error margin
- Default 25

`#define RX_SYNC_TIMEOUT 100000`

- Defines the receiver timeout in microseconds
- State switches to RX_NOISE if no pulses are received in the timeout period
- Default 100000

`#define RX_SYNC_THRESHOLD 8`

- Defines the threshold needed to be synchronized (0 is no sync, 8 is well synced)
- Default 8


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
- Provides precision control of output when combined with setPWM()


## pwm_input.h

Defines an interface for reading a PWM signal on any adc pin (portc) using micros.h.

`void startPWM(uint8_t adcPin)`

- Starts PWM input

`#define PWM_ON_PERIOD(period, duty) _code_;`

- Called by interrupt after each received pulse
- Replace \_code_ with custom code to execute
- period: uint32_t (microseconds)
- duty: uint8_t (0 is ~0%, 255 is ~100%)

## micros.h

Defines a microsecond timer using counter 0. Similar to Arduino's micros() function.

`void startMicros()`

- Starts counter for timekeeping

`uint32_t micros()`

- Returns microseconds passed since calling startMicros()
