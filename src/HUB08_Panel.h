#pragma once

#include <Arduino.h>
#include "Adafruit_GFX.h"

#define PANEL_SIZE_X 24
#define PANEL_SIZE_Y 12
#define PANEL_SCAN_N 3

//#define DEBUG

//#define USE_INTERRUPT
//#define LINE_TIME 800	// Tiks left for primary job (Code inside loop() function)

//#define USE_INTERRUPT_ALT
//#define LINE_TIME_ALT 52


enum Color : uint16_t
{
	// 565 format: rrrrrggggggbbbbb
	Color_Black		= 0x00,
	Color_Blue		= 0x1F,
	Color_Green		= 0x7E0,
	Color_Cyan		= 0x7FF,
	Color_Red		= 0xF800,
	Color_Magenta	= 0xF819,
	Color_Yellow	= 0xFFE0,
	Color_White		= 0xFFFF,
};

class HUB08_Panel: public Adafruit_GFX {
	public:
		HUB08_Panel(uint16_t width, uint16_t height);
		~HUB08_Panel();

		void drawPixel(int16_t x, int16_t y, uint16_t color);
		void fillScreen(uint16_t color);
		void writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
		uint8_t *getBuffer(void) const { return buffer; }

		void begin();
		void Update();

		uint8_t Color_From_565(uint16_t c);

		uint16_t Color_From_RGB(uint8_t r, uint8_t g, uint8_t b);
		uint16_t Color_From_332(uint8_t c);

		int frames = 0;
#ifdef DEBUG
		void dumpBuffer();
#endif
	private:
		uint8_t *buffer;
		uint8_t _line_num = 0;
		uint8_t _frame_num = 0;
		uint8_t _line_map[3] = { B00000000, B10000000, B01000000 };	// LINE A/B pin selector: --, A-, -B
};