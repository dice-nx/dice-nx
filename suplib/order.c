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
 * ORDER.C
 */

#ifdef INTELBYTEORDER

unsigned int
FromMsbOrder(unsigned int n)
{
    n = ((n & 0x000000FF) << 24) |
        ((n & 0x0000FF00) << 8) |
        ((n & 0x00FF0000) >> 8) |
        ((n & 0xFF000000) >> 24);
    return(n);
}

unsigned int
ToMsbOrder(unsigned int n)
{
    n = ((n             ) << 24) |
        ((n & 0x0000FF00) << 8) |
        ((n & 0x00FF0000) >> 8) |
        ((n             ) >> 24);
    return(n);
}

unsigned short
FromMsbOrderShort(unsigned short n)
{
    n = (n << 8) | (n >> 8);
    return(n);
}

unsigned short
ToMsbOrderShort(unsigned short n)
{
    n = (n << 8) | (n >> 8);
    return(n);
}

#endif

