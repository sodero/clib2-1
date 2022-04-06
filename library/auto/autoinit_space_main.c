/*
**	$Id$
**	Generated by IDLTool 53.31
**	Do not edit
**
**	AutoInit stub for space
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/space.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/intuition.h>
#include <stdlib.h>

static struct Library * __IntuitionBase = NULL;
static struct IntuitionIFace *__IIntuition = NULL;
struct SpaceIFace * ISpace = NULL;
static struct ClassLibrary * __SpaceBase = NULL;
static struct SpaceIFace * __ISpace = NULL;

/****************************************************************************/

extern struct ClassLibrary * SpaceBase;
extern Class * SpaceClass;

/****************************************************************************/

void space_main_constructor(void)
{
    if (ISpace != NULL)
    {
        return; /* Someone was quicker */
    }
    if (SpaceBase == NULL) /* Library base is NULL, we need to open it */
    {
        if (IIntuition == NULL)
        {
            if (IntuitionBase == NULL)
            {
                __IntuitionBase = IntuitionBase = IExec->OpenLibrary("intuition.library", 0);
                if (IntuitionBase == NULL)
                {
                    BPTR StdErr = IDOS->ErrorOutput();
                    if (StdErr == ZERO)
                        StdErr = IDOS->Output();
                    IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "intuition.library");
                    abort();
                }
            }
            __IIntuition = IIntuition = (struct IntuitionIFace *)IExec->GetInterface(IntuitionBase, "main", 1, NULL);
            if (IIntuition == NULL)
            {
                BPTR StdErr = IDOS->ErrorOutput();
                if (StdErr == ZERO)
                    StdErr = IDOS->Output();
                IDOS->FPrintf(StdErr, "ERROR: Failed to get '%s' V%ld interface for '%s'.\n", "main", 1, "intuition.library");
                abort();
            }
        }
        /* We were called before the base constructor.
         * This means we will be called _after_ the base destructor.
         * So we cant drop the interface _after_ closing the last library base,
         * we just open the library here which ensures that.
         */
        __SpaceBase = SpaceBase = IIntuition->OpenClass("gadgets/space.gadget", 0, &SpaceClass);
        if (SpaceBase == NULL)
        {
            BPTR StdErr = IDOS->ErrorOutput();
            if (StdErr == ZERO)
                StdErr = IDOS->Output();
            IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "gadgets/space.gadget");
            abort();
        }
    }

    __ISpace = ISpace = (struct SpaceIFace *)IExec->GetInterface((struct Library *)SpaceBase, "main", 1, NULL);
    if (ISpace == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to get '%s' V%ld interface for '%s'.\n", "main", 1, "gadgets/space.gadget");
        abort();
    }
}
__attribute__((section(".ctors.zzzy"))) static void
(*space_main_constructor_ptr)(void) USED = space_main_constructor;

/****************************************************************************/

void space_main_destructor(void)
{
    if (__ISpace)
    {
        IExec->DropInterface ((struct Interface *)__ISpace);
    }
    if (__SpaceBase != NULL)
    {
        IIntuition->CloseClass(__SpaceBase);
    }
    if (__IIntuition != NULL)
    {
        IExec->DropInterface((struct Interface *)__IIntuition);
    }
    if (__IntuitionBase != NULL)
    {
        IExec->CloseLibrary(__IntuitionBase);
    }
}
__attribute__((section(".dtors.zzzy"))) static void
(*space_main_destructor_ptr)(void) USED = space_main_destructor;

/****************************************************************************/

