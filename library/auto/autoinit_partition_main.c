/*
**	$Id$
**	Generated by IDLTool 53.31
**	Do not edit
**
**	AutoInit stub for partition
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <exec/types.h>
#include <intuition/classes.h>

#include <interfaces/partition.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

struct PartitionIFace * IPartition = NULL;
static struct Library * __PartitionBase = NULL;
static struct PartitionIFace * __IPartition = NULL;

/****************************************************************************/

extern struct Library * PartitionBase;

/****************************************************************************/

void partition_main_constructor(void)
{
    if (IPartition != NULL)
    {
        return; /* Someone was quicker */
    }
    if (PartitionBase == NULL) /* Library base is NULL, we need to open it */
    {
        /* We were called before the base constructor.
         * This means we will be called _after_ the base destructor.
         * So we cant drop the interface _after_ closing the last library base,
         * we just open the library here which ensures that.
         */
        __PartitionBase = PartitionBase = IExec->OpenLibrary("gadgets/partition.gadget", 0);
        if (PartitionBase == NULL)
        {
            BPTR StdErr = IDOS->ErrorOutput();
            if (StdErr == ZERO)
                StdErr = IDOS->Output();
            IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "gadgets/partition.gadget");
            abort();
        }
    }

    __IPartition = IPartition = (struct PartitionIFace *)IExec->GetInterface((struct Library *)PartitionBase, "main", 1, NULL);
    if (IPartition == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to get '%s' V%ld interface for '%s'.\n", "main", 1, "gadgets/partition.gadget");
        abort();
    }
}
__attribute__((section(".ctors.zzzy"))) static void
(*partition_main_constructor_ptr)(void) USED = partition_main_constructor;

/****************************************************************************/

void partition_main_destructor(void)
{
    if (__IPartition)
    {
        IExec->DropInterface ((struct Interface *)__IPartition);
    }
    if (__PartitionBase)
    {
        IExec->CloseLibrary(__PartitionBase);
    }
}
__attribute__((section(".dtors.zzzy"))) static void
(*partition_main_destructor_ptr)(void) USED = partition_main_destructor;

/****************************************************************************/

