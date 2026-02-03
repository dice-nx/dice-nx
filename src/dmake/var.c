/*
 * $VER: var.c 3.20.0 (23.1.2026)
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 2003-2011,2023 The DragonFly Project.
 * This code is derived from software contributed to The DragonFly Project
 * by Matthew Dillon <dillon@backplane.com>
 */

#include "defs.h"

Prototype void InitVar(void);
Prototype Var *MakeVar(char *, char);
Prototype Var *FindVar(char *, char);
Prototype void AppendVar(Var *, char *, long);
Prototype void InsertVar(Var *, char *, long);

List VarList;

void
InitVar(void)
{
    NewList(&VarList);
}

/*
 *  create a variable, deleting any previous contents
 */

Var *
MakeVar(char *name, char type)
{
    Var *var;

    for (var = GetHead(&VarList); var; var = GetSucc(&var->var_Node)) {
        if ((char)var->var_Node.ln_Type == type && strcmp(var->var_Node.ln_Name, name) == 0) {
            while (PopCmdListChar(&var->var_CmdList) != EOF)
                ;
            return(var);
        }
    }
    var = malloc(sizeof(Var) + strlen(name) + 1);
    bzero(var, sizeof(Var));

    var->var_Node.ln_Name = (char *)(var + 1);
    var->var_Node.ln_Type = type;
    strcpy(var->var_Node.ln_Name, name);
    NewList(&var->var_CmdList);
    AddTail(&VarList, &var->var_Node);
    return(var);
}

Var *
FindVar(char *name, char type)
{
    Var *var;

    for (var = GetHead(&VarList); var; var = GetSucc(&var->var_Node)) {
        if ((char)var->var_Node.ln_Type == type && strcmp(var->var_Node.ln_Name, name) == 0)
            break;
    }

    /*
     *  check for local & env variable(s).  local variables under 2.04
     *  or later only.
     */

    if (var == NULL || var->var_Node.ln_Type == '0') {
        char *ptr;

        if ((ptr = getenv(name)) != NULL) {
            var = MakeVar(name, '0');
            AppendVar(var, ptr, strlen(ptr));
        }
    }
    return(var);
}

void
AppendVar(var, buf, len)
Var *var;
char *buf;
long len;
{
    while (len--)
        PutCmdListChar(&var->var_CmdList, *buf++);
}

void
InsertVar(var, buf, len)
Var *var;
char *buf;
long len;
{
    buf += len;
    while (len--)
        InsCmdListChar(&var->var_CmdList, *--buf);
}

