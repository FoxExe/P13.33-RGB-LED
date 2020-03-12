#include <Arduino.h>	// Need for PlatformIO

#include <HUB08_Panel.h>
//#include <Fonts/FreeMono9pt7b.h>

// One panel size (w/h): 24 x 12
// But i use two.
HUB08_Panel screen(48, 12);

#define TIMER1_PERIOD 1000 // Update info on panel every 1 second
uint32_t timer1 = 0;

void setup() {
	screen.begin();
	//screen.setTextWrap(false); // Allow text to run off right edge
	//screen.setTextSize(1);
	//screen.setFont(&FreeMono9pt7b);
	screen.setTextColor(Color_Green);
	screen.setCursor(0, 0);
	screen.print(F("Test"));
}

void loop() {
	screen.Update();	// Update one line at time (3 line per frame)
	delayMicroseconds(10);	// Brighteness

	if (millis() - timer1 >= TIMER1_PERIOD)
	{
		screen.fillScreen(0);
		screen.drawRect(0, 0, screen.width(), screen.height(), Color_White);

		screen.setTextColor(Color_Green);
		screen.setCursor(2, 3);
		screen.print(F("FPS:"));
		screen.print(screen.frames);

		screen.frames = 0;	// Reset frames counter for calculate frames per second

		do
		{
			timer1 += TIMER1_PERIOD;
			if (timer1 < TIMER1_PERIOD)
				break;
		} while (timer1 < millis() - TIMER1_PERIOD);
	}
}