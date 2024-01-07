# Attiny85 Door Sign

This is a simple project to create a door sign with an Attiny85 and a few LEDs. 
The goal is to power the sign with one CR2032 battery and therefore use as little power as possible.
To achieve this, the Attiny85 is put to sleep and only woken up by an interrupt.
I build a sign for the camper van of my aunt and uncle, but it can be used for any door, with any design.

## Idea
- Sign for any door (e.g. for a camper van)
- With LEDs for fun little animation
- With button to activate animation

## Material
- Attiny85
- 2x 3mm LED white (headlights)
- 1x 3mm LED orange (blinker)
- 2x 1 Ohm resistor
- CR2032 battery
- capacitive touch sensor

## Setup

### Housing
- 4x3.5mm ply wood plates on top of each other
- *front plate*
 - engraved picture 
 - cutouts for LEDs
 - circuit mounted on back side
 - capacitive touch sensor should be under the door of the camper van
- *1. middle plates*
 - cutout for nuts to mount the plates together
 - cutout for battery and circuit
- *2. middle plate*
 - cutout for screwholes above of the nut cutouts
 - cutout for battery and circuit
- *back plate*
 - cutout for service hatch to change battery
 - service hatch is secured with a screws

PICTURE OF HOUSING

### Circuit
- capacitive touch sensor for interrupt pin
- LEDs for headlights: front brighter than back -> different resistors
- resistors: 100 Ohm for back, 220 Ohm for front (try out)
- LEDs connected in parallel (check if current from Attiny is enough)
- LED for blinker connected to PWM pin
- 3V CR2032 battery as power source
- Attiny85 as controller
 - pin 0: interrupt pin for capacitive touch sensor
 - pin 1: PWM pin for headlights
 - pin 2: digital pin for blinker

PICTURE OF CIRCUIT

### Program
- touching the capacitive touch sensor wakes up Attiny85
- Attiny runs program
- *Animation*
 - headlights turn on
 - blinker blinks
 - animation runs a few times
- Attiny goes back to sleep

## Notes

### Power consumption
The Attiny85 consumes ultra low power in sleep mode while the Capacitive touch sensor consumes around 80 uA.  
Therefore the Touchsensor is the biggest consumer of power, but the sign should still run for half a year with one CR2032 battery if the animation is not used to often. 

