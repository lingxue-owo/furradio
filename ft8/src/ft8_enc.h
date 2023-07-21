/*
 * ft8_wave_gen.h
 *
 *  Created on: Jul 19, 2023
 *      Author: mioyuki
 */

#ifndef FT8_ENC_H_
#define FT8_ENC_H_

#include "common.h"

int ft8_wave_init(const u08 *symbol, const f64 if_freq, const f64 fs_freq);
s16 ft8_wave_getsample();

#endif /* FT8_ENC_H_ */
