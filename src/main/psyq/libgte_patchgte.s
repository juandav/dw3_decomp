/*
 * libgte: _patch_gte rewrites the start of the BIOS's exception handler (the
 * C0 table's entry 6) so that it also reads the cause register, if it still
 * holds the code func_8002B514 starts with; func_8002B548 is the A0 table's
 * call 0x44, FlushCache.
 *
 * Hand-written assembly, not compiler output: it keeps the caller's $ra in a
 * global instead of a stack frame and calls the BIOS through its table at
 * 0xB0 with the function number in $t1 (`li $t2,0xB0; jalr $t2`), which no C
 * compiles to. func_8002B514 is not a function but the two versions of the
 * handler's start, and FlushCache is a BIOS call
 * (`li $t2,0xA0; jr $t2; li $t1,0x44`).
 */

.include "macro.inc"

.set noat
.set noreorder

.section .text

glabel _patch_gte
    lui        $at, %hi(PATCH_GTE_RA)
    sw         $ra, %lo(PATCH_GTE_RA)($at)
    jal        EnterCriticalSection
     nop
    addiu      $t1, $zero, 0x56
    addiu      $t2, $zero, 0xB0
    jalr       $t2
     nop
    lw         $v0, 0x18($v0)
    nop
    addiu      $v0, $v0, 0x28
    addu       $t7, $v0, $zero
    lui        $t2, %hi(func_8002B514)
    addiu      $t2, $t2, %lo(func_8002B514)
    lui        $t1, %hi(.Lgte_prologue)
    addiu      $t1, $t1, %lo(.Lgte_prologue)
  .L1:
    lw         $v1, 0x0($t2)
    lw         $t3, 0x0($v0)
    addiu      $t2, $t2, 0x4
    bne        $v1, $t3, .L3
     addiu     $v0, $v0, 0x4
    bne        $t2, $t1, .L1
     nop
    addu       $v0, $t7, $zero
    lui        $t2, %hi(.Lgte_prologue)
    addiu      $t2, $t2, %lo(.Lgte_prologue)
    lui        $t1, %hi(.Lgte_prologue_end)
    addiu      $t1, $t1, %lo(.Lgte_prologue_end)
  .L2:
    lw         $v1, 0x0($t2)
    nop
    sw         $v1, 0x0($v0)
    addiu      $t2, $t2, 0x4
    bne        $t2, $t1, .L2
     addiu     $v0, $v0, 0x4
  .L3:
    jal        func_8002B548
     nop
    jal        ExitCriticalSection
     nop
    lui        $ra, %hi(PATCH_GTE_RA)
    lw         $ra, %lo(PATCH_GTE_RA)($ra)
    nop
    jr         $ra
     nop
endlabel _patch_gte

glabel func_8002B514
    sw         $at, 0x4($k0)
    sw         $v0, 0x8($k0)
    sw         $v1, 0xC($k0)
    sw         $ra, 0x7C($k0)
    mfc0       $v1, $14
    nop
  .Lgte_prologue:
    sw         $at, 0x4($k0)
    sw         $v0, 0x8($k0)
    mfc0       $v0, $13
    sw         $v1, 0xC($k0)
    mfc0       $v1, $14
    sw         $ra, 0x7C($k0)
endlabel func_8002B514
  .Lgte_prologue_end:
    nop

glabel func_8002B548
    addiu      $t2, $zero, 0xA0
    jr         $t2
     addiu     $t1, $zero, 0x44
endlabel func_8002B548
    nop
