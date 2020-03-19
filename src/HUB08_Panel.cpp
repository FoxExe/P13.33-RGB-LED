#include "HUB08_Panel.h"

#if defined(ENAMLE_HSV)
	#include "gamma.h"
#endif

static HUB08_Panel *activePanel = NULL;

// Same as GFXCanvas8
HUB08_Panel::HUB08_Panel(uint16_t width, uint16_t height) : Adafruit_GFX(width, height) {
	// Use 1 byte buffer and 332 colors for reduce memory usage
	uint32_t bytes = width * height;
	if ((buffer = (uint8_t *)malloc(bytes))) {
		memset(buffer, 0, bytes);
	}
}

HUB08_Panel::~HUB08_Panel() {
	if (buffer)
		free(buffer);
}

// 565 to 332
inline uint8_t HUB08_Panel::Color_From_565(uint16_t c) {
	return (c & 0xE000) >> 8 | (c & 0x700) >> 6 | (c & 0x18) >> 3;
}

// 24-bit RGB to 565
uint16_t HUB08_Panel::Color_From_RGB(uint8_t r, uint8_t g, uint8_t b) {
	return (r & B11111000) << 8 | (g & B11111100) << 3 | (b & B11111000) >> 3;
}

// 332 to 565
uint16_t HUB08_Panel::Color_From_332(uint8_t c) {
	return (c & B11100000) << 8 | (c & B00011100) << 6 | (c & B00000011) << 3;
}

#if defined(ENAMLE_HSV)
uint16_t HUB08_Panel::Color_From_HSV(long hue, uint8_t sat, uint8_t val, boolean gflag) {
	uint8_t  r, g, b, lo;
	uint16_t s1, v1;

	// Hue
	hue %= 1536;              // -1535 to +1535
	if (hue < 0) hue += 1536; //     0 to +1535
	lo = hue & 255;           // Low byte  = primary/secondary color mix
	switch (hue >> 8) {       // High byte = sextant of colorwheel
		case 0 : r = 255     ; g =  lo     ; b =   0     ; break; // R to Y
		case 1 : r = 255 - lo; g = 255     ; b =   0     ; break; // Y to G
		case 2 : r =   0     ; g = 255     ; b =  lo     ; break; // G to C
		case 3 : r =   0     ; g = 255 - lo; b = 255     ; break; // C to B
		case 4 : r =  lo     ; g =   0     ; b = 255     ; break; // B to M
		default: r = 255     ; g =   0     ; b = 255 - lo; break; // M to R
	}

	// Saturation: add 1 so range is 1 to 256, allowig a quick shift operation
	// on the result rather than a costly divide, while the type upgrade to int
	// avoids repeated type conversions in both directions.
	s1 = sat + 1;
	r  = 255 - (((255 - r) * s1) >> 8);
	g  = 255 - (((255 - g) * s1) >> 8);
	b  = 255 - (((255 - b) * s1) >> 8);

	// Value (brightness) & 16-bit color reduction: similar to above, add 1
	// to allow shifts, and upgrade to int makes other conversions implicit.
	v1 = val + 1;
	if (gflag) {	// Gamma-corrected color?
		r = pgm_read_byte(&gamma_table[(r * v1) >> 8]); // Gamma correction table maps
		g = pgm_read_byte(&gamma_table[(g * v1) >> 8]); // 8-bit input to 4-bit output
		b = pgm_read_byte(&gamma_table[(b * v1) >> 8]);
	} else { // linear (uncorrected) color
		r = (r * v1) >> 12; // 4-bit results
		g = (g * v1) >> 12;
		b = (b * v1) >> 12;
	}

	return
		(r << 12) | ((r & 0x8) << 8) | // 4/4/4 -> 5/6/5
		(g <<  7) | ((g & 0xC) << 3) |
		(b <<  1) | ( b        >> 3);
}
#endif

void HUB08_Panel::drawPixel(int16_t x, int16_t y, uint16_t color) {
	if ((x < 0) || (y < 0) || (x >= _width) || (y >= _height))
		return;

	int16_t t;
	switch (rotation) {
		case 1:
			t = x;
			x = WIDTH - 1 - y;
			y = t;
			break;
		case 2:
			x = WIDTH - 1 - x;
			y = HEIGHT - 1 - y;
			break;
		case 3:
			t = x;
			x = y;
			y = HEIGHT - 1 - t;
			break;
	}

	// Save 565 color as 332
	buffer[x + y * WIDTH] = Color_From_565(color);
}

void HUB08_Panel::fillScreen(uint16_t color) {
	memset(buffer, Color_From_565(color), WIDTH * HEIGHT);
}

void HUB08_Panel::writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
	if ((x >= _width) || (y < 0) || (y >= _height))
		return;

	int16_t x2 = x + w - 1;
	if (x2 < 0)
		return;

	// Clip left/right
	if (x < 0) {
		x = 0;
		w = x2 + 1;
	}

	if (x2 >= _width)
		w = _width - x;

	int16_t t;
	switch (rotation) {
		case 1:
			t = x;
			x = WIDTH - 1 - y;
			y = t;
			break;
		case 2:
			x = WIDTH - 1 - x;
			y = HEIGHT - 1 - y;
			break;
		case 3:
			t = x;
			x = y;
			y = HEIGHT - 1 - t;
			break;
	}

	memset(buffer + y * WIDTH + x, Color_From_565(color), w);
}


