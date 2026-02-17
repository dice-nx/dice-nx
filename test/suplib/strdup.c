/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

#include <stdlib.h>
#include <string.h>

char *
strdup(const char *str)
{
    char *ptr;
    
    if (ptr = malloc(strlen(str) + 1))
        strcpy(ptr, str);
    return(ptr);
}

