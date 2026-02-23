/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 *
 * _AbortLockout global, accessed by setjmp/setjmp.a and amiga/chkabort.c,
 * locks out ^C aborting
 */

__near short _AbortLockout;

