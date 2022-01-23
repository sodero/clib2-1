/*
 * $Id: stdlib_dlopen.c,v 1.2 2010-08-21 11:37:03 obarthel Exp $
 *
 * :ts=4
 *
 * Portable ISO 'C' (1994) runtime library for the Amiga computer
 * Copyright (c) 2002-2015 by Olaf Barthel <obarthel (at) gmx.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   - Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   - Neither the name of Olaf Barthel nor the names of contributors
 *     may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _STDLIB_HEADERS_H
#include "stdlib_headers.h"
#endif /* _STDLIB_HEADERS_H */

/****************************************************************************/

#include <dlfcn.h>
#include <libraries/elf.h>
#include <proto/elf.h>

void *dlopen(const char *path_name, int mode)
{
	void *result = NULL;

	if (path_name == NULL || path_name[0] == '\0') {
		__set_errno(ENOENT);
		goto out;
	}

#if defined(UNIX_PATH_SEMANTICS)
	struct name_translation_info path_name_nti;
	if (__global_clib2 != NULL && __global_clib2->__unix_path_semantics)
	{
		if (__translate_unix_to_amiga_path_name(&path_name, &path_name_nti) != 0)
			goto out;

		if (path_name_nti.is_root)
		{
			__set_errno(EACCES);
			goto out;
		}
	}
#endif /* UNIX_PATH_SEMANTICS */

	if (__global_clib2->__dl_elf_handle != NULL)
	{
		struct ElfIFace *IElf = __global_clib2->IElf;
		uint32 flags = 0;

		if (mode & RTLD_LOCAL)
			flags = ELF32_RTLD_LOCAL;

		if (mode & RTLD_GLOBAL)
			flags = ELF32_RTLD_GLOBAL;

		result = DLOpen(__global_clib2->__dl_elf_handle, path_name, flags);
	}
	else
	{
		__set_errno(ENOSYS);
	}
out:

	return (result);
}