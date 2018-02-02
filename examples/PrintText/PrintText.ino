/*
Name:		PrintText.ino
Created:	2/2/2018 10:00:00 PM
Author:		Allester Fox <fox.axon@gmail.com>

Panel name: P13.33-3S-1R1G1B-24X12
Panel base: 6x JXI5020 for leds and LeadASIC PR4538 as main controller
Panel interface: HUB08
HUB08 layout:
 ___________
| GND	A	|
| GND	B	|
| GND	C	|__
| OE	D	   |
| RA1	G1	 __|
| B1	RB1	|
| GND	LAT	|
| GND	CLK	|
|___________|

Used: A, B, RA1, G1, B1, LAT, CLK, OE, GND

### Benchmark ###
8 colors:
~470 FPS with 1 panel
~248 FPS with 2 panels

256 colors:
~60 fps with 1 panel
~30 fps with 2 panels

*/

#include <RGB_Matrix.h>
#include <font.h>

RGB_Matrix panel(PANEL_SIZE_X * 2, PANEL_SIZE_Y);	// Panels size

void setup() {
	Serial.begin(115200);

	panel.init();
	panel.setBrightness(20);	// OE delay (Light delay). More is bright
	panel.setFont(font5x8);

	Serial.println(F("> Ready"));
}

char CurrentChar;
char buffer[8] = "Hello! ";	// Leading zero, so use only 7 chars
uint8_t buffPos = 6;

void loop() {
	while (Serial.available() > 0)
	{
		CurrentChar = Serial.read();
		Serial.print(F("HEX: 0x"));
		Serial.println(CurrentChar, 16);

		switch (CurrentChar)
		{
		case '\r':	// 0xD
		case '\n':
			memset(buffer, ' ', 8);
			buffPos = 0;
			break;
		case '\b':	// 0xC ?
		case 0x7F:
			if (buffPos == 0)
				buffPos = 7;
			else
				buffPos--;
			buffer[buffPos] = ' ';
			break;
		case 0x41:	// Up
			break;	// Ignore
		case 0x42:	// Down
			break;	// Ignore
		case 0x43:	// Right
					// Move cursor right
			buffPos++;
			if (buffPos > 7)
				buffPos = 0;
			break;
		case 0x44:	// Left
					// Move cursor left
			if (buffPos == 0)
				buffPos = 7;
			else
				buffPos--;
			break;

		case 0x1B:	// <-
		case 0x5B:	// [
			break;	// Just ignore these chars.
		default:
			buffer[buffPos] = CurrentChar;
			buffPos++;
			if (buffPos > 7)
				buffPos = 0;
			break;
		}

		Serial.print(F("BUF: "));
		Serial.println(buffer);
		Serial.println();
	}

	panel.drawString(0, 2, buffer, Color_Green);

	panel.drawFrame();
}