
/*
 * $VER: lib/wild.h 3.20.0 (23.1.2026)
 *
 * (c)Copyright 1992 Obvious Implementations Corp, All Rights Reserved
 */

#ifndef _LIB_WILD_H
#define _LIB_WILD_H

extern void *_ParseWild(const char *, short)
extern int _CompWild(const char *, void *, void *);
extern void _FreeWild(void *);

#endif
