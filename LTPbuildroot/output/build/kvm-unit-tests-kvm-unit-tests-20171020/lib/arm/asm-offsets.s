	.cpu cortex-a7
	.eabi_attribute 28, 1	@ Tag_ABI_VFP_args
	.eabi_attribute 20, 1	@ Tag_ABI_FP_denormal
	.eabi_attribute 21, 1	@ Tag_ABI_FP_exceptions
	.eabi_attribute 23, 3	@ Tag_ABI_FP_number_model
	.eabi_attribute 24, 1	@ Tag_ABI_align8_needed
	.eabi_attribute 25, 1	@ Tag_ABI_align8_preserved
	.eabi_attribute 26, 2	@ Tag_ABI_enum_size
	.eabi_attribute 30, 2	@ Tag_ABI_optimization_goals
	.eabi_attribute 34, 1	@ Tag_CPU_unaligned_access
	.eabi_attribute 18, 4	@ Tag_ABI_PCS_wchar_t
	.file	"asm-offsets.c"
@ GNU C99 (Buildroot 2018.02.1-gba7f6ed-dirty) version 6.4.0 (arm-buildroot-linux-uclibcgnueabihf)
@	compiled by GNU C version 6.3.0 20170516, GMP version 6.1.2, MPFR version 3.1.6, MPC version 1.0.3, isl version none
@ GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
@ options passed: 
@ -I /usr/src/output/build/kvm-unit-tests-kvm-unit-tests-20171020/lib
@ -I /usr/src/output/build/kvm-unit-tests-kvm-unit-tests-20171020/lib/libfdt
@ -I lib
@ -isysroot /usr/src/output/host/arm-buildroot-linux-uclibcgnueabihf/sysroot
@ -MMD lib/arm/asm-offsets.d -MF lib/arm/.asm-offsets.d
@ -MQ lib/arm/asm-offsets.s -D NO_RDSEEDRAND lib/arm/asm-offsets.c -marm
@ -mcpu=cortex-a7 -mfloat-abi=hard -mfpu=neon-vfpv4 -mabi=aapcs-linux
@ -mtls-dialect=gnu -auxbase-strip lib/arm/asm-offsets.s -g -O2 -Wall
@ -Wwrite-strings -Wclobbered -Wempty-body -Wuninitialized
@ -Wignored-qualifiers -Wunused-but-set-parameter -Wno-frame-address
@ -Wmissing-parameter-type -Wold-style-declaration -Woverride-init
@ -std=gnu99 -ffreestanding -fno-omit-frame-pointer -fno-pic -fverbose-asm
@ options enabled:  -faggressive-loop-optimizations -falign-jumps
@ -falign-labels -falign-loops -fauto-inc-dec -fbranch-count-reg
@ -fcaller-saves -fchkp-check-incomplete-type -fchkp-check-read
@ -fchkp-check-write -fchkp-instrument-calls -fchkp-narrow-bounds
@ -fchkp-optimize -fchkp-store-bounds -fchkp-use-static-bounds
@ -fchkp-use-static-const-bounds -fchkp-use-wrappers
@ -fcombine-stack-adjustments -fcommon -fcompare-elim -fcprop-registers
@ -fcrossjumping -fcse-follow-jumps -fdefer-pop
@ -fdelete-null-pointer-checks -fdevirtualize -fdevirtualize-speculatively
@ -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-types
@ -fexpensive-optimizations -fforward-propagate -ffunction-cse -fgcse
@ -fgcse-lm -fgnu-runtime -fgnu-unique -fguess-branch-probability
@ -fhoist-adjacent-loads -fident -fif-conversion -fif-conversion2
@ -findirect-inlining -finline -finline-atomics
@ -finline-functions-called-once -finline-small-functions -fipa-cp
@ -fipa-cp-alignment -fipa-icf -fipa-icf-functions -fipa-icf-variables
@ -fipa-profile -fipa-pure-const -fipa-ra -fipa-reference -fipa-sra
@ -fira-hoist-pressure -fira-share-save-slots -fira-share-spill-slots
@ -fisolate-erroneous-paths-dereference -fivopts -fkeep-static-consts
@ -fleading-underscore -flifetime-dse -flra-remat -flto-odr-type-merging
@ -fmath-errno -fmerge-constants -fmerge-debug-strings
@ -fmove-loop-invariants -foptimize-sibling-calls -foptimize-strlen
@ -fpartial-inlining -fpeephole -fpeephole2 -fplt -fprefetch-loop-arrays
@ -freg-struct-return -freorder-blocks -freorder-functions
@ -frerun-cse-after-loop -fsched-critical-path-heuristic
@ -fsched-dep-count-heuristic -fsched-group-heuristic -fsched-interblock
@ -fsched-last-insn-heuristic -fsched-pressure -fsched-rank-heuristic
@ -fsched-spec -fsched-spec-insn-heuristic -fsched-stalled-insns-dep
@ -fschedule-insns -fschedule-insns2 -fsection-anchors
@ -fsemantic-interposition -fshow-column -fshrink-wrap -fsigned-zeros
@ -fsplit-ivs-in-unroller -fsplit-wide-types -fssa-backprop -fssa-phiopt
@ -fstdarg-opt -fstrict-aliasing -fstrict-overflow
@ -fstrict-volatile-bitfields -fsync-libcalls -fthread-jumps
@ -ftoplevel-reorder -ftrapping-math -ftree-bit-ccp -ftree-builtin-call-dce
@ -ftree-ccp -ftree-ch -ftree-coalesce-vars -ftree-copy-prop -ftree-cselim
@ -ftree-dce -ftree-dominator-opts -ftree-dse -ftree-forwprop -ftree-fre
@ -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
@ -ftree-loop-optimize -ftree-parallelize-loops= -ftree-phiprop -ftree-pre
@ -ftree-pta -ftree-reassoc -ftree-scev-cprop -ftree-sink -ftree-slsr
@ -ftree-sra -ftree-switch-conversion -ftree-tail-merge -ftree-ter
@ -ftree-vrp -funit-at-a-time -fvar-tracking -fvar-tracking-assignments
@ -fverbose-asm -fzero-initialized-in-bss -marm -mlittle-endian
@ -mpic-data-is-text-relative -msched-prolog -muclibc -munaligned-access
@ -mvectorize-with-neon-quad

	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu neon-vfpv4
	.type	main, %function
