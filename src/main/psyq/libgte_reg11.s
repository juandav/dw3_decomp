/*
 * libgte REG11: SetFarColor, the far color into GTE control registers 21-23.
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

glabel SetFarColor
    sll        $a0, $a0, 4
    sll        $a1, $a1, 4
    sll        $a2, $a2, 4
    ctc2       $a0, $21
    ctc2       $a1, $22
    ctc2       $a2, $23
    jr         $ra
     nop
endlabel SetFarColor
