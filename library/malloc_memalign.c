/*
 * $Id: malloc_memalign.c,v 1.0 2021-01-10 10:52:18 apalmate Exp $
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
 *****************************************************************************
 *
 * Documentation and source code for this library, and the most recent library
 * build are available from <http://sourceforge.net/projects/clib2>.
 *
 *****************************************************************************
 */

#ifndef _STDLIB_HEADERS_H
#include "stdlib_headers.h"
#endif /* _STDLIB_HEADERS_H */

#ifndef _STDIO_HEADERS_H
#include "stdio_headers.h"
#endif /* _STDIO_HEADERS_H */

#include <stdint.h>
#include <malloc.h>

struct alignlist
{
   struct alignlist *next;
   void *aligned;  /* The address that mmemaligned returned.  */
   void *exact;    /* The address that malloc returned.  */
};
static struct alignlist *_aligned_blocks = NULL;

void *memalign(size_t alignment, size_t size)
{
    void *result;
    unsigned long int adj;

    size = ((size + alignment - 1) / alignment) * alignment;

    result = malloc(size);
    if (result == NULL)
        return NULL;

    adj = (unsigned long int)((unsigned long int)((char *)result - (char *)NULL)) % alignment;
    if (adj != 0)
    {
        struct alignlist *l;
        for (l = _aligned_blocks; l != NULL; l = l->next) {
            /* This slot is free.  Use it.  */
            if (l->aligned == NULL) {
                break;
            }
        }
        if (l == NULL)
        {
            l = (struct alignlist *)malloc(sizeof(struct alignlist));
            if (l == NULL)
            {
                free(result);
                return NULL;
            }
        }
        l->exact = result;
        result = l->aligned = (char *)result + alignment - adj;
        l->next = _aligned_blocks;
        _aligned_blocks = l;
    }

    return result;
}