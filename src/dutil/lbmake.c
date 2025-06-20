/*
 *    (c)Copyright 1992-1997 Obvious Implementations Corp.  Redistribution and
 *    use is allowed under the terms of the DICE-LICENSE FILE,
 *    DICE-LICENSE.TXT.
 */

/*
 *  Second generation library maker.  Gets library information from lib.def
 *  file in current directory
 *
 *  LBMAKE [keywords] [types]
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>

#ifdef AMIGA
#include <lists.h>
#include <exec/types.h>
#include <dos/dos.h>
#include <clib/dos_protos.h>
#include <clib/exec_protos.h>
#include <clib/alib_protos.h>
#include <lib/version.h>
#else
#include <suplib/all.h>
#include <include/lib/version.h>
#endif

#include "lbmake_rev.h"

#define arysize(ary)    (sizeof(ary)/sizeof((ary)[0]))

#define KT_TYPE     0
#define KT_LIBRARY  1
#define KT_OBJECT   3
#define KT_ALTTREE  4
#define KT_OPTION   5

typedef struct Node Node;
typedef struct List List;
typedef struct FileInfoBlock FileInfoBlock;

typedef struct KeyNode {
    Node    kn_Node;
    char    *kn_Data;
    char    *kn_Obj;        /*  file list only              */
    char    *kn_Aux;        /*  file list only              */
    short   kn_Option;      /*  -1 loose, 0 ignore, 1 use   */
    short   kn_Flags;
} KeyNode;

#define KF_COMPILED     0x0001
#define KF_ERROR        0x0002

typedef struct CmdNode {
    char    *cn_Name;       /*  name of command */
    short   cn_Args;        /*  number of args  */
    short   cn_Id;
    int     (*cn_Func)(short, char **, short, int32_t);
} CmdNode;

void    help(int);
KeyNode *FindKeyNode(KeyNode *, char *);
KeyNode *FindOptionNode(KeyNode *, char *);
int     CompileStuff(KeyNode *);
int     JoinStuff(KeyNode *, int);
int     ScanLibDefFile(char *);
int     ProcessCommandLine(int, char *, int32_t);
int     ProcessFileLine(int, char *, int32_t);
KeyNode* AllocKeyNode(char *, char *, char *, char *);

int     CmdAddKey(short, char **, short, int32_t);
int     CmdType(short, char **, short, int32_t);
int     CmdDefTree(short, char **, short, int32_t);

int     Assemble(char *, char *);
int     AssembleA68(char *, char *);
int     FDToLib(char *, char *, char *);
int     Compile(char *, char *);

int     strreplace(char *, char *, char *);

int     CompareTimeStamps(char *, char *);
void    CreateDirPath(char *);
char    *FillName(char *, char **, char *);
void    DicePrefix(char **, char *, char *);

#ifdef LATTICE
void    *GetHead(List *);
void    *GetSucc(Node *);
#endif

CmdNode CmdAry[] = {
    {   "Objects",  2,  KT_OBJECT , CmdAddKey   },
    {   "Library",  2,  KT_LIBRARY, CmdAddKey   },
    {   "Type"   ,  -1, KT_TYPE   , CmdType     },
    {   "DefTree",  1,  0         , CmdDefTree  },
    {   "AltTree",  2,  KT_ALTTREE, CmdAddKey   },
    {   "Option",   -1, KT_OPTION , CmdAddKey   }
};

List    KeyList;
List    FileList;
char    *LBMakeName;
char    *CompilerName;
char    *FDToLibName;
char    FlagsBuf[256];
char    TypeBuf[256];
char    DefTree[256];
char    TmpBuf[8192];
char    LastPath[256];

short   DoNotExecute;

int _DiceCacheEnable = 1;

DCOPYRIGHT;

