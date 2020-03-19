/*
 * GPIO pinout:
 * 
 * B   = 6
 * A   = 7
 * RA1 = 8
 * G1  = 9
 * B1  = 10
 * LAT = 11
 * CLK = 12
 * OE  = 13
 * 
 */

#include <Arduino.h>	// Need for PlatformIO

#include <HUB08_Panel.h>
//#include <Fonts/FreeMono9pt7b.h>

// One panel size (w/h): 24 x 12
// How about two?
HUB08_Panel screen(48, 12);

#define TIMER1_PERIOD 100 // Image update time
uint32_t timer1 = 0;

// Rainbow. Better to use calculation, but im lazy :)
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
	screen.begin();
}

uint8_t color_code = 0;
uint8_t color_offset = 0;

void loop() {
	screen.Update();	// Update one line at time (3 line per frame)

	if (millis() - timer1 >= TIMER1_PERIOD)
	{
		//screen.fillScreen(0);
		color_code = color_offset;

		for (uint8_t size_x = 0; size_x < screen.width(); size_x++)
		{
			if (color_code == sizeof(color_array) - 1)
				color_code = 0;
			else
				color_code++;

			screen.drawLine(size_x, 0, size_x, screen.height(), screen.Color_From_332(color_array[color_code]));
			screen.Update();	// Because not fast enaught
		}

		if (color_offset == sizeof(color_array) - 1)
			color_offset = 0;
		else
			color_offset++;

		// millis() counter overflow protection
		do
		{
			timer1 += TIMER1_PERIOD;
			if (timer1 < TIMER1_PERIOD)
				break;
		} while (timer1 < millis() - TIMER1_PERIOD);
	}
}