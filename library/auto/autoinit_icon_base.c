/*
**	$Id$
**	Generated by IDLTool 53.31
**	Do not edit
**
**	AutoInit stub for icon
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <workbench/workbench.h>
#include <datatypes/pictureclass.h>

#include <interfaces/icon.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

/****************************************************************************/

struct Library * IconBase = NULL;
static struct Library * __IconBase = NULL;

/****************************************************************************/

void icon_base_constructor(void)
{
    if (IconBase != NULL)
    {
        return; /* Someone was quicker, e.g. an interface constructor */
    }
    __IconBase = IconBase = IExec->OpenLibrary("icon.library", 0);
    if (IconBase == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "icon.library");
        abort();
    }
}
__attribute__((section(".ctors.zzzz"))) static void
(*icon_base_constructor_ptr)(void) USED = icon_base_constructor;

/****************************************************************************/

void icon_base_destructor(void)
{
    if (__IconBase != NULL)
    {
        IExec->CloseLibrary(__IconBase);
    }
}
__attribute__((section(".dtors.zzzz"))) static void
(*icon_base_destructor_ptr)(void) USED = icon_base_destructor;

/****************************************************************************/

