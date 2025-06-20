/*
 *    (c)Copyright 1992-1997 Obvious Implementations Corp.  Redistribution and
 *    use is allowed under the terms of the DICE-LICENSE FILE,
 *    DICE-LICENSE.TXT.
 */

/*
 *  MAIN.C
 *
 *  c1 infile -o outfile -m<models> ...
 */

/*
**      $Filename: main.c $
**      $Author: dice $
**      $Revision: 30.326 $
**      $Date: 1995/12/24 06:09:43 $
**      $Log: main.c,v $
 * Revision 30.326  1995/12/24  06:09:43  dice
 * .
 *
 * Revision 30.325  1995/12/24  05:38:10  dice
 * .
 *
 * Revision 30.156  1995/01/11  05:04:49  dice
 * version string now reports 'MiniDice'
 *
 * Revision 30.6  1994/08/04  04:49:36  dice
 * .
 *
 * Revision 30.5  1994/06/13  18:37:31  dice
 * .
 *
 * Revision 30.0  1994/06/10  18:04:52  dice
 * .
 *
 * Revision 1.4  1993/11/22  00:28:36  jtoebes
 * Final cleanup to eliminate all cerror() messages with strings.
 *
 * Revision 1.3  1993/09/19  18:01:29  jtoebes
 * Changed main to utilize the _REV form of version numbering to be more
 * integrated with the tool set.
 *
**/

#include "defs.h"
#include "DC1_rev.h"
#include <include/lib/version.h>

DCOPYRIGHT;

Prototype short MC68020Opt;
Prototype short MC68881Opt;
Prototype short State;
Prototype short DDebug;
Prototype short SmallCode;
Prototype short SmallData;
Prototype short ConstCode;
Prototype short AbsData;
Prototype short ResOpt;
Prototype short PIOpt;
Prototype short VerboseOpt;
Prototype short ProtoOnlyOpt;
Prototype short XOpt;
Prototype short FFPOpt;
Prototype short GenStackOpt;
Prototype short GenLinkOpt;
Prototype short RegCallOpt;
Prototype short RegSpecOutputOpt;
Prototype short ProfOpt;
Prototype short ForkOpt;
Prototype short UnixCommonOpt;
Prototype short DebugOpt;
Prototype short AsmOnlyOpt;
Prototype short ErrorOpt;
Prototype int32_t       ZAllocs;
Prototype int32_t       TAllocs;
Prototype int32_t       ZChunks, ZAloneChunks;
Prototype int32_t       TChunks, TAloneChunks;
Prototype int32_t       SymAllocs;
Prototype int32_t       ExitCode;
Prototype int32_t       RetryCount;
Prototype char  *OutFileName;
Prototype char  *InFileName;
Prototype Var   DummyDataVar;
Prototype Var   DummyCodeVar;
Prototype char  *ErrorFile;
Prototype FILE  *ErrorFi;

short   State = SOUTSIDE;
short   FFPOpt;
short   GenStackOpt;
short   GenLinkOpt;
short   DDebug;
short   SmallCode = 1;
short   SmallData = 1;
short   RegCallOpt;
short   ConstCode;    /* const objs -> CODE sect, 1 = (pc), 2 = ext-abs */
short   ProfOpt;
short   ForkOpt;
short   RegSpecOutputOpt;
short   AbsData;
short   ResOpt;
short   PIOpt;
short   VerboseOpt;
short   ProtoOnlyOpt;       /*  prototyped calls only   */
short   XOpt;
short   UnixCommonOpt;
short   MC68020Opt;
short   MC68881Opt;
short   DebugOpt;
short   AsmOnlyOpt;
short   ErrorOpt;

short   LargeDataModelChosen;   /*  main() use only */
char    *InFileName;            /*  main() use only */
char    *ErrorFile;

int32_t ZAllocs;
int32_t TAllocs;
int32_t ZChunks, ZAloneChunks;
int32_t TChunks, TAloneChunks;
int32_t SymAllocs;
int32_t ExitCode;
int32_t RetryCount;
char    *OutFileName;
Var     DummyDataVar;
Var     DummyCodeVar;

FILE    *ErrorFi;

Prototype int main(int, char **);
Prototype void help(void);
Prototype void _Assert(const char *, int32_t);
Prototype void DumpStats(void);
Prototype void ParseOpts(short, char **, short);

Local void InitDummy(void);

int _DiceCacheEnable = 1;
int _bufsiz = 8192;