void HUB08_Panel::begin() {
	activePanel = this;

	// PORTB = Ports: 15, 14, 13, 12, 11, 10, 9, 8	(Digital) (14, 15 - Oscillator pins. Do not use!)
	// PORTC = Ports: -, -, A5, A4, A3, A2, A1, A0	(Analog)
	// PORTD = Ports: 7, 6, 5, 4, 3, 2, 1, 0		(Digital)

	DDRB  |= B00111111;	// Port B: Data Direction Register (1 = Out, 0 = In)
	PORTB |= B00100000;	// Port B: Data Register / Output (1 = High, 0 = Low)
	//PINB = B00000000;	// Port B: Inputs Pins Register (read only)

	DDRD  |= B11000000;	// Port D: Data Direction Register (1 = Out, 0 = In)
	PORTD |= B00000000;	// Port D: Data Register / Output (1 = High, 0 = Low)
	//PIND = B00000000;	// Port D: Inputs Pins Register (read only)

#if defined(USE_INTERRUPT) && !defined(USE_INTERRUPT_ALT)
	cli();		// Disable interrupts
	TCCR1A  = _BV(WGM11); // Mode 14 (fast PWM), OC1A off
	TCCR1B  = _BV(WGM13) | _BV(WGM12) | _BV(CS10); // Mode 14, no prescale
	ICR1    = LINE_TIME;
	TIMSK1 |= _BV(TOIE1); // Enable Timer1 interrupt
	sei();                // Enable global interrupts
#endif //USE_INTERRUPT

#if defined(USE_INTERRUPT_ALT) && !defined(USE_INTERRUPT)
	// Reset timer1 interrupts
	TCCR1A = 0; 
	TCCR1B = 0;

	// Enable CTC mode and set prescaler to 1024
	bitWrite(TCCR1B, CS12, 1); 
	bitWrite(TCCR1B, CS11, 0);
	bitWrite(TCCR1B, CS10, 1); 

	// 16MHz CPU speed / Delimeter 1024 / 800 Hz (800Hz / 3 ScanLine = ~266 FPS)
	OCR1A = F_CPU / 1024 / LINE_TIME_ALT;

	bitWrite(TCCR1B, WGM12, 1);		// Reset counter
	bitWrite(TIMSK1, OCIE1A, 1);	// Start timerinterrupt

	sei();
/*
	cli();		// Disable interrupts
	TCCR1A = 0; // Reset registers
	TCCR1B = 0;
	TCCR1B |= _BV(WGM12);		// Turn ON CTC
	TCCR1B |= _BV(CS12);		// Delimeter: 256
	OCR1A = 52 * ((WIDTH / PANEL_SIZE_X) * (HEIGHT / PANEL_SIZE_Y));
	TCNT1 = 0;
	TIFR1 |= _BV(OCF1A);   // clear any pending interrupts
	TIMSK1 |= _BV(OCIE1A); // enable the output compare interrupt
	sei(); // Enable interrupts
*/
#endif

}

void HUB08_Panel::Update() {
	if (!_update) return;

	PORTB |= B00100000; // OE off (HIGH)

	PORTD &= B00000011;	// Clear LINE_A/LINE_B
	PORTD |= _line_map[_line_num];	// Set LINE_A/LINE_B

	for (uint8_t panels_row = 0; panels_row < _height / PANEL_SIZE_Y; panels_row++)
	{
		for (uint8_t block = 0; block < _width / 8; block++)
		{
			for (uint8_t row = 0; row < PANEL_SIZE_Y / PANEL_SCAN_N; row++)
			{
				for (uint8_t pixelInBlock = 0; pixelInBlock < 8; pixelInBlock++)
				{
					int pos =
						(panels_row * _width * PANEL_SIZE_Y)
						+ (_width * PANEL_SIZE_Y)
						- (_width - block * 8) - row * _width * PANEL_SCAN_N
						- (-_line_num + PANEL_SCAN_N - 1) * _width + pixelInBlock;

					PORTB &= B11101000;	// CLR + RGB off
					PORTB |=
						((((buffer[pos] & B11100000) >> 5) > _frame_num)? B00000001 : B00000000) |
						((((buffer[pos] & B00011100) >> 2) > _frame_num)? B00000010 : B00000000) |
						((((buffer[pos] & B00000011) << 1) > _frame_num)? B00000100 : B00000000) |
						B00010000; // Set CLK to HIGH
				}
			}
		}
	}

	PORTB &= B11101000;	// CLR + RGB off
	PORTB |= B00001000;	// LE on
	PORTB &= B11010111; // OE on, LE off

	// Calculate next line number
	if (_line_num == PANEL_SCAN_N - 1) {
		_line_num = 0;

		if (_frame_num == 7)
			_frame_num = 0;
		else
			_frame_num++;
	} else
		_line_num++;

	// Reset interrupt timer and set next time
#if defined(USE_INTERRUPT)
	ICR1      = LINE_TIME;
	TCNT1     = 0;
#elif defined(USE_INTERRUPT_ALT)
	_update = false;
#endif
}

#ifdef DEBUG
void HUB08_Panel::dumpBuffer()
{
	Serial.println(F("=== Buffer: ==="));

	for (uint8_t row = 0; row < _height; row++)
	{
		for (uint8_t col = 0; col < _width; col++)
		{
			Serial.print(F("0x"));
			Serial.print(buffer[_width * row + col], HEX);
			Serial.print(F(", "));
		}
		Serial.println();
	}
	Serial.println();
}
#endif // DEBUG


#if defined(USE_INTERRUPT) && !defined(USE_INTERRUPT_ALT)
ISR(TIMER1_OVF_vect, ISR_BLOCK) {
	activePanel->Update();	// Draw frame (One line)
	TIFR1 |= TOV1;			// Clear Timer1 interrupt flag
}
#endif //USE_INTERRUPT

// Set interrupt
#if defined(USE_INTERRUPT_ALT) && !defined(USE_INTERRUPT)
void HUB08_Panel::SetUpdate() {
	_update = true;
}

ISR (TIMER1_COMPA_vect)
{
	activePanel->SetUpdate();
}
#endif

