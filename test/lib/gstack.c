/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

extern char *_stack_base;

main(ac, av)
char *av[];
{
    char x;

    printf("%08lx %d\n", _stack_base, &x - _stack_base);
    deep(atoi(av[1]));
}

deep(n)
long n;
{
    char x;
    char y[200];

    printf("P %08lx %d\n", _stack_base, &x - _stack_base);
    if (n)
        deep(n-1);
    printf("F %08lx %d\n", _stack_base, &x - _stack_base);
}

void
stack_abort(void)
{
    puts("XX!");
    exit(20);
}
