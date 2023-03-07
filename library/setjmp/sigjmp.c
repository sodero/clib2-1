/* Copyright (C) 1992-2023 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#ifndef _SIGNAL_HEADERS_H
#include "signal_headers.h"
#endif /* _SIGNAL_HEADERS_H */

/* This function is called by the `sigsetjmp' macro
   before doing a `__setjmp' on ENV[0].__jmpbuf.
   Always return zero.  */

int
__sigjmp_save(sigjmp_buf env, int savemask) {
    ENTER();
    SHOWVALUE(savemask);
    env[0].__mask_was_saved = (savemask
                               && sigprocmask(SIG_BLOCK, (sigset_t *) NULL,
                                                (sigset_t * ) & env[0].__saved_mask) == 0);

    SHOWVALUE(env[0].__mask_was_saved);
    RETURN(0);
    return 0;
}