int
main(ac, av)
int ac;
char **av;
{
    if (ac == 1)
        help();

    Assert(1);  /* filler to avoid gnu compiler warnings */

    atexit(CloseLibsExit);

    ParseOpts(ac, av, 1);

    InitLex();

    if (InFileName)
        PushLexFile(InFileName, strlen(InFileName), 0, -1);
    else
        PushLexFile((char *)stdin, 0, 0, -2);

    ErrorInFileValid = 1;

#ifdef NOTDEF
        buf[0] = '\n';              /*  so lexer can catch '#' on first line */
        buf[bytes+1] = 0;           /*  also for lexer                       */
        InitLex(1, buf, bytes+1);
    }
#endif

    /*
     *  Other Initialization
     */

    InitSym(1);
    InitTypes(1);
    InitGen(1);
    InitDummy();

    /*
     *  Top Level
     */

    SemanticLevelDown();
    {
        int32_t t = GetToken();

        /*  OMD assumes code section is first */
        asm_segment(&DummyCodeVar);
        while (t) {
            t = TopLevel(t);
            tclear();
        }
    }
    DumpStats();

    SemanticLevelUp();
    DumpAuxSubs();
    DumpExternList(1);
    DumpStrList();
    DumpExternList(0);
    asm_end();
    InitGen(0);
    InitTypes(0);
    if (OutFileName && ExitCode > 5 && !DDebug) {
        fclose(stdout);
        remove(OutFileName);
    }
    return(ExitCode);
}

void
help()
{
    printf("%s\n%s\n", VSTRING, DCopyright);
    exit(5);
}


void
_Assert(file, line)
const char *file;
int32_t line;
{
#if defined(DEBUG) && defined(UNIX)
    for (;;) 
        ;
#endif
    zerror(EFATAL_INTERNAL_ERROR, line, file);
}

void
DumpStats()
{
    if (VerboseOpt || DDebug) {
        if (DDebug) {
            eprintf(0, "memory: per=%d tmp=%d\n", ZAllocs, TAllocs);
            eprintf(0, "        zchunks=%d alone=%d\n", ZChunks, ZAloneChunks);
            eprintf(0, "        tchunks=%d alone=%d\n", TChunks, TAloneChunks);
        }
        eprintf(0, "types created: %d  symbols: %d  retries: %d\n",
            NumTypesAlloc,
            SymAllocs,
            RetryCount
        );
        eprintf(0, "lexer linenum cache: %d/%d hits\n", LexCacheHits, LexCacheHits + LexCacheMisses);
    }
}

void
InitDummy()
{
    DummyCodeVar.var_Stor.st_Flags |= SF_CODE;
    DummyDataVar.u.AssExp = (Exp *)-1L;
}

