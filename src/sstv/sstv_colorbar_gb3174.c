#include "furradio/sstv.h"
#include "common.h"

//                                W    Y    C    G    M    R    B   K
static const float tbr_gb[] = {1., .75,  0.,  0., .75, .75,  0., 0.,};
static const float tbg_gb[] = {1., .75, .75, .75,  0.,  0.,  0., 0.,};
static const float tbb_gb[] = {1.,  0., .75,  0., .75,  0., .75, 0.,};

static const float tbr_100[] = {1, 1, 0, 0, 1, 1, 0, 0,};
static const float tbg_100[] = {1, 1, 1, 1, 0, 0, 0, 0,};
static const float tbb_100[] = {1, 0, 1, 0, 1, 0, 1, 0,};

static const float tbr_75[]  = {.75, .75,  0.,  0., .75, .75,  0., 0.,};
static const float tbg_75[]  = {.75, .75, .75, .75,  0.,  0.,  0., 0.,};
static const float tbb_75[]  = {.75,  0., .75,  0., .75,  0., .75, 0.,};

static void line(f32 *r, f32 *g, f32 *b, const int w, const int n,
                 const f32 *tbr, const f32 *tbg, const f32 *tbb);

void sstv_colorbar1_gen(float *r, float *g, float *b,
                        const int w, const int h, const enum sstv_testcard c)
{
    int y;
    float *rl, *gl, *bl;
    const float *tbr, *tbg, *tbb;
    switch (c) {
        case SSTV_TESTCARD_COLORBAR_GB3174:
            tbr = tbr_gb,  tbg = tbg_gb,  tbb = tbb_gb;  break;
        case SSTV_TESTCARD_COLORBAR_100:
            tbr = tbr_100, tbg = tbg_100, tbb = tbb_100; break;
        case SSTV_TESTCARD_COLORBAR_75:
            tbr = tbr_75,  tbg = tbg_75,  tbb = tbb_75;  break;
        default: return;
    }
    for (y = 0; y < h; ++y) {
        rl = r + y * w;
        gl = g + y * w;
        bl = b + y * w;
        line(rl, gl, bl, w, 8, tbr, tbg, tbb);
    }
}

static void line(f32 *r, f32 *g, f32 *b, const int w, const int n,
                 const f32 *tbr, const f32 *tbg, const f32 *tbb)
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


