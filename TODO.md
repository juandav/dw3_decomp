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
  (`config/eu/stages/<stage>.txt`): all 1,590 of the European stages'
  functions are C.
- [x] The setup functions (the one that fills `D_800990B4` and loads the
  stage's text file) are C in both versions, from one C. The European
  scheduling needed the stores up to `0x1C` and the one to `0x44` to stay
  before the others while the constants rise to the top. The start
  position does it: written as a constructor, `unk2C = (Vec2){x, y}`, it
  makes GCC's `store_constructor` clobber the whole field (a `BLKmode`
  `MEM`, which conflicts with every access to `D_800990B4`) before its two
  stores, so the stores stay on their side of it and the constants don't.
  It gives the USA order too. The text file is `STAGE_TEXT`, the file and
  archive numbers `STAGE_FILE` and `STAGE_ARCHIVE`, the stage's own
  defines; `unk7C` (`FIELDSTG`'s `func_80091490`) finds a record of a list
  of 0x1C-byte records by its id.
- [x] The 8 functions that read `GAME` fields 8 bytes later in the European
  version (`countdown`, `unk26DC`, `unk26E8`) are C in both: `WSTAG745`/
  `746` `func_800A4CA4`, `WSTAG795` `func_800A50F8`/`func_800A5240`,
  `WSTAG800` `func_800A5404`/`func_800A554C`, `WSTAG810` `func_800A58F0`/
  `func_800A5954`, with `GAME.countdown` (`u8 [4]`, `0x26CC`) and the
  `StageInfo` fields `0x50`-`0x60`.
- [x] The 55 European stages, `WSTAG920`-`974`, have C files, their data
  too: all their functions are C.
- [x] Where the versions' code differs only in numbers, `include/stage.h`
  and the stages' own defines give them: the file numbers (`SPRITES`,
  `MENU_TEXT`...), `MENU_SPRITES` and `TEXT_ENTRY` (the European version
  adds the language to the text file).
- [x] `game3_2` is C in the European version, but its unit in the report is
  `game3`'s: it counts now that `game3.c` is built for `eu` too.

## The USA executable

- [x] The game code is all C: `spriteDrawerDraw` and `convertText`
  (`graphics.c`) were the last.
- [x] The executable's rodata is all C. `OVERLAY_ADDRESS` and
  `SUB_OVERLAY_ADDRESS` (`system.c`) are `const` pointers in `.rodata`,
  read with `lui`/`lw` although `system.c` is built with `-G8`: the game's
  code is built with `-membedded-data`, which puts a small `const` in
  `.rodata` and changes nothing else. `text_window.c`'s strings and tables
  are C.
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

- [ ] 7 of the 563 PsyQ functions are still `INCLUDE_ASM`, in 5 objects
  (`libmcrd_low` and `libmcrd_libmcrd` 2 each, `libsnd_cc_6`,
  `libsnd_vm_vol`, `libcd_c_011`), all compiled code; 166 are still named
  `func_`. What Sony wrote in assembly (71 functions, 56 objects) is `.s`
  sources in `src/main/psyq/`. Drafts of the ones left are in
  `permuter/drafts_2026-10/` and `permuter/_SsContDataEntry/` (the main
  checkout's, which git ignores). Closest attempts:
  - `_SsContDataEntry` (`libsnd_cc_6`) matches with two more changes to
    the 2.7.2 cc1 (`permuter/_SsContDataEntry/mkcc1.py` makes it): combine's
    `set_nonzero_bits_and_sign_copies` without 2.7's `reg_n_sets > 1` and
    `reg_basic_block < 0` tests (GCC 2.8's, for a `beqz` where ours has
    `blez`), and patch 19's two-reference rule off (its frame is
    `vars= 64`). That rule is there for `GsSetFlatLight`'s `x / 255`, so
    it needs a sharper condition first: here the two pseudos are kept
    alive only by a `(use ...)` insn that combine made. 23 diffs with the
    cc1 as it is.
  - `_SsVmSetVol` (`libsnd_vm_vol`; its prototype wants `short` vab and
    prog and `u_short` pan) is 317 diffs: loop.c doesn't hoist the
    constants of its `/ 127` and `/ 16129` out of the loop, which needs a
    threshold of about 258 where 2.7.2's formula gives about 98. With
    that forced, 46 diffs of register allocation are left.
  - `func_8002C590` (`libcd_c_011`) is 87 diffs; `func_8003BAEC`,
    `func_8003BE70`, `_card_format2` and `_card_create2` 90 to 256.
