#include "RGB_Matrix.h"

#define PANEL_SCAN_N	3
#define BitSetFast(b, num, val) { b ^= (-val ^ b) & (1 << num); }

#define swap(a, b)     \
	{                  \
		uint8_t t = a; \
		a = b;         \
		b = t;         \
	}

RGB_Matrix::RGB_Matrix(uint8_t width, uint8_t height)
{
	_drawSizeX = width;
	_drawSizeY = height;
	_frame_buffer = new uint8_t[width * height]{ 0, };	// Set all to zero
}

RGB_Matrix::~RGB_Matrix()
{
}

uint8_t RGB_Matrix::Width()
{
	return _drawSizeX;
}

uint8_t RGB_Matrix::Height()
{
	return _drawSizeY;
}

//void RGB_Matrix::init(uint8_t clk, uint8_t lat, uint8_t oe, uint8_t line_a, uint8_t line_b, uint8_t pin_r, uint8_t pin_g, uint8_t pin_b)
void RGB_Matrix::init()
{
	/*
	
	_clk = clk;
	_lat = lat;
	_oe = oe;
	_line_a = line_a;
	_line_b = line_b;
	_pin_r = pin_r;
	_pin_g = pin_g;
	_pin_b = pin_b;
	*/

	_clk = 12;
	_lat = 11;
	_oe = 13;
	_line_a = 7;
	_line_b = 6;
	_pin_r = 8;
	_pin_g = 9;
	_pin_b = 10;


	// Configure ports
	// TODO: Use registers for speed!
	pinMode(_clk, OUTPUT);
	pinMode(_lat, OUTPUT);
	pinMode(_oe, OUTPUT);
	pinMode(_line_a, OUTPUT);
	pinMode(_line_b, OUTPUT);
	pinMode(_pin_r, OUTPUT);
	pinMode(_pin_g, OUTPUT);
	pinMode(_pin_b, OUTPUT);

	digitalWrite(_pin_r, LOW);
	digitalWrite(_pin_g, LOW);
	digitalWrite(_pin_b, LOW);

	digitalWrite(_oe, HIGH);
	digitalWrite(_lat, LOW);
	digitalWrite(_clk, LOW);

	// PORTB = Ports: -, -, 13, 12, 11, 10, 9, 8	(Digital)
	// PORTC = Ports: -, -, A5, A4, A3, A2, A1, A0	(Analog)
	// PORTD = Ports: 7, 6, 5, 4, 3, 2, 1, 0		(Digital)
	// DDRB -> Data Direction Register B (Set Input/Output mode)
	//DDRD  |= B11000000;		// Set 6 and 7 to output
	//PORTD &= ~B11000000;		// Set 6 and 7 to LOW
	//DDRB  = B00111111;		// Set 13...8 to output
	//PORTB = B00100000;		// Set OE to HIGH (Because its inverted)
}

void RGB_Matrix::drawFrame()
{
	for (uint8_t gradientStep = 0; gradientStep < 8; gradientStep++) {
		for (uint8_t scan = 0; scan < PANEL_SCAN_N; scan++)
		{
			// Row select
			BitSetFast(PORTD, 7, !!(scan & B00000001));
			BitSetFast(PORTD, 6, !!(scan & B00000010));
			//digitalWrite(_line_a, !!(scan & B00000001));
			//digitalWrite(_line_b, !!(scan & B00000010));

			for (uint8_t panels_row = 0; panels_row < _drawSizeY / PANEL_SIZE_Y; panels_row++)
			{
				for (uint8_t block = 0; block < _drawSizeX / 8; block++)
				{
					for (uint8_t row = 0; row < PANEL_SIZE_Y / PANEL_SCAN_N; row++)
					{
						//int pos = panels_h * _drawSizeX * PANEL_SIZE_Y + _drawSizeX * PANEL_SIZE_Y - column - row * _drawSizeX * PANEL_SCAN_N - (-scan + PANEL_SCAN_N - 1) * _drawSizeX;
						for (uint8_t pixelInBlock = 0; pixelInBlock < 8; pixelInBlock++)
						{
							int pos = (panels_row * _drawSizeX * PANEL_SIZE_Y) + (_drawSizeX * PANEL_SIZE_Y) - (_drawSizeX - block * 8) - row * _drawSizeX * PANEL_SCAN_N - (-scan + PANEL_SCAN_N - 1) * _drawSizeX + pixelInBlock;

							//digitalWrite(_pin_r, !!(_frame_buffer_r[pos] & pos2));
							//digitalWrite(_pin_g, !!(_frame_buffer_g[pos] & pos2));
							//digitalWrite(_pin_b, !!(_frame_buffer_b[pos] & pos2));

							uint8_t offset = B00000001 << gradientStep;

							// Heavy optimisation o_O
							PORTB = B00110000 |	// 6th bit - OE pin (13 / Inverted)
								!!(_lightPattern[(_frame_buffer[pos] & B11100000) >> 5] & offset) |
								!!(_lightPattern[(_frame_buffer[pos] & B00011100) >> 2] & offset) << 1 |
								!!(_lightPattern[(_frame_buffer[pos] & B00000011) << 1] & offset) << 2;

							//Serial.print(pos);
							//Serial.print(", ");

							/*
							PORTB = B00110000 |	// 6th bit - OE pin (13 / Inverted)
								!!((_frame_buffer[pos] & B11100000) >> 5) |
								!!((_frame_buffer[pos] & B00011100) >> 2) << 1 |
								!!((_frame_buffer[pos] & B00000011) << 1) << 2;
							*/

							//BitSetFast(PORTB, 0, !!(_lightPattern[(_frame_buffer[pos] & B11100000) >> 5] & offset));	// Red
							//BitSetFast(PORTB, 1, !!(_lightPattern[(_frame_buffer[pos] & B00011100) >> 2] & offset));	// Green
							//BitSetFast(PORTB, 2, !!(_lightPattern[(_frame_buffer[pos] & B00000011) << 1] & offset));	// Blue


							//BitSetFast(PORTB, 0, !!(_frame_buffer[pos] & pos2));	// 0xRRRGGGBB
							//BitSetFast(PORTB, 1, !!(_frame_buffer[pos] & pos2));
							//BitSetFast(PORTB, 2, !!(_frame_buffer[pos] & pos2));


							// Clock pin HIGH, LOW
							//PORTB |= B00010000;
							PORTB &= ~B00010000;
						}
					}
				}
				//Serial.println();
			}

			// update frame
			//digitalWrite(_lat, HIGH);
			//digitalWrite(_lat, LOW);

			// Latch pin: HIGH, then LOW
			PORTB |= B00001000;
			PORTB &= ~B00001000;

			//digitalWrite(_oe, LOW);
			//delayMicroseconds(_brightness);
			//digitalWrite(_oe, HIGH);

			PORTB &= ~B00100000;	// OE on (LOW)
			delayMicroseconds(_brightness);
			PORTB |= B00100000;		// OE off (HIGH)
		}
		//Serial.println();
	}
}

