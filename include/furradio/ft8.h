#ifndef FT8_H_
#define FT8_H_

#include <stdint.h>

/* Encode */

/* ft8_enc.c:
 * radio/audio wave generate */

int ft8_wave_init(const uint8_t* symbol,
				  const double if_freq, const double fs_freq);
int16_t ft8_wave_get_sample(void);
int ft8_wave_get_block(int16_t* wave, const uint8_t* symb, const double fs);

 /* ft8_enc_msg.c:
  * commonly used frame
  * message type #00 FreeText
  * message type #05 Telemetry
  * message type 1   StdMsg
  * message type 4   Non-std Callsign */

enum ft8_call_type_e {
	FT8_CALL_TYPE_DE     = 0x00,
	FT8_CALL_TYPE_QRZ    = 0x01,
	FT8_CALL_TYPE_CQ     = 0x02,
	FT8_CALL_TYPE_CQ_NUM = 0x03,
	FT8_CALL_TYPE_CQ_TXT = 0x04,
	FT8_CALL_TYPE_NSTD   = 0x05,
	FT8_CALL_TYPE_STD    = 0x06,
};

enum ft8_report_type_e {
	FT8_REPORT_TYPE_BLANK = 0x01,
	FT8_REPORT_TYPE_RRR   = 0x02,
	FT8_REPORT_TYPE_RR73  = 0x03,
	FT8_REPORT_TYPE_73    = 0x04,
	FT8_REPORT_TYPE_GRID  = 0x05,
	FT8_REPORT_TYPE_SNR   = 0x06,
};

struct ft8_std_msg_t {
	enum ft8_call_type_e   call_1_type;
	enum ft8_call_type_e   call_2_type;
	enum ft8_report_type_e report_type;
	int16_t cq_num_1, cq_num_2, snr;
	uint8_t call_1_r, call_2_r, report_r;
	const char *call_1, *call_2, *grid;
};

struct ft8_nstd_call_t {
	const char *hash_call, *text_call;
	uint8_t is_hash_local, is_cq, report;
};

int ft8_encode_00(uint8_t* symbol, const char *freetext);
int ft8_encode_05(uint8_t* symbol, const uint8_t telemetry[18]);
int ft8_encode_1(uint8_t* symbol, const struct ft8_std_msg_t *p);
int ft8_encode_4(uint8_t* symbol, const struct ft8_nstd_call_t *p);

// Decode

// TestBench
void ft8_tb(void);

#endif






