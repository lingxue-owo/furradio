#include "furradio/sstv.h"

int sstv_line_get(enum sstv_type type)
{
    switch (type) {
        case SSTV_MART_1: case SSTV_MART_2:
        case SSTV_SCOT_1: case SSTV_SCOT_2: case SSTV_SCOT_DX:
            return 256;
        case SSTV_MART_3: case SSTV_MART_4:
        case SSTV_SCOT_3: case SSTV_SCOT_4:
            return 128;
        case SSTV_PD_120:
            return 496;
        case SSTV_AVT_90:
        case SSTV_ROBOT_36: case SSTV_ROBOT_72:
            return 240;
        case SSTV_AVT_94:
            return 200;

        case SDTV_NTSC_M: return 482;
        case SDTV_PAL_D:  return 576;
        case HDTV_720:    return 720;
        case HDTV_1080:   return 1080;
        case HDTV_4K:     return 2160;
        case HDTV_8K:     return 4320;
        default: return 0;
    }
}

enum sstv_ratio  sstv_ratio_get(enum sstv_type type)
{
    switch (type) {
        case SSTV_MART_1: case SSTV_MART_2: case SSTV_MART_3: case SSTV_MART_4:
        case SSTV_SCOT_1: case SSTV_SCOT_2: case SSTV_SCOT_3: case SSTV_SCOT_4:
        case SSTV_SCOT_DX:
        case SSTV_PD_120:
        case SSTV_AVT_90:   case SSTV_AVT_94:
        case SSTV_ROBOT_36: case SSTV_ROBOT_72:
        case SDTV_NTSC_M:   case SDTV_PAL_D:
            return SSTV_RATIO_43;
        case HDTV_720: case HDTV_1080: case HDTV_4K: case HDTV_8K:
            return SSTV_RATIO_169;
        default: return SSTV_RATIO_11;
    }
}
