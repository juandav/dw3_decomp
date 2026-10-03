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
European C is the PsyQ libraries, the executable's game code and data, the
overlay functions the USA version has in C and every stage's C: the 238 USA
stages are built from the USA version's C, the 55 European ones from their
own.

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
  The European executable's game code is the USA one's 346 functions.
- [x] Build every overlay's USA C for the European version too, functions
  and data, with `#if VERSION_US`/`#elif VERSION_EU` where the discs
  differ: file numbers (`SHOCKTST` loads `0xBE` for `0xC5`), the language
  tables of `STDWTITL`, `STCRDDEK` and `CNTY_SEL`, data of other lengths,
  and `FIGHTSTG`'s 4 functions of its own.
- [ ] 12 USA names are still missing in the European overlays' files, data
  that code which differs reads (`STDWTITL_movies`, `STAGSLCT_entryNames`,
  `SHOCKTST_menuRows`...), and a few European functions have no confident
  pair: 2 in `CARDGAME`, 1 in `STGDGLAB`; `FIGHTSTG`'s other 4
  (`func_8008F5D4`, `func_800A15A8`, `func_800A1FE0`, `func_800A246C`) are
  European only. The executable has them all but `FLAGS_40`, which the
  European `GAME.flags` has at an odd offset, inside `FLAGS_02`
  (`FLAGS_02 + 0x66`, in `game_state.h`).
- [x] The stages: 233 of the USA version's 238 are 8 bytes longer in the
  European version because each one's setup function adds the language
  (`LANGUAGE`, which `CNTY_SEL` sets) to the text file it loads; the
  other 5 also have longer functions (`WSTAG210`, `220`, `270`, `280`) or
  one more (`WSTAG780`). Each USA stage builds from its C file in both
  versions, its functions with the USA names
  (`config/eu/stages/<stage>.txt`): 1,297 of the European stages' 1,590
  functions are C, and 293 `INCLUDE_ASM` are left: every stage's setup
  function.
- [ ] The setup functions (the one that fills `D_800990B4` and loads the
  stage's text file) don't match in the European version from the USA C:
  the language load (`LANGUAGE`) sits after the store to `0x14`, before
  the `0x1C` and `0x44` ones, while the two-instruction constants and the
  call's arguments are loaded at the very top. The scheduling it needs is
  known: the stores up to `0x1C` and the one to `0x44` must come before
  the others, as if they could alias, while the constants move freely
  (`DEBUG_LOG` stops both). A store to `0x44` through a pointer GCC's
  alias analysis can't follow gives exactly that, but costs a second base
  register; making every store `volatile` gives it too, but then the last
  store can't fill the call's delay slot. No natural C found yet: no order
  of the statements, `DEBUG_LOG` placement or replacement, local, inline
  function, loop, cast or compiler flag tried gives it (the closest is 33
  instructions off, in `WSTAG310`). Once found, it applies to all 293.
  What a second attempt ruled out or learned (on `WSTAG310`):
  - The dependencies needed are exactly those of GCC 2.8.1's
    `flush_pending_lists` (`sched.c`) at the `0x44` store: after every
    memory access before it, before every one after it, with registers
    free. The scheduler only flushes at a call, a volatile `asm`, a loop
    note (these two also tie the registers, as `DEBUG_LOG` does) or when
    more than 32 memory accesses are pending in the block, and this
    function has 6 before that store.
  - The alias analysis only sees a conflict between two stores to
    `D_800990B4` when their base registers are different pseudos, one of
    them with no known value (set twice, or without a `REG_EQUAL` note).
    The `LANGUAGE` load can't be the anchor either: its address is a
    `lo_sum` of the symbol, which never conflicts with the stores.
  - CSE folds into the one base every other way of reaching the struct:
    a pointer local (for some of the stores or all of them, declared at
    the top or in a block), a pointer set twice, a `static inline` setter
    (with the struct, the value or the file as its argument) or getter.
  - Without `DEBUG_LOG`, every statement order gives 36 instructions off,
    with the language load after the last store. With `DEBUG_LOG`
    anywhere (first, after `0x14`, `0x1C` or `0x44`, or twice) it is
    41-50: the constants can't rise above it.
  - `volatile` on every store but `0x20` is 42 off (`0x20` moves); on all
    of them, the order and registers match but the delay slot stays
    empty, since GCC wraps each volatile access in `.set volatile`.
  - No flag changes it: `-fforce-addr`, `-fforce-mem`, `-fvolatile-global`,
    `-fno-rerun-cse-after-loop`, `-fno-cse-follow-jumps`,
    `-fno-strength-reduce`, `-fcaller-saves` and the rest give 36,
    `-fvolatile` 43, and `-fno-schedule-insns` 65. Neither does GCC 2.8.0
    or the SN 2.8.1.
- [x] The 8 functions that read `GAME` fields 8 bytes later in the European
  version (`countdown`, `unk26DC`, `unk26E8`) are C in both: `WSTAG745`/
  `746` `func_800A4CA4`, `WSTAG795` `func_800A50F8`/`func_800A5240`,
  `WSTAG800` `func_800A5404`/`func_800A554C`, `WSTAG810` `func_800A58F0`/
  `func_800A5954`, with `GAME.countdown` (`u8 [4]`, `0x26CC`) and the
  `StageInfo` fields `0x50`-`0x60`.
- [ ] The setup functions of 100 USA stages are C in the USA version only
  (`#if VERSION_US`, `INCLUDE_ASM` in the European one).
- [x] The 55 European stages, `WSTAG920`-`974`, have C files, their data
  too: every function but their setup is C.
- [x] Where the versions' code differs only in numbers, `include/stage.h`
  and the stages' own defines give them: the file numbers (`SPRITES`,
  `MENU_TEXT`...), `MENU_SPRITES` and `TEXT_ENTRY` (the European version
  adds the language to the text file).
