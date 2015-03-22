#include <sl_def.h>


	Uint16	FntXsize;
	Uint16	FntYsize;
	Uint8	FntContry;
	Uint8	FntBitPat[8] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};

void  FNT_SetBuffSize(Uint16 x,Uint16 y,Uint8 contry)
{
	FntXsize  = x;
	FntYsize  = y;
	FntContry = contry;
}

//extern	Uint8	FntEouFontData[]; 

/*
Uint8	FntAsciiFontData[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x10,0x10,0x00,
	0x00,0x00,0x24,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x44,0x44,0xfe,0x44,0x44,0x44,0x44,0x44,0x44,0xfe,0x44,0x44,0x00,0x00,
	0x00,0x00,0x10,0x10,0x7c,0x92,0x90,0x90,0x7c,0x12,0x12,0x92,0x7c,0x10,0x10,0x00,
	0x00,0x00,0x00,0x60,0x90,0x92,0x64,0x08,0x10,0x20,0x4c,0x92,0x12,0x0c,0x00,0x00,
	0x00,0x00,0x18,0x24,0x24,0x24,0x18,0x30,0x53,0x52,0x8a,0x8a,0x44,0x46,0x39,0x00,
	0x00,0x00,0x10,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x04,0x08,0x08,0x10,0x10,0x30,0x20,0x20,0x30,0x10,0x10,0x08,0x08,0x04,0x00,
	0x00,0x20,0x10,0x10,0x08,0x08,0x0c,0x04,0x04,0x0c,0x08,0x08,0x10,0x10,0x20,0x00,
	0x00,0x00,0x00,0x00,0x10,0x92,0x54,0x38,0x10,0x38,0x54,0x92,0x10,0x00,0x00,0x00,
	0x00,0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x7c,0x10,0x10,0x10,0x10,0x10,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x18,0x08,0x10,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,
	0x00,0x02,0x02,0x02,0x04,0x04,0x08,0x08,0x10,0x10,0x20,0x20,0x40,0x40,0x40,0x00,
	0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,
	0x00,0x10,0x30,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,
	0x00,0x18,0x24,0x42,0x42,0x02,0x04,0x04,0x08,0x10,0x20,0x20,0x40,0x40,0x7e,0x00,
	0x00,0x18,0x24,0x42,0x42,0x02,0x04,0x18,0x04,0x02,0x02,0x42,0x42,0x24,0x18,0x00,
	0x00,0x0c,0x14,0x14,0x24,0x24,0x44,0x44,0x44,0x44,0x7e,0x04,0x04,0x04,0x0e,0x00,
	0x00,0x7e,0x40,0x40,0x40,0x40,0x58,0x64,0x42,0x02,0x02,0x42,0x42,0x24,0x18,0x00,
	0x00,0x18,0x24,0x42,0x42,0x40,0x58,0x64,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,
	0x00,0x7e,0x42,0x42,0x42,0x04,0x04,0x08,0x08,0x10,0x10,0x20,0x20,0x40,0x40,0x00,
	0x00,0x18,0x24,0x42,0x42,0x42,0x24,0x18,0x24,0x42,0x42,0x42,0x42,0x24,0x18,0x00,
	0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x26,0x1a,0x02,0x02,0x42,0x42,0x24,0x18,0x00,
	0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,
	0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x08,0x08,0x10,0x00,
	0x00,0x00,0x00,0x02,0x04,0x08,0x10,0x20,0x40,0x20,0x10,0x08,0x04,0x02,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0x00,0x00,0x7e,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x40,0x20,0x10,0x08,0x04,0x02,0x04,0x08,0x10,0x20,0x40,0x00,0x00,
	0x00,0x18,0x24,0x42,0x42,0x02,0x04,0x08,0x10,0x10,0x10,0x00,0x00,0x10,0x10,0x00,
	0x00,0x38,0x44,0x82,0x92,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0x94,0x80,0x40,0x3c,0x00,
	0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x7e,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x00,
	0x00,0x78,0x44,0x42,0x42,0x42,0x44,0x78,0x44,0x42,0x42,0x42,0x42,0x44,0x78,0x00,
	0x00,0x18,0x24,0x42,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x42,0x24,0x18,0x00,
	0x00,0x78,0x44,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x44,0x78,0x00,
	0x00,0x7e,0x40,0x40,0x40,0x40,0x40,0x7c,0x40,0x40,0x40,0x40,0x40,0x40,0x7e,0x00,
	0x00,0x7e,0x40,0x40,0x40,0x40,0x40,0x7c,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,
	0x00,0x18,0x24,0x42,0x40,0x40,0x40,0x5e,0x42,0x42,0x42,0x42,0x42,0x26,0x1a,0x00,
	0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x7e,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x00,
	0x00,0x38,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,
	0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x42,0x24,0x18,0x00,
	0x00,0x42,0x44,0x44,0x48,0x48,0x50,0x60,0x50,0x48,0x48,0x44,0x44,0x42,0x42,0x00,
	0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7e,0x00,
	0x00,0x42,0x42,0x66,0x66,0x5a,0x5a,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x00,
	0x00,0x42,0x42,0x62,0x62,0x52,0x52,0x4a,0x4a,0x46,0x46,0x42,0x42,0x42,0x42,0x00,
	0x00,0x3c,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3c,0x00,
	0x00,0x78,0x44,0x42,0x42,0x42,0x44,0x78,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,
	0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x5a,0x66,0x26,0x19,0x00,
	0x00,0x78,0x44,0x42,0x42,0x42,0x44,0x78,0x50,0x48,0x48,0x44,0x44,0x42,0x42,0x00,
	0x00,0x18,0x24,0x42,0x40,0x40,0x20,0x10,0x08,0x04,0x02,0x02,0x42,0x24,0x18,0x00,
	0x00,0x7c,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,
	0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,
	0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x24,0x18,0x18,0x00,
	0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x5a,0x5a,0x5a,0x24,0x24,0x24,0x00,
	0x00,0x42,0x42,0x42,0x24,0x24,0x24,0x18,0x18,0x24,0x24,0x24,0x42,0x42,0x42,0x00,
	0x00,0x82,0x82,0x44,0x44,0x28,0x28,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,
	0x00,0x7e,0x02,0x02,0x04,0x04,0x08,0x08,0x10,0x10,0x20,0x20,0x40,0x40,0x7e,0x00,
	0x00,0x3c,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3c,0x00,
	0x00,0x40,0x40,0x40,0x20,0x20,0x10,0x10,0x08,0x08,0x04,0x04,0x02,0x02,0x02,0x00,
	0x00,0x3c,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x3c,0x00,
	0x00,0x10,0x28,0x44,0x82,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0x00,
	0x00,0x00,0x18,0x18,0x18,0x10,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x84,0x04,0x74,0x8c,0x84,0x8c,0x72,0x00,
	0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x58,0x64,0x42,0x42,0x42,0x42,0x64,0x58,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1c,0x22,0x40,0x40,0x40,0x40,0x22,0x1c,0x00,
	0x00,0x00,0x04,0x04,0x04,0x04,0x04,0x34,0x4c,0x84,0x84,0x84,0x84,0x4c,0x34,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x44,0x82,0xfe,0x80,0x80,0x42,0x3c,0x00,
	0x00,0x00,0x0c,0x12,0x10,0x10,0x10,0x7c,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x3a,0x46,0x82,0x82,0x82,0x46,0x3a,0x02,0x44,0x38,
	0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x58,0x64,0x42,0x42,0x42,0x42,0x42,0x42,0x00,
	0x00,0x00,0x00,0x10,0x10,0x00,0x00,0x30,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,
	0x00,0x00,0x08,0x08,0x00,0x00,0x18,0x08,0x08,0x08,0x08,0x08,0x08,0x48,0x48,0x30,
	0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x42,0x44,0x48,0x50,0x70,0x48,0x44,0x42,0x00,
	0x00,0x00,0x30,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xec,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5c,0x62,0x42,0x42,0x42,0x42,0x42,0x42,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x44,0x38,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x58,0x64,0x42,0x42,0x42,0x64,0x58,0x40,0x40,0x40,
	0x00,0x00,0x00,0x00,0x00,0x00,0x1a,0x26,0x42,0x42,0x42,0x26,0x1a,0x02,0x02,0x02,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2c,0x32,0x20,0x20,0x20,0x20,0x20,0x20,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x40,0x30,0x0c,0x02,0x42,0x3c,0x00,
	0x00,0x00,0x00,0x00,0x20,0x20,0x20,0x78,0x20,0x20,0x20,0x20,0x20,0x24,0x18,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x46,0x3a,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x82,0x82,0x82,0x82,0x82,0x44,0x28,0x10,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x82,0x82,0x82,0x92,0x92,0xaa,0x44,0x44,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x82,0x44,0x28,0x10,0x10,0x28,0x44,0x82,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x42,0x42,0x42,0x42,0x42,0x22,0x14,0x08,0x10,0x60,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0x02,0x04,0x08,0x10,0x20,0x40,0x7e,0x00,
	0x00,0x0c,0x10,0x10,0x10,0x10,0x10,0x20,0x20,0x10,0x10,0x10,0x10,0x10,0x0c,0x00,
	0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x00,
	0x00,0x30,0x08,0x08,0x08,0x08,0x08,0x04,0x04,0x08,0x08,0x08,0x08,0x08,0x30,0x00,
	0x00,0x60,0x92,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
*/


