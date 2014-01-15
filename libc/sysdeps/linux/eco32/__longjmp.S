/*
 * libc/sysdeps/linux/eco32/__longjmp.S
 *
 *  Copyright (C) 2014 Stefan Kristiansson <stefan.kristiansson@saunalahti.fi>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License.  See the file COPYING.LIB in the main
 * directory of this archive for more details.
 */

#include <features.h>
#include <jmpbuf-offsets.h>

.globl __longjmp
.type  __longjmp,@function

__longjmp:
	ori	$2,$5,0		/* return value in 2nd arg */

	/* restore callee saved regs.  */
	ldw	$16,$4,JB_REGS+0
	ldw	$17,$4,JB_REGS+4
	ldw 	$18,$4,JB_REGS+8
	ldw 	$19,$4,JB_REGS+12
	ldw	$20,$4,JB_REGS+16
	ldw	$21,$4,JB_REGS+20
	ldw	$22,$4,JB_REGS+24
	ldw	$23,$4,JB_REGS+28

	ldw	$31,$4,JB_PC
	ldw	$28,$4,JB_FP
	ldw	$29,$4,JB_SP

	jr	$31

.size __longjmp,.-__longjmp
libc_hidden_def(__longjmp)
