#pragma once

#include "RGB_Matrix.h"
// For make your font use this tool: https://github.com/FoxExe/Image2Bitmap/releases
// Mode: "BW_1bpp_C" (Black/White, 1 bit per pixel, continues)
// Image: 255 symbols, one symbol per row (5px x 2040px (w/h) for this font, for example)

const uint8_t font_5x6_data[] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x92, 0x94, 0xa4, 0xc6, 0x4a, 0x52, 0x93, 0x08, 0x40, 0x10, 0x84, 0x21, 
	0x00, 0x42, 0x10, 0x84, 0x01, 0x08, 0x42, 0x10, 0x04, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x8a, 0x52, 0x94, 0x42, 0x29, 0x4a, 0x51, 0x10, 0x41, 0x08, 0x88, 0x01, 0x09, 0xf2, 
	0x10, 0x42, 0x74, 0xa4, 0xe1, 0x09, 0xd2, 0x93, 0x88, 0xa5, 0x29, 0x44, 0x41, 0x04, 0x22, 0x20, 
	0x44, 0x42, 0x08, 0x62, 0x10, 0x04, 0x21, 0x08, 0x42, 0x10, 0x04, 0x7f, 0x7a, 0xd2, 0xbe, 0x1c, 
	0x93, 0x85, 0xc0, 0x00, 0x1e, 0x01, 0x08, 0x40, 0x10, 0x84, 0x22, 0x80, 0x00, 0x00, 0x00, 0x52, 
	0x94, 0x44, 0x10, 0x42, 0x22, 0x04, 0x44, 0x20, 0x82, 0x84, 0x21, 0x08, 0x78, 0x00, 0x07, 0x80, 
	0x02, 0x28, 0x00, 0x00, 0x00, 0x64, 0xa4, 0xc4, 0x40, 0x00, 0x00, 0x00, 0x84, 0x21, 0x00, 0x45, 
	0x29, 0x40, 0x02, 0x95, 0xf5, 0x7d, 0x4e, 0x75, 0x1c, 0x57, 0x11, 0x0a, 0x22, 0x84, 0x8a, 0x51, 
	0x14, 0xa2, 0x88, 0x42, 0x00, 0x00, 0x22, 0x10, 0x84, 0x11, 0x04, 0x21, 0x08, 0x80, 0x49, 0x9e, 
	0x64, 0x80, 0x42, 0x7c, 0x84, 0x00, 0x00, 0x03, 0x11, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x23, 
	0x8c, 0x22, 0x22, 0x10, 0x22, 0x94, 0xa5, 0x10, 0x8c, 0x21, 0x08, 0xe6, 0x48, 0x4c, 0x87, 0xbc, 
	0x46, 0x0a, 0x4c, 0x23, 0x29, 0xe2, 0x13, 0xd0, 0xe0, 0xa4, 0xc6, 0x43, 0x92, 0x93, 0x3c, 0x22, 
	0x11, 0x08, 0x64, 0x99, 0x29, 0x31, 0x92, 0x93, 0x84, 0xc0, 0x31, 0x80, 0x63, 0x00, 0x63, 0x00, 
	0xc4, 0x51, 0x10, 0x82, 0x08, 0x00, 0xf0, 0x3c, 0x04, 0x10, 0x42, 0x22, 0x08, 0xa1, 0x10, 0x06, 
	0x4c, 0xeb, 0x59, 0x21, 0xd2, 0x97, 0xa5, 0x2e, 0x4b, 0x92, 0x97, 0x19, 0x28, 0x42, 0x4c, 0xe4, 
	0xa5, 0x29, 0x73, 0xd0, 0xe4, 0x21, 0xef, 0x43, 0x90, 0x84, 0x19, 0x28, 0x5a, 0x4c, 0x94, 0xbd, 
	0x29, 0x49, 0xc4, 0x21, 0x08, 0xe7, 0x10, 0x84, 0xa2, 0x25, 0x4c, 0x52, 0x92, 0x84, 0x21, 0x08, 
	0x7a, 0x5e, 0xf4, 0xa5, 0x29, 0x6b, 0xd6, 0xb4, 0x99, 0x29, 0x4a, 0x4c, 0xe4, 0xa5, 0xc8, 0x41, 
	0x92, 0x96, 0xac, 0xcf, 0x4a, 0x5c, 0x94, 0x99, 0x24, 0x12, 0x4c, 0x71, 0x08, 0x42, 0x12, 0x52, 
	0x94, 0xa4, 0xc9, 0x4a, 0x52, 0x63, 0x25, 0x29, 0x7b, 0xd2, 0x94, 0x98, 0xc9, 0x4a, 0x31, 0x51, 
	0x08, 0x4f, 0x08, 0x88, 0x87, 0x9c, 0x84, 0x21, 0x0e, 0x84, 0x10, 0x41, 0x09, 0xc2, 0x10, 0x84, 
	0xe2, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf1, 0x00, 0x00, 0x00, 0x00, 0x74, 0xa4, 0xe8, 
	0x43, 0x92, 0x97, 0x21, 0x0e, 0x4a, 0x5c, 0x00, 0x0c, 0x84, 0x18, 0x42, 0x74, 0xa4, 0xe0, 0x01, 
	0x96, 0xc3, 0x08, 0xa4, 0x71, 0x08, 0x00, 0x19, 0x27, 0x0b, 0x90, 0xe4, 0xa5, 0x22, 0x01, 0x84, 
	0x23, 0xa1, 0x09, 0x72, 0x52, 0x61, 0x08, 0x42, 0x38, 0x00, 0xd5, 0x6b, 0x50, 0x03, 0x92, 0x94, 
	0x80, 0x06, 0x4a, 0x4c, 0x00, 0x39, 0x2e, 0x42, 0x00, 0x74, 0x9c, 0x21, 0x02, 0x9a, 0x84, 0x00, 
	0x03, 0x30, 0x4c, 0x42, 0x38, 0x85, 0x10, 0x00, 0x94, 0xa4, 0xe0, 0x01, 0x4a, 0x51, 0x00, 0x08, 
	0xd6, 0xaa, 0x00, 0x24, 0xc6, 0x48, 0x00, 0x94, 0x9d, 0x26, 0x03, 0xc4, 0x47, 0x90, 0x4c, 0x11, 
	0x06, 0x21, 0x08, 0x42, 0x70, 0x88, 0x32, 0x09, 0x85, 0x50, 0x00, 0x01, 0x08, 0x40, 0x10, 0x84, 
	0x00, 0x08, 0xa5, 0x7e, 0x20, 0x72, 0x18, 0xa6, 0x01, 0xca, 0x62, 0x9c, 0x07, 0x21, 0x08, 0x40, 
	0x1c, 0xa5, 0x4b, 0xf1, 0x72, 0x1c, 0x87, 0x02, 0xae, 0x23, 0xaa, 0x06, 0x09, 0x82, 0x60, 0x12, 
	0xb6, 0xa5, 0x24, 0x4a, 0xda, 0x94, 0x81, 0x2a, 0x62, 0x92, 0x07, 0x29, 0x4a, 0x90, 0x23, 0xba, 
	0xd6, 0x20, 0x4a, 0x5e, 0x94, 0x81, 0xd1, 0x8c, 0x5c, 0x0f, 0xa9, 0x4a, 0x50, 0x1c, 0x97, 0x21, 
	0x00, 0x3a, 0x10, 0x83, 0x83, 0xe4, 0x21, 0x08, 0x04, 0xa4, 0xc4, 0x40, 0x08, 0xea, 0xd5, 0xc4, 
	0x8a, 0x88, 0xa8, 0x81, 0x29, 0x4a, 0x5e, 0x14, 0xa4, 0xe1, 0x08, 0x2b, 0x5a, 0xd7, 0xe0, 0xad, 
	0x6b, 0x5f, 0x87, 0x08, 0x72, 0x5c, 0x04, 0xa5, 0xab, 0x68, 0x10, 0x87, 0x25, 0xc0, 0x60, 0x9c, 
	0x26, 0x02, 0x55, 0xed, 0x64, 0x03, 0x28, 0xca, 0x50, 0x00, 0xc1, 0x39, 0xc2, 0x33, 0x14, 0xa2, 
	0x00, 0x0e, 0x72, 0x98, 0x00, 0x39, 0x08, 0x40, 0x00, 0xe5, 0x7e, 0x20, 0x01, 0x1c, 0x83, 0x00, 
	0x15, 0x75, 0x6a, 0x00, 0x31, 0xc2, 0x60, 0x00, 0x95, 0xb5, 0x26, 0x02, 0x56, 0xd4, 0x80, 0x0a, 
	0x62, 0x92, 0x00, 0x39, 0x4a, 0x90, 0x00, 0x97, 0xa5, 0x20, 0x02, 0x9c, 0xa5, 0x00, 0x06, 0x4a, 
	0x4c, 0x00, 0x7d, 0x4a, 0x50, 0x01, 0xe0, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x1e, 0x01, 0x08, 
	0x40, 0x10, 0x84, 0x01, 0x09, 0xf2, 0x10, 0x84, 0x01, 0x08, 0x42, 0x10, 0x04, 0x21, 0x00, 0x00, 
	0x38, 0x42, 0x00, 0x00, 0xe1, 0x18, 0x84, 0x01, 0x08, 0x42, 0x10, 0x04, 0x21, 0x00, 0x00, 0x38, 
	0x42, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x38, 0x42, 
	0x84, 0x21, 0x08, 0x78, 0x04, 0x27, 0xc8, 0x47, 0x10, 0x84, 0x21, 0x00, 0x42, 0x7c, 0x84, 0x00, 
	0x01, 0xe0, 0x00, 0x04, 0x27, 0xc8, 0x42, 0x10, 0x04, 0x21, 0x08, 0x40, 0x10, 0x84, 0x84, 0x21, 
	0x08, 0x78, 0x00, 0x03, 0x90, 0xc6, 0x10, 0x04, 0x21, 0x1c, 0x42, 0x10, 0x84, 0x21, 0x00, 0x42, 
	0x10, 0x00, 0xf0, 0x3c, 0x00, 0x10, 0x9f, 0x21, 0x08, 0x40, 0x10, 0x84, 0x21, 0x00, 0x42, 0x11, 
	0xc4, 0x21, 0x08, 0x47, 0x10, 0x84, 0x21, 0x21, 0x08, 0x42, 0x1e, 0x84, 0x21, 0x08, 0x78, 0x00, 
	0x07, 0x80, 0x00, 0x00, 0x0e, 0x42, 0x10, 0x42, 0x7c, 0x84, 0x01, 0x09, 0xf2, 0x10, 0x00, 0x07, 
	0x80, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x01, 0xe0, 0x10, 0x84, 0x01, 0x08, 
	0x42, 0x10, 0x04, 0x21, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0xe4, 0xa5, 0xc8, 0x01, 0x90, 0x83, 
	0x00, 0x1f, 0x21, 0x08, 0x00, 0x25, 0x26, 0x23, 0x08, 0xea, 0xd5, 0xc4, 0x02, 0x4c, 0x64, 0x80, 
	0x09, 0x4a, 0x5e, 0x10, 0x25, 0x27, 0x08, 0x01, 0x5a, 0xd7, 0xe0, 0x05, 0x6b, 0x5f, 0x84, 0x1c, 
	0x31, 0x4c, 0x00, 0x25, 0xab, 0x68, 0x00, 0x86, 0x29, 0x80, 0x03, 0x1c, 0x26, 0x00, 0x12, 0xed, 
	0x64, 0x00, 0x19, 0x46, 0x52, 0x9c, 0x87, 0x21, 0xca, 0x01, 0x9c, 0x83, 0x00, 0xc8, 0x72, 0x0c, 
	0x00, 0x19, 0xc8, 0x32, 0x9c, 0x42, 0x11, 0xca, 0x03, 0x84, 0x21, 0x19, 0x29, 0x31, 0x10, 0x60, 
	0x25, 0x26, 0x22, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x05, 0x29, 
	0x44, 0x05, 0x39, 0x6a, 0xd6, 0xd1, 0x72, 0x9d, 0x52, 0x10, 0x04, 0x21, 0x00, 
};

// width, height, space right, space bottom, font data
Font font_5x6 = {5, 6, 0, 1, font_5x6_data };