Uint8	FntAsciiFontData2bpp[] = {
// Tile number 0x000
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x001
, 0x0F,0x00,0x3F,0xC0,0x3F,0xD0,0x3F,0x50,0x0F,0x40,0x01,0x40,0x0F,0x00,0x01,0x40
// Tile number 0x002
, 0x00,0x00,0xF0,0xF0,0xF4,0xF4,0xD4,0xD4,0x50,0x50,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x004
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x005
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x006
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x007
, 0x00,0x00,0x0F,0x00,0x0F,0x40,0x0D,0x40,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x008
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x009
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x00A
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x00B
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x00C
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x00D
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xC0,0x03,0xD0,0x00,0x50
// Tile number 0x00E
, 0x00,0x00,0x00,0x00,0x3F,0xFC,0x3F,0xFD,0x05,0x55,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x00F
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xC0,0x03,0xD0,0x00,0x50
// Tile number 0x010
, 0x00,0x00,0x00,0x0C,0x00,0x34,0x00,0xD0,0x03,0x40,0x0D,0x00,0x34,0x00,0x10,0x00
// Tile number 0x011
, 0x00,0x00,0x3F,0xF0,0xF5,0x7C,0xF4,0x3D,0xF4,0x3D,0xF4,0x3D,0x3F,0xF5,0x05,0x54
// Tile number 0x012
, 0x00,0x00,0x03,0xC0,0x0F,0xD0,0x03,0xD0,0x03,0xD0,0x03,0xD0,0x3F,0xFC,0x05,0x55
// Tile number 0x013
, 0x00,0x00,0x3F,0xF0,0xF5,0x7C,0x17,0xFD,0x3F,0xD5,0xFD,0x50,0xFF,0xFC,0x15,0x55
// Tile number 0x014
, 0x00,0x00,0x3F,0xFC,0x05,0xD5,0x0F,0xF0,0x01,0x7C,0xF0,0x3D,0x3F,0xF5,0x05,0x54
// Tile number 0x015
, 0x00,0x00,0x00,0xF0,0x03,0xF4,0x0F,0x74,0x3D,0x34,0x3F,0xFC,0x05,0xF5,0x00,0x14
// Tile number 0x016
, 0x00,0x00,0xFF,0xF0,0xF5,0x54,0xFF,0xF0,0x15,0x7C,0xF0,0x3D,0x3F,0xF5,0x05,0x54
// Tile number 0x017
, 0x00,0x00,0x3F,0xF0,0xF5,0x54,0xFF,0xF0,0xF5,0x7C,0xF4,0x3D,0x3F,0xF5,0x05,0x54
// Tile number 0x018
, 0x00,0x00,0xFF,0xFC,0xF5,0x7D,0x14,0xF5,0x03,0xD4,0x0F,0x50,0x0F,0x40,0x01,0x40
// Tile number 0x019
, 0x00,0x00,0x3F,0xF0,0xF5,0x7C,0x3F,0xF5,0xF5,0x7C,0xF4,0x3D,0x3F,0xF5,0x05,0x54
// Tile number 0x01A
, 0x00,0x00,0x3F,0xF0,0xF5,0x7C,0xF4,0x3D,0x3F,0xFD,0x05,0x7D,0x3F,0xF5,0x05,0x54
// Tile number 0x01B
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x01C
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x01D
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x01E
, 0x00,0x00,0x3F,0xFC,0x3F,0xFD,0x05,0x55,0x3F,0xFC,0x3F,0xFD,0x05,0x55,0x00,0x00
// Tile number 0x01F
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x020
, 0x0F,0xF0,0x3D,0x7C,0x35,0x3D,0x04,0xF5,0x03,0xD4,0x00,0x50,0x03,0xD0,0x00,0x50
// Tile number 0x021
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x022
, 0x0F,0xC0,0x3D,0xF0,0xF5,0x3C,0xF4,0x3D,0xFF,0xFD,0xF5,0x7D,0xF4,0x3D,0x14,0x05
// Tile number 0x023
, 0xFF,0xF0,0xF5,0x7C,0xF4,0x3D,0xFF,0xF5,0xF5,0x7C,0xF4,0x3D,0xFF,0xF5,0x15,0x54
// Tile number 0x024
, 0x0F,0xF0,0x3D,0x7C,0xF5,0x05,0xF4,0x00,0xF4,0x00,0x3C,0x3C,0x0F,0xF5,0x01,0x54
// Tile number 0x025
, 0xFF,0xC0,0xF5,0xF0,0xF4,0x3C,0xF4,0x3D,0xF4,0x3D,0xF4,0xF5,0xFF,0xD4,0x15,0x50
// Tile number 0x026
, 0xFF,0xFC,0xF5,0x55,0xF4,0x00,0xFF,0xF0,0xF5,0x54,0xF4,0x00,0xFF,0xFC,0x15,0x55
// Tile number 0x027
, 0xFF,0xFC,0xF5,0x55,0xF4,0x00,0xFF,0xF0,0xF5,0x54,0xF4,0x00,0xF4,0x00,0x14,0x00
// Tile number 0x028
, 0x0F,0xFC,0x3D,0x55,0xF5,0x00,0xF4,0xFC,0xF4,0x3D,0x3C,0x3D,0x0F,0xFD,0x01,0x55
// Tile number 0x029
, 0xF0,0x3C,0xF4,0x3D,0xF4,0x3D,0xFF,0xFD,0xF4,0x3D,0xF4,0x3D,0xF4,0x3D,0x14,0x05
// Tile number 0x02A
, 0x3F,0xFC,0x07,0xD5,0x03,0xD0,0x03,0xD0,0x03,0xD0,0x03,0xD0,0x3F,0xFC,0x05,0x55
// Tile number 0x02B
, 0x03,0xFC,0x00,0x7D,0x00,0x3D,0x00,0x3D,0xF0,0x3D,0xF4,0x3D,0x3F,0xF5,0x05,0x54
// Tile number 0x02C
, 0xF0,0x3C,0xF4,0xF4,0xF7,0xD0,0xFF,0x40,0xFF,0xD0,0xF7,0xF4,0xF4,0xFD,0x14,0x15
// Tile number 0x02D
, 0x3C,0x00,0x3D,0x00,0x3D,0x00,0x3D,0x00,0x3D,0x00,0x3D,0x00,0x3F,0xFC,0x05,0x55
// Tile number 0x02E
, 0xF0,0x3C,0xFC,0xFD,0xFF,0xFD,0xFF,0xFD,0xF7,0x7D,0xF4,0x7D,0xF4,0x3D,0x14,0x05
// Tile number 0x02F
, 0xF0,0x3C,0xFC,0x3D,0xFF,0x3D,0xFF,0xFD,0xF7,0xFD,0xF4,0xFD,0xF4,0x3D,0x14,0x05
// Tile number 0x030
, 0x3F,0xF0,0xF5,0x7C,0xF4,0x3D,0xF4,0x3D,0xF4,0x3D,0xF4,0x3D,0x3F,0xF5,0x05,0x54
// Tile number 0x031
, 0xFF,0xF0,0xF5,0x7C,0xF4,0x3D,0xF4,0x3D,0xFF,0xF5,0xF5,0x54,0xF4,0x00,0x14,0x00
// Tile number 0x032
, 0x3F,0xF0,0xF5,0x7C,0xF4,0x3D,0xF4,0x3D,0xF7,0xFD,0xF5,0xF5,0x3F,0xDC,0x05,0x45
// Tile number 0x033
, 0xFF,0xF0,0xF5,0x7C,0xF4,0x3D,0xF4,0xFD,0xFF,0xD5,0xF7,0xF0,0xF4,0xFC,0x14,0x15
// Tile number 0x034
, 0x3F,0xC0,0xF5,0xF0,0xF4,0x54,0x3F,0xF0,0x05,0x7C,0xF0,0x3D,0x3F,0xF5,0x05,0x54
// Tile number 0x035
, 0x3F,0xFC,0x07,0xD5,0x03,0xD0,0x03,0xD0,0x03,0xD0,0x03,0xD0,0x03,0xD0,0x00,0x50
// Tile number 0x036
, 0xF0,0x3C,0xF4,0x3D,0xF4,0x3D,0xF4,0x3D,0xF4,0x3D,0xF4,0x3D,0x3F,0xF5,0x05,0x54
// Tile number 0x037
, 0xF0,0x3C,0xF4,0x3D,0xF4,0x3D,0xFC,0xFD,0x3F,0xF5,0x0F,0xD4,0x03,0x50,0x00,0x40
// Tile number 0x038
, 0xF0,0x3C,0xF4,0x3D,0xF7,0x3D,0xFF,0xFD,0xFF,0xFD,0xFD,0xFD,0xF5,0x3D,0x14,0x05
// Tile number 0x039
, 0xF0,0x3C,0xFC,0xFD,0x3F,0xF4,0x0F,0xD0,0x3F,0xF0,0xFD,0xFC,0xF5,0x3D,0x14,0x05
// Tile number 0x03A
, 0x3C,0x3C,0x3D,0x3D,0x3D,0x3D,0x0F,0xF5,0x03,0xD0,0x03,0xD0,0x03,0xD0,0x00,0x50
// Tile number 0x03B
, 0xFF,0xFC,0x15,0xFD,0x03,0xF4,0x0F,0xD0,0x3F,0x40,0xFD,0x00,0xFF,0xFC,0x15,0x55
// Tile number 0x03C
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x03D
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x03E
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x03F
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x040
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x041
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x042
, 0x0F,0xC0,0x3D,0xF0,0xF5,0x3C,0xF4,0x3D,0xFF,0xFD,0xF5,0x7D,0xF4,0x3D,0x14,0x05
// Tile number 0x043
, 0xFF,0xF0,0xF5,0x7C,0xF4,0x3D,0xFF,0xF5,0xF5,0x7C,0xF4,0x3D,0xFF,0xF5,0x15,0x54
// Tile number 0x044
, 0x0F,0xF0,0x3D,0x7C,0xF5,0x05,0xF4,0x00,0xF4,0x00,0x3C,0x3C,0x0F,0xF5,0x01,0x54
// Tile number 0x045
, 0xFF,0xC0,0xF5,0xF0,0xF4,0x3C,0xF4,0x3D,0xF4,0x3D,0xF4,0xF5,0xFF,0xD4,0x15,0x50
// Tile number 0x046
, 0xFF,0xFC,0xF5,0x55,0xF4,0x00,0xFF,0xF0,0xF5,0x54,0xF4,0x00,0xFF,0xFC,0x15,0x55
// Tile number 0x047
, 0xFF,0xFC,0xF5,0x55,0xF4,0x00,0xFF,0xF0,0xF5,0x54,0xF4,0x00,0xF4,0x00,0x14,0x00
// Tile number 0x048
, 0x0F,0xFC,0x3D,0x55,0xF5,0x00,0xF4,0xFC,0xF4,0x3D,0x3C,0x3D,0x0F,0xFD,0x01,0x55
// Tile number 0x049
, 0xF0,0x3C,0xF4,0x3D,0xF4,0x3D,0xFF,0xFD,0xF4,0x3D,0xF4,0x3D,0xF4,0x3D,0x14,0x05
// Tile number 0x04A
, 0x3F,0xFC,0x07,0xD5,0x03,0xD0,0x03,0xD0,0x03,0xD0,0x03,0xD0,0x3F,0xFC,0x05,0x55
// Tile number 0x04B
, 0x03,0xFC,0x00,0x7D,0x00,0x3D,0x00,0x3D,0xF0,0x3D,0xF4,0x3D,0x3F,0xF5,0x05,0x54
// Tile number 0x04C
, 0xF0,0x3C,0xF4,0xF4,0xF7,0xD0,0xFF,0x40,0xFF,0xD0,0xF7,0xF4,0xF4,0xFD,0x14,0x15
// Tile number 0x04D
, 0x3C,0x00,0x3D,0x00,0x3D,0x00,0x3D,0x00,0x3D,0x00,0x3D,0x00,0x3F,0xFC,0x05,0x55
// Tile number 0x04E
, 0xF0,0x3C,0xFC,0xFD,0xFF,0xFD,0xFF,0xFD,0xF7,0x7D,0xF4,0x7D,0xF4,0x3D,0x14,0x05
// Tile number 0x04F
, 0xF0,0x3C,0xFC,0x3D,0xFF,0x3D,0xFF,0xFD,0xF7,0xFD,0xF4,0xFD,0xF4,0x3D,0x14,0x05
// Tile number 0x050
, 0x3F,0xF0,0xF5,0x7C,0xF4,0x3D,0xF4,0x3D,0xF4,0x3D,0xF4,0x3D,0x3F,0xF5,0x05,0x54
// Tile number 0x051
, 0xFF,0xF0,0xF5,0x7C,0xF4,0x3D,0xF4,0x3D,0xFF,0xF5,0xF5,0x54,0xF4,0x00,0x14,0x00
// Tile number 0x052
, 0x3F,0xF0,0xF5,0x7C,0xF4,0x3D,0xF4,0x3D,0xF7,0xFD,0xF5,0xF5,0x3F,0xDC,0x05,0x45
// Tile number 0x053
, 0xFF,0xF0,0xF5,0x7C,0xF4,0x3D,0xF4,0xFD,0xFF,0xD5,0xF7,0xF0,0xF4,0xFC,0x14,0x15
// Tile number 0x054
, 0x3F,0xC0,0xF5,0xF0,0xF4,0x54,0x3F,0xF0,0x05,0x7C,0xF0,0x3D,0x3F,0xF5,0x05,0x54
// Tile number 0x055
, 0x3F,0xFC,0x07,0xD5,0x03,0xD0,0x03,0xD0,0x03,0xD0,0x03,0xD0,0x03,0xD0,0x00,0x50
// Tile number 0x056
, 0xF0,0x3C,0xF4,0x3D,0xF4,0x3D,0xF4,0x3D,0xF4,0x3D,0xF4,0x3D,0x3F,0xF5,0x05,0x54
// Tile number 0x057
, 0xF0,0x3C,0xF4,0x3D,0xF4,0x3D,0xFC,0xFD,0x3F,0xF5,0x0F,0xD4,0x03,0x50,0x00,0x40
// Tile number 0x058
, 0xF0,0x3C,0xF4,0x3D,0xF7,0x3D,0xFF,0xFD,0xFF,0xFD,0xFD,0xFD,0xF5,0x3D,0x14,0x05
// Tile number 0x059
, 0xF0,0x3C,0xFC,0xFD,0x3F,0xF4,0x0F,0xD0,0x3F,0xF0,0xFD,0xFC,0xF5,0x3D,0x14,0x05
// Tile number 0x05A
, 0x3C,0x3C,0x3D,0x3D,0x3D,0x3D,0x0F,0xF5,0x03,0xD0,0x03,0xD0,0x03,0xD0,0x00,0x50
// Tile number 0x05B
, 0xFF,0xFC,0x15,0xFD,0x03,0xF4,0x0F,0xD0,0x3F,0x40,0xFD,0x00,0xFF,0xFC,0x15,0x55
// Tile number 0x05C
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x05D
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x05E
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x05F
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x060
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x061
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x062
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x063
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// Tile number 0x003
, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};


