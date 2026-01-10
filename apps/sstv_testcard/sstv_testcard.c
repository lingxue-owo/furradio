#include "furradio/bmp.h"
#include "furradio/sstv.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum card_type {
    CARD_TYPE_UNDIFINED,
    COLOR_BAR_GB3174,
    COLOR_BAR_75,
    COLOR_BAR_100,
};

static void colorbar_line(u08 *r, u08 *g, u08 *b,
                             const int width, const enum card_type ctype);
static void colorbar_gen(u08 *r, u08 *g, u08 *b,
                            const int width, const int hight, const enum card_type ctype);
static void testcard_gen(enum sstv_type stype, enum card_type ctype);

void help()
{
    printf("sstv_testcard [sstvtype] [cardtype]\n");
    printf("    [sstvtype]  m1 - 4        : martin  1 - 4\n");
    printf("                s1 - s4, sdx  : scottie 1 - 4, dx\n");
    printf("                pd120\n");
    printf("                avt90,94\n");
    printf("                robot36,72\n");
    printf("    [cardtype]  cb75     : color bar 75%%\n");
    printf("                cb100    : color bar 100%%\n");
    printf("                cbgb     : color bar 100/0/75/0, GB 3174 - 1995\n");
}

int main(int argc, char *argv[])
{
    enum card_type ctype = CARD_TYPE_UNDIFINED;
    enum sstv_type stype = SSTV_TYPE_UNDEFINED;
    switch (argc) {
        case 3:
            if (!strcmp(argv[2], "cb75"))  ctype = COLOR_BAR_75;
            if (!strcmp(argv[2], "cb100")) ctype = COLOR_BAR_100;
            if (!strcmp(argv[2], "cbgb"))  ctype = COLOR_BAR_GB3174;
        case 2:
            if (!strcmp(argv[1], "m1"))      stype = SSTV_MART_1;
            if (!strcmp(argv[1], "m2"))      stype = SSTV_MART_2;
            if (!strcmp(argv[1], "m3"))      stype = SSTV_MART_3;
            if (!strcmp(argv[1], "m4"))      stype = SSTV_MART_4;
            if (!strcmp(argv[1], "s1"))      stype = SSTV_SCOT_1;
            if (!strcmp(argv[1], "s2"))      stype = SSTV_SCOT_2;
            if (!strcmp(argv[1], "s3"))      stype = SSTV_SCOT_3;
            if (!strcmp(argv[1], "s4"))      stype = SSTV_SCOT_4;
            if (!strcmp(argv[1], "sdx"))     stype = SSTV_SCOT_DX;
            if (!strcmp(argv[1], "pd120"))   stype = SSTV_PD_120;
            if (!strcmp(argv[1], "avt90"))   stype = SSTV_AVT_90;
            if (!strcmp(argv[1], "avt94"))   stype = SSTV_AVT_94;
            if (!strcmp(argv[1], "robot36")) stype = SSTV_ROBOT_36;
            if (!strcmp(argv[1], "robot72")) stype = SSTV_ROBOT_72;

            if (!strcmp(argv[1], "ntsc"))    stype = SDTV_NTSC_M;
            if (!strcmp(argv[1], "pal"))     stype = SDTV_PAL_D;
            if (!strcmp(argv[1], "hd"))      stype = HDTV_720;
            if (!strcmp(argv[1], "fhd"))     stype = HDTV_1080;
            if (!strcmp(argv[1], "uhd"))     stype = HDTV_4K;
            if (!strcmp(argv[1], "8k"))      stype = HDTV_8K;
            break;
        default:
            help();
            return -2;
    }
    if (ctype == CARD_TYPE_UNDIFINED || stype == SSTV_TYPE_UNDEFINED) {
        help();
        return -3;
    }
    testcard_gen(stype, ctype);
    return 0;
}

static void testcard_gen(enum sstv_type stype, enum card_type ctype)
{
    int hight, width;
    u08 *r, *g, *b;
    enum sstv_ratio ratio;
    char fname[256];

    hight = sstv_line_get(stype);
    ratio = sstv_ratio_get(stype);

    switch (ratio) {
    case SSTV_RATIO_11:  width = hight; break;
    case SSTV_RATIO_43:  width = hight *  4 / 3; break;
    case SSTV_RATIO_169: width = hight * 16 / 9; break;
    default: width = hight;
    }

    r = (u08*)malloc(hight * width * sizeof(u08));
    g = (u08*)malloc(hight * width * sizeof(u08));
    b = (u08*)malloc(hight * width * sizeof(u08));

    switch (ctype) {
    case COLOR_BAR_GB3174:
    case COLOR_BAR_75:
    case COLOR_BAR_100:
        colorbar_gen(r,g,b, width, hight, ctype);
        break;
    default: break;
    }

    sprintf(fname, "testcard_%dx%d_%d_%d.bmp", hight, width, ctype, stype);
    bmp_rgb_write(fname, r, g, b, width, hight);
    free(r); free(g); free(b);
    return;
}


static void colorbar_gen(u08 *r, u08 *g, u08 *b,
            const int width, const int hight, const enum card_type ctype)
{
    int y;
    u08 *rl, *gl, *bl;
    for (y = 0; y < hight; ++y) {
        rl = r + y * width;
        gl = g + y * width;
        bl = b + y * width;
        colorbar_line(rl, gl, bl, width, ctype);
    }
}

static void colorbar_line(u08 *r, u08 *g, u08 *b, const int width, const enum card_type ctype)
{                            // W    Y    C    G    M    R    B   K
    static const u08 tbr_gb3174[] = {255, 191,   0,   0, 191, 191,   0, 0};
    static const u08 tbg_gb3174[] = {255, 191, 191, 191,   0,   0,   0, 0};
    static const u08 tbb_gb3174[] = {255,   0, 191,   0, 191,   0, 191, 0};
    static const u08 tbr_100[]    = {255, 255,   0,   0, 255, 255,   0, 0};
    static const u08 tbg_100[]    = {255, 255, 255, 255,   0,   0,   0, 0};
    static const u08 tbb_100[]    = {255,   0, 255,   0, 255,   0, 255, 0};
    static const u08 tbr_75[]     = {191, 191,   0,   0, 191, 191,   0, 0};
    static const u08 tbg_75[]     = {191, 191, 191, 191,   0,   0,   0, 0};
    static const u08 tbb_75[]     = {191,   0, 191,   0, 191,   0, 191, 0};

    int i, j, k, len;
    const u08 *tbr, *tbg, *tbb;
    const int num = 8;

    switch (ctype) {
        case COLOR_BAR_GB3174: tbr = tbr_gb3174, tbg = tbg_gb3174, tbb = tbb_gb3174; break;
        case COLOR_BAR_100:    tbr = tbr_100,    tbg = tbg_100,    tbb = tbb_100;    break;
        case COLOR_BAR_75:     tbr = tbr_75,     tbg = tbg_75,     tbb = tbb_75;     break;
        default: return;
    }

    len = width / num;
    for (i = j = k = 0; i < num; ++i)
        for (; j < (i + 1) * len; ++j) {
            r[j] = tbr[i];
            g[j] = tbg[i];
            b[j] = tbb[i];
            ++k;
        }
    for (; k < width; ++k)
        r[k] = g[k] = b[k] = 0;
}

