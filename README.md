# Basic ATMEGA328P Radio Transmission Library

This library contains code for using low cost transmitters and receivers with the ATMEGA328P. Two transmitters/receivers pairs are provided -- one digital and one analog.

---

## Digital Transmitter/Receiver

The digital transmitter/receiver can be used to transfer up to 400 bits per second.

### Transmitter

The transmitter definitions are located at src/tx_digital.h:

`txSend(uint8_t* buffer, uint8_t length, uint8_t blocking)`

- Transmits data from buffer[0] to buffer[length - 1] (or empty message if length = 0)
- Blocks if non-zero value is passed to blocking

### Receiver

The receiver definitions are located at src/rx_digital.h:

`rxInit(uint8_t adcPin)`

- Starts the receiver on the specified adc pin. (portc)

`rxRecv(uint8_t** buffer, uint8_t* length)`

- Checks if the receiver has any data. If yes, buffer is pointed to data[0] and length is set to the payload length
- Returns receiver state (RX_NOISE, RX_SYNC, RX_TRANSFER, RX_COMPLETE, RX_FAILED)
- State can also be retrieved using RX_STATE (to avoid call to rxRecv)

### Demo

An example using the digital transmitter/receiver is located in src/examples/digital-txrx. The clip below shows a demo the example.

![digital transmitter/receiver example demo](img/digital_txrx.gif)

The transmitter is at the top. The transmission indicator is on when transmitting.

The receiver is on the bottom. The reception indicator is turned on after the correct message is received.

---

## Analog Transmitter/Receiver

The analog transmitter/receiver can be used to continuously send two 8 bit values.

### Transmitter

The transmitter definitions are located at src/tx_analog.h:

`txStart()`

- Starts the transmitter

`txSend(uint8_t a, uint8_t b)`

- Transmits a and b

`txStop()`

- Stops the transmitter

### Receiver

The receiver definitions are located at src/rx_analog.h:

`rxInit(uint8_t adcPin)`

- Starts the receiver on the specified adc pin. (portc)

`rxRecv(uint8_t* a, uint8_t* b)`

- Gets current values from receiver
- Returns receiver state (RX_NOISE, RX_SYNC)

### Demo

An example using the analog transmitter/receiver is located in src/examples/analog-txrx. The clip below shows a demo the example.

![analog transmitter/receiver example demo](img/analog_txrx.gif)

The transmitter is at the top. The transmission indicator is on when transmitting.

The receiver is on the bottom. The reception indicator is on when a signal is detected.
