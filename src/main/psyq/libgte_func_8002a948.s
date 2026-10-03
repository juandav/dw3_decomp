/*
 * libgte: two words that are not code and that nothing reads
 * (func_8002A948), then InitGeom, which calls _patch_gte, turns the GTE on
 * (bit 30 of the status register) and sets its defaults: ZSF3, ZSF4, the
 * projection distance H, DQA, DQB and the screen offset.
 *
 * Hand-written assembly, not compiler output: it keeps the caller's $ra in a
 * global (INIT_GEOM_RA) instead of a stack frame, reads and writes the
 * status register (mfc0, mtc0) and the GTE's control registers (ctc2), which
 * C can't express, and leaves delay slots that the PsyQ build would have
 * filled.
 */

.include "macro.inc"

.set noat
.set noreorder

.section .text

dlabel func_8002A948
    .word 0x00097350
    .word 0x00470000
enddlabel func_8002A948

glabel InitGeom
    lui        $at, %hi(INIT_GEOM_RA)
    sw         $ra, %lo(INIT_GEOM_RA)($at)
    jal        _patch_gte
     nop
    lui        $ra, %hi(INIT_GEOM_RA)
    lw         $ra, %lo(INIT_GEOM_RA)($ra)
    nop
    mfc0       $v0, $12
    lui        $v1, 0x4000
    or         $v0, $v0, $v1
    mtc0       $v0, $12
    nop
    addiu      $t0, $zero, 0x155
    ctc2       $t0, $29
    nop
    addiu      $t0, $zero, 0x100
    ctc2       $t0, $30
    nop
    addiu      $t0, $zero, 0x3E8
    ctc2       $t0, $26
    nop
    addiu      $t0, $zero, -0x1062
    ctc2       $t0, $27
    nop
    lui        $t0, 0x140
    ctc2       $t0, $28
    nop
    ctc2       $zero, $24
    ctc2       $zero, $25
    nop
    jr         $ra
     nop
endlabel InitGeom
    nop
    nop
