#!/bin/sh

avr-gcc -Wall -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o tx.o tx.c
avr-gcc -mmcu=atmega328p tx.o -o tx
avr-objcopy -O ihex -R .eeprom tx tx.hex
avrdude -F -V -c arduino -p ATMEGA328P -P $1 -b 115200 -U flash:w:tx.hex
rm tx.o tx tx.hex
