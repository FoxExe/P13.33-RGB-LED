# This is a library for control P13.33-3S-1R1G1B-24X12 panel.

## Panel info:
* Interface: HUB08 (RGB)
* Main control chip: LeadASIC PR4538
* Shift registers chips: JXI5020 (16 bit)

![rgb_led_panel-256-colors2](https://user-images.githubusercontent.com/3135063/31408538-5ef9a728-ae22-11e7-9c12-78d0051538ab.jpg)

## Features:
* Support 256 colors (RGB format: 332)
* Depends on Adafruit GFX library
* Support Atmega328p and STM32F103c8t6
* Atmega can drive 2 panels, but you can see flickers in interrupt mode
* STM32 can drive upto 10 panels without any issues.

## Arduino nano pinouts:
HUB08 |  AVR | STM32
------|------|-------
CLK   |  12  |  B12
LAT   |  11  |  B9
OE    |  13  |  B8
A     |  6   |  B6
B     |  7   |  B7
RA1   |  8   |  B13
G1    |  9   |  B14
B1    |  10  |  B15

## HUB08 layout:
Key  |  Key
-----|-----
GND  |    A
GND  |    B
GND  |    C
OE   |    D
RA1  |   G1
B1   |  RB1
GND  |  LAT
GND  |  CLK

# Notes:
* This library can use Timer2 (AVR) or TIM3 (STM32) for update (turn on) led's on panel. Uncomment on of these defines for this:
* `USE_INTERRUPT_OUT` - Use interrupt for set update flag. Use screen.Update() in your code for turn on leds on panel (Draw frame)
* `USE_INTERRUPT_INT` - Use interrupt for draw frames. No need to modify your code.

# TODO:
- [x] 255 (or more) colors support.
- [x] Use interrupts to get rid of flickering.
- [ ] Allow to use different GPIO pins
- [ ] Optimisation...
