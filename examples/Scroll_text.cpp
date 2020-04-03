#include <Arduino.h>
#include "Adafruit_GFX.h"
#include <HUB08_Panel.h>

HUB08_Panel screen(48, 12);

void setup() {
	screen.begin();
	//screen.setTextWrap(false); 		// Allow text to run off right edge
	//screen.setFont(&FreeSans9pt7b);	// Hmm... Not work...
	screen.setCursor(1, 3);
	screen.setTextColor(Color_Green);
	screen.setTextWrap(false);
	screen.print(F("Hi!"));
}

int16_t scroll_x = screen.width() - 1;	// Scroll text from left to right
const char scroll_text[] = "Hello, world!";

void loop() {
#if !defined(USE_INTERRUPT_INT)
	screen.Update();
#if !defined(USE_INTERRUPT_OUT)
	delayMicroseconds(10);
#endif
#endif

	screen.fillScreen(Color_Black);
	screen.setCursor(scroll_x, 3);
	screen.setTextColor(Color_Magenta);
	screen.print(scroll_text);
	if (scroll_x > -((int16_t)sizeof(scroll_text) * 6))
		scroll_x--;
	else
		scroll_x = screen.width();

	delay(50);	// ~20 FPS
}