/*
 * libc/sysdeps/linux/eco32/setjmp.S
 *
 *  Copyright (C) 2014 Stefan Kristiansson <stefan.kristiansson@saunalahti.fi>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License.  See the file COPYING.LIB in the main
 * directory of this archive for more details.
 */

#include <features.h>
#include <jmpbuf-offsets.h>

	.globl setjmp
	.type  setjmp,@function
setjmp:
	ori	$5,$0,1
	j	__sigsetjmp

.size setjmp,.-setjmp

	.globl _setjmp
	.type  _setjmp,@function
_setjmp:
	ori	$5,$0,0
	j	__sigsetjmp

.size _setjmp,.-_setjmp

	.globl __sigsetjmp
	.type  __sigsetjmp,@function
__sigsetjmp:
	stw	$16,$4,JB_REGS+0
	stw	$17,$4,JB_REGS+4
	stw	$18,$4,JB_REGS+8
	stw	$19,$4,JB_REGS+12
	stw	$20,$4,JB_REGS+16
	stw	$21,$4,JB_REGS+20
	stw	$22,$4,JB_REGS+24
	stw	$23,$4,JB_REGS+28

	stw	$31,$4,JB_PC
	stw	$29,$4,JB_SP
	stw	$28,$4,JB_FP

	ori	$8,$0,__sigjmp_save
	jr	$8

.size __sigsetjmp,.-__sigsetjmp
