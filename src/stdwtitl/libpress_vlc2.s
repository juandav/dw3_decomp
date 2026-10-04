/*
 * libpress: DecDCTvlcSize2 and DecDCTvlc2. DecDCTvlc2 decodes a frame's VLC
 * bitstream into the MDEC's run-level codes with the table DecDCTvlcBuild
 * unpacks (src/stdwtitl/libpress_build.c), DecDCTvlcSize2 sets how much it
 * decodes per call; their state between calls is libpress's data
 * (D_800878C0, D_800878C4, D_800878E8).
 *
 * Hand-written assembly, not compiler output: it uses `add` and `addi`,
 * which GCC never emits, and keeps the whole decoder in the $t registers
 * with no stack frame.
 */

.include "macro.inc"

.set noat
.set noreorder

.section .text

glabel DecDCTvlcSize2
    lui        $t0, %hi(D_800878C0)
    addiu      $t0, $t0, %lo(D_800878C0)
    addi       $at, $a0, -0x1
    blez       $at, .L1
     lw        $v0, 0x0($t0)
    sll        $at, $a0, 1
    jr         $ra
     sw        $at, 0x0($t0)
  .L1:
    lui        $at, (0xFFFFFF >> 16)
    ori        $at, $at, (0xFFFFFF & 0xFFFF)
    jr         $ra
     sw        $at, 0x0($t0)
endlabel DecDCTvlcSize2