int
main(int ac, char **av)
{
    short j;
    int r = 0;
    char **arg = av;
    char *libDefFilename = NULL;

    NewList(&KeyList);
    NewList(&FileList);

    DicePrefix(&LBMakeName, av[0], "lbmake");
    DicePrefix(&CompilerName, av[0], "dcc");
    DicePrefix(&FDToLibName, av[0], "fdtolib");

    // Skip past the first argument, which is the program name
    arg++; ac--;

    if(ac == 0) { // No arguments, so show help
        help(0);
        return 0;
    }

    if (strncmp(*arg, "-d", 2) == 0) { // name of the lib.def file
        char *a = *arg;
        if (a[2] == 0) { // filename is in the next element of argv
            arg++; ac--;
            libDefFilename = *arg;
        } else { // filename is straight after the option
            libDefFilename = &a[2];
        }
        arg++; ac--;
    }

    if (ScanLibDefFile(libDefFilename) < 0)
        help(10);

    while(ac > 0) {
        short option;
        KeyNode *kn;

        switch(**arg) {
        case '-':
            if (strcmp(*arg, "-n") == 0) {
                DoNotExecute = 1;
                continue;
            }
            option = -1;
            ++*arg;
            break;
        case '+':
            ++*arg;
        default:
            option = 1;
            break;
        }
        for (kn = NULL, j = 0; (kn = FindKeyNode(kn, *arg)) != NULL; ++j)
            kn->kn_Option = option;
        for (kn = NULL; (kn = FindOptionNode(kn, *arg)) != NULL; ++j) {
            if (kn->kn_Option == 0)
                kn->kn_Option = option;
        }
        if (j == 0) {
            printf("Unable to find symbol %s\n", *arg);
            r = 10;
        }

        arg++; ac--;
    }

    /*
     *  Handle compilation flags
     *  Handle alternate object tree
     *  Select compiler
     */

    {
        KeyNode *kn;
        for (kn = GetHead(&KeyList); kn; kn = GetSucc(&kn->kn_Node)) {
            if (kn->kn_Option <= 0)
                continue;

            switch(kn->kn_Node.ln_Type) {
            case KT_TYPE:
                strcat(FlagsBuf, kn->kn_Data);
                strcat(FlagsBuf, " ");
                strcat(TypeBuf, kn->kn_Node.ln_Name);
                break;
            case KT_ALTTREE:
                strcpy(DefTree, kn->kn_Data);
                break;
            default:
                break;
            }
        }
    }

    /*
     *  Create destination tree
     */

    sprintf(TmpBuf, DefTree, TypeBuf);
    CreateDirPath(TmpBuf);

    /*
     *  Scan for objects to create and libraries to make
     */

    {
        KeyNode *kn;
        for (kn = GetHead(&KeyList); r == 0 && kn; kn = GetSucc(&kn->kn_Node)) {
            if (kn->kn_Option <= 0)
                continue;

            switch(kn->kn_Node.ln_Type) {
            case KT_OBJECT:
            case KT_LIBRARY:
                r = CompileStuff(kn);   /*  < 0 error, == 0 need to link, 1 no work */
                if (r >= 0 && DoNotExecute == 0)
                    r = JoinStuff(kn, r);
                break;
            default:
                break;
            }
            if (r < 0)
                break;
        }
    }
    if (r < 0)
        r = 20;
    return(r);
}

void
help(int code)
{
    puts(VSTRING);
    puts(DCopyright);
    puts("LBMAKE [-d LIBDEFFILENAME] [keywords types]");
    exit(code);
}

KeyNode *
FindKeyNode(kn, name)
KeyNode *kn;
char *name;
{
    for (kn = ((kn) ? GetSucc(&kn->kn_Node) : GetHead(&KeyList)); kn; kn = GetSucc(&kn->kn_Node)) {
        if (stricmp(name, kn->kn_Node.ln_Name) == 0)
            break;
    }
    return(kn);
}

KeyNode *
FindOptionNode(kn, name)
KeyNode *kn;
char *name;
{
    short len = strlen(name);

    for (kn = ((kn) ? GetSucc(&kn->kn_Node) : GetHead(&FileList)); kn; kn = GetSucc(&kn->kn_Node)) {
        char *ptr;

        for (ptr = kn->kn_Data; *ptr; ++ptr) {
            if (*ptr == '+' || *ptr == '-') {
                short l2;
                {
                    short c;
                    for (l2 = 0; (c = ptr[l2]) != 0; ++l2) {
                        if (c == ' ' || c == '\t' || c == '\n')
                            break;
                    }
                }
                if (len == l2 - 1 && strnicmp(ptr + 1, name, len) == 0) {
                    if (*ptr == '-')
                        kn->kn_Option = -1;
                    return(kn);
                }
            }
        }
    }
    return(NULL);
}

