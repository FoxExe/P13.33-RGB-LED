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

// This line for platform.io
#include <Arduino.h>

#include "RGB_Matrix.h"
#include "font_5x8.h"

RGB_Matrix screen(1, 1); // Panels count/configuration (Rows / Columns)

void setup()
{
	screen.init();
	screen.setFont(font5x8);
}

uint16_t line = 0;
int frame = 0;

// Draw 
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

#define TIMER1_PERIOD 1000 // Update screen every 1 second
#define TIMER2_PERIOD 5000 // Change task every 5 seconds

uint32_t timer1 = 0;
uint32_t timer2 = 0;

uint8_t mode = 0;

void loop()
{
	/*
	// For calculate maximum FPS
	screen.drawNextFrameLine();
	delayMicroseconds(50);	// Brighteness
	if (line == PANEL_SCAN_N - 1)
	{
		frame++;
		line = 0;
	}
	else
	{
		line++;
	}
	*/

	// DEMO
	if (millis() - timer1 >= TIMER1_PERIOD)
	{
		switch (mode)
		{
		case 0:	// DRAW RAINBOW
		{
			uint8_t color_interval_x = 255 * 3 / screen.Width();
			//uint8_t color_interval_y = 255 / screen.Height();

			uint8_t r = 255, g = 0, b = 0, step = 0;

			for (uint8_t y = 0; y < screen.Height(); y++)
			{
				for (uint8_t x = 0; x < screen.Width(); x++)
				{
					do
					{
						if (r > 0 && b == 0)
						{
							r--;
							g++;
						}
						if (g > 0 && r == 0)
						{
							g--;
							b++;
						}
						if (b > 0 && g == 0)
						{
							r++;
							b--;
						}
						step++;
					} while (step < color_interval_x);
					screen.drawPixel(x, y, screen.ColorFromRGB(r, g, b));
					step = 0;
				}

				r = 255, g = 0, b = 0;
			}
		}
		break;
		case 1:	// DRAW ALL COLORS
		{
			uint8_t color_interval = 255 * 3 / screen.Width();
			for (uint8_t x = 0; x < screen.Width(); x++)
			{
				for (uint8_t y = 0; y < screen.Height(); y++)
				{
					screen.drawPixel(x, y, x * color_interval);
				}
			}
		}
		break;
		case 2:	// SHOW FPS COUNTER
		{
			if (screen.Width() > PANEL_SIZE_X)
			{
				screen.drawString(2, 3, F("FPS:"), Color_White);
				screen.drawString(25, 3, frame, Color_Green);
			}
			else
			{
				screen.drawString(2, 3, frame, Color_Green);
			}
			screen.drawRect(0, 0, screen.Width(), screen.Height(), Color_Blue);
		}
		break;
		case 3:	// SHOW SECONDS COUNTER
		{
			if (screen.Width() > PANEL_SIZE_X)
			{
				screen.drawString(2, 3, F("SEC:"), Color_Yellow);
				screen.drawString(25, 3, millis() / 1000, Color_Red);
			}
			else
			{
				screen.drawString(2, 3, millis() / 1000, Color_Red);
			}
			screen.drawRect(0, 0, screen.Width(), screen.Height(), Color_Cyan);
		}
		break;
		default:
		{
			mode = 0;
		}
		break;
		}

		frame = 0;	// Update FPS counter

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