# TODO

Both versions build byte for byte, but most of the game is still assembly:
the USA executable's game code is almost all C, its overlays and stages are
mostly not, and the European version has no C at all. The project's focus
now moves to the European version, *Digimon World 2003*, the most complete
release: it has every USA overlay and stage plus 55 stages of its own. The
counts below were taken from the source and from the `us` and `eu` builds at
commit `45827a6`.

## The European version

`make VERSION=eu compare` is OK for `SLES_039.36`, its 21 overlays and its 293
stages, but all of it is splat's disassembly: the executable is one segment
per section (`config/eu/main.yaml`), each overlay its rodata, code and data as
asm, and every stage is marked `asm` in `config/eu/stages.txt`.
`config/eu/symbols.txt` is empty and `eu`'s `C_SRC` is too.

- [ ] Pair the European functions with the USA ones. splat finds the same
  number of functions in 19 of the 21 overlays; it finds 907 in the
  executable against 911 (346 game, 563 PsyQ and 2 start-up), 301 in
  `FIGHTSTG` against 297 (splat's labels; objdiff counts 310 in the USA
  one) and 71 in `STGDGLAB` against 70, and 1,595 in the
  293 stages against 1,374 in the USA version's 238. The pairs say where the
  USA version's files start and end in the European binaries, and which
  functions differ.
- [ ] Split the European executable into the USA version's files: `crt0`,
  `inn`, `system`, `memcard`, `game3`, `game3_2`, `pad`, `text_window`,
  `graphics`, `sound`, the PsyQ objects and the data files, each as an asm
  segment under the USA name, so that the report has the same units.
- [ ] Split each European overlay the same way (`STDWTITL` into `stdwtitl`,
  `stdwtitl_2` and `libpress`, `STDGNAME` into `stdgname` and `stdgname_2`).
- [ ] Seed `config/eu/symbols.txt` and `config/eu/symbols_<overlay>.txt` with
  the USA names of the paired functions and data, so that the two versions
  share their names.
- [ ] Start the European C: build the USA files that match unchanged
  (`C_SRC` in `mk/version/eu.mk`, `c` segments in the configs), then the ones
  that need `#if VERSION_EU` blocks or a copy of their own.
- [ ] Give each stage the USA version has a C file in both versions, and write
  C for the 55 European stages, `WSTAG920`-`974`.
- [ ] The European report has one unit per binary until the split: its
  `main/main` counts PsyQ too, which the USA report leaves out.
- [ ] The European overlay and stage configs still say `gp_value: 0x8005C2F8`,
  the USA executable's `$gp` (`tools/stage_yaml.py` writes it for every
  version); the European one is `0x8005CB50`, as `config/eu/main.yaml` has
  it.
- [ ] `mk/version/eu.mk` still says the overlays are blobs: since
  `45827a6` they are disassembled.

## The USA executable

- [ ] 3 game functions left: `spriteDrawerDraw` and `convertText`
  (`graphics.c`) and `drawTalkBoxArrow` (`text_window.c`).
- [ ] Rodata still behind `INCLUDE_RODATA`: 6 strings and tables in
  `text_window.c` and 2 in `system.c`, which the C could define once their
  users are all C.
- [ ] 9 game functions still have splat's name: `func_80012698`,
  `func_8001350C`, `func_80013590`, `func_80015490`, `func_80015584`,
  `func_80015A34`, `func_80015D90`, `func_8001602C` and `func_80017878`.
- [ ] The executable's data is C in `src/main/data/`, mostly words named by
  address (`game.c` is 7,195 lines): move each table to the module that uses
  it, with its type and a name.
- [ ] `crt0` (`2MBYTE.OBJ`) is still splat's disassembly in
  `asm/<version>/main/crt0.s`: make it a hand-written `.s` source under
  `src/main/`.

## PsyQ

- [ ] 88 of the 563 PsyQ functions are still `INCLUDE_ASM`, in 67 objects
  (`libcard_patch` 7, `libmcrd_libmcrd` 4 and the rest 3 or fewer); 166
  are still named `func_`. Check which of them were written in assembly,
  not compiled, and make those `.s` sources.
