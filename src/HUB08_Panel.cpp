#include "HUB08_Panel.h"

#if defined(ENAMLE_HSV)
	#include "gamma.h"
#endif

static HUB08_Panel *activePanel = NULL;

/************************* Interrupt handlers **************************/

// Set interrupt handlers
#if defined(USE_INTERRUPT_OUT) && !defined (USE_INTERRUPT_INT)

#if defined(ARDUINO_ARCH_STM32)
void TimerIntCallback(HardwareTimer*)
{
	activePanel->_update = true;
}
#elif defined(ARDUINO_ARCH_AVR)
ISR (TIMER1_COMPA_vect)
{
	activePanel->_update = true;
}
#endif	// ARDUINO_ARCH_AVR

#elif defined(USE_INTERRUPT_INT) && !defined(USE_INTERRUPT_OUT)

#if defined(ARDUINO_ARCH_STM32)
void TimerIntCallback(HardwareTimer*)
{
	activePanel->Update();
/*
	if (500 > activePanel->frames > 1000) {
		GPIOC->BSRR  = 1 << 13;	// HIGH
		activePanel->frames = 0;
	} else {
		GPIOC->BRR  = 1 << 13;	// LOW
	}
*/
}
#elif defined(ARDUINO_ARCH_AVR)
ISR (TIMER1_COMPA_vect)
{
	activePanel->Update();
}
#endif	// ARDUINO_ARCH_AVR

#endif
/***********************************************************************/


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
uint8_t HUB08_Panel::Color_From_565(uint16_t c) {
	return (c & 0xE000) >> 8 | (c & 0x700) >> 6 | (c & 0x18) >> 3;
}

// 24-bit RGB to 332
uint16_t HUB08_Panel::Color_From_RGB(uint8_t r, uint8_t g, uint8_t b) {
	return (r & B11100000) | (g & B11100000) >> 3 | (b & B11000000) >> 6;
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

	return Color_From_565(
		(r << 12) | ((r & 0x8) << 8) | // 4/4/4 -> 5/6/5
		(g <<  7) | ((g & 0xC) << 3) |
		(b <<  1) | ( b        >> 3));
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
	buffer[x + y * WIDTH] = color;
}

void HUB08_Panel::fillScreen(uint16_t color) {
	memset(buffer, color, WIDTH * HEIGHT);
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

	memset(buffer + y * WIDTH + x, color, w);
}

