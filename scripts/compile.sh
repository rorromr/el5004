#!/bin/bash

for EXAMPLE in $PWD/arduino/GoKart/examples/*/*.ino; do
	arduino --verify --board arduino:avr:mega:cpu=atmega2560 $EXAMPLE
done