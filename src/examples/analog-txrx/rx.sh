#!/bin/sh

avr-gcc -Wall -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o rx.o rx.c
avr-gcc -mmcu=atmega328p rx.o -o rx
avr-objcopy -O ihex -R .eeprom rx rx.hex
avrdude -F -V -c arduino -p ATMEGA328P -P $1 -b 115200 -U flash:w:rx.hex
rm rx.o rx rx.hex
