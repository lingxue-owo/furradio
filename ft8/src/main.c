/*
 ============================================================================
 Name        : furadio_ft8.c
 Author      : mioyuki
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */
#include "ft8_enc.h"

#include "common.h"
#include <stdio.h>

int ft8_encode(s16 *wave, const u08 *symb, const f64 fs);

#define SAMPLE_FREQ 48000 /* [Hz] */

int main(void) {
#if 0
	u08 symb[79] = {
			3,1,4,0,6, 5,2, // 7symb sync costas array
			0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0, // 29symb
			3,1,4,0,6, 5,2,
			0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,
			3,1,4,0,6, 5,2,
	};
	s16 wave[15 * SAMPLE_FREQ]; // wave FT8 frame time: 12.640s
	ft8_encode(wave, symb, SAMPLE_FREQ);
#endif

	u08 symb0[79] = {0};
	u08 data[18] = {1,2,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd,0xe,0xf,0,0xa,0xa};
	ft8_encode_05(symb0, data);
    ft8_encode_00(symb0, "TEST TEXT");
//	ft8_encode_1(symb0, "CQ", FALSE, "BG3ILA", FALSE, FALSE, "ON63");

	return 0;
}

int ft8_encode(s16 *wave, const u08* symb, const f64 fs)
{
	int n = 0;
	ft8_wave_init(symb, 1747, fs);
	for (n = 0; n < fs * 12.640; n++) {
//		printf("n %d T %lf ", n, n/fs);
		wave[n] = ft8_wave_getsample();
	}
	return n;
}
