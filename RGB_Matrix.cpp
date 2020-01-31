#include "RGB_Matrix.h"

#define TIME_PRESCALER_1 _BV(CS10);
#define TIME_PRESCALER_8 _BV(CS11);
#define TIME_PRESCALER_64 _BV(CS11) | _BV(CS10);
#define TIME_PRESCALER_256 _BV(CS12);
#define TIME_PRESCALER_1024 _BV(CS12) | _BV(CS10);

#define FRAME_LINE_DELAY 10

#ifdef ENABLE_HSV
static const uint8_t PROGMEM gamma_table[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02,
	0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
	0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
	0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x04,
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05,
	0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
	0x05, 0x05, 0x05, 0x06, 0x06, 0x06, 0x06, 0x06,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07,
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x07, 0x07, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x09, 0x09, 0x09, 0x09,
	0x09, 0x09, 0x09, 0x09, 0x09, 0x0a, 0x0a, 0x0a,
	0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0b, 0x0b,
	0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0c, 0x0c,
	0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0d, 0x0d,
	0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0e, 0x0e, 0x0e,
	0x0e, 0x0e, 0x0e, 0x0e, 0x0f, 0x0f, 0x0f, 0x0f};
#endif

#define BitSetFast(port, num, val)          \
	{                                       \
		port ^= (-val ^ port) & (1 << num); \
	}

#define swap(a, b)     \
	{                  \
		uint8_t t = a; \
		a = b;         \
		b = t;         \
	}