static	Uint8 *FNT_SerchFont8_2bpp(Uint8 code)
{
	if(code >= 0x20 && code < 0x80)
	    return((Uint8 *)(FntAsciiFontData2bpp+((Uint32 )(code-0x20))*16));

	return((Uint8 *)FntAsciiFontData2bpp);
}


static	void  FNT_Print1Char256_8x8_2bpp(volatile Uint8 *vram,Uint8 code,
									Uint16 x,Uint16 y,Uint16 col1,Uint16 col2,Uint16 col3,Uint16 back)
{
Uint32	wx,wy,wp;
Sint32	i=0,j;
Uint8	*codep;

	codep = FNT_SerchFont8_2bpp(code);

	wx = x;
	wy = y;

	wp = wx	+ wy * FntXsize;
	if(back < 256) 
	{
	    for(i=0;i<16;i++) 

		{
			for(j=3;j>-1;j--) 
			{
				switch ((codep[i]>>(j*2)) & (0x03) )
				{
					case 0x01 :
//						printf("1");
					vram[wp]= (Uint8 )col1;
						break;
					case 0x02 :
//						printf("2");
					vram[wp]= (Uint8 )col2;
						break;
					case 0x03 :
//						printf("3");
					vram[wp]= (Uint8 )col3;
						break;
					default:
//						printf("0");
					vram[wp]= (Uint8 )back;
						break;
				}
/*
				if(codep[i] & FntBitPat[j])
//					vram[wp]= (Uint8 )col;
					printf("1");
				else
					printf("0");
//					vram[wp]= (Uint8 )back;

*/				
//					vram[wp]= (Uint8 )col1;
              wp++;
			}
//			if(i%2)
//				printf("\n");
//			wp += (FntXsize - 8);
			if(i%2)
			       wp += (FntXsize-8);
		}
	}
/*	else{
	    for(i=0;i<16;i++) {
		for(j=0;j<8;j++) {
			if(codep[i] & FntBitPat[j])
				vram[wp]= (Uint8 )col;
			wp++;
		}
		wp += (FntXsize - 8);
	    }
	}
*/
}


