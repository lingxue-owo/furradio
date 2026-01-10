/*
 ============================================================================
 Name        : furadio_ft8.c
 Author      : mioyuki
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include "furradio/ft8.h"
#include "furradio/wav.h"
#include "common.h"

#include <stdio.h>

#define SAMPLE_FREQ WAVE_RATE_12000

static void print_symb(u08* symbol)
{
	int i;
	for (i = 0; i < 79; ++i)
		printf("%u", symbol[i]);
	printf("\n");
}

void tb_1(void)
{
	u08 symb[79] = {
			3,1,4,0,6, 5,2, // 7symb sync costas array
			0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0, // 29symb
			3,1,4,0,6, 5,2,
			0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,
			3,1,4,0,6, 5,2,
	};
	static s16 wave[15 * SAMPLE_FREQ]; 
	// wave FT8 frame time: 12.640s

	ft8_wave_get_block(wave, symb, SAMPLE_FREQ);
	print_symb(symb);
	wav_s16_write(wave, 15 * SAMPLE_FREQ, 
		SAMPLE_FREQ, "ft8_tb1.wav");
}

void tb_2(void)
{
	u08 symb0[79] = { 0 };
	u08 data[18] = { 1,2,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd,0xe,0xf,0,0xa,0xa };
	ft8_encode_05(symb0, data);
	ft8_encode_00(symb0, "TEST TEXT");
	print_symb(symb0);
}

void tb_3(void)
{
	u08 symb0[79] = { 0 };
	struct ft8_std_msg_t msg = { 0 };
	msg.call_1_type = FT8_CALL_TYPE_CQ;
	msg.call_2_type = FT8_CALL_TYPE_STD;
	msg.call_2 = "BG3ILA";
	msg.grid = "ON63";
	ft8_encode_1(symb0, &msg);
	print_symb(symb0);
}

int main(void) 
{
	tb_1();
	tb_2();
	tb_3();
	return 0;
}


