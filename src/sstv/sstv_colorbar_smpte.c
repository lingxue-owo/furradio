#include "furradio/sstv.h"
#include "common.h"

#include <stdio.h>

static void line1(f32 *cr, f32 *y, f32 *cb, int w, enum sstv_ratio ratio);
static void line2(f32 *cr, f32 *y, f32 *cb, int w, enum sstv_ratio ratio);
static void line3(f32 *cr, f32 *y, f32 *cb, int w, enum sstv_ratio ratio);
static void line4a(f32 *cr, f32 *y, f32 *cb, int w, enum sstv_ratio ratio);
static void line4b(f32 *cr, f32 *y, f32 *cb, int w, enum sstv_ratio ratio);

void sstv_colorbar2_gen(f32 *cr, f32 *y, f32 *cb,
    const int w, const int h, const enum sstv_ratio ratio)
{
    int l, h1;
    f32 *yl, *cbl, *crl;
    h1 = h * 1 / 12;
    for (l = 0; l < h; ++l) {
        yl  = y  + l * w;
        cbl = cb + l * w;
        crl = cr + l * w;
        if      (l < h1*1) {line4a(crl, yl, cbl, w, ratio);} //43
        else if (l < h1*2) {line4b(crl, yl, cbl, w, ratio);} // 42
        else if (l < h1*3) {line4a(crl, yl, cbl, w, ratio);} // 41
        else if (l < h1*4) {line3(crl, yl, cbl, w, ratio);} // 3
        else if (l < h1*5) {line2(crl, yl, cbl, w, ratio);} // Patten2
        else               {line1(crl, yl, cbl, w, ratio);} // Patten1
    }
}

// 10 bit QUant BT.709
#define F10Y(y)    (((y)- 64.)/876.)
#define F10C(c)    (((c)-512.)/896.)

#define BLACK_N2   {*(y++) = -.02; *(cr++) = *(cb++) = .0;}
#define BLACK_0    {*(y++) = +.00; *(cr++) = *(cb++) = .0;}
#define BLACK_2    {*(y++) = +.02; *(cr++) = *(cb++) = .0;}
#define BLACK_4    {*(y++) = +.04; *(cr++) = *(cb++) = .0;}
#define GRAY_15    {*(y++) = +.15; *(cr++) = *(cb++) = .0;}
#define GRAY_40    {*(y++) = +.40; *(cr++) = *(cb++) = .0;}
#define WHITE_75   {*(y++) = +.75; *(cr++) = *(cb++) = .0;}
#define WHITE_100  {*(y++) = +1.0; *(cr++) = *(cb++) = .0;}

#define YELLOW_75  {*(y++)=F10Y(674);*(cr++)=F10C(543);*(cb++)=F10C(176);}
#define CYAN_75    {*(y++)=F10Y(581);*(cr++)=F10C(176);*(cb++)=F10C(589);}
#define GREEN_75   {*(y++)=F10Y(534);*(cr++)=F10C(207);*(cb++)=F10C(253);}
#define MAGENTA_75 {*(y++)=F10Y(251);*(cr++)=F10C(817);*(cb++)=F10C(771);}
#define RED_75     {*(y++)=F10Y(204);*(cr++)=F10C(848);*(cb++)=F10C(435);}
#define BLUE_75    {*(y++)=F10Y(111);*(cr++)=F10C(481);*(cb++)=F10C(848);}

#define YELLOW_100 {*(y++)=F10Y(877);*(cr++)=F10C(553);*(cb++)=F10C(64);}
#define CYAN_100   {*(y++)=F10Y(754);*(cr++)=F10C( 64);*(cb++)=F10C(615);}
#define RED_100    {*(y++)=F10Y(250);*(cr++)=F10C(960);*(cb++)=F10C(409);}
#define BLUE_100   {*(y++)=F10Y(127);*(cr++)=F10C(471);*(cb++)=F10C(960);}

#define PLUS_I     {*(y++)=F10Y(245);*(cr++)=F10C(629);*(cb++)=F10C(412);}
#define MINUS_I    {*(y++)=F10Y(224);*(cr++)=F10C(395);*(cb++)=F10C(612);}
#define PLUS_Q     {*(y++)=F10Y(141);*(cr++)=F10C(606);*(cb++)=F10C(697);}