- [x] `game3_2` is C in the European version, but its unit in the report is
  `game3`'s: it counts now that `game3.c` is built for `eu` too.

## The USA executable

- [x] The game code is all C: `spriteDrawerDraw` and `convertText`
  (`graphics.c`) were the last.
- [ ] Rodata still behind `INCLUDE_RODATA`: `OVERLAY_ADDRESS` and
  `SUB_OVERLAY_ADDRESS` in `system.c`. The original has the two pointers in
  `.rodata` and reads them with `lui`/`lw`, but `system.c` is built with
  `-G8`, so GCC puts a 4-byte `const` it defines in `.sdata` and reads it
  through `$gp`. `text_window.c`'s strings and tables are C.
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
  objects) is `.s` sources in `src/main/psyq/`. Closest attempts:
  `func_80021FC0` (`libpad_pdtapres`, the byte to send at the pad's
  position: `cmd`, or `0x42` when it is 0, then the actuator table or the
  data) has the right shape at 32 diffs, but our cross-jumping makes the
  `0x4D` case jump into the default case's `return p->data[i]`, where the
  original lets both jump to case 0's final `lbu`. `MemCardOpen` (a retry
  loop around `MemCardAccept`, with the error path between the loop and
  the success path) is at 64 diffs: ours keeps the constant 3 in a register
  in the loop, the original `&D_80082068`, which it stores through.
- [ ] 9 `INCLUDE_RODATA`: `libgpu_sys` 4, `libcd_bios_1` 3 and
  `libmcrd_libmcrd` 2 (two strings that `MemCardOpen`, still asm, reads).

## Overlays

