#pragma once

#include "RGB_Matrix.h"

const unsigned char symbols5x8[] PROGMEM =
{
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x3E, 0x5B, 0x4F, 0x5B, 0x3E,
	0x3E, 0x6B, 0x4F, 0x6B, 0x3E,
	0x1C, 0x3E, 0x7C, 0x3E, 0x1C,
	0x18, 0x3C, 0x7E, 0x3C, 0x18,
	0x1C, 0x57, 0x7D, 0x57, 0x1C,
	0x1C, 0x5E, 0x7F, 0x5E, 0x1C,
	0x00, 0x18, 0x3C, 0x18, 0x00,
	0xFF, 0xE7, 0xC3, 0xE7, 0xFF,
	0x00, 0x18, 0x24, 0x18, 0x00,
	0xFF, 0xE7, 0xDB, 0xE7, 0xFF,
	0x30, 0x48, 0x3A, 0x06, 0x0E,
	0x26, 0x29, 0x79, 0x29, 0x26,
	0x40, 0x7F, 0x05, 0x05, 0x07,
	0x40, 0x7F, 0x05, 0x25, 0x3F,
	0x5A, 0x3C, 0xE7, 0x3C, 0x5A,
	0x7F, 0x3E, 0x1C, 0x1C, 0x08,
	0x08, 0x1C, 0x1C, 0x3E, 0x7F,
	0x14, 0x22, 0x7F, 0x22, 0x14,
	0x5F, 0x5F, 0x00, 0x5F, 0x5F,
	0x06, 0x09, 0x7F, 0x01, 0x7F,
	0x00, 0x66, 0x89, 0x95, 0x6A,
	0x60, 0x60, 0x60, 0x60, 0x60,
	0x94, 0xA2, 0xFF, 0xA2, 0x94,
	0x08, 0x04, 0x7E, 0x04, 0x08,
	0x10, 0x20, 0x7E, 0x20, 0x10,
	0x08, 0x08, 0x2A, 0x1C, 0x08,
	0x08, 0x1C, 0x2A, 0x08, 0x08,
	0x1E, 0x10, 0x10, 0x10, 0x10,
	0x0C, 0x1E, 0x0C, 0x1E, 0x0C,
	0x30, 0x38, 0x3E, 0x38, 0x30,
	0x06, 0x0E, 0x3E, 0x0E, 0x06,
	0x00, 0x00, 0x00, 0x00, 0x00,	//   0x20 32
	0x00, 0x00, 0x5F, 0x00, 0x00,	// ! 0x21 33
	0x00, 0x07, 0x00, 0x07, 0x00,	// "
	0x14, 0x7F, 0x14, 0x7F, 0x14,	// #
	0x24, 0x2A, 0x7F, 0x2A, 0x12,	// $
	0x23, 0x13, 0x08, 0x64, 0x62,
	0x36, 0x49, 0x56, 0x20, 0x50,
	0x00, 0x08, 0x07, 0x03, 0x00,
	0x00, 0x1C, 0x22, 0x41, 0x00,
	0x00, 0x41, 0x22, 0x1C, 0x00,
	0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
	0x08, 0x08, 0x3E, 0x08, 0x08,
	0x00, 0x80, 0x70, 0x30, 0x00,
	0x08, 0x08, 0x08, 0x08, 0x08,
	0x00, 0x00, 0x60, 0x60, 0x00,
	0x20, 0x10, 0x08, 0x04, 0x02,
	0x3E, 0x51, 0x49, 0x45, 0x3E,	// 0 0x30 48
	0x00, 0x42, 0x7F, 0x40, 0x00,	// 1
	0x72, 0x49, 0x49, 0x49, 0x46,	// 2
	0x21, 0x41, 0x49, 0x4D, 0x33,	// 3
	0x18, 0x14, 0x12, 0x7F, 0x10,	// 4
	0x27, 0x45, 0x45, 0x45, 0x39,	// 5
	0x3C, 0x4A, 0x49, 0x49, 0x31,	// 6
	0x41, 0x21, 0x11, 0x09, 0x07,	// 7
	0x36, 0x49, 0x49, 0x49, 0x36,	// 8
	0x46, 0x49, 0x49, 0x29, 0x1E,	// 9
	0x00, 0x00, 0x14, 0x00, 0x00,	// :
	0x00, 0x40, 0x34, 0x00, 0x00,	// ;
	0x00, 0x08, 0x14, 0x22, 0x41,	// <
	0x14, 0x14, 0x14, 0x14, 0x14,	// =
	0x00, 0x41, 0x22, 0x14, 0x08,	// >
	0x02, 0x01, 0x59, 0x09, 0x06,	// ?
	0x3E, 0x41, 0x5D, 0x59, 0x4E,
	0x7C, 0x12, 0x11, 0x12, 0x7C,	// A
	0x7F, 0x49, 0x49, 0x49, 0x36,	// B
	0x3E, 0x41, 0x41, 0x41, 0x22,	// C
	0x7F, 0x41, 0x41, 0x41, 0x3E,	// D
	0x7F, 0x49, 0x49, 0x49, 0x41,	// E
	0x7F, 0x09, 0x09, 0x09, 0x01,	// F
	0x3E, 0x41, 0x41, 0x51, 0x73,	// G
	0x7F, 0x08, 0x08, 0x08, 0x7F,	// H
	0x00, 0x41, 0x7F, 0x41, 0x00,	// I
	0x20, 0x40, 0x41, 0x3F, 0x01,	// J
	0x7F, 0x08, 0x14, 0x22, 0x41,	// K
	0x7F, 0x40, 0x40, 0x40, 0x40,	// L
	0x7F, 0x02, 0x1C, 0x02, 0x7F,	// M
	0x7F, 0x04, 0x08, 0x10, 0x7F,	// N
	0x3E, 0x41, 0x41, 0x41, 0x3E,	// O
	0x7F, 0x09, 0x09, 0x09, 0x06,	// P
	0x3E, 0x41, 0x51, 0x21, 0x5E,	// Q
	0x7F, 0x09, 0x19, 0x29, 0x46,	// R
	0x26, 0x49, 0x49, 0x49, 0x32,	// S
	0x03, 0x01, 0x7F, 0x01, 0x03,	// T
	0x3F, 0x40, 0x40, 0x40, 0x3F,	// U
	0x1F, 0x20, 0x40, 0x20, 0x1F,	// V
	0x3F, 0x40, 0x38, 0x40, 0x3F,	// W
	0x63, 0x14, 0x08, 0x14, 0x63,	// X
	0x03, 0x04, 0x78, 0x04, 0x03,	// Y
	0x61, 0x59, 0x49, 0x4D, 0x43,	// Z
	0x00, 0x7F, 0x41, 0x41, 0x41,
	0x02, 0x04, 0x08, 0x10, 0x20,
	0x00, 0x41, 0x41, 0x41, 0x7F,
	0x04, 0x02, 0x01, 0x02, 0x04,
	0x40, 0x40, 0x40, 0x40, 0x40,
	0x00, 0x03, 0x07, 0x08, 0x00,
	0x20, 0x54, 0x54, 0x78, 0x40,
	0x7F, 0x28, 0x44, 0x44, 0x38,
	0x38, 0x44, 0x44, 0x44, 0x28,
	0x38, 0x44, 0x44, 0x28, 0x7F,
	0x38, 0x54, 0x54, 0x54, 0x18,
	0x00, 0x08, 0x7E, 0x09, 0x02,
	0x18, 0xA4, 0xA4, 0x9C, 0x78,
	0x7F, 0x08, 0x04, 0x04, 0x78,
	0x00, 0x44, 0x7D, 0x40, 0x00,
	0x20, 0x40, 0x40, 0x3D, 0x00,
	0x7F, 0x10, 0x28, 0x44, 0x00,
	0x00, 0x41, 0x7F, 0x40, 0x00,
	0x7C, 0x04, 0x78, 0x04, 0x78,
	0x7C, 0x08, 0x04, 0x04, 0x78,
	0x38, 0x44, 0x44, 0x44, 0x38,
	0xFC, 0x18, 0x24, 0x24, 0x18,
	0x18, 0x24, 0x24, 0x18, 0xFC,
	0x7C, 0x08, 0x04, 0x04, 0x08,
	0x48, 0x54, 0x54, 0x54, 0x24,
	0x04, 0x04, 0x3F, 0x44, 0x24,
	0x3C, 0x40, 0x40, 0x20, 0x7C,
	0x1C, 0x20, 0x40, 0x20, 0x1C,
	0x3C, 0x40, 0x30, 0x40, 0x3C,
	0x44, 0x28, 0x10, 0x28, 0x44,
	0x4C, 0x90, 0x90, 0x90, 0x7C,
	0x44, 0x64, 0x54, 0x4C, 0x44,
	0x00, 0x08, 0x36, 0x41, 0x00,
	0x00, 0x00, 0x77, 0x00, 0x00,
	0x00, 0x41, 0x36, 0x08, 0x00,
	0x02, 0x01, 0x02, 0x04, 0x02,
	0x3C, 0x26, 0x23, 0x26, 0x3C,
	0x1E, 0xA1, 0xA1, 0x61, 0x12,
	0x3A, 0x40, 0x40, 0x20, 0x7A,
	0x38, 0x54, 0x54, 0x55, 0x59,
	0x21, 0x55, 0x55, 0x79, 0x41,
	0x21, 0x54, 0x54, 0x78, 0x41,
	0x21, 0x55, 0x54, 0x78, 0x40,
	0x20, 0x54, 0x55, 0x79, 0x40,
	0x0C, 0x1E, 0x52, 0x72, 0x12,
	0x39, 0x55, 0x55, 0x55, 0x59,
	0x39, 0x54, 0x54, 0x54, 0x59,
	0x39, 0x55, 0x54, 0x54, 0x58,
	0x00, 0x00, 0x45, 0x7C, 0x41,
	0x00, 0x02, 0x45, 0x7D, 0x42,
	0x00, 0x01, 0x45, 0x7C, 0x40,
	0xF0, 0x29, 0x24, 0x29, 0xF0,
	0xF0, 0x28, 0x25, 0x28, 0xF0,
	0x7C, 0x54, 0x55, 0x45, 0x00,
	0x20, 0x54, 0x54, 0x7C, 0x54,
	0x7C, 0x0A, 0x09, 0x7F, 0x49,
	0x32, 0x49, 0x49, 0x49, 0x32,
	0x32, 0x48, 0x48, 0x48, 0x32,
	0x32, 0x4A, 0x48, 0x48, 0x30,
	0x3A, 0x41, 0x41, 0x21, 0x7A,
	0x3A, 0x42, 0x40, 0x20, 0x78,
	0x00, 0x9D, 0xA0, 0xA0, 0x7D,
	0x39, 0x44, 0x44, 0x44, 0x39,
	0x3D, 0x40, 0x40, 0x40, 0x3D,
	0x3C, 0x24, 0xFF, 0x24, 0x24,
	0x48, 0x7E, 0x49, 0x43, 0x66,
	0x2B, 0x2F, 0xFC, 0x2F, 0x2B,
	0xFF, 0x09, 0x29, 0xF6, 0x20,
	0xC0, 0x88, 0x7E, 0x09, 0x03,
	0x20, 0x54, 0x54, 0x79, 0x41,
	0x00, 0x00, 0x44, 0x7D, 0x41,
	0x30, 0x48, 0x48, 0x4A, 0x32,
	0x38, 0x40, 0x40, 0x22, 0x7A,
	0x00, 0x7A, 0x0A, 0x0A, 0x72,
	0x7D, 0x0D, 0x19, 0x31, 0x7D,
	0x26, 0x29, 0x29, 0x2F, 0x28,
	0x26, 0x29, 0x29, 0x29, 0x26,
	0x30, 0x48, 0x4D, 0x40, 0x20,
	0x38, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x38,
	0x2F, 0x10, 0xC8, 0xAC, 0xBA,
	0x2F, 0x10, 0x28, 0x34, 0xFA,
	0x00, 0x00, 0x7B, 0x00, 0x00,
	0x08, 0x14, 0x2A, 0x14, 0x22,
	0x22, 0x14, 0x2A, 0x14, 0x08,
	0xAA, 0x00, 0x55, 0x00, 0xAA,
	0xAA, 0x55, 0xAA, 0x55, 0xAA,
	0x00, 0x00, 0x00, 0xFF, 0x00,
	0x10, 0x10, 0x10, 0xFF, 0x00,
	0x14, 0x14, 0x14, 0xFF, 0x00,
	0x10, 0x10, 0xFF, 0x00, 0xFF,
	0x10, 0x10, 0xF0, 0x10, 0xF0,
	0x14, 0x14, 0x14, 0xFC, 0x00,
	0x14, 0x14, 0xF7, 0x00, 0xFF,
	0x00, 0x00, 0xFF, 0x00, 0xFF,
	0x14, 0x14, 0xF4, 0x04, 0xFC,
	0x14, 0x14, 0x17, 0x10, 0x1F,
	0x10, 0x10, 0x1F, 0x10, 0x1F,
	0x14, 0x14, 0x14, 0x1F, 0x00,
	0x10, 0x10, 0x10, 0xF0, 0x00,
	0x00, 0x00, 0x00, 0x1F, 0x10,
	0x10, 0x10, 0x10, 0x1F, 0x10,
	0x10, 0x10, 0x10, 0xF0, 0x10,
	0x00, 0x00, 0x00, 0xFF, 0x10,
	0x10, 0x10, 0x10, 0x10, 0x10,
	0x10, 0x10, 0x10, 0xFF, 0x10,
	0x00, 0x00, 0x00, 0xFF, 0x14,
	0x00, 0x00, 0xFF, 0x00, 0xFF,
	0x00, 0x00, 0x1F, 0x10, 0x17,
	0x00, 0x00, 0xFC, 0x04, 0xF4,
	0x14, 0x14, 0x17, 0x10, 0x17,
	0x14, 0x14, 0xF4, 0x04, 0xF4,
	0x00, 0x00, 0xFF, 0x00, 0xF7,
	0x14, 0x14, 0x14, 0x14, 0x14,
	0x14, 0x14, 0xF7, 0x00, 0xF7,
	0x14, 0x14, 0x14, 0x17, 0x14,
	0x10, 0x10, 0x1F, 0x10, 0x1F,
	0x14, 0x14, 0x14, 0xF4, 0x14,
	0x10, 0x10, 0xF0, 0x10, 0xF0,
	0x00, 0x00, 0x1F, 0x10, 0x1F,
	0x00, 0x00, 0x00, 0x1F, 0x14,
	0x00, 0x00, 0x00, 0xFC, 0x14,
	0x00, 0x00, 0xF0, 0x10, 0xF0,
	0x10, 0x10, 0xFF, 0x10, 0xFF,
	0x14, 0x14, 0x14, 0xFF, 0x14,
	0x10, 0x10, 0x10, 0x1F, 0x00,
	0x00, 0x00, 0x00, 0xF0, 0x10,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xFF, 0xFF, 0xFF, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xFF, 0xFF,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x38, 0x44, 0x44, 0x38, 0x44,
	0x7C, 0x2A, 0x2A, 0x3E, 0x14,
	0x7E, 0x02, 0x02, 0x06, 0x06,
	0x02, 0x7E, 0x02, 0x7E, 0x02,
	0x63, 0x55, 0x49, 0x41, 0x63,
	0x38, 0x44, 0x44, 0x3C, 0x04,
	0x40, 0x7E, 0x20, 0x1E, 0x20,
	0x06, 0x02, 0x7E, 0x02, 0x02,
	0x99, 0xA5, 0xE7, 0xA5, 0x99,
	0x1C, 0x2A, 0x49, 0x2A, 0x1C,
	0x4C, 0x72, 0x01, 0x72, 0x4C,
	0x30, 0x4A, 0x4D, 0x4D, 0x30,
	0x30, 0x48, 0x78, 0x48, 0x30,
	0xBC, 0x62, 0x5A, 0x46, 0x3D,
	0x3E, 0x49, 0x49, 0x49, 0x00,
	0x7E, 0x01, 0x01, 0x01, 0x7E,
	0x2A, 0x2A, 0x2A, 0x2A, 0x2A,
	0x44, 0x44, 0x5F, 0x44, 0x44,
	0x40, 0x51, 0x4A, 0x44, 0x40,
	0x40, 0x44, 0x4A, 0x51, 0x40,
	0x00, 0x00, 0xFF, 0x01, 0x03,
	0xE0, 0x80, 0xFF, 0x00, 0x00,
	0x08, 0x08, 0x6B, 0x6B, 0x08,
	0x36, 0x12, 0x36, 0x24, 0x36,
	0x06, 0x0F, 0x09, 0x0F, 0x06,
	0x00, 0x00, 0x18, 0x18, 0x00,
	0x00, 0x00, 0x10, 0x10, 0x00,
	0x30, 0x40, 0xFF, 0x01, 0x01,
	0x00, 0x1F, 0x01, 0x01, 0x1E,
	0x00, 0x19, 0x1D, 0x17, 0x12,
	0x00, 0x3C, 0x3C, 0x3C, 0x3C,
	0x00, 0x00, 0x00, 0x00, 0x00,
};