/*
 *  Compile a library or object group, scan file list for files to do
 *  things to.  Base the action on their tailer:
 *
 *      .a      assemble with DAS
 *      .asm    assemble with DAS
 *      .a68    assemble with A68K
 *      .fd     generate using FDTOLIB
 *      .lib    copy
 *      .o      copy
 *      .c      compile
 *      <other> error
 */

int
CompileStuff(kn)
KeyNode *kn;
{
    KeyNode *fn;
    char *ptr;
    char buf[128];
    char obj[128];
    int r = 1;

    printf("Compile Stuff %s: %s\n", kn->kn_Node.ln_Name, kn->kn_Data);

    sprintf(buf, "+%s", kn->kn_Node.ln_Name);

    for (fn = GetHead(&FileList); r >= 0 && fn; fn = GetSucc(&fn->kn_Node)) {
        if (fn->kn_Option <= 0)
            continue;
        if (strstr(fn->kn_Data, buf) == NULL)
            continue;

        {
            int n;

            if (strchr(fn->kn_Obj, ':'))
                n = 0;
            else
                n = sprintf(obj, DefTree, TypeBuf);
            strcpy(obj + n, fn->kn_Obj);

            if ((ptr = strrchr(obj, '/')) != NULL) {
                *ptr = 0;
                if (strcmp(obj, LastPath) != 0) {
                    CreateDirPath(obj);
                    strcpy(LastPath, obj);
                }
                *ptr = '/';
            }
        }

        /*
         *  check timestamp. returns -1, 0, 1 as in strcmp(), but also returns
         *  -1 if either file does not exist
         */

        if (CompareTimeStamps(obj, fn->kn_Node.ln_Name) < 0) {
            if (r > 0)
                r = 0;

            if ((ptr = strrchr(fn->kn_Node.ln_Name, '.')) != NULL) {
                if (stricmp(ptr, ".a") == 0 || stricmp(ptr, ".asm") == 0)
                    r = Assemble(fn->kn_Node.ln_Name, obj);
                else if (stricmp(ptr, ".a68") == 0)
                    r = AssembleA68(fn->kn_Node.ln_Name, obj);
                else if (stricmp(ptr, ".fd") == 0)
                    r = FDToLib(fn->kn_Node.ln_Name, obj, fn->kn_Aux);
                else if (stricmp(ptr, ".lib") == 0 || stricmp(ptr, ".o") == 0)
                    r = 0;
                else
                    r = Compile(fn->kn_Node.ln_Name, obj);
            } else {
                r = Compile(fn->kn_Node.ln_Name, obj);
            }

            /*
             *  If an error occured quit out
             */

            if (r > 5)
                r = -r;
            if (r < 0)
                break;
        }
    }
    return(r);
}

/*
 *  JoinStuff()
 *
 *  join objects into the destination library
 */

