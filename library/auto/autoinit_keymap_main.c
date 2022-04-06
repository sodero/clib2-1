/*
**	$Id$
**	Generated by IDLTool 53.31
**	Do not edit
**
**	AutoInit stub for keymap
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <devices/inputevent.h>
#include <libraries/keymap.h>

#include <interfaces/keymap.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

struct KeymapIFace * IKeymap = NULL;
static struct Library * __KeymapBase = NULL;
static struct KeymapIFace * __IKeymap = NULL;

/****************************************************************************/

extern struct Library * KeymapBase;

/****************************************************************************/

void keymap_main_constructor(void)
{
    if (IKeymap != NULL)
    {
        return; /* Someone was quicker */
    }
    if (KeymapBase == NULL) /* Library base is NULL, we need to open it */
    {
        /* We were called before the base constructor.
         * This means we will be called _after_ the base destructor.
         * So we cant drop the interface _after_ closing the last library base,
         * we just open the library here which ensures that.
         */
        __KeymapBase = KeymapBase = IExec->OpenLibrary("keymap.library", 0);
        if (KeymapBase == NULL)
        {
            BPTR StdErr = IDOS->ErrorOutput();
            if (StdErr == ZERO)
                StdErr = IDOS->Output();
            IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "keymap.library");
            abort();
        }
    }

    __IKeymap = IKeymap = (struct KeymapIFace *)IExec->GetInterface((struct Library *)KeymapBase, "main", 1, NULL);
    if (IKeymap == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to get '%s' V%ld interface for '%s'.\n", "main", 1, "keymap.library");
        abort();
    }
}
__attribute__((section(".ctors.zzzy"))) static void
(*keymap_main_constructor_ptr)(void) USED = keymap_main_constructor;

/****************************************************************************/

void keymap_main_destructor(void)
{
    if (__IKeymap)
    {
        IExec->DropInterface ((struct Interface *)__IKeymap);
    }
    if (__KeymapBase)
    {
        IExec->CloseLibrary(__KeymapBase);
    }
}
__attribute__((section(".dtors.zzzy"))) static void
(*keymap_main_destructor_ptr)(void) USED = keymap_main_destructor;

/****************************************************************************/

