/*
 * DICE-NX project - https://dice-nx.dev/
 *
 * Copyright 1992-1997 Obvious Implementations Corp.
 * Copyright 2023- DICE-NX project contributors
 *
 * Licensed under the BSD-3-Clause License, as written in the LICENSE file
 * at the root of this project.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 *      SUPLIB/MEMORY.H
 */

#define setmem(ptr,len,c) memset(ptr,c,len)
#define movmem(s,d,len)   memcpy(d,s,len)
#define clrmem(d,n)       memset(d,0,n)
#define cmpmem(s,d,n)     bcmp(s,d,n)

