/*
 * $VER: clib/dicecache_protos.h 3.20.0 (23.1.2026)
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */
#ifndef CLIB_DICECACHE_PROTOS_H
#define CLIB_DICECACHE_PROTOS_H 1

/*
 *  If DiceCacheOpen() returns NULL, *psize contains:
 */

#define PS_CACHE_DISABLED   0   /*  disabled or not read-only   */
#define PS_NO_MATCH         1
#define PS_LOCK_FAILED      2
#define PS_GENERAL_FAILURE  9

/*
 *
 */

#ifndef _DICECACHE_INTERNAL_SKIP

typedef void *CacheNode;

CacheNode *DiceCacheOpen(const char *, const char *, long *);
void DiceCacheClose(CacheNode *);
void *DiceCacheSeek(CacheNode *, long, long *);
long DiceCacheGetSuffixes(char *, long);
long DiceCacheAddSuffix(const char *);
long DiceCacheRemSuffix(const char *);
void DiceCacheFlush(long);
void DiceCacheSet(long *, long);
void DiceCacheGet(long *, long);
void DiceCacheEnable(void);
void DiceCacheDisable(void);

#endif
#endif
