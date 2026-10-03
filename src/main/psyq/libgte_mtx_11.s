/*
 * libgte MTX_11: SetColorMatrix, the five words of a MATRIX into GTE control
 * registers 16-20.
 *
 * Hand-written assembly, not compiler output: it moves values in and out of
 * the GTE (ctc2, mtc2, mfc2 and its commands), which C can't express, keeps
 * to the $t registers and leaves delay slots that the PsyQ build (GCC 2.7.2
 * and ASPSX in reorder mode) would have filled.
 */

.include "macro.inc"

.set noat
.set noreorder

.section .text

glabel SetColorMatrix
    lw         $t0, 0x0($a0)
    lw         $t1, 0x4($a0)
    lw         $t2, 0x8($a0)
    lw         $t3, 0xC($a0)
    lw         $t4, 0x10($a0)
    ctc2       $t0, $16
    ctc2       $t1, $17
    ctc2       $t2, $18
    ctc2       $t3, $19
    ctc2       $t4, $20
    jr         $ra
     nop
endlabel SetColorMatrix
