#!/usr/bin/env python3
"""Turn a splat data file (.word lines) into C definitions.

usage: data_to_c.py asm/<ovl>/data/<ovl>.data.s > data.c

Each data symbol becomes an s32 (one word) or an s32 array; words that splat
wrote as a symbol become that symbol's address. Symbols of .short or .byte
become u16 or u8 arrays. Anything that doesn't fit whole, word-aligned words
(GCC word-aligns every array) or mixes sizes needs a real type by hand. The declarations those need
come first. This is only a starting point that reproduces the bytes: give the
data real types once the code that uses it is understood.
"""

import re
import sys

VALUE = re.compile(r"^\s+/\* [0-9A-F]+ ([0-9A-F]{8})(?: [0-9A-F]{8})? \*/\s+\.(word|short|byte)\s+(\S+)")
LABEL = re.compile(r"^dlabel (\w+)")
OTHER = re.compile(r"^\s+/\* .*\*/\s+\.(half|ascii|asciz|space)\b")
TYPES = {"word": "s32", "short": "u16", "byte": "u8"}
SIZES = {"word": 4, "short": 2, "byte": 1}


def main():
    symbols = []  # (name, [values])
    kinds = {}  # name -> directive of its values
    for line in open(sys.argv[1]):
        if m := LABEL.match(line):
            symbols.append((m.group(1), []))
        elif m := VALUE.match(line):
            name = symbols[-1][0]
            if not symbols[-1][1] and int(m.group(1), 16) % 4:
                sys.exit(f"{name} is not word-aligned: give it a real type by hand")
            if kinds.setdefault(name, m.group(2)) != m.group(2):
                sys.exit(f"{name} mixes .{kinds[name]} and .{m.group(2)}: give it a real type by hand")
            symbols[-1][1].append(m.group(3))
        elif OTHER.match(line):
            sys.exit(f"unsupported data: {line.strip()}")
    for name, values in symbols:
        if len(values) * SIZES[kinds[name]] % 4:
            sys.exit(f"{name} doesn't fill whole words: give it a real type by hand")
    defined = {name for name, _ in symbols}
    scalars = {name for name, values in symbols if len(values) == 1}
    words = {name for name in kinds if kinds[name] == "word"}

    def value(v):
        if re.fullmatch(r"-?(0x[0-9A-Fa-f]+|\d+)", v):
            n = int(v, 16) if "0x" in v else int(v)
            n &= 0xFFFFFFFF
            return str(n - (1 << 32) if n & 0x80000000 else n) if n < 0x10000 or n > 0xFFFF0000 else f"0x{n:X}"
        addr = f"&{v}" if v in scalars else v
        return f"(s32){addr}"

    out, decls = [], []
    for name, values in symbols:
        for v in values:
            if re.fullmatch(r"(func|D|jtbl)_[0-9A-F]{8}", v):
                d = f"void {v}();" if v.startswith("func_") else (
                    f"extern s32 {v};" if v in scalars else f"extern s32 {v}[];")
                if d not in decls:
                    decls.append(d)
        t = TYPES[kinds[name]]
        if len(values) == 1:
            out.append(f"{t} {name} = {value(values[0])};")
        else:
            vals = [value(v) if name in words else v for v in values]
            n = 4 if name in words else 8
            rows = [", ".join(vals[i:i + n]) + "," for i in range(0, len(vals), n)]
            out.append(f"{t} {name}[] = {{\n" + "\n".join("    " + r for r in rows) + "\n};")
    print("\n".join(decls))
    if decls:
        print()
    print("\n".join(out))


if __name__ == "__main__":
    main()