- [ ] 14 `INCLUDE_RODATA`: `libmcrd_libmcrd` 6, `libgpu_sys` 4,
  `libcd_bios_1` 3, `libspu_spu` 1.

## Overlays

- [ ] 295 of the overlays' 1,697 functions are C. All C: `CNTY_SEL`,
  `SOUNDTST`. Mostly: `STCRDABM` (27 / 29), `STDGNAME` (29 / 32), `SHOCKTST`
  (15 / 17), `STAGSLCT` (6 / 8), `STDWTITL` (65 / 93). Started: `FIELDSTG`
  (108 / 222), `STCRDDEK` (6 / 55), `STGTRAIN` (3 / 94), `FIGHTSTG`
  (2 / 310). Not started: `CARDGAME` (306), `STSTATUS` (123), `STGDGLAB` (70),
  `STITSHOP` (69), `STPLNMET` (53), `STCRDSHP` (45), `STGMCARD` (45),
  `WFIGHTMN` (42), `STFGTREP` (36), `WFIGHTTS` (14).
- [ ] Find out what `CARDGAME`, `FIGHTSTG`, `STCRDSHP`, `STFGTREP`,
  `STGDGLAB`, `STGMCARD`, `STGTRAIN`, `STITSHOP`, `STPLNMET`, `STSTATUS`,
  `WFIGHTMN` and `WFIGHTTS` run, and say it in their header and the README.
  `STAGSLCT`'s menu of every scene of the game may help.
- [ ] Name the overlays' functions: only `CNTY_SEL`, `SHOCKTST`,
  `SOUNDTST`, `STAGSLCT`, `STCRDABM` and `STDWTITL` have names; the other
  overlays' symbol files are empty or hold a few `D_` entries, so `FIELDSTG`
  and `STDGNAME`, much of which is C, are still `func_`.
- [ ] Overlay data: 37 % of it is C. `INCLUDE_RODATA` is left in `SHOCKTST`
  (7), `FIGHTSTG` (5), `SOUNDTST` (4), `STAGSLCT` (3), `CARDGAME` and
  `FIELDSTG` (2 each) and `WFIGHTTS` (1).

## Stages

- [ ] 815 of the 1,374 functions of the USA stages are C, and 64 of the 238
  stages are all C; 559 `INCLUDE_ASM` are left.
- [ ] None of the stages' data is C yet (0 of 815,984 bytes in the report).
- [ ] The stages share many functions, built from the same source, but each
  stage's file has its own copy: the 815 C functions have 641 different
  bodies (addresses included). A shared include for the common ones, and
  names for them, would say so.
- [ ] Every stage function still has splat's name. A stage's own symbol file,
  `config/<version>/stages/<stage>.txt`, is read by the Makefile and
  `tools/stage_yaml.py`, but none exists yet.
- [ ] Find what each stage is (the map or event it runs).

## Names and types

- [ ] 405 `unk` struct fields in the headers, and 2,008 different `D_`
  symbols referenced from `src/` and `include/`.
- [ ] The versions share their names, and `tools/check_names.py` fails the CI
  on a European name that isn't the USA one; but `config/eu/symbols.txt` is
  empty, so it checks nothing yet. A tool that renames in every version's
  symbol files, `src/` and `include/` at once would keep them in step.

## Tooling and docs

- [ ] The README's status and overlay tables are written by hand from
  `make report`; the CI checks the hacks badge and table
  (`tools/hacks.py --check README.md`), but not them.
- [ ] Pull requests from forks only run the `names` job (`check_names.py`
  and `hacks.py`): the builds need the private repository with the original
  files.
- [ ] `objdiff.json` holds one version at a time: the last one `make
  objdiff` was run for.
- [ ] Some comments still describe the USA version only:
  `tools/stage_yaml.py` speaks of "the 238 stage overlays", and
  `tools/objdiff_generate.py` of `config/main.yaml`.
