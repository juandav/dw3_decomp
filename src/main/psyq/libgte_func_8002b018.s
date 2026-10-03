/*
 * libgte: func_8002B018 (SetGeomScreen), the projection distance into the
 * GTE's H register.
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

glabel func_8002B018
    ctc2       $a0, $26
    jr         $ra
     nop
endlabel func_8002B018
    nop
