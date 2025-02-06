
/*
 * $VER: lib/version.h 1.0 (17.4.93)
 *
 * (c)Copyright 1992 Obvious Implementations Corp, All Rights Reserved
 */

#ifndef _LIB_VERSION_H
#define _LIB_VERSION_H

#define MAJOR_VERSION 3
#define MINOR_VERSION 20
#define PATCH_VERSION 0

#ifndef __COMMODORE_DATE__
#define __COMMODORE_DATE__ __DATE__
#endif

#define _STRING(label)          #label
#define _STRING_EVAL(label)     _STRING(label)

#define DICE_NX_ID "DICE-NX " _STRING_EVAL(MAJOR_VERSION) "." _STRING_EVAL(MINOR_VERSION) "." _STRING_EVAL(PATCH_VERSION)

#define DCOPYRIGHT static char *DCopyright = \
    "DICE-NX project - https://dice-nx.dev\n" \
    "Copyright 1992-2023 Obvious Implementations Corp.\n" \
    "Copyright 2023- DICE-NX project contributors.\n" \
    "Redistribution & Use under BSD-3-Clause License." \
    VERSTAG " from " DICE_NX_ID

#define INSTDIR                 _STRING_EVAL(_INSTDIR)

#ifdef AMIGA
#define DCC             "dcc:"
#define DCC_CONFIG      "dcc_config:"
#else
#define DCC             INSTDIR
#define DCC_CONFIG      DCC "config/"
#endif

#ifdef INTELBYTEORDER
#define FromMsbOrder(n) ( (((n)&0xff000000)>>24) | (((n)&0x00ff0000)>>8) | (((n)&0x0000ff00)<<8) | (((n)&0x000000ff)<<24) )
#define ToMsbOrder(n)   ( (((n)&0xff000000)>>24) | (((n)&0x00ff0000)>>8) | (((n)&0x0000ff00)<<8) | (((n)&0x000000ff)<<24) )
#define FromMsbOrderShort(n) ((((n)&0x00ff)<<8) | (((n)&0xff00)>>8))
#define ToMsbOrderShort(n)   ((((n)&0x00ff)<<8) | (((n)&0xff00)>>8))
#else
#define FromMsbOrder(n)         (n)
#define ToMsbOrder(n)           (n)
#define FromMsbOrderShort(n)    (n)
#define ToMsbOrderShort(n)      (n)
#endif

#endif
