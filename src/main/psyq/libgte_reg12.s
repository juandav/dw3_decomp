/*
 * libgte REG12: SetGeomOffset, the screen offset into GTE control registers
 * 24 and 25.
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

glabel SetGeomOffset
    sll        $a0, $a0, 16
    sll        $a1, $a1, 16
    ctc2       $a0, $24
    ctc2       $a1, $25
    jr         $ra
     nop
endlabel SetGeomOffset
    nop
    nop
