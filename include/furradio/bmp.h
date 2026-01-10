#ifndef BMP_H_
#define BMP_H_

#include <stdint.h>

#pragma pack(1)
struct bmp_header_t {
	// file_header, 14 bytes
	uint16_t type;       // 0x4D42 'BM'
	uint32_t file_size;  // File total size in byte
	uint16_t rsv1;       // 0x0000
	uint16_t rsv2;       // 0x0000
	uint32_t offset;     // 54 Start of Image data, byte

	// device_independent_bitmap_header, 40 bytes
	uint32_t info_size;   // 0x28 (40)
	 int32_t width;       // image width  px, positive left->right
	 int32_t height;      // image height px, positive down->up
	uint16_t plane;       // 0x0001
	uint16_t px_bit;      // 24 - 8bit BGR
	uint32_t compression; //  0 - no compression
	uint32_t img_size;    //
	 int32_t x_res;       // 0 - unknown, positive px/inch, negtive px/meter
	 int32_t y_res;       // 0 - unknown, positive px/inch, negtive px/meter
	uint32_t ctb_size;    // 0 - color table not used, colors in color table
	uint32_t importent;   // 0 - color table not used, key color number
};
#pragma pack()

// image_size = width x height x 3
// file_size = image_size + offset
// offset = 54
// Data: u08 B-G-R

int bmp_rgb_write(const char* filename,
				  uint8_t* r, uint8_t *g, uint8_t *b,
				  int width, int height);

// testbench
void bmp_tb(void);

#endif