void HUB08_Panel::begin() {
	activePanel = this;

	/**************************************
	 * HUB08 to Atmega328p/STM32F103 pinout:
	 * 
	 * +--------+-------+-------+
	 * |  HUB	|  AVR	| STM32	|
	 * +--------+-------+-------+
	 * |  CLK	|	12	|  B12	|
	 * |  LAT	|	11	|  B9	|
	 * |   OE	|	13	|  B8	|
	 * |    A	|	6	|  B6	|
	 * |    B	|	7	|  B7	|
	 * |  RA1	|	8	|  B13	|
	 * |   G1	|	9	|  B14	|
	 * |   B1	|	10	|  B15	|
	 * +--------+-------+-------+
	 * 
	 * GND to power negative ("-" / GND)
	 * C, D, RB1 - not connected
	 **************************************/

#if defined(ARDUINO_ARCH_STM32)
	/*****************************************************************
	 * LibMaple for STM32F103xx GPIO controls explain:
	 * 
	 * PORTA->CRL - Control register HIGH, ports: 8..15
	 * PORTA->CRH - Control register LOW,   ports: 0..7
	 * 
	 * port bits: CCMM
	 * High bits (CC) - CNF (Config)
	 * Low  bits (MM) - MODE
	 * 
	 * 0000 = 0x0 - INPUT,		ANALOG
	 * 0001 = 0x1 - OUTPUT_10MHz,	PUSH_PULL
	 * 0010 = 0x2 - OUTPUT_2MHz,	PUSH_PULL
	 * 0011 = 0x3 - OUTPUT_50MHz,	PUSH_PULL
	 * 0100 = 0x4 - INPUT,		FLOAT_IN
	 * 0101 = 0x5 - OUTPUT_10MHz,	OPEN_DRAIN
	 * 0110 = 0x6 - OUTPUT_2MHz,	OPEN_DRAIN
	 * 0111 = 0x7 - OUTPUT_50MHz,	OPEN_DRAIN
	 * 1000 = 0x8 - INPUT, PULL_UP / PULL_DOWN
	 * 1001 = 0x9 - OUTPUT_10MHz,	ALT_PUSH_PULL
	 * 1010 = 0xA - OUTPUT_2MHz,	ALT_PUSH_PULL
	 * 1011 = 0xB - OUTPUT_50MHz,	ALT_PUSH_PULL
	 * 1100 = 0xC - INPUT,		[reserved]
	 * 1101 = 0xD - OUTPUT_10MHz,	ALT_OPEN_DRAIN
	 * 1110 = 0xE - OUTPUT_2MHz,	ALT_OPEN_DRAIN
	 * 1111 = 0xF - OUTPUT_50MHz,	ALT_OPEN_DRAIN
	 * 
	 * Port numbers:   76543210
	 * GPIOA->CRL &= 0x000000FF;	// Reset mode for all ports, except 0 and 1
	 * GPIOA->CRL |= 0x88033083;	// Set port modes: 1, 6, 7 = INPUT | 0, 3, 4 = OUTPUT
	 * 
	 * GPIOA->IDR - Input Data Register (Only Low 16 bits used)
	 * bool result = GPIOA->IDR & 0b0000000000000100;	// True if A2 = HIGH
	 * 
	 * GPIOA->ODR - Output Data Register (Only Low 16 bits used)
	 * GPIOA->ODR |= 0b0000000000000100;	// Set A2 to HIGH
	 * 
	 * GPIOA->BRR - Bit Reset Register
	 * GPIOA->BRR = 0b0000000000000100;		// Set A2 to LOW
	 * GPIOA->BRR = 0b0000000000000100 << 16;	// Set A2 to HIGH (Move to upper 16 bits)
	 * 
	 * GPIOA->BSRR - Bit Set Reset Register. Same as BRR, but inverted.
	 * Example:
	 * GPIOA->BRR  = 0b0000000000000100;	// Set A2 to LOW
	 * GPIOA->BSRR = 0b0000000000000100;	// Set A2 to HIGH
	 *****************************************************************/
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;	// Enable GPIO port B clock
	GPIOB->CRH &= ~0xFFFF00FF;	// Reset PB 8, 9, 12, 13, 14, 15
	GPIOB->CRH |=  0x33330033;	// Set OUTPUT mode
	GPIOB->CRL &= ~0xFF000000;	// Reset PB 6, 7
	GPIOB->CRL |=  0x33000000;	// Set OUTPUT mode
	GPIOB->ODR &= ~0b1111001111000000;	// 6..9, 12..15 -> LOW
	GPIOB->ODR |=  0b0000000100000000;	// OE -> HIGH (Inverted, so its off now)

#if defined(USE_INTERRUPT_OUT) || defined(USE_INTERRUPT_INT)
	// Setup TIM3 to 1500 Hz (Available: TIM1..4)
	HardwareTimer *MyTim = new HardwareTimer(TIM3);
	MyTim->setMode(1, TIMER_OUTPUT_COMPARE, NC);
	MyTim->setOverflow(1500, HERTZ_FORMAT); // 1500 Hz or ~500FPS
	MyTim->attachInterrupt(TimerIntCallback);
	MyTim->resume();
#endif

#elif defined(ARDUINO_ARCH_AVR)
	/*****************************************************************
	 * PORTB = Ports: 15, 14, 13, 12, 11, 10, 9, 8	(Digital) (14, 15 - Oscillator pins. Do not use!)
	 * PORTC = Ports: -, -, A5, A4, A3, A2, A1, A0	(Analog)
	 * PORTD = Ports: 7, 6, 5, 4, 3, 2, 1, 0		(Digital)
	 *****************************************************************/

	DDRB  |= B00111111;	// Port B: Data Direction Register (1 = Out, 0 = In)
	PORTB |= B00100000;	// Port B: Data Register / Output (1 = High, 0 = Low)
	//PINB = B00000000;	// Port B: Inputs Pins Register (read only)

	DDRD  |= B11000000;	// Port D: Data Direction Register (1 = Out, 0 = In)
	PORTD |= B00000000;	// Port D: Data Register / Output (1 = High, 0 = Low)
	//PIND = B00000000;	// Port D: Inputs Pins Register (read only)

#if defined(USE_INTERRUPT_OUT) || defined(USE_INTERRUPT_INT)
	// Disable interrupts
	cli();

	// Reset timer1 interrupts
	TCCR1A = 0; 
	TCCR1B = 0;

	// Enable CTC mode and set prescaler to 1024
	bitWrite(TCCR1B, WGM12, 1);
	bitWrite(TCCR1B, CS12, 1); 
	bitWrite(TCCR1B, CS11, 0);
	bitWrite(TCCR1B, CS10, 1); 

	/**************************************
	 * 16.000.000 Hz CPU speed / Delimeter 1024 / 800 Hz (800Hz / 3 ScanLine = ~266 FPS)
	 * F_CPU / 1024 / 1600 ~= 9.76  - One panel
	 * F_CPU / 1024 / 800 ~= 19.53  - Two panels
	 * With one panel we can achive better performance / less flickers
	 * Value | 1 panel | 2 panels
	 * 5 | 800 FPS | 470 FPS |
	 * 6 | 745 FPS | 400 FPS  |
	 * 7 | 650 FPS | 350 FPS  |
	 * 8 | 575 FPS | 300 FPS  |
	 **************************************/
#if defined(USE_INTERRUPT_OUT)
	OCR1A = 6 * ((WIDTH / PANEL_SIZE_X) * (HEIGHT / PANEL_SIZE_Y));
#elif defined(USE_INTERRUPT_INT)
	OCR1A = 12 * ((WIDTH / PANEL_SIZE_X) * (HEIGHT / PANEL_SIZE_Y));
#endif

	// Reset timer counter, pending interrups and enable compare interrupt
	TCNT1 = 0;
	bitWrite(TIFR1, OCF1A, 1);
	bitWrite(TIMSK1, OCIE1A, 1);

	// Enable interrupts again
	sei();
#endif	// USE_INTERRUPT_OUT | USE_INTERRUPT_INT

#endif	// ARDUINO_ARCH_STM32 | ARDUINO_ARCH_AVR

}

