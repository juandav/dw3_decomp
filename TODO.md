# TODO

Both versions build byte for byte, but most of the game is still assembly:
the USA executable's game code is almost all C, its overlays and stages are
mostly not, and the European version builds little C besides the PsyQ
libraries. The project's focus
now moves to the European version, *Digimon World 2003*, the most complete
release: it has every USA overlay and stage plus 55 stages of its own. The
counts below were taken from the source and from the `us` and `eu` builds at
commit `45827a6`.

## The European version

`make VERSION=eu compare` is OK for `SLES_039.36`, its 21 overlays and its 293
stages. The executable and the overlays are split into the USA version's
files (`tools/split_version.py`), so their asm lands at the USA paths, and
their functions carry the USA names (`tools/match_versions.py --seed`). The
European C is the PsyQ libraries, the executable's game code and data and two
overlay files built from the USA version's C. The stages are still one asm
segment each.

- [x] Pair the European functions with the USA ones
  (`tools/match_versions.py`, which writes `build/eu/version_pairs.txt`):
  910 of the executable's 913 functions, 1,680 of the overlays' 1,689 and
  1,358 of the stages' 1,595 pair with confidence. The USA version's
  functions are 99.9 %, 99.7 % and 98.8 % paired; what is left of the
  European stages is mostly `WSTAG920`-`974`.
- [x] Split the European executable into the USA version's files (`crt0`,
  `inn`, `system`, ..., the PsyQ objects and the data files) and each
  overlay the same way (`STDWTITL` into `stdwtitl`, `stdwtitl_2` and
  `libpress`, `STDGNAME` into `stdgname` and `stdgname_2`), so that the
  report has the USA units.
- [x] Seed `config/eu/symbols.txt` and `config/eu/symbols_<overlay>.txt` with
  the USA names of the paired functions and data: 1,064 of the USA
  version's 1,091 names are in the European files.
- [x] Build the USA files that match unchanged: the 275 PsyQ files,
  `game3_2`, `SOUNDTST` and `STDWTITL`'s `libpress`
  (`tools/version_symbols.py` names what they use).
- [x] 17 PsyQ files (`libsnd_vm_init`, `libspu_s_sav`, `libmcrd_libmcrd`...)
  used a `D_` name of the USA version that the European asm has at another
  address: those data have real names now (`_spu_rev_startaddr`,
  `_spu_RQ`, `PAD_SIO_REGS`, `MCRD_READ_RETRIES`...).
- [x] Build the executable's game code and data for `eu` too, with
  `#if VERSION_EU` blocks where they differ: the language (`LANGUAGE`, set
  by `CNTY_SEL`) picks the text files (`TEXT_FILE()`), the save file name and
  whether the buttons swap; 50 Hz (`NTSC_MODE`) changes the clocks, the
  sound's tick and fades and the video mode; the disc's files are numbered
  differently (`FILE_MENU_SPRITES`, `FILE_FONT`); `GAME` has 8 more bytes of
  flags. Its data is `data_to_c.py`'s output for `asm/eu/` where it differs.
  The European executable's game code is the USA one's 344 of 346 functions.
- [ ] The overlays' files need `#if VERSION_EU` blocks or a copy of their
  own: `SHOCKTST` loads `0xBE` for `0xC5`.
- [ ] 12 USA names are still missing in the European overlays' files, data
  that code which differs reads (`STDWTITL_movies`, `STAGSLCT_entryNames`,
  `SHOCKTST_menuRows`...), and a few European functions have no confident
  pair: 2 in `CARDGAME`, 6 in `FIGHTSTG`, 1 in `STGDGLAB`. The executable
  has them all but `FLAGS_40`, which the European `GAME.flags` has at an odd
  offset, inside `FLAGS_02` (`FLAGS_02 + 0x66`, in `game_state.h`).
- [ ] The stages: 233 of the USA version's 238 are 8 bytes longer in the
  European version, the other 5 more, and their functions only have
  splat's names, so the European ones get none.
  Give each stage the USA version has a C file in both versions, and write
  C for the 55 European stages, `WSTAG920`-`974`.
