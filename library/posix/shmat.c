/*
 * $Id: shm_shmat.c,v 1.1 2021-01-26 12:28:14 clib2devs Exp $
*/

#ifdef HAVE_SYSV

#ifndef _SHM_HEADERS_H
#include "shm_headers.h"
#endif /* _SHM_HEADERS_H */

void *
_shmat(int shmid, const void *prefadds, int flags)
{
    DECLARE_SYSVYBASE();

    ENTER();

    SHOWVALUE(shmid);
    SHOWPOINTER(prefadds);
    SHOWVALUE(flags);

    if (__global_clib2->haveShm)
    {
        void *ret;
        ret = shmat(shmid, prefadds, flags);
        if (ret == ((void *)-1))
        {
            __set_errno(GetIPCErr());
        }
        RETURN(ret);
        return ret;
    }
    else
    {
        __set_errno(ENOSYS);
        RETURN(NULL);
        return NULL;
    }
}

#endif