/*
 * SUPLIB/MEMORY.H
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp.
 */

#define setmem(ptr,len,c) memset(ptr,c,len)
#define movmem(s,d,len)   memcpy(d,s,len)
#define clrmem(d,n)       memset(d,0,n)
#define cmpmem(s,d,n)     bcmp(s,d,n)

