/*
 * GPIO pinout:
 * 
 * B   = 6
 * A   = 7
 * RA1 = 8
 * G1  = 9
 * B1  = 10
 * LAT = 11
 * CLK = 12
 * OE  = 13
 * 
 */

#include <Arduino.h>	// Need for PlatformIO

#include <HUB08_Panel.h>
//#include <Fonts/FreeSans9pt7b.h>

// One panel size (w/h): 24 x 12
HUB08_Panel screen(24, 12);

#define TIMER_PERIOD 1000 // Update info on panel every 1 second
uint32_t timer = 0;

void setup() {
	screen.begin();
	screen.setTextColor(Color_Green);
	//screen.setTextWrap(false); // Allow text to run off right edge
	//screen.setFont(&FreeSans9pt7b);	// BROCKEN :(
	screen.setCursor(1, 3);
	screen.print(F("Hi!"));
}

uint8_t r = 8;	// Start from red
uint8_t g = 0;
uint8_t b = 0;

uint8_t nextColor() {
	if (b == 0 && r > 0) {
		r--;
		g++;
	} else if (r == 0 && g > 0) {
		g--;
		b++;
	} else {
		b--;
		r++;
	}

	return (r << 5) | (g << 2) | (b >> 1);
}

void loop() {
#ifdef USE_INTERRUPT_OUT
	screen.Update();	// Update one line at time (3 line per frame)
#endif

	if (millis() - timer >= TIMER_PERIOD)
	{
		for (uint8_t x = 0; x < screen.width(); x++)
		{
			screen.drawLine(x, 0, x, screen.height() - 1, nextColor());
#ifdef USE_INTERRUPT_OUT
			screen.Update();	// drawLine() not so fast, so need draw frame/line
#endif
		}

		nextColor();

		do
		{
			timer += TIMER_PERIOD;
			if (timer < TIMER_PERIOD)
				break;
		} while (timer < millis() - TIMER_PERIOD);
	}
}