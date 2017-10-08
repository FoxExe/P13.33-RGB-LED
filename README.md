# This is a library for control P13.33-3S-1R1G1B-24X12 panel.

## Panel info:
* Interface: HUB08 (RGB)
* Main control chip: LeadASIC PR4538
* Shift registers chips: JXI5020 (16 bit / like 2x 74HC245)

## Lib features:
* Draw pixels
* Draw text
* Draw primitives (Square, Rectangle, lines)
* Supported 8 colors: Black, White, Red, Green, Blue, Cyan, Magenta, Yellow.
* Heavy optimized! Pins are hardcoded (Arduino NANO)
* Upto 470 fps with one panel. ~250 fps with two.

## Arduino nano pinouts:
`CLK = 12;
LAT = 11;
OE = 13;
A = 7;
B = 6;
RA1 = 8;
G1 = 9;
B1 = 10;
C, D, RB1 - not used.
GND to ground (-).`

## HUB08 layout:
`	GND		A
	GND		B
	GND		C
	OE		D
	RA1		G1
	B1		RB1
	GND		LAT
	GND		CLK`


# TODO:
[ ] Add more colors (RGB332 or RGB565 format for 256 and 65k colors)
[ ] Draw frames in interrupt mode (For max performance)
[ ] Define connection pins in Init() function like before.
[ ] Optimisation...