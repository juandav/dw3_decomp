#!/usr/bin/env python3
"""Turn a splat data file (.word lines) into C definitions.

usage: data_to_c.py asm/<ovl>/data/<ovl>.data.s > data.c

Each data symbol becomes an s32 (one word) or an s32 array; words that splat
wrote as a symbol become that symbol's address. The declarations those need
come first. This is only a starting point that reproduces the bytes: give the
data real types once the code that uses it is understood.
"""

import re
import sys

WORD = re.compile(r"^\s+/\* [0-9A-F]+ [0-9A-F]{8} [0-9A-F]{8} \*/\s+\.word\s+(\S+)")
LABEL = re.compile(r"^dlabel (\w+)")
OTHER = re.compile(r"^\s+/\* .*\*/\s+\.(half|byte|short|ascii|asciz|space)\b")


def main():
    symbols = []  # (name, [values])
    for line in open(sys.argv[1]):
        if m := LABEL.match(line):
            symbols.append((m.group(1), []))
        elif m := WORD.match(line):
            symbols[-1][1].append(m.group(1))
        elif OTHER.match(line):
            sys.exit(f"not only words: {line.strip()}")
    defined = {name for name, _ in symbols}
    scalars = {name for name, values in symbols if len(values) == 1}

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
        if len(values) == 1:
            out.append(f"s32 {name} = {value(values[0])};")
        else:
            vals = [value(v) for v in values]
            rows = [", ".join(vals[i:i + 4]) + "," for i in range(0, len(vals), 4)]
            out.append(f"s32 {name}[] = {{\n" + "\n".join("    " + r for r in rows) + "\n};")
    print("\n".join(decls))
    if decls:
        print()
    print("\n".join(out))


if __name__ == "__main__":
    main()
