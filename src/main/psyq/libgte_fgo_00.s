/*
 * libgte FGO_00: TransposeMatrix.
 *
 * Hand-written assembly, not compiler output: it copies the matrix a word at
 * a time and then fixes the halves that a word copy put in the wrong place
 * with overlapping `sh`, which no compiler does.
 */

.include "macro.inc"

.set noat
.set noreorder

.section .text

glabel TransposeMatrix
    addu       $v0, $a1, $zero
    lw         $t1, 0x0($a0)
    lw         $t2, 0x4($a0)
    sw         $t1, 0x4($a1)
    sw         $t2, 0x0($a1)
    sh         $t1, 0x0($a1)
    lw         $t3, 0x8($a0)
    lw         $t1, 0xC($a0)
    sw         $t3, 0xC($a1)
    sw         $t1, 0x8($a1)
    sh         $t2, 0xC($a1)
    sh         $t3, 0x8($a1)
    lh         $t2, 0x10($a0)
    sh         $t1, 0x4($a1)
    jr         $ra
     sh        $t2, 0x10($a1)
endlabel TransposeMatrix
