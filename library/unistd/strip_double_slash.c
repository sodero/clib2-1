/*
 * $Id: unistd_strip_double_slash.c,v 1.4 2006-01-08 12:04:27 clib2devs Exp $
*/

#ifndef _UNISTD_HEADERS_H
#include "unistd_headers.h"
#endif /* _UNISTD_HEADERS_H */

/* Remove '//' from an AmigaDOS path name. For example, "volume:one/two//three"
   is equivalent to "volume:one/three" and the following function removes the
   redundant part of the path. */
int
__strip_double_slash(char *file_name, int len) {
    int position;

    position = len;

    while (len > 1) {
        position--;

        /* Stop when we hit the volume name or the first character of the name. */
        if ((position == 0) || (file_name[position] == ':') || (file_name[position - 1] == ':'))
            break;

        /* Do we have a // embedded in the file_name? That // must stand alone
           between directory names and not in front of a volume name or
           yet another /. */
        if ((position > 1) && (file_name[position] == '/' && file_name[position - 1] == '/') &&
            (file_name[position - 2] != ':' && file_name[position - 2] != '/')) {
            int start, delta;

            start = position;

            /* Back up behind the //. */
            position -= 2;

            /* Find the spot where the previous directory or volume
               name begins. */
            while ((position > 0) && (file_name[position] != ':') && (file_name[position] != '/'))
                position--;

            /* Don't move too far. */
            if ((file_name[position] == ':') || (file_name[position] == '/'))
                position++;

            /* Find out how long the directory name is that
               we are going to remove now. */
            delta = start - position + 1;

            /* Remove the file_name part; we copy one more byte than
               necessary to account for the NUL at the end. */
            len -= delta;

            memmove(&file_name[position], &file_name[position + delta], len - position + 1);

            /* The string is shorter, and here we go again... */
            position = len;
        }
    }

    return (len);
}
