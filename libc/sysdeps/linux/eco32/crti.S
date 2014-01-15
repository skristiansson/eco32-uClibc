	.section .init
	.global	_init
_init:
	subi	$29,$29,4
	stw	$31,$29,0

	.section .fini
	.global	_fini
_fini:
	subi	$29,$29,4
	stw	$31,$29,0
