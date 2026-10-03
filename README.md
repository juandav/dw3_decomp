# Digimon World 3 decomp

| Version | Code | Data | Functions |
|---|---|---|---|
| 🇪🇺 Europe (`SLES_039.36`) | [![Code](https://decomp.dev/juandav/dw3_decomp.svg?mode=shield&measure=code&version=SLES_039.36&label=Code)](https://decomp.dev/juandav/dw3_decomp/SLES_039.36) | [![Data](https://decomp.dev/juandav/dw3_decomp.svg?mode=shield&measure=data&version=SLES_039.36&label=Data)](https://decomp.dev/juandav/dw3_decomp/SLES_039.36) | [![Functions](https://decomp.dev/juandav/dw3_decomp.svg?mode=shield&measure=functions&version=SLES_039.36&label=Functions)](https://decomp.dev/juandav/dw3_decomp/SLES_039.36) |
| 🇺🇸 USA (`SLUS_014.36`) | [![Code](https://decomp.dev/juandav/dw3_decomp.svg?mode=shield&measure=code&version=SLUS_014.36&label=Code)](https://decomp.dev/juandav/dw3_decomp/SLUS_014.36) | [![Data](https://decomp.dev/juandav/dw3_decomp.svg?mode=shield&measure=data&version=SLUS_014.36&label=Data)](https://decomp.dev/juandav/dw3_decomp/SLUS_014.36) | [![Functions](https://decomp.dev/juandav/dw3_decomp.svg?mode=shield&measure=functions&version=SLUS_014.36&label=Functions)](https://decomp.dev/juandav/dw3_decomp/SLUS_014.36) |

[![Executable](https://decomp.dev/juandav/dw3_decomp.svg?mode=shield&measure=code&version=SLUS_014.36&category=game&label=USA%20executable)](https://decomp.dev/juandav/dw3_decomp/SLUS_014.36?category=game)
[![Stages](https://decomp.dev/juandav/dw3_decomp.svg?mode=shield&measure=code&version=SLUS_014.36&category=stages&label=USA%20stages)](https://decomp.dev/juandav/dw3_decomp/SLUS_014.36?category=stages)

[![Build](https://github.com/juandav/dw3_decomp/actions/workflows/build.yaml/badge.svg)](https://github.com/juandav/dw3_decomp/actions/workflows/build.yaml)
[![Platform](https://img.shields.io/badge/platform-PlayStation-003791)](#the-games-binaries)
[![Versions](https://img.shields.io/badge/versions-USA%20%7C%20Europe-blue)](#how-the-versions-are-organised)
[![Compiler](https://img.shields.io/badge/compiler-GCC%202.8.1%20%7C%202.7.2-orange)](#toolchain)
[![Fake matches | hacks](https://img.shields.io/badge/fake%20matches%20%7C%20hacks-0%20%7C%20134-yellow)](#fake-matches-and-hacks)
[![License](https://img.shields.io/github/license/juandav/dw3_decomp)](LICENSE)

A work in progress matching decompilation of **Digimon World 3** for the
PlayStation: C source that compiles back into byte-identical copies of the
game's executable, its overlays and its stages. The USA release, *Digimon
World 3*, and the European one, *Digimon World 2003*, both build from this
source tree and match byte for byte. The USA release is the one being
decompiled; the European one, the most complete release, is where the work
is heading next: it is split into the USA release's files and carries its
names, and builds the PsyQ libraries, the executable's game code and data,
the overlay functions the USA version has in C and the stages from the same
C, but is splat's disassembly otherwise.

This repository does not contain any game data. You need your own copy of the
game to build it.

[![Progress map](https://decomp.dev/juandav/dw3_decomp.png)](https://decomp.dev/juandav/dw3_decomp)

<sub>Each rectangle is a unit, sized by its code; green means it matches.
Click it for the details on decomp.dev.</sub>

## Status

Measured with `make report` on both versions; the badges above are always
current:

| Part | Version | Functions in C | Code | Data |
|---|---|---|---|---|
| Executable, game code | Europe | 346 / 346 | 100.00 % | 100.00 % |
| | USA | 346 / 346 | 100.00 % | 100.00 % |
| The 21 overlays | Europe | 1,629 / 1,702 | 90.49 % | 94.96 % |
| | USA | 1,624 / 1,697 | 90.44 % | 95.08 % |
| The stages (293 and 238) | Europe | 1,590 / 1,590 | 100.00 % | 100.00 % |
| | USA | 1,369 / 1,369 | 100.00 % | 100.00 % |
| **Total** | **Europe** | **3,565 / 3,638** | **93.50 %** | **99.40 %** |
| | **USA** | **3,339 / 3,412** | **93.21 %** | **99.34 %** |

- The executable's game code is all C, and its rodata. Its data is C too,
  in `src/main/data/`, until it moves next to the code that uses it.
- The PsyQ 4.7 libraries linked into the executable are decompiled too, one
  file per library object: 485 of their 563 functions are C, and the 71 Sony
  wrote in assembly are `.s` sources. They are Sony's
  code, not the game's, so like other PSX decomps they are built and compared
  but left out of the progress.
- `CNTY_SEL`, `SOUNDTST`, `STPLNMET`, `STDGNAME`, `STFGTREP` and `STCRDABM`
  are all C, `CARDGAME` and `STSTATUS` all but one function, and `STCRDDEK`, `STDWTITL`,
  `SHOCKTST`, `STGTRAIN`, `FIELDSTG` and `FIGHTSTG` mostly. The
  other large overlays are still mostly assembly.
- The stages are all C, the 238 USA ones and the 55 of the European version
  alone. Many stages share functions built from the same source, so one
  match often repeats across stages. The stages' data is
  C too, as splat's words, at the end of each stage's C file.
- The European version, the default one and the one decomp.dev shows first,
  is split into the USA version's files, with the USA names, and builds the
  275 PsyQ files, the executable's game code and data (the same 346
  functions as the USA version), the overlay functions the USA version has
  in C, the 238 stages the USA version has from their C files (1,370
  functions and their data), and the 220 functions and the data of its 55
  own stages. The
  rest of its executable and overlays is splat's disassembly, so its report
  counts it as still to do.

Progress is measured by [objdiff](https://github.com/encounter/objdiff), with
one unit per C file, and tracked on
[decomp.dev](https://decomp.dev/juandav/dw3_decomp).

### Fake matches and hacks

The matched C is meant to read as natural C, but some spots only match
through a form that natural C wouldn't take for granted. Each one carries a
comment that says so, in one of three standard forms
([CONTRIBUTING.md](CONTRIBUTING.md#matching) has the rules), and the badge
above counts them: fake matches, then the other two kinds together.

| Kind | Count | Marker |
|---|---|---|
| Fake matches | 0 | a comment that starts with `/* fake match:` and says what is forced and why |
| Unused frame locals | 7 | `/* unused, but it is in the original stack frame */` |
| Form-dependent matches | 127 | a comment that says the `match depends on` the form |
| Functions still in assembly | 65 | `INCLUDE_ASM` |

- A fake match is the last resort: a form forced only for the code it makes,
  such as an empty `do {} while (0)` that ends a CSE block or a variable
  that exists only to shape the code. There are none so far.
- An unused frame local is a local that the code never touches, kept because
  the original's stack frame has room for it: without it, the frame is
  smaller than the original's. Two are in PsyQ objects (`libgs_gs_107`,
  `libgs_gs_131`), one in the game's `drawTalkBoxArrow`, one in STSTATUS's
  `func_8008CC5C` and three in WFIGHTTS.
- A form-dependent match is C that matches in one of several equivalent
  forms only: an extra block, an `if` without braces, a copy of a variable, a
  type, or one version's own form of a loop. The hundred and twenty-seven so far are a copy
  of a variable in `drawTalkBoxArrow`, an unsigned compare in STGMCARD's
  `func_80082E28`, a variable that holds two values in STCRDDEK's
  `STCRDDEK_drawDeckCards`, a counter set before a call in
  `STCRDDEK_drawEditor`, a `u32` copy of a character in the keyboards of
  STCRDDEK and STDGNAME (`STCRDDEK_updateKeyboard`, `STDGNAME_updateKeyboard`),
  a `* 4` written as a statement of its own in FIELDSTG's `func_80091BC0`,
  variables local to a case or a block in its `func_80086E64` and
  `func_80091D3C`, an empty case in its `func_800870D4`, two variables for one
  character and an `s16` in its `func_80084654`, calls in an `if`/`else`
  and a `case 0` next to `default` in its `func_80084D0C`, the button's shift and mask as two statements in its `func_8008D710`, a gauge cell read and shifted as two statements in its `func_8008C59C`, an `s16` shadow offset in its `func_8008E7E0`, a distance written twice in its `func_8008B450`, a loop with both of its tests at its top and steps added as a choice in its `func_8008F184`, the registry held in a variable in its `func_8008D4C4`, a counter for each loop in its `func_80085650`, the start position set with a `(Vec2){x, y}` constructor in its `func_80091124`, a -1 held in a variable in STGTRAIN's `func_800874A0`,
  stats read as `*(totals.stats + i)` in its `func_80083ADC`, `s16` copies
  of two stats in its `func_80085E30`, a counter that
  holds an icon too in its `func_800878C0`, a frame pointer that holds the
  animation first in its `func_800828E8`, the same `u32` copy in STPLNMET's
  `STPLNMET_updateKeyboard`, twenty-six spots in STSTATUS and one in STCRDSHP (a
  copy, a cast, a temporary, a pointer, a pointer sum, `for` initializers, a
  variable of its own for a loop or a case, a statement written in both
  branches, a list indexed rather than walked, the order of a sum's terms, a
  test of another field or two calls in place of a conditional argument), a `cards++` written in the `for`
  in STCRDSHP's `STCRDSHP_createGrid` and `STCRDSHP_drawCards` (which also
  writes its digits' x as `dx + 0x27 + x`), five spots in STGDGLAB and three
  in STITSHOP (loops with counters of their own, a reused variable, an
  index from a later member, range tests written out, a function of its own
  or a copy), six spots in STFGTREP and eleven
  in WFIGHTMN (a variable, a case or a statement of its own, a pointer sum,
  a statement written in both branches, a counter set before a call, a
  variable reused, a pointer, an offset from a pointer or a `while (1)`),
  twenty-seven spots in FIGHTSTG (cases that do nothing, a case next to
  `default`, a variable reused, shared by cases or of its own, a counter set
  in a loop's init, an index from a later member, a pointer sum, pointers and
  blocks of their own, a task taken as `void *`, a value read first, a `goto`
  into a branch, an `if`/`else`, an order of stores, a `* 32` for a shift, an
  early exit written as a `do`-`while (0)` with `break`s as the stages' event
  code writes it, a choice written in both branches or a `?:`), eleven spots
  in CARDGAME (a loop or state variable of its
  own, an empty case, or a statement written twice), a reset written in both
  branches in SHOCKTST's `SHOCKTST_playAllPatterns`, a variable that keeps
  the old top too in STAGSLCT's `STAGSLCT_updateStageSelect`, three in PsyQ's
  libpad (`func_80021FC0`'s variables and switch, and in `func_8002468C`
  a copy of its argument, a `return` through a variable and an interrupt
  register reached as a structure member), the do-while of
  `COUNTDOWN_BORROW`, the statement macro of the timed stages' countdown,
  and the start position that every stage's setup function sets as a
  `(Vec2){x, y}` constructor (both in `include/stage.h`).
- The functions still in assembly are not in the badge: they are the work
  left, in the game and in PsyQ.

`tools/hacks.py --list` lists every one with its file, line and function, and
also what is assembly without being a hack: the rodata still behind
`INCLUDE_RODATA`, data written as a top-level `__asm__`, and the macros that
wrap the inline asm C can't say. The CI fails on what the source must never
have: `NON_MATCHING` code, `#if 0` blocks, and inline asm in place of C.
`tools/hacks.py --check README.md` checks that the badge and the table above
are up to date.

## The game's binaries

The executable, `SLUS_014.36` in the USA release, holds the engine and the
PsyQ libraries. The rest of the game is in overlays, `AAA/PRO/*.PRO` on the
disc, which load right after the executable's `.bss`. Every engine module is a
global struct holding its state and a table of methods (`GFX`, `HEAP`,
`FILE_CACHE`, `PAD`, `SOUND`, `GAME`...), and every game object is a task
(`createTask`, `include/dw3/task.h`); the overlays reach the engine through
those tables. Each overlay has its own splat config, source folder and symbol
prefix (`CNTY_SEL_`, `STDWTITL_`...):

| Overlay | Loads at (us) | Functions in C (us) | What it runs |
|---|---|---|---|
| `CARDGAME` | `0x80082448` | 305 / 306 | the card battle (mode `0x700`): the decks, the cards in play and the battle screen |
| `CNTY_SEL` | `0x80082448` | 26 / 26 | the country select screen |
| `FIELDSTG` | `0x80082448` | 214 / 222 | the field mode, where the player walks around the map; the stages load on top of it |
| `FIGHTSTG` | `0x80082448` | 263 / 310 | the battle: the fight stage and its lights, the fighters' models, faces and cameras, the battle camera and windows, the queue of battle events and the stat, hit and status checks |
| `SHOCKTST` | `0x80082448` | 16 / 17 | the debug vibration test |
| `SOUNDTST` | `0x80082448` | 8 / 8 | the debug sound test |
| `STAGSLCT` | `0x80082448` | 7 / 8 | the debug stage select, a menu of every scene of the game |
| `STCRDABM` | `0x80082448` | 29 / 29 | the card album |
| `STCRDDEK` | `0x80082448` | 54 / 55 | the decks, which it names with the on-screen keyboard (`include/name_entry.h`) |
| `STCRDSHP` | `0x80082448` | 43 / 45 | the card packs (mode 0x1300): opening a pack uses it up and draws six cards, one from each slot's list in `STCRDSHP_packs` |
| `STDGNAME` | `0x80082448` | 32 / 32 | a name entry screen, a keyboard of character pages |
| `STDWTITL` | `0x80082448` | 91 / 93 | the title screen, the opening movies and a notice screen |
| `STFGTREP` | `0x80082448` | 36 / 36 | the report after a battle (mode 0x1400), which `WFIGHTMN` requests: the partners that went up a level |
| `STGDGLAB` | `0x80082448` | 69 / 70 | the partners' digivolutions, it seems: a menu of three screens that checks the requirements of `STGDGLAB_tables` against a partner's entries and sets its three slots |
| `STGMCARD` | `0x80082448` | 45 / 45 | the memory card screen (mode 0xC00): the saves of a card, their details, and saving and loading |
| `STGTRAIN` | `0x80082448` | 89 / 94 | the gyms: a partner trains a stat, gaining some and losing others, with its sprites and the result windows |
| `STITSHOP` | `0x80082448` | 68 / 69 | the item shop, where the player buys and sells items and equips what was bought on a partner |
| `STPLNMET` | `0x80082448` | 53 / 53 | the player's name entry (mode 0x500), with a copy of `STDGNAME`'s keyboard |
| `STSTATUS` | `0x80082448` | 122 / 123 | the screens the field menu opens (`STSTATUS_screens`), such as the item list and the equipment |
| `WFIGHTMN` | `0x800A4CA4` | 41 / 42 | the battle's sub-overlay, which `FIGHTSTG` loads (file 0x1FA) for a normal battle: it checks the party and its equipment and ends the battle |
| `WFIGHTTS` | `0x800A4CA4` | 13 / 14 | the debug battle test, which `FIGHTSTG` loads (file 0x1FB) in place of `WFIGHTMN`: lists of fighters, motions, effects and stages |
| `WSTAG###` (238) | `0x800A4CA4` | 1,369 / 1,369 | the stages: small programs that load on top of `FIELDSTG` and call into it |

`SMDLDATA`, `SDIGIEDT`, `SFSTDATA` and `WSTAG260` hold no code and aren't
built. The disc's `AAA/DAT`, `AAA/PRO` and `AAA/STR` directories are only
reachable through the ISO 9660 path table, which is why
`tools/extract_disc.py` is needed: dumpsxiso doesn't see them.

The executable's game code is split at its original object boundaries and
named by subsystem:

| File | Contents | Address (us) |
|---|---|---|
| `asm/<version>/main/crt0.s` | PsyQ startup (`2MBYTE.OBJ`) | `0x80010EBC`-`0x80010F80` |
| `src/main/inn.c` | the inn and the full-screen fade | `0x80010F80`-`0x800120B8` |
| `src/main/system.c` | field menu, CD reader, file cache, task creation and `main` | `0x800120B8`-`0x80014884` |
| `src/main/memcard.c` | memory card saves | `0x80014884`-`0x800154F8` |
| `src/main/game3.c` | game state: flags, event conditions, modes, party and stats | `0x800154F8`-`0x800172E8` |
| `src/main/game3_2.c` | partner data, heap and task registry | `0x800172E8`-`0x80017FAC` |
| `src/main/pad.c` | controllers and random numbers | `0x80017FAC`-`0x80018FEC` |
| `src/main/text_window.c` | text windows, font, cursor and message boxes | `0x80018FEC`-`0x8001D070` |
| `src/main/graphics.c` | display, drawing layers, sprite/TIM/card drawers | `0x8001D070`-`0x8001FC68` |
| `src/main/sound.c` | sound banks and the mode overlay loader | `0x8001FC68`-`0x80020998` |
| `src/main/psyq/` | the PsyQ libraries, one file per library object (`.s` for the ones written in assembly) | `0x80020998`-`0x8003E9D8` |

Memory maps (psylink puts `.rodata` in front of `.text`):

| | `us` (`SLUS_014.36`) | `eu` (`SLES_039.36`) |
|---|---|---|
| `.rodata` | `0x80010000`-`0x80010EBC` | `0x80010000`-`0x80010E88` |
| `.text` | `0x80010EBC`-`0x8003E9D8` | `0x80010E88`-`0x8003EDCC` |
| `.data` | `0x8003E9D8`-`0x8005C480` | `0x8003EDCC`-`0x8005CCE8` |
| `.bss` | `0x8005C480`-`0x80082448` | `0x8005CCE8`-`0x80082CB0` |
| `$gp` | `0x8005C2F8` | `0x8005CB50` |
| Overlays (`OVERLAY_VRAM`) | `0x80082448` | `0x80082CB0` |
| Stages, `WFIGHTMN`, `WFIGHTTS` (`STAGE_VRAM`) | `0x800A4CA4` | `0x800A5DE0` |

A 320x480 16-bit TIM image is loaded together with the program, so the
executable stores `.bss` and the gap after it as zeros; splat keeps that tail
as `assets/<version>/tail.bin`. `STAGE_VRAM` is right after `CARDGAME`, the
largest overlay.

## How the versions are organised

One source tree builds every version, one at a time, picked with `VERSION`
(`eu` by default):

| `VERSION` | Release | Executable (SHA-1) | Disc image (SHA-1) | Overlays | Stages | C |
|---|---|---|---|---|---|---|
| `us` | *Digimon World 3*, USA, SLUS-01436 | `SLUS_014.36` (`444653259f78ddb483fd22af72cce9276f42f214`) | `Digimon World 3 (USA).bin` (`f0b022f9be53cbce14640abd8f01beaadcb35208`) | 21 | 238 | yes |
| `eu` | *Digimon World 2003*, Europe, SLES-03936 | `SLES_039.36` (`d1b7e4d646e3a9c2b88fdb25d20b5f7116bbb06d`) | `Digimon World 2003 (Europe).bin` (`457cb233349ba841e03b33d8060f8fbcadd45cb3`) | 21 | 293 | PsyQ, the game code and data, 2 overlay files |

- `mk/version/<version>.mk` has each version's settings: the release's name,
  the executable's name, the disc directory, the overlays, where they load
  (`OVERLAY_VRAM`, `STAGE_VRAM`) and the C files it builds (`C_SRC`). The
  Makefile builds nothing else. `tools/version.py` reads the same file, so
  every tool follows `VERSION` too.
- `config/<version>/` has its splat configs (`main.yaml`, `<overlay>.yaml`),
  symbols (`symbols.txt`, `symbols_<overlay>.txt`), the list of stages
  (`stages.txt`) and the checksums (`<executable>.sha1`, `overlays.sha1`,
  `stages.sha1`). The generated `asm/<version>/`, `build/<version>/`,
  `expected/<version>/` and `assets/<version>/` are kept apart too.
- The stages have no config file each: `config/<version>/stages.txt` lists
  them with the offsets where their code starts and ends, and
  `tools/stage_yaml.py` writes their splat configs into
  `build/<version>/generated/stages/`. A stage marked `asm` there keeps its
  code and data in asm segments until it has a C file in that version; one
  marked `asm-data` only its data.
- The C sees `VERSION_US` and `VERSION_EU`, each 0 or 1
  (`include/version.h`), and so does the assembly (`--defsym`). Code tests
  them with `#if VERSION_EU`, never `#ifdef`; CONTRIBUTING.md has the rules.
- `us` builds every C file under `src/`. `eu` builds the ones it shares so
  far (`C_SRC`), with `#if VERSION_EU` blocks where its code or data differ;
  the rest of its executable and overlays is split into
  the USA version's files as asm segments, so its asm lands at the same paths
  (`asm/eu/main/system.s` for `asm/us/main/system.s`). Its stages that the
  USA version has build from their C files (`config/eu/stages/<stage>.txt`
  gives their functions the USA names), and so do its own, whose functions
  are C where they are the code of a USA stage's C. The European release has the USA one's 21
  overlays and 238 stages plus 55 stages of its own (`WSTAG920`-`974`).
- The versions share their names: the European symbol files hold the USA
  names of the functions and data paired between the two
  (`tools/match_versions.py`), and `tools/check_names.py` checks that they
  stay the same.

## Toolchain

| | |
|---|---|
| Game code | GCC 2.8.1 (`-O2 -G0`; `-G8` for `inn.c`, `system.c`, `memcard.c`, `game3.c`, `game3_2.c`, `graphics.c` and `sound.c`) + ASPSX 2.86, emulated with [maspsx](https://github.com/mkst/maspsx) |
| SDK | PsyQ 4.7: GCC 2.7.2 (`-O2`, binary-patched), some objects a patched GCC 2.8.1 |
| Splitting | [splat](https://github.com/ethteck/splat) 0.50.0 |
| Diffing | [objdiff](https://github.com/encounter/objdiff) 3.8.1, [decomp.dev](https://decomp.dev) |

- The compiler was identified by running m2c over every game function and
  building the output with several GCC versions: GCC 2.8.x `-O2` matches 82 of
  342 functions untouched, 2.7.2 matches 49 and 2.91.66 matches 46. GCC 2.8.0
  and 2.8.1 give the same results, and so do ASPSX 2.56 to 2.86.
- The game's divisions carry no divide-by-zero check, so maspsx runs without
  `--expand-div` for it (the PsyQ objects have it).
- Four files read their small variables through `$gp`, so they are built with
  `-G8` in both GCC and maspsx (`SDATA_LIMIT` in the Makefile). Those
  variables are declared `static` in the C; maspsx emits them as common
  symbols that resolve to their definitions. `inn.c`, `memcard.c` and
  `game3.c` are built with `-G8` too: the European version reads
  `LANGUAGE`, a small extern, as the assembler's macro, its address loaded
  again for every read. The rest of the game uses
  `-G0`.
- The PsyQ libraries were built with GCC 2.7.2, whose ASPSX moved the
  instruction before each `j $31` into its delay slot:
  `tools/aspsx_reorder.py` post-processes them to do the same.
  `tools/patch_cc1.py` binary-patches our GCC 2.7.2 into the cc1 the
  libraries were built with (its docstring lists every patch). The objects in
  `PSYQ_GCC28` (Makefile) came from a GCC 2.8.1 without split addresses:
  `tools/sn_cc1.py` patches a cc1 for them (its docstring lists every
  patch; the latest gives a parameter's stack slot a `REG_EQUIV` only when
  the parameter arrives there, as GCC 2.7.2 does, for `CD_sync` and
  `CD_ready`) and `tools/unfill_epilogue.py` undoes its filled epilogue
  delay slot. `PSYQ_RERUN_CSE` lists the objects
  built with the second CSE pass.
  `STDWTITL` links PsyQ's `libpress` (the movie decoder), so
  `src/stdwtitl/libpress.c` gets the same rules (`PSYQ_OBJ`).
- `src/main/psyq/` is cut at the object boundaries found from the signatures
  and from the padding between objects: ASPSX pads the `.text` of every
  object to a multiple of 16 bytes with `nop`s. Every C file ends with
  `OBJECT_END()` (from `include_asm.h`), which reproduces that padding when
  the last function is in C.
- The 56 PsyQ objects Sony wrote in assembly (the BIOS calls, the GTE
  functions of `libgte`, the BIOS patches, `setjmp`) are `src/main/psyq/*.s`,
  splat `hasm` segments: each says at its top what shows it is hand-written.
  splat writes such a file only when it is missing, and the symbols it uses
  are named in `config/<version>/symbols.txt` as for C.
- The PsyQ files include the PsyQ 4.7 headers from
  [psyq_headers](https://github.com/jype0/psyq_headers). `libgte.h` names
  some parameters `$2`, hence `-fdollars-in-identifiers`. Both code bases use
  signed `char` (`-fsigned-char`).
- Most global function pointers live in tables (the heap, `HEAP`, holds
  `free`, `alloc` and `zero`, for example) and must be called through a struct.
  GCC 2.8 assumes a struct field and a scalar global never alias, so with a
  scalar `extern` it moves stores to struct fields past the load of the
  function pointer.

## Building

### Prerequisites

On Debian or Ubuntu (the CI uses Ubuntu 24.04 and Python 3.12), install:
```
binutils-mipsel-linux-gnu gcc-mipsel-linux-gnu git make python3 python3-venv unzip wget
```
Or build in Docker instead ([below](#building-with-docker)).

Clone with the submodules (maspsx, m2c, decomp-permuter and the PsyQ headers):
```
git clone --recursive https://github.com/juandav/dw3_decomp.git
cd dw3_decomp
# or, in an existing clone:
git submodule update --init --recursive
```

Create the Python environment. Keep it active whenever you run `make` or the
scripts in `tools/`:
```
python3 -m venv .venv
. .venv/bin/activate
pip3 install -r requirements.txt
```

Download the prebuilt tools into `bin/`, checked against `tools/deps.sha256`.
They are GCC 2.8.1 and 2.7.2 for the PSX, objdiff-cli and mkpsxiso:
```
tools/dl_deps.sh
```

### Building with Docker

The `Dockerfile` has the CI's build environment: Ubuntu 24.04 with the MIPS
binutils, Python with `requirements.txt`, and the compilers and tools that
`tools/dl_deps.sh` downloads. It holds no game data. `tools/docker.sh` builds
the image and runs a command in it, with the repository (`disks/` and
`external/` included) mounted at `/dw3`, as your own user. `VERSION` is passed
on when it is set; without a command it opens a shell. No `bin/` or `.venv`
is needed on the host: `BIN_DIR` points at the image's tools. Clone with the
submodules and put the disc files in `disks/` as below, then:
```
git submodule update --init --recursive
tools/docker.sh make generate
tools/docker.sh sh -c 'make -j$(nproc)'
tools/docker.sh make compare
VERSION=eu tools/docker.sh make generate
```
The prebuilt tools are x86 Linux binaries, so the image is `linux/amd64`.

### Getting the game files

Each disc goes in its own `disks/<version>/`. Extract it with
`tools/extract_disc.py`, which also reaches the `AAA/` directories, and check
the executable:
```
python3 tools/extract_disc.py "/path/to/Digimon World 3 (USA).bin" disks/us
sha1sum disks/us/SLUS_014.36   # 444653259f78ddb483fd22af72cce9276f42f214

python3 tools/extract_disc.py "/path/to/Digimon World 2003 (Europe).bin" disks/eu
sha1sum disks/eu/SLES_039.36   # d1b7e4d646e3a9c2b88fdb25d20b5f7116bbb06d
```

Only `disks/<version>/<executable>` and `disks/<version>/AAA/PRO/` are
needed, and only for the versions you build. `config/<version>/` holds the
SHA-1 of every original binary, which `make compare` checks the build
against: `<executable>.sha1`, `overlays.sha1` and `stages.sha1`.

### Build

The same steps build each version, with `VERSION` set to `eu` or `us` (`eu`
when it is left out):
```
# Split the executable, the overlays and the stages with splat
# (asm/<version>/, build/<version>/generated/)
make VERSION=eu generate

# Build build/<version>/<executable> and build/<version>/AAA/PRO/*.PRO
make VERSION=eu -j$(nproc)

# Check the executable, every overlay and every stage against the originals
make VERSION=eu compare
```

`make compare` prints one `OK` per binary, and a change only counts once
every line still says `OK`: 260 lines for `us` (the executable, 21 overlays
and 238 stages), 315 for `eu` (the executable, 21 overlays and 293 stages):
```
build/us/SLUS_014.36: OK
build/us/AAA/PRO/CNTY_SEL.PRO: OK
build/us/AAA/PRO/STCRDABM.PRO: OK
...
```
The CI builds and compares both versions on every push.

`make VERSION=<version> regenerate` deletes `asm/<version>/`,
`build/<version>/` (and the patched compilers in `build/tools/`),
`expected/<version>/` and `assets/<version>/`, and splits the binaries again.
Run it after changing a `config/<version>/*.yaml`, a symbol file or
`stages.txt`, so that no stale files stay behind in `asm/<version>/`.

To use a different binutils or objdiff, create `local.mk`:
```
TOOLCHAIN := /path/to/mipsel-linux-gnu-
OBJDIFF := /path/to/objdiff-cli
```

## Progress

```
# Write objdiff.json and the target objects in expected/<version>/
make VERSION=eu objdiff

# Write build/<version>/report.json
make VERSION=eu report
```

After `make objdiff`, open the repository in the
[objdiff](https://github.com/encounter/objdiff) GUI to see each unit's
functions and data against the original. `tools/objdiff_generate.py` makes one
unit per C file (`main/system`, `cnty_sel/cnty_sel`, `stages/wstag200`...); a
file `X_2.c`, the second half of one original object, is reported together
with `X.c`. The units go into the category `game` (the executable), one
category per overlay, and `stages` for all the stages. The executable's data
is one unit, `main/game_data`. `src/main/psyq/` gets no unit. A file the
version being reported doesn't build from C yet, but has split at the same
path (the European `asm/eu/cnty_sel/cnty_sel.s`), is its unit with no base
object, from that code and the module's rodata, data and bss segments, so the
report counts all of it as still to do; a binary with no such file (the
European stages only it has) is one unit of splat's code and data
(`stages/wstag920`...). `objdiff.json` is for the version it was last
written for.

objdiff counts a unit's `.rodata` or `.data` as matched only when all of the
section is the original's, bytes and relocations. The report compares copies
of the objects (`build/<version>/report/`, `expected/<version>/report/`) made
to write the same data the same way: the base gets the target's names for the
rodata GCC emits without one (string literals, jump tables), pointers are
written as section plus offset on both sides, and the rodata still included
from asm (`INCLUDE_RODATA`, the jump tables of functions behind `INCLUDE_ASM`)
gets one byte changed, so its section only counts once all of it is C. Data
that splat still has in its own segments (`data` in a config rather than
`.data`) isn't in the C object, so it counts as still to do.

The CI (`.github/workflows/build.yaml`) first runs `tools/check_names.py` and
`tools/hacks.py`, which only read the source and the configs. It then builds
both versions on every push, runs `make compare` and `make report`, and uploads
each `build/<version>/report.json` as the `SLES_039.36_report` and
`SLUS_014.36_report` artifacts, which decomp.dev reads; its default version is
the European one. The original files
come from a private repository, so pull requests from forks only run the
first two checks. `.github/workflows/docker.yaml` builds and compares both
versions in the Docker image whenever the image or what it installs changes.

## Layout

| Path | Contents |
|---|---|
| `src/main/` | the executable's game code, one file per original object (see [above](#the-games-binaries)) |
| `src/main/data/` | the executable's data as C, until it moves next to the code that uses it |
| `src/main/psyq/` | the PsyQ libraries, one file per library object: C, or `.s` for the 56 objects Sony wrote in assembly |
| `src/<overlay>/` | each overlay's C; `<overlay>_2.c` is the second half of an object split in two |
| `src/stages/` | one C file per stage, `wstag###.c` |
| `include/game.h`, `include/dw3/` | types and declarations of the game code, one header per engine module (`task.h`, `heap.h`, `graphics.h`, `files.h`, `pad.h`, `sound.h`, `text.h`, `game_state.h`, `memcard.h`, `menus.h`) |
| `include/<overlay>.h`, `include/stage.h` | the overlays' types and declarations, and the stages' |
| `include/psyq.h` | declarations shared by the PsyQ files |
| `include/` | `common.h`, `version.h`, `include_asm.h` and the assembler macros |
| `config/<version>/` | the version's splat configs, symbols, stage list and checksums |
| `mk/version/` | each version's settings for the Makefile and the tools |
| `tools/` | build helpers, matching helpers and the report generator (see [Tools](#tools)) |
| `external/` | submodules: maspsx, m2c, decomp-permuter, psyq_headers |
| `.github/workflows/build.yaml` | the CI: checks the names and the hacks, builds and compares both versions, uploads their reports |
| `Dockerfile`, `tools/docker.sh`, `.github/workflows/docker.yaml` | the build environment as a Docker image, the script that runs a command in it, and its CI |
| `asm/<version>/`, `build/<version>/`, `expected/<version>/`, `assets/<version>/` | generated; not in git |
| `disks/<version>/` | the extracted disc; not in git |

## Tools

| Tool | What it does |
|---|---|
| `tools/dl_deps.sh` | downloads the PSX GCCs, objdiff-cli and mkpsxiso into `bin/` |
| `tools/extract_disc.py` | extracts a disc image, `AAA/` included |
| `tools/stage_yaml.py` | writes a stage's splat config from `config/<version>/stages.txt` |
| `tools/try_match.py` | compiles a draft and compares each of its functions with the original |
| `tools/permuter_import.py` | sets up a [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) directory for one function |
| `tools/data_to_c.py` | turns a splat data file into C definitions that reproduce its bytes |
| `tools/objdiff_generate.py` | writes `objdiff.json` (`make objdiff`) |
| `tools/data_sizes.py` | gives compiled data symbols their ELF size, for objdiff (part of the build) |
| `tools/patch_cc1.py`, `tools/sn_cc1.py`, `tools/cc1_mtlr28.c`, `tools/cc1_mtlr28.sh` | patch the PSX GCCs into the compilers of the PsyQ objects |
| `tools/aspsx_reorder.py`, `tools/unfill_epilogue.py` | reproduce the PsyQ objects' assembler (part of the build) |
| `tools/hacks.py` | counts the fake matches and hacks (`--list`, `--check README.md`) and fails on `NON_MATCHING` code, `#if 0` and inline asm in place of C |
| `tools/check_names.py` | checks that every version's symbol files use the USA version's names |
| `tools/match_versions.py` | pairs a version's functions with the USA ones (`build/<version>/version_pairs.txt`) and, with `--seed`, writes their USA names into the version's symbol files |
| `tools/split_version.py` | splits a version's executable and overlays into the USA version's files, from the pairs |
| `tools/version_symbols.py` | names, at a version's addresses, what a USA C file uses, so that the version can build it |
| `tools/rename.py` | renames a symbol in every version's symbol files, `src/` and `include/` |
| `tools/docker.sh` | runs a command in the Docker build environment |
| `tools/version.py` | the version being worked on and its paths, for the other tools |

## Contributing

Read [CONTRIBUTING.md](CONTRIBUTING.md) for the matching workflow and the rules
on matching, versions, code style, names and pull requests.
[TODO.md](TODO.md) lists what is left to do.

In short: every function starts as an `INCLUDE_ASM` line in `src/`. To
decompile one, get a first draft from m2c, make it match with
`tools/try_match.py`, objdiff and, for a near miss, the permuter, then replace
the `INCLUDE_ASM` with it and check that `make compare` still says `OK` for
every binary of both versions.

The PsyQ functions were named from the
[PsyQ 4.7 signatures](https://github.com/lab313ru/psx_psyq_signatures).

## Links

- [decomp.dev: Digimon World 3](https://decomp.dev/juandav/dw3_decomp)
- Inspired by these projects:
  [Digimon World decomp](https://github.com/jype0/dw_decomp),
  [Digimon World 2 decomp](https://github.com/Wyrelade/Digimon-World-2-Decomp),
  [Digimon Digital Card Battle decomp](https://github.com/juandav/dcb_decomp),
  which links the same PsyQ 4.7 libraries and shares several of the compiler
  patches.
- Tools: [splat](https://github.com/ethteck/splat),
  [maspsx](https://github.com/mkst/maspsx),
  [objdiff](https://github.com/encounter/objdiff),
  [m2c](https://github.com/matt-kempster/m2c),
  [decomp-permuter](https://github.com/simonlindholm/decomp-permuter),
  [old-gcc](https://github.com/decompals/old-gcc) (the PSX GCC builds),
  [mkpsxiso](https://github.com/Lameguy64/mkpsxiso),
  [psyq_headers](https://github.com/jype0/psyq_headers).
