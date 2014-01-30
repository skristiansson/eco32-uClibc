#ifndef _BITS_SYSCALLS_H
#define _BITS_SYSCALLS_H
#ifndef _SYSCALL_H
# error "Never use <bits/syscalls.h> directly; include <sys/syscall.h> instead."
#endif

#ifndef __ASSEMBLER__

#include <errno.h>

/*
 * GCC can't handle a constraint on $25 directly, hence the extra ori.
 * I think this might be related to that $25 is a fixed register,
 * but it needs investigation in gcc.
 */
#define INTERNAL_SYSCALL_NCS(name, err, nr, args...)			\
(__extension__								\
({									\
	register long __ret __asm__("$2");				\
	long _scno = name;						\
	LOAD_ARGS_##nr(args);						\
	__asm__ __volatile__("ori $25,%1,0\n"				\
			     "trap"					\
			     : "=r"(__ret), "=r"(_scno)			\
			       ASM_ARGS_##nr(=r)			\
			     : "r"(_scno) ASM_ARGS_##nr(r)		\
			     : ASM_CLOBBERS_##nr			\
			       "$10", "$11", "$12", "$13",		\
			       "$14", "$15", "memory");			\
	__ret;								\
})									\
)
#define INTERNAL_SYSCALL_ERROR_P(val, err)	\
	((unsigned long)(val) >= (unsigned long)(-125))

#define LOAD_ARGS_0() do { } while(0)
#define ASM_ARGS_0(x)
#define ASM_CLOBBERS_0	"$4", ASM_CLOBBERS_1
#define LOAD_ARGS_1(a1)				\
	register long _a1 __asm__("$4") = (long)(a1);	\
	LOAD_ARGS_0()
#define ASM_ARGS_1(x)	ASM_ARGS_0(x), #x(_a1)
#define ASM_CLOBBERS_1	"$5", ASM_CLOBBERS_2
#define LOAD_ARGS_2(a1, a2)				\
	register long _a2 __asm__("$5") = (long)(a2);	\
	LOAD_ARGS_1(a1)
#define ASM_ARGS_2(x)	ASM_ARGS_1(x), #x(_a2)
#define ASM_CLOBBERS_2	"$6", ASM_CLOBBERS_3
#define LOAD_ARGS_3(a1, a2, a3)				\
	register long _a3 __asm__("$6") = (long)(a3);	\
	LOAD_ARGS_2(a1, a2)
#define ASM_ARGS_3(x)	ASM_ARGS_2(x), #x(_a3)
#define ASM_CLOBBERS_3	"$7", ASM_CLOBBERS_4
#define LOAD_ARGS_4(a1, a2, a3, a4)			\
	register long _a4 __asm__("$7") = (long)(a4);	\
	LOAD_ARGS_3(a1, a2, a3)
#define ASM_ARGS_4(x)	ASM_ARGS_3(x), #x(_a4)
#define ASM_CLOBBERS_4	"$8", ASM_CLOBBERS_5
/* The rest aren't real function parameter registers */
#define LOAD_ARGS_5(a1, a2, a3, a4, a5)			\
	register long _a5 __asm__("$8") = (long)(a5);	\
	LOAD_ARGS_4(a1, a2, a3, a4)
#define ASM_ARGS_5(x)	ASM_ARGS_4(x), #x(_a5)
#define ASM_CLOBBERS_5	"$9", ASM_CLOBBERS_6
#define LOAD_ARGS_6(a1, a2, a3, a4, a5, a6)		\
	register long _a6 __asm__("$9") = (long)(a6);	\
	LOAD_ARGS_5(a1, a2, a3, a4, a5)
#define ASM_ARGS_6(x)	ASM_ARGS_5(x), #x(_a6)
#define ASM_CLOBBERS_6

#endif /* __ASSEMBLER__ */
#endif /* _BITS_SYSCALLS_H */