void
ParseOpts(short ac, char **av, short c1Only)
{
    short i;

    for (i = 1; i < ac; ++i) {
        char *ptr = av[i];

        if (*ptr != '-') {
            /*
             *  If from a #pragma ignore file names (which could also be
             *  parts of previous - options that aren't meant for us)
             */

            if (c1Only) {
                InFileName = ptr;
            }
            continue;
        }
        ptr += 2;
        switch(ptr[-1]) {
        case 'i':       /* -int<catalog_def_file> */
            if (strncmp(ptr, "nt", 2) == 0) {
                ptr += 2;
                if (*ptr == 0)
                    ptr = av[++i];
                if (LoadLocaleDefs(ptr) == 0)
                    zerror(EERROR_BAD_LOCALE, ptr);
            }
            break;
        case '0':
            MC68020Opt = 1;
            break;
        case '8':
            MC68881Opt = 1;
            break;
        case 'S':       /*  set section name for code, data, bss    */
            /*
             *  set section name for code, data, bss.  -S selects
             *  new names for data & bss automatically (same as those
             *  referenced in dlib:c.o so library data/bss is placed
             *  first and thus ALWAYS A4 relative accessable)
             */
            {
                char *sname = NULL;

                if (ptr[0]) {
                    if (ptr[1])
                        sname = ptr + 1;
                    else
                        sname = av[++i];
                }

                switch(*ptr) {
                case 'd':   /*  data    */
                    SegNames[1] = sname;
                    break;
                case 'D':   /*  far-data */
                    SegNames[2] = sname;
                    break;
                case 'b':   /*  bss     */
                    SegNames[3] = sname;
                    break;
                case 'B':   /*  far-bss */
                    SegNames[4] = sname;
                    break;
                case 'c':   /*  code    */
                    SegNames[0] = sname;
                    break;
                case 0:     /*  auto-select */
                    SegNames[1] = "libdata";
                    SegNames[3] = "libbss";
                    break;
                default:
                    help();
                }
            }
            break;
        case 'd':
            if (*ptr)
                DebugOpt = atoi(ptr);
            else
                DebugOpt = 1;
            break;
        case 'Z':
            DDebug = (*ptr) ? atoi(ptr) : 1;
            break;
        case 'a':
            AsmOnlyOpt = 1;     /*  comment assembly please */
            DebugOpt = 1;
            break;
        case 'g':
            switch(*ptr) {
            case 's':
                GenStackOpt = 1;
                break;
            case 'l':
                GenLinkOpt = 1;
                break;
            default:
                break;
            }
            break;
        case 'R':
            /*RemoveInFile = 1;*/
            break;
        case 'F':
            ErrorOpt = 1;
            if (*ptr >= '1' && *ptr <= '9')
                ErrorOpt = *ptr - '0';
            ptr = av[++i];
            ErrorFi = fopen(ptr, "a");
            ErrorFile = ptr;
            break;
        case 'f':
            if (strcmp(ptr, "fp") == 0)
                FFPOpt = 1;
            if (strcmp(ptr, "ork") == 0)
                ForkOpt = 1;
            break;
        case 'p':
            if (strcmp(ptr, "roto") == 0) {
                ProtoOnlyOpt = 1;
            } else if (strcmp(ptr, "rof") == 0) {
                ProfOpt = 1;
            } else if (strcmp(ptr, "rof0") == 0) {
                ProfOpt = 0;
            } else if (strcmp(ptr, "i") == 0) {
/*              if (ResOpt == 1)
                    puts("DC1: warning, -pi -r == -pr"); */
                PIOpt = 1;
            } else if (strcmp(ptr, "i0") == 0) {
                PIOpt = 0;
            } else if (strcmp(ptr, "r") == 0) {
                PIOpt = 1;
                ResOpt = 1;
            } else if (strcmp(ptr, "r0") == 0) {
                PIOpt = 0;
                ResOpt = 0;
            } else {
                help();
            }
            if (PIOpt && ConstCode == 1)    /*  silently force -ms to -mS */
                ConstCode = 2;
            break;
        case 'r':
            if (*ptr == '0') {
                ResOpt = 0;
            } else {
/*              if (PIOpt && ResOpt == 0)
                    puts("DC1: warning, -pi -r == -pr"); */
                ResOpt = 1;
                if (!LargeDataModelChosen && SmallData == 0)
                    SmallData = 1;
            }
            break;
        case 'x':
            XOpt = atoi(ptr);
            break;
        case 'v':
            VerboseOpt = 1;
            break;
        case 'o':
            if (*ptr == 0)
                ptr = av[++i];
            OutFileName = ptr;
            if (ptr == NULL || freopen(ptr, "w", stdout) == NULL)
                zerror(EFATAL_CANT_OPEN_OUTPUT, ptr ? ptr : "?");
            break;
        case 'm':
            switch(*ptr) {
            case 'c':
                SmallCode = 1;
                break;
            case 'C':
                SmallCode = 0;
                break;
            case 'w':
                SmallData = 2;
                AbsData = 1;
                break;
            case 'a':       /*  -ma is a nop    */
                AbsData = 1;
                break;
            case 'd':
                SmallData = 1;
                LargeDataModelChosen = 0;
                break;
            case 'D':
                SmallData = 0;
                LargeDataModelChosen = 1;
                break;
            case 'r':
                if (ptr[1] == '0')
                    RegCallOpt = 0;
                else
                    RegCallOpt = 1;
                break;
            case 'R':
                RegCallOpt = 2;
                if (ptr[1] == 'R') {
                    RegCallOpt = 3;
                    if (ptr[2] == 'X')
                        RegSpecOutputOpt = 1;
                    if (ptr[2] == 'Y')
                        RegSpecOutputOpt = 2;
                }
                break;
            case 's':
                if (ptr[1] == '0')
                    ConstCode = 0;
                else
                    ConstCode = 1;
                if (PIOpt && ConstCode)     /*  silently force to -mS   */
                    ConstCode = 2;
                break;
            case 'S':
                ConstCode = 2;
                break;
            case 'u':
                if (ptr[1] == '0')
                    UnixCommonOpt = 0;
                else
                    UnixCommonOpt = 1;          /*  unix common type        */
                break;
            default:
                goto fail;
            }
            break;
        default:
fail:
            if (c1Only)
                help();
        }
    }
    if (MC68020Opt)
        printf("\tmc68020\n");
    if (MC68881Opt)
        printf("\tmc68881\n");
    if (PIOpt) {
        AbsData   = 0;
        SmallData = 1;
        SmallCode = 1;
    }
}

