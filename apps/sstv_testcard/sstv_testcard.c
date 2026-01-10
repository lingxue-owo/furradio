#include "furradio/bmp.h"
#include "furradio/sstv.h"
#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void help(void);
static void gen(enum sstv_type stype, enum sstv_testcard ctype);

static void help()
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
    enum sstv_testcard ctype = SSTV_TESTCARD_UNDIFINED;
    enum sstv_type     stype = SSTV_TYPE_UNDEFINED;
    switch (argc) {
        case 3:
            if (!strcmp(argv[2], "cb75"))  ctype = SSTV_TESTCARD_COLORBAR_75;
            if (!strcmp(argv[2], "cb100")) ctype = SSTV_TESTCARD_COLORBAR_100;
            if (!strcmp(argv[2], "cbgb"))  ctype = SSTV_TESTCARD_COLORBAR_GB3174;
            if (!strcmp(argv[2], "smpte")) ctype = SSTV_TESTCARD_COLORBAR_SMPTE;
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
    if (ctype == SSTV_TESTCARD_UNDIFINED ||
        stype == SSTV_TYPE_UNDEFINED)
    {
        help();
        return -3;
    }
    gen(stype, ctype);
    return 0;
}

static void gen(enum sstv_type s, enum sstv_testcard c)
{
    int h, w; //hight, width;
    u08 *r, *g, *b;
    enum sstv_ratio t;
    char f[256];

    h = sstv_line_get(s);
    t = sstv_ratio_get(s);

    switch (t) {
    case SSTV_RATIO_43:  w = h *  4 / 3; break;
    case SSTV_RATIO_169: w = h * 16 / 9; break;
    case SSTV_RATIO_11:
    default: w = h;
    }

    r = (u08*)malloc(h * w * sizeof(u08));
    g = (u08*)malloc(h * w * sizeof(u08));
    b = (u08*)malloc(h * w * sizeof(u08));

    switch (c) {
    case SSTV_TESTCARD_COLORBAR_GB3174: sstv_cbgb_gen(r,g,b,w,h);  break;
    case SSTV_TESTCARD_COLORBAR_75:     sstv_cb75_gen(r,g,b,w,h);  break;
    case SSTV_TESTCARD_COLORBAR_100:    sstv_cb100_gen(r,g,b,w,h); break;
    default: break;
    }

    sprintf(f, "testcard_%dx%d_%d_%d.bmp", h, w, c, s);
    bmp_rgb_write(f, r, g, b, w, h);
    free(r); free(g); free(b);
    return;
}
