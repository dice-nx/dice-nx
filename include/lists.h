
/*
 *  $VER: lists.h 3.20.0 (23.1.2026)
 *
 * (c)Copyright 1992 Obvious Implementations Corp, All Rights Reserved
 */

#ifndef LISTS_H
#define LISTS_H

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif

extern void *GetHead(void *);
extern void *GetTail(void *);
extern void *GetSucc(void *);
extern void *GetPred(void *);

#endif