static void line1(f32 *cr, f32 *y, f32 *cb, int w, enum sstv_ratio ratio)
{
    int d, f, c, i, r = (ratio == SSTV_RATIO_169) ? 1920 : 1440;
    d = w * 240 / r; f = w * 205 / r; c = w * 206 / r;
    if (ratio == SSTV_RATIO_169) for(i=0;i<d;++i) GRAY_40
    for (i=0; i <f; ++i) WHITE_75
    for (i=0; i <c; ++i) YELLOW_75
    for (i=0; i <c; ++i) CYAN_75
    for (i=0; i <c; ++i) GREEN_75
    for (i=0; i <c; ++i) MAGENTA_75
    for (i=0; i <c; ++i) RED_75
    for (i=0; i <f; ++i) BLUE_75
    if (ratio == SSTV_RATIO_169) for(i=0;i<d;++i) GRAY_40
}

static void line2(f32 *cr, f32 *y, f32 *cb, int w, enum sstv_ratio ratio)
{
    int d, f, c, i, r = (ratio == SSTV_RATIO_169) ? 1920 : 1440;
    d = w * 240 / r; f = w * 205 / r; c = w * 206 / r;
    if (ratio == SSTV_RATIO_169) for(i=0;i<d;++i) CYAN_100
    for (i=0; i <f; ++i)  MINUS_I
    for (i=0;i<5*c+f;++i) WHITE_75
    if (ratio == SSTV_RATIO_169) for(i=0;i<d;++i) BLUE_100
}

static void line3(f32 *cr, f32 *y, f32 *cb, int w, enum sstv_ratio ratio)
{
    int d, f, c, i, r = (ratio == SSTV_RATIO_169) ? 1920 : 1440;
    d = w * 240 / r; f = w * 205 / r; c = w * 206 / r;
    if (ratio == SSTV_RATIO_169) for(i=0;i<d;++i) YELLOW_100
    for (i=0; i <f; ++i)  PLUS_Q
    for (i=0; i<5*c+f; ++i) {
         *(y++)  = F10Y(64.+(940.-64.)*i/(5.*c+f));
         *(cr++) = *(cb++) = .0000;
    }
    if (ratio == SSTV_RATIO_169) for(i=0;i<d;++i) RED_100
}

static void line4a(f32 *cr, f32 *y, f32 *cb, int w, enum sstv_ratio ratio)
{
    int i,r = (ratio == SSTV_RATIO_169) ? 1920 : 1440;
    int d = w * 240 / r;
    if (ratio == SSTV_RATIO_169) for(i=0;i<d;++i) GRAY_15
    for (i=0; i<w*309/r; ++i)  BLACK_0
    for (i=0; i<w*411/r; ++i)  WHITE_100
    for (i=0; i<w*171/r; ++i)  BLACK_0
    for (i=0; i<w*69/r;  ++i)  BLACK_N2
    for (i=0; i<w*68/r;  ++i)  BLACK_0
    for (i=0; i<w*69/r;  ++i)  BLACK_2
    for (i=0; i<w*68/r;  ++i)  BLACK_0
    for (i=0; i<w*69/r;  ++i)  BLACK_4
    for (i=0; i<w*206/r; ++i)  BLACK_0
    if (ratio == SSTV_RATIO_169) for(i=0;i<d;++i) GRAY_15
}

static void line4b(f32 *cr, f32 *y, f32 *cb, int w, enum sstv_ratio ratio)
{
    int i,j,m,r = (ratio == SSTV_RATIO_169) ? 1920 : 1440;
    int d = w * 240 / r;
    if (ratio == SSTV_RATIO_169) for(i=0;i<d;++i) GRAY_15
    // sub-black
    m = w * 309 / 2 / r;
    for (i = 0; i < m; ++i) {
        *(y++)  = F10Y(64.+(4-64.)*i/m);
        *(cr++) = *(cb++) = .0000;
    }
    for (j = i, i = 0; j < w*309/r; ++i, ++j) {
        *(y++)  = F10Y(4+(64.-4)*i/m);
        *(cr++) = *(cb++) = .0000;
    }
    // super-white
    m = w * 411 / 2 / r;
    for (i = 0; i < m; ++i) {
        *(y++)  = F10Y(940.+(1019.-940.)*i/m);
        *(cr++) = *(cb++) = .0000;
    }
    for (j = i, i = 0; j < w*411/r; ++i, ++j) {
        *(y++)  = F10Y(1019+(940.-1019.)*i/m);
        *(cr++) = *(cb++) = .0000;
    }
    for (i=0; i<w*171/r; ++i)  BLACK_0
    for (i=0; i<w*69/r;  ++i)  BLACK_N2
    for (i=0; i<w*68/r;  ++i)  BLACK_0
    for (i=0; i<w*69/r;  ++i)  BLACK_2
    for (i=0; i<w*68/r;  ++i)  BLACK_0
    for (i=0; i<w*69/r;  ++i)  BLACK_4
    for (i=0; i<w*206/r; ++i)  BLACK_0
    if (ratio == SSTV_RATIO_169) for(i=0;i<d;++i) GRAY_15
}
