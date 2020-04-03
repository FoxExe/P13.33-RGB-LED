#pragma once

#include <Arduino.h>
#include "Adafruit_GFX.h"

#define PANEL_SIZE_X 24	// Single panel width
#define PANEL_SIZE_Y 12	// Single panel height
#define PANEL_SCAN_L 3  // These panels have 3 lines

//#define DEBUG
#define ENAMLE_HSV

// Use interrupt for set update flat (OUT) or for update frame in interrupt mode (INT)
// Set only one of them!
//#define USE_INTERRUPT_OUT
#define USE_INTERRUPT_INT

enum Color : uint8_t
{
	// 565 format: rrrrrggggggbbbbb
	Color_Black		= B00000000,
	Color_Blue		= B00000011,
	Color_Green		= B00011100,
	Color_Cyan		= B00011111,
	Color_Red		= B11100000,
	Color_Magenta	= B11100011,
	Color_Yellow	= B11111100,
	Color_White		= B11111111,
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

		uint32_t frames = 0;

		uint8_t  Color_From_565(uint16_t c);
		uint16_t Color_From_RGB(uint8_t r, uint8_t g, uint8_t b);
#if defined(ENAMLE_HSV)
		uint16_t Color_From_HSV(long hue, uint8_t sat, uint8_t val, boolean gflag);
#endif
#if defined(USE_INTERRUPT_OUT)
		bool _update = false;
#endif

#ifdef DEBUG
		void dumpBuffer();
#endif
	private:
		uint8_t *buffer;
		uint8_t _line_num = 0;
		uint8_t _frame_num = 0;
};