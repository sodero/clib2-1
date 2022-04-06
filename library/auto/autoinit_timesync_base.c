/*
**	$Id$
**	Generated by IDLTool 53.31
**	Do not edit
**
**	AutoInit stub for timesync
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <libraries/timesync.h>

#include <interfaces/timesync.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

/****************************************************************************/

struct Library * TimesyncBase = NULL;
static struct Library * __TimesyncBase = NULL;

/****************************************************************************/

void timesync_base_constructor(void)
{
    if (TimesyncBase != NULL)
    {
        return; /* Someone was quicker, e.g. an interface constructor */
    }
    __TimesyncBase = TimesyncBase = IExec->OpenLibrary("timesync.library", 0);
    if (TimesyncBase == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "timesync.library");
        abort();
    }
}
__attribute__((section(".ctors.zzzz"))) static void
(*timesync_base_constructor_ptr)(void) USED = timesync_base_constructor;

/****************************************************************************/

void timesync_base_destructor(void)
{
    if (__TimesyncBase != NULL)
    {
        IExec->CloseLibrary(__TimesyncBase);
    }
}
__attribute__((section(".dtors.zzzz"))) static void
(*timesync_base_destructor_ptr)(void) USED = timesync_base_destructor;

/****************************************************************************/

