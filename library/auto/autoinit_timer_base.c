/*
**	$Id$
**	Generated by IDLTool 53.31
**	Do not edit
**
**	AutoInit stub for timer
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <devices/timer.h>

#include <interfaces/timer.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

/****************************************************************************/

struct Library * TimerBase = NULL;
static struct Library * __TimerBase = NULL;

/****************************************************************************/

void timer_base_constructor(void)
{
    if (TimerBase != NULL)
    {
        return; /* Someone was quicker, e.g. an interface constructor */
    }
    __TimerBase = TimerBase = IExec->OpenLibrary("timer.device", 0);
    if (TimerBase == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "timer.device");
        abort();
    }
}
__attribute__((section(".ctors.zzzz"))) static void
(*timer_base_constructor_ptr)(void) USED = timer_base_constructor;

/****************************************************************************/

void timer_base_destructor(void)
{
    if (__TimerBase != NULL)
    {
        IExec->CloseLibrary(__TimerBase);
    }
}
__attribute__((section(".dtors.zzzz"))) static void
(*timer_base_destructor_ptr)(void) USED = timer_base_destructor;

/****************************************************************************/