- [ ] 7 `INCLUDE_RODATA`: `libgpu_sys` 4 and `libcd_bios_1` 3.
- [x] `CD_sync` and `CD_ready` (`libcd_bios_1`) match once the SN cc1
  (`tools/sn_cc1.py`) gives a parameter copied to a pseudo a `REG_EQUIV`
  for its stack slot only when it arrives there (`entry_parm ==
  stack_parm`), as GCC 2.7.2 does; `CD_datasync` no longer needs its copy
  of `mode`. Every `PSYQ_GCC28` object builds the same with it.

## Overlays

- [ ] 1,607 of the overlays' 1,697 functions are C. All C: `CNTY_SEL`,
  `SOUNDTST`, `STPLNMET`, `STDGNAME`, `STGMCARD`, `STFGTREP`, `STCRDABM`. Mostly:
  `STCRDDEK` (54 / 55), `SHOCKTST` (16 / 17), `STAGSLCT` (7 / 8),
  `FIELDSTG` (211 / 222), `STDWTITL` (91 / 93: `libpress`'s handwritten
  `DecDCTvlc2` and `DecDCTvlcSize2` stay asm), `STGTRAIN` (88 / 94),
  `STITSHOP` (68 / 69), `STGDGLAB` (69 / 70), `CARDGAME` (305 / 306),
  `STSTATUS` (122 / 123), `STCRDSHP` (43 / 45), `WFIGHTTS` (13 / 14),
  `WFIGHTMN` (41 / 42), `FIGHTSTG` (250 / 310).
- [ ] The small overlays' last functions:
  - `STCRDDEK_createScreenWindows` (3 diffs): the `unk5C` loop's counter
    gets `s2` where the original has `s3`, the register of the other loops'
    counter.
  - `STAGSLCT_showBiosVersion` matches only with an empty `do {} while (0)`
    that ends a CSE block, a fake match.
  - `SHOCKTST_convertText` (173 diffs): the
    original keeps both `times + 2` and `powers + 2` as induction variables
    and doesn't hoist the parser's constants.
  - `FIELDSTG` (five objects, `fieldstg.c` to `fieldstg_5.c`):
    `func_800896C0`, the field's battle transition (the screen breaks into
    30 tiles that slide off in a spiral), matches in both versions only with
    an empty `do {} while (0)` between `speed` and `move`: its loop notes
    stop the second scheduler from moving the load of `GFX.buffer` up into
    the load delay of `task->counter`'s. Nothing hints at a print
    or a loop there, so it stays asm.
    `func_80091124`, `func_80091AA8`, `func_8008D4C4` and `func_80085650`
    are close but the permuter found no match; `func_8008DB60` and
    `func_8008DFE0` only match with the permuter's copy of a variable kept
    for nothing; `func_8008EC74` differs in its block layout,
    `func_80085EEC` is a near miss too, and `func_80090450` matches in Europe
    but swaps `s4` and `s5` in the USA. `func_8008A154` (the field's
    update, which creates the characters and runs the transition) has the
    right code but 80 diffs of registers; the permuter only got closer with
    an empty `do {} while (0)`, a fake match.
