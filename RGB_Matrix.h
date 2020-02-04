#pragma once

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define PIN_OE		13
#define PIN_CLK		12
#define PIN_LATCH	11
#define PIN_LINE_A	7
#define PIN_LINE_B	6
#define PIN_RED		8
#define PIN_GREEN	9
#define PIN_BLUE	10

#define PANEL_SIZE_X 24
#define PANEL_SIZE_Y 12
#define PANEL_SCAN_N 3

//#define ENABLE_HSV 1

struct Font
{
	uint8_t char_width;
	uint8_t char_height;
	uint8_t space_right;
	uint8_t space_bottom;
	const uint8_t *data;
};

enum Color : uint8_t
{
// RGB332 format: 0xRRRGGGBB
	Color_Black		= B00000000,	// 0x00 = B00000000
	Color_Blue		= B00000011,	// 0x01 = B00000011
	Color_Green		= B00011100,	// 0x02 = B00011100
	Color_Cyan		= B00011111,	// 0x03 = B00011111
	Color_Red		= B11100000,	// 0x04 = B11100000
	Color_Magenta	= B11100011,	// 0x05 = B11100011
	Color_Yellow	= B11111100,	// 0x06 = B11111100
	Color_White		= B11111111,	// 0x07 = B11111111
};

class RGB_Matrix
{
public:
	// Supported Color

	RGB_Matrix(uint8_t rows, uint8_t cols);
	~RGB_Matrix();

	uint8_t Width();
	uint8_t Height();

	uint8_t CharWidth();	// Font char size
	uint8_t CharHeight();

	//void init(uint8_t clk, uint8_t lat, uint8_t oe, uint8_t line_a, uint8_t line_b, uint8_t pin_r, uint8_t pin_g, uint8_t pin_b);
	void init();
	void drawNextFrameLine();
	void clear();
	void fillScreen(uint8_t color);

	void setFont(Font font);
	bool setCursor(uint8_t x, uint8_t y);
	uint8_t ColorFromRGB(uint8_t r, uint8_t g, uint8_t b);
	uint8_t ColorFromHSV(long hue, uint8_t sat, uint8_t val, boolean gflag);
	void drawPixel(uint8_t x, uint8_t y, uint8_t color);
	void drawChar(uint8_t x, uint8_t y, char c, uint8_t color);
	void drawString(uint8_t x, uint8_t y, int value, uint8_t color);
	void drawString(uint8_t x, uint8_t y, char *string, uint8_t color);
	void drawString(uint8_t x, uint8_t y, const char *string, uint8_t color);
	void drawString(uint8_t x, uint8_t y, const __FlashStringHelper *string, uint8_t color);

	void drawImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h, char * bitmap, uint8_t color);

	void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color);
	void drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
	void drawFillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
	void drawCircle(uint8_t x, uint8_t y, uint8_t r, uint8_t color);
	void drawFillCircle(uint8_t x, uint8_t y, uint8_t r, uint8_t color);

#ifdef _DEBUG
	void dumpColor(uint8_t color);
	void dumpBuffer();
#endif
private:
	uint8_t _cursor_x;
	uint8_t _cursor_y;
	uint8_t _cursor_x_start;
	uint8_t _drawSizeX;
	uint8_t _drawSizeY;

	// NOTE: Set this two vars to maximum values!
	uint8_t _frameBStep = 7;
	uint8_t _frameLine = PANEL_SCAN_N - 1;

	bool _busy = false;

	Font _font;
	void _drawChar(char c, uint8_t color);
	inline void _drawPixel(uint8_t x, uint8_t y, uint8_t color);

	uint8_t *_frame_buffer;

	uint8_t _lightPattern[8] = {
		B00000000,	// 0%
		B00000001,	// 12.5%
		B00010001,	// 25%
		B01001010,	// 37.5%
		B01010101,	// 50%
		B01011011,	// 62.5%
		B01110111,	// 75%
		B11111111	// 100%
	};
// Not a best idea...
/*
	uint8_t _lightPattern[8] = {
		B00000000,	// 0%
		B00000011,	// 25%
		B00000111,	// 37.5%
		B00001111,	// 50%
		B00011111,	// 62.5%
		B00111111,	// 75%
		B01111111,	// 87.5%
		B11111111,	// 100%
	};
*/
};
