/*
 *    (c)Copyright 1992-1997 Obvious Implementations Corp.  Redistribution and
 *    use is allowed under the terms of the DICE-LICENSE FILE,
 *    DICE-LICENSE.TXT.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "uprev_rev.h"

#define MAX_FNAME 256

//const static char version_string[] = VERSTAG;

int parse_version_string(const char *verstr, int *parsed_version);

/* Parse a version string of up to three parts (e.g. 3.20.1). Pass in a string
 * and a pointer to an integer array of at least three elements. The elements
 * will be filled in with the parsed version numbers. If fewer than three parts
 * are present, the remaining elements will be set to -1.
 * Returns a positive integer on success, or 0 on error.
 */
int parse_version_string(const char *verstr, int *parsed_version)
{
   int part = 0;
   const char *p = verstr;
   char *endptr;

   for (part = 0; part < 3; part++)
   {
      while (*p == ' ' || *p == '\t') p++; // Skip whitespace
      if (*p == '\0')
      {
         parsed_version[part] = -1; // No more parts
         continue;
      }

      long val = strtol(p, &endptr, 10);
      if (endptr == p)
      {
         return 0; // No digits found
      }
      parsed_version[part] = (int)val;
      p = endptr;

      while (*p == ' ' || *p == '\t') p++; // Skip whitespace
      if (*p == '.')
      {
         p++; // Move past the dot
      }
      else
      {
         part++;
         break; // No more parts
      }
   }

   // Fill remaining parts with -1
   for (; part < 3; part++)
   {
      parsed_version[part] = -1;
   }

   return 1; // Success
}

int main(int argc, char **argv)
{
   FILE *fp;
   char *vertag;
   int version;
   int revision;
   int patch;
   char fname[MAX_FNAME];
   char buf[80];
   time_t t;
   struct tm *tp;

   if ((argc > 3) || (argc < 2))
   {
      printf("Usage: %s <Project> [<Version>]\n", argv[0]);
      return(5);
   }

   vertag = "";
   version =  1;
   revision = 0;
   patch = 0;

   /* Determine the name of the revision file */
   strncpy(fname, argv[1], MAX_FNAME-7);
   fname[MAX_FNAME-7] = 0;
   strcat(fname, "_rev.h");

   /* See if the file already exists. */
   fp = fopen(fname, "r");
   if (fp != NULL)
   {
      /* It exists, get the version and revision out of it */
      while(fgets(buf, 80, fp) != NULL)
      {
         int ln;
         ln = strlen(buf)-1;
         if (buf[ln] == '\n') buf[ln] = 0;

         if (!memcmp(buf, "#define ", 8))
         {
            char *p;
            p = buf+8;
            while(*p == ' ' || *p == '\t') p++;
            if (!memcmp(p, "VERS ", 5))
            {
               p += 4;
               while(*p == ' ' || *p == '\t') p++;
               /* Now we need to get past the name of the executable */
               ln = strlen(argv[1]);
               if (strlen(p) > ln)
               {
                  char c;
                  c = p[ln];
                  p[ln] = 0;
                  if (strcasecmp(p, argv[1]))
                  {
                     /* We don't have a match, we need to go for the */
                     /* space which separates the name               */
                     p[ln] = c;
                     while (*p && *p != ' ') p++;
                  }
                  else
                  {
                     /* Well, it matches, shift past the name */
                     p += ln + 1;
                  }
                  /* Now we should be pointing past the name (and a single space) */
                  /* at any aux version tag information that they might have      */
                  /* we want to go from the END of the string and eliminate any   */
                  /* numeric digits that are there.                               */
                  ln = strlen(p);
                  if ((ln > 1) && (p[ln-1] == '"')) ln--;
                  while((ln > 1) && (p[ln-1] >= '0') && (p[ln-1] <= '9')) ln--;
                  if ((ln > 1) && (p[ln-1] == '.'))
                  {
                     ln--;
                     while((ln > 1) && (p[ln-1] >= '0') && (p[ln-1] <= '9')) ln--;
                     if ((ln > 1) && (p[ln-1] == '.'))
                     {
                        ln--;
                        while((ln > 1) && (p[ln-1] >= '0') && (p[ln-1] <= '9')) ln--;
                     }
                  }
                  p[ln] = 0;
                  while (*p == ' ' || *p == '\t') p++;
                  vertag = strdup(p);
               }
            }
            else if (!memcmp(p, "VERSION ", 8))
            {
               version = atoi(p+7);
            }
            else if (!memcmp(p, "REVISION ", 9))
            {
               revision = atoi(p+9);
            }
            else if (!memcmp(p, "PATCH ", 6))
            {
               patch = atoi(p+6);
            }
         }
      }

      fclose(fp);
   }

   /* Figure out what version number we will be using */
   if (argc > 2)
   {
      int new_version[3];
      if (!parse_version_string(argv[2], new_version)) {
         printf("Invalid version string: %s\n", argv[2]);
         return(10);
      }

      if (new_version[0] > version) {
         version = new_version[0];
         revision = new_version[1] != -1 ? new_version[1] : 0;
         patch = new_version[2] != -1 ? new_version[2] : 0;
      } else if (new_version[0] < version) {
         printf("Cannot set version to %d as it is less than current version %d\n",
                new_version[0], version);
         return(10);
      } else {
         // Major version is the same, check minor
         if (new_version[1] != -1) {
            if (new_version[1] > revision) {
               revision = new_version[1];
               patch = new_version[2] != -1 ? new_version[2] : 0;
            } else if (new_version[1] < revision) {
               printf("Cannot set revision to %d as it is less than current revision %d\n",
                      new_version[1], revision);
               return(10);
            } else {
               // Minor version is the same, check patch
               if (new_version[2] != -1) {
                  if (new_version[2] > patch) {
                     patch = new_version[2];
                  } else {
                     printf("Cannot set patch to %d as it is not higher than current patch %d\n",
                            new_version[2], patch);
                     return(10);
                  }
               }
            }
         }
      }
   } else {
      /* No version specified, just increment the revision */
      revision++;
      patch = 0;
   }

   fp = fopen(fname, "w");
   if (fp == NULL)
   {
      perror(fname);
      return(20);
   }

   time(&t);
   tp = localtime(&t);

   (void)tp->tm_mday;
   (void)tp->tm_year;
   (void)tp->tm_mon;

   sprintf(buf, "%d.%d.%d", tp->tm_mday, tp->tm_mon+1, 1900+tp->tm_year);

   /* Figure out what is the number to */

   fprintf(fp, "/* This file is automatically generated by uprev. Do not edit. */\n\n");
   fprintf(fp, "#define VERSION        %d\n",
                                       version);
   fprintf(fp, "#define REVISION       %3d\n",
                                       revision);
   fprintf(fp, "#define PATCH       %3d\n",
                                       patch);
   fprintf(fp, "#define DATE    \"%s\"\n",
                                  buf);
   fprintf(fp, "#define VERS    \"%s %s%d.%d.%d\"\n",
                                 argv[1], vertag, version, revision, patch);
   fprintf(fp, "#define VSTRING \"%s %s%d.%d.%d (%s)\"\n",
                                 argv[1], vertag, version, revision, patch, buf);
   fprintf(fp, "#define VERSTAG \"\\0$%s: %s %s%d.%d (%s)\"\n",
                                 "VER", argv[1], vertag, version, revision, buf);
   fclose(fp);

   return(0);
}
