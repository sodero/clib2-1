/*
**	$Id$
**	Generated by IDLTool 53.31
**	Do not edit
**
**	AutoInit stub for bullet
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <utility/tagitem.h>
#include <diskfont/glyph.h>

#include <interfaces/bullet.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

/****************************************************************************/

struct Library * BulletBase = NULL;
static struct Library * __BulletBase = NULL;

/****************************************************************************/

void bullet_base_constructor(void)
{
    if (BulletBase != NULL)
    {
        return; /* Someone was quicker, e.g. an interface constructor */
    }
    __BulletBase = BulletBase = IExec->OpenLibrary("bullet.library", 0);
    if (BulletBase == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "bullet.library");
        abort();
    }
}
__attribute__((section(".ctors.zzzz"))) static void
(*bullet_base_constructor_ptr)(void) USED = bullet_base_constructor;

/****************************************************************************/

void bullet_base_destructor(void)
{
    if (__BulletBase != NULL)
    {
        IExec->CloseLibrary(__BulletBase);
    }
}
__attribute__((section(".dtors.zzzz"))) static void
(*bullet_base_destructor_ptr)(void) USED = bullet_base_destructor;

/****************************************************************************/

