#ifndef WAV_H_
#define WAV_H_

#include <stdint.h>

enum wave_sample_rate_e {
    WAVE_RATE_12000 = 12000,
    WAVE_RATE_48000 = 48000,
};

int wav_s16_write(int16_t* p, int length,
    enum wave_sample_rate_e fs, const char* filename);

#endif

