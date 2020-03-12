# This is a library for control P13.33-3S-1R1G1B-24X12 panel.

## Panel info:
* Interface: HUB08 (RGB)
* Main control chip: LeadASIC PR4538
* Shift registers chips: JXI5020 (16 bit / like 2x 74HC245)

![rgb_led_panel-256-colors2](https://user-images.githubusercontent.com/3135063/31408538-5ef9a728-ae22-11e7-9c12-78d0051538ab.jpg)

## Features:
* Support 255 colors (RGB format: 332)
* Depends/Use Adafruit GFX library
* GPIO hardcoded for Arduino Pro Mini (Need for heavy optimisation)
* Flickers if use more than 1 panel :(

## Arduino nano pinouts:
	CLK	->	12
	LAT	->	11
	OE	->	13
	A	->	7
	B	->	6
	RA1	->	8
	G1	->	9
	B1	->	10
	GND	->	GND
	C, D, RB1 -> not connected

## HUB08 layout:
	GND		A
	GND		B
	GND		C
	OE		D
	RA1		G1
	B1		RB1
	GND		LAT
	GND		CLK

# Notes:
* Uncomment `USE_INTERRUPT` and `LINE_TIME` for use interrupts for draw frames (Timer delay)
* Uncomment `USE_INTERRUPT_ALT` and `LINE_TIME_ALT` for alternative interrupt configuration (Timer overflow)

# TODO:
- [x] 255 (or more) colors support.
- [x] Use interrupts to get rid of flickering.
- [ ] Allow to use different GPIO pins
- [ ] Not understand why, but inside loop() its runs faster, than in interrupt...
- [ ] Optimisation...
