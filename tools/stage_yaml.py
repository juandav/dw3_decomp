#!/usr/bin/env python3
"""Write the splat config of a stage overlay (AAA/PRO/WSTAG###.PRO).

The 238 stage overlays all have the same layout, so instead of a config file
each, config/<version>/stages.txt lists them with the offsets where their code starts
and ends:

    WSTAG200 0x4 0x2B8

A stage loads at STAGE_VRAM (mk/version/<version>.mk; 0x800A4CA4 in us), after
the largest main overlay (CARDGAME), on top of FIELDSTG, whose functions it calls. Most stages start right with code; the
others with a word no function of the stage reads (a color such as 0x808080,
or a pointer), which stays in asm, so there is no other .rodata to migrate to
functions. From the end of the code on, the file is data.

usage: stage_yaml.py wstag200 build/us/generated/stages/wstag200.yaml
(VERSION, as for make, picks the version; us by default)
"""

import hashlib
import os
import sys

import version


TEMPLATE = """\
# {version_name}: {name}, written by tools/stage_yaml.py
name: {name}
sha1: {sha1}
options:
  basename: {name}
  target_path: {target}
  base_path: {base}
  platform: psx
  compiler: GCC

  asm_path: asm/{version}/stages
  src_path: src/stages
  build_path: build/{version}

  ld_script_path: build/{version}/generated/{name}.ld

  global_vram_start: 0x80000000
  global_vram_end: 0x80200000

  find_file_boundaries: True
  gp_value: 0x8005C2F8

  generate_asm_macros_files: False

  section_order: [".rodata", ".text", ".data", ".bss"]

  symbol_addrs_path:
{symbols}
  undefined_funcs_auto_path: build/{version}/generated/undefined_funcs_auto_{name}.txt
  undefined_syms_auto_path: build/{version}/generated/undefined_syms_auto_{name}.txt

  string_encoding: ASCII
  data_string_encoding: ASCII
  rodata_string_guesser_level: 2
  data_string_guesser_level: 2

  ld_bss_is_noload: False

  migrate_rodata_to_functions: False
  create_data_pads: False

segments:
  - name: {name}
    type: code
    start: 0x0
    vram: 0x{vram:X}
    align: 4
    subalign: 4
    subsegments:
{header}      - [0x{text_start:X}, c, {name}]
      - [0x{text_end:X}, data, {name}]
  - [0x{size:X}]
"""


# a stage that is still one blob (listed by name alone)
BLOB_TEMPLATE = """\
# {version_name}: {name}, written by tools/stage_yaml.py
name: {name}
sha1: {sha1}
options:
  basename: {name}
  target_path: {target}
  base_path: {base}
  platform: psx
  compiler: GCC

  asm_path: asm/{version}/stages
  asset_path: asm/{version}/stages/bin
  src_path: src/stages
  build_path: build/{version}

  ld_script_path: build/{version}/generated/{name}.ld

  symbol_addrs_path:
{symbols}
  undefined_funcs_auto_path: build/{version}/generated/undefined_funcs_auto_{name}.txt
  undefined_syms_auto_path: build/{version}/generated/undefined_syms_auto_{name}.txt

  generate_asm_macros_files: False
  create_c_files: False

segments:
  - name: {name}
    type: databin
    start: 0x0
    vram: 0x{vram:X}
    subalign: 4
  - [0x{size:X}]
"""


def main():
    name, out = sys.argv[1], sys.argv[2]
    root = str(version.ROOT)
    config = f"config/{version.VERSION}"
    found = blob = False
    for line in open(os.path.join(root, config, "stages.txt")):
        words = line.split("#", 1)[0].split()
        if words and words[0].lower() == name:
            found = True
            if len(words) == 1:
                blob = True
                text_start = text_end = 0
            else:
                text_start, text_end = int(words[1], 16), int(words[2], 16)
    if not found:
        sys.exit(f"{name} is not in {config}/stages.txt")

    disk = os.path.relpath(version.DISK_DIR, root)
    target = f"{disk}/AAA/PRO/{name.upper()}.PRO"
    data = open(os.path.join(root, target), "rb").read()
    symbols = [f"{config}/symbols.txt"]
    if os.path.exists(os.path.join(root, f"{config}/symbols_fieldstg.txt")):
        symbols.append(f"{config}/symbols_fieldstg.txt")
    if os.path.exists(os.path.join(root, f"{config}/stages/{name}.txt")):
        symbols.append(f"{config}/stages/{name}.txt")

    os.makedirs(os.path.dirname(out), exist_ok=True)
    with open(out, "w") as f:
        f.write(
            (BLOB_TEMPLATE if blob else TEMPLATE).format(
                name=name,
                version=version.VERSION,
                version_name=version.VERSION_NAME,
                sha1=hashlib.sha1(data).hexdigest(),
                target=target,
                base=os.path.relpath(root, os.path.dirname(os.path.abspath(out))),
                symbols="".join(f"    - {s}\n" for s in symbols),
                vram=version.STAGE_VRAM,
                header=f"      - [0x0, rodata, {name}]\n" if text_start else "",
                text_start=text_start,
                text_end=text_end,
                size=len(data),
            )
        )


if __name__ == "__main__":
    main()
