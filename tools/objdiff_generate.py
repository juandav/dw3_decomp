#!/usr/bin/env python3
"""Write objdiff.json with one unit per C file under src/, for the version
being built (VERSION, as for make; eu by default).

Target objects are splat's full disassembly of each C segment
(expected/<version>/asm/<segment>/<file>.s.o); base objects are the files
built from src/ (build/<version>/src/...), where every function still behind INCLUDE_ASM carries a .NON_MATCHING
label that objdiff drops from the progress count.

A source file X_2.c is the second half of an original object split in
config/main.yaml (X.c and X_2.c come from one file before the split). Its
unit is reported together with X's under X's name, from the two objects
linked with `ld -r`, so progress keeps being tracked per unit as before.

The PsyQ SDK (src/main/psyq/) is Sony's code linked into the executable, not
the game's: like other PSX decomps (jype0/dw_decomp), progress doesn't count
it, so it gets no unit. It is still built and checked by `make compare`.

The executable's game data is one unit, main/game_data: splat's data files
(GAME_DATA) against the C files in src/main/data/ that hold it until it moves
next to the code that uses it.
"""

import json
import subprocess

import version

ROOT = version.ROOT
V = version.VERSION
ASM = version.ASM_DIR

# The executable's game code and one category per overlay (src/<overlay>/,
# see OVERLAYS in the Makefile).
CATEGORIES = [
    {"id": "game", "name": "Game (executable)"},
]


def is_library(name: str) -> bool:
    return name == "main/psyq" or name.startswith("main/psyq/")


# splat's files of the executable's game data (not the SDK's psyq and gte_tables)
GAME_DATA = ["data/game.data", "data/game_2.data", "data/game_3.data", "data/game_bss.bss"]


def category_for(name: str) -> str:
    if name.startswith("main/"):
        return "game"
    return name.split("/")[0]


def link(out: str, parts: list) -> None:
    """ld -r the objects PARTS into OUT (paths relative to the root)."""
    (ROOT / out).parent.mkdir(parents=True, exist_ok=True)
    subprocess.run(["mipsel-linux-gnu-ld", "-r", "-o", out] + parts, cwd=ROOT, check=True)


def asm_units(names: list) -> list:
    """One unit per binary that has no C file yet, with no base object: splat's
    code and data of the executable, an overlay or a stage linked together,
    so that the progress counts the whole of a version even before its first
    C file (the European one, for now)."""
    stages = [line.split()[0] for line in open(version.CONFIG_DIR / "stages.txt")
              if line.strip() and not line.startswith("#")]
    binaries = {d.name: [f"{d.name}/{d.name}.s"] + [f"{d.name}/data/{f.name}"
                for f in sorted((d / "data").glob("*.s"))]
                for d in sorted(ASM.iterdir()) if d.is_dir() and d.name != "stages"}
    for stage in (s.lower() for s in stages):
        binaries[f"stages/{stage}"] = [f"stages/{stage}.s"] + [
            f"stages/data/{f.name}" for f in sorted((ASM / "stages/data").glob(f"{stage}[._]*s"))]
    if "main" in binaries:
        binaries["main"][0] = "main/text.s"
    units = []
    for binary, files in binaries.items():
        if any(n == binary or n.startswith(f"{binary}/") for n in names):
            continue
        objs = [f"expected/{V}/asm/{f}.o" for f in files if (ASM / f).exists()]
        if not objs:
            continue
        name = binary if "/" in binary else f"{binary}/{binary}"
        target = f"expected/{V}/report/{name}.s.o"
        link(target, objs)
        units.append({"name": name, "target_path": target,
                      "metadata": {"progress_categories": [category_for(name)]}})
    return units


def main() -> None:
    names = [src.relative_to(ROOT / "src").with_suffix("").as_posix()
             for src in sorted((ROOT / "src").rglob("*.c"))]
    names = [n for n in names if not is_library(n) and not n.startswith("main/data/")]
    # the C files of this version: the ones built for it, which splat made a
    # full disassembly of
    names = [n for n in names if (ASM / f"{n}.s").exists()
             and (ROOT / f"build/{V}/src/{n}.c.o").exists()]
    halves = {n[:-2]: n for n in names if n.endswith("_2") and n[:-2] in names}
    units = []
    for name in names:
        if name in halves.values():
            continue
        target = f"expected/{V}/asm/{name}.s.o"
        base = f"build/{V}/src/{name}.c.o"
        if name in halves:
            second = halves[name]
            target = f"expected/{V}/report/{name}.s.o"
            base = f"build/{V}/report/{name}.c.o"
            link(target, [f"expected/{V}/asm/{name}.s.o", f"expected/{V}/asm/{second}.s.o"])
            link(base, [f"build/{V}/src/{name}.c.o", f"build/{V}/src/{second}.c.o"])
        units.append(
            {
                "name": name,
                "target_path": target,
                "base_path": base,
                "metadata": {"progress_categories": [category_for(name)]},
            }
        )

    data = [f"expected/{V}/asm/main/data/{d}.s.o" for d in GAME_DATA
            if (ASM / f"main/data/{d}.s").exists()]
    if data:
        link(f"expected/{V}/report/main/game_data.s.o", data)
        unit = {
            "name": "main/game_data",
            "target_path": f"expected/{V}/report/main/game_data.s.o",
            "metadata": {"progress_categories": ["game"]},
        }
        base = [f"build/{V}/{c.with_suffix('.c.o').relative_to(ROOT).as_posix()}"
                for c in sorted((ROOT / "src/main/data").glob("*.c"))]
        if base:
            link(f"build/{V}/report/main/game_data.c.o", base)
            unit["base_path"] = f"build/{V}/report/main/game_data.c.o"
        units.append(unit)

    units += asm_units(names)

    categories = list(CATEGORIES)
    for overlay in sorted({category_for(u["name"]) for u in units} - {"game"}):
        label = "Stage overlays" if overlay == "stages" else f"{overlay.upper()} overlay"
        categories.append({"id": overlay, "name": label})

    config = {
        "$schema": "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json",
        "custom_make": "make",
        "custom_args": [f"VERSION={V}"],
        "build_target": False,
        "build_base": True,
        "watch_patterns": ["*.c", "*.h", "*.s", "*.inc"],
        "units": units,
        "progress_categories": categories,
    }

    with open(ROOT / "objdiff.json", "w") as f:
        json.dump(config, f, indent=2)
        f.write("\n")


if __name__ == "__main__":
    main()
