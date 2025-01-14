/*
 * $Id: stdio_gets.c,v 1.7 2022-03-27 12:04:24 clib2devs Exp $
*/

#ifndef _STDIO_HEADERS_H
#include "stdio_headers.h"
#endif /* _STDIO_HEADERS_H */

char *
gets(char *s) {
    FILE *stream = stdin;
    struct iob *file = (struct iob *) stream;
    char *result = s;
    int c;

    ENTER();

    SHOWPOINTER(s);

    assert(s != NULL);

    flockfile(stream);

    if (s == NULL) {
        SHOWMSG("invalid parameters");

        __set_errno(EFAULT);

        result = NULL;
        goto out;
    }

    /* Take care of the checks and data structure changes that
     * need to be handled only once for this stream.
     */
    if (__fgetc_check(stream) < 0) {
        result = NULL;
        goto out;
    }

    /* So that we can tell error and 'end of file' conditions apart. */
    clearerr(stream);

    while (TRUE) {
        /* If there is data in the buffer, try to copy it directly
           into the string buffer. If there is a line feed in the
           buffer, too, try to conclude the read operation. */
        if (file->iob_BufferPosition < file->iob_BufferReadBytes) {
            size_t num_bytes_in_buffer = file->iob_BufferReadBytes - file->iob_BufferPosition;
            const unsigned char *buffer = &file->iob_Buffer[file->iob_BufferPosition];
            const unsigned char *lf;

            /* Try to find a line feed character which could conclude
               the read operation if the remaining buffer data, including
               the line feed character, fit into the string buffer. */
            lf = (unsigned char *) memchr(buffer, '\n', num_bytes_in_buffer);
            if (lf != NULL) {
                size_t num_characters_in_line = ++lf - buffer;

                /* Copy the remainder of the read buffer into the
                   string buffer, including the terminating line
                   feed character. */
                memmove(s, buffer, num_characters_in_line);

                file->iob_BufferPosition += num_characters_in_line;
                s[num_characters_in_line] = 0;
                /* And that concludes the line read operation. */
                goto out;
            }

            memmove(s, buffer, num_bytes_in_buffer);
            s += num_bytes_in_buffer;

            file->iob_BufferPosition += num_bytes_in_buffer;
        }

        c = __getc(stream);
        if (c == EOF) {
            if (ferror(stream)) {
                /* Just to be on the safe side. */
                (*s) = '\0';

                result = NULL;
                goto out;
            }

            /* Make sure that we return NULL if we really
               didn't read anything at all */
            if (s == result)
                result = NULL;

            break;
        }

        if (c == '\n')
            break;

        (*s++) = c;
    }

    (*s) = '\0';

    SHOWSTRING(result);

out:

    funlockfile(stream);

    RETURN(result);
    return (result);
}
