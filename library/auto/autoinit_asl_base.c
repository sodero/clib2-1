/*
**	$Id$
**	Generated by IDLTool 53.31
**	Do not edit
**
**	AutoInit stub for asl
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <exec/libraries.h>
#include <utility/tagitem.h>
#include <libraries/asl.h>

#include <interfaces/asl.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

/****************************************************************************/

struct Library * AslBase = NULL;
static struct Library * __AslBase = NULL;

/****************************************************************************/

void asl_base_constructor(void)
{
    if (AslBase != NULL)
    {
        return; /* Someone was quicker, e.g. an interface constructor */
    }
    __AslBase = AslBase = IExec->OpenLibrary("asl.library", 0);
    if (AslBase == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "asl.library");
        abort();
    }
}
__attribute__((section(".ctors.zzzz"))) static void
(*asl_base_constructor_ptr)(void) USED = asl_base_constructor;

/****************************************************************************/

void asl_base_destructor(void)
{
    if (__AslBase != NULL)
    {
        IExec->CloseLibrary(__AslBase);
    }
}
__attribute__((section(".dtors.zzzz"))) static void
(*asl_base_destructor_ptr)(void) USED = asl_base_destructor;

/****************************************************************************/

