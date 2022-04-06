/*
**	$Id$
**	Generated by IDLTool 53.31
**	Do not edit
**
**	AutoInit stub for diffview
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <intuition/intuition.h>
#include <intuition/classes.h>
#include <gadgets/diffview.h>

#include <interfaces/diffview.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

struct DiffViewIFace * IDiffView = NULL;
static struct Library * __DiffViewBase = NULL;
static struct DiffViewIFace * __IDiffView = NULL;

/****************************************************************************/

extern struct Library * DiffViewBase;

/****************************************************************************/

void diffview_main_constructor(void)
{
    if (IDiffView != NULL)
    {
        return; /* Someone was quicker */
    }
    if (DiffViewBase == NULL) /* Library base is NULL, we need to open it */
    {
        /* We were called before the base constructor.
         * This means we will be called _after_ the base destructor.
         * So we cant drop the interface _after_ closing the last library base,
         * we just open the library here which ensures that.
         */
        __DiffViewBase = DiffViewBase = IExec->OpenLibrary("gadgets/diffview.gadget", 0);
        if (DiffViewBase == NULL)
        {
            BPTR StdErr = IDOS->ErrorOutput();
            if (StdErr == ZERO)
                StdErr = IDOS->Output();
            IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "gadgets/diffview.gadget");
            abort();
        }
    }

    __IDiffView = IDiffView = (struct DiffViewIFace *)IExec->GetInterface((struct Library *)DiffViewBase, "main", 1, NULL);
    if (IDiffView == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to get '%s' V%ld interface for '%s'.\n", "main", 1, "gadgets/diffview.gadget");
        abort();
    }
}
__attribute__((section(".ctors.zzzy"))) static void
(*diffview_main_constructor_ptr)(void) USED = diffview_main_constructor;

/****************************************************************************/

void diffview_main_destructor(void)
{
    if (__IDiffView)
    {
        IExec->DropInterface ((struct Interface *)__IDiffView);
    }
    if (__DiffViewBase)
    {
        IExec->CloseLibrary(__DiffViewBase);
    }
}
__attribute__((section(".dtors.zzzy"))) static void
(*diffview_main_destructor_ptr)(void) USED = diffview_main_destructor;

/****************************************************************************/

