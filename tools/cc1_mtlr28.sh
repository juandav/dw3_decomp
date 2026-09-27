#!/bin/sh
# Rebuild the mark_target_live_regs replacement that tools/patch_cc1.py
# (patch 14) puts into the 2.7.2 cc1: compile tools/cc1_mtlr28.c for i386 at
# 0x08171590, resolve cc1's symbols by address and print the bytes as hex.
# Needs an i386 C compiler and linker, e.g. `pip install ziglang`:
#   ZIG="python3 -m ziglang" tools/cc1_mtlr28.sh bin/gcc-2.7.2-psx/cc1
set -e
ZIG=${ZIG:-zig}
CC1=${1:-bin/gcc-2.7.2-psx/cc1}
T=$(mktemp -d)
$ZIG cc -target x86-freestanding-none -O2 -fno-pic -mcpu=i686 -mno-sse -mno-mmx \
    -fno-stack-protector -ffreestanding -fno-builtin -fno-unwind-tables \
    -fno-asynchronous-unwind-tables -g0 -c tools/cc1_mtlr28.c -o $T/m.o
defs=$(mipsel-linux-gnu-nm $T/m.o | awk '$1 == "U" {print $2}' | while read s; do
    a=$(mipsel-linux-gnu-nm $CC1 | awk -v s=$s '$3 == s {print $1}')
    echo "--defsym=$s=0x$a"
done)
echo 'SECTIONS { . = 0x08171590; .text : { *(.text) *(.rodata*) } /DISCARD/ : { *(.comment) *(.llvm_addrsig) *(.note*) } }' > $T/m.ld
$ZIG ld.lld -m elf_i386 -T $T/m.ld $defs -o $T/m.elf $T/m.o 2> /dev/null
$ZIG objcopy -O binary -j .text $T/m.elf $T/m.bin
python3 -c "import sys; print(open(sys.argv[1], 'rb').read().hex())" $T/m.bin
rm -r $T
