/*
 * $Id: math_log10.c,v 1.9 2021-01-31 11:23:53 clib2devs Exp $
*/

#ifndef _MATH_HEADERS_H
#include "math_headers.h"
#endif /* _MATH_HEADERS_H */

static const double
	two54 = 1.80143985094819840000e+16,		/* 0x43500000, 0x00000000 */
	ivln10 = 4.34294481903251816668e-01,	/* 0x3FDBCB7B, 0x1526E50E */
	log10_2hi = 3.01029995663611771306e-01, /* 0x3FD34413, 0x509F6000 */
	log10_2lo = 3.69423907715893078616e-13, /* 0x3D59FEF3, 0x11F12B36 */
	zero = 0.0;

double
log10(double x)
{
    double y, z;
    int i, k, hx;
    unsigned int lx;

    EXTRACT_WORDS(hx, lx, x);

    k = 0;
    if (hx < 0x00100000) /* x < 2**-1022  */
    {
        if (((hx & 0x7fffffff) | lx) == 0)
            return -two54 / zero; /* log(+-0)=-inf */
        if (hx < 0)
            return (x - x) / zero; /* log(-#) = NaN */
        k -= 54;
        x *= two54; /* subnormal number, scale up x */
        GET_HIGH_WORD(hx, x);
    }

    if (hx >= 0x7ff00000)
        return x + x;

    k += (hx >> 20) - 1023;
    i = ((unsigned int)k & 0x80000000) >> 31;
    hx = (hx & 0x000fffff) | ((0x3ff - i) << 20);
    y = (double)(k + i);
    SET_HIGH_WORD(x, hx);
    z = y * log10_2lo + ivln10 * log(x);

    return z + y * log10_2hi;
}
