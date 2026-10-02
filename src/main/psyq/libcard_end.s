/*
 * libcard: _ExitCard writes three nops over the BIOS's exception handler
 * (the C0 table's entry 6), at offset 0x70.
 *
 * Hand-written assembly, not compiler output: it keeps the caller's $ra in a
 * global instead of a stack frame and calls the BIOS through its table at
 * 0xB0 with the function number in $t1 (`li $t2,0xB0; jalr $t2`), which no C
 * compiles to. The three nops it copies are the `.Lexit_card_code` data
 * after it.
 */

.include "macro.inc"

.set noat
.set noreorder

.section .text

glabel _ExitCard
    lui        $at, %hi(EXIT_CARD_RA)
    sw         $ra, %lo(EXIT_CARD_RA)($at)
    jal        EnterCriticalSection
     nop
    addiu      $t1, $zero, 0x56
    addiu      $t2, $zero, 0xB0
    jalr       $t2
     nop
    lw         $v0, 0x18($v0)
    lui        $t2, %hi(.Lexit_card_code)
    addiu      $t2, $t2, %lo(.Lexit_card_code)
    lui        $t1, %hi(.Lexit_card_code_end)
    addiu      $t1, $t1, %lo(.Lexit_card_code_end)
  .L1:
    lw         $v1, 0x0($t2)
    nop
    sw         $v1, 0x70($v0)
    addiu      $t2, $t2, 0x4
    bne        $t2, $t1, .L1
     addiu     $v0, $v0, 0x4
    jal        func_8002B548
     nop
    jal        ExitCriticalSection
     nop
    lui        $ra, %hi(EXIT_CARD_RA)
    lw         $ra, %lo(EXIT_CARD_RA)($ra)
    nop
    jr         $ra
     nop
endlabel _ExitCard
  .Lexit_card_code:
    nop
    nop
    nop
  .Lexit_card_code_end:
    nop
