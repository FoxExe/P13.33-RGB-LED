/*
// Arduino pins:
PIN_OE		13
PIN_CLK		12
PIN_LATCH	11
PIN_LINE_A	7
PIN_LINE_B	6
PIN_RED		8
PIN_GREEN	9
PIN_BLUE	10

// HUB08 pinout:
	GND		A
	GND		B
	GND		C
	OE		D
	RA1		G1
	B1		RB1
	GND		LAT
	GND		CLK
*/

#include <Arduino.h>

#include "RGB_Matrix.h"

//#include "font_5x8.h"
#include "font_5x6.h"
//#include "font_8x10.h"
#include "font_Terminus_8x12.h"

RGB_Matrix screen(1, 2); // Panels count (Rows / columns)

void setup()
{
	screen.init();
	screen.setFont(font_5x6);
}

uint16_t line = 0;
int frame = 0;

ISR(TIMER1_COMPA_vect)
{
	screen.drawNextFrameLine();

	if (line == PANEL_SCAN_N - 1)
	{
		frame++;
		line = 0;
	}
	else
	{
		line++;
	}
}

#define TIMER1_PERIOD 1000 // 1 sec
#define TIMER2_PERIOD 5000 // 3 sec

uint32_t timer1 = 0;
uint32_t timer2 = 0;

uint8_t mode = 0;

void loop()
{
	// DEMO
	if (millis() - timer1 >= TIMER1_PERIOD)
	{
		switch (mode)
		{
		case 0:
		{
			screen.setFont(font_5x6);
			screen.drawString(2, 3, F("SEC:"), Color_Cyan);
			screen.drawString(25, 3, millis() / 1000, Color_Magenta);
			screen.drawRect(0, 0, screen.Width(), screen.Height(), Color_White);
		}
		break;
		case 1:
		{
			screen.drawString(2, 3, F("FPS:"), Color_White);
			screen.drawString(25, 3, frame, Color_Green);
			screen.drawRect(0, 0, screen.Width(), screen.Height(), Color_Red);
		}
		break;
		case 2:
		{
			screen.setFont(font_Terminus_8x12);
			screen.drawString(2, 0, F("01234"), Color_Yellow);
		}
		break;
		case 3:
		{
			screen.drawString(2, 0, F("ABCDE"), Color_Red);
		}
		break;
		case 4:
		{
			screen.drawString(2, 0, F("(%@?)"), Color_Green);
		}
		break;
		default:
		{
			screen.drawString(2, 0, F("DEMO!"), Color_Blue);
			mode = 0;
			frame = 0;
			return;
		}
		break;
		}

		frame = 0;

		do
		{
			timer1 += TIMER1_PERIOD;
			if (timer1 < TIMER1_PERIOD)
				break;								 // переполнение uint32_t
		} while (timer1 < millis() - TIMER1_PERIOD); // защита от пропуска шага
	}

	if (millis() - timer2 >= TIMER2_PERIOD)
	{
		screen.clear();
		mode++;

		do
		{
			timer2 += TIMER2_PERIOD;
			if (timer2 < TIMER2_PERIOD)
				break;
		} while (timer2 < millis() - TIMER2_PERIOD);
	}
}