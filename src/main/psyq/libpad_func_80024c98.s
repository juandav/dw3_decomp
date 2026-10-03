/*
 * libpad: BIOS calls: EnterCriticalSection (a syscall); ExitCriticalSection
 * (a syscall); func_80024CB8, the B0 table's call 0x32 (open).
 *
 * Hand-written assembly, not compiler output: EnterCriticalSection and
 * ExitCriticalSection are a bare `syscall` with the call's number in $a0,
 * and a BIOS call is `li $t2,<table>; jr $t2; li $t1,<number>`, a jump to
 * the BIOS's table with the call's number in $t1 and no frame, which no C
 * compiles to.
 */

.include "macro.inc"

.set noat
.set noreorder

.section .text

glabel EnterCriticalSection
    addiu      $a0, $zero, 0x1
    syscall    0
    jr         $ra
     nop
endlabel EnterCriticalSection

glabel ExitCriticalSection
    addiu      $a0, $zero, 0x2
    syscall    0
    jr         $ra
     nop
endlabel ExitCriticalSection

glabel func_80024CB8
    addiu      $t2, $zero, 0xB0
    jr         $t2
     addiu     $t1, $zero, 0x32
endlabel func_80024CB8
    nop