main:
.LFB2:
	.file 1 "lib/arm/asm-offsets.c"
	.loc 1 13 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!	@,
	.cfi_def_cfa_offset 4
	.cfi_offset 11, -4
	add	fp, sp, #0	@,,
	.cfi_def_cfa_register 11
	.loc 1 14 0
	.syntax divided
@ 14 "lib/arm/asm-offsets.c" 1
	
->S_R0 #0 offsetof(struct pt_regs, uregs[0])	@
@ 0 "" 2
	.loc 1 15 0
@ 15 "lib/arm/asm-offsets.c" 1
	
->S_R1 #4 offsetof(struct pt_regs, uregs[1])	@
@ 0 "" 2
	.loc 1 16 0
@ 16 "lib/arm/asm-offsets.c" 1
	
->S_R2 #8 offsetof(struct pt_regs, uregs[2])	@
@ 0 "" 2
	.loc 1 17 0
@ 17 "lib/arm/asm-offsets.c" 1
	
->S_R3 #12 offsetof(struct pt_regs, uregs[3])	@
@ 0 "" 2
	.loc 1 18 0
@ 18 "lib/arm/asm-offsets.c" 1
	
->S_R4 #16 offsetof(struct pt_regs, uregs[4])	@
@ 0 "" 2
	.loc 1 19 0
@ 19 "lib/arm/asm-offsets.c" 1
	
->S_R5 #20 offsetof(struct pt_regs, uregs[5])	@
@ 0 "" 2
	.loc 1 20 0
@ 20 "lib/arm/asm-offsets.c" 1
	
->S_R6 #24 offsetof(struct pt_regs, uregs[6])	@
@ 0 "" 2
	.loc 1 21 0
@ 21 "lib/arm/asm-offsets.c" 1
	
->S_R7 #28 offsetof(struct pt_regs, uregs[7])	@
@ 0 "" 2
	.loc 1 22 0
@ 22 "lib/arm/asm-offsets.c" 1
	
->S_R8 #32 offsetof(struct pt_regs, uregs[8])	@
@ 0 "" 2
	.loc 1 23 0