int
JoinStuff(kn, need)
KeyNode *kn;
int need;
{
    KeyNode *fn;
    FILE *fi = NULL;
    FILE *fj;
    char buf[128];
    static char src[128];
    static char dst[128];
    int r = 0;

    /*
     *  compute library name
     */

    if (kn->kn_Node.ln_Type == KT_LIBRARY) {
        sprintf(buf, kn->kn_Data, TypeBuf);
        if (need > 0 && (fi = fopen(buf, "r"))) {
            printf("UpToDate: %s\n", buf);
            fclose(fi);
            return(0);
        }
        if ((fi = fopen(buf, "w")) != NULL) {
            printf("Create %s\n", buf);
        } else {
            printf("Unable to create %s\n", buf);
            return(-1);
        }
    }

    /*
     *  append object modules
     */

    sprintf(buf, "+%s", kn->kn_Node.ln_Name);
    for (fn = GetHead(&FileList); r == 0 && fn; fn = GetSucc(&fn->kn_Node)) {
        if (fn->kn_Option <= 0)
            continue;
        if (strstr(fn->kn_Data, buf) == NULL)
            continue;

        {
            int n;
            if (strchr(fn->kn_Obj, ':'))
                n = 0;
            else
                n = sprintf(src, DefTree, TypeBuf);
            strcpy(src + n, fn->kn_Obj);
        }

        if (kn->kn_Node.ln_Type == KT_OBJECT) {
            char *ptr = fn->kn_Obj + strlen(fn->kn_Obj);
            while (ptr >= fn->kn_Obj && *ptr != ':' && *ptr != '/')
                --ptr;
            sprintf(dst, kn->kn_Data, ptr + 1, TypeBuf);
            if (CompareTimeStamps(dst, src) >= 0) {
                printf("UpToDate: %s\n", dst);
                continue;
            }

            fi = fopen(dst, "w");
            printf("Create %s\n", dst);
        }


        if ((fj = fopen(src, "r")) != NULL) {
            int32_t n;
            while ((n = fread(TmpBuf, 1, sizeof(TmpBuf), fj)) > 0) {
                if (fi) {
                    if (fwrite(TmpBuf, 1, n, fi) != n) {
                        puts("write error");
                        r = -1;
                        break;
                    }
                }
            }
            fclose(fj);
        } else {
            printf("Unable to open %s\n", src);
            r = -1;
        }
        if (kn->kn_Node.ln_Type == KT_OBJECT && fi) {
            fclose(fi);
            fi = NULL;
        }
    }
    if (fi)
        fclose(fi);
    return(r);
}

int
ScanLibDefFile(char *libDefName)
{
    FILE *fi;
    char *ptr;
    char buf[256];
    int r = 0;
    short lineNo = 0;

    if (libDefName == NULL) {
#ifdef AMIGA
    libDefName = "lib.def";
#else
    libDefName = "ulib.def";
#endif
    }

    if ((fi = fopen(libDefName, "r")) != NULL) {
        while (fgets(buf, sizeof(buf), fi)) {
            ++lineNo;
            for (ptr = buf; *ptr == ' ' || *ptr == '\t'; ++ptr);

            if (*ptr == '\n' || *ptr == '#')
                continue;

            if (*ptr == '@') {
                r = ProcessCommandLine(r, ptr, lineNo);
            } else {
                r = ProcessFileLine(r, ptr, lineNo);
            }
        }
        fclose(fi);
    } else {
        printf("Unable to open %s\n", libDefName);
        r = -1;
    }
    return(r);
}

int
ProcessCommandLine(r, cmd, line)
int r;
char *cmd;
int32_t line;
{
    static char *av[64];
    short ac;

    if ((cmd = strtok(cmd + 1, " \t\n")) != NULL) {
        CmdNode *cn;
        for (cn = CmdAry; cn < CmdAry + arysize(CmdAry); ++cn) {
            if (stricmp(cmd, cn->cn_Name) == 0)
                break;
        }
        for (ac = 0; ac < 64 && (av[ac] = strtok(NULL, " \t\n")); ++ac)
            ;
        if (cn) {
            if (cn->cn_Args >= 0 && ac != cn->cn_Args) {
                printf("Expected %d args for %s line %d\n", cn->cn_Args, cmd, line);
                r = -1;
            } else {
                if (cn->cn_Func(ac, av, cn->cn_Id, line) < 0)
                    r = -1;
            }
        } else {
            printf("Unknown @ command line %d (%s)\n", line, cmd);
            r = -1;

        }
    } else {
        printf("Bad @ command line %d\n", line);
        r = -1;
    }
    return(r);
}

