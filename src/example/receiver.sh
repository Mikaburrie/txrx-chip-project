#!/bin/sh

avr-gcc -Wall -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o receiver.o receiver.c
avr-gcc -mmcu=atmega328p receiver.o -o receiver
avr-objcopy -O ihex -R .eeprom receiver receiver.hex
avrdude -F -V -c arduino -p ATMEGA328P -P $1 -b 115200 -U flash:w:receiver.hex
rm receiver.o receiver receiver.hex
