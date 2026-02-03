/*
 * TEST.C
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#if FOO || BAR
#error "FOO || BAR"
#else
#error "!(FOO || BAR)"
#endif

#if FOO
#error "FOO"
#else
#error "!FOO"
#endif
