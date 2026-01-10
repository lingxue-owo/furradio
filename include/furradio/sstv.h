
#ifndef SSTV_H_
#define SSTV_H_

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

int sstv_line_get(enum sstv_type type);
enum sstv_ratio sstv_ratio_get(enum sstv_type type);

#endif
