/*
 * $Id: stdio_growiobtable.c,v 1.9 2006-01-08 12:04:24 clib2devs Exp $
*/

#ifndef _STDIO_HEADERS_H
#include "stdio_headers.h"
#endif /* _STDIO_HEADERS_H */

#ifndef _STDLIB_MEMORY_H
#include "stdlib_memory.h"
#endif /* _STDLIB_MEMORY_H */

int __grow_iob_table(int max_iob) {
    const int granularity = 10;
    int new_num_iob;
    int result = ERROR;

    if (max_iob == 0)
        new_num_iob = __num_iob + granularity;
    else
        new_num_iob = max_iob;

    if (new_num_iob > __num_iob) {
        struct iob **new_iob;
        int i;

        new_iob = malloc(sizeof(*new_iob) * new_num_iob);
        if (new_iob == NULL) {
            SHOWMSG("not enough memory for file table");

            __set_errno(ENOMEM);
            goto out;
        }

        for (i = __num_iob; i < new_num_iob; i++) {
            new_iob[i] = malloc(sizeof(*new_iob[i]));
            if (new_iob[i] == NULL) {
                int j;

                SHOWMSG("not enough memory for file table entry");

                for (j = __num_iob; j < i; j++)
                    free(new_iob[j]);

                free(new_iob);

                __set_errno(ENOMEM);
                goto out;
            }

            memset(new_iob[i], 0, sizeof(*new_iob[i]));
        }

        if (__iob != NULL) {
            for (i = 0; i < __num_iob; i++)
                new_iob[i] = __iob[i];

            free(__iob);
        }

        __iob = new_iob;
        __num_iob = new_num_iob;
    }

    result = OK;

out:

    return (result);
}