int
ProcessFileLine(r, ptr, line)
int r;
char *ptr;
int32_t line;
{
    KeyNode *kn;
    char *opts;
    short i;
    short j;
    static char src[256];
    static char obj[256];
    static char aux[256];

    while (*ptr == ' ' || *ptr == '\t')
        ++ptr;

    for (i = 0; ptr[i] && ptr[i] != ' ' && ptr[i] != '\t'; ++i) {
        /*
         *  Handle a comma (separator between filepathname and
         *  auxillary information (e.g. library name for .fd files)
         */
        if (ptr[i] == ',')
            break;
    }

    strncpy(src, ptr, i);
    src[i] = 0;

    strcpy(obj, src);

    aux[0] = 0;
    if (ptr[i] == ',') {
        ++i;
        for (opts = ptr + i; *opts && *opts != ' ' && *opts != '\t'; ++opts)
            ;
        strncpy(aux, ptr + i, opts - (ptr + i));
        aux[opts - (ptr + i)] = 0;
    } else {
        opts = ptr + i;
    }
    if (*opts == 0) {
        printf("File Line Error, no keywords: %s", ptr);
        return(-1);
    }
    for (; *opts == ' ' || *opts == '\t'; ++opts)
        ;

    /*
     *  remove '[' and ']' from source name
     */

    for (i = j = 0; src[i]; ++i) {
        switch(src[i]) {
        case '[':
        case ']':
            break;
        default:
            src[j] = src[i];
            ++j;
            break;
        }
    }
    src[j] = 0;

    /*
     *  remove [path] from object name
     */


    for (ptr = strchr(obj, '['); ptr; ptr = strchr(ptr, '[')) {
        char *p2;
        if ((p2 = strchr(ptr, ']')) != NULL) {
            movmem(p2 + 1, ptr, strlen(p2));
        } else {
            printf("No matching ']' on line %d\n", line);
            return(-1);
        }
    }

    /*
     *  modify tail to .o if not already a .lib or .o
     */

    if ((ptr = strrchr(obj, '.')) != NULL) {
        if (stricmp(ptr, ".lib") != 0 && stricmp(ptr, ".o") != 0)
            strcpy(ptr, ".o");
    } else {
        strcat(obj, ".o");
    }

    kn = AllocKeyNode(src, opts, obj, (aux[0] ? aux : NULL));

    AddTail(&FileList, &kn->kn_Node);

    return(r);
}

int
CmdAddKey(short ac, char **av, short id, int32_t line)
{
    KeyNode *kn = AllocKeyNode(av[0], av[1], NULL, NULL);
    kn->kn_Node.ln_Type = id;
    AddTail(&KeyList, &kn->kn_Node);
    return(0);
}

int
CmdType(short ac, char **av, short id, int32_t line)
{
    short i;

    if (ac == 0) {
        printf("Expected type designator line %d\n", line);
        return(-1);
    }
    for (i = 1, TmpBuf[0] = 0; i < ac; ++i) {
        if (i > 1)
            strcat(TmpBuf, " ");
        strcat(TmpBuf, av[i]);
    }
    av[1] = TmpBuf;
    return(CmdAddKey(ac, av, id, line));
}

int
CmdDefTree(short ac, char **av, short id, int32_t line)
{
    strcpy(DefTree, av[0]);
    return(0);
}

KeyNode *
AllocKeyNode(name1, name2, objName, auxName)
char *name1;
char *name2;
char *objName;
char *auxName;
{
    static char   *AlBuf;
    static int32_t   AlBytes;
    KeyNode *kn;
    int32_t bytes = sizeof(KeyNode) + 2 + strlen(name1) + strlen(name2);
    char *fillPtr;

    if (objName)
        bytes += strlen(objName) + 1;
    if (auxName)
        bytes += strlen(auxName) + 1;

    bytes = (bytes + 3) & ~3;

    if (bytes > AlBytes) {
        AlBuf = malloc(4096);
        if (AlBuf == NULL) {
            puts("malloc failed");
            exit(20);
        }
        AlBytes = 4096;
        setmem(AlBuf, 4096, 0);
    }
    kn = (KeyNode *)AlBuf;
    fillPtr = FillName((char *)(kn + 1), &kn->kn_Node.ln_Name, name1);
    fillPtr = FillName(fillPtr, &kn->kn_Data, name2);
    fillPtr = FillName(fillPtr, &kn->kn_Obj, objName);
    fillPtr = FillName(fillPtr, &kn->kn_Aux, auxName);
    AlBuf += bytes;
    AlBytes -= bytes;
    return(kn);
}

char *
FillName(fillPtr, pptr, name)
char *fillPtr;
char **pptr;
char *name;
{
    if (name) {
        strcpy(fillPtr, name);
        *pptr = fillPtr;
        fillPtr += strlen(name) + 1;
    } else {
        *pptr = NULL;
    }
    return(fillPtr);
}

