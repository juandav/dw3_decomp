.EXTRA_PREREQS := $(abspath $(lastword $(MAKEFILE_LIST)))

.DEFAULT_GOAL := all

-include local.mk

TOOLCHAIN ?= mipsel-linux-gnu-

BUILDDIR := build
ASM_DIR := asm
EXPECTEDDIR := expected
GENDIR := $(BUILDDIR)/generated

TARGET := disks/us/SLUS_014.36
ELF := $(BUILDDIR)/SLUS_014.36.elf
EXE := $(BUILDDIR)/SLUS_014.36
MAP := $(BUILDDIR)/SLUS_014.36.map

CPP := $(TOOLCHAIN)cpp
AS := $(TOOLCHAIN)as
LD := $(TOOLCHAIN)ld
OBJCOPY := $(TOOLCHAIN)objcopy

PYTHON := python3
SPLAT := $(PYTHON) -m splat split

GCC_VERSION ?= 2.8.1
CC1 ?= bin/gcc-$(GCC_VERSION)-psx/cc1

# The PsyQ libraries were built with GCC 2.7.2, and their ASPSX moved the
# instruction before `j $31` into its delay slot (tools/aspsx_reorder.py) and
# expanded `div` with the divide-by-zero and overflow checks.
# Most of them without the second CSE pass: it would put back the constant
# address of a global where the first pass kept it in a register.
MASPSX_POST :=
PSYQ_CSE :=
FLOAT_ABI := -msoft-float
$(BUILDDIR)/src/main/psyq/%.c.o: GCC_VERSION := 2.7.2
$(BUILDDIR)/src/main/psyq/%.c.o: FLOAT_ABI := -mhard-float
$(BUILDDIR)/src/main/psyq/%.c.o: MASPSX_POST := | $(PYTHON) tools/aspsx_reorder.py
$(BUILDDIR)/src/main/psyq/%.c.o: MASPSX_DIV := --expand-div
$(BUILDDIR)/src/main/psyq/%.c.o: PSYQ_CSE := -fno-rerun-cse-after-loop
PSYQ_RERUN_CSE := libc2_puts libgpu_break libcd_bios_2 libcd_c_007 libsnd_midiread libspu_s_m_f libapi_first libsnd_ssclose libsnd_vm_pb libsnd_sscall libsnd_sstable libpad_pdresres libspu_s_m_int libc2_strcmp libc2_strcspn libsnd_vm_f libspu_s_sva libsnd_vm_stav libgpu_sys libmcrd_libmcrd libc2_prnt libetc_intr libsnd_vm_key libspu_s_sav
$(PSYQ_RERUN_CSE:%=$(BUILDDIR)/src/main/psyq/%.c.o): PSYQ_CSE :=
# Our GCC 2.7.2 binary-patched into the libraries' cc1 (see tools/patch_cc1.py)
PSYQ_CC1 := $(BUILDDIR)/tools/gcc-2.7.2-psx/cc1
$(BUILDDIR)/src/main/psyq/%.c.o: CC1 := $(PSYQ_CC1)
# Some objects come from a GCC 2.8.1 without split addresses (the same objects
# are listed in dcb_decomp): it keeps the address of a global in a register
# and reaches its fields from there, never used `return` insns (tools/sn_cc1.py)
# and filled the delay slot of `j $31` itself, which tools/unfill_epilogue.py
# undoes so that ASPSX's rule applies as for the rest.
PSYQ_GCC28 := libsnd_miditime libsnd_ssvol libspu_s_n2p libspu_spu libsnd_ssopenp libspu_s_snc libspu_s_sca libsnd_cc_99 libsnd_vm_aloc1 libcd_bios_1 libcd_c_009 libsnd_vm_no1 libsnd_vm_nowon libsnd_vs_vh_2 libpad_pdresres_2 libpad_pddirres libgs_gs_108 libpad_pdtapres libcd_c_011
SN_CC1 := $(BUILDDIR)/cc1-2.8.1-sn
CC1_PRE := cat
$(PSYQ_GCC28:%=$(BUILDDIR)/src/main/psyq/%.c.o): CC1 := $(SN_CC1)
$(PSYQ_GCC28:%=$(BUILDDIR)/src/main/psyq/%.c.o): PSYQ_CSE := -mno-split-addresses
$(PSYQ_GCC28:%=$(BUILDDIR)/src/main/psyq/%.c.o): CC1_PRE := $(PYTHON) tools/unfill_epilogue.py
$(PSYQ_GCC28:%=$(BUILDDIR)/src/main/psyq/%.c.o): $(SN_CC1)
MASPSX := $(PYTHON) external/maspsx/maspsx.py
OBJDIFF ?= bin/objdiff-cli-linux-x86_64

