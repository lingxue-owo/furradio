/*
 * ft8_wave_gen.h
 *
 *  Created on: Jul 19, 2023
 *      Author: mioyuki
 */

#ifndef FT8_ENC_H_
#define FT8_ENC_H_

#include "common.h"

/* ft8_enc.c:
 * radio/audio wave generate */
int ft8_wave_init(const u08 *symbol, const f64 if_freq, const f64 fs_freq);
s16 ft8_wave_getsample();

/* ft8_enc_msg.c:
 * commonly used frame
 * message type #00 FreeText
 * message type #05 Telemetry
 * message type 1   StdMsg
 * message type 4   Non-std Callsign */

int ft8_encode_00(u08 *symbol, const char *text);
int ft8_encode_05(u08 *symbol, const u08 data[18]);
#if 0
int ft8_encode_1(u08 *symbol,
		const char *remote_call, const int is_remote_rover,
		const char *local_call, const int is_local_rover,
		const int is_r, const char *report);
int ft8_encode_4(u08 *symbol,
		const u32 hash12, const char *nonstd_call,
		const int is_hash, const int qsl, const int is_cq);
#define FT8_QSL_BLANK 0x00
#define FT8_QSL_RRR   0x02
#define FT8_QSL_RR73  0x04
#define FT8_QSL_73    0x08
#endif

#endif /* FT8_ENC_H_ */