glabel DecDCTvlc2
    lui        $t0, %hi(D_800878C0)
    addiu      $t0, $t0, %lo(D_800878C0)
    addi       $a2, $a2, 0x800
    lui        $at, (0x10000 >> 16)
    add        $a3, $a2, $at
    bnez       $a0, .L2
     lw        $t1, 0x0($t0)
    lui        $t0, %hi(D_800878C4)
    addiu      $t0, $t0, %lo(D_800878C4)
    lw         $a0, 0x0($t0)
    lw         $a1, 0x4($t0)
    lw         $v0, 0x8($t0)
    lw         $v1, 0xC($t0)
    lw         $t4, 0x10($t0)
    lw         $t5, 0x14($t0)
    lw         $t7, 0x18($t0)
    lw         $t8, 0x1C($t0)
    lw         $t9, 0x20($t0)
    add        $t1, $t1, $t1
    b          .L15
     add       $t6, $a1, $t1
  .L2:
    add        $t5, $zero, $zero
    add        $t7, $zero, $zero
    add        $t8, $zero, $zero
    add        $t9, $zero, $zero
    add        $t1, $t1, $t1
    add        $t6, $a1, $t1
    lw         $t1, 0x0($a0)
    lhu        $t4, 0x4($a0)
    lhu        $t2, 0x6($a0)
    lhu        $v0, 0x8($a0)
    lhu        $v1, 0xA($a0)
    addi       $t2, $t2, -0x3
    bltz       $t2, .L3
     sll       $t4, $t4, 10
    addi       $t5, $zero, 0x1
  .L3:
    addi       $a0, $a0, 0xC
    sll        $v0, $v0, 16
    or         $v0, $v0, $v1
    or         $v1, $zero, $zero
    sw         $t1, 0x0($a1)
    andi       $t1, $t1, 0xFFFF
    sll        $t1, $t1, 2
    addiu      $t1, $t1, 0x4
    add        $t1, $t1, $a1
    lui        $t0, %hi(D_800878E8)
    addiu      $t0, $t0, %lo(D_800878E8)
    sw         $t1, 0x0($t0)
    addi       $a1, $a1, 0x2
  .L4:
    beqz       $t5, .L12
     srl       $t0, $v0, 22
    xori       $at, $t0, 0x3FF
    beqz       $at, .L21
     addi      $a1, $a1, 0x2
    addi       $at, $t5, -0x3
    bltz       $at, .L5
     addi      $at, $a2, -0x400
    addi       $at, $at, -0x400
  .L5:
    srl        $t0, $v0, 24
    sll        $t0, $t0, 2
    add        $t0, $t0, $at
    lhu        $t1, 0x0($t0)
    lhu        $t2, 0x2($t0)
    and        $t0, $zero, $zero
    beqz       $t2, .L7
     sllv      $v0, $v0, $t1
    addi       $at, $zero, 0x20
    sub        $at, $at, $t2
    srlv       $t0, $v0, $at
    bltz       $v0, .L6
     sllv      $v0, $v0, $t2
    addi       $t3, $zero, -0x1
    srlv       $t3, $t3, $at
    sub        $t0, $t0, $t3
  .L6:
    add        $v1, $v1, $t2
  .L7:
    add        $v1, $v1, $t1
    andi       $at, $v1, 0x10
    beqz       $at, .L8
     andi      $v1, $v1, 0xF
    lhu        $t1, 0x0($a0)
    addi       $a0, $a0, 0x2
    sllv       $t1, $t1, $v1
    or         $v0, $v0, $t1
  .L8:
    addi       $at, $t5, -0x2
    bgtz       $at, .L10
     add       $t1, $t9, $t0
    beqz       $at, .L9
     add       $t1, $t8, $t0
    add        $t1, $t7, $t0
    b          .L11
     add       $t7, $t7, $t0
  .L9:
    b          .L11
     add       $t8, $t8, $t0
  .L10:
    add        $t9, $t9, $t0
  .L11:
    sll        $t1, $t1, 2
    andi       $t1, $t1, 0x3FF
    or         $t1, $t4, $t1
    addi       $t5, $t5, 0x1
    addi       $at, $t5, -0x7
    bnez       $at, .L14
     sh        $t1, 0x0($a1)
    b          .L14
     addi      $t5, $t5, -0x6
  .L12:
    xori       $at, $t0, 0x1FF
    beqz       $at, .L21
     addi      $a1, $a1, 0x2
    sll        $v0, $v0, 10
    addi       $v1, $v1, 0xA
    andi       $at, $v1, 0x10
    beqz       $at, .L13
     andi      $v1, $v1, 0xF
    lhu        $t1, 0x0($a0)
    addi       $a0, $a0, 0x2
    sllv       $t1, $t1, $v1
    or         $v0, $v0, $t1
  .L13:
    or         $t0, $t4, $t0
    sh         $t0, 0x0($a1)
  .L14:
    subu       $at, $a1, $t6
    bgez       $at, .L24
     addi      $a1, $a1, 0x2
  .L15:
    srl        $t0, $v0, 19
    sll        $t0, $t0, 3
    add        $t0, $t0, $a2
    lw         $t1, 0x0($t0)
    nop
    bnez       $t1, .L17
     andi      $at, $t1, 0xFF
    sll        $v0, $v0, 8
    addi       $v1, $v1, 0x8
    andi       $at, $v1, 0x10
    beqz       $at, .L16
     andi      $v1, $v1, 0xF
    lhu        $t0, 0x0($a0)
    addi       $a0, $a0, 0x2
    sllv       $t0, $t0, $v1
    or         $v0, $v0, $t0
  .L16:
    srl        $t0, $v0, 23
    sll        $t0, $t0, 2
    add        $t0, $t0, $a3
    lw         $t1, 0x0($t0)
    add        $t3, $zero, $zero
    b          .L18
     andi      $at, $t1, 0xFF
  .L17:
    lw         $t3, 0x4($t0)
  .L18:
    sllv       $v0, $v0, $at
    add        $v1, $v1, $at
    andi       $at, $v1, 0x10
    beqz       $at, .L19
     andi      $v1, $v1, 0xF
    lhu        $t0, 0x0($a0)
    addi       $a0, $a0, 0x2
    sllv       $t0, $t0, $v1
    or         $v0, $v0, $t0
  .L19:
    srl        $t1, $t1, 16
    xori       $at, $t1, 0x7C1F
    beqz       $at, .L20
     xori      $at, $t1, 0xFE00
    beqz       $at, .L4
     sh        $t1, 0x0($a1)
    beqz       $t3, .L15
     addi      $a1, $a1, 0x2
    andi       $t2, $t3, 0xFFFF
    xori       $at, $t2, 0x7C1F
    beqz       $at, .L20
     xori      $at, $t2, 0xFE00
    beqz       $at, .L4
     sh        $t2, 0x0($a1)
    srl        $t2, $t3, 16
    beqz       $t2, .L15
     addi      $a1, $a1, 0x2
    xori       $at, $t2, 0x7C1F
    beqz       $at, .L20
     xori      $at, $t2, 0xFE00
    beqz       $at, .L4
     sh        $t2, 0x0($a1)
    b          .L15
     addi      $a1, $a1, 0x2
  .L20:
    srl        $t0, $v0, 16
    sh         $t0, 0x0($a1)
    addi       $a1, $a1, 0x2
    lhu        $t0, 0x0($a0)
    addi       $a0, $a0, 0x2
    sll        $v0, $v0, 16
    sllv       $t0, $t0, $v1
    b          .L15
     or        $v0, $v0, $t0
  .L21:
    lui        $t0, %hi(D_800878E8)
    addiu      $t0, $t0, %lo(D_800878E8)
    lw         $t1, 0x0($t0)
    ori        $t0, $zero, 0xFE00
  .L22:
    subu       $at, $a1, $t1
    bgez       $at, .L23
     nop
    sh         $t0, 0x0($a1)
    b          .L22
     addi      $a1, $a1, 0x2
  .L23:
    jr         $ra
     add       $v0, $zero, $zero
  .L24:
    lui        $t0, %hi(D_800878C4)
    addiu      $t0, $t0, %lo(D_800878C4)
    sw         $a0, 0x0($t0)
    sw         $a1, 0x4($t0)
    sw         $v0, 0x8($t0)
    sw         $v1, 0xC($t0)
    sw         $t4, 0x10($t0)
    sw         $t5, 0x14($t0)
    sw         $t7, 0x18($t0)
    sw         $t8, 0x1C($t0)
    sw         $t9, 0x20($t0)
    jr         $ra
     addi      $v0, $zero, 0x1
endlabel DecDCTvlc2
    nop
