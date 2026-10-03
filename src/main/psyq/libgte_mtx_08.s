/*
 * libgte MTX_08: ScaleMatrix.
 *
 * Hand-written assembly, not compiler output: it keeps every value in the $t
 * registers while $v1 and $a2-$a3 are free, which GCC's register allocation
 * never does, and leaves the load delay slots that the PsyQ build (GCC 2.7.2
 * and ASPSX in reorder mode) would have filled.
 */

.include "macro.inc"

.set noat
.set noreorder

.section .text

glabel ScaleMatrix
    lw         $t3, 0x0($a1)
    lw         $t4, 0x4($a1)
    lw         $t5, 0x8($a1)
    lw         $t0, 0x0($a0)
    nop
    andi       $t1, $t0, 0xFFFF
    sll        $t1, $t1, 16
    sra        $t1, $t1, 16
    multu      $t1, $t3
    mflo       $t1
    sra        $t1, $t1, 12
    andi       $t1, $t1, 0xFFFF
    sra        $t2, $t0, 16
    multu      $t2, $t4
    mflo       $t2
    sra        $t2, $t2, 12
    sll        $t2, $t2, 16
    or         $t1, $t1, $t2
    sw         $t1, 0x0($a0)
    lw         $t0, 0x4($a0)
    nop
    andi       $t1, $t0, 0xFFFF
    sll        $t1, $t1, 16
    sra        $t1, $t1, 16
    multu      $t1, $t5
    mflo       $t1
    sra        $t1, $t1, 12
    andi       $t1, $t1, 0xFFFF
    sra        $t2, $t0, 16
    multu      $t2, $t3
    mflo       $t2
    sra        $t2, $t2, 12
    sll        $t2, $t2, 16
    or         $t1, $t1, $t2
    sw         $t1, 0x4($a0)
    lw         $t0, 0x8($a0)
    nop
    andi       $t1, $t0, 0xFFFF
    sll        $t1, $t1, 16
    sra        $t1, $t1, 16
    multu      $t1, $t4
    mflo       $t1
    sra        $t1, $t1, 12
    andi       $t1, $t1, 0xFFFF
    sra        $t2, $t0, 16
    multu      $t2, $t5
    mflo       $t2
    sra        $t2, $t2, 12
    sll        $t2, $t2, 16
    or         $t1, $t1, $t2
    sw         $t1, 0x8($a0)
    lw         $t0, 0xC($a0)
    nop
    andi       $t1, $t0, 0xFFFF
    sll        $t1, $t1, 16
    sra        $t1, $t1, 16
    multu      $t1, $t3
    mflo       $t1
    sra        $t1, $t1, 12
    andi       $t1, $t1, 0xFFFF
    sra        $t2, $t0, 16
    multu      $t2, $t4
    mflo       $t2
    sra        $t2, $t2, 12
    sll        $t2, $t2, 16
    or         $t1, $t1, $t2
    sw         $t1, 0xC($a0)
    lw         $t0, 0x10($a0)
    nop
    andi       $t1, $t0, 0xFFFF
    sll        $t1, $t1, 16
    sra        $t1, $t1, 16
    multu      $t1, $t5
    mflo       $t1
    sra        $t1, $t1, 12
    sw         $t1, 0x10($a0)
    jr         $ra
     addu      $v0, $a0, $zero
endlabel ScaleMatrix
    nop
    nop
