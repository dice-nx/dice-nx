
/*
 *  $VER: stdarg.h 3.20.0 (23.1.2026)
 *
 * (c)Copyright 1992 Obvious Implementations Corp, All Rights Reserved
 */

#ifndef STDARG_H
#define STDARG_H

#ifndef STDIO_H
typedef void *va_list;
#endif

#define va_arg(valist,typename) ((valist = (void *)((char *)valist + sizeof(typename))), (*(typename *)((char *)(valist) - sizeof(typename))))
#define va_start(valist,right)  (valist = (void*)((char *)&right + sizeof(right)))
#define va_end(valist)
#define va_copy(dest,src) (dest = src)

#endif
