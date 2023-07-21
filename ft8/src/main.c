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
	u08 symb[79] = {
			3,1,4,0,6, 5,2, // 7symb sync costas array
			0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0, // 29symb
			3,1,4,0,6, 5,2,
			0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,
			3,1,4,0,6, 5,2,
	};
	s16 wave[15 * SAMPLE_FREQ]; // wave FT8 frame time: 12.640s
//	ft8_encode_1(symb, "CQ", FALSE, "BG3ILA", FALSE, FALSE, "ON63");
	ft8_encode(wave, symb, SAMPLE_FREQ);
	return 0;
}

int ft8_encode(s16 *wave, const u08* symb, const f64 fs)
{
	int n = 0;
	ft8_wave_init(symb, 1747, fs);
	for (n = 0; n < fs * 12.640; n++) {
		printf("n %d T %lf ", n, n/fs);
		wave[n] = ft8_wave_getsample();
	}
	return n;
}
