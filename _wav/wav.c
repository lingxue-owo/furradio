#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>

#include "wav.h"

#define RIFF 0x46464952 
#define WAVE 0x45564157 
#define FMT  0x20746d66
#define DATA 0x61746164

enum wave_quant_bit_e {
    WAVE_BIT_8  = 8,
    WAVE_BIT_16 = 16,
};

enum wave_channel_num_e {
    WAVE_CH_1 = 1,
    WAVE_CH_2 = 2,
};

struct wave_header_t {
    uint32_t chunk_id;
    uint32_t chunk_size;
    uint32_t format;

    uint32_t schunk1_id;
    uint32_t schunk1_size;
    uint16_t audio_format;
    uint16_t ch_num;
    uint32_t sp_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bit_per_sp;

    uint32_t schunk2_id;
    uint32_t schunk2_size;
};

static void header_init(struct wave_header_t *header, 
    enum wave_sample_rate_e fs, 
    enum wave_quant_bit_e   q, 
    enum wave_channel_num_e ch, 
    int sample_number)
{
    int sample_size = ch * q / 8;
    int wave_size = sample_number * sample_size;

    header->chunk_id     = RIFF;
    header->chunk_size   = 36 + wave_size;
    header->format       = WAVE;
    header->schunk1_id   = FMT;
    header->schunk1_size = 16;
    header->audio_format = 1;
    header->ch_num       = ch;
    header->sp_rate      = fs;
    header->byte_rate    = sample_size * fs;
    header->block_align  = sample_size;
    header->bit_per_sp   = q;
    header->schunk2_id   = DATA;
    header->schunk2_size = wave_size;
}

int wav_s16_write (int16_t* p, int length, 
    enum wave_sample_rate_e fs,
    const char *filename)
{
    struct wave_header_t h;
    FILE* fp; 

    fp = fopen(filename, "wb");
    if (!fp) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    header_init(&h, fs, WAVE_BIT_16, WAVE_CH_1, length);
    fwrite(&h, sizeof(h), 1, fp);
    fwrite(p, sizeof(int16_t), length, fp);
    fclose(fp);
}

