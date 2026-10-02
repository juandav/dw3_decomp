/*
 * libgte REG10: SetBackColor, the back color into GTE control registers
 * 13-15.
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

glabel SetBackColor
    sll        $a0, $a0, 4
    sll        $a1, $a1, 4
    sll        $a2, $a2, 4
    ctc2       $a0, $13
    ctc2       $a1, $14
    ctc2       $a2, $15
    jr         $ra
     nop
endlabel SetBackColor
