#!/usr/bin/env python3
"""Write objdiff.json with one unit per C file under src/, for the version
being built (VERSION, as for make; eu by default).

Target objects are splat's full disassembly of each C segment
(expected/<version>/asm/<segment>/<file>.s.o); base objects are the files
built from src/ (build/<version>/src/...), where every function still behind
INCLUDE_ASM carries a .NON_MATCHING label that objdiff drops from the
progress count. splat marks every symbol it writes that way, the target's
too: on the target side objdiff only drops the marker, not the symbol.

objdiff counts a data section (.rodata, .data) as matched only when all of
it matches, and it compares a section's bytes and relocations up to the end
of its last symbol, pairing the symbols by name. The report works on copies
of both objects (build/<version>/report/, expected/<version>/report/) that
say the same thing the same way, so that data which is byte for byte the
original's counts, and nothing else does:

- The rodata GCC emits for string literals, constants and jump tables has
  no symbol of its own, while the target names it (D_..., jtbl_...,
  *_STR_...): the base gets the target's names at the same offsets
  (name_rodata). The names only set the compared range; whatever the base
  holds there must still be identical.
- The rodata still included from asm (INCLUDE_RODATA, and the jump tables
  of the functions behind INCLUDE_ASM) has the original's bytes, so it gets
  one byte changed (mark_asm_rodata): the section it is in doesn't count
  until all of it is C.
- GCC writes a pointer to a local datum or to a jump table's case as the
  section plus the offset, splat as the label it names there: where they
  differ, both are rewritten as section plus offset (relocate_by_section),
  and the base gets the target's label where it has no symbol
  (name_reloc_targets), so that objdiff resolves both to the same place.
- splat counts the padding after a module's last datum as part of it, GCC
  leaves it to the linker (pad_sections).

A source file X_2.c is the second half of an original object split in
config/us/main.yaml (X.c and X_2.c come from one file before the split). Its
unit is reported together with X's under X's name, from the two objects
linked with `ld -r`, so progress keeps being tracked per unit as before.
An overlay split into several objects, X.c, X_2.c, X_3.c..., is not a pair
of halves: each of its files is a unit of its own (CARDGAME, FIGHTSTG).

The PsyQ SDK (src/main/psyq/) is Sony's code linked into the executable, not
the game's: like other PSX decomps (jype0/dw_decomp), progress doesn't count
it, so it gets no unit. It is still built and checked by `make compare`.

The executable's game data is one unit, main/game_data: splat's data files
(GAME_DATA) against the C files in src/main/data/ that hold it until it moves
next to the code that uses it.

A version that doesn't build a C file yet still has its unit, with no base
object, when splat writes the module's code at the same path as in the USA
version (the European one is split into the USA modules,
tools/split_version.py): asm/eu/cnty_sel/cnty_sel.s is cnty_sel/cnty_sel's
code, not yet C. Its target is that code with the module's rodata, data and
bss segments (asm/<version>/<binary>/data/<module>.rodata.s...), so the report
counts all of it as still to do. A binary with neither (not split, or a
stage only that version has) is one unit of its own, from all its code and
data (asm_units).
"""

import json
import shutil
import subprocess

from elftools.elf.elffile import ELFFile

import version

ROOT = version.ROOT
V = version.VERSION
ASM = version.ASM_DIR

# The executable's game code and one category per overlay (src/<overlay>/,
# see OVERLAYS in the Makefile).
CATEGORIES = [
    {"id": "game", "name": "Game (executable)"},
]

# the data sections objdiff compares byte for byte
DATA_SECTIONS = (".rodata", ".data")

# the relocation of a pointer in data
R_MIPS_32 = 2


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


def combine(out: str, parts: list) -> None:
    """OUT as a copy of the one object in PARTS, or the objects linked."""
    if len(parts) == 1:
        (ROOT / out).parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(ROOT / parts[0], ROOT / out)
    else:
        link(out, parts)


def data_segments(name: str) -> list:
    """splat's objects of the rodata, data and bss segments of the module
    NAME (binary/module), which a version that doesn't build it from C yet
    has apart from its code."""
    binary, module = name.split("/", 1)
    paths = [f"{binary}/data/{module}.{kind}.s" for kind in ("rodata", "data", "bss")]
    return [f"expected/{V}/asm/{p}.o" for p in paths if (ASM / p).exists()]


