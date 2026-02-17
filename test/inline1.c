/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

#include <protos/exec_protos.h>

main(ac, av)
char *av[];
{
    struct Task *task;

    task = FindTask(av[1]);
    printf("task = %08lx\n", task);
    return(0);
}
