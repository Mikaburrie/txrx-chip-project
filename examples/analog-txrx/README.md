
# Analog Transmitter/Receiver Example

An example using the analog transmitter/receiver.

tx.c and rx.c implement the analog receiver. txrx_settings.h defines common settings for the pair.

The shell scripts tx.sh and rx.sh will compile and flash an ATMEGA328P. The scripts take one argument which is the device to flash (e.g. ./tx.sh /dev/ttyACM0).

The clip below shows a demo of the example.

![analog transmitter/receiver example demo](../../img/analog_txrx.gif)

The transmitter is at the top. The transmission indicator is on when transmitting.

The receiver is on the bottom. The reception indicator is on when a signal is detected.
