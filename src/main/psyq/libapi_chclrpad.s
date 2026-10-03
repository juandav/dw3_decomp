/*
 * libapi: _remove_ChgclrPAD clears 9 words of the BIOS's ChangeClearPad work
 * area, which it finds from the B0 table's entry 0x5B.
 *
 * Hand-written assembly, not compiler output: it keeps the caller's $ra in a
 * global instead of a stack frame and calls the BIOS through its table at
 * 0xB0 with the function number in $t1 (`li $t2,0xB0; jalr $t2`), which no C
 * compiles to. It also uses `addi`, which GCC never emits.
 */

.include "macro.inc"

.set noat
.set noreorder

.section .text

glabel _remove_ChgclrPAD
    lui        $at, %hi(REMOVE_CHGCLRPAD_RA)
    sw         $ra, %lo(REMOVE_CHGCLRPAD_RA)($at)
    jal        EnterCriticalSection
     nop
    addiu      $t1, $zero, 0x57
    addiu      $t2, $zero, 0xB0
    jalr       $t2
     nop
    addiu      $t2, $zero, 0x9
    lw         $v0, 0x16C($v0)
    nop
    addi       $v1, $v0, 0x62C
  .L1:
    sw         $zero, 0x0($v1)
    addiu      $v1, $v1, 0x4
    addiu      $t2, $t2, -0x1
    bnez       $t2, .L1
     nop
    jal        func_8002B548
     nop
    jal        ExitCriticalSection
     nop
    lui        $ra, %hi(REMOVE_CHGCLRPAD_RA)
    lw         $ra, %lo(REMOVE_CHGCLRPAD_RA)($ra)
    nop
    jr         $ra
     nop
endlabel _remove_ChgclrPAD
    nop
    nop
