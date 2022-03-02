/*
 * $Id: math_frexp.c,v 1.6 2006-01-08 12:04:23 obarthel Exp $
 *
 * :ts=4
 *
 * Portable ISO 'C' (1994) runtime library for the Amiga computer
 * Copyright (c) 2002-2015 by Olaf Barthel <obarthel (at) gmx.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   - Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   - Neither the name of Olaf Barthel nor the names of contributors
 *     may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * PowerPC math library based in part on work by Sun Microsystems
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 */

#ifndef _MATH_HEADERS_H
#include "math_headers.h"
#endif /* _MATH_HEADERS_H */

static const double
	two54 = 1.80143985094819840000e+16; /* 0x43500000, 0x00000000 */

INLINE STATIC double
__frexp(double x, int *eptr)
{
	int hx, ix, lx;

	EXTRACT_WORDS(hx, lx, x);

	ix = 0x7fffffff & hx;
	*eptr = 0;

	if (ix >= 0x7ff00000 || ((ix | lx) == 0))
		return x;		 /* 0,inf,nan */
	if (ix < 0x00100000) /* subnormal */
	{
		x *= two54;
		GET_HIGH_WORD(hx, x);
		ix = hx & 0x7fffffff;
		*eptr = -54;
	}

	*eptr += (ix >> 20) - 1022;

	hx = (hx & 0x800fffff) | 0x3fe00000;
	SET_HIGH_WORD(x, hx);

	return x;
}

double
frexp(double x, int *nptr)
{
	double result;

	assert(nptr != NULL);

	if (nptr == NULL)
	{
		__set_errno(EFAULT);

		result = __get_huge_val();
		goto out;
	}

	if (x != 0.0)
	{
		result = __frexp(x, nptr);
	}
	else
	{
		result = 0.0;

		(*nptr) = 0;
	}

out:

	return (result);
}