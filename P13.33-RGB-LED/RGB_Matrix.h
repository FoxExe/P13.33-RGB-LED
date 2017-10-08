#pragma once

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

//#define DEBUG
#define PANEL_SIZE_X	24
#define PANEL_SIZE_Y	12

/*
	RGB332 format:
	0xRRRGGGBB

	000
	001
	010
	011
	100
	101
	110
	111
*/

struct Font
{
	uint8_t char_width;
	uint8_t char_height;
	const unsigned char * font;
};

enum Color : uint8_t
{
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
	
	// Color names in RGB332 format (0xRRRGGGBB)


	RGB_Matrix(uint8_t width, uint8_t height);
	~RGB_Matrix();
	
	uint8_t Width();
	uint8_t Height();

	//void init(uint8_t clk, uint8_t lat, uint8_t oe, uint8_t line_a, uint8_t line_b, uint8_t pin_r, uint8_t pin_g, uint8_t pin_b);
	void init();
	void drawFrame();

	void setFont(Font font);
	void setBrightness(uint8_t brightness);

	bool setCursor(unsigned int x, unsigned int y);
	uint8_t ColorFromRGB(uint8_t r, uint8_t g, uint8_t b);
	void drawPixel(unsigned int x, unsigned int y, uint8_t color);
	void drawChar(unsigned int x, unsigned int y, char c, uint8_t color);
	void drawString(unsigned int x, unsigned int y, char *string, uint8_t color);
	void drawString(unsigned int x, unsigned int y, const char *string, uint8_t color);
	void drawImage(unsigned int x, unsigned int y, unsigned int w, unsigned int h, char * bitmap, uint8_t color);

	void drawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, uint8_t color);
	void drawRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, uint8_t color);
	void drawFillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, uint8_t color);
	void drawCircle(unsigned int x, unsigned int y, unsigned int r, uint8_t color);
	void drawFillCircle(unsigned int x, unsigned int y, unsigned int r, uint8_t color);
#ifdef DEBUG
	void dumpColor(uint8_t color);
	void dumpBuffer();
#endif // DEBUG
private:
	uint8_t _clk;
	uint8_t _lat;
	uint8_t _oe;
	uint8_t _line_a;
	uint8_t _line_b;
	uint8_t _pin_r;
	uint8_t _pin_g;
	uint8_t _pin_b;
	uint8_t _brightness = 25;	// by default

	uint8_t _cursor_x;
	uint8_t _cursor_y;
	uint8_t _drawSizeX;
	uint8_t _drawSizeY;

	// Led light pattern. But need 8 states, so one is removed.
	uint8_t _lightPattern[8] = {
		B00000000,	// 0
		B00000001,	// 1
		B00010001,	// 2
		B01001010,	// 3
		B01010101,	// 4
		B10110101,	// 5
		B11101110,	// 6
		//B11111110,	// 7
		B11111111	// 8
	};

	Font _font;
	void _drawChar(char c, uint8_t color);

	uint8_t *_frame_buffer;
};

