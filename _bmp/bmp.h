#ifndef BMP_H_
#define BMP_H_

#include "../common.h"

#pragma pack(1)
struct bmp_header_t {
	// file_header, 14 bytes
	u16 type;       // 0x4D42 'BM'
	u32 file_size;  // File total size in byte
	u16 rsv1;       // 0x0000
	u16 rsv2;       // 0x0000
	u32 offset;     // 54 Start of Image data, byte

	// device_independent_bitmap_header, 40 bytes
	u32 info_size;   // 0x28 (40)
	s32 width;       // image width  px, positive left->right
	s32 height;      // image height px, positive down->up
	u16 plane;       // 0x0001
	u16 px_bit;      // 24 - 8bit BGR
	u32 compression; //  0 - no compression
	u32 img_size;  // 
	s32 x_res;       // 0 - unknown, positive px/inch, negtive px/meter
	s32 y_res;       // 0 - unknown, positive px/inch, negtive px/meter
	u32 ctb_size;    // 0 - color table not used, colors in color table 
	u32 importent;   // 0 - color table not used, key color number
};
#pragma pack()

// image_size = width x height x 3
// file_size = image_size + offset
// offset = 54
// Data: u08 B-G-R

int bmp_rgb_write(const char* filename, u08* r, u08 *g, u08 *b, int width, int height);

// testbench
void bmp_tb(void);

#endif
