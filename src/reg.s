	.file	"reg_roots.s"
	.text
	.globl	find_register_roots
	.type	find_register_roots, @function
find_register_roots:
.LFB6:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$32, %rsp	#,
	movq	%rdi, -24(%rbp)	# state, state
# asm_start.c:4:     gc_node_t node = (gc_node_t)long_table_find(state->pointers, (long) 5);
	movq	-24(%rbp), %rax	# state, tmp83
	movq	(%rax), %rax	# state_4(D)->pointers, _1


        movq	%rbx, %rsi
	movq	%rax, %rdi	# _1,
	call	long_table_find@PLT	#
	movq	%rax, -8(%rbp)	# tmp84, node
# asm_start.c:5:     if (node != NULL) {
	cmpq	$0, -8(%rbp)	#, node
	je	.L3	#,
# asm_start.c:6:         add_root(state, node);
	movq	-8(%rbp), %rdx	# node, tmp85
	movq	-24(%rbp), %rax	# state, tmp86
	movq	%rdx, %rsi	# tmp85,
	movq	%rax, %rdi	# tmp86,
	call	add_root@PLT	#
.L3:

        movq	%rbp, %rsi
	movq	%rax, %rdi	# _1,
	call	long_table_find@PLT	#
	movq	%rax, -8(%rbp)	# tmp84, node
# asm_start.c:5:     if (node != NULL) {
	cmpq	$0, -8(%rbp)	#, node
	je	.L4	#,
# asm_start.c:6:         add_root(state, node);
	movq	-8(%rbp), %rdx	# node, tmp85
	movq	-24(%rbp), %rax	# state, tmp86
	movq	%rdx, %rsi	# tmp85,
	movq	%rax, %rdi	# tmp86,
	call	add_root@PLT	#
.L4:


# asm_start.c:8: }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE6:
	.size	find_register_roots, .-find_register_roots
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
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