- [ ] `FIGHTSTG`'s blocked functions: `func_8009C764`, `func_8009C8EC` and
  `func_8009C998` differ only in registers and the order of a few loads (the
  permuter finds nothing natural); `func_800877D4` and `func_800A0FDC` are
  near misses too, and so is `func_80083C78` (1 diff: the operands of the
  `addu` of `children` and the bone). `func_80088FC4` (the effect models'
  creator) only stores `texPos` before `file`. Of the GTE functions,
  `func_80084780` (the mesh's bounds check) keeps 26 diffs because gcc folds
  its -64 and +128 into one constant (the permuter gets no closer); the
  large mesh drawers `func_80084890` (48 diffs) and `func_800850D8` (26)
  differ in how they keep the state's fields in registers. `func_80099D24`
  only matches with an empty `do {} while (0)`, a fake match. The battle
  checks: `func_8009EF04` (`getDamage`) only matches with a copy of `side`
  kept for nothing, a forced form; `func_8009EA74` keeps 2 diffs (`v1` and
  `a2` swapped for the value); `FIGHTSTG_computeStats` (26 diffs: the
  equipment loops share a base register the original doesn't), and
  `func_800A0830` (43) and `func_800A067C` (27: the original keeps
  `&D_800A31E8 + 8` in a register to read `unkD0`) got no closer with the
  permuter (best scores 490, 270 and 145). In `fightstg_5.c` and
  `fightstg_6.c`: `func_800937FC`, `func_80095AC0`, `func_800967A4`,
  `func_800973D4` (which also wants `DigimonData.unk2A` as a `u16`),
  `func_80091788` and `func_80091950` (the battle camera's views) place a
  block out of line before a case or a loop, which only an empty
  `do {} while (0)` gives (`func_800937FC` still keeps 22 diffs with one);
  `func_80094D04` (21 diffs) does the same with its triangle block.
  `func_8008AF74` (the battle script's model command) keeps 6 diffs: the
  original loads case 3's time between reading `pc[0]` and storing it, and
  the permuter only got closer with a variable kept for nothing.
  `func_800928BC` (76 diffs in the USA, 88 in Europe), `func_800931CC` (21),
  `func_800921EC` (18), `func_800924DC` (69) and `func_8008B784` (24) differ
  in their registers, and `func_80093E4C`, which reads the stats through
  `D_800A2294`'s offsets, gets a giv split the original doesn't have. Still
  to try: `func_8008C0BC`, `func_8008C8F0`, `func_8008CFFC`,
  `func_8008E3C8`, `func_8008EAF8`, `func_80090290`, `func_80090908`,
  `func_80091A58` and Europe's `func_800A1048`. `fightstg.c` defines
  `D_800A310C` as a `u16` array where `func_8009AEA4` reads it as
  `EventDelay`s, and `D_800A2274` as an `s32` array where
  `func_800937FC` reads an `Unk8009A214`.
- [ ] The battle menus' near misses. `WFIGHTTS`: `func_800A6954` (the
  Digimon list, 14 windows a side; its cursors and scrolls are
  `D_800A8268[2]` and `D_800A8270[2]`, two scalars each in the C for now)
  stays at 31 diffs with `D_800A8270[1] + 0x37 + j`: gcc then keeps
  `j + 0x37` in a register where the original adds the scroll first, and
  `j + D_800A8270[1] + 0x37`, the original's order, stops gcc hoisting the
  scroll's address (60 diffs); the steps (`a3`/`t0`) and `j` and
  `&D_800A32E0` (`s1`/`s2`) are swapped too, and a 12-minute permuter run
  found nothing natural; the variable reuse and statement order that matched
  its neighbours change nothing. `WFIGHTMN`: `func_800A5538` (the units' stats
  from the party and the battle's enemies) is at 29 diffs. A
  `units = D_800A31E8.fighters[0]` pointer, set again to `fighters[1]` for
  the enemies' loop, gives the party's loop its registers; the rest is the
  enemies' loop: the original doesn't schedule its load of
  `D_800A2584` above the `mp` stores, as if they could alias. GCC 2.8's
  alias analysis separates them because the stores' base is
  `D_800A31E8` and the load's another symbol; the original's stores must
  have lost their base (a pointer stepped with `++` loses it, but then
  gets the wrong registers). Declaring `D_800A2584` as a struct's only
  member matches the size (8 diffs), but it is a scalar in `FIGHTSTG`;
  the permuter's best (2 diffs) ends the stores' block with an empty
  `do {} while (0)`. `CARDGAME`: `func_8009DE0C` (the sort of a list of cards by `battle->cards[list[k]]`, swapping
  `unk30A` and `unk446` with it by flag) stays at 22 diffs: `from` and
  `flags & 1` swap `a1` and `s0`, and the loop counter and the `unk446`
  pointer `t3` and `t4`. Our `from` has 7 refs over 59 insns, `flags & 1` 4
  over 53, so ours allocates `from` first; the declarations' order,
  `u16`/`u32` copies, flag variables, the swaps' order, pointer sums and
  the compares' order change nothing, and a 25-minute permuter run found
  nothing natural.
- [ ] `WFIGHTTS` keeps the old names of the battle camera (`Unk800911C8`,
  `Unk80091618`, which `include/fightstg.h` keeps for it). `WFIGHTMN`
  includes `fightstg.h` alone now and uses its names (`BattleFighter`,
  `QueuedEvent`, `EventQueue`, `BattleEvent`, `BattleTableEntry`...); the
  call that reads `D_800A3104` stays that.
- [ ] The field menu's near misses. `STSTATUS`: `func_80095D6C` (21
  diffs, registers only, in the third loop: the original gives its counter
  `s1`, `&FILE_CACHE` `s2`, `i * 46 + 0x25` `s4`, `i * 46 + 0x13` `s5` and
  the `PanelAnim` pointer `s6`; with a counter of its own for that loop
  ours has `&FILE_CACHE` right but swaps the counter with the `0x25` sum and
  the `0x13` sum with the pointer). What fixed the rest of `STSTATUS` and
  might help here: drawing a frame's last part in each branch, separate
  variables for each loop or case (`func_80097F2C` indexes its town list
  with the loop's counter; `func_8008F7A0`, `func_8009440C` and
  `func_8008927C` need a cursor variable or a counter per case), the order
  of a sum's terms (`i * 0xE + 0x88 + scroll` gives the original's
  `scroll + 0x88` first), and `substate++` written in both branches.
  Counters per loop in other combinations, the `0x17` draw after the
  branches and a 25-minute permuter run (only forced forms) change nothing.
  `STCRDSHP`: `func_800870F4` (1 diff: the original
  copies the quotient of the count by 6 into another register for the
  `addu` of the pages count; computing the remainder first, as in
  `pages = buy->count % 6 != 0; buy->pages = pages + buy->count / 6;`,
  gets the copy, but then the `addu`'s operands come out swapped, and
  writing `buy->count / 6 + pages` ties the sum to the quotient's
  register instead). `func_80083BEC` (the states of
  the screen that opens a pack) is down to 2 diffs: in case 52 the
  original loads `open->page` into `a1` where ours ties it to `v1`, the
  register of `page * 8`. What got it there: case 4 keeps the old page in
  `first` and writes `last` as `(first + 1) * 8 - 1` (which CSE doesn't
  merge with `first * 8`), case 52 needs a variable of its own for the
  last row, and case 11 a variable for `RANDOM.next() % 16`; the page
  goes through `a1` in the original whatever variable holds it.
  `STITSHOP`: `func_80089104`
  (3 diffs: the order in which the loop initializes its `x` induction
  variables). `STGDGLAB`: `func_8008C234` (4 diffs: our
  scheduler moves the `skillCount = 6` store after the argument moves of
  the call to `func_8008BB78`, where the original keeps it before them; no variable, label or order changes it, nor
  the permuter). `STCRDSHP` is three objects, like
  `STSTATUS`'s ten: GCC aligns a jump table to 8 bytes, and the original's
  tables only line up at its object boundaries.
- [ ] `STGTRAIN`'s near misses: `func_80085AF8` (3 diffs: the original
  schedules the table's `lui` later in two of the three branches; the
  permuter's best reuses a variable), `func_800859F4` (15, `s0`/`s2`
  swapped) and `func_8008B35C` (the RLEN loader: the original reloads
  `D_8008C4D4` in the loop and spills `clutX`; ours keeps both in
  registers). `func_80087E34`, `func_80088CFC` and `func_800867A0` were
  tried without a match (register allocation; `func_800867A0` is closest
  in Europe).
- [ ] Check `STFGTREP`'s guess (the report after a battle) against its
  texts, and `STGDGLAB`'s (the partners' digivolutions) against its
  strings.
  `STAGSLCT`'s menu of every scene of the game may help.
