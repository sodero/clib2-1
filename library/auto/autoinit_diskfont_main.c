/*
**	$Id$
**	Generated by IDLTool 53.31
**	Do not edit
**
**	AutoInit stub for diskfont
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <dos/dos.h>
#include <libraries/diskfont.h>
#include <utility/tagitem.h>
#include <graphics/rastport.h>

#include <interfaces/diskfont.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

struct DiskfontIFace * IDiskfont = NULL;
static struct Library * __DiskfontBase = NULL;
static struct DiskfontIFace * __IDiskfont = NULL;

/****************************************************************************/

extern struct Library * DiskfontBase;

/****************************************************************************/

void diskfont_main_constructor(void)
{
    if (IDiskfont != NULL)
    {
        return; /* Someone was quicker */
    }
    if (DiskfontBase == NULL) /* Library base is NULL, we need to open it */
    {
        /* We were called before the base constructor.
         * This means we will be called _after_ the base destructor.
         * So we cant drop the interface _after_ closing the last library base,
         * we just open the library here which ensures that.
         */
        __DiskfontBase = DiskfontBase = IExec->OpenLibrary("diskfont.library", 0);
        if (DiskfontBase == NULL)
        {
            BPTR StdErr = IDOS->ErrorOutput();
            if (StdErr == ZERO)
                StdErr = IDOS->Output();
            IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "diskfont.library");
            abort();
        }
    }

    __IDiskfont = IDiskfont = (struct DiskfontIFace *)IExec->GetInterface((struct Library *)DiskfontBase, "main", 1, NULL);
    if (IDiskfont == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to get '%s' V%ld interface for '%s'.\n", "main", 1, "diskfont.library");
        abort();
    }
}
__attribute__((section(".ctors.zzzy"))) static void
(*diskfont_main_constructor_ptr)(void) USED = diskfont_main_constructor;

/****************************************************************************/

void diskfont_main_destructor(void)
{
    if (__IDiskfont)
    {
        IExec->DropInterface ((struct Interface *)__IDiskfont);
    }
    if (__DiskfontBase)
    {
        IExec->CloseLibrary(__DiskfontBase);
    }
}
__attribute__((section(".dtors.zzzy"))) static void
(*diskfont_main_destructor_ptr)(void) USED = diskfont_main_destructor;

/****************************************************************************/

