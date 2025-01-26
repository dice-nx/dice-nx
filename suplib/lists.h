/*
 * DICE-NX project - https://dice-nx.dev/
 *
 * Copyright 1992-1997 Obvious Implementations Corp.
 * Copyright 2023- DICE-NX project contributors
 *
 * Licensed under the BSD-3-Clause License, as written in the LICENSE file
 * at the root of this project.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 *  LISTS.H - Amiga compatibility
 */

struct List {
    struct Node *lh_Head;
    struct Node *lh_Tail;
    struct Node *lh_TailPred;
    unsigned char lh_Type;
    unsigned char lh_Pad;
};

struct MinList {
    struct MinNode *mlh_Head;
    struct MinNode *mlh_Tail;
    struct MinNode *mlh_TailPred;
};

struct Node {
    struct Node *ln_Succ;
    struct Node *ln_Pred;
    unsigned char ln_Type;
    char ln_Pri;
    char *ln_Name;
};

struct MinNode {
    struct MinNode *mln_Succ;
    struct MinNode *mln_Pred;
};

extern void NewList(struct List *);
extern void *RemHead(struct List *);
extern void AddHead(struct List *, struct Node *);
extern void AddTail(struct List *, struct Node *);
extern void *GetHead(struct List *);
extern void *GetTail(struct List *);
extern void *GetSucc(struct Node *);
extern void *GetPred(struct Node *);
extern void *Remove(struct Node *);
extern void *FindName(struct List *, const char *);
extern void Enqueue(struct List *, struct Node *);
extern void Insert(struct List *, struct Node *, struct Node *);

