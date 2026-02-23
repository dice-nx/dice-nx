/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * Internationalization auto-load, brought in by DCC
 */

#include <exec/types.h>
#include <clib/locale_protos.h>
#include <stdio.h>

extern long _AutoLocale[];
extern struct Library *LocaleBase;

static APTR Catalog;
static APTR Locale;

__autoexit static void
ILocaleExit(void)
{
    if (Catalog) {
        CloseCatalog(Catalog);
        Catalog = NULL;
    }
    if (Locale) {
        CloseLocale(Locale);
        Locale = NULL;
    }
}

int
SetCatalog(char *localeName, char *catName)
{
    int r = 0;

    ILocaleExit();
    if (LocaleBase) {
        Locale = OpenLocale(localeName);
        r = 1;
        if (Catalog = OpenCatalogA(Locale, catName, NULL)) {
            long *al;

            r = 2;

            for (al = _AutoLocale + 1; *al; al += 2) {
                printf("%s ->", (char *)*al);
                *al = GetCatalogStr(Catalog, al[1], (char *)al[0]);
                printf("%s\n", (char *)*al);
            }
        }
    }
    return(r);
}

