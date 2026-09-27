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
| Compiler | Game: GCC 2.8.1 (`-O2 -G0`); PsyQ: GCC 2.7.2 (`-O2`); ASPSX emulated with [maspsx](https://github.com/mkst/maspsx) |
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

Download tools (GCC 2.8.1 and 2.7.2 for PSX, objdiff-cli and mkpsxiso):
```
tools/dl_deps.sh
```

## Build

```
# Update submodules
git submodule update --init --recursive

# Extract the disc (the executable and the AAA/ directories, which dumpsxiso
# doesn't see: only the ISO9660 path table reaches them)
python3 tools/extract_disc.py "/path/to/Digimon World 3 (USA).bin" disks/us

# Disassemble the original executable and overlays
make regenerate

# (Optional) Create file local.mk to override defaults
TOOLCHAIN := /path/to/mipsel-linux-gnu-

# Build the executable and the overlays
make -j$(nproc)

# Compare them with the originals
make compare

# Generate the objdiff config and the progress report
make objdiff
make report
```

`make compare` must print OK for `build/SLUS_014.36` and every overlay. A
function only counts as decompiled once all of them still match.

The progress report counts the game's code: the executable's and the
overlays'. The PsyQ SDK linked into the executable is Sony's code, so like
other PSX decomps it is built and compared but not counted.

## Layout

| Path | Contents |
|---|---|
| `config/main.yaml` | splat config for `SLUS_014.36` |
| `config/symbols.txt` | known symbols |
| `src/main/game.c` | game code, `0x80010F80`-`0x8001D070` |
| `src/main/gfx.c` | graphics and object code, `0x8001D070`-`0x8001FC68` (built with `-G8`) |
| `src/main/sound.c` | sound code, `0x8001FC68`-`0x80020998` |
| `include/game.h` | types and declarations shared by the game files |
| `src/main/psyq/` | PsyQ libraries, one file per library object, `0x80020998`-`0x8003E9D8` |
| `include/psyq.h` | declarations shared by the PsyQ files |
| `asm/main/crt0.s` | PsyQ startup (`2MBYTE.OBJ`), `0x80010EBC`-`0x80010F80` |
| `config/<overlay>.yaml`, `src/<overlay>/` | the game's overlays (`AAA/PRO/*.PRO`), loaded at `0x80082448`; `WFIGHTMN` and `WFIGHTTS` load on top of `CARDGAME`, at `0x800A4CA4` |
| `config/overlays.sha1` | checksums of the overlays |
| `config/stages.txt`, `src/stages/` | the 238 stage overlays (`AAA/PRO/WSTAG###.PRO`), loaded at `0x800A4CA4` on top of `FIELDSTG`; `tools/stage_yaml.py` makes their splat configs |
| `config/stages.sha1` | checksums of the stage overlays |
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
- `gfx.c` reads its small variables through `$gp`, so it is built with `-G8`
  in both GCC and maspsx (see `SDATA_LIMIT` in the Makefile). Those variables
  are declared `static` in `gfx.c`; maspsx emits them as common symbols that
  resolve to the definitions in the data asm. The rest of the game uses
  `-G0`. `main` and `func_80013758` also use `$gp` and will need the same
  treatment once their files are split out.
- The PsyQ libraries were built with GCC 2.7.2, whose ASPSX moved the
  instruction before each `j $31` into its delay slot unless it was a load or
  that would leave a load of `$31` right before the jump. maspsx does not do
  this, so `tools/aspsx_reorder.py` post-processes the PsyQ files.
- `src/main/psyq/` is cut at the object boundaries found from the signatures
  and from the padding between objects: ASPSX pads the `.text` of every
  object to a multiple of 16 bytes with `nop`s. Every file ends with
  `OBJECT_END()` (from `include_asm.h`), which reproduces that padding when
  the last function is in C.
- The PsyQ files include the PsyQ 4.7 headers from
  [psyq_headers](https://github.com/jype0/psyq_headers). `libgte.h` names
  some parameters `$2`, hence `-fdollars-in-identifiers`. Both code bases use
  signed `char` (`-fsigned-char`).
- Most global function pointers live in tables (`D_8004AD90` holds `free`,
  `malloc` and `bzero`, for example) and must be called through a struct.
  GCC 2.8 assumes a struct field and a scalar global never alias, so with a
  scalar `extern` it moves stores to struct fields past the load of the
  function pointer.

### Where to start

- `src/main/game.c` still holds most of the game. splat reports likely file
  boundaries from the jump tables in `.rodata` (at `0x884`, `0x9A0`, `0x9BC`,
  `0xA90` and `0xAEC`), which are a good first hint to split it further.
- The PsyQ functions were named from the
  [PsyQ 4.7 signatures](https://github.com/lab313ru/psx_psyq_signatures).
- Most of the game lives outside the main executable, in the overlays. The
  disc's `AAA/DAT`, `AAA/PRO` and `AAA/STR` directories are only reachable
  through the ISO 9660 path table, which is why `tools/extract_disc.py` is
  needed. `SMDLDATA`, `SDIGIEDT`, `SFSTDATA` and `WSTAG260` hold no code and
  aren't built.

## Links

Inspired by these projects:
[Digimon World decomp](https://github.com/jype0/dw_decomp),
[Digimon World 2 decomp](https://github.com/Wyrelade/Digimon-World-2-Decomp),
[Digimon Digital Card Battle decomp](https://github.com/juandav/dcb_decomp).
