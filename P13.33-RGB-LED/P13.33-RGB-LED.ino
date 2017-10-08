/*
	Name:		HUB08_12x24_RGB.ino
	Created:	9/29/2017 8:19:44 PM
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

	~470 FPS with 1 module
	~248 FPS with 2 modules

	TODO:
	 * Draw frame by timer (in interrupt).
	 * Option: When we have some work - swith update frame to interrupt mode, but dont send data, only A/B/OE swith
	 * Add back buffer?
	 * Add more colors (RGB565 format for 65535 colors). How to do that?
*/

//#define DEBUG
#define DEBUG_REPORT 1000
#define TIMER_DELAY  1000


#include "RGB_Matrix.h"
#include "font.h"

#include <RTClib.h>
RTC_Millis rtc;

#define PIN_OE		13
#define PIN_CLK		12
#define PIN_LATCH	11
#define PIN_LINE_A	7
#define PIN_LINE_B	6
#define PIN_RED		8
#define PIN_GREEN	9
#define PIN_BLUE	10

RGB_Matrix panel(PANEL_SIZE_X * 2, PANEL_SIZE_Y);	// Panels size

#ifdef DEBUG
unsigned long fps_delay = DEBUG_REPORT;
unsigned long fps_last = 0;
unsigned long fps_start, fps_stop;
unsigned int fps_count = 0;
#endif // DEBUG

unsigned long timer_delay = TIMER_DELAY;

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
#ifdef DEBUG
	Serial.begin(115200);
#endif // DEBUG
	rtc.begin(DateTime(F(__DATE__), F(__TIME__)));

	//panel.init(PIN_CLK, PIN_LATCH, PIN_OE, PIN_LINE_A, PIN_LINE_B, PIN_RED, PIN_GREEN, PIN_BLUE);
	panel.init();
	panel.setBrightness(50);	// 25 if not set (Default)
	panel.setFont(font5x8);


	/*
	panel.drawFillRect(0, 0, 1, 8, B00000111);
	panel.drawFillRect(1, 0, 1, 8, B00001011);
	panel.drawFillRect(2, 0, 1, 8, B00001111);
	panel.drawFillRect(3, 0, 1, 8, B00010011);
	panel.drawFillRect(4, 0, 1, 8, B00010111);
	panel.drawFillRect(5, 0, 1, 8, B00011011);
	panel.drawFillRect(6, 0, 1, 8, B00011111);
	panel.drawFillRect(7, 0, 1, 8, B00011110);
	panel.drawFillRect(8, 0, 1, 8, B00011101);
	panel.drawFillRect(9, 0, 1, 8, B00011100);
	panel.drawFillRect(10, 0, 1, 8, B00111100);
	panel.drawFillRect(11, 0, 1, 8, B01011100);
	panel.drawFillRect(12, 0, 1, 8, B01111100);
	panel.drawFillRect(13, 0, 1, 8, B11111100);
	panel.drawFillRect(14, 0, 1, 8, B10111100);
	panel.drawFillRect(15, 0, 1, 8, B11011100);
	panel.drawFillRect(16, 0, 1, 8, B11111100);
	panel.drawFillRect(17, 0, 1, 8, B11111000);
	panel.drawFillRect(18, 0, 1, 8, B11110100);
	panel.drawFillRect(19, 0, 1, 8, B11110000);
	panel.drawFillRect(20, 0, 1, 8, B11101000);
	panel.drawFillRect(21, 0, 1, 8, B11100100);
	panel.drawFillRect(22, 0, 1, 8, B11100000);
	panel.drawFillRect(23, 0, 1, 8, B11100001);
	panel.drawFillRect(24, 0, 1, 8, B11100010);
	panel.drawFillRect(25, 0, 1, 8, B11000011);
	panel.drawFillRect(26, 0, 1, 8, B10100011);
	panel.drawFillRect(27, 0, 1, 8, B10000011);
	panel.drawFillRect(28, 0, 1, 8, B01100011);
	panel.drawFillRect(29, 0, 1, 8, B01000011);
	panel.drawFillRect(30, 0, 1, 8, B00100011);
	panel.drawFillRect(31, 0, 1, 8, B00000000);

	panel.drawFillRect(0, 8, 1, 4, B00000000);
	panel.drawFillRect(1, 8, 1, 4, B00100000);
	panel.drawFillRect(2, 8, 1, 4, B01000000);
	panel.drawFillRect(3, 8, 1, 4, B01100000);
	panel.drawFillRect(4, 8, 1, 4, B10000000);
	panel.drawFillRect(5, 8, 1, 4, B10100000);
	panel.drawFillRect(6, 8, 1, 4, B11000000);
	panel.drawFillRect(7, 8, 1, 4, B11100000);

	panel.drawFillRect(8, 8, 1, 4, B00000000);
	panel.drawFillRect(9, 8, 1, 4, B00000100);
	panel.drawFillRect(10, 8, 1, 4, B00001000);
	panel.drawFillRect(11, 8, 1, 4, B00001100);
	panel.drawFillRect(12, 8, 1, 4, B00010000);
	panel.drawFillRect(13, 8, 1, 4, B00010100);
	panel.drawFillRect(14, 8, 1, 4, B00011000);
	panel.drawFillRect(15, 8, 1, 4, B00011100);

	panel.drawFillRect(16, 8, 1, 4, B00000000);
	panel.drawFillRect(17, 8, 1, 4, B00000001);
	panel.drawFillRect(18, 8, 1, 4, B00000001);
	panel.drawFillRect(19, 8, 1, 4, B00000010);
	panel.drawFillRect(20, 8, 1, 4, B00000010);
	panel.drawFillRect(21, 8, 1, 4, B00000011);
	panel.drawFillRect(22, 8, 1, 4, B00000011);
	panel.drawFillRect(23, 8, 1, 4, B00000011);
	*/

	/*
	uint8_t r = 0, g = 0, b = 0;
	for (uint8_t x = 0; x < panel.Width(); x++) {
		for (uint8_t y = 0; y < 8; y++) {
			panel.drawPixel(x, y, (r << 5) | (g << 2) | (b >> 1));
			r++;
			if (r == 8) {
				r = 0;
				g++;
				if (g == 8) {
					g = 0;
					b++;
				}
			}
		}
	}
	*/
}