void RGB_Matrix::setFont(Font font)
{
	_font = font;
}

bool RGB_Matrix::setCursor(unsigned int x, unsigned int y)
{
	if ((x >= _drawSizeX) || (y >= _drawSizeY))
		return false;
	else {
		_cursor_x = x;
		_cursor_y = y;
		return true;
	}
}

// Set brightness. Less = Bright. 255 max.
void RGB_Matrix::setBrightness(uint8_t brightness)
{
	_brightness = brightness;
}

uint8_t RGB_Matrix::ColorFromRGB(uint8_t r, uint8_t g, uint8_t b) {
	return (r & B11100000) | (g & B11100000) >> 3 | (b & B11000000) >> 6;
}

// Set pixel
// TODO: Make this function inline for better performance?
void RGB_Matrix::drawPixel(unsigned int x, unsigned int y, uint8_t color)
{
	_frame_buffer[y * _drawSizeX + x] = color;
}

void RGB_Matrix::drawChar(unsigned int x, unsigned int y, char c, uint8_t color)
{
	//if ((y + _font.char_height) >= _drawSizeY - 1)	// Remove padding
	//	return;

	//if ((x + _font.char_width) >= _drawSizeX - 1)
	//	return;

	uint8_t i, bit;
	for (i = 0; i < _font.char_width; i++)
	{
		uint8_t d = pgm_read_ptr(_font.font + (c * _font.char_width) + i);
		uint8_t bit;
		for (bit = 0; bit < _font.char_height; bit++)
		{
			if (d & (B00000001 << bit))
			{
				drawPixel(x + i, y + bit, color);
			}
			else
			{
				drawPixel(x + i, y + bit, 0x00);	// Empty / Black
			}
		}
	}

	// Add right space
	for (bit = 0; bit < _font.char_height; bit++)
	{
		drawPixel(x + _font.char_width, y + bit, 0x00);	// Empty / Black
	}

	// TODO: Add bottom space?
}

void RGB_Matrix::drawString(unsigned int x, unsigned int y, const char *string, uint8_t color)
{
	if (!setCursor(x, y))
		return;

	while (1)
	{
		char c = (*string++);
		if (!c)
			return;
		_drawChar(c, color);
	}
}

void RGB_Matrix::drawString(unsigned int x, unsigned int y, const __FlashStringHelper * string, uint8_t color)
{
	if (!setCursor(x, y))
		return;

	PGM_P p = reinterpret_cast<PGM_P>(string);
	while (1) {
		unsigned char c = pgm_read_byte(p++);
		if (!c)
			return;
		_drawChar(c, color);
	}
}

void RGB_Matrix::drawString(unsigned int x, unsigned int y, char *string, uint8_t color)
{
	if (!setCursor(x, y))
		return;

	while (*string)
	{
		_drawChar(*string++, color);
	}
}

