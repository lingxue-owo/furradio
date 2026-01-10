#include "furradio/sstv.h"
#include "common.h"

//                                W    Y    C    G    M    R    B   K
static const u08 tbr_gb3174[] = {255, 191,   0,   0, 191, 191,   0, 0};
static const u08 tbg_gb3174[] = {255, 191, 191, 191,   0,   0,   0, 0};
static const u08 tbb_gb3174[] = {255,   0, 191,   0, 191,   0, 191, 0};

static const u08 tbr_100[]    = {255, 255,   0,   0, 255, 255,   0, 0};
static const u08 tbg_100[]    = {255, 255, 255, 255,   0,   0,   0, 0};
static const u08 tbb_100[]    = {255,   0, 255,   0, 255,   0, 255, 0};

static const u08 tbr_75[]     = {191, 191,   0,   0, 191, 191,   0, 0};
static const u08 tbg_75[]     = {191, 191, 191, 191,   0,   0,   0, 0};
static const u08 tbb_75[]     = {191,   0, 191,   0, 191,   0, 191, 0};

static void line(u08 *r, u08 *g, u08 *b, const int w, const int n,
                 const u08 *tbr, const u08 *tbg, const u08 *tbb);

void sstv_colorbar1_gen(uint8_t *r, uint8_t *g, uint8_t *b,
                        const int w, const int h, const enum sstv_testcard c)
{
    int y;
    u08 *rl, *gl, *bl;
    const u08 *tbr, *tbg, *tbb;
    switch (c) {
        case SSTV_TESTCARD_COLORBAR_GB3174: tbr = tbr_gb3174, tbg = tbg_gb3174, tbb = tbb_gb3174; break;
        case SSTV_TESTCARD_COLORBAR_100:    tbr = tbr_100,    tbg = tbg_100,    tbb = tbb_100;    break;
        case SSTV_TESTCARD_COLORBAR_75:     tbr = tbr_75,     tbg = tbg_75,     tbb = tbb_75;     break;
        default: return;
    }

    for (y = 0; y < h; ++y) {
        rl = r + y * w;
        gl = g + y * w;
        bl = b + y * w;
        line(rl, gl, bl, w, 8, tbr, tbg, tbb);
    }
}

static void line(u08 *r, u08 *g, u08 *b, const int w, const int n,
                 const u08 *tbr, const u08 *tbg, const u08 *tbb)
{
    int i, j, k, l;
    l = w / n; // color bar width [px]
    for (i = j = k = 0; i < n; ++i)
        for (; j < (i + 1) * l; ++j) {
            r[j] = tbr[i];
            g[j] = tbg[i];
            b[j] = tbb[i];
            ++k;
        }
    for (; k < w; ++k)
        r[k] = g[k] = b[k] = 0;
}


