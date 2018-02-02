/*
	Name:		Rainbow.ino
	Created:	2/2/2018 10:00:00 PM
	Author:		Allester Fox <fox.axon@gmail.com>

	Panel name: P13.33-3S-1R1G1B-24X12
	Panel base: 6x JXI5020 for leds and LeadASIC PR4538 as main controller
	Panel interface: HUB08
	Pinouts:
	GND		A
	GND		B
	GND		C
	OE		D
	RA1		G1
	B1		RB1
	GND		LAT
	GND		CLK

	8 color:
	~470 FPS with 1 panel
	~248 FPS with 2 panels

	256 color:
	~60 fps with 1 panel
	~30 fps with 2 panels

	TODO:
	 * Draw frame by timer (in interrupt).
	 * Option: When we have some work - swith update frame to interrupt mode, but dont send data, only A/B/OE swith
	 * Add back buffer?
	 * Add more colors (RGB565 format for 65535 colors). How to do that?
*/

#include "RGB_Matrix.h"
#include "font.h"

#define SPEED 5

RGB_Matrix panel(PANEL_SIZE_X * 2, PANEL_SIZE_Y);	// Panels size

uint8_t color_array[] = {
	B11100000,	// R=8, G=0, B=0
	B11100100,
	B11101000,
	B11101100,
	B11110000,
	B11110100,
	B11111000,
	B11111100,	// R=8, G=8, B=0
	B11011100,
	B10111100,
	B10011100,
	B01111100,
	B01011100,
	B00111100,
	B00011100,	// R=0, G=8, B=0
	B00011100,
	B00011101,
	B00011101,
	B00011110,
	B00011110,
	B00011111,
	B00011111,	// R=0, G=8, B=8
	B00011011,
	B00010111,
	B00010011,
	B00001111,
	B00001011,
	B00000111,
	B00000011,	// R=0, G=0, B=8
	B00100011,
	B01000011,
	B01100011,
	B10000011,
	B10100011,
	B11000011,
	B11100011,	// R=8, G=0, B=8
	B11100011,
	B11100011,
	B11100011,
	B11100010,
	B11100010,
	B11100001,
	B11100001,
};

void setup() {
	panel.init();
	panel.setBrightness(50);
	panel.setFont(font5x8);
}

uint8_t color_offset = 0;
uint8_t color_code = 0;

void loop() {
	color_code = color_offset;

	for (uint8_t size_x = 0; size_x < panel.Width(); size_x++)
	{
		if (color_code == sizeof(color_array) - 1)
			color_code = 0;
		else
			color_code++;
		panel.drawLine(size_x, 0, size_x, panel.Height(), color_array[color_code]);
	}

	if (color_offset == sizeof(color_array) - 1)
		color_offset = 0;
	else
		color_offset++;

	for (uint8_t delay = 0; delay < SPEED; delay++)
	{
		panel.drawFrame();
	}
}