void RGB_Matrix::_drawChar(char c, uint8_t color)
{
	if (c == '\n' || c == '\r')
	{
		_cursor_x = 0;
		_cursor_y += _font.char_height;
		if (_cursor_y > _drawSizeY)
			_cursor_y = 0;
	}
	else
	{
		drawChar(_cursor_x, _cursor_y, c, color);
		_cursor_x += _font.char_width + 1;

		if (_cursor_x + _font.char_width > _drawSizeX)
		{
			_cursor_x = 0;
			_cursor_y += _font.char_height;
		}
		if (_cursor_y > _drawSizeY)
			_cursor_y = 0;
	}
}


void RGB_Matrix::drawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, uint8_t color)
{
	uint8_t steep = abs(y2 - y1) > abs(x2 - x1);
	if (steep)
	{
		swap(x1, y1);
		swap(x2, y2);
	}

	if (x1 > x2)
	{
		swap(x1, x2);
		swap(y1, y2);
	}

	uint8_t dx, dy;
	dx = x2 - x1;
	dy = abs(y2 - y1);

	int8_t err = dx / 2;
	int8_t ystep;

	if (y1 < y2)
	{
		ystep = 1;
	}
	else
	{
		ystep = -1;
	}

	for (; x1 <= x2; x1++)
	{
		if (steep)
		{
			drawPixel(y1, x1, color);
		}
		else
		{
			drawPixel(x1, y1, color);
		}
		err -= dy;
		if (err < 0)
		{
			y1 += ystep;
			err += dx;
		}
	}
}

void RGB_Matrix::drawRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, uint8_t color)
{
	uint8_t i;
	for (i = x; i < x + w; i++)
	{
		drawPixel(i, y, color);
		drawPixel(i, y + h - 1, color);
	}
	for (i = y; i < y + h; i++)
	{
		drawPixel(x, i, color);
		drawPixel(x + w - 1, i, color);
	}
}

void RGB_Matrix::drawFillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, uint8_t color)
{
	uint8_t row, col;
	for (row = y; row < y + h; row++)
	{
		for (col = x; col < x + w; col++)
		{
			drawPixel(col, row, color);
		}
	}
}

void RGB_Matrix::drawCircle(unsigned int x, unsigned int y, unsigned int r, uint8_t color)
{
	int8_t f = 1 - r;
	int8_t ddF_x = 1;
	int8_t ddF_y = -2 * r;
	int8_t tmp_x = 0;
	int8_t tmp_y = r;

	drawPixel(x, y + r, color);
	drawPixel(x, y - r, color);
	drawPixel(x + r, y, color);
	drawPixel(x - r, y, color);

	while (tmp_x < tmp_y)
	{
		if (f >= 0)
		{
			tmp_y--;
			ddF_y += 2;
			f += ddF_y;
		}
		tmp_x++;
		ddF_x += 2;
		f += ddF_x;

		drawPixel(x + tmp_x, y + tmp_y, color);
		drawPixel(x - tmp_x, y + tmp_y, color);
		drawPixel(x + tmp_x, y - tmp_y, color);
		drawPixel(x - tmp_x, y - tmp_y, color);

		drawPixel(x + tmp_y, y + tmp_x, color);
		drawPixel(x - tmp_y, y + tmp_x, color);
		drawPixel(x + tmp_y, y - tmp_x, color);
		drawPixel(x - tmp_y, y - tmp_x, color);
	}
}

void RGB_Matrix::drawFillCircle(unsigned int x, unsigned int y, unsigned int r, uint8_t color)
{
	int8_t f = 1 - r;
	int8_t ddF_x = 1;
	int8_t ddF_y = -2 * r;
	int8_t tmp_x = 0;
	int8_t tmp_y = r;
	uint8_t i;

	for (i = y - r; i <= y + r; i++)
	{
		drawPixel(x, i, color);
	}

	while (tmp_x < tmp_y)
	{
		if (f >= 0)
		{
			tmp_y--;
			ddF_y += 2;
			f += ddF_y;
		}
		tmp_x++;
		ddF_x += 2;
		f += ddF_x;

		for (i = y - tmp_y; i <= y + tmp_y; i++)
		{
			drawPixel(x + tmp_x, i, color);
			drawPixel(x - tmp_x, i, color);
		}
		for (i = y - tmp_x; i <= y + tmp_x; i++)
		{
			drawPixel(x + tmp_y, i, color);
			drawPixel(x - tmp_y, i, color);
		}
	}
}

#ifdef DEBUG
void RGB_Matrix::dumpColor(uint8_t color)
{
	Serial.println();

	for (uint8_t row = 0; row < _drawSizeY; row++)
	{
		for (uint8_t col = 0; col < _drawSizeX; col++)
		{
			Serial.print(!!(_frame_buffer[_drawSizeX * row + col] & color));
		}
		Serial.println();
	}

	Serial.println();
}

void RGB_Matrix::dumpBuffer()
{
	Serial.println();
	char buffer[3];

	for (uint8_t row = 0; row < _drawSizeY; row++)
	{
		for (uint8_t col = 0; col < _drawSizeX; col++)
		{
			sprintf(buffer, "%02d-", _frame_buffer[_drawSizeX * row + col]);
			Serial.print(buffer);
		}
		Serial.println();
	}

	Serial.println();
}

#endif // DEBUG