INC := -Iinclude -Iexternal/psyq_headers/psyq_lib47/include

CPPFLAGS = $(INC) -undef -nostdinc \
	    -D__GNUC__=2 -D__GNUC_MINOR__=$(word 2,$(subst ., ,$(GCC_VERSION))) -Dmips -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx \
	    -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D_LANGUAGE_C -DLANGUAGE_C
CC1FLAGS = -quiet -O2 -G$(SDATA_LIMIT) -mips1 -mcpu=3000 -mgas $(FLOAT_ABI) \
	    -fgnu-linker -fsigned-char -fno-builtin -fdollars-in-identifiers -Wall -Wno-unused $(PSYQ_CSE)
MASPSXFLAGS = --aspsx-version=2.86 -G$(SDATA_LIMIT) --use-comm-section --use-comm-for-lcomm $(MASPSX_DIV)

# Most of the game is built with -G0; graphics.c reads its own small variables
# through $gp. Declare those variables static in C: maspsx then emits them
# as common symbols that resolve to the definitions in the data asm.
SDATA_LIMIT := 0
$(BUILDDIR)/src/main/system.c.o: SDATA_LIMIT := 8
$(BUILDDIR)/src/main/graphics.c.o: SDATA_LIMIT := 8
$(BUILDDIR)/src/main/sound.c.o: SDATA_LIMIT := 8
$(BUILDDIR)/src/main/game3_2.c.o: SDATA_LIMIT := 8
ASFLAGS := -EL -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0 $(INC)
LDFLAGS := -nostdlib --no-check-sections -Map $(MAP) \
	   -T $(GENDIR)/main.ld \
	   -T config/undefined_syms.txt \
	   -T $(GENDIR)/undefined_syms_auto_main.txt \
	   -T $(GENDIR)/undefined_funcs_auto_main.txt

ALL_C_SRC := $(shell find src -name '*.c' 2> /dev/null)
C_SRC := $(filter src/main/%,$(ALL_C_SRC))

# Target objects for objdiff: splat's full disassembly of every C unit
TARGET_ASM := $(ALL_C_SRC:src/%.c=$(ASM_DIR)/%.s)

ASM_SRC := $(filter-out $(TARGET_ASM),$(shell find $(ASM_DIR)/main -name '*.s' \
	   -not -path '*/nonmatchings/*' -not -path '*/matchings/*' 2> /dev/null))

C_OBJ := $(C_SRC:%.c=$(BUILDDIR)/%.c.o)
ASM_OBJ := $(ASM_SRC:%.s=$(BUILDDIR)/%.s.o)
TARGET_OBJ := $(TARGET_ASM:%.s=$(BUILDDIR)/%.s.o)
BIN_OBJ := $(BUILDDIR)/assets/tail.bin.o
OBJ := $(C_OBJ) $(ASM_OBJ) $(BIN_OBJ)

# Overlays: the game's AAA/PRO/*.PRO files, loaded at 0x80082448 after the
# executable's .bss. Each one has its own splat config (config/<name>.yaml),
# sources (src/<name>, asm/<name>) and output (build/AAA/PRO/<FILE>.PRO), and
# is linked against the executable's symbols (MAIN_SYMS).
OVERLAYS := cardgame cnty_sel fieldstg fightstg shocktst soundtst stagslct stcrdabm stcrddek stcrdshp stdgname stdwtitl stfgtrep stgdglab stgmcard stgtrain stitshop stplnmet ststatus wfightmn wfightts
OVL_FILE_cardgame := CARDGAME.PRO
OVL_FILE_cnty_sel := CNTY_SEL.PRO
OVL_FILE_fieldstg := FIELDSTG.PRO
OVL_FILE_fightstg := FIGHTSTG.PRO
OVL_FILE_shocktst := SHOCKTST.PRO
OVL_FILE_soundtst := SOUNDTST.PRO
OVL_FILE_stagslct := STAGSLCT.PRO
OVL_FILE_stcrdabm := STCRDABM.PRO
OVL_FILE_stcrddek := STCRDDEK.PRO
OVL_FILE_stcrdshp := STCRDSHP.PRO
OVL_FILE_stdgname := STDGNAME.PRO
OVL_FILE_stdwtitl := STDWTITL.PRO
OVL_FILE_stfgtrep := STFGTREP.PRO
OVL_FILE_stgdglab := STGDGLAB.PRO
OVL_FILE_stgmcard := STGMCARD.PRO
OVL_FILE_stgtrain := STGTRAIN.PRO
OVL_FILE_stitshop := STITSHOP.PRO
OVL_FILE_stplnmet := STPLNMET.PRO
OVL_FILE_ststatus := STSTATUS.PRO
OVL_FILE_wfightmn := WFIGHTMN.PRO
OVL_FILE_wfightts := WFIGHTTS.PRO
OVL_PARENT_wfightmn := cardgame
OVL_PARENT_wfightts := cardgame