void  FNT_Print256_2bpp(volatile Uint8 *vram,volatile Uint8 *str,Uint16 x,Uint16 y,
											Uint16 col1,Uint16 col2,Uint16 col3,Uint16 back)
{
Uint32	i;
Uint16	wx,wy;

	wx = x;wy = y;

	/* �Z���^�����O */
/* #if !(__GNUC__) */

//	if(wx > FntXsize)	wx = FntXsize/2 - strlen((Uint8 *)str)*4;
	if(wx > FntXsize)	wx = FntXsize/2 - strlen((const char *)str)*4;

	i=0;
	while(str[i]) {
		if(str[i] > 0x80 && str[i] < 0xA0) {
			/* �V�t�g�i�h�r�S�p�R�[�h��������X�y�[�X��������B */
			wx += 16;
			i++;
		}else if(str[i]=='\\'){
			i++;
			if(str[i]=='n') {
//				wx = x;wy += 18;// ���s 
//				if(wy > FntYsize-15)	return;
				wx = x;wy += 10;// ���s 
				if(wy > FntYsize-7)	return;

			}
		}else if(str[i]==0x0a) {
//			wx = x;wy += 18;// ���s 
//			if(wy > FntYsize-15)	return;
			wx = x;wy += 10;// ���s 
			if(wy > FntYsize-7)	return;			
		}else{
			FNT_Print1Char256_8x8_2bpp(vram,str[i],wx,wy,col1,col2,col3,back);
			wx += 8;
		}
		if(wx+8 >= FntXsize) {
//			wx = x;wy += 18;/* ���s */
//			if(wy > FntYsize-15)	return;
				wx = x;wy += 10;// ���s 
				if(wy > FntYsize-7)	return;
		}
		i++;
	}
}


