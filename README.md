# Digimon World 3 decomp

[![Code](https://decomp.dev/juandav/dw3_decomp.svg?mode=shield&measure=code&label=Code)](https://decomp.dev/juandav/dw3_decomp)
[![Data](https://decomp.dev/juandav/dw3_decomp.svg?mode=shield&measure=data&label=Data)](https://decomp.dev/juandav/dw3_decomp)

A work in progress matching decompilation of Digimon World 3 for the
PlayStation.

This repository does not contain any game data. You need your own dump of the
game to build it.

| | |
|---|---|
| Version | USA (`SLUS-01436`) |
| Disc image | `Digimon World 3 (USA).bin`, SHA-1 `f0b022f9be53cbce14640abd8f01beaadcb35208` |
| Main executable | `SLUS_014.36`, SHA-1 `444653259f78ddb483fd22af72cce9276f42f214` |
| Compiler | GCC 2.8.1 (`-O2 -G0`) + ASPSX 2.86, emulated with [maspsx](https://github.com/mkst/maspsx) |
| SDK | PsyQ 4.7 |

## Dependencies

Install the following packages:
```
binutils-mipsel-linux-gnu gcc-mipsel-linux-gnu git make python3 python3-venv unzip wget
```

Install Python dependencies:
```
python3 -m venv .venv
. .venv/bin/activate
pip3 install -r requirements.txt
```

Download tools (GCC 2.8.1 for PSX, objdiff-cli and mkpsxiso):
```
tools/dl_deps.sh
```

## Build

```
# Update submodules
git submodule update --init --recursive

# Dump original PSX Digimon World 3 (USA) ISO
bin/mkpsxiso-2.20-Linux/bin/dumpsxiso -x disks/us -s disks/us/us.xml "/path/to/Digimon World 3 (USA).bin"

# Disassemble the original executable
make regenerate

# (Optional) Create file local.mk to override defaults
TOOLCHAIN := /path/to/mipsel-linux-gnu-

# Build the executable
make -j$(nproc)

# Compare it with the original
make compare

# Generate the objdiff config and the progress report
make objdiff
make report
```

`make compare` must print `build/SLUS_014.36: OK`. A function only counts as
decompiled once the whole executable still matches.

## Layout

| Path | Contents |
|---|---|
| `config/main.yaml` | splat config for `SLUS_014.36` |
| `config/symbols.txt` | known symbols |
| `src/main/game.c` | game code, `0x80010F80`-`0x80020998` |
| `src/main/psyq.c` | PsyQ libraries, `0x80020998`-`0x8003E9D8` |
| `asm/main/crt0.s` | PsyQ startup (`2MBYTE.OBJ`), `0x80010EBC`-`0x80010F80` |
| `include/` | headers and assembler macros |
| `tools/` | build helpers |

Memory map of `SLUS_014.36` (psylink puts `.rodata` in front of `.text`):

| Section | Address |
|---|---|
| `.rodata` | `0x80010000`-`0x80010EBC` |
| `.text` | `0x80010EBC`-`0x8003E9D8` |
| `.data` | `0x8003E9D8`-`0x8005C480` |
| `.bss` | `0x8005C480`-`0x80082448` |
| TIM image | `0x800A4CB4`-`0x800EFCC8` (320x480, 16 bpp) |

The TIM image is loaded together with the program, so the executable stores
`.bss` and the gap after it as zeros. splat keeps it as `assets/tail.bin`.

## Contributing

Every function starts as an `INCLUDE_ASM` line in `src/`. To decompile one,
replace that line with C, rebuild and run `make compare`. objdiff
(`make objdiff`, then open the project in objdiff) shows the differences per
function.

Rodata is migrated into the functions that use it: a function's jump tables and
strings live in its own `.s` file, so its C version emits them itself (switch
statements work as usual). Rodata shared by several functions stays behind
`INCLUDE_RODATA`.

`tools/try_match.py draft.c [func ...]` compiles a draft with the project
toolchain and compares each function with the original executable, printing
both side by side when they differ. `CC1`, `CFLAGS` and `MASPSXFLAGS` override
the defaults.

### Toolchain notes

- The compiler was identified by running m2c over every game function and
  building the output with several GCC versions: GCC 2.8.x `-O2` matches 82 of
  342 functions untouched, 2.7.2 matches 49 and 2.91.66 matches 46. GCC 2.8.0
  and 2.8.1 give the same results, and so do ASPSX 2.56 to 2.86.
- Divisions carry no divide-by-zero check, so maspsx runs without
  `--expand-div`.
- The code between `0x8001D070` and `0x8001FBD4` (plus `main` and
  `func_80013758`) reads a few variables through `$gp` (`.sdata`/`.sbss` at
  `0x8005C458`-`0x8005C4C0`). They match with `-G8` in both GCC and maspsx, as
  long as the variable is defined in the same C file. The rest of the game
  needs `-G0`.

### Where to start

- `src/main/game.c` is a single file for now. splat reports likely file
  boundaries from the jump tables in `.rodata` (at `0x884`, `0x9A0`, `0x9BC`,
  `0xA90` and `0xAEC`), which are a good first hint to split it into the
  original source files.
- The PsyQ functions were named from the
  [PsyQ 4.7 signatures](https://github.com/lab313ru/psx_psyq_signatures).
  They can be split into one file per library object in the same way.
- Most of the game lives outside the main executable. The disc's `AAA/DAT`,
  `AAA/PRO` and `AAA/STR` directories are empty in the ISO 9660 listing, so
  the game must find its files by sector. The overlays are not part of the
  build yet.

## Links

Inspired by these projects:
[Digimon World decomp](https://github.com/jype0/dw_decomp),
[Digimon World 2 decomp](https://github.com/Wyrelade/Digimon-World-2-Decomp),
[Digimon Digital Card Battle decomp](https://github.com/juandav/dcb_decomp).