RGB_Matrix::RGB_Matrix(uint8_t rows, uint8_t cols)
{
	_drawSizeX = cols * PANEL_SIZE_X;
	_drawSizeY = rows * PANEL_SIZE_Y;
	_frame_buffer = new uint8_t[_drawSizeX * _drawSizeY]{
		0,
	};
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

void RGB_Matrix::init()
{
	// Configure ports
	// TODO: Use registers for speed!
	pinMode(PIN_CLK, OUTPUT);
	pinMode(PIN_LATCH, OUTPUT);
	pinMode(PIN_OE, OUTPUT);
	pinMode(PIN_LINE_A, OUTPUT);
	pinMode(PIN_LINE_B, OUTPUT);
	pinMode(PIN_RED, OUTPUT);
	pinMode(PIN_GREEN, OUTPUT);
	pinMode(PIN_BLUE, OUTPUT);

	digitalWrite(PIN_OE, HIGH);
	digitalWrite(PIN_LATCH, LOW);
	digitalWrite(PIN_CLK, LOW);
	digitalWrite(PIN_RED, LOW);
	digitalWrite(PIN_GREEN, LOW);
	digitalWrite(PIN_BLUE, LOW);

	// PORTB = Ports: -, -, 13, 12, 11, 10, 9, 8	(Digital)
	// PORTC = Ports: -, -, A5, A4, A3, A2, A1, A0	(Analog)
	// PORTD = Ports: 7, 6, 5, 4, 3, 2, 1, 0		(Digital)
	// DDRB -> Data Direction Register B (Set Input/Output mode)
	//DDRD  |= B11000000;		// Set 6 and 7 to output
	//PORTD &= ~B11000000;		// Set 6 and 7 to LOW
	//DDRB  = B00111111;		// Set 13...8 to output
	//PORTB = B00100000;		// Set OE to HIGH (Because its inverted)

	// Configure timer1 for frame update
	cli();		// Disable interrupts
	TCCR1A = 0; // Reset registers
	TCCR1B = 0;
	/* Timer count calculation example:
	 * 16000000/1024/800 = 19,53125
	 * 16000000/256/600  = 104,1666  (600 MHz / 3 lines = 200 FPS)
	 * 16000000/256/900  = 69,44444  (900 MHz / 3 lines = 300 FPS)
	 * 16000000/256/1200 = 52,08333  (1200 MHz / 3 lines = 400 FPS)
	 * Warning: One panel can achive ~500FPS, but two - maxumum is 300FPS!
	 */
	//	OCR1A = 120 / ; // 90=150 FPS
	OCR1A = 42 * ((_drawSizeX / PANEL_SIZE_X) * (_drawSizeY / PANEL_SIZE_Y)); // 78-80 good for 2 panels.
	TCCR1B |= (1 << WGM12);													  // Turn ON CTC
	TCCR1B |= TIME_PRESCALER_256;											  // Delimeter: 256
	TIMSK1 |= (1 << OCIE1A);												  // Timer mode: Compare
	sei();																	  // Enable interrupts

	/*
	long L_Time = FRAME_LINE_DELAY * 125;
	L_Time = L_Time / 2;

	cli();
	TCCR1A = 0;
	TCCR1B = 0;
	OCR1A = L_Time;
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS12);
	TIMSK1 |= (1 << OCIE1A);
	sei();
*/
}

void RGB_Matrix::drawNextFrameLine()
{
	if (_busy)
		return;
	else
		_busy = true;

	PORTB |= B00100000; // OE off (HIGH)

	// Calculate next gradient step
	if (_frameBStep == 7)
	{
		_frameBStep = 0;
	}
	else
	{
		_frameBStep++;
	}

	// Calculate next frame line
	if (_frameLine == PANEL_SCAN_N - 1)
	{
		_frameLine = 0;
	}
	else
	{
		_frameLine++;
	}

	// Row select
	BitSetFast(PORTD, 7, !!(_frameLine & B00000001));
	BitSetFast(PORTD, 6, !!(_frameLine & B00000010));
	//digitalWrite(PIN_LINE_A, !!(_frameLine & B00000001));
	//digitalWrite(PIN_LINE_B, !!(_frameLine & B00000010));

	for (uint8_t panels_row = 0; panels_row < _drawSizeY / PANEL_SIZE_Y; panels_row++)
	{
		for (uint8_t block = 0; block < _drawSizeX / 8; block++)
		{
			for (uint8_t row = 0; row < PANEL_SIZE_Y / PANEL_SCAN_N; row++)
			{
				//int pos = panels_h * _drawSizeX * PANEL_SIZE_Y + _drawSizeX * PANEL_SIZE_Y - column - row * _drawSizeX * PANEL_SCAN_N - (-_frameLine + PANEL_SCAN_N - 1) * _drawSizeX;
				for (uint8_t pixelInBlock = 0; pixelInBlock < 8; pixelInBlock++)
				{
					int pos = (panels_row * _drawSizeX * PANEL_SIZE_Y) + (_drawSizeX * PANEL_SIZE_Y) - (_drawSizeX - block * 8) - row * _drawSizeX * PANEL_SCAN_N - (-_frameLine + PANEL_SCAN_N - 1) * _drawSizeX + pixelInBlock;

					uint8_t offset = B00000001 << _frameBStep;

					// Set all bits. Holy s**t...
					PORTB = B00110000 | // 6th bit - OE pin (13 / Inverted)
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

					// Clock pin HIGH, LOW
					//PORTB |= B00010000;	// already set
					PORTB &= ~B00010000;
				}
			}
		}
		//Serial.println();
	}

	// Line done. Send latch signal.
	PORTB |= B00001000;
	//PORTB &= ~B00001000;

	PORTB &= ~B00101000; // LE + OE signal

	//PORTB &= ~B00100000; // OE on (LOW)
	//delayMicroseconds(50);
	//PORTB |= B00100000; // OE off (HIGH)

	//Serial.println();
	_busy = false;
}

void RGB_Matrix::clear()
{
	fillScreen(Color_Black);
	/*
	memset(_frame_buffer, Color_Black, _drawSizeX * _drawSizeY);
	for (int pos = 0; pos < _drawSizeX * _drawSizeY; pos++)
	{
		_frame_buffer[pos] = Color_Black;
	}
	*/
}

void RGB_Matrix::fillScreen(uint8_t color)
{
	memset(_frame_buffer, color, _drawSizeX * _drawSizeY);
}

void RGB_Matrix::setFont(Font font)
{
	_font = font;
}

bool RGB_Matrix::setCursor(uint8_t x, uint8_t y)
{
	if ((x >= _drawSizeX) || (y >= _drawSizeY))
		return false;
	else
	{
		_cursor_x = x;
		_cursor_y = y;
		return true;
	}
}

uint8_t RGB_Matrix::ColorFromRGB(uint8_t r, uint8_t g, uint8_t b)
{
	return (r & B11100000) | (g & B11100000) >> 3 | (b & B11000000) >> 6;
}

#ifdef ENABLE_HSV
uint8_t RGB_Matrix::ColorFromHSV(long hue, uint8_t sat, uint8_t val, boolean gflag)
{

	uint8_t r, g, b, lo;
	uint16_t s1, v1;

	// Hue
	hue %= 1536; // -1535 to +1535
	if (hue < 0)
		hue += 1536; //     0 to +1535
	lo = hue & 255;  // Low byte  = primary/secondary color mix
	switch (hue >> 8)
	{ // High byte = sextant of colorwheel
	case 0:
		r = 255;
		g = lo;
		b = 0;
		break; // R to Y
	case 1:
		r = 255 - lo;
		g = 255;
		b = 0;
		break; // Y to G
	case 2:
		r = 0;
		g = 255;
		b = lo;
		break; // G to C
	case 3:
		r = 0;
		g = 255 - lo;
		b = 255;
		break; // C to B
	case 4:
		r = lo;
		g = 0;
		b = 255;
		break; // B to M
	default:
		r = 255;
		g = 0;
		b = 255 - lo;
		break; // M to R
	}

	// Saturation: add 1 so range is 1 to 256, allowig a quick shift operation
	// on the result rather than a costly divide, while the type upgrade to int
	// avoids repeated type conversions in both directions.
	s1 = sat + 1;
	r = 255 - (((255 - r) * s1) >> 8);
	g = 255 - (((255 - g) * s1) >> 8);
	b = 255 - (((255 - b) * s1) >> 8);

	// Value (brightness) & 16-bit color reduction: similar to above, add 1
	// to allow shifts, and upgrade to int makes other conversions implicit.
	v1 = val + 1;
	if (gflag)
	{											   // Gamma-corrected color?
		r = pgm_read_byte(&gamma_table[(r * v1)]); // Gamma correction table maps
		g = pgm_read_byte(&gamma_table[(g * v1)]); // 8-bit input to 4-bit output
		b = pgm_read_byte(&gamma_table[(b * v1)]);
	}
	else
	{
		// linear (uncorrected) color
		r = (r * v1) >> 8; // 4-bit results
		g = (g * v1) >> 8;
		b = (b * v1) >> 8;
	}

	return (r & B11100000) | (g & B11100000) >> 3 | (b & B11000000) >> 6;
}
#endif

// Set pixel
void RGB_Matrix::drawPixel(uint8_t x, uint8_t y, uint8_t color)
{
	_drawPixel(x, y, color);
}

void RGB_Matrix::_drawPixel(uint8_t x, uint8_t y, uint8_t color)
{
	_frame_buffer[y * _drawSizeX + x] = color;
}

void RGB_Matrix::drawChar(uint8_t x, uint8_t y, char c, uint8_t color)
{
	//if ((y + _font.char_height) >= _drawSizeY - 1)	// Remove padding
	//	return;

	//if ((x + _font.char_width) >= _drawSizeX - 1)
	//	return;

	uint8_t i, d, bit;
	for (i = 0; i < _font.char_width; i++)
	{
		d = pgm_read_ptr(_font.font + (c * _font.char_width) + i);
		for (bit = 0; bit < _font.char_height; bit++)
		{
			if (d & (B00000001 << bit))
			{
				_drawPixel(x + i, y + bit, color);
			}
			else
			{
				_drawPixel(x + i, y + bit, 0); // Empty / Black
			}
		}
	}

	// Add right space
	for (bit = 0; bit < _font.char_height; bit++)
	{
		_drawPixel(x + _font.char_width, y + bit, 0x00); // Empty / Black
	}
}

void RGB_Matrix::drawString(uint8_t x, uint8_t y, int value, uint8_t color)
{
	if (!setCursor(x, y))
		return;

	char string[16];
	uint8_t i = 0;
	char c;
	itoa(value, string, 10);
	while ((c = (string[i++])))
	{
		_drawChar(c, color);
	}
}

void RGB_Matrix::drawString(uint8_t x, uint8_t y, const char *string, uint8_t color)
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

void RGB_Matrix::drawString(uint8_t x, uint8_t y, const __FlashStringHelper *string, uint8_t color)
{
	if (!setCursor(x, y))
		return;

	PGM_P p = reinterpret_cast<PGM_P>(string);
	while (1)
	{
		unsigned char c = pgm_read_byte(p++);
		if (!c)
			return;
		_drawChar(c, color);
	}
}

void RGB_Matrix::drawString(uint8_t x, uint8_t y, char *string, uint8_t color)
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

void RGB_Matrix::drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color)
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
			_drawPixel(y1, x1, color);
		}
		else
		{
			_drawPixel(x1, y1, color);
		}
		err -= dy;
		if (err < 0)
		{
			y1 += ystep;
			err += dx;
		}
	}
}

