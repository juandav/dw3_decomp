#!/usr/bin/env python3
"""Turn a splat data file (.word lines) into C definitions.

usage: data_to_c.py [--sizes] asm/<ovl>/data/<ovl>.data.s > data.c

Each data symbol becomes an s32 (one word) or an s32 array; words that splat
wrote as a symbol become that symbol's address. Symbols of .short or .byte
become u16 or u8 arrays, and symbols that mix sizes u8 arrays of their bytes.
GCC word-aligns every array, so each object must start and end on a word:
`data_to_c.py --sizes FILE` prints the symbol sizes (for config/symbols_<ovl>.txt)
that merge the symbols splat split off at odd offsets into the object before. The declarations those need
come first. This is only a starting point that reproduces the bytes: give the
data real types once the code that uses it is understood.
"""

import re
import sys

VALUE = re.compile(r"^\s+/\* [0-9A-F]+ ([0-9A-F]{8})(?: [0-9A-F]{8})? \*/\s+\.(word|short|byte)\s+(\S+(?: [+-] \S+)?)")
LABEL = re.compile(r"^dlabel (\w+)")
OTHER = re.compile(r"^\s+/\* .*\*/\s+\.(half|ascii|asciz|space)\b")
TYPES = {"word": "s32", "short": "u16", "byte": "u8"}
SIZES = {"word": 4, "short": 2, "byte": 1}


def parse(path):
    """[(name, address, [(kind, value)])] of the data file."""
    symbols = []
    for line in open(path):
        if m := LABEL.match(line):
            symbols.append([m.group(1), None, []])
        elif m := VALUE.match(line):
            if symbols[-1][1] is None:
                symbols[-1][1] = int(m.group(1), 16)
            symbols[-1][2].append((m.group(2), m.group(3)))
        elif OTHER.match(line):
            sys.exit(f"unsupported data: {line.strip()}")
    return symbols


def sizes(symbols):
    """Symbols that must be one object with the ones after them, so that every
    C object starts and ends on a word: GCC word-aligns every array. Printed as
    splat symbol_addrs lines; splat then writes BASE+offset for the rest."""
    i = 0
    while i < len(symbols):
        name, addr, values = symbols[i]
        end = addr + sum(SIZES[k] for k, _ in values)
        j = i + 1
        while end % 4 and j < len(symbols):
            end = symbols[j][1] + sum(SIZES[k] for k, _ in symbols[j][2])
            j += 1
        if j > i + 1:
            print(f"{name} = 0x{addr:08X}; // size:0x{end - addr:X}")
        i = j


def main():
    symbols = parse(sys.argv[-1])
    if "--sizes" in sys.argv:
        return sizes(symbols)
    kinds = {}
    for name, addr, values in symbols:
        if addr % 4:
            sys.exit(f"{name} is not word-aligned: run with --sizes")
        if sum(SIZES[k] for k, _ in values) % 4:
            sys.exit(f"{name} doesn't fill whole words: run with --sizes")
        kinds[name] = values[0][0] if len({k for k, _ in values}) == 1 else "bytes"
    scalars = {name for name, _, values in symbols if len(values) == 1}

    def value(v):
        if re.fullmatch(r"-?(0x[0-9A-Fa-f]+|\d+)", v):
            n = int(v, 16) if "0x" in v else int(v)
            n &= 0xFFFFFFFF
            return str(n - (1 << 32) if n & 0x80000000 else n) if n < 0x10000 or n > 0xFFFF0000 else f"0x{n:X}"
        sym, _, off = v.partition(" ")
        addr = f"&{sym}" if sym in scalars else sym
        return f"(s32){addr}" + (f" {off}" if off else "")

    out, decls = [], []
    for name, _, values in symbols:
        kind = kinds[name]
        if kind == "bytes":
            # mixed sizes: its bytes, little-endian (only plain numbers can be split)
            data = b""
            for k, v in values:
                if not re.fullmatch(r"-?(0x[0-9A-Fa-f]+|\d+)", v):
                    sys.exit(f"{name} mixes sizes and holds {v}: give it a real type by hand")
                data += (int(v, 0) & ((1 << (8 * SIZES[k])) - 1)).to_bytes(SIZES[k], "little")
            vals = [f"0x{b:02X}" for b in data]
            rows = [", ".join(vals[i:i + 8]) + "," for i in range(0, len(vals), 8)]
            out.append(f"u8 {name}[] = {{\n" + "\n".join("    " + r for r in rows) + "\n};")
            continue
        vs = [v for _, v in values]
        for v in vs:
            if not re.fullmatch(r"-?(0x[0-9A-Fa-f]+|\d+)", v):
                v = v.split(" ")[0]
                d = f"void {v}();" if v.startswith("func_") else (
                    f"extern s32 {v};" if v in scalars else f"extern s32 {v}[];")
                if d not in decls:
                    decls.append(d)
        t = TYPES[kind]
        if len(vs) == 1:
            out.append(f"{t} {name} = {value(vs[0])};")
        else:
            vals = [value(v) if kind == "word" else v for v in vs]
            n = 4 if kind == "word" else 8
            rows = [", ".join(vals[i:i + n]) + "," for i in range(0, len(vals), n)]
            out.append(f"{t} {name}[] = {{\n" + "\n".join("    " + r for r in rows) + "\n};")
    print("\n".join(decls))
    if decls:
        print()
    print("\n".join(out))


if __name__ == "__main__":
    main()