- [ ] Name the overlays' functions: only `CNTY_SEL`, `SHOCKTST`,
  `SOUNDTST`, `STAGSLCT`, `STCRDABM`, `STCRDDEK` and `STDWTITL` have names
  (`STDGNAME` all but four of its own; and
  `FIGHTSTG` its event queue, fighters' file and battle table, and
  `STITSHOP`, `STSTATUS`, `STGDGLAB`, `STCRDSHP`, `STFGTREP`, `STGMCARD`,
  `STPLNMET`, `WFIGHTMN` and `WFIGHTTS` their helpers and tasks); the other
  overlays' symbol files are empty or hold a few `D_` entries, so `FIELDSTG`
  and `STGTRAIN`, much of which is C, are still `func_`.
- [ ] Overlay data: 82 % of it is C in both versions; the `.data` of every
  overlay is C. objdiff counts a section only when all of it
  matches, so the `.rodata` of the overlays with functions still in asm
  doesn't count yet. `INCLUDE_RODATA` is left in `SHOCKTST` (7),
  `FIGHTSTG` (4), `FIELDSTG` and the European `STAGSLCT` and `SOUNDTST`
  (1 each). `STAGSLCT`'s texts are C, but the European overlay pads its
  cursor, `"＞"`, with 0x39 where the build gives 0 (as `SOUNDTST` pads its
  own with 0x2D, below), so that one stays asm. `WFIGHTTS`'s strings are a
  `const char` array whose padding after each table's last string is what
  the assembler left there, in both versions. The European `CNTY_SEL` `.data`
  stays at 98.95 % in the report: the file ends 3 bytes into its last
  word, which splat's object leaves out.
- [x] `SOUNDTST`'s texts are string literals in its lists, which GCC puts
  in `.rodata` in reverse order of each list. The European file pads the
  last one, `"＞"`, with 0x2D instead of 0, so there it stays asm
  (`SOUNDTST_STR_CURSOR`).

## Stages

- [x] The USA stages are all C: their 1,369 functions, the setup
  functions too (see the European stages above).
- [x] A stage's jump tables come from its C (`c-rodata` in `stages.txt`),
  and so does the color that 85 stages start with (a `const CVECTOR` that
  the setup function copies to `unk38`); `head-word` keeps the color in
  asm where it comes before jump tables, as GCC would align them to 8 bytes
  after it (`WSTAG924`).
- [x] The stages' data and rodata are all C, in both versions (816,636
  bytes in the USA version's report, 950,484 in the European one's), as
  splat's words (`tools/data_to_c.py`) at the end of each stage's C file,
  with `#if VERSION_US` / `VERSION_EU` rows for the words that differ (file
  numbers, mostly) or that one version hasn't. `WSTAG331`'s data differs
  throughout between the versions (its event scripts), so some of its
  arrays have each version's whole definition.
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
