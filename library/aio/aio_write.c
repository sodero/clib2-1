/*
 * $Id: aio_aio_write.c,v 1.0 2023-03-03 07:15:37 clib2devs Exp $
*/

#ifndef _STDIO_HEADERS_H
#include "stdio_headers.h"
#endif /* _STDIO_HEADERS_H */

#include <aio.h>
#include <pthread.h>
#include "aio_misc.h"

int
aio_write(struct aiocb *aiocbp) {
    return (__aio_enqueue_request((aiocb_union *) aiocbp, LIO_WRITE) == NULL ? -1 : 0);
}
