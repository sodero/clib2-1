/* $Id: socket_res_state.c,v 1.0 2022-03-14 10:44:15 clib2devs Exp $
 */

#include <resolv.h>

/* This is completely unused, and exists purely to satisfy broken apps. */

struct __res_state *__res_state() {
    static struct __res_state res;
    return &res;
}