# The stage overlays (AAA/PRO/WSTAG###.PRO), listed in config/stages.txt, load
# on top of FIELDSTG. Their splat configs are made by tools/stage_yaml.py and
# their sources are src/stages/<name>.c and asm/stages/.
STAGES := $(shell awk '!/^\#/ && NF { print tolower($$1) }' config/stages.txt)
OVERLAYS += $(STAGES)
$(foreach s,$(STAGES),\
	$(eval OVL_FILE_$(s) := $(shell echo $(s) | tr a-z A-Z).PRO)\
	$(eval OVL_PARENT_$(s) := fieldstg)\
	$(eval OVL_YAML_$(s) := $(GENDIR)/stages/$(s).yaml)\
	$(eval OVL_C_SRC_$(s) := src/stages/$(s).c)\
	$(eval OVL_ASM_SRC_$(s) := $(wildcard $(ASM_DIR)/stages/data/$(s).*.s))\
	$(eval OVL_SYMBOLS_$(s) := config/symbols_fieldstg.txt $(wildcard config/stages/$(s).txt)))

$(GENDIR)/stages/%.yaml: config/stages.txt tools/stage_yaml.py
	$(PYTHON) tools/stage_yaml.py $* $@

# The executable's own symbols for the overlays to link against (not the
# absolute ones it only references, such as FIELDSTG functions it calls).
NM := $(TOOLCHAIN)nm
MAIN_SYMS := $(BUILDDIR)/main_syms.ld
$(MAIN_SYMS): $(ELF)
	$(NM) $< | awk '$$2 ~ /^[TDRBSG]$$/ { printf "%s = 0x%s;\n", $$3, $$1 }' > $@

# An overlay loaded on top of another one (OVL_PARENT_<name>) also links
# against its parent's symbols.
$(BUILDDIR)/%_syms.ld: $(BUILDDIR)/%.elf
	$(NM) $< | awk '$$2 ~ /^[TDRBSG]$$/ { printf "%s = 0x%s;\n", $$3, $$1 }' > $@

define OVERLAY_template
$(1)_C_SRC := $$(filter $$(or $$(OVL_C_SRC_$(1)),src/$(1)/%),$$(ALL_C_SRC))
$(1)_ASM_SRC := $$(filter-out $$(TARGET_ASM),$$(if $$(OVL_YAML_$(1)),$$(OVL_ASM_SRC_$(1)),\
	$$(shell find $$(ASM_DIR)/$(1) -name '*.s' \
	-not -path '*/nonmatchings/*' -not -path '*/matchings/*' 2> /dev/null)))
$(1)_OBJ := $$($(1)_C_SRC:%.c=$$(BUILDDIR)/%.c.o) $$($(1)_ASM_SRC:%.s=$$(BUILDDIR)/%.s.o)
C_OVL_OBJ += $$(filter %.c.o,$$($(1)_OBJ))

$$(GENDIR)/$(1).ld: .EXTRA_PREREQS :=
$$(GENDIR)/$(1).ld: $$(or $$(OVL_YAML_$(1)),config/$(1).yaml) config/symbols.txt \
		$$(or $$(OVL_SYMBOLS_$(1)),config/symbols_$(1).txt)
	$$(SPLAT) $$< --disassemble-all --make-full-disasm-for-code
	@touch $$@

