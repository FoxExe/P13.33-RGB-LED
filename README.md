# This is a library for control P13.33-3S-1R1G1B-24X12 panel.

## Panel info:
* Interface: HUB08 (RGB)
* Main control chip: LeadASIC PR4538
* Shift registers chips: JXI5020 (16 bit / like 2x 74HC245)

![rgb_led_panel-256-colors2](https://user-images.githubusercontent.com/3135063/31408538-5ef9a728-ae22-11e7-9c12-78d0051538ab.jpg)

## Lib features:
* Draw pixels (Base color or 256-colors)
* Draw text
* Draw primitives (Square, Rectangle, lines)
* Heavy optimized! Pins are hardcoded (Arduino-328 based chips, like Nano or Pro)
* 500-600 FPS for one panel, ~300 for two, but see flickers.

## Arduino nano pinouts:
	CLK = 12;
	LAT = 11;
	OE = 13;
	A = 7;
	B = 6;
	RA1 = 8;
	G1 = 9;
	B1 = 10;
	C, D, RB1 - not used.
	GND to ground (-).

## HUB08 layout:
	GND		A
	GND		B
	GND		C
	OE		D
	RA1		G1
	B1		RB1
	GND		LAT
	GND		CLK


# TODO:
- [x] Add more colors (RGB332 or RGB565 format for 256 and 65k colors)
- [x] Draw frames in interrupt mode (For max performance)
- [ ] Define connection pins in Init() function like before.
- [ ] Custom font sizes
- [ ] Optimisation...
