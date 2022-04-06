/*
**	$Id$
**	Generated by IDLTool 53.31
**	Do not edit
**
**	AutoInit stub for usbsys
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <usb/system.h>

#include <interfaces/usbsys.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

struct USBSysIFace * IUSBSys = NULL;
static struct Library * __USBSysBase = NULL;
static struct USBSysIFace * __IUSBSys = NULL;

/****************************************************************************/

extern struct Library * USBSysBase;

/****************************************************************************/

void usbsys_main_constructor(void)
{
    if (IUSBSys != NULL)
    {
        return; /* Someone was quicker */
    }
    if (USBSysBase == NULL) /* Library base is NULL, we need to open it */
    {
        /* We were called before the base constructor.
         * This means we will be called _after_ the base destructor.
         * So we cant drop the interface _after_ closing the last library base,
         * we just open the library here which ensures that.
         */
        __USBSysBase = USBSysBase = IExec->OpenLibrary("usbsys.device", 0);
        if (USBSysBase == NULL)
        {
            BPTR StdErr = IDOS->ErrorOutput();
            if (StdErr == ZERO)
                StdErr = IDOS->Output();
            IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "usbsys.device");
            abort();
        }
    }

    __IUSBSys = IUSBSys = (struct USBSysIFace *)IExec->GetInterface((struct Library *)USBSysBase, "main", 1, NULL);
    if (IUSBSys == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to get '%s' V%ld interface for '%s'.\n", "main", 1, "usbsys.device");
        abort();
    }
}
__attribute__((section(".ctors.zzzy"))) static void
(*usbsys_main_constructor_ptr)(void) USED = usbsys_main_constructor;

/****************************************************************************/

void usbsys_main_destructor(void)
{
    if (__IUSBSys)
    {
        IExec->DropInterface ((struct Interface *)__IUSBSys);
    }
    if (__USBSysBase)
    {
        IExec->CloseLibrary(__USBSysBase);
    }
}
__attribute__((section(".dtors.zzzy"))) static void
(*usbsys_main_destructor_ptr)(void) USED = usbsys_main_destructor;

/****************************************************************************/

