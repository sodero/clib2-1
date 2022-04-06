/*
**	$Id$
**	Generated by IDLTool 53.31
**	Do not edit
**
**	AutoInit stub for bitmap
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/bitmap.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

struct BitMapIFace * IBitMap = NULL;
static struct Library * __BitMapBase = NULL;
static struct BitMapIFace * __IBitMap = NULL;

/****************************************************************************/

extern struct Library * BitMapBase;

/****************************************************************************/

void bitmap_main_constructor(void)
{
    if (IBitMap != NULL)
    {
        return; /* Someone was quicker */
    }
    if (BitMapBase == NULL) /* Library base is NULL, we need to open it */
    {
        /* We were called before the base constructor.
         * This means we will be called _after_ the base destructor.
         * So we cant drop the interface _after_ closing the last library base,
         * we just open the library here which ensures that.
         */
        __BitMapBase = BitMapBase = IExec->OpenLibrary("images/bitmap.image", 0);
        if (BitMapBase == NULL)
        {
            BPTR StdErr = IDOS->ErrorOutput();
            if (StdErr == ZERO)
                StdErr = IDOS->Output();
            IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "images/bitmap.image");
            abort();
        }
    }

    __IBitMap = IBitMap = (struct BitMapIFace *)IExec->GetInterface((struct Library *)BitMapBase, "main", 1, NULL);
    if (IBitMap == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to get '%s' V%ld interface for '%s'.\n", "main", 1, "images/bitmap.image");
        abort();
    }
}
__attribute__((section(".ctors.zzzy"))) static void
(*bitmap_main_constructor_ptr)(void) USED = bitmap_main_constructor;

/****************************************************************************/

void bitmap_main_destructor(void)
{
    if (__IBitMap)
    {
        IExec->DropInterface ((struct Interface *)__IBitMap);
    }
    if (__BitMapBase)
    {
        IExec->CloseLibrary(__BitMapBase);
    }
}
__attribute__((section(".dtors.zzzy"))) static void
(*bitmap_main_destructor_ptr)(void) USED = bitmap_main_destructor;

/****************************************************************************/

