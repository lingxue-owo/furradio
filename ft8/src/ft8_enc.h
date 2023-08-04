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

#define FT8_CALL_TYPE_DE     0x00
#define FT8_CALL_TYPE_QRZ    0x01
#define FT8_CALL_TYPE_CQ     0x02
#define FT8_CALL_TYPE_CQ_NUM 0x03
#define FT8_CALL_TYPE_CQ_TXT 0x04
#define FT8_CALL_TYPE_NSTD   0x05
#define FT8_CALL_TYPE_STD    0x06

#define FT8_REPORT_TYPE_BLANK 0x01
#define FT8_REPORT_TYPE_RRR   0x02
#define FT8_REPORT_TYPE_RR73  0x03
#define FT8_REPORT_TYPE_73    0x04
#define FT8_REPORT_TYPE_GRID  0x05
#define FT8_REPORT_TYPE_SNR   0x06

struct std_msg_t {
	u08   call_1_type, call_2_type, report_type;
	s16   cq_num_1,    cq_num_2,    snr;
	u08   call_1_r,    call_2_r,    report_r;
	const char  *call_1, *call_2,   *grid;
};

struct nstd_call_t {
	const char *hash_call, *text_call;
	u08 is_hash_local, is_cq, report;
};

int ft8_encode_00(u08 *symbol, const char *freetext);
int ft8_encode_05(u08 *symbol, const u08 telemetry[18]);
int ft8_encode_1(u08 *symbol, const struct std_msg_t *p);
int ft8_encode_4(u08 *symbol, const struct nstd_call_t *p);

#endif /* FT8_ENC_H_ */
