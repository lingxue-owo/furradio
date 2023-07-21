#include <math.h>
#include "ft8_enc.h"

#define DEBUG_ 1
#if DEBUG_
#include <stdio.h>
#endif

#define STD_CODE_FREQ 6.25 /* FT8 symb T=0.160ms, f = 6.25 Hz */
#define SYMB_LENGTH   79   /* FT8 symb length, 79symb x 160ms = 12.640s */

static f64 fs, f0;
static const u08 *symb;
static u32 carr_nco;
static u32 symb_nco;
static int symb_cnt;

static double gfsk(u32 symb_phi, int flag);
static double rcos(u32 symb_phi);
static double dcos(u32 symb_phi);

int ft8_wave_init(const u08 *symbol, const f64 if_freq, const f64 fs_freq)
{
	fs = fs_freq;
	f0 = if_freq;
	symb = symbol;
	carr_nco = 0;
	symb_nco = 0;
	symb_cnt = 0;
	return 0;
}

s16 ft8_wave_getsample()
{
	u32 carr_fdw, symb_fdw;
	u32 carr_nco_new, symb_nco_new;
	s08 symb_last, symb_curr, symb_next;
	double df, df_last, df_curr, df_next,amp, ret;
	double carr_dop = 0, symb_dop = 0;
	// Doppler, symb_dop = carr_dop * (symb_freq/carr_freq)
	// Doppler offset not used here, set them to zero

	/* get symbols */
	if (symb_cnt < SYMB_LENGTH) {
		symb_last = (symb_cnt == 0) ? 3 : symb[symb_cnt-1];
		symb_curr = symb[symb_cnt];
		symb_next = (symb_cnt == SYMB_LENGTH-1) ?
				symb[SYMB_LENGTH-1] : symb[symb_cnt+1];
	} else {
		symb_last = symb_curr = symb_next = 0;
	}

	/* get carr/code freq, and NCO freq ctrl double word (fdw) */
	df_last = symb_last * gfsk(symb_nco, +1);
	df_curr = symb_curr * gfsk(symb_nco, 0);
	df_next = symb_next * gfsk(symb_nco, -1);
	df = df_last + df_curr + df_next;
	carr_fdw = (u32)((f0 + df + carr_dop) / fs * NCOFS);
	symb_fdw = (u32)((STD_CODE_FREQ + symb_dop) / fs * NCOFS);

	/* NCO acc */
	carr_nco_new = carr_nco + carr_fdw;
	symb_nco_new = symb_nco + symb_fdw;

	/* get amptitude */
	switch (symb_cnt) {
	case 0                : amp = rcos(symb_nco); break;
	case (SYMB_LENGTH - 1): amp = dcos(symb_nco); break;
	default               : amp = 1.0; break;
	}

	/* phase LUT(loop-up table) generate wave */
	ret = amp * cos(2 * M_PI * carr_nco / NCOFS);

#if DEBUG_
	printf("freq %lf %lf %lf %lf %lf ", df_last, df_curr, df_next, df, f0+df);
	printf("symbcnt %d amp %lf ", symb_cnt, amp);
	printf("symb %d %d %d %d ", symb_cnt, symb_last, symb_curr, symb_next);
	printf("nco %lf %lf ret %lf", symb_nco/NCOFS, carr_nco/NCOFS, ret);
	printf("\n");
#endif

	/* process NCO overflow, update NCO */
	if (symb_nco_new < symb_nco)
		symb_cnt++;
	symb_nco = symb_nco_new;
	carr_nco = carr_nco_new;
	return (s16)(ret * 32767);
}

static double gfsk(u32 nco, int flag)
{
	double x = nco / NCOFS + flag;
	return (6.25/2.0) * (erf(5.336*2*x) - erf(5.336*2*(x-1)));
}

static double rcos(u32 nco)
{
	if (nco > (u32)(NCOFS / 8.))
		return 1.0;
	double x = nco / NCOFS;
	return .5*(1-cos(8 * M_PI * x));
}

static double dcos(u32 phi)
{
	if (phi < (u32)(NCOFS * 7./8.))
		return 1.0;
	double x = phi / NCOFS;
	return .5*(1-cos(8 * M_PI * (1-x)));
}


