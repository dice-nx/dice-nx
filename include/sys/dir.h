/*
 * $VER: sys/dir.h 3.20.0 (23.1.2026)
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992 Obvious Implementations Corp
 */

#ifndef SYS_DIR_H
#define SYS_DIR_H

#define MAXPATHLEN  1024
#define MAXNAMLEN   256

typedef struct DIR {
    long    am_Private;
} DIR;

struct direct {
    char    *d_name;
    short   d_namlen;
    short   d_reserved;
    long    d_ino;
};

struct dirent {
    char    *d_name;
    short   d_namlen;
    short   d_reserved;
    long    d_ino;
};


DIR *opendir(const char *);
struct direct *readdir(DIR *);
int rewinddir(DIR *);
int closedir(DIR *);

#endif