class Elf:
    """What the report needs of an object: its sections, symbols and the
    relocations of its data, with where each is in the file."""

    def __init__(self, path: str):
        with open(ROOT / path, "rb") as f:
            elf = ELFFile(f)
            # (name, file offset, size) of each section, by index
            self.sections = [(s.name, s["sh_offset"], s["sh_size"]) for s in elf.iter_sections()]
            self.index = {name: i for i, (name, _, _) in enumerate(self.sections)}
            symtab = elf.get_section_by_name(".symtab")
            self.symtab = (symtab["sh_offset"], symtab["sh_entsize"])
            self.symbols = [{"name": s.name, "value": s["st_value"], "size": s["st_size"],
                             "shndx": s["st_shndx"], "type": s["st_info"]["type"],
                             "bind": s["st_info"]["bind"]}
                            for s in symtab.iter_symbols()]
            # section: [(file offset of the entry, offset, symbol, type)]
            self.relocs = {}
            for name in DATA_SECTIONS:
                rel = elf.get_section_by_name(".rel" + name)
                if rel is not None:
                    self.relocs[name] = [(rel["sh_offset"] + i * rel["sh_entsize"],
                                          r["r_offset"], r["r_info_sym"], r["r_info_type"])
                                         for i, r in enumerate(rel.iter_relocations())]

    def defined(self, sym: dict) -> bool:
        """Whether SYM is defined in one of the object's sections (not an
        extern, a common or an absolute)."""
        return isinstance(sym["shndx"], int) and 0 < sym["shndx"] < len(self.sections)

    def section_symbol(self, index: int):
        """The index of the symbol of section INDEX, or None."""
        return next((i for i, s in enumerate(self.symbols)
                     if s["type"] == "STT_SECTION" and s["shndx"] == index), None)

    def size(self, section: str) -> int:
        """The size of SECTION (0 if there is none)."""
        index = self.index.get(section)
        return 0 if index is None else self.sections[index][2]

    def free(self, section: str, offset: int) -> bool:
        """Whether OFFSET is inside SECTION and no symbol is at it or around
        it. objdiff gives no size to a symbol inside another, and fails when
        it pairs one of the target's by name with such a symbol."""
        index = self.index.get(section)
        return offset < self.size(section) and not any(
            s["value"] <= offset < s["value"] + max(s["size"], 1) for s in self.symbols
            if s["shndx"] == index and s["name"] and s["type"] != "STT_SECTION")

    def symbols_in(self, section: str) -> list:
        """(name, offset) of the named symbols defined in SECTION."""
        index = self.index.get(section)
        if index is None:
            return []
        return [(s["name"], s["value"]) for s in self.symbols
                if s["shndx"] == index and s["name"] and s["type"] != "STT_SECTION"]


def section_bytes(path: str, name: str) -> bytes:
    """The contents of PATH's section NAME (empty if it has none)."""
    with open(ROOT / path, "rb") as f:
        section = ELFFile(f).get_section_by_name(name)
        return section.data() if section else b""


def objcopy(path: str, args: list) -> None:
    if args:
        subprocess.run(["mipsel-linux-gnu-objcopy"] + args + [path], cwd=ROOT, check=True)


def pad_sections(base: str, target: str) -> None:
    """Pad BASE's .rodata and .data with the zeros that end TARGET's.

    splat counts the padding after a module's last datum as part of it;
    GCC leaves it to the linker, which fills the same zeros in the ROM.
    ld -r pads them and keeps the sections' relocations."""
    pads = {}
    for name in DATA_SECTIONS:
        ours, theirs = section_bytes(base, name), section_bytes(target, name)
        extra = theirs[len(ours):]
        if ours and 0 < len(extra) < 8 and not any(extra):
            pads[name] = len(extra)
    if not pads:
        return
    script = ROOT / (base + ".ld")
    script.write_text("SECTIONS {\n" + "".join(
        f"  {name} 0 : {{ *({name}) . += {n}; }}\n" for name, n in pads.items()) + "}\n")
    padded = base + ".padded"
    subprocess.run(["mipsel-linux-gnu-ld", "-r", "-T", str(script), "-o", padded, base], cwd=ROOT, check=True)
    (ROOT / padded).replace(ROOT / base)
    script.unlink()


def asm_rodata(path: str) -> set:
    """The names of PATH's rodata still included from asm: what
    INCLUDE_RODATA and the functions behind INCLUDE_ASM bring (their jump
    tables), which splat marks .NON_MATCHING."""
    return {name[: -len(".NON_MATCHING")] for name, _ in Elf(path).symbols_in(".rodata")
            if name.endswith(".NON_MATCHING")}


