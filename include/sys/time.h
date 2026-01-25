
/*
 * $VER: sys/time.h 3.20.0 (23.1.2026)
 * (c)Copyright 1992 Obvious Implementations Corp, All Rights Reserved
 */

#ifndef SYS_TIME_H
#define SYS_TIME_H

#include <time.h>

struct timeval {
    unsigned long   tv_sec;
    unsigned long   tv_usec;
};

#define timerisset(tvp)         ((tvp)->tv_sec || (tvp)->tv_usec)
#define timercmp(tvp, uvp, cmp) \
        ((tvp)->tv_sec cmp (uvp)->tv_sec || \
         (tvp)->tv_sec == (uvp)->tv_sec && (tvp)->tv_usec cmp (uvp)->tv_usec)
#define timerclear(tvp)         (tvp)->tv_sec = (tvp)->tv_usec = 0

#endif

