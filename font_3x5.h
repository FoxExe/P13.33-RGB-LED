#pragma once

#include "Arduino.h"

uint8_t compressedFont[] = {0x00, 0x44, 0x59, 0x99};

/*
 * Font size: 3x5
 * 3x5=15 bits per character, i.e.:
 * 0 8      16 24    32 40    48 56 60
 * 0...14, 15...29, 30...44, 45...59, 
 *   A        B        C        D
 *   0        1        2        3
 * 
 */


// TODO: Skip unused symbols
// 32-47 - Symbols
// 48-57 - Numbers
// 58-64 - Symbols
// 65-90 - English/Uppercase
// 91-98 - Symbols
// 97-122 - English/Lowercase
// 128-159 - Russian/Uppercase
// 160-175 - Russian/Lowercase, part 1
// 224-239 - Russian/Lowercase, part 2
// 240-241 - Russian: "ё, Ё".


uint8_t width = 3;
uint8_t height = 5;

char myChar = 'c';

uint8_t char_lenght = width * height; // 15
int start_bit = myChar * char_lenght; // 30 (C = 2, 2*15 = 30)
int start_byte = start_bit / 8;		  // 3 (30/8 = 3.75)
int start_offset = start_bit % 8;	  // 6 (3*8=24, 30-24=6)