- [x] `game3_2` is C in the European version, but its unit in the report is
  `game3`'s: it counts now that `game3.c` is built for `eu` too.

## The USA executable

- [ ] 2 game functions left: `spriteDrawerDraw` and `convertText`
  (`graphics.c`).
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

- [ ] 12 of the 563 PsyQ functions are still `INCLUDE_ASM`, in 8 objects
  (`libmcrd_libmcrd` 3 and the rest 2 or fewer), all compiled code; 166
  are still named `func_`. What Sony wrote in assembly (71 functions, 56
  objects) is `.s` sources in `src/main/psyq/`.
- [ ] 9 `INCLUDE_RODATA`: `libgpu_sys` 4, `libcd_bios_1` 3 and
  `libmcrd_libmcrd` 2 (two strings that `MemCardOpen`, still asm, reads).

## Overlays

- [ ] 733 of the overlays' 1,697 functions are C. All C: `CNTY_SEL`,
  `SOUNDTST`. Mostly: `STCRDABM` (27 / 29), `STDGNAME` (29 / 32), `SHOCKTST`
  (15 / 17), `STAGSLCT` (6 / 8), `STDWTITL` (65 / 93), `STITSHOP` (50 / 69),
  `CARDGAME` (203 / 306), `STGMCARD` (36 / 45). Started: `FIELDSTG`
  (108 / 222), `STGDGLAB` (44 / 70), `STSTATUS` (42 / 123), `STPLNMET`
  (24 / 53), `STCRDSHP` (16 / 45), `STFGTREP` (13 / 36), `WFIGHTTS` (6 / 14),
  `STCRDDEK` (6 / 55), `WFIGHTMN` (4 / 42), `STGTRAIN` (3 / 94), `FIGHTSTG`
  (2 / 310).
- [ ] Find out what `FIGHTSTG` and `STGTRAIN` run, and say it in their
  header and the README. Check `STFGTREP`'s guess (the report after a
  battle) against its texts. Check `STGDGLAB`'s guess (the partners'
  digivolutions) against its strings.
  `STAGSLCT`'s menu of every scene of the game may help.
- [ ] Name the overlays' functions: only `CNTY_SEL`, `SHOCKTST`,
  `SOUNDTST`, `STAGSLCT`, `STCRDABM` and `STDWTITL` have names (and
  `STITSHOP`, `STSTATUS`, `STGDGLAB`, `STCRDSHP`, `STFGTREP`, `STGMCARD`,
  `STPLNMET`, `WFIGHTMN` and `WFIGHTTS` their helpers and tasks); the other
  overlays' symbol files are empty or hold a few `D_` entries, so `FIELDSTG`
  and `STDGNAME`, much of which is C, are still `func_`.
- [ ] Overlay data: 37 % of it is C. `INCLUDE_RODATA` is left in `SHOCKTST`
  (7), `FIGHTSTG` (5), `SOUNDTST` (4), `STAGSLCT` (3), `FIELDSTG` (2),
  `CARDGAME` and `WFIGHTTS` (1 each).

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
- [x] The versions share their names, and `tools/check_names.py` fails the CI
  on a European name that isn't the USA one; `tools/rename.py` renames in
  every version's symbol files, `src/` and `include/` at once.

## Tooling and docs

- [ ] The README's status and overlay tables are written by hand from
  `make report`; the CI checks the hacks badge and table
  (`tools/hacks.py --check README.md`), but not them.
- [ ] Pull requests from forks only run the `names` job (`check_names.py`
  and `hacks.py`): the builds need the private repository with the original
  files.
- [ ] `objdiff.json` holds one version at a time: the last one `make
  objdiff` was run for.
- [x] Some comments still described the USA version only:
  `tools/stage_yaml.py` spoke of "the 238 stage overlays", and
  `tools/objdiff_generate.py` of `config/main.yaml`.
