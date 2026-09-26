#!/usr/bin/env python3
"""Fill `j $31` delay slots the way ASPSX did for the GCC 2.7.2 PsyQ objects.

GCC 2.7.2 leaves the function return (`j $31`) in reorder mode and maspsx
follows it with a nop. The ASPSX used for those objects moved the previous
instruction into the delay slot instead, unless that would put a load of
$31 right before the jump.

usage: aspsx_reorder.py < maspsx_output.s > output.s
"""

import re
import sys

BRANCHES = re.compile(
    r"(j|jal|jr|jalr|b|bal|beq|bne|blez|bgtz|bltz|bgez|beqz|bnez|"
    r"bltzal|bgezal|beql|bnel|blezl|bgtzl|bltzl|bgezl)$"
)
LOADS = re.compile(r"(lw|lh|lhu|lb|lbu|lwl|lwr)$")
STORES = re.compile(r"(sw|sh|sb|swl|swr)$")
# Instructions the assembler expands into several machine instructions
MACROS = re.compile(r"(la|li|div|divu|rem|remu|mul|ulw|usw|ulh|ulhu)$")


def split(line):
    """Return (mnemonic, operands) for an instruction line, else None."""
    code = line.split("#", 1)[0].strip()
    if not code or code.endswith(":") or code.startswith("."):
        return None
    parts = code.split(None, 1)
    ops = [o.strip() for o in parts[1].split(",")] if len(parts) > 1 else []
    return parts[0], ops


def main():
    lines = sys.stdin.read().split("\n")
    out = []
    i = 0
    while i < len(lines):
        line = lines[i]
        ins = split(line)
        nxt = lines[i + 1] if i + 1 < len(lines) else ""
        if (
            ins
            and ins[0] == "j"
            and ins[1] == ["$31"]
            and nxt.strip().startswith("nop")
            and "branch/jump" in nxt
        ):
            # previous instruction line
            k = len(out) - 1
            while k >= 0 and not out[k].split("#", 1)[0].strip():
                k -= 1
            prev = split(out[k]) if k >= 0 else None
            prev2 = None
            if prev:
                m = k - 1
                while m >= 0 and not out[m].split("#", 1)[0].strip():
                    m -= 1
                prev2 = split(out[m]) if m >= 0 else None
            sym_store = (
                prev is not None
                and STORES.match(prev[0]) is not None
                and len(prev[1]) == 2
                and not re.search(r"\(\$\w+\)$", prev[1][1])
            )
            movable = (
                prev is not None
                and not sym_store
                and not BRANCHES.match(prev[0])
                and not MACROS.match(prev[0])
                and prev[0] != "nop"
                and not (prev[1] and prev[1][0] == "$31")
                and not LOADS.match(prev[0])
                and not (prev2 and LOADS.match(prev2[0]) and prev2[1][:1] == ["$31"])
            )
            if movable:
                moved = out.pop(k)
                out.append(line)
                out.append(moved)
                i += 2
                continue
            if sym_store:
                # a store to a symbol: the lui of $at stays, the store moves
                reg, sym = prev[1]
                out[k] = f".set\tnoat\nlui\t$at,%hi({sym})"
                out.append(line)
                out.append(f"{prev[0]}\t{reg},%lo({sym})($at)\n.set\tat")
                i += 2
                continue
            if prev is not None and prev[0] == "la" and prev[1][0] != "$31":
                # ASPSX expands la and moves its second half into the slot
                reg, sym = prev[1]
                out[k] = f"lui\t{reg},%hi({sym})"
                out.append(line)
                out.append(f"addiu\t{reg},{reg},%lo({sym})")
                i += 2
                continue
        out.append(line)
        i += 1
    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    main()