- [ ] 1,003 of the overlays' 1,697 functions are C. All C: `CNTY_SEL`,
  `SOUNDTST`. Mostly: `STCRDABM` (27 / 29), `STDGNAME` (29 / 32), `SHOCKTST`
  (15 / 17), `STAGSLCT` (6 / 8), `FIELDSTG` (190 / 222), `STDWTITL`
  (65 / 93), `STITSHOP` (50 / 69), `CARDGAME` (303 / 306), `STGMCARD`
  (44 / 45). Started: `STGDGLAB` (44 / 70), `STSTATUS` (42 / 123),
  `STPLNMET` (24 / 53), `STCRDSHP` (16 / 45), `STFGTREP` (26 / 36),
  `WFIGHTTS` (6 / 14), `STCRDDEK` (6 / 55), `WFIGHTMN` (4 / 42), `STGTRAIN`
  (3 / 94), `FIGHTSTG` (69 / 310).
- [ ] Find out what `STGTRAIN` runs, and say it in its header and the
  README. Check `STFGTREP`'s guess (the report after a
  battle) against its texts. Check `STGDGLAB`'s guess (the partners'
  digivolutions) against its strings.
  `STAGSLCT`'s menu of every scene of the game may help.
- [ ] Name the overlays' functions: only `CNTY_SEL`, `SHOCKTST`,
  `SOUNDTST`, `STAGSLCT`, `STCRDABM` and `STDWTITL` have names (and
  `STITSHOP`, `STSTATUS`, `STGDGLAB`, `STCRDSHP`, `STFGTREP`, `STGMCARD`,
  `STPLNMET`, `WFIGHTMN` and `WFIGHTTS` their helpers and tasks); the other
  overlays' symbol files are empty or hold a few `D_` entries, so `FIELDSTG`
  and `STDGNAME`, much of which is C, are still `func_`.
- [ ] Overlay data: 78 % of it is C in both versions; the `.data` of every
  overlay is C. objdiff counts a section only when all of it
  matches, so the `.rodata` of the overlays with functions still in asm
  doesn't count yet. `INCLUDE_RODATA` is left in `SHOCKTST` (7),
  `FIGHTSTG` (4), `SOUNDTST` (4), `STAGSLCT` (3), `FIELDSTG` and
  `WFIGHTTS` (1 each). The European `CNTY_SEL` `.data`
  stays at 98.95 % in the report: the file ends 3 bytes into its last
  word, which splat's object leaves out.

## Stages

- [ ] 1,231 of the 1,369 functions of the USA stages are C, and 100 of the
  238 stages are all C; 138 `INCLUDE_ASM` are left, all setup functions
  (the form of the other 100 doesn't fit them). 50 are plain setups like
  the matched ones, 39 of them with a one-instruction constant at `0x2C`:
  there the first call's arguments are loaded first after `DEBUG_LOG`,
  above that constant, which the C form can't do (`WSTAG235` is 4
  instructions off with the `0x34` store moved up). 37 more check
  `GAME_PROGRESS` after the calls, and 51 also copy `unk38` (34 of them
  with the `GAME_PROGRESS` check).
- [x] A stage's jump tables come from its C (`c-rodata` in `stages.txt`);
  `head-word` keeps a first word before them in asm, as GCC would align a
  C constant there (`WSTAG924`).
- [x] The stages' data is C, in both versions: 808,672 of the 815,984 bytes
  of the USA stages in the report, as splat's words (`tools/data_to_c.py`)
  at the end of each stage's C file, with `#if VERSION_US` / `VERSION_EU`
  rows for the words that differ (file numbers, mostly) or that one version
  hasn't.
- [ ] `WSTAG331`'s data is still asm (`asm-data` in `stages.txt`): it differs
  throughout between the versions.
- [ ] Most of the stages' data is still splat's words: the point paths,
  animations and tile tables the C reads have types (`include/stage.h`),
  give the rest real ones (and names) as the code that reads it is
  understood.
- [ ] The stages share many functions, built from the same source, but each
  stage's file has its own copy. A shared include for the common ones, and
  names for them, would say so.
- [ ] Every stage function still has splat's name. A stage's own symbol file,
  `config/<version>/stages/<stage>.txt`, is read by the Makefile and
  `tools/stage_yaml.py`; the European ones give the USA stages' functions
  their USA names, the USA version has none yet.
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