@ 23 "lib/arm/asm-offsets.c" 1
	
->S_R9 #36 offsetof(struct pt_regs, uregs[9])	@
@ 0 "" 2
	.loc 1 24 0
@ 24 "lib/arm/asm-offsets.c" 1
	
->S_R10 #40 offsetof(struct pt_regs, uregs[10])	@
@ 0 "" 2
	.loc 1 25 0
@ 25 "lib/arm/asm-offsets.c" 1
	
->S_FP #44 offsetof(struct pt_regs, uregs[11])	@
@ 0 "" 2
	.loc 1 26 0
@ 26 "lib/arm/asm-offsets.c" 1
	
->S_IP #48 offsetof(struct pt_regs, uregs[12])	@
@ 0 "" 2
	.loc 1 27 0
@ 27 "lib/arm/asm-offsets.c" 1
	
->S_SP #52 offsetof(struct pt_regs, uregs[13])	@
@ 0 "" 2
	.loc 1 28 0
@ 28 "lib/arm/asm-offsets.c" 1
	
->S_LR #56 offsetof(struct pt_regs, uregs[14])	@
@ 0 "" 2
	.loc 1 29 0
@ 29 "lib/arm/asm-offsets.c" 1
	
->S_PC #60 offsetof(struct pt_regs, uregs[15])	@
@ 0 "" 2
	.loc 1 30 0
@ 30 "lib/arm/asm-offsets.c" 1
	
->S_PSR #64 offsetof(struct pt_regs, uregs[16])	@
@ 0 "" 2
	.loc 1 31 0
@ 31 "lib/arm/asm-offsets.c" 1
	
->S_OLD_R0 #68 offsetof(struct pt_regs, uregs[17])	@
@ 0 "" 2
	.loc 1 32 0
@ 32 "lib/arm/asm-offsets.c" 1
	
->S_FRAME_SIZE #72 sizeof(struct pt_regs)	@
@ 0 "" 2
	.loc 1 34 0
	.arm
	.syntax unified
	mov	r0, #0	@,
	add	sp, fp, #0	@,,
	.cfi_def_cfa_register 13
	@ sp needed	@
	ldr	fp, [sp], #4	@,
	.cfi_restore 11
	.cfi_def_cfa_offset 0
	bx	lr	@
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.text
.Letext0:
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x84
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF10
	.byte	0xc
	.4byte	.LASF11
	.4byte	.LASF12
	.4byte	.Ldebug_ranges0+0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF0
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.4byte	.LASF1
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.4byte	.LASF2
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.4byte	.LASF3
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF4
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.4byte	.LASF5
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.4byte	.LASF6
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x3
	.byte	0x1
	.byte	0x2
	.4byte	.LASF8
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x4
	.4byte	.LASF13
	.byte	0x1
	.byte	0xc
	.4byte	0x25
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.byte	0
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LFB2
	.4byte	.LFE2
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF0:
	.ascii	"unsigned int\000"
.LASF7:
	.ascii	"long unsigned int\000"
.LASF1:
	.ascii	"signed char\000"
.LASF5:
	.ascii	"short unsigned int\000"
.LASF8:
	.ascii	"_Bool\000"
.LASF2:
	.ascii	"short int\000"
.LASF6:
	.ascii	"long long unsigned int\000"
.LASF12:
	.ascii	"/usr/src/output/build/kvm-unit-tests-kvm-unit-tests"
	.ascii	"-20171020\000"
.LASF4:
	.ascii	"unsigned char\000"
.LASF10:
	.ascii	"GNU C99 6.4.0 -marm -mcpu=cortex-a7 -mfloat-abi=har"
	.ascii	"d -mfpu=neon-vfpv4 -mabi=aapcs-linux -mtls-dialect="
	.ascii	"gnu -g -O2 -std=gnu99 -ffreestanding -fno-omit-fram"
	.ascii	"e-pointer -fno-pic\000"
.LASF9:
	.ascii	"sizetype\000"
.LASF13:
	.ascii	"main\000"
.LASF11:
	.ascii	"lib/arm/asm-offsets.c\000"
.LASF3:
	.ascii	"long long int\000"
	.ident	"GCC: (Buildroot 2018.02.1-gba7f6ed-dirty) 6.4.0"
	.section	.note.GNU-stack,"",%progbits
