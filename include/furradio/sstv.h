
#ifndef SSTV_H_
#define SSTV_H_

#include <stdint.h>

enum sstv_type {
    SSTV_TYPE_UNDEFINED,

    SSTV_MART_1, SSTV_MART_2, SSTV_MART_3, SSTV_MART_4,
    SSTV_SCOT_1, SSTV_SCOT_2, SSTV_SCOT_3, SSTV_SCOT_4, SSTV_SCOT_DX,
    SSTV_PD_120,
    SSTV_AVT_90,   SSTV_AVT_94,
    SSTV_ROBOT_36, SSTV_ROBOT_72,

    SDTV_NTSC_M, SDTV_PAL_D,
    HDTV_720, HDTV_1080, HDTV_4K, HDTV_8K,
};

enum sstv_ratio {
    SSTV_RATIO_11, SSTV_RATIO_43, SSTV_RATIO_169,
};

// system param
int sstv_line_get(enum sstv_type type);
enum sstv_ratio sstv_ratio_get(enum sstv_type type);

// testcards
enum sstv_testcard {
    SSTV_TESTCARD_UNDIFINED,
    SSTV_TESTCARD_COLORBAR_75,
    SSTV_TESTCARD_COLORBAR_100,
    SSTV_TESTCARD_COLORBAR_GB3174,
    SSTV_TESTCARD_COLORBAR_SMPTE,
};

enum sstv_smpte_patten {
    SSTV_SMPTE_P1,
    SSTV_SMPTE_P2,
    SSTV_SMPTE_P3,
    SSTV_SMPTE_P4,
};

void sstv_colorbar1_gen(float *r, float *g, float *b,
            const int width, const int hight, const enum sstv_testcard ctype);
static inline void sstv_cbgb_gen(
    float *r, float *g, float *b, const int w, const int h) {
    sstv_colorbar1_gen(r, g, b, w, h, SSTV_TESTCARD_COLORBAR_GB3174);}
static inline void sstv_cb100_gen(
    float *r, float *g, float *b, const int w, const int h) {
    sstv_colorbar1_gen(r, g, b, w, h, SSTV_TESTCARD_COLORBAR_100);}
static inline void sstv_cb75_gen(
    float *r, float *g, float *b, const int w, const int h) {
    sstv_colorbar1_gen(r, g, b, w, h, SSTV_TESTCARD_COLORBAR_75);}


void sstv_colorbar2_gen(float *cr, float *y, float *cb,
            const int w, const int h, const enum sstv_ratio ratio);
static inline void sstv_cbsmpte_gen(
    float *cr, float *y, float *cb, const int w, const int h) {
    sstv_colorbar2_gen(cr, y, cb, w, h, SSTV_RATIO_43);}
static inline void sstv_cbsmptew_gen(
        float *cr, float *y, float *cb, const int w, const int h) {
        sstv_colorbar2_gen(cr, y, cb, w, h, SSTV_RATIO_169);}

void sstv_rgb2ycbcr_bt601(float *rcr, float *gy, float *bcb, const int wxh);
void sstv_ycbcr2rgb_bt601(float *rcr, float *gy, float *bcb, const int wxh);
void sstv_rgb2ycbcr_bt709(float *rcr, float *gy, float *bcb, const int wxh);
void sstv_ycbcr2rgb_bt709(float *rcr, float *gy, float *bcb, const int wxh);

#endif
