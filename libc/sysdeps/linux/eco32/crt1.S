/*
 * libc/sysdeps/linux/eco32/crt0.S -- entry point for linux/eco32
 *
 *  Copyright (C) 2014 Stefan Kristiansson <stefan.kristiansson@saunalahti.fi>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Library General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

.text
	.globl	_start
	.type	_start,%function
	.type	_init,%function
	.type	_fini,%function
#ifndef __UCLIBC_CTOR_DTOR__
	.weak   _init
	.weak   _fini
#endif
	.type   main,@function
	.type   __uClibc_main,@function
_start:
	/* Setup the arguments to __uClibc_main. */
	ori	$4,$0,main	/*  main */
	ldw	$5,$29,0	/* argc */
	ldw	$6,$29,4	/* argv */
	ori	$7,$0,_init	/* init */
	/* adjust stack for the last three args and regs $4 to $7 */
	subi	$29,$29,12 + 16
	ori	$8,$0,_fini	/* _fini */
	stw	$8,$29,16
	ori	$8,$0,0
	stw	$8,$29,20 	/* rtld_fini = NULL */
	stw	$29,$29,24	/* stack end */

	j	__uClibc_main

.size _start,.-_start

/* Define a symbol for the first piece of initialized data.  */
	.data
	.globl __data_start
__data_start:
	.long 0
	.weak data_start
	data_start = __data_start
