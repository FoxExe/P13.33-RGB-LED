/*
	Name:		HUB08_12x24_RGB.ino
	Created:	9/29/2017 8:19:44 PM
	Author:		Allester Fox <fox.axon@gmail.com>

	Panel name: P13.33-3S-1R1G1B-24X12
	Panel base: 6x JXI5020 for leds and LeadASIC PR4538 as main controller
	Panel interface: HUB08
	Pinouts:
	GND		A
	GND		B
	GND		C
	OE		D
	RA1		G1
	B1		RB1
	GND		LAT
	GND		CLK

*/

#define TIMER_DELAY  50

#include "RGB_Matrix.h"
#include "font.h"

#include <Wire.h>
#include <RTClib.h>
//RTC_Millis rtc; // Wrong data because draw frames in interrupt (timer1) too slow
RTC_DS3231 rtc;

#include <timer-api.h>

#define PIN_OE		13
#define PIN_CLK		12
#define PIN_LATCH	11
#define PIN_LINE_A	7
#define PIN_LINE_B	6
#define PIN_RED		8
#define PIN_GREEN	9
#define PIN_BLUE	10

RGB_Matrix panel(PANEL_SIZE_X * 2, PANEL_SIZE_Y);	// Panels size

void setup() {
	Serial.begin(115200);

	timer_init_ISR_100Hz(TIMER_DEFAULT);

	if (!rtc.begin())
	{
		char buffer[8];
		sprintf(buffer, "RTC ERR");
		panel.drawString(0, 2, buffer, panel.green);
		while (1);
	}

	if (rtc.lostPower())
	{
		// Jan 10 2020, 10:20:30
		rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
	}

	//panel.init(PIN_CLK, PIN_LATCH, PIN_OE, PIN_LINE_A, PIN_LINE_B, PIN_RED, PIN_GREEN, PIN_BLUE);
	panel.init();
	panel.setBrightness(20);	// 25 if not set (Default)
	panel.setFont(font5x8);

	panel.drawRect(0, 0, panel.Width(), panel.Height(), panel.blue);
}

extern "C" {
	void timer_handle_interrupts(int timer) {
		panel.drawFrame();
	}
}

unsigned long timer_delay = 0;

void loop() {
	if (millis() / TIMER_DELAY != timer_delay) {
		timer_delay = millis() / TIMER_DELAY;

		DateTime now = rtc.now();
		char buffer[8];

		if (now.second() % 30 < 4)
		{
			sprintf(buffer, " %02d.%02d  ", now.day(), now.month());
		}
		else
		{
			sprintf(buffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
		}
		panel.drawString(0, 2, buffer, panel.green);
	}

	if (Serial.available() > 0) {
		String command = Serial.readStringUntil('\n');	// Read first part
		if (command.startsWith(F("get")))
		{
			DateTime now = rtc.now();
			Serial.print(now.day());
			Serial.print(".");
			Serial.print(now.month());
			Serial.print(".");
			Serial.print(now.year());
			Serial.print(" ");
			Serial.print(now.hour());
			Serial.print(":");
			Serial.print(now.minute());
			Serial.print(":");
			Serial.print(now.second());
			Serial.println();
		}

		// set
		// 25.01.2020 09:30:00
		if (command.startsWith(F("set")))
		{
			Serial.println(F("Type date/time in format: DD.MM.YYYY hh:mm:ss"));
			String set_day = Serial.readStringUntil('.');
			String set_month = Serial.readStringUntil('.');
			String set_year = Serial.readStringUntil(' ');
			String set_hour = Serial.readStringUntil(':');
			String set_minute = Serial.readStringUntil(':');
			String set_seconds = Serial.readStringUntil('\n');

			Serial.println(F("Parsed data:"));
			Serial.print(set_day);
			Serial.print(".");
			Serial.print(set_month);
			Serial.print(".");
			Serial.print(set_year);
			Serial.print(" ");
			Serial.print(set_hour);
			Serial.print(":");
			Serial.print(set_minute);
			Serial.print(":");
			Serial.print(set_seconds);
			Serial.println();

			rtc.adjust(DateTime(set_day.toInt(), set_month.toInt(), set_day.toInt(), set_hour.toInt(), set_minute.toInt(), set_seconds.toInt()));
			//rtc.adjust();
		}
	}
}