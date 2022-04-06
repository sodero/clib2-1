/*
**	$Id$
**	Generated by IDLTool 53.31
**	Do not edit
**
**	AutoInit stub for ramdrive
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <exec/types.h>

#include <interfaces/ramdrive.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

/****************************************************************************/

struct Library * RamdriveDevice = NULL;
static struct Library * __RamdriveDevice = NULL;

/****************************************************************************/

void ramdrive_base_constructor(void)
{
    if (RamdriveDevice != NULL)
    {
        return; /* Someone was quicker, e.g. an interface constructor */
    }
    __RamdriveDevice = RamdriveDevice = IExec->OpenLibrary("ramdrive.device", 0);
    if (RamdriveDevice == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "ramdrive.device");
        abort();
    }
}
__attribute__((section(".ctors.zzzz"))) static void
(*ramdrive_base_constructor_ptr)(void) USED = ramdrive_base_constructor;

/****************************************************************************/

void ramdrive_base_destructor(void)
{
    if (__RamdriveDevice != NULL)
    {
        IExec->CloseLibrary(__RamdriveDevice);
    }
}
__attribute__((section(".dtors.zzzz"))) static void
(*ramdrive_base_destructor_ptr)(void) USED = ramdrive_base_destructor;

/****************************************************************************/