def name_rodata(base: str, target: str) -> None:
    """Give BASE's anonymous rodata the names TARGET has at the same offsets."""
    # the asm's .NON_MATCHING marker makes objdiff leave its rodata out of
    # the section's compared range and cut the section short; without it,
    # it is compared like the rest (and mark_asm_rodata keeps it from
    # counting)
    args = []
    for name in sorted(asm_rodata(base)):
        args += ["--strip-symbol", name + ".NON_MATCHING"]
    # a name the base already uses (defined elsewhere, or referenced) stays
    # out, and so does one where the base has its own datum
    ours = Elf(base)
    used = {s["name"] for s in ours.symbols if s["name"]}
    for name, offset in Elf(target).symbols_in(".rodata"):
        if name not in used and not name.endswith(".NON_MATCHING") and ours.free(".rodata", offset):
            args += ["--add-symbol", f"{name}=.rodata:{offset:#x},object,global"]
    objcopy(base, args)


def name_reloc_targets(base: str, target: str) -> None:
    """Give BASE the labels TARGET's data points to outside .rodata (a jump
    table's cases in .text, a datum in .data) where BASE has no symbol.

    objdiff resolves a pointer written as section plus offset to the symbol
    at that place, and compares the symbols' offsets: with a symbol at the
    same offset on both sides, the pointers are the same if the offsets
    are. A case's label goes inside its function, as in the target (where
    it has no size either); a datum's only where the base has no symbol
    around it (see Elf.free)."""
    ours, theirs = Elf(base), Elf(target)
    have = {(s["shndx"], s["value"]) for s in ours.symbols if ours.defined(s)}
    used = {s["name"] for s in ours.symbols if s["name"]}
    labels = {}
    for relocs in theirs.relocs.values():
        for _, _, index, kind in relocs:
            sym = theirs.symbols[index]
            if kind != R_MIPS_32 or not theirs.defined(sym) or sym["type"] == "STT_SECTION":
                continue
            section = theirs.sections[sym["shndx"]][0]
            if section == ".rodata" or sym["value"] >= ours.size(section):
                continue
            if (ours.index[section], sym["value"]) in have or sym["name"] in used:
                continue
            label = section == ".text" and sym["size"] == 0 and sym["type"] == "STT_NOTYPE"
            if not (label or ours.free(section, sym["value"])):
                continue
            labels[sym["name"]] = (section, sym["value"])
    objcopy(base, [arg for name, (section, value) in sorted(labels.items())
                   for arg in ("--add-symbol", f"{name}={section}:{value:#x},global")])


def mark_asm_rodata(path: str, names: set) -> None:
    """Flip the first byte of each of NAMES in PATH's .rodata.

    The asm's rodata is the target's bytes, so objdiff would count it as
    matched although it is still asm. A changed byte makes the section it
    is in differ, and objdiff counts a data section only when all of it
    matches: the report then shows that section as missing until its data
    is written in C."""
    elf = Elf(path)
    if ".rodata" not in elf.index:
        return
    start = elf.sections[elf.index[".rodata"]][1]
    offsets = [start + value for name, value in elf.symbols_in(".rodata") if name in names]
    if not offsets:
        return
    blob = bytearray((ROOT / path).read_bytes())
    for offset in offsets:
        blob[offset] ^= 0xFF
    (ROOT / path).write_bytes(blob)


def type_rodata_objects(path: str) -> None:
    """Give the global names GCC defines in PATH's .rodata the object type.

    GCC declares no type for its data, so a const array's symbol is
    untyped, while the target's names added above are objects. objdiff
    sizes an object up to the next object, over the untyped symbols in
    between, which are then left without a size and can't be paired; as
    objects, every symbol ends where the next one starts."""
    elf = Elf(path)
    rodata = elf.index.get(".rodata")
    if rodata is None:
        return
    offset, entsize = elf.symtab
    entries = [offset + i * entsize for i, s in enumerate(elf.symbols)
               if s["shndx"] == rodata and s["name"]
               and s["type"] == "STT_NOTYPE" and s["bind"] == "STB_GLOBAL"]
    if not entries:
        return
    blob = bytearray((ROOT / path).read_bytes())
    for entry in entries:
        # st_info: binding in the high nibble, type in the low one (1 = object)
        blob[entry + 12] = (blob[entry + 12] & 0xF0) | 1
    (ROOT / path).write_bytes(blob)


