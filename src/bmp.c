#define _CRT_SECURE_NO_WARNINGS

#include "furradio/bmp.h"
#include "common.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int bmp_rgb_write(const char* filename, u08 *r, u08 *g, u08 *b, int width, int height)
{
	int i, j, k, len;
	FILE* fp;
	u08* buff;
	struct bmp_header_t h = {0};

	len = width * 3;
	len += (len % 4) ? (4 - len % 4) : 0;

	buff = malloc(len); 	
	if (!buff) return -1;
	memset(buff, 0, len);

	fp = fopen(filename, "wb");
	if (!fp)   return -1;

	h.type      = 0x4d42;
	h.offset    = 54;
	h.info_size = 40;
	h.plane     = 1;
	h.px_bit    = 24;

	h.width     = width;
	h.height    = height;
	h.img_size  = width * height * 3;
	h.file_size = h.img_size + h.offset;

	fwrite(&h, sizeof(h), 1, fp);

	for (i = 0; i < height; ++i) {
		for (j = 0; j < width; ++j) {
			k = i * width + j;
			*(buff + 3*j    ) = b[k];
			*(buff + 3*j + 1) = g[k];
			*(buff + 3*j + 2) = r[k];
		}
		fwrite(buff, 1, len, fp);
	}

	fclose(fp);
	free(buff);
	return 0;
}
