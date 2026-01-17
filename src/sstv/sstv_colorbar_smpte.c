#include "furradio/sstv.h"
#include "common.h"

void sstv_cbsmpte_gen(
    uint8_t *y, uint8_t *cb, uint8_t *cr, const int w, const int h)
{
    int l;
    u08 *yl, *cbl, *crl;
    for (l = 0; l < h; ++l) {
        yl  = y  + l * w;
        cbl = cb + l * w;
        crl = cr + l * w;
//        line(yl, cbl, crl, w);
    }
}

//static void ()
