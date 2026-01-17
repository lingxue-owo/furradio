#define _CRT_SECURE_NO_WARNINGS

#include "furradio/bmp.h"
#include "common.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int bmp_write(const char* filename, const f32 *r, const f32 *g, const f32 *b,
	const int width, const int height, enum bmp_color color)
{
	int ret, i;
	u08 *rr, *gg, *bb;
	f32 t;
	rr = malloc(width * height * sizeof(u08));
	gg = malloc(width * height * sizeof(u08));
	bb = malloc(width * height * sizeof(u08));
	for (i = 0; i < width * height; ++i) {
		switch(color) {
		case BMP_24BIT_FULL:
			t=r[i]*255; if(t>255)t=255; if(t<0)t=0; rr[i]=(u08)t;
			t=g[i]*255; if(t>255)t=255; if(t<0)t=0; gg[i]=(u08)t;
			t=b[i]*255; if(t>255)t=255; if(t<0)t=0; bb[i]=(u08)t;
			break;
		case BMP_24BIT_LIMIT:
			t=r[i]*219+16; if(t>255)t=255; if(t<0)t=0; rr[i]=(u08)t;
			t=g[i]*219+16; if(t>255)t=255; if(t<0)t=0; gg[i]=(u08)t;
			t=b[i]*219+16; if(t>255)t=255; if(t<0)t=0; bb[i]=(u08)t;
			break;
		default:
			rr[i] = gg[i] = bb[i] = 0;
			break;
		}
	}
	ret = bmp_rgb_write(filename,rr,gg,bb,width,height);
	free(rr); free(gg); free(bb);
	return ret;
}

int bmp_rgb_write(const char* filename,
				  u08 *r, u08 *g, u08 *b, int width, int height)
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