void RGB_Matrix::drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color)
{
	uint8_t i;
	for (i = x; i < x + w; i++)
	{
		_drawPixel(i, y, color);
		_drawPixel(i, y + h - 1, color);
	}
	for (i = y; i < y + h; i++)
	{
		_drawPixel(x, i, color);
		_drawPixel(x + w - 1, i, color);
	}
}

void RGB_Matrix::drawFillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color)
{
	uint8_t row, col;
	for (row = y; row < y + h; row++)
	{
		for (col = x; col < x + w; col++)
		{
			_drawPixel(col, row, color);
		}
	}
}

void RGB_Matrix::drawCircle(uint8_t x, uint8_t y, uint8_t r, uint8_t color)
{
	int8_t f = 1 - r;
	int8_t ddF_x = 1;
	int8_t ddF_y = -2 * r;
	int8_t tmp_x = 0;
	int8_t tmp_y = r;

	_drawPixel(x, y + r, color);
	_drawPixel(x, y - r, color);
	_drawPixel(x + r, y, color);
	_drawPixel(x - r, y, color);

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

		_drawPixel(x + tmp_x, y + tmp_y, color);
		_drawPixel(x - tmp_x, y + tmp_y, color);
		_drawPixel(x + tmp_x, y - tmp_y, color);
		_drawPixel(x - tmp_x, y - tmp_y, color);

		_drawPixel(x + tmp_y, y + tmp_x, color);
		_drawPixel(x - tmp_y, y + tmp_x, color);
		_drawPixel(x + tmp_y, y - tmp_x, color);
		_drawPixel(x - tmp_y, y - tmp_x, color);
	}
}

void RGB_Matrix::drawFillCircle(uint8_t x, uint8_t y, uint8_t r, uint8_t color)
{
	int8_t f = 1 - r;
	int8_t ddF_x = 1;
	int8_t ddF_y = -2 * r;
	int8_t tmp_x = 0;
	int8_t tmp_y = r;
	uint8_t i;

	for (i = y - r; i <= y + r; i++)
	{
		_drawPixel(x, i, color);
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
			_drawPixel(x + tmp_x, i, color);
			_drawPixel(x - tmp_x, i, color);
		}
		for (i = y - tmp_x; i <= y + tmp_x; i++)
		{
			_drawPixel(x + tmp_y, i, color);
			_drawPixel(x - tmp_y, i, color);
		}
	}
}

#ifdef _DEBUG
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
#endif // _DEBUG
