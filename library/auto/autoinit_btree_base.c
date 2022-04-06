/*
**	$Id$
**	Generated by IDLTool 53.31
**	Do not edit
**
**	AutoInit stub for btree
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <exec/types.h>
#include <libraries/btree.h>

#include <interfaces/btree.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

/****************************************************************************/

struct Library * BTreeBase = NULL;
static struct Library * __BTreeBase = NULL;

/****************************************************************************/

void btree_base_constructor(void)
{
    if (BTreeBase != NULL)
    {
        return; /* Someone was quicker, e.g. an interface constructor */
    }
    __BTreeBase = BTreeBase = IExec->OpenLibrary("btree.library", 0);
    if (BTreeBase == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "btree.library");
        abort();
    }
}
__attribute__((section(".ctors.zzzz"))) static void
(*btree_base_constructor_ptr)(void) USED = btree_base_constructor;

/****************************************************************************/

void btree_base_destructor(void)
{
    if (__BTreeBase != NULL)
    {
        IExec->CloseLibrary(__BTreeBase);
    }
}
__attribute__((section(".dtors.zzzz"))) static void
(*btree_base_destructor_ptr)(void) USED = btree_base_destructor;

/****************************************************************************/

