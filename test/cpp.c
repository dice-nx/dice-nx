/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

#define F1(x)  F2(x)
#define F2(x)  F1(x)

F1(fubar);    F2(fubar)

#define MAX(a,b)    (a,b)

MAX(MAX(1,2),3);

#define FUBAR(x)    (x)

FUBAR(FUBAR(4));

#define BAR(x)  BAR(1,x,2,BAR(99))

BAR(3);

BAR(BAR(4));