char buffer[8] = { 0, };

void loop() {
	
	
#ifdef DEBUG
	fps_start = millis();
#endif // DEBUG
	for (uint8_t color_code = 0; color_code < sizeof(color_array); color_code++)
	{
		panel.drawFillRect(0, 0, panel.Width(), panel.Height(), color_array[color_code]);

		for (uint8_t delay = 0; delay < 5; delay++)
		{
			if (millis() > timer_delay) {
				//char buffer[8];
				//panel.drawString(12, 2, itoa(millis() / 1000, buffer, 10), panel.green);

				DateTime now = rtc.now();
				//char buffer[8];
				sprintf(buffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
				
		
				timer_delay = millis() + TIMER_DELAY - (millis() % TIMER_DELAY);
			}

			panel.drawString(0, 2, buffer, Color_Green);
			panel.drawFrame();
		}
	}

#ifdef DEBUG
	fps_stop = millis();
	fps_count++;

	if (millis() > fps_delay) {
		Serial.print(fps_count);
		Serial.print(F(" FPS, "));
		Serial.print(((fps_stop - fps_start) + fps_last) / 2);
		Serial.print(F(" ms. Uptime: "));
		Serial.print(millis() / 1000);
		Serial.print(F(" sec\n"));

		//panel.dumpColor(Color_Blue);	// DEBUG
		//panel.dumpBuffer();
		//panel.drawFrame();

		fps_count = 0;
		fps_delay = millis() + DEBUG_REPORT - (millis() % DEBUG_REPORT);	// Better delay. ~1 second.
	}
#endif // DEBUG
}