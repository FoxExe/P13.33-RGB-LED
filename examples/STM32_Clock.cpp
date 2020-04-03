#include <Arduino.h>
#include "Adafruit_GFX.h"
#include <HUB08_Panel.h>

HUB08_Panel screen(48, 12);

bool ledstate = true;

void setup() {
	screen.begin();
	//screen.setTextWrap(false); 		// Allow text to run off right edge
	//screen.setFont(&FreeSans9pt7b);	// Hmm... Not work...
	screen.setCursor(1, 3);
	screen.setTextColor(Color_Green);
	screen.setTextWrap(false);
	screen.print(F("Hi!"));

	//pinMode(LED_BUILTIN, OUTPUT);
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;	// Enable GPIO port C clock
	GPIOC->CRH &= 0xFF0FFFFF;	// Reset PC13 (Already set to 0 at start)
	GPIOC->CRH |= 0x00300000;	// Set PC13 to OUTPUT
	bitWrite(GPIOC->ODR, 13, HIGH);	// Inverted state (1 = off)

	// Enable build-in RTC
	RTC_init(HOUR_FORMAT_24, LSE_CLOCK, false);

	if (!RTC_IsTimeSet()) {
		RTC_SetDate(2020, 4, 1, RTC_WEEKDAY_WEDNESDAY);
		RTC_SetTime(12, 0, 0, 0, HOUR_AM);
	}

	// You can use these functions for better timings (Using RTC)
	// getCurrentMillis()
	// getCurrentMicros()
}

char buffer[10] = "";

struct time_data
{
	uint8_t hours = 0;
	uint8_t minutes = 0;
	uint8_t seconds = 0;
} Time;

struct date_data
{
	uint8_t year = 0;	// 0..99	- Last two digits
	uint8_t month = 0;	// 1..12
	uint8_t day = 0;	// 1..31
	uint8_t wday = 0;	// 1..7 - Day of week
} Date;

void loop() {
	ledstate = !ledstate;
	bitWrite(GPIOC->ODR, 13, ledstate);	// PC13 / Led change

	RTC_GetTime(&Time.hours, &Time.minutes, &Time.seconds, NULL, NULL);

	if (0 > Time.seconds > 5 || 30 > Time.seconds > 35) {
		RTC_GetDate(&Date.year, &Date.month, &Date.day, &Date.wday);
		screen.setCursor(0, 3);
		screen.setTextColor(Color_Blue);
		screen.fillScreen(Color_Black);	// Clear screen
		sprintf(buffer, "%02d.%02d |%1d", Date.day, Date.month, Date.wday);
		screen.print(buffer);
	} else {
		screen.setCursor(0, 3);
		screen.setTextColor(Color_Green);
		screen.fillScreen(Color_Black);	// Clear screen
		sprintf(buffer, "%02d:%02d:%02d", Time.hours, Time.minutes, Time.seconds);
		screen.print(buffer);
	}

	delay(1000);
}