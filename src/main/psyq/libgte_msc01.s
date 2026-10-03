/*
 * libgte MSC01: SquareRoot0, the square root of a 32-bit integer from the
 * GTE's leading-zero count (LZCS/LZCR) and SQRT_TABLE.
 *
 * Hand-written assembly, not compiler output: it moves values in and out of
 * the GTE (ctc2, mtc2, mfc2 and its commands), which C can't express, keeps
 * to the $t registers and leaves delay slots that the PsyQ build (GCC 2.7.2
 * and ASPSX in reorder mode) would have filled. It also uses `sub` and
 * `addi`, which GCC never emits, and $at.
 */

.include "macro.inc"

.set noat
.set noreorder

.section .text

glabel SquareRoot0
    mtc2       $a0, $30
    nop
    nop
    mfc2       $v0, $31
    addiu      $at, $zero, 0x20
    beq        $v0, $at, .L3
     nop
    andi       $t0, $v0, 0x1
    addiu      $at, $zero, -0x2
    and        $t2, $v0, $at
    addiu      $t1, $zero, 0x1F
    sub        $t1, $t1, $t2
    sra        $t1, $t1, 1
    addi       $t3, $t2, -0x18
    bltz       $t3, .L1
     nop
    sllv       $t4, $a0, $t3
    b          .L2
  .L1:
     addiu     $t3, $zero, 0x18
    sub        $t3, $t3, $t2
    srav       $t4, $a0, $t3
  .L2:
    addi       $t4, $t4, -0x40
    sll        $t4, $t4, 1
    lui        $t5, %hi(SQRT_TABLE)
    addu       $t5, $t5, $t4
    lh         $t5, %lo(SQRT_TABLE)($t5)
    nop
    sllv       $t5, $t5, $t1
    srl        $v0, $t5, 12
    jr         $ra
     nop
  .L3:
    jr         $ra
     addiu     $v0, $zero, 0x0
endlabel SquareRoot0
    nop
    nop
    nop