/*
 *  Compile, Assemble, Generate
 *
 */

int
Assemble(srcFile, objFile)
char *srcFile;
char *objFile;
{
    int32_t r;
    char buf[256];

    sprintf(buf, "%s %s -o %s -c", CompilerName, srcFile, objFile);
    puts(buf);
    fflush(stdout);     /* SAS/C */

    r = 0;
    if (DoNotExecute == 0)
        r = system(buf);
    return(r);
}


int
AssembleA68(srcFile, objFile)
char *srcFile;
char *objFile;
{

    /* XXX */
    return(-1);
}


int
FDToLib(srcFile, objFile, aux)
char *srcFile;
char *objFile;
char *aux;
{
    int32_t r;
    char buf[1024];
    char hfile[256];

    /*
     *  locate header file (only required for registered-args tag generation)
     */

    strcpy(hfile, srcFile);
    if (strreplace(hfile, "_lib.fd", "_protos.h") < 0) {
        printf("FD file not in *_lib.fd format: %s\n", srcFile);
        return(-1);
    }
    if (strreplace(hfile, "/fd/", "/clib/") < 0)
        strreplace(hfile, ":fd/", ":clib/");

    int needed_buf = 11 + strlen(FDToLibName) + strlen (srcFile)
        + strlen(hfile) + strlen(objFile) + strlen (FlagsBuf);
    if (needed_buf > sizeof(buf)) {
        puts("Internal buffer overflow");
        exit(20);
    }
    r = sprintf(buf,
                 "%s %s -h %s -o %s %s",
                 FDToLibName, srcFile, hfile, objFile, FlagsBuf);
    if (aux) {
        needed_buf = 8 + strlen(buf) + strlen(aux);
        if (needed_buf > sizeof(buf)) {
            puts("Internal buffer overflow");
            exit(20);
        }
        sprintf(buf + r, " -auto %s", aux);
    }
    puts(buf);
    fflush(stdout);     /* SAS/C */

    r = 0;
    if (DoNotExecute == 0)
        r = system(buf);

    return(r);
}

int
Compile(srcFile, objFile)
char *srcFile;
char *objFile;
{
    int32_t r;
    char buf[1024];

    int needed_buf = 10 + strlen(CompilerName) + strlen(srcFile)
        + strlen(objFile) + strlen(FlagsBuf);
    if(needed_buf > sizeof(buf)) {
        puts("Internal buffer overflow");
        exit(20);
    }
    sprintf(buf,
             "%s %s -o %s %s -c", CompilerName, srcFile, objFile, FlagsBuf);
    puts(buf);
    fflush(stdout);     /* SAS/C */

    r = 0;
    if (DoNotExecute == 0)
        r = system(buf);

    return(r);
}

#ifndef LATTICE

int
CompareTimeStamps(name1, name2)
char *name1;
char *name2;
{
    struct stat stat1;
    struct stat stat2;
    int32_t r = -1;

    if (stat(name1, &stat1) == 0) {
        if (stat(name2, &stat2) == 0) {
            if (stat1.st_mtime >= stat2.st_mtime) {
                if (stat1.st_mtime == stat2.st_mtime) {
                    r = 0;
                } else {
                    r = 1;
                }
            }
        }

    }
    return(r);
}

#ifdef NOTDEF

int
CompareTimeStamps(name1, name2)
char *name1;
char *name2;
{
    int32_t lock1;
    int32_t lock2;
    __aligned FileInfoBlock fib1;
    __aligned FileInfoBlock fib2;
    int r = -1;

    if (lock1 = Lock(name1, SHARED_LOCK)) {
        if (Examine(lock1, &fib1)) {
            if (lock2 = Lock(name2, SHARED_LOCK)) {
                if (Examine(lock2, &fib2)) {
                    if (fib1.fib_Date.ds_Days >= fib2.fib_Date.ds_Days) {
                        if (fib1.fib_Date.ds_Days == fib2.fib_Date.ds_Days) {
                            if (fib1.fib_Date.ds_Minute >= fib2.fib_Date.ds_Minute) {
                                if (fib1.fib_Date.ds_Minute == fib2.fib_Date.ds_Minute) {
                                    if (fib1.fib_Date.ds_Tick == fib2.fib_Date.ds_Tick)
                                        r = 0;
                                    else if (fib1.fib_Date.ds_Tick > fib2.fib_Date.ds_Tick)
                                        r = 1;
                                } else {
                                    r = 1;
                                }
                            }
                        } else {
                            r = 1;
                        }
                    }
                }
                UnLock(lock2);
            }
        }
        UnLock(lock1);
    }
    return(r);
}
#endif

