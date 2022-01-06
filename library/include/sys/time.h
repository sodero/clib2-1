#ifndef _SYS_TIME_H
#define _SYS_TIME_H

#include <features.h>

__BEGIN_DECLS

#if !defined(__TIMEVAL_ALREADY_DEFINED)
struct timeval
{
	unsigned long tv_secs;
	unsigned long tv_micro;
};

/* Make sure that the 'struct timeval' is not redefined, should <devices/timer.h> get included again. */
#define __TIMEVAL_ALREADY_DEFINED
#endif /* !__TIMEVAL_ALREADY_DEFINED */

struct timezone
{
    int tz_minuteswest; /* of Greenwich */
    int tz_dsttime;     /* type of dst correction to apply */
};

#define DST_NONE 0 /* not on dst */
#define DST_USA 1  /* USA style dst */
#define DST_AUST 2 /* Australian style dst */
#define DST_WET 3  /* Western European dst */
#define DST_MET 4  /* Middle European dst */
#define DST_EET 5  /* Eastern European dst */
#define DST_CAN 6  /* Canada */

extern int gettimeofday(struct timeval *tp, struct timezone *tzp);

#ifdef __USE_GNU
/* Macros for converting between `struct timeval' and `struct timespec'.  */
#define TIMEVAL_TO_TIMESPEC(tv, ts)           \
    {                                         \
        (ts)->tv_sec = (tv)->tv_sec;          \
        (ts)->tv_nsec = (tv)->tv_usec * 1000; \
    }
#define TIMESPEC_TO_TIMEVAL(tv, ts)           \
    {                                         \
        (tv)->tv_sec = (ts)->tv_sec;          \
        (tv)->tv_usec = (ts)->tv_nsec / 1000; \
    }
#endif

__END_DECLS

#endif