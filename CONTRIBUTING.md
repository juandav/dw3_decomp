# Contributing

The conventions follow the [Digimon World decomp](https://github.com/jype0/dw_decomp)
and the [Digimon Digital Card Battle decomp](https://github.com/juandav/dcb_decomp),
so that the Digimon decomps read the same way. The README explains how to
set up and build the project; this file is about the work itself.

## Decompiling a function

Every function that isn't C yet is an `INCLUDE_ASM` line in its file under
`src/`, which includes splat's disassembly of it:
```c
INCLUDE_ASM("main/nonmatchings/graphics", convertText);
INCLUDE_ASM("stages/nonmatchings/wstag210", func_800A4D38);
```
The folder is relative to `asm/<version>/`, so the function above is
`asm/us/main/nonmatchings/graphics/convertText.s` after `make generate`.

1. **Get a first draft.** m2c turns the `.s` into C to start from:
   ```
   python3 external/m2c/m2c.py asm/us/main/nonmatchings/graphics/convertText.s
   ```
   Give it `--context` with a preprocessed copy of the file's headers to
   get the project's types and names in the output. The draft is a starting
   point: give it the real types, the struct fields and the engine calls of
   the code around it (see [Code](#code)).
2. **Make it match on its own.** Put the draft in a file of its own that
   includes the same headers as its unit, and compare it with the original:
   ```
   tools/try_match.py draft.c convertText
   ```
   It compiles the draft with the project's compiler, finds the function in
   `asm/<version>/` and prints `MATCH`, or both versions side by side with the
   differing instructions marked `**`. Relocated fields are masked, so a
   different symbol name doesn't count as a difference. Set `UNIT=wstag210`
   (any part of the path) when several units have a function of that name, as
   the stages do; `VERSION` picks the version. For a `-G8` file (`inn.c`,
   `system.c`, `memcard.c`, `game3.c`, `game3_2.c`, `graphics.c`, `sound.c`), pass the
   same flags as the Makefile: `CFLAGS='-O2 -G8 -fsigned-char -fno-builtin
   -fdollars-in-identifiers' MASPSXFLAGS='--aspsx-version=2.86 -G8'`. For
   PsyQ code, `CC1=bin/gcc-2.7.2-psx/cc1` (plus `RERUN=1` or `GCC28=1` for the
   objects in `PSYQ_RERUN_CSE` or `PSYQ_GCC28`); the docstring of
   `tools/try_match.py` has the details.
3. **Search for a near miss.** When only register allocation or instruction
   order is left, try other source shapes first: types, the order of
   statements, a temporary, a loop written another way. Then the permuter
   can search for you:
   ```
   tools/permuter_import.py draft.c convertText
   python3 external/decomp-permuter/permuter.py permuter/convertText -j8
   ```
   The permuter's finds are hints, not answers: keep only what reads as C
   someone would write (see [Matching](#matching)).
4. **Put it in place.** Replace the `INCLUDE_ASM` line with the C, add the
   prototypes and types it needs to the headers, rebuild and check:
   ```
   make -j$(nproc) && make compare
   make VERSION=us -j$(nproc) && make VERSION=us compare
   ```
   Every line of both versions has to say `OK`.
5. **Check it in objdiff.** `make objdiff` and the objdiff GUI show the
   function and its data against the original inside the whole unit;
   `make report` writes the progress that decomp.dev will show.

Rodata is migrated into the functions that use it: a function's jump tables
and strings live in its own `.s` file, so its C version emits them itself, and
switch statements work as usual. Rodata shared by several functions stays
behind `INCLUDE_RODATA` until all of them are C. Data that splat left as
`.word`s becomes C with `tools/data_to_c.py`, which reproduces the bytes;
give it real types once the code that uses it is understood.

## Matching

- A change only counts if `make compare` still says `OK` for every binary of
  both versions: the executable, the overlays and the stages have to stay
  byte for byte identical. Run it for `us` and for `eu` before opening a pull
  request; the CI runs both.
- Only byte-identical matches go in. No `NON_MATCHING` code, no `#if 0`
  blocks, no inline assembly in place of C, and no tricks that wouldn't pass
  review. A function that doesn't match yet stays behind its `INCLUDE_ASM`; a
  draft that came close can go in the pull request's description, not in the
  source. `tools/hacks.py` fails the CI on `NON_MATCHING` (or `NONMATCHING`),
  on `#if 0`, on inline asm in a function's body, on a register variable
  pinned with `asm("$reg")` and on a top-level asm that isn't data.
- A fake match is the last resort, not a shortcut: only for a function that
  natural C has failed to match after a real search (other source shapes,
  types, statement order, the permuter's legitimate finds), a forced form is
  allowed, such as an empty `do {} while (0)` used as a CSE or scheduling
  barrier, a variable reused for an unrelated job, or a local that only
  shapes the stack frame. Mark the exact spot with a comment that starts with
  `/* fake match:` and gives, in one or two lines, what is forced and why:
  the compiler decision it reproduces. Example: `/* fake match: the empty
  loop ends a CSE block, so GFX's address is loaded again, as in the
  original */`. A forced form without its reason doesn't pass review, and
  the rest of the function stays readable C.
- Two lesser workarounds have a standard marker of their own, so that
  `tools/hacks.py` can count them for the README's badge:
  - a local that nothing reads or writes, kept because the original's stack
    frame has room for it, ends its declaration with exactly
    `/* unused, but it is in the original stack frame */`
    (`MATRIX unused; /* unused, but it is in the original stack frame */` in
    `libgs_gs_131.c`). Anything more to say about it goes in a comment of its
    own above it. A local that makes no difference to the output is deleted
    instead.
  - C that only matches in one of several equivalent forms (an extra block,
    an `if` without braces, a copy of a variable, a type, one version's own
    form of a loop) has a comment that says the `match depends on` that
    form, and why: `/* kept on one line: the match depends on it, since GCC
    2.8.1's line notes decide where the index is computed */`.

  After adding or removing a fake match or one of these, run
  `tools/hacks.py` and update the README's badge and table to its counts:
  the CI runs `tools/hacks.py --check README.md`. `tools/hacks.py --list`
  lists them all.
- When a form recurs and has a likely origin, give it a name and say so
  once, as `COUNTDOWN_BORROW` in `include/stage.h` does: a statement macro
  for the timed stages' countdown, whose `do { } while (0)` the match
  depends on. Say it once for a form every copy shares too, as the comment
  above `StageInfo` does for the setup functions' `(Vec2){x, y}`.
- Code that was written in assembly, not compiled, stays as assembly. Say in
  a comment what shows it is hand-written (things no compiler emits). An
  object that is all assembly is a `.s` source, a splat `hasm` segment, as
  the PsyQ ones in `src/main/psyq/` are.

## Versions

The same source builds every version of the game (`make VERSION=eu`, the default, or `us`).
The Makefile passes one `-DVERSION_<VERSION>`, and `include/version.h`
(through `common.h`) makes `VERSION_US` and `VERSION_EU` both defined, each 0
or 1; the assembly gets the same names from `--defsym`.

- Test a version with `#if`, never `#ifdef` or `defined()`: `#if VERSION_EU`.
  A misspelt name is then a `-Wundef` warning instead of silently false.
- A condition names the versions it is for: `#if VERSION_US || VERSION_EU`,
  not `#if !VERSION_US`, so that a version added later doesn't fall into a
  branch nobody checked for it. The versions have no order: no
  `VERSION >= ...` or "newer than" tests.
- Only name a version you have checked. While a file is still asm in some
  version, its `#if` blocks name only the versions that build it from C.
- Each version lists the C files it builds in `mk/version/<version>.mk`
  (`C_SRC`), and the Makefile builds nothing else. `us` builds every C file
  under `src/`; `eu` the ones it shares so far (the PsyQ libraries, the
  executable's game code and data, `SOUNDTST`, `STDWTITL`'s `libpress`). The rest of
  `eu`'s executable and overlays is split into the USA files as asm
  segments with the same names (`tools/split_version.py`).
- To build a file for `eu` too: add it to `eu`'s `C_SRC`, make its segments
  in `config/eu/` `c` (with `.rodata` and `.data` when those are C in
  `us`), then name what the C uses at the European addresses:

  ```
  tools/match_versions.py eu      # with both versions built: build/eu/version_pairs.tsv
  tools/version_symbols.py eu src/<binary>/<file>.c --write
  make VERSION=eu generate build/eu/src/<binary>/<file>.c.o
  tools/version_symbols.py eu src/<binary>/<file>.c --write
  make VERSION=eu regenerate && make VERSION=eu && make VERSION=eu compare
  ```

  The first run names the functions and rodata the C includes as asm, so
  that splat writes their files; the second, after the object builds, names
  every function and datum it reads from where the original has them.
  `version_symbols.py` lists what it can't name: a name whose reads
  disagree, or one of splat's names from `us` (`D_80081E20`) that the
  European asm has at another address. For a stage, drop the `asm` mark of
  its line in `config/eu/stages.txt` once it has a C file there.
- A file whose contents differ throughout between versions gets one copy per
  version instead of an `#if` around all of it, named after the version
  (`<module>_eu.c` next to `<module>.c`).

## Code

Look at the C around you and write the same way. What the existing code
does:

- Four spaces, no tabs; the opening brace on the same line; braces around
  every `if`, `for` and `while` body, even a one-line one.
- Comments are `/* */`. A function gets a one-line comment above it that
  says what it does or returns (`/* Advances a panel animation; 1 once it has
  finished */`), and a block of code a comment for what isn't obvious from
  the code: a magic number, a file id, a mode.
- The game code uses the types of `include/common.h` (`s8`, `u8`, `s16`,
  `u16`, `s32`, `u32`) and the PsyQ types where it talks to the SDK (`RECT`,
  `CVECTOR`, `u_long`). The PsyQ files use the SDK's own types and include
  `psyq.h`.
- Struct fields keep their offset in a comment, and fields that aren't
  understood yet are named by it:
  ```c
  typedef struct StageTask {
      TASK_HEADER(StageTask);
      /* 0x50 */ void *owner;
  } StageTask;
  ```
  A task's struct starts with `TASK_HEADER(Type)` (`include/dw3/task.h`),
  and its state machine uses `TASK_INIT`, `TASK_RUN`, `TASK_DONE` and
  `TASK_KILL`.
- The engine is reached through its tables, as the original does:
  `SOUND.playSound(...)`, `GFX.funcs.createLayer(...)`,
  `FILE_CACHE.load(...)`, `GAME.funcs.getPartyMember(...)`, or a task's own
  methods, `task->nextState(task)`. Declare a global function pointer table
  as a struct or an array, never as a scalar `extern`: GCC 2.8 moves stores
  to struct fields past the load of a scalar's function pointer.
- In a `-G8` file, the small variables the code reads through `$gp` are
  declared `static` at the top of the file.
- Headers: `include/game.h` includes the engine's headers, one per module in
  `include/dw3/<module>.h`, each with its own types and prototypes;
  `include/<overlay>.h` has an overlay's, and `include/stage.h` what the
  stages share. Every header has an `#ifndef <NAME>_H` guard, and most a
  comment at the top that says what the module or overlay is.
- A `.c` file keeps the externs and prototypes only it uses at its top,
  after the includes. Anything a second file needs moves to a header.

## Layout

- One folder per binary under `src/`: `src/main/` for the executable,
  `src/<overlay>/` for each overlay, and `src/stages/` with one
  `wstag###.c` per stage.
- The executable's files follow its original objects (`inn.c`, `system.c`,
  `memcard.c`, ...); the SDK is in `src/main/psyq/`, one file per library
  object, each ending with `OBJECT_END()`.
- A file `X_2.c` is the second half of an original object that the splat
  config splits in two; the report counts both halves as the unit `X`.
- The executable's data is in `src/main/data/` until it moves to the module
  that defines it. Its European tables differ all over (file numbers,
  screen positions, overlay addresses) and splat names them at other
  addresses: they are `data_to_c.py`'s output for `asm/eu/` next to the USA
  ones, in `#if VERSION_US`/`#elif VERSION_EU` blocks for the objects that
  differ. Give a table the same name in both versions when you name it.

## Names

A name has to come from evidence: the strings a function uses, the SDK calls
it makes, its callers, the data it reads. What isn't understood yet keeps its
address (`func_800A4D38`, `D_800A6EAC`, `unk14`).

| What | Style | Examples |
|---|---|---|
| Functions | camelCase, a verb that says what the function does | `createTextWindow`, `startPanel`, `updatePanel`, `tryAllocMem` |
| Globals and tables | UPPER_SNAKE | `FIELD_MENU_LAYOUT`, `PAGE_STATS`, `ROOT_TASK` |
| Engine modules | UPPER_SNAKE, a struct of state and methods | `GFX`, `HEAP`, `FILE_CACHE`, `PAD`, `SOUND`, `GAME` |
| Types | PascalCase | `StageTask`, `FieldMenuView`, `PanelAnim` |
| Struct fields | camelCase, with the offset comment kept | `/* 0x58 */ s32 cursor;` |
| Parameters and locals | camelCase, the same word for the same thing everywhere | `task`, `layer`, `win`, `id` |
| Overlay functions and data | the overlay's name in capitals first, then camelCase | `CNTY_SEL_tickScreen`, `STDWTITL_startLogoTask`, `CNTY_SEL_screenRect` |
| Strings | `[OVERLAY_]STR_` or `PATH_`, then the words | `STR_NULL_MESSAGE`, `SHOCKTST_STR_SLOW`, `SHOCKTST_PATH_DLSKDATA_TXT` |

Verbs: a task's per-frame update is `tick*`, the function that creates it
`start*Task`; `draw*` draws, `create*` sets up and returns an object,
`show*`, `init*`, `load*`, `get*`/`set*`, `is*`/`has*`.

Every name goes in the version's symbol file, so that splat's disassembly of
the original uses it too and objdiff keeps pairing the functions:
`config/us/symbols.txt` for the executable, `config/us/symbols_<overlay>.txt`
for an overlay, with `// type:func` for a function and `// size:0x..` for
data whose size splat can't tell. Group related symbols under a comment that
says what they are, as `symbols_cnty_sel.txt` does. Then
`make regenerate`, so that no file under the old name stays in `asm/us/`.

The stages are all loaded at the same address and many have functions at the
same addresses, so their functions keep splat's names for now; the
Makefile already reads a stage's own symbol file,
`config/<version>/stages/<stage>.txt`, when there is one.

The versions share their names: a function or datum is called the same in
every version, each at its own address, and a name in `eu`'s symbol files
means what that name means in `us`'s. The CI runs `tools/check_names.py`,
which fails when a name in `eu`'s symbol files isn't `us`'s name in the same
binary (a function there if it is one here), or is named twice. splat's
automatic names (`func_`, `D_`) and the binaries `us` doesn't have (`eu`'s
own stages) aren't checked. So a rename touches every version's symbol
files the same way: `tools/rename.py OLD NEW` renames in every version's
symbol files, `src/` and `include/` (an overlay's name keeps its prefix),
then `make VERSION=<version> regenerate` each version.

- A name only one version has, for its own code, says so with
  `version-only` in its comment:
  `func_name = 0x80012345; // type:func version-only`.
- Code that `us` has in another binary is given `us`'s name, with
  `us-<binary>` in the comment (`us-main` for the executable, `us-cardgame`
  for an overlay, `us-wstag200` for a stage); check_names checks it against
  that binary's names in `us`:
  `drawWindow = 0x800A5123; // type:func us-main`.

The European version's names come from `us`: `tools/match_versions.py eu`
pairs its functions with the USA ones (by their instructions with the
addresses masked, their order, their calls and their strings) and the data
they read, and `--seed` writes the USA names of the confident pairs into
`config/eu/symbols*.txt`, between the lines it marks, keeping the names
written by hand. Name a function in `us` and run it again to give `eu` the
name too; a function whose code differs too much to pair is named by hand,
above the seeded block.

## Commits and pull requests

- Commit messages are one short sentence in the imperative, without a
  trailing period: "Decompile the stage progress setters", "Declare the
  FIELDSTG field state", "Let permuter_import pick the stage a function
  belongs to". Add a body when the change
  needs explaining: what was found, why a form matches. No trailers.
- A pull request is small and about one thing. Matches, renames and moving
  code around go in separate pull requests: decomp.dev shows a renamed or
  moved function as broken under its old name and new under the new one.
- A pull request that renames things lists every rename in a table
  (address, old name, new name).
- Before opening one, run `make compare` for both versions; both must print
  only `OK`. Run `tools/hacks.py --check README.md` and
  `tools/check_names.py` too, which the CI runs first. The CI builds and compares `eu` and `us`, and uploads both
  reports that decomp.dev reads.
- Pull requests are squash-merged, titled "Title (#N)": "Build the overlays
  and decompile CNTY_SEL (#12)". The title says what the pull request does,
  like a commit message.