/*
static	Uint8 *FNT_SerchFont8(Uint8 code)
{
	if(code >= 0x20 && code < 0x80)
	    return((Uint8 *)(FntAsciiFontData+((Uint32 )(code-0x20))*16));

	return((Uint8 *)FntAsciiFontData);
}
*/
/*
static	void  FNT_Print1Char256_8x16(volatile Uint8 *vram,Uint8 code,
									Uint16 x,Uint16 y,Uint16 col,Uint16 back)
{
Uint32	wx,wy,wp;
Uint32	i,j;
Uint8	*codep;

	codep = FNT_SerchFont8(code);

	wx = x;
	wy = y;

	wp = wx	+ wy * FntXsize;
	if(back < 256) {
	    for(i=0;i<16;i++) {
		for(j=0;j<8;j++) {
			if(codep[i] & FntBitPat[j])
				vram[wp]= (Uint8 )col;
			else
				vram[wp]= (Uint8 )back;
			wp++;
		}
		wp += (FntXsize - 8);
	    }
	}else{
	    for(i=0;i<16;i++) {
		for(j=0;j<8;j++) {
			if(codep[i] & FntBitPat[j])
				vram[wp]= (Uint8 )col;
			wp++;
		}
		wp += (FntXsize - 8);
	    }
	}
}
*/
/*
void  FNT_Print256(volatile Uint8 *vram,volatile Uint8 *str,Uint16 x,Uint16 y,
											Uint16 col,Uint16 back)
{
Uint32	i;
Uint16	wx,wy;

	wx = x;wy = y;

	// �Z���^�����O 
// #if !(__GNUC__) 

	if(wx > FntXsize)	wx = FntXsize/2 - strlen((Uint8 *)str)*4;

	i=0;
	while(str[i]) {
		if(str[i] > 0x80 && str[i] < 0xA0) {
			// �V�t�g�i�h�r�S�p�R�[�h��������X�y�[�X��������B 
			wx += 16;
			i++;
		}else if(str[i]=='\\'){
			i++;
			if(str[i]=='n') {
				wx = x;wy += 18;// ���s 
				if(wy > FntYsize-15)	return;
			}
		}else if(str[i]==0x0a) {
			wx = x;wy += 18;// ���s 
			if(wy > FntYsize-15)	return;
		}else{
			FNT_Print1Char256_8x16(vram,str[i],wx,wy,col,back);
			wx += 8;
		}
		if(wx+8 >= FntXsize) {
			wx = x;wy += 18;// ���s 
			if(wy > FntYsize-15)	return;
		}
		i++;
	}
}
*/