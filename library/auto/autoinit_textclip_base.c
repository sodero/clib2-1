/*
**	$Id$
**	Generated by IDLTool 53.31
**	Do not edit
**
**	AutoInit stub for textclip
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <exec/types.h>

#include <interfaces/textclip.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

/****************************************************************************/

struct Library * TextClipBase = NULL;
static struct Library * __TextClipBase = NULL;

/****************************************************************************/

void textclip_base_constructor(void)
{
    if (TextClipBase != NULL)
    {
        return; /* Someone was quicker, e.g. an interface constructor */
    }
    __TextClipBase = TextClipBase = IExec->OpenLibrary("textclip.library", 0);
    if (TextClipBase == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "textclip.library");
        abort();
    }
}
__attribute__((section(".ctors.zzzz"))) static void
(*textclip_base_constructor_ptr)(void) USED = textclip_base_constructor;

/****************************************************************************/

void textclip_base_destructor(void)
{
    if (__TextClipBase != NULL)
    {
        IExec->CloseLibrary(__TextClipBase);
    }
}
__attribute__((section(".dtors.zzzz"))) static void
(*textclip_base_destructor_ptr)(void) USED = textclip_base_destructor;

/****************************************************************************/

