/*
 * libc2: func_8003D648, the A0 table's call 0xAC (_card_load).
 *
 * Hand-written assembly, not compiler output: a BIOS call is
 * `li $t2,<table>; jr $t2; li $t1,<number>`, a jump to the BIOS's table with
 * the call's number in $t1 and no frame, which no C compiles to.
 */

.include "macro.inc"

.set noat
.set noreorder

.section .text

glabel func_8003D648
    addiu      $t2, $zero, 0xA0
    jr         $t2
     addiu     $t1, $zero, 0xAC
endlabel func_8003D648
    nop
