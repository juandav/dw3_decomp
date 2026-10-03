/*
 * libetc: two words that are not code and that nothing reads
 * (func_8002ECE8), then _96_remove, the A0 table's call 0x72.
 *
 * Hand-written assembly, not compiler output: a BIOS call is
 * `li $t2,<table>; jr $t2; li $t1,<number>`, a jump to the BIOS's table with
 * the call's number in $t1 and no frame, which no C compiles to.
 */

.include "macro.inc"

.set noat
.set noreorder

.section .text

dlabel func_8002ECE8
    .word 0x00007350
    .word 0x00470000
enddlabel func_8002ECE8

glabel _96_remove
    addiu      $t2, $zero, 0xA0
    jr         $t2
     addiu     $t1, $zero, 0x72
endlabel _96_remove
    nop
    nop
    nop
