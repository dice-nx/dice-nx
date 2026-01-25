
/*
 * $VER: lib/atexit.h 3.20.0 (23.1.2026)
 *
 * (c)Copyright 1992 Obvious Implementations Corp, All Rights Reserved
 */

#ifndef _LIB_ATEXIT_H
#define _LIB_ATEXIT_H

typedef struct AtExit {
    struct  AtExit *Next;
    void (*Func)(void);
} AtExit;

extern AtExit *_ExitBase;

#endif

