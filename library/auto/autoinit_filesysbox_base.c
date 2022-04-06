/*
**	$Id$
**	Generated by IDLTool 53.31
**	Do not edit
**
**	AutoInit stub for filesysbox
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <exec/types.h>
#include <utility/tagitem.h>
#include <libraries/filesysbox.h>
#include <devices/timer.h>

#include <interfaces/filesysbox.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

/****************************************************************************/

struct Library * FileSysBoxBase = NULL;
static struct Library * __FileSysBoxBase = NULL;

/****************************************************************************/

void filesysbox_base_constructor(void)
{
    if (FileSysBoxBase != NULL)
    {
        return; /* Someone was quicker, e.g. an interface constructor */
    }
    __FileSysBoxBase = FileSysBoxBase = IExec->OpenLibrary("filesysbox.library", 0);
    if (FileSysBoxBase == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "filesysbox.library");
        abort();
    }
}
__attribute__((section(".ctors.zzzz"))) static void
(*filesysbox_base_constructor_ptr)(void) USED = filesysbox_base_constructor;

/****************************************************************************/

void filesysbox_base_destructor(void)
{
    if (__FileSysBoxBase != NULL)
    {
        IExec->CloseLibrary(__FileSysBoxBase);
    }
}
__attribute__((section(".dtors.zzzz"))) static void
(*filesysbox_base_destructor_ptr)(void) USED = filesysbox_base_destructor;

/****************************************************************************/

