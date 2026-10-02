/*
 * libgte RMAT_00: RotMatrixZYX_gte, a rotation matrix from three angles,
 * with the sines and cosines of rcossin_tbl.
 *
 * Hand-written assembly, not compiler output: it moves values in and out of
 * the GTE (ctc2, mtc2, mfc2 and its commands), which C can't express, keeps
 * to the $t registers and leaves delay slots that the PsyQ build (GCC 2.7.2
 * and ASPSX in reorder mode) would have filled. It also uses `add`, which
 * GCC never emits, and $at.
 */

.include "macro.inc"

.set noat
.set noreorder

.section .text

glabel RotMatrixZYX_gte
    lh         $t0, 0x4($a0)
    or         $v0, $zero, $a1
    lui        $v1, %hi(rcossin_tbl)
    addiu      $v1, $v1, %lo(rcossin_tbl)
    lw         $t4, 0x0($a0)
    sra        $t3, $t0, 31
    add        $t0, $t0, $t3
    xor        $t0, $t0, $t3
    sll        $t0, $t0, 2
    andi       $t0, $t0, 0x3FFC
    add        $t0, $t0, $v1
    lw         $a2, 0x0($t0)
    sra        $t0, $t4, 16
    sra        $t2, $t0, 31
    add        $t0, $t0, $t2
    xor        $t0, $t0, $t2
    sll        $t0, $t0, 2
    andi       $t0, $t0, 0x3FFC
    add        $t0, $t0, $v1
    lw         $a1, 0x0($t0)
    sll        $t0, $t4, 16
    sra        $t0, $t0, 16
    sra        $t1, $t0, 31
    add        $t0, $t0, $t1
    xor        $t0, $t0, $t1
    sll        $t0, $t0, 2
    andi       $t0, $t0, 0x3FFC
    add        $t0, $t0, $v1
    lw         $a0, 0x0($t0)
    sll        $at, $a2, 16
    sra        $a2, $a2, 16
    sll        $a2, $a2, 16
    add        $at, $at, $t3
    xor        $at, $at, $t3
    srl        $at, $at, 16
    or         $a2, $a2, $at
    sll        $at, $a1, 16
    sra        $a1, $a1, 16
    sll        $a1, $a1, 16
    add        $at, $at, $t2
    xor        $at, $at, $t2
    srl        $at, $at, 16
    or         $a1, $a1, $at
    sll        $at, $a0, 16
    sra        $a0, $a0, 16
    sll        $a0, $a0, 16
    add        $at, $at, $t1
    xor        $at, $at, $t1
    srl        $at, $at, 16
    or         $a0, $a0, $at
    sra        $t0, $a0, 16
    mtc2       $t0, $8
    sll        $a3, $a1, 16
    sra        $a3, $a3, 16
    mtc2       $a3, $9
    sll        $v1, $a2, 16
    sra        $v1, $v1, 16
    mtc2       $v1, $10
    sra        $at, $a2, 16
    mtc2       $at, $11
    nop
    nop
    gpf        1
    sra        $at, $a1, 16
    mult       $at, $t0
    mfc2       $t0, $9
    mfc2       $t1, $10
    sll        $t6, $a0, 16
    mfc2       $t2, $11
    sra        $t6, $t6, 16
    mtc2       $t6, $8
    mtc2       $a3, $9
    mtc2       $v1, $10
    sra        $at, $a2, 16
    mtc2       $at, $11
    nop
    nop
    gpf        1
    mflo       $at
    sra        $at, $at, 12
    sh         $at, 0x10($v0)
    mfc2       $t3, $9
    mfc2       $t4, $10
    mfc2       $t5, $11
    sra        $at, $a2, 16
    mtc2       $at, $8
    sra        $at, $a1, 16
    mtc2       $at, $9
    mult       $at, $t6
    mtc2       $t3, $10
    mtc2       $t0, $11
    neg        $a3, $a3
    andi       $a3, $a3, 0xFFFF
    gpf        1
    mfc2       $a0, $9
    mfc2       $a1, $10
    mfc2       $a2, $11
    mtc2       $at, $9
    mflo       $at
    mtc2       $v1, $8
    sra        $at, $at, 12
    mtc2       $t3, $10
    sll        $at, $at, 16
    mtc2       $t0, $11
    or         $a3, $a3, $at
    sw         $a3, 0xC($v0)
    gpf        1
    andi       $a0, $a0, 0xFFFF
    sub        $a1, $a1, $t1
    sll        $a1, $a1, 16
    or         $a1, $a1, $a0
    sw         $a1, 0x0($v0)
    mfc2       $at, $9
    add        $a2, $a2, $t4
    mfc2       $t6, $10
    andi       $a2, $a2, 0xFFFF
    mfc2       $t7, $11
    sll        $at, $at, 16
    or         $at, $at, $a2
    sw         $at, 0x4($v0)
    add        $t6, $t6, $t2
    andi       $t6, $t6, 0xFFFF
    sub        $t7, $t7, $t5
    sll        $t7, $t7, 16
    or         $t6, $t6, $t7
    jr         $ra
     sw        $t6, 0x8($v0)
endlabel RotMatrixZYX_gte
    nop
