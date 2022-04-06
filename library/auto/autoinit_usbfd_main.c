/*
**	$Id$
**	Generated by IDLTool 53.31
**	Do not edit
**
**	AutoInit stub for usbfd
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <exec/types.h>

#include <interfaces/usbfd.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

struct USBFDIFace * IUSBFD = NULL;
static struct Library * __USBFDBase = NULL;
static struct USBFDIFace * __IUSBFD = NULL;

/****************************************************************************/

extern struct Library * USBFDBase;

/****************************************************************************/

void usbfd_main_constructor(void)
{
    if (IUSBFD != NULL)
    {
        return; /* Someone was quicker */
    }
    if (USBFDBase == NULL) /* Library base is NULL, we need to open it */
    {
        /* We were called before the base constructor.
         * This means we will be called _after_ the base destructor.
         * So we cant drop the interface _after_ closing the last library base,
         * we just open the library here which ensures that.
         */
        __USBFDBase = USBFDBase = IExec->OpenLibrary("usbfd.library", 0);
        if (USBFDBase == NULL)
        {
            BPTR StdErr = IDOS->ErrorOutput();
            if (StdErr == ZERO)
                StdErr = IDOS->Output();
            IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "usbfd.library");
            abort();
        }
    }

    __IUSBFD = IUSBFD = (struct USBFDIFace *)IExec->GetInterface((struct Library *)USBFDBase, "main", 1, NULL);
    if (IUSBFD == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to get '%s' V%ld interface for '%s'.\n", "main", 1, "usbfd.library");
        abort();
    }
}
__attribute__((section(".ctors.zzzy"))) static void
(*usbfd_main_constructor_ptr)(void) USED = usbfd_main_constructor;

/****************************************************************************/

void usbfd_main_destructor(void)
{
    if (__IUSBFD)
    {
        IExec->DropInterface ((struct Interface *)__IUSBFD);
    }
    if (__USBFDBase)
    {
        IExec->CloseLibrary(__USBFDBase);
    }
}
__attribute__((section(".dtors.zzzy"))) static void
(*usbfd_main_destructor_ptr)(void) USED = usbfd_main_destructor;

/****************************************************************************/

