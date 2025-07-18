#include "bmp.h"


#define SIZE 256

#define W (SIZE+128+1)
#define H (SIZE)

void bmp_tb(void)
{
	int i, j;
	static u08 r[H][W];
	static u08 g[H][W];
	static u08 b[H][W];

	for (i = 0; i < H; ++i) {
		for (j = 0; j < W; ++j) {
			r[i][j] = i % 256;
			g[i][j] = j % 256;
			b[i][j] = 128;
		}
	}
	bmp_rgb_write("bmp_tb0.bmp", 
		(u08*)r, (u08*)g, (u08*)b, W, H);

	for (i = 0; i < H; ++i) {
		for (j = 0; j < W; ++j) {
			r[i][j] = i;
			g[i][j] = i;
			b[i][j] = i;
		}
	}
	bmp_rgb_write("bmp_tb2.bmp", 
		(u08*)r, (u08*)g, (u08*)b, W, H);
}
