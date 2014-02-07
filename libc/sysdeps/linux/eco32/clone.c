/*
 * libc/sysdeps/linux/eco32/clone.c -- `clone' syscall for eco32
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 *
 *
 *  Copyright (C) 2004,05  Microtronix Datacom Ltd
 *  Copyright (C) 2002,03  NEC Electronics Corporation
 *  Copyright (C) 2002,03  Miles Bader <miles@gnu.org>
 */

#include <errno.h>
#include <sys/syscall.h>

int
clone (int (*fn)(void *arg), void *child_stack, int flags, void *arg, ...)
{
	int err = -EINVAL;

	if (fn && child_stack) {
		err = INLINE_SYSCALL(clone, 2, flags, child_stack);
		/* call fn and exit on child thread */
		if (err == 0)
			_exit(fn(arg));
	}

	if (err < 0) {
		__set_errno(-err);
		return -1;
	}

	return err;
}
