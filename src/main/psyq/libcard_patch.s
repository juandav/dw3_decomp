/*
 * libcard's BIOS patches, all from the B0 table's entry 0x5B
 * (ChangeClearPad) or the C0 table's entry 6 (the exception handler):
 * _patch_card_info clears a word of the BIOS's memory card driver;
 * _patch_card copies the first half of func_8003B78C (a jump to 0xA000DFAC)
 * into the BIOS routine the exception handler loads at offset 0x70, and
 * keeps the address after it at 0xDFFC; _patch_card2 copies the second half
 * (a call to 0xA000DF80) into the driver; _copy_memcard_patch copies
 * func_8003B71C and func_8003B748 to 0xDF80, where those jumps land.
 *
 * Hand-written assembly, not compiler output: it keeps the caller's $ra in a
 * global instead of a stack frame and calls the BIOS through its table at
 * 0xB0 with the function number in $t1 (`li $t2,0xB0; jalr $t2`), which no C
 * compiles to. It also uses `addi`, which GCC never emits. The copied
 * fragments are not functions: they read the BIOS's $v1 without setting it,
 * jump through absolute addresses (0xA000DF80, 0xA000DFAC and the word at
 * 0xDFFC) and wait in a loop on $t0.
 */

.include "macro.inc"

.set noat
.set noreorder

.section .text

glabel _patch_card_info
    lui        $at, %hi(PATCH_CARD_RA)
    sw         $ra, %lo(PATCH_CARD_RA)($at)
    addiu      $t1, $zero, 0x57
    addiu      $t2, $zero, 0xB0
    jalr       $t2
     nop
    addiu      $t2, $zero, 0x9
    lw         $v0, 0x16C($v0)
    nop
    addi       $v1, $v0, 0x1988
    jal        func_8002B548
     sw        $zero, 0x0($v1)
    lui        $ra, %hi(PATCH_CARD_RA)
    lw         $ra, %lo(PATCH_CARD_RA)($ra)
    nop
    jr         $ra
     nop
endlabel _patch_card_info

glabel func_8003B71C
    lhu        $t7, 0xA($v1)
    lui        $t0, 0x0
    or         $t8, $t7, $v0
    ori        $t9, $t8, 0x12
    sh         $t9, 0xA($v1)
    addiu      $t0, $zero, 0x28
  .L1:
    addiu      $t0, $t0, -0x1
    bnez       $t0, .L1
     nop
    jr         $ra
     nop
endlabel func_8003B71C

glabel func_8003B748
    lw         $v0, 0x1074($v1)
    nop
    andi       $v0, $v0, 0x80
    beqz       $v0, .L3
     nop
  .L2:
    lw         $v0, 0x1044($v1)
    nop
    andi       $v0, $v0, 0x80
    bnez       $v0, .L2
     nop
    lui        $v0, 0x1
    lw         $v0, -0x2004($v0)
    nop
    jr         $v0
     nop
  .L3:
    jr         $ra
     nop
endlabel func_8003B748

glabel func_8003B78C
    lui        $v0, %hi(0xA000DFAC)
    addiu      $v0, $v0, %lo(0xA000DFAC)
    jr         $v0
     nop
    nop
    lui        $t0, %hi(0xA000DF80)
    addiu      $t0, $t0, %lo(0xA000DF80)
    jalr       $t0
     nop
endlabel func_8003B78C
    nop

glabel _patch_card
    lui        $at, %hi(PATCH_CARD_RA)
    sw         $ra, %lo(PATCH_CARD_RA)($at)
    jal        EnterCriticalSection
     nop
    addiu      $t1, $zero, 0x56
    addiu      $t2, $zero, 0xB0
    jalr       $t2
     nop
    lw         $v0, 0x18($v0)
    nop
    lw         $v1, 0x70($v0)
    nop
    andi       $t1, $v1, 0xFFFF
    sll        $t1, $t1, 16
    lw         $v1, 0x74($v0)
    nop
    andi       $t2, $v1, 0xFFFF
    addu       $v1, $t1, $t2
    addiu      $v0, $v1, 0x28
    lui        $t2, %hi(func_8003B78C)
    addiu      $t2, $t2, %lo(func_8003B78C)
    lui        $t1, %hi(func_8003B78C + 0x14)
    addiu      $t1, $t1, %lo(func_8003B78C + 0x14)
  .L4:
    lw         $v1, 0x0($t2)
    nop
    sw         $v1, 0x0($v0)
    addiu      $t2, $t2, 0x4
    bne        $t2, $t1, .L4
     addiu     $v0, $v0, 0x4
    lui        $at, 0x1
    jal        func_8002B548
     sw        $v0, -0x2004($at)
    lui        $ra, %hi(PATCH_CARD_RA)
    lw         $ra, %lo(PATCH_CARD_RA)($ra)
    nop
    jr         $ra
     nop
endlabel _patch_card

glabel _patch_card2
    lui        $at, %hi(PATCH_CARD_RA)
    sw         $ra, %lo(PATCH_CARD_RA)($at)
    jal        EnterCriticalSection
     nop
    addiu      $t1, $zero, 0x57
    addiu      $t2, $zero, 0xB0
    jalr       $t2
     nop
    lw         $v0, 0x16C($v0)
    nop
    lw         $v1, 0x9C8($v0)
    lui        $t2, %hi(func_8003B78C + 0x14)
    addiu      $t2, $t2, %lo(func_8003B78C + 0x14)
    lui        $t1, %hi(_patch_card)
    addiu      $t1, $t1, %lo(_patch_card)
  .L5:
    lw         $t0, 0x0($t2)
    nop
    sw         $t0, 0x9C8($v0)
    addiu      $t2, $t2, 0x4
    bne        $t2, $t1, .L5
     addiu     $v0, $v0, 0x4
    jal        func_8002B548
     nop
    lui        $ra, %hi(PATCH_CARD_RA)
    lw         $ra, %lo(PATCH_CARD_RA)($ra)
    nop
    jr         $ra
     nop
endlabel _patch_card2

glabel _copy_memcard_patch
    ori        $v0, $zero, 0xDF80
    lui        $t2, %hi(func_8003B71C)
    addiu      $t2, $t2, %lo(func_8003B71C)
    lui        $t1, %hi(func_8003B78C)
    addiu      $t1, $t1, %lo(func_8003B78C)
  .L6:
    lw         $v1, 0x0($t2)
    nop
    sw         $v1, 0x0($v0)
    addiu      $t2, $t2, 0x4
    bne        $t2, $t1, .L6
     addiu     $v0, $v0, 0x4
    jr         $ra
     nop
endlabel _copy_memcard_patch
    nop
    nop
    nop
