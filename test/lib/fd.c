/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

#include <fcntl.h>
#include <errno.h>

main(ac, av)
char *av[];
{
    int fd = open(av[1], O_RDWR|O_CREAT|O_TRUNC);
    if (fd < 0)
        printf("Unable to open %s, code %d\n", av[1], errno);
    errno = 0;
    write(fd, "foo", sizeof("foo") - 1);
    printf("errno %d\n", errno);
    close(fd);
}