Font font5x8 = { 5, 8, symbols5x8 };

const unsigned char symbols4x6[] PROGMEM = 
{
	0x21, 0x23, 0x23, 0x1E, 0x21, 0x2B, 0xA5, 0x1E, 0x01, 0x01, 0x81, 0x01, 0x1B, 0x1C, 0x3A, 0x11,
	0xCE, 0xDF, 0x4E, 0xC0, 0x1A, 0xDA, 0xFC, 0x20, 0x1F, 0x08, 0x1D, 0x00, 0x10, 0x13, 0x0F, 0x00,
	0x88, 0xCF, 0x8F, 0x08, 0x14, 0xE1, 0x2A, 0x0C, 0x00, 0x20, 0x80, 0x0C, 0x80, 0x0D, 0x03, 0x08,
	0x00, 0x00, 0x00, 0x0C, 0x00, 0x01, 0x00, 0x0C, 0x2C, 0x24, 0x24, 0x08, 0x2C, 0x24, 0x24, 0x08,
	0x0B, 0x09, 0x09, 0x02, 0x00, 0x70, 0x00, 0x02, 0x30, 0x00, 0x30, 0x02, 0xF0, 0xA8, 0xF8, 0x02,
	0xA1, 0xF7, 0x50, 0x07, 0x9B, 0x48, 0x2F, 0x00, 0xF0, 0x78, 0xC8, 0x02, 0x03, 0x30, 0x00, 0x03,
	0x00, 0xE7, 0x10, 0x00, 0x12, 0xE7, 0x02, 0x00, 0x51, 0x21, 0x53, 0x00, 0x43, 0xE1, 0x41, 0x00,
	0x03, 0x80, 0x00, 0x03, 0x40, 0x42, 0x41, 0x02, 0x00, 0x02, 0x01, 0x02, 0x80, 0x42, 0x31, 0x02,
	0x78, 0x44, 0x3C, 0x00, 0x08, 0x7D, 0x00, 0x00, 0x64, 0x54, 0x48, 0x00, 0x45, 0x54, 0x29, 0x00,
	0x1C, 0x11, 0x7C, 0x00, 0x5C, 0x54, 0x25, 0x00, 0x78, 0x55, 0x75, 0x00, 0x64, 0x14, 0x0C, 0x00,
	0x7C, 0x54, 0x7D, 0x00, 0x5D, 0x54, 0x3C, 0x00, 0x00, 0x28, 0x00, 0x00, 0x40, 0x28, 0x00, 0x00,
	0x11, 0x28, 0x44, 0x00, 0x28, 0x28, 0x28, 0x00, 0x44, 0x29, 0x10, 0x00, 0x05, 0x54, 0x0C, 0x00,
	0xCE, 0x55, 0x96, 0x00, 0x9E, 0x45, 0x9E, 0x00, 0xDF, 0x55, 0x8A, 0x00, 0x8E, 0x51, 0x51, 0x00,
	0x5F, 0xD1, 0x4E, 0x00, 0xDF, 0x15, 0xD5, 0x00, 0xDF, 0x05, 0xC5, 0x00, 0xCE, 0x15, 0xDD, 0x00,
	0xDF, 0x04, 0xDF, 0x00, 0xD1, 0x1F, 0xD1, 0x00, 0x48, 0x50, 0xCF, 0x00, 0xDF, 0x44, 0x5B, 0x00,
	0x9F, 0x10, 0x10, 0x00, 0x5F, 0x46, 0xDF, 0x00, 0x9F, 0x4E, 0x9F, 0x00, 0x0E, 0x11, 0x0E, 0x00,
	0x17, 0x21, 0x00, 0x00, 0xA3, 0x66, 0xC7, 0x00, 0xF7, 0x23, 0xC5, 0x00, 0xC4, 0x25, 0x22, 0x00,
	0xC0, 0x27, 0xF0, 0x00, 0xC3, 0xA4, 0x67, 0x00, 0x41, 0xE6, 0x51, 0x00, 0xC7, 0xA3, 0xE7, 0x00,
	0xF6, 0x21, 0xC6, 0x00, 0x00, 0xD7, 0x00, 0x00, 0x06, 0x05, 0xD4, 0x00, 0xF7, 0xC4, 0x24, 0x00,
	0x10, 0xF1, 0x02, 0x00, 0xE4, 0xE4, 0xE7, 0x00, 0xE0, 0x20, 0xC0, 0x00, 0xC4, 0x24, 0xC4, 0x00,
	0xF8, 0x48, 0x30, 0x00, 0x31, 0x49, 0xF9, 0x00, 0x71, 0x09, 0x08, 0x00, 0x50, 0x79, 0x29, 0x00,
	0x08, 0x7D, 0x49, 0x00, 0x38, 0x41, 0x79, 0x00, 0x38, 0x61, 0x38, 0x00, 0x78, 0x72, 0x79, 0x00,
	0x49, 0x30, 0x49, 0x00, 0x18, 0xA1, 0x78, 0x00, 0x69, 0x7A, 0x59, 0x00, 0x11, 0x6C, 0x45, 0x00,
	0x01, 0x6D, 0x01, 0x00, 0x45, 0x6C, 0x11, 0x00, 0x09, 0x0C, 0x05, 0x00, 0x7C, 0x7D, 0x7C, 0x00,
	0x8F, 0xF1, 0x89, 0x00, 0x9F, 0x90, 0x9F, 0x00, 0x9E, 0x5A, 0xDF, 0x00, 0xDB, 0xDB, 0xDD, 0x00,
	0xDB, 0x9A, 0xDD, 0x00, 0x9A, 0xDB, 0x9C, 0x00, 0x5A, 0x5B, 0x1C, 0x00, 0xEE, 0x12, 0x82, 0x00,
	0xDF, 0x1B, 0xDF, 0x00, 0xDF, 0x1A, 0xDF, 0x00, 0xDE, 0x1B, 0xDE, 0x00, 0x81, 0xDE, 0x91, 0x00,
	0x81, 0x5F, 0x91, 0x00, 0x40, 0x9D, 0xD0, 0x00, 0x1F, 0x88, 0x1F, 0x00, 0x1E, 0x8B, 0x9E, 0x00,
	0xA7, 0xB6, 0xC4, 0x00, 0x06, 0xC7, 0x16, 0x00, 0xE7, 0x21, 0xF7, 0x00, 0xE7, 0x14, 0xE7, 0x00,
	0xD7, 0x54, 0xD7, 0x00, 0xD7, 0x94, 0xD7, 0x00, 0x27, 0x54, 0x77, 0x00, 0x27, 0x54, 0x27, 0x00,
	0x0B, 0xF8, 0x0F, 0x00, 0x03, 0xA4, 0x43, 0x40, 0x47, 0x44, 0xC7, 0x00, 0x73, 0xCC, 0x60, 0x90,
	0x77, 0xC5, 0xA4, 0x10, 0x01, 0xFF, 0x81, 0x00, 0xE4, 0x0A, 0xE9, 0x01, 0xAA, 0x4F, 0xA2, 0x40,
	0x79, 0x15, 0x79, 0x00, 0x78, 0x55, 0x25, 0x00, 0x7D, 0x55, 0x29, 0x00, 0x7D, 0x05, 0x05, 0x00,
	0x61, 0x3C, 0x7D, 0x00, 0x7D, 0x54, 0x45, 0x00, 0x7C, 0x54, 0x44, 0x00, 0x6C, 0x7C, 0x6C, 0x00,
	0x44, 0x55, 0x29, 0x00, 0x7D, 0x22, 0x7E, 0x00, 0x7C, 0x20, 0x50, 0x00, 0x79, 0x04, 0x7F, 0x02,
	0x7D, 0x19, 0x7F, 0x01, 0x7C, 0x11, 0x7C, 0x00, 0x38, 0x44, 0x38, 0x00, 0x7C, 0x04, 0x7C, 0x00,
	0x1F, 0xC5, 0x02, 0x00, 0x0E, 0x11, 0x11, 0x00, 0x41, 0xDF, 0x01, 0x00, 0x01, 0x82, 0x5F, 0x00,
	0x03, 0x1F, 0x03, 0x00, 0x11, 0xCE, 0x11, 0x00, 0x1F, 0xD0, 0x1F, 0x00, 0x03, 0xC4, 0x1F, 0x00,
	0x9F, 0xDF, 0x9F, 0x80, 0x1F, 0xDF, 0x1F, 0x00, 0x01, 0x1F, 0x18, 0x00, 0xDF, 0xD8, 0xDF, 0xC0,
	0x5F, 0xD8, 0x40, 0x00, 0x51, 0xD5, 0x4E, 0x00, 0x9F, 0xCC, 0x9F, 0x00, 0xD2, 0xCD, 0xDF, 0x00,
	0x10, 0x0C, 0x00, 0x10, 0xF0, 0x50, 0xA0, 0x00, 0x02, 0xF2, 0x81, 0x80, 0x40, 0x40, 0x40, 0x00,
	0x00, 0x88, 0x24, 0xE0, 0x00, 0x03, 0x02, 0x00, 0xE7, 0x00, 0xE7, 0x00, 0x17, 0x10, 0x17, 0x10,
	0x02, 0x8F, 0x82, 0x82, 0x02, 0xB3, 0x50, 0xE0, 0x80, 0xFE, 0x02, 0x02, 0xEF, 0x4F, 0xEF, 0x4F,
	0xA7, 0xF0, 0xA7, 0x00, 0x87, 0x80, 0x87, 0x80, 0x17, 0x96, 0xB6, 0xE0, 0xF7, 0x76, 0x56, 0xE0,
	0x70, 0xCC, 0x38, 0x70, 0x49, 0x7C, 0x49, 0x00, 0x64, 0x5B, 0x00, 0x00, 0x48, 0x74, 0x00, 0x00,
	0x00, 0xF8, 0x00, 0x00, 0x02, 0x3E, 0x02, 0x02, 0x13, 0x11, 0x11, 0x00, 0x08, 0x50, 0x08, 0x00,
	0x08, 0x17, 0x0B, 0x00, 0x01, 0x32, 0x02, 0x00, 0x00, 0x10, 0x00, 0x00, 0x20, 0x7C, 0x04, 0x04,
	0x02, 0x3B, 0x02, 0x02, 0x24, 0x3C, 0x20, 0x00, 0x02, 0x3A, 0x3A, 0x01, 0xF3, 0x93, 0x7F, 0x1D,
	0xB0, 0x1F, 0xC3, 0x03, 0xDF, 0xDA, 0x9B, 0x00, 0xC0, 0xDF, 0xD2, 0x00, 0x00, 0x5E, 0x93, 0x00,
	0xC0, 0xDF, 0xD3, 0x00, 0x81, 0x9E, 0x93, 0x00, 0x9F, 0x55, 0x8E, 0x00, 0xCC, 0x92, 0x8D, 0x00,
	0xCC, 0xD3, 0xCC, 0x00, 0xCD, 0xD3, 0x4D, 0x00, 0xCD, 0x93, 0xCD, 0x00, 0xCA, 0x84, 0x4A, 0x00,
	0x9F, 0x55, 0x9F, 0x00, 0x9F, 0x90, 0xDE, 0x00, 0x9E, 0xD1, 0x1E, 0x00, 0xDD, 0xD1, 0xDD, 0x00,
	0xF1, 0x36, 0x47, 0x00, 0xE7, 0x36, 0x63, 0x00, 0xE6, 0x36, 0x47, 0x00, 0xF7, 0x25, 0x73, 0x00,
	0xD7, 0x24, 0x77, 0x00, 0xF7, 0x26, 0xF7, 0x00, 0xCB, 0x58, 0xFF, 0x00, 0xCF, 0x48, 0xF3, 0x00,
	0xF7, 0xB2, 0x27, 0x00, 0xF6, 0xB6, 0xC7, 0x00, 0xE7, 0xB2, 0x27, 0x00, 0xE6, 0xB6, 0xC7, 0x00,
	0xF3, 0x55, 0x1B, 0x00, 0xE7, 0xA4, 0xC5, 0x00, 0xF7, 0xA4, 0x31, 0x00, 0xF7, 0xA4, 0xD5, 0x00,
	0x71, 0x8D, 0xDC, 0x00, 0xB1, 0x95, 0x71, 0x00, 0x7D, 0x41, 0x6C, 0x00, 0xBD, 0x89, 0x7D, 0x00,
	0x70, 0x8D, 0xD9, 0x00, 0xB1, 0x91, 0x71, 0x00, 0xB9, 0xC5, 0x35, 0x00, 0xB1, 0x9D, 0x71, 0x00,
	0x71, 0x25, 0x71, 0x00, 0x7D, 0x11, 0x7C, 0x00, 0x7D, 0x29, 0x71, 0x00, 0x4D, 0x7D, 0x04, 0x00,
	0x55, 0x77, 0x07, 0x00, 0x4D, 0x7F, 0x02, 0x00, 0x51, 0x71, 0x01, 0x00, 0x05, 0xFD, 0x80, 0x00,
	0x82, 0xBF, 0xE0, 0x00, 0x80, 0x1F, 0x92, 0x00, 0x80, 0x9E, 0x90, 0x00, 0xB0, 0x21, 0xDD, 0x00,
	0xDE, 0x92, 0xDF, 0x00, 0xDC, 0xD6, 0xC8, 0x00, 0x9E, 0x88, 0x96, 0x00, 0xDF, 0xD0, 0xD1, 0x00,
	0x1F, 0x10, 0x01, 0x00, 0xEF, 0xB1, 0xC8, 0x00, 0xA1, 0x1F, 0x80, 0x00, 0x9F, 0x91, 0x11, 0x00,
	0x1F, 0x11, 0x01, 0x00, 0x9F, 0x96, 0xD0, 0x00, 0x90, 0x5F, 0x92, 0x00, 0xEF, 0xF1, 0xC8, 0x00,
	0xE7, 0x60, 0xE7, 0x00, 0xFB, 0xBF, 0xE3, 0x00, 0xFB, 0x5C, 0x23, 0x00, 0xE7, 0xA3, 0xB7, 0x00,
	0x47, 0xA0, 0xB7, 0x00, 0x77, 0x94, 0x37, 0x00, 0xF3, 0xB5, 0x27, 0x00, 0xB7, 0x74, 0xD7, 0x00,
	0x67, 0x45, 0xC2, 0x00, 0x77, 0xA4, 0x37, 0x00, 0x77, 0xA5, 0x32, 0x00, 0x1F, 0xF7, 0x1A, 0x00,
	0x0F, 0xF6, 0x09, 0x00, 0x37, 0xE2, 0x37, 0x00, 0x57, 0xE1, 0x50, 0x00, 0xDB, 0xFC, 0x33, 0x00,
	0x0A, 0x7D, 0x48, 0x00, 0x75, 0x44, 0x75, 0x00, 0x75, 0x44, 0x74, 0x00, 0x7D, 0x45, 0x79, 0x00,
	0x7D, 0x45, 0x79, 0x00, 0x75, 0x41, 0x74, 0x00, 0x75, 0x41, 0x74, 0x00, 0x78, 0x4F, 0x78, 0x00,
	0x72, 0x4D, 0x70, 0x00, 0x7D, 0x41, 0x7D, 0x00, 0x75, 0x41, 0x75, 0x00, 0x3C, 0xC2, 0xBC, 0x00,
	0x38, 0xC3, 0xBA, 0x00, 0x1C, 0xE1, 0xBC, 0x00, 0x48, 0x69, 0x5D, 0x00, 0x50, 0x51, 0x74, 0x00,
	0xD2, 0x59, 0x96, 0x00, 0xD4, 0x5C, 0xD4, 0x00, 0xD3, 0x1A, 0xD7, 0x00, 0xD5, 0x54, 0x5D, 0x00,
	0x81, 0x41, 0xC0, 0x00, 0xC1, 0xC0, 0xC1, 0x00, 0x00, 0x41, 0xC0, 0x00, 0xC0, 0x30, 0xE0, 0x00,
	0xC2, 0x42, 0xC2, 0x00, 0x81, 0x40, 0xC1, 0x00, 0xC1, 0x0F, 0xFD, 0x00, 0xDE, 0x01, 0xC0, 0x00,
	0xDF, 0x15, 0xD5, 0x00, 0xDE, 0xC1, 0xD7, 0x00, 0xDF, 0xDF, 0xD6, 0x00, 0x41, 0xDF, 0x1D, 0x00,
	0xF7, 0xC1, 0x06, 0x00, 0xF5, 0x65, 0x87, 0x00, 0x57, 0x5C, 0xF7, 0x00, 0x47, 0xF5, 0xF7, 0x00,
	0x7F, 0xD4, 0xFF, 0x00, 0xE6, 0x47, 0x96, 0x00, 0xE4, 0xA5, 0xE7, 0x00, 0xE7, 0x23, 0x27, 0x00,
	0xC7, 0x23, 0xE7, 0x00, 0x67, 0xE0, 0x67, 0x00, 0x65, 0xA5, 0xE7, 0x00, 0xE7, 0x84, 0xEF, 0x00,
	0xE1, 0x91, 0xE7, 0x00, 0xE7, 0x87, 0x67, 0x00, 0xC7, 0x67, 0xEF, 0x00, 0xE0, 0x87, 0xE7, 0x00,
	0x79, 0x11, 0x78, 0x00, 0x79, 0x09, 0x78, 0x00, 0x09, 0x79, 0x09, 0x00, 0x38, 0xFD, 0x39, 0x00,
	0x79, 0x40, 0x79, 0xC0, 0x39, 0x21, 0x78, 0x00, 0x79, 0x79, 0x79, 0x00, 0x79, 0x78, 0xF8, 0x00,
	0x0B, 0x79, 0x63, 0x00, 0x79, 0x61, 0x01, 0x00, 0x79, 0x61, 0x61, 0x00, 0x59, 0x68, 0x79, 0x00,
	0x21, 0x78, 0x79, 0x00, 0x79, 0x28, 0x79, 0x00, 0x09, 0x38, 0xE9, 0x00, 0x79, 0x08, 0x0D, 0x00,
	0x9E, 0x1A, 0x96, 0x00, 0x9C, 0x82, 0x9E, 0x00, 0x1E, 0x1E, 0x98, 0x00, 0x02, 0x1E, 0x9A, 0x00,
	0x1F, 0x09, 0x96, 0x00, 0x7F, 0x28, 0xBF, 0x00, 0x9E, 0x30, 0x9E, 0x00, 0x9E, 0x80, 0x81, 0x00,
	0x1E, 0x02, 0x83, 0x00, 0x1E, 0x0C, 0x9E, 0x00, 0x90, 0x10, 0x9E, 0x00, 0x90, 0x08, 0x9E, 0x00,
	0x80, 0x00, 0x9E, 0x00, 0x98, 0x00, 0x9E, 0x00, 0x80, 0x1E, 0x80, 0x00, 0x00, 0x96, 0x88, 0x00,
	0xC7, 0x00, 0xE7, 0x00, 0x07, 0x05, 0xE3, 0x00, 0xE0, 0xE2, 0xE1, 0x00, 0xE0, 0x00, 0xEF, 0x00,
	0x04, 0x84, 0x07, 0x00, 0x00, 0x64, 0x03, 0x00, 0x07, 0x44, 0x07, 0x00, 0x07, 0x44, 0xA7, 0x00,
	0x00, 0x1F, 0xF8, 0x00, 0x04, 0x34, 0x07, 0x00, 0x07, 0x44, 0x03, 0x00, 0x07, 0x84, 0x57, 0x00,
	0x03, 0xF0, 0x0F, 0x00, 0x07, 0xA4, 0xD7, 0x00, 0x0F, 0x3A, 0x53, 0x00, 0x04, 0xC5, 0x67, 0x00,
	0x03, 0x08, 0x04, 0x00, 0x00, 0x14, 0x01, 0x00, 0x01, 0xC1, 0x41, 0x00, 0x21, 0x20, 0x21, 0x00,
	0x00, 0x18, 0x00, 0x00, 0x10, 0x18, 0x00, 0x00, 0x80, 0xC0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00,
	0x0C, 0x00, 0x0C, 0x00, 0x18, 0x00, 0x18, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0x1A, 0x02, 0x19, 0x00,
	0x20, 0x58, 0x00, 0x00, 0x00, 0x58, 0x20, 0x00, 0x78, 0x7C, 0x04, 0x00, 0x70, 0x4B, 0x71, 0x00,
};

Font font4x6 = { 4, 6, symbols4x6 };
