#include "furradio/sstv.h"
#include "common.h"

void sstv_rgb2ycbcr_bt601(float *rcr, float *gy, float *bcb, const int wxh)
{
    int i;
    float r,g,b,y,cb,cr;
    for (i = 0; i < wxh; ++i) {
        r  = rcr[i]; g = gy[i]; b = bcb[i];
        y  = +0.299 *r +0.587 *g +0.114 *b;
        cb = -0.1687*r -0.3313*g +0.5000*b;
        cr =  0.5000*r -0.4187*g -0.0813*b;
        gy[i] = y; bcb[i] = cb; rcr[i] = cr;
    }
}

void sstv_ycbcr2rgb_bt601(float *rcr, float *gy, float *bcb, const int wxh)
{
    int i;
    float r,g,b,y,cb,cr;
    for (i = 0; i < wxh; ++i) {
        y  = gy[i]; cb = bcb[i]; cr = rcr[i];
        r  =  1. * y -1.2189e-06 * cb +1.4020e+00 * cr;
        g  =  1. * y -3.4413e-01 * cb -7.1411e-01 * cr;
        b  =  1. * y +1.7720e+00 * cb -1.3458e-04 * cr;
        rcr[i] = r; gy[i] = g; bcb[i] = b;
    }
}

void sstv_rgb2ycbcr_bt709(float *rcr, float *gy, float *bcb, const int wxh)
{
    int i;
    float r,g,b,y,cb,cr;
    for (i = 0; i < wxh; ++i) {
        r  = rcr[i]; g = gy[i]; b = bcb[i];
        y  =  0.2126 * r +0.7152 * g + 0.0722 * b;
        cb = -0.1146 * r -0.3854 * g + 0.5000 * b;
        cr =  0.5000 * r -0.4542 * g - 0.0458 * b;
        gy[i] = y; bcb[i] = cb; rcr[i] = cr;
    }
}

void sstv_ycbcr2rgb_bt709(float *rcr, float *gy, float *bcb, const int wxh)
{
    int i;
    float r,g,b,y,cb,cr;
    for (i = 0; i < wxh; ++i) {
        y  = gy[i]; cb = bcb[i]; cr = rcr[i];
        r  =  1. * y -1.5150e-4 * cb + 1.57478   * cr;
        g  =  1. * y -1.8728e-1 * cb - 4.6812e-1 * cr;
        b  =  1. * y +1.8556    * cb + 1.0574e-4 * cr;
        rcr[i] = r; gy[i] = g; bcb[i] = b;
    }
}











