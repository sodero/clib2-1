/*
 * $Id: debug_kputstr2.c,v 1.3 2006-01-08 12:04:22 clib2devs Exp $
*/

#include "debug_headers.h"

void
KPutStr(const UBYTE * s)
{
	assert( s != NULL );

	kputstr(s);
}
