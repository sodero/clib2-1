/*
**	$Id$
**	Generated by IDLTool 53.31
**	Do not edit
**
**	AutoInit stub for diskio
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <exec/types.h>
#include <utility/tagitem.h>
#include <libraries/diskio.h>

#include <interfaces/diskio.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

/****************************************************************************/

struct Library * DiskIOBase = NULL;
static struct Library * __DiskIOBase = NULL;

/****************************************************************************/

void diskio_base_constructor(void)
{
    if (DiskIOBase != NULL)
    {
        return; /* Someone was quicker, e.g. an interface constructor */
    }
    __DiskIOBase = DiskIOBase = IExec->OpenLibrary("diskio.library", 0);
    if (DiskIOBase == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "diskio.library");
        abort();
    }
}
__attribute__((section(".ctors.zzzz"))) static void
(*diskio_base_constructor_ptr)(void) USED = diskio_base_constructor;

/****************************************************************************/

void diskio_base_destructor(void)
{
    if (__DiskIOBase != NULL)
    {
        IExec->CloseLibrary(__DiskIOBase);
    }
}
__attribute__((section(".dtors.zzzz"))) static void
(*diskio_base_destructor_ptr)(void) USED = diskio_base_destructor;

/****************************************************************************/

