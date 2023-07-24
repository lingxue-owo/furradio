#include "ft8_enc.h"

#define DEBUG 1

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

static u08 g_buff[22];
static const char g_table[] =" 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ+-./?";
//                          ^^         ^11

#if 0
//static int  call_to_c28(u32 *p, const char *call);
//static int  call_to_c58(u32 *p, const char *call);
//static int  call_to_h12(u32 *p, const char *call);
//static int  grid_to_g15(u32 *p, const char *grid);

static int  text_to_f71(u32 *p, const char *text);
static int  idx(const char *g_table, int len, char ch);
static void x42(u08 *bit);
static void add(u08 *bit, int n);
#endif

static void clear();
static void data_to_t71(const u08  *data);
static void add_type(u08 type);
static void add_subtype(u08 subtype);
static void add_crc();
static void add_ldpc();
static void sybmap(u08* symbol, int bitpos);
static void costas(u08* symbol);

#if DEBUG
static void _print_symb(u08* symbol);
static void _print_bit();
#endif

/* 00 Free Text */
int ft8_encode_00(u08 *symbol, const char *text)
{
	int ret = 0;
	clear();
//	ret |= text_to_f71 (buff + 0, text); /* bit 0-70 */
	g_buff[2] |= (0 << 7);  /* n3=0 bit 71-73 */
	g_buff[2] |= (1 << 10); /* i3=0 bit 74-76 */
	//	crc( bit + 77, bit);
	//	ldpc(bit + 91, bit);
	costas(symbol +  0);
	sybmap(symbol +  7, 0);
	costas(symbol + 36);
	sybmap(symbol + 43, 87);
	costas(symbol + 72);
#if DEBUG
	_print_symb(symbol);
	_print_bit();
#endif
	return ret;
}

int ft8_encode_05(u08 *symbol, const u08 data[18])
{
	clear();
	data_to_t71(data);
	add_subtype(5);
	add_type(0);
	add_crc();
	add_ldpc();
	costas(symbol +  0);
	sybmap(symbol +  7, 0);
	costas(symbol + 36);
	sybmap(symbol + 43, 87);
	costas(symbol + 72);
#if DEBUG
	printf("ENC05\n");
	_print_symb(symbol);
	_print_bit();
#endif
	return 0;
}

static void data_to_t71(const u08 *data)
{
	int i, j, cnt;
	g_buff[0] |= (data[0] & 0x07) << 5;
	cnt = 3;
	for (i = 1; i < 18; i++) {
		for (j = 0; j < 4; j++) {
			if (data[i] & (0x08 >> (j % 4)))
				g_buff[cnt/8] |= 0x80 >> (cnt % 8);
			++cnt;
		}
	}
}

#if 0
static int text_to_f71(u08 *bit, const char *text)
{
	int ret, i;
	ret = 0;
	for (i = 0; i < 71; ++i)
		bit[i] = 0;
	for (i = 0; i < 13; ++i) {
		if (!text[i]) break;
		x42(bit);
		int n = idx(g_table, 42, text[i]);
		add(bit, n);
	}
	return ret;
}

static void x42(u08 *bit)
{

}

static void add(u08 *bit, int n)
{

}

static int idx(const char *g_table, int len, char ch)
{
	int n;
	for (n = 0; n < len; n++)
		if (g_table[n] == ch)
			return n;
	return -1;
}
#endif

static void add_type(u08 type)
{
	type &= 0x07;
	g_buff[9] |= type << 3;
	return;
}

static void add_subtype(u08 subtype)
{
	subtype &= 0x07;
	g_buff[8] |= subtype >> 2;
	g_buff[9] |= subtype << 6;
}

static void add_crc()
{
	int i, bit;
	unsigned short crc = 0;
	for (i = 0; i < 82; ++i) {
		if (i < 77) {
			bit = g_buff[i >> 3] & (0x80u >> (i & 0x7));
			crc ^=  bit ? 0x2000 : 0;
		}
		if (crc & 0x2000) {
			crc <<= 1;
			crc ^= 0x2757;
		} else {
			crc <<= 1;
		}
	}
	crc &= 0x3fff;
	g_buff[9]  |= (crc >> 11) & 0xff;
	g_buff[10] |= (crc >> 3 ) & 0xff;
	g_buff[11] |= (crc << 5 ) & 0xff;
}

static void add_ldpc()
{
	return;
}

static void sybmap(u08* symbol, int pos)
{
	int i, j, n, b, t;
	const static u08 gray_table[8] = {0,1,3,2,5,6,4,7};
	for (i = 0 ; i < 29; ++i) {
		t = 0;
		for (j = 0; j < 3; j++) {
			n = 3 * i + j + pos;
			b = g_buff[n / 8] & (0x80u >> (n % 8));
			t |= b ? (0x4u >> j) : 0;
		}
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

static void clear()
{
	int i;
	for (i = 0; i < 10; i++)
		g_buff[i] = 0;
}

#if DEBUG
static void _print_symb(u08* symbol)
{
	int i;
	for (i = 0; i < 79; ++i)
		printf("%u ", symbol[i]);
	printf("\n");
}

static void _print_bit()
{
	int i, j;
	for (i = 0; i < 10; i++)
		for (j = 0; j < 8; j++)
			printf("%c", (g_buff[i] & (0x80 >> j)) ? '1' : '0');
	printf("\n");

	for (i = 0; i < 10; ++i)
		printf("%02x ", g_buff[i]);
	printf("\n");
}
#endif
