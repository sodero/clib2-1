/*
 * $Id: stdio_findvacantiobentry.c,v 1.5 2006-01-08 12:04:24 clib2devs Exp $
*/

#ifndef _STDIO_HEADERS_H
#include "stdio_headers.h"
#endif /* _STDIO_HEADERS_H */

#ifndef NDEBUG

BOOL __is_valid_iob(struct iob *iob) {
    BOOL result = FALSE;
    ENTER();
    SHOWPOINTER(iob);
    struct _clib2 *__clib2 = __CLIB2;

    if (iob == NULL) {
        SHOWMSG("iob is NULL");
        RETURN(result);
        return result;
    }

    if (FLAG_IS_SET(iob->iob_Flags, IOBF_INTERNAL)) {
        /* This is used by vsprintf(), etc. */
        result = TRUE;
    } else {
        SHOWMSG("Locking stdio");
        __stdio_lock();
        D(("__num_iob = %ld", __clib2->__num_iob));
        D(("iob->iob_SlotNumber = %ld", iob->iob_SlotNumber));
        SHOWPOINTER(__clib2->__iob[iob->iob_SlotNumber]);

        if (__clib2->__num_iob > 0 && 0 <= iob->iob_SlotNumber && iob->iob_SlotNumber < __clib2->__num_iob && __clib2->__iob[iob->iob_SlotNumber] == iob)
            result = TRUE;

        SHOWMSG("Unlock stdio");
        __stdio_unlock();
    }

    RETURN(result);
    return result;
}

#endif /* NDEBUG */

int __find_vacant_iob_entry(void) {
    int result = ERROR;
    int i;
    struct _clib2 *__clib2 = __CLIB2;

    assert(__clib2->__iob != NULL || __clib2->__num_iob == 0);

    for (i = 0; i < __clib2->__num_iob; i++) {
        if (FLAG_IS_CLEAR(__clib2->__iob[i]->iob_Flags, IOBF_IN_USE)) {
            result = i;
            break;
        }
    }

    return (result);
}
