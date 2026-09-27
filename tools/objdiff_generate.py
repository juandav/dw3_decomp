#!/usr/bin/env python3
"""Write objdiff.json with one unit per C file under src/.

Target objects are splat's full disassembly of each C segment
(expected/asm/<segment>/<file>.s.o); base objects are the files built from
src/, where every function still behind INCLUDE_ASM carries a .NON_MATCHING
label that objdiff drops from the progress count.

A source file X_2.c is the second half of an original object split in
config/main.yaml (X.c and X_2.c come from one file before the split). Its
unit is reported together with X's under X's name, from the two objects
linked with `ld -r`, so progress keeps being tracked per unit as before.
"""

import json
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

# Units whose name starts with one of these prefixes go to that category;
# everything else is game code.
CATEGORY_PREFIXES = {
    "main/psyq": "sdk",
}

CATEGORIES = [
    {"id": "game", "name": "Game"},
    {"id": "sdk", "name": "PsyQ SDK"},
]


def category_for(name: str) -> str:
    for prefix, category in CATEGORY_PREFIXES.items():
        if name == prefix or name.startswith(prefix + "/"):
            return category
    return "game"


def link(out: str, parts: list) -> None:
    """ld -r the objects PARTS into OUT (paths relative to the root)."""
    (ROOT / out).parent.mkdir(parents=True, exist_ok=True)
    subprocess.run(["mipsel-linux-gnu-ld", "-r", "-o", out] + parts, cwd=ROOT, check=True)


def main() -> None:
    names = [src.relative_to(ROOT / "src").with_suffix("").as_posix()
             for src in sorted((ROOT / "src").rglob("*.c"))]
    halves = {n[:-2]: n for n in names if n.endswith("_2") and n[:-2] in names}
    units = []
    for name in names:
        if name in halves.values():
            continue
        target = f"expected/asm/{name}.s.o"
        base = f"build/src/{name}.c.o"
        if name in halves:
            second = halves[name]
            target = f"expected/report/{name}.s.o"
            base = f"build/report/{name}.c.o"
            link(target, [f"expected/asm/{name}.s.o", f"expected/asm/{second}.s.o"])
            link(base, [f"build/src/{name}.c.o", f"build/src/{second}.c.o"])
        units.append(
            {
                "name": name,
                "target_path": target,
                "base_path": base,
                "metadata": {"progress_categories": [category_for(name)]},
            }
        )

    config = {
        "$schema": "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json",
        "custom_make": "make",
        "build_target": False,
        "build_base": True,
        "watch_patterns": ["*.c", "*.h", "*.s", "*.inc"],
        "units": units,
        "progress_categories": CATEGORIES,
    }

    with open(ROOT / "objdiff.json", "w") as f:
        json.dump(config, f, indent=2)
        f.write("\n")


if __name__ == "__main__":
    main()
