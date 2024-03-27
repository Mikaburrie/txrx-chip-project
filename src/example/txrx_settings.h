// Controls rate of transmission/reception (bits/s)
#define RATE 500

// Controls sync pulses transmitted and how many need to be received
#define SYNC_PULSES 20

// Controls duty bias of the transmitter to compensate for duty loss at high rates
#define TX_DUTY_BIAS 10

// Controls how different the duty for 0 and 1 are.
// Low ranges will be hard to distinguish at the receiver.
// High ranges might not be detected by the hardware.
#define TX_DUTY_RANGE 100

// Controls maximum allowed deviation of the rate during reception
#define RX_MAX_RATE_ERROR 50

// Controls the maximum received message length.
// Transmitted messages larger than the buffer will trigger the RX_FAILED state.
#define RX_BUFFER_LENGTH 255

#define TX_RATE RATE
#define RX_RATE RATE
#define TX_SYNC_PULSES SYNC_PULSES
#define RX_SYNC_PULSES (SYNC_PULSES/2)
