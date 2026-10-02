/*
 * libapi's pad patch: _patch_pad gets the BIOS's B0 table (B0 call 0x57,
 * GetB0Table), finds from its entry 0x5B (ChangeClearPad) the BIOS's
 * routines that turn the controller interrupt on and off, keeps them in
 * PAD_ENABLE_FUNC and PAD_DISABLE_FUNC, and clears 11 words of the BIOS's
 * pad work area. EnablePAD and DisablePAD jump to them.
 *
 * Hand-written assembly, not compiler output: it keeps the caller's $ra in a
 * global instead of a stack frame and calls the BIOS through its table at
 * 0xB0 with the function number in $t1 (`li $t2,0xB0; jalr $t2`), which no C
 * compiles to. It also uses `addi`, which GCC never emits.
 */

.include "macro.inc"

.set noat
.set noreorder

.section .text

glabel EnablePAD
    lui        $t1, %hi(PAD_ENABLE_FUNC)
    lw         $t1, %lo(PAD_ENABLE_FUNC)($t1)
    nop
    jr         $t1
     nop
endlabel EnablePAD

glabel DisablePAD
    lui        $t1, %hi(PAD_DISABLE_FUNC)
    lw         $t1, %lo(PAD_DISABLE_FUNC)($t1)
    nop
    jr         $t1
     nop
endlabel DisablePAD

glabel _patch_pad
    lui        $at, %hi(PATCH_PAD_RA)
    sw         $ra, %lo(PATCH_PAD_RA)($at)
    jal        EnterCriticalSection
     nop
    addiu      $t1, $zero, 0x57
    addiu      $t2, $zero, 0xB0
    jalr       $t2
     nop
    lw         $v0, 0x16C($v0)
    addiu      $t1, $zero, 0xB
    addi       $v1, $v0, 0x884
    lui        $at, %hi(PAD_ENABLE_FUNC)
    sw         $v1, %lo(PAD_ENABLE_FUNC)($at)
    addi       $v1, $v0, 0x894
    lui        $at, %hi(PAD_DISABLE_FUNC)
    sw         $v1, %lo(PAD_DISABLE_FUNC)($at)
  .L1:
    sw         $zero, 0x594($v0)
    addiu      $v0, $v0, 0x4
    addiu      $t1, $t1, -0x1
    bnez       $t1, .L1
     nop
    jal        func_8002B548
     nop
    lui        $ra, %hi(PATCH_PAD_RA)
    lw         $ra, %lo(PATCH_PAD_RA)($ra)
    nop
    jr         $ra
     nop
endlabel _patch_pad
    nop
    nop
