#!/bin/sh

avr-gcc -Wall -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o transmitter.o transmitter.c
avr-gcc -mmcu=atmega328p transmitter.o -o transmitter
avr-objcopy -O ihex -R .eeprom transmitter transmitter.hex
avrdude -F -V -c arduino -p ATMEGA328P -P $1 -b 115200 -U flash:w:transmitter.hex
rm transmitter.o transmitter transmitter.hex