void HUB08_Panel::Update() {
#if defined(USE_INTERRUPT_OUT) && !defined(USE_INTERRUPT_INT)
	if (!_update) return;
	_update = false;
#endif

#if defined(ARDUINO_ARCH_STM32)
	GPIOB->ODR |= _BV(8);	// OE -> HIGH (Inverted, so its off now)
	GPIOB->ODR &= ~(_BV(6) | _BV(7));	// Reset Line A/B (pins 6 and 7)
	GPIOB->ODR |= _line_num << 6;		// Set Line A/B
#elif defined(ARDUINO_ARCH_AVR)
	PORTB |= B00100000; // OE off (HIGH)
	PORTD &= B00000011;	// Clear LINE_A/LINE_B
	PORTD |= _line_num << 6;	// Set LINE_A/LINE_B
#endif

	for (uint8_t panels_row = 0; panels_row < HEIGHT / PANEL_SIZE_Y; panels_row++)
	{
		for (uint8_t block = 0; block < WIDTH / 8; block++)
		{
			for (uint8_t row = 0; row < PANEL_SIZE_Y / PANEL_SCAN_L; row++)
			{
				for (uint8_t pixelInBlock = 0; pixelInBlock < 8; pixelInBlock++)
				{
					int pos =
						  (WIDTH * PANEL_SIZE_Y)	// Offset 1
						+ (panels_row * WIDTH * PANEL_SIZE_Y)	// Offset 2
						- (WIDTH - block * 8)	// offset 3
						- row * WIDTH * PANEL_SCAN_L	// Offset 4
						- (-_line_num + PANEL_SCAN_L - 1) * WIDTH	// Offset 5
						+ pixelInBlock;

#if defined(ARDUINO_ARCH_STM32)
					GPIOB->ODR &= ~(_BV(12) | _BV(13) | _BV(14) | _BV(15));	// Reset CLK and RGB pins

					if (((buffer[pos] & 0b11100000) >> 5) > _frame_num)
						GPIOB->ODR |= _BV(13);	// Red -> HIGH
					if (((buffer[pos] & 0b00011100) >> 2) > _frame_num)
						GPIOB->ODR |= _BV(14);	// Green -> HIGH
					if (((buffer[pos] & 0b00000011) << 1) > _frame_num)
						GPIOB->ODR |= _BV(15);	// Blue -> HIGH

					GPIOB->ODR |= _BV(12);	// CLK -> HIGH
#elif defined(ARDUINO_ARCH_AVR)
					// CLK + RGB off
					PORTB &= _BV(3) | _BV(5) | _BV(6) | _BV(7);
/*
					PORTB |=
						((((buffer[pos] & B11100000) >> 5) > _frame_num)? B00000001 : B00000000) |
						((((buffer[pos] & B00011100) >> 2) > _frame_num)? B00000010 : B00000000) |
						((((buffer[pos] & B00000011) << 1) > _frame_num)? B00000100 : B00000000) |
						B00010000; // Set CLK to HIGH
*/

					// Hmm... Strange, but this faster than previous code...
					if (((buffer[pos] & 0b11100000) >> 5) > _frame_num)
						PORTB |= _BV(0);
					if (((buffer[pos] & 0b00011100) >> 2) > _frame_num)
						PORTB |= _BV(1);
					if (((buffer[pos] & 0b00000011) << 1) > _frame_num)
						PORTB |= _BV(2);
					PORTB |= _BV(3);
#endif
				}
			}
		}
	}

#if defined(ARDUINO_ARCH_STM32)
	GPIOB->ODR &= ~(_BV(12) | _BV(13) | _BV(14) | _BV(15));	// CLK and RGB -> LOW
	GPIOB->ODR |= _BV(9);	// LAT -> HIGH
	GPIOB->ODR &= ~(_BV(9) | _BV(8));	// LAT -> LOW, OE -> LOW (on)
#elif defined(ARDUINO_ARCH_AVR)
	PORTB &= 0b11101000;	// CLK + RGB off
	PORTB |= 0b00001000;	// LAT on
	PORTB &= 0b11010111; // LAT off, OE on
#endif

	// Calculate next line number
	if (_line_num == PANEL_SCAN_L - 1) {
		_line_num = 0;

		if (_frame_num == 7)
			_frame_num = 0;
		else
			_frame_num++;

		//frames++;

	} else
		_line_num++;
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
