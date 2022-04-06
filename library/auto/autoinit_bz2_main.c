/*
**	$Id$
**	Generated by IDLTool 53.31
**	Do not edit
**
**	AutoInit stub for bz2
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <libraries/bz2.h>
#include <stdio.h>

#include <interfaces/bz2.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

struct BZ2IFace * IBZ2 = NULL;
static struct Library * __BZ2Base = NULL;
static struct BZ2IFace * __IBZ2 = NULL;

/****************************************************************************/

extern struct Library * BZ2Base;

/****************************************************************************/

void bz2_main_constructor(void)
{
    if (IBZ2 != NULL)
    {
        return; /* Someone was quicker */
    }
    if (BZ2Base == NULL) /* Library base is NULL, we need to open it */
    {
        /* We were called before the base constructor.
         * This means we will be called _after_ the base destructor.
         * So we cant drop the interface _after_ closing the last library base,
         * we just open the library here which ensures that.
         */
        __BZ2Base = BZ2Base = IExec->OpenLibrary("bz2.library", 0);
        if (BZ2Base == NULL)
        {
            BPTR StdErr = IDOS->ErrorOutput();
            if (StdErr == ZERO)
                StdErr = IDOS->Output();
            IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "bz2.library");
            abort();
        }
    }

    __IBZ2 = IBZ2 = (struct BZ2IFace *)IExec->GetInterface((struct Library *)BZ2Base, "main", 1, NULL);
    if (IBZ2 == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to get '%s' V%ld interface for '%s'.\n", "main", 1, "bz2.library");
        abort();
    }
}
__attribute__((section(".ctors.zzzy"))) static void
(*bz2_main_constructor_ptr)(void) USED = bz2_main_constructor;

/****************************************************************************/

void bz2_main_destructor(void)
{
    if (__IBZ2)
    {
        IExec->DropInterface ((struct Interface *)__IBZ2);
    }
    if (__BZ2Base)
    {
        IExec->CloseLibrary(__BZ2Base);
    }
}
__attribute__((section(".dtors.zzzy"))) static void
(*bz2_main_destructor_ptr)(void) USED = bz2_main_destructor;

/****************************************************************************/

