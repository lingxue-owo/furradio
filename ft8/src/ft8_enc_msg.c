#include "ft8_enc.h"

// bit  length note
// 0 -76    77 message
// 77-90    14 crc  checksum
// 91-173   83 ldpc checksum

// symb length note
// 0-6       7 costas array sequence
// 7-35     29 Message A
// 36-42     7 costas array sequence
// 43-71    29 Message B
// 72-78     7 costas array sequence

#define BIT_LENGTH  174 /* ldpc(174,91) encode output*/
static u08 bit[BIT_LENGTH];

static int  type_to_i3n3(u08 *msg, const int type, const int subtype);
//static int  text_to_f71(u08 *msg, const char *text);
//static int  data_to_t71(u08 *msg, const u08  *data);
//static int  call_to_c28(u08 *msg, const char *call);
//static int  call_to_c58(u08 *msg, const char *call);
//static int  call_to_h12(u08 *msg, const char *call);
//static int  grid_to_g15(u08 *msg, const char *grid);

static void fitbit(u08 *bit, u32 data, int length);
static void enc(u08 *symbol, u08 *bit);
static void crc(u08 *chk, const u08 *msg);
static void crc_shift(u08 *p);
static void crc_xor(u08 *p);
//static void ldpc(u08 *chk, const u08 *msg);
static void map(u08* symbol, u08* bit);
static void costas(u08* symbol);

/* 00 Free Text */
int ft8_encode_00(u08 *symbol, const char *text)
{
	int ret = 0;
	type_to_i3n3(bit+ 0, 0, 0);
//	ret |= text_to_f71(bit + 6, text);
	enc(symbol, bit);
	return ret;
}

int ft8_encode_05(u08 *symbol, const u08 data[18])
{
	int ret = 0;
	ret |= type_to_i3n3(bit + 0, 0, 5);
//	ret |= data_to_t71 (bit + 6, data);
	enc(symbol, bit);
	return ret;
}

static int type_to_i3n3(u08 *msg, const int type, const int subtype)
{
	int ret = 0;
	fitbit(msg + 0, type, 3);
	if (type == 0)
		fitbit(msg + 3, subtype, 3);
	return ret;
}

static void fitbit(u08 *bit, u32 data, int length)
{
	int i;
	for (i = 0; i < length; ++i)
		bit[i] = (data & (1u << i)) ? 1 : 0;
}

static void enc(u08 *symbol, u08 *bit)
{
	crc( bit + 77, bit);
//	ldpc(bit + 91, bit);
	costas(symbol + 0);
	map(   symbol + 36, bit + 0);
	costas(symbol + 0);
	map(   symbol + 43, bit + 87);
	costas(symbol + 72);
	return;
}

static void crc(u08 *chk, const u08 *msg)
{
	int i;
	static u08 crc[14] = {0};
	for (i = 0; i < 82; ++i) {
		if (i < 77)
			crc[0] ^= msg[i];
		if (crc[0]) {
			crc_shift(crc);
			crc_xor(crc);
		} else {
			crc_shift(crc);
		}
	}
	for (i = 0; i < 14; i++)
		chk[i] = crc[i];
	return;
}

static void crc_shift(u08 *p)
{
	int j;
	for (j = 0; j < 13; ++j)
		p[j] = p[j + 1];
	p[13] = 0;
}

static void crc_xor(u08 *p)
{
	int j;
	const static int poly[14] = {
		1,0, 0,1,1,1, 0,1,0,1, 0,1,1,1,
	}; /* 0x2757 */
	for (j = 0; j < 14; ++j)
		p[j] ^= poly[j];
}

static void map(u08* symbol, u08* bit)
{
	int i, t;
	const static u08 gray_table[8] = {0,1,3,2,5,6,4,7};
	for (i = 0; i < 29; ++i) {
		t = 0;
		t |= bit[3*i+0] ? 0x01 : 0;
		t |= bit[3*i+1] ? 0x02 : 0;
		t |= bit[3*i+2] ? 0x04 : 0;
		symbol[i] = gray_table[t];
	}
	return;
}

static void costas(u08* symbol)
{
	int i;
	static u08 costas[7] = {3,1,4,0,6,5,2};
	for (i = 0; i < 7; i++)
		symbol[i] = costas[i];
	return;
}