$(1)_SYMS := $$(MAIN_SYMS) $$(if $$(OVL_PARENT_$(1)),$$(BUILDDIR)/$$(OVL_PARENT_$(1))_syms.ld)
$$(BUILDDIR)/$(1).elf: $$($(1)_OBJ) $$(GENDIR)/$(1).ld $$($(1)_SYMS)
	$$(LD) -nostdlib --no-check-sections -Map $$(BUILDDIR)/$(1).map \
		-T $$(GENDIR)/$(1).ld $$(addprefix -T ,$$($(1)_SYMS)) \
		-T $$(GENDIR)/undefined_syms_auto_$(1).txt \
		-T $$(GENDIR)/undefined_funcs_auto_$(1).txt -o $$@

$$(BUILDDIR)/AAA/PRO/$$(OVL_FILE_$(1)): $$(BUILDDIR)/$(1).elf
	@mkdir -p $$(dir $$@)
	$$(OBJCOPY) -O binary $$< $$@
endef
$(foreach o,$(OVERLAYS),$(eval $(call OVERLAY_template,$(o))))
OVL_BIN := $(foreach o,$(OVERLAYS),$(BUILDDIR)/AAA/PRO/$(OVL_FILE_$(o)))

all: $(EXE) $(OVL_BIN)

# Only rerun splat when its own inputs change, never for Makefile edits. splat
# leaves an unchanged linker script alone, so touch it or it reruns every time.
$(GENDIR)/main.ld: .EXTRA_PREREQS :=
$(GENDIR)/main.ld: config/main.yaml config/symbols.txt
	$(SPLAT) $< --disassemble-all --make-full-disasm-for-code
	@touch $@

generate: $(GENDIR)/main.ld $(OVERLAYS:%=$(GENDIR)/%.ld)

regenerate: reset
	$(MAKE) generate

compare: $(EXE) $(OVL_BIN)
	@sha1sum -c config/SLUS_014.36.sha1 config/overlays.sha1 config/stages.sha1

$(EXE): $(ELF)
	$(OBJCOPY) -O binary $< $@
	@truncate -s %2048 $@

$(ELF): $(OBJ) $(GENDIR)/main.ld config/undefined_syms.txt
	$(LD) $(LDFLAGS) -o $@

$(PSYQ_CC1): bin/gcc-2.7.2-psx/cc1 tools/patch_cc1.py
	$(PYTHON) tools/patch_cc1.py $< $@

$(SN_CC1): bin/gcc-2.8.1-psx/cc1 tools/sn_cc1.py
	@mkdir -p $(dir $@)
	$(PYTHON) tools/sn_cc1.py $< $@

$(filter $(BUILDDIR)/src/main/psyq/%,$(C_OBJ)): $(PSYQ_CC1)

$(BUILDDIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) -MMD -MP -MT $@ -MF $(@:.o=.d) $< -o $(@:.o=.i)
	$(CC1) $(CC1FLAGS) -o $(@:.o=.cc1.s) $(@:.o=.i)
	$(CC1_PRE) < $(@:.o=.cc1.s) | $(MASPSX) $(MASPSXFLAGS) $(MASPSX_POST) | $(PYTHON) tools/data_sizes.py > $(@:.o=.s)
	$(AS) $(ASFLAGS) -o $@ $(@:.o=.s)
	@$(OBJCOPY) --set-section-alignment .text=4 --set-section-alignment .rodata=4 $@

# gas aligns these sections to 16 bytes, psylink packed them to 4
$(BUILDDIR)/%.s.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<
	@$(OBJCOPY) --set-section-alignment .text=4 \
				--set-section-alignment .rodata=4 \
				--set-section-alignment .data=4 \
				--set-section-alignment .bss=4 $@

$(BUILDDIR)/assets/%.bin.o: assets/%.bin
	@mkdir -p $(dir $@)
	$(LD) -r -b binary -o $@ $<

expected: $(TARGET_OBJ) $(C_OBJ) $(C_OVL_OBJ)
	rm -rf $(EXPECTEDDIR)
	@mkdir -p $(EXPECTEDDIR)
	cp -r $(BUILDDIR)/$(ASM_DIR) $(EXPECTEDDIR)/$(ASM_DIR)

objdiff: expected
	$(PYTHON) tools/objdiff_generate.py

report: objdiff
	$(OBJDIFF) report generate -o $(BUILDDIR)/report.json

clean:
	rm -rf $(BUILDDIR)

reset: clean
	rm -rf $(ASM_DIR) $(EXPECTEDDIR) assets

-include $(C_OBJ:.o=.d) $(C_OVL_OBJ:.o=.d)

.PHONY: all generate regenerate compare expected objdiff report clean reset