#else

int
CompareTimeStamps(name1, name2)
char *name1;
char *name2;
{
    int32_t lock1;
    int32_t lock2;
    FileInfoBlock *fib1 = malloc(sizeof(FileInfoBlock));
    FileInfoBlock *fib2 = malloc(sizeof(FileInfoBlock));
    int r = -1;

    if (lock1 = Lock(name1, SHARED_LOCK)) {
        if (Examine(lock1, fib1)) {
            if (lock2 = Lock(name2, SHARED_LOCK)) {
                if (Examine(lock2, fib2)) {
                    if (fib1->fib_Date.ds_Days >= fib2->fib_Date.ds_Days) {
                        if (fib1->fib_Date.ds_Days == fib2->fib_Date.ds_Days) {
                            if (fib1->fib_Date.ds_Minute >= fib2->fib_Date.ds_Minute) {
                                if (fib1->fib_Date.ds_Minute == fib2->fib_Date.ds_Minute) {
                                    if (fib1->fib_Date.ds_Tick == fib2->fib_Date.ds_Tick)
                                        r = 0;
                                    else if (fib1->fib_Date.ds_Tick > fib2->fib_Date.ds_Tick)
                                        r = 1;
                                } else {
                                    r = 1;
                                }
                            }
                        } else {
                            r = 1;
                        }
                    }
                }
                UnLock(lock2);
            }
        }
        UnLock(lock1);
    }
    free(fib1);
    free(fib2);
    return(r);
}

void *
GetHead(list)
List *list;
{
    if (list->lh_Head->ln_Succ)
        return(list->lh_Head);
    return(NULL);
}

void *
GetSucc(node)
Node *node;
{
    if (node->ln_Succ->ln_Succ)
        return(node->ln_Succ);
    return(NULL);
}

#endif

void
CreateDirPath(buf)
char *buf;
{
    short n;
    char *p2;

    if ((n = strlen(buf)) && buf[n-1] == '/')
        buf[--n] = 0;

    if (CompareTimeStamps(buf, buf) != 0) {
#ifdef AMIGA
        if (mkdir(buf) < 0) {
#else
        if (mkdir(buf, 0777) < 0) {
#endif
            if ((p2 = strrchr(buf, '/')) != NULL) {
                *p2 = 0;
                CreateDirPath(buf);
                *p2 = '/';
#ifdef AMIGA
                mkdir(buf);
#else
                mkdir(buf, 0777);
#endif
            }
        }
    }
}

int
strreplace(buf, findStr, repStr)
char *buf;
char *findStr;
char *repStr;
{
    char *ptr;

    if ((ptr = strstr(buf, findStr)) != NULL) {
        short l1 = strlen(findStr);
        short l2 = strlen(repStr);

        if (l1 < l2)
            movmem(ptr, ptr + (l2 - l1), strlen(ptr) + 1);
        else if (l1 > l2)
            movmem(ptr, ptr - (l1 - l2), strlen(ptr) + 1);
        bcopy(repStr, ptr, l2);
        return(0);
    } else {
        return(-1);
    }
}

void
DicePrefix(char **pbuf, char *av0, char *app)
{
    char *ptr;
    short n = 0;

    for (ptr=av0+strlen(av0); ptr >= av0 && *ptr != '/' && *ptr != ':'; --ptr)
        ;
    ++ptr;
    if (av0 != ptr)
        n = ptr - av0;
    *pbuf = malloc(strlen(app) + n + 1);
    if (n)
        strncpy(*pbuf, av0, n);
    strcpy(*pbuf + n, app);
}

