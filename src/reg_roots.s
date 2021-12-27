	.file	"reg_roots.s"
	.text
	.globl	find_register_roots
	.type	find_register_roots, @function
find_register_roots:
	endbr64	

	pushq	%rdi # save rdi (state)

	movq	(%rdi), %rdi # rdi = state->pointers
	movq	%rbx, %rsi
	call	long_table_find@PLT	#
	cmpq	$0, %rax
	je	.RBX_FALSE # if null, continue

	popq	%rdi # restore rdi
	pushq	%rdi
	movq	(%rdi), %rdi # rdi = state->pointers
	movq	%rax, %rsi
	call	add_root@PLT
.RBX_FALSE:
	popq	%rdi # restore rdi
	pushq	%rdi

	movq	(%rdi), %rdi # rdi = state->pointers
	movq	%rbp, %rsi
	call	long_table_find@PLT	#
	cmpq	$0, %rax
	je	.RBP_FALSE # if null, continue

	popq	%rdi # restore rdi
	pushq	%rdi
	movq	(%rdi), %rdi # rdi = state->pointers
	movq	%rax, %rsi
	call	add_root@PLT
.RBP_FALSE:
	popq	%rdi # restore rdi
	pushq	%rdi

	movq	(%rdi), %rdi # rdi = state->pointers
	movq	%r12, %rsi
	call	long_table_find@PLT	#
	cmpq	$0, %rax
	je	.R12_FALSE # if null, continue

	popq	%rdi # restore rdi
	pushq	%rdi
	movq	(%rdi), %rdi # rdi = state->pointers
	movq	%rax, %rsi
	call	add_root@PLT
.R12_FALSE:
	popq	%rdi # restore rdi
	pushq	%rdi

	movq	(%rdi), %rdi # rdi = state->pointers
	movq	%r13, %rsi
	call	long_table_find@PLT	#
	cmpq	$0, %rax
	je	.R13_FALSE # if null, continue

	popq	%rdi # restore rdi
	pushq	%rdi
	movq	(%rdi), %rdi # rdi = state->pointers
	movq	%rax, %rsi
	call	add_root@PLT
.R13_FALSE:
	popq	%rdi # restore rdi
	pushq	%rdi

	movq	(%rdi), %rdi # rdi = state->pointers
	movq	%r14, %rsi
	call	long_table_find@PLT	#
	cmpq	$0, %rax
	je	.R14_FALSE # if null, continue

	popq	%rdi # restore rdi
	pushq	%rdi
	movq	(%rdi), %rdi # rdi = state->pointers
	movq	%rax, %rsi
	call	add_root@PLT
.R14_FALSE:
	popq	%rdi # restore rdi
	pushq	%rdi

	movq	(%rdi), %rdi # rdi = state->pointers
	movq	%r15, %rsi
	call	long_table_find@PLT	#
	cmpq	$0, %rax
	je	.R15_FALSE # if null, continue

	popq	%rdi # restore rdi
	pushq	%rdi
	movq	(%rdi), %rdi # rdi = state->pointers
	movq	%rax, %rsi
	call	add_root@PLT
.R15_FALSE:
	popq	%rdi # restore rdi
	

	.size	find_register_roots, .-find_register_roots
	.ident	"evan oh yeah"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
