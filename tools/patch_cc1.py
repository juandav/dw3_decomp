#!/usr/bin/env python3
"""Binary-patch bin/gcc-2.7.2-psx/cc1 into the cc1 the PsyQ libraries were built with.

usage: tools/patch_cc1.py [in out]   (default: bin/gcc-2.7.2-psx/cc1 ->
                                       build/tools/gcc-2.7.2-psx/cc1)

Two differences between our GCC 2.7.2 build and the compiler of the PsyQ 4.7
libraries show up as the same symptom: a short loaded once and used both
sign-extended and raw (`lh` + `lhu` of the same field in the ROM), and a bogus
`addiu $sp,-8/-16` frame (`.frame ... vars=8/16`) with no stack accesses.

1. try_combine: when three insns (load HI, sll 16, sra 16) combine into a
   sign-extending load while the HImode load is still needed, ours rewrites the
   second load as a SUBREG of the extended value; the ROM keeps both loads
   (the "two independent SETs" split). The SIGN_EXTEND special case is
   skipped here.
2. regclass: the combined-away shift temporaries keep stale reference counts.
   With no costs recorded their preferred class came out as ST_REGS (FP
   condition codes, no SImode), so global.c couldn't place them and reload
   gave them stack slots. The best-class search now starts below ST_REGS,
   which the soft-float PsyQ code never uses.

The whole build matches with the patched cc1 (it only changes functions that
had one of the two symptoms).
"""
import os
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
STOCK = f"{ROOT}/bin/gcc-2.7.2-psx/cc1"
PATCHED = f"{ROOT}/build/tools/gcc-2.7.2-psx/cc1"


def patch(src, dst):
    d = bytearray(open(src, "rb").read())
    phoff, = struct.unpack_from("<I", d, 0x1C)
    phentsize, phnum = struct.unpack_from("<HH", d, 0x2A)
    segs = []
    for i in range(phnum):
        t, off, va, _, fsz = struct.unpack_from("<5I", d, phoff + i * phentsize)
        if t == 1:
            segs.append((va, off, fsz))

    def fo(va):
        for v, o, s in segs:
            if v <= va < v + s:
                return va - v + o
        raise ValueError(hex(va))

    def put(va, old, new):
        o = fo(va)
        if d[o:o + len(old)] != bytes(old):
            sys.exit(f"patch_cc1: unexpected bytes at {va:#x}: {d[o:o + len(old)].hex()}")
        d[o:o + len(new)] = new

    # 1. try_combine+9186: `jne` after `cmp $SIGN_EXTEND` -> `jmp` to the same target
    va = 0x08128E9F
    o = fo(va)
    rel = int.from_bytes(d[o + 2:o + 6], "little", signed=True)
    put(va, b"\x0f\x85" + d[o + 2:o + 6],
        b"\xe9" + (rel + 1).to_bytes(4, "little", signed=True) + b"\x90")
    # 2. regclass+2986: `for (class = ALL_REGS - 1; ...)` -> start at MD_REGS (6)
    put(0x0814313C, b"\xbe\x07\x00\x00\x00", b"\xbe\x06\x00\x00\x00")

    os.makedirs(os.path.dirname(dst), exist_ok=True)
    tmp = dst + ".tmp"
    with open(tmp, "wb") as f:
        f.write(d)
    os.chmod(tmp, 0o755)
    os.replace(tmp, dst)


def ensure():
    """Path of the patched cc1, (re)built when missing or stale."""
    me = os.path.abspath(__file__)
    if (not os.path.exists(PATCHED)
            or os.path.getmtime(PATCHED) < max(os.path.getmtime(STOCK), os.path.getmtime(me))):
        patch(STOCK, PATCHED)
    return PATCHED


if __name__ == "__main__":
    if len(sys.argv) == 3:
        patch(sys.argv[1], sys.argv[2])
    else:
        print(ensure())
