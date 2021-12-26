	.file	"reg_roots.c"
# GNU C17 (Ubuntu 9.3.0-17ubuntu1~20.04) version 9.3.0 (x86_64-linux-gnu)
#	compiled by GNU C version 9.3.0, GMP version 6.2.0, MPFR version 4.0.2, MPC version 1.1.0, isl version isl-0.22.1-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -imultiarch x86_64-linux-gnu asm_start.c -mtune=generic
# -march=x86-64 -O0 -fverbose-asm -fasynchronous-unwind-tables
# -fstack-protector-strong -Wformat -Wformat-security
# -fstack-clash-protection -fcf-protection
# options enabled:  -fPIC -fPIE -faggressive-loop-optimizations
# -fassume-phsa -fasynchronous-unwind-tables -fauto-inc-dec -fcommon
# -fdelete-null-pointer-checks -fdwarf2-cfi-asm -fearly-inlining
# -feliminate-unused-debug-types -ffp-int-builtin-inexact -ffunction-cse
# -fgcse-lm -fgnu-runtime -fgnu-unique -fident -finline-atomics
# -fipa-stack-alignment -fira-hoist-pressure -fira-share-save-slots
# -fira-share-spill-slots -fivopts -fkeep-static-consts
# -fleading-underscore -flifetime-dse -flto-odr-type-merging -fmath-errno
# -fmerge-debug-strings -fpeephole -fplt -fprefetch-loop-arrays
# -freg-struct-return -fsched-critical-path-heuristic
# -fsched-dep-count-heuristic -fsched-group-heuristic -fsched-interblock
# -fsched-last-insn-heuristic -fsched-rank-heuristic -fsched-spec
# -fsched-spec-insn-heuristic -fsched-stalled-insns-dep -fschedule-fusion
# -fsemantic-interposition -fshow-column -fshrink-wrap-separate
# -fsigned-zeros -fsplit-ivs-in-unroller -fssa-backprop
# -fstack-clash-protection -fstack-protector-strong -fstdarg-opt
# -fstrict-volatile-bitfields -fsync-libcalls -ftrapping-math -ftree-cselim
# -ftree-forwprop -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
# -ftree-loop-optimize -ftree-parallelize-loops= -ftree-phiprop
# -ftree-reassoc -ftree-scev-cprop -funit-at-a-time -funwind-tables
# -fverbose-asm -fzero-initialized-in-bss -m128bit-long-double -m64 -m80387
# -malign-stringops -mavx256-split-unaligned-load
# -mavx256-split-unaligned-store -mfancy-math-387 -mfp-ret-in-387 -mfxsr
# -mglibc -mieee-fp -mlong-double-80 -mmmx -mno-sse4 -mpush-args -mred-zone
# -msse -msse2 -mstv -mtls-direct-seg-refs -mvzeroupper

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

	movq	%rdi, -24(%rbp)	# state, state
# asm_start.c:4:     gc_node_t node = (gc_node_t)long_table_find(state->pointers, (long) 5);
	movq	-24(%rbp), %rax	# state, tmp83
	movq	(%rax), %rax	# state_4(D)->pointers, _1
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

	movq	%rdi, -24(%rbp)	# state, state
# asm_start.c:4:     gc_node_t node = (gc_node_t)long_table_find(state->pointers, (long) 5);
	movq	-24(%rbp), %rax	# state, tmp83
	movq	(%rax), %rax	# state_4(D)->pointers, _1
        movq	%r12, %rsi
	movq	%rax, %rdi	# _1,
	call	long_table_find@PLT	#
	movq	%rax, -8(%rbp)	# tmp84, node
# asm_start.c:5:     if (node != NULL) {
	cmpq	$0, -8(%rbp)	#, node
	je	.L5	#,
# asm_start.c:6:         add_root(state, node);
	movq	-8(%rbp), %rdx	# node, tmp85
	movq	-24(%rbp), %rax	# state, tmp86
	movq	%rdx, %rsi	# tmp85,
	movq	%rax, %rdi	# tmp86,
	call	add_root@PLT	#
.L5:

	movq	%rdi, -24(%rbp)	# state, state
# asm_start.c:4:     gc_node_t node = (gc_node_t)long_table_find(state->pointers, (long) 5);
	movq	-24(%rbp), %rax	# state, tmp83
	movq	(%rax), %rax	# state_4(D)->pointers, _1
        movq	%r13, %rsi
	movq	%rax, %rdi	# _1,
	call	long_table_find@PLT	#
	movq	%rax, -8(%rbp)	# tmp84, node
# asm_start.c:5:     if (node != NULL) {
	cmpq	$0, -8(%rbp)	#, node
	je	.L6	#,
# asm_start.c:6:         add_root(state, node);
	movq	-8(%rbp), %rdx	# node, tmp85
	movq	-24(%rbp), %rax	# state, tmp86
	movq	%rdx, %rsi	# tmp85,
	movq	%rax, %rdi	# tmp86,
	call	add_root@PLT	#
.L6:

	movq	%rdi, -24(%rbp)	# state, state
# asm_start.c:4:     gc_node_t node = (gc_node_t)long_table_find(state->pointers, (long) 5);
	movq	-24(%rbp), %rax	# state, tmp83
	movq	(%rax), %rax	# state_4(D)->pointers, _1
        movq	%r14, %rsi
	movq	%rax, %rdi	# _1,
	call	long_table_find@PLT	#
	movq	%rax, -8(%rbp)	# tmp84, node
# asm_start.c:5:     if (node != NULL) {
	cmpq	$0, -8(%rbp)	#, node
	je	.L7	#,
# asm_start.c:6:         add_root(state, node);
	movq	-8(%rbp), %rdx	# node, tmp85
	movq	-24(%rbp), %rax	# state, tmp86
	movq	%rdx, %rsi	# tmp85,
	movq	%rax, %rdi	# tmp86,
	call	add_root@PLT	#
.L7:

	movq	%rdi, -24(%rbp)	# state, state
# asm_start.c:4:     gc_node_t node = (gc_node_t)long_table_find(state->pointers, (long) 5);
	movq	-24(%rbp), %rax	# state, tmp83
	movq	(%rax), %rax	# state_4(D)->pointers, _1
        movq	%r15, %rsi
	movq	%rax, %rdi	# _1,
	call	long_table_find@PLT	#
	movq	%rax, -8(%rbp)	# tmp84, node
# asm_start.c:5:     if (node != NULL) {
	cmpq	$0, -8(%rbp)	#, node
	je	.L8	#,
# asm_start.c:6:         add_root(state, node);
	movq	-8(%rbp), %rdx	# node, tmp85
	movq	-24(%rbp), %rax	# state, tmp86
	movq	%rdx, %rsi	# tmp85,
	movq	%rax, %rdi	# tmp86,
	call	add_root@PLT	#
.L8:


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