def relocate_by_section(base: str, target: str) -> None:
    """Where BASE and TARGET write a pointer in .rodata or .data at the same
    offset against different symbols, write both as the symbol's section
    plus its offset.

    splat names what a table points to (a string, a jump table's case, a
    datum), so the original's relocations use those labels; GCC relocates
    against the section plus the offset, stored in the word, for anything
    without a global name. Same pointer, written differently: the rewrite
    keeps where it points to, and the words then hold the same offsets if
    the pointers are the same. Pointers to the same name are left as they
    are (one side may only know it as an extern or a common)."""
    elfs = {path: Elf(path) for path in (base, target)}
    blobs = {path: bytearray((ROOT / path).read_bytes()) for path in (base, target)}

    def word_at(path: str, section: str, offset: int) -> int:
        """The file offset of the word at OFFSET in PATH's SECTION."""
        return elfs[path].sections[elfs[path].index[section]][1] + offset

    def written(path: str, section: str, reloc: tuple) -> tuple:
        """How PATH writes RELOC: the symbol's name and the stored word."""
        elf, start = elfs[path], word_at(path, section, reloc[1])
        sym = elf.symbols[reloc[2]]
        name = elf.sections[sym["shndx"]][0] if sym["type"] == "STT_SECTION" else sym["name"]
        return name, bytes(blobs[path][start:start + 4])

    changed = False
    for section in DATA_SECTIONS:
        if section not in elfs[base].relocs or section not in elfs[target].relocs:
            continue
        theirs = {r[1]: r for r in elfs[target].relocs[section]}
        for ours in elfs[base].relocs[section]:
            other = theirs.get(ours[1])
            if other is None or ours[3] != R_MIPS_32 or other[3] != R_MIPS_32:
                continue
            if written(base, section, ours) == written(target, section, other):
                continue
            for path, (entry, offset, index, kind) in ((base, ours), (target, other)):
                elf = elfs[path]
                sym = elf.symbols[index]
                if not elf.defined(sym) or sym["type"] == "STT_SECTION":
                    continue
                section_sym = elf.section_symbol(sym["shndx"])
                if section_sym is None:
                    continue
                blob, start = blobs[path], word_at(path, section, offset)
                blob[entry + 4:entry + 8] = ((section_sym << 8) | kind).to_bytes(4, "little")
                value = int.from_bytes(blob[start:start + 4], "little") + sym["value"]
                blob[start:start + 4] = (value & 0xFFFFFFFF).to_bytes(4, "little")
                changed = True
    if changed:
        for path, blob in blobs.items():
            (ROOT / path).write_bytes(blob)


def prepare(base: str, target: str) -> None:
    """Make the report's copies BASE and TARGET write the same data the
    same way (see the top of the file)."""
    pad_sections(base, target)
    asm = asm_rodata(base)
    name_rodata(base, target)
    name_reloc_targets(base, target)
    mark_asm_rodata(base, asm)
    type_rodata_objects(base)
    relocate_by_section(base, target)


def asm_units(names: list) -> list:
    """One unit per binary that has no unit yet, with no base object: splat's
    code and data of the executable, an overlay or a stage linked together,
    so that the progress counts the whole of a version even before it is
    split into the USA modules (and a stage only it has)."""
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
    # the modules of this version: the ones splat writes the code of at the
    # C file's path (a full disassembly of a C segment, or an asm segment of
    # a module the version doesn't build from C yet)
    names = [n for n in names if (ASM / f"{n}.s").exists()]
    built = {n for n in names if (ROOT / f"build/{V}/src/{n}.c.o").exists()}
    halves = {n[:-2]: n for n in names
              if n.endswith("_2") and n[:-2] in names and f"{n[:-2]}_3" not in names}
    units = []
    for name in names:
        if name in halves.values():
            continue
        parts = [name] + ([halves[name]] if name in halves else [])
        target = f"expected/{V}/report/{name}.s.o"
        unit = {"name": name, "target_path": target}
        if all(n in built for n in parts):
            base = f"build/{V}/report/{name}.c.o"
            combine(target, [f"expected/{V}/asm/{n}.s.o" for n in parts])
            combine(base, [f"build/{V}/src/{n}.c.o" for n in parts])
            prepare(base, target)
            unit["base_path"] = base
        else:
            # not C yet (all or part of it): the code with the data segments
            # of what is still asm, all of it to do
            objs = []
            for n in parts:
                objs.append(f"expected/{V}/asm/{n}.s.o")
                if n not in built:
                    objs += data_segments(n)
            combine(target, objs)
        unit["metadata"] = {"progress_categories": [category_for(name)]}
        units.append(unit)

    data = [f"expected/{V}/asm/main/data/{d}.s.o" for d in GAME_DATA
            if (ASM / f"main/data/{d}.s").exists()]
    if data:
        target = f"expected/{V}/report/main/game_data.s.o"
        link(target, data)
        unit = {
            "name": "main/game_data",
            "target_path": target,
            "metadata": {"progress_categories": ["game"]},
        }
        base = [f"build/{V}/{c.with_suffix('.c.o').relative_to(ROOT).as_posix()}"
                for c in sorted((ROOT / "src/main/data").glob("*.c"))]
        if base and all((ROOT / b).exists() for b in base):
            unit["base_path"] = f"build/{V}/report/main/game_data.c.o"
            link(unit["base_path"], base)
            prepare(unit["base_path"], target)
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
