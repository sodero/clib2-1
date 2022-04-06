/*
**	$Id$
**	Generated by IDLTool 53.31
**	Do not edit
**
**	AutoInit stub for layers
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#include <exec/types.h>
#include <graphics/layers.h>
#include <graphics/clip.h>
#include <graphics/rastport.h>
#include <graphics/regions.h>

#include <interfaces/layers.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

struct LayersIFace * ILayers = NULL;
static struct Library * __LayersBase = NULL;
static struct LayersIFace * __ILayers = NULL;

/****************************************************************************/

extern struct Library * LayersBase;

/****************************************************************************/

void layers_main_constructor(void)
{
    if (ILayers != NULL)
    {
        return; /* Someone was quicker */
    }
    if (LayersBase == NULL) /* Library base is NULL, we need to open it */
    {
        /* We were called before the base constructor.
         * This means we will be called _after_ the base destructor.
         * So we cant drop the interface _after_ closing the last library base,
         * we just open the library here which ensures that.
         */
        __LayersBase = LayersBase = IExec->OpenLibrary("layers.library", 0);
        if (LayersBase == NULL)
        {
            BPTR StdErr = IDOS->ErrorOutput();
            if (StdErr == ZERO)
                StdErr = IDOS->Output();
            IDOS->FPrintf(StdErr, "ERROR: Failed to open '%s'.\n", "layers.library");
            abort();
        }
    }

    __ILayers = ILayers = (struct LayersIFace *)IExec->GetInterface((struct Library *)LayersBase, "main", 1, NULL);
    if (ILayers == NULL)
    {
        BPTR StdErr = IDOS->ErrorOutput();
        if (StdErr == ZERO)
            StdErr = IDOS->Output();
        IDOS->FPrintf(StdErr, "ERROR: Failed to get '%s' V%ld interface for '%s'.\n", "main", 1, "layers.library");
        abort();
    }
}
__attribute__((section(".ctors.zzzy"))) static void
(*layers_main_constructor_ptr)(void) USED = layers_main_constructor;

/****************************************************************************/

void layers_main_destructor(void)
{
    if (__ILayers)
    {
        IExec->DropInterface ((struct Interface *)__ILayers);
    }
    if (__LayersBase)
    {
        IExec->CloseLibrary(__LayersBase);
    }
}
__attribute__((section(".dtors.zzzy"))) static void
(*layers_main_destructor_ptr)(void) USED = layers_main_destructor;

/****************************************************************************/

