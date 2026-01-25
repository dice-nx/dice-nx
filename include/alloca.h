
/*
 * $VER: alloca.h 3.20.0 (23.1.2026)
 *
 * (c)Copyright 1992 Obvious Implementations Corp, All Rights Reserved
 */

#ifndef ALLOCA_H
#define ALLOCA_H

extern __regargs void *_dice_alloca(long);

#define alloca          _dice_alloca

#endif

