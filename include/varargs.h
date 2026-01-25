
/*
 * $VER: varargs.h 3.20.0 (23.1.2026)
 *
 * (c)Copyright 1992 Obvious Implementations Corp, All Rights Reserved
 */

#ifndef VARARGS_H
#define VARARGS_H
#ifndef STDARG_H
#include <stdarg.h>
#define va_dcl long va_alist;
#define va_start(pvar)  (pvar = (void *)(&va_alist))
#endif
#endif

