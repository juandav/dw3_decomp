.EXTRA_PREREQS := $(abspath $(lastword $(MAKEFILE_LIST)))

.DEFAULT_GOAL := all

-include local.mk

# The version of the game to build. Each one has its settings in
# mk/version/<version>.mk: the executable's name, the disc, the overlays and
# the source files. The C and the assembly see VERSION_US and VERSION_EU, the
# one being built as 1 and the other as 0 (include/version.h).
VERSION ?= eu
VERSIONS := eu us
ifeq ($(filter $(VERSION),$(VERSIONS)),)
$(error unsupported VERSION $(VERSION); supported: $(VERSIONS))
endif
VERSION_UPPER := $(shell echo $(VERSION) | tr a-z A-Z)
include mk/version/$(VERSION).mk
# the tools read it too (tools/version.py)
export VERSION

TOOLCHAIN ?= mipsel-linux-gnu-

# splat configs, symbols and checksums
CONFIG_DIR := config/$(VERSION)
BUILDDIR := build/$(VERSION)
ASM_DIR := asm/$(VERSION)
ASSETS_DIR := assets/$(VERSION)
EXPECTEDDIR := expected/$(VERSION)
GENDIR := $(BUILDDIR)/generated
# the compilers the build patches, the same for every version
TOOLS_BUILDDIR := build/tools

ELF := $(BUILDDIR)/$(EXE_NAME).elf
EXE := $(BUILDDIR)/$(EXE_NAME)
MAP := $(BUILDDIR)/$(EXE_NAME).map

CPP := $(TOOLCHAIN)cpp
AS := $(TOOLCHAIN)as
LD := $(TOOLCHAIN)ld
OBJCOPY := $(TOOLCHAIN)objcopy

PYTHON := python3
SPLAT := $(PYTHON) -m splat split

# the prebuilt compilers and tools that tools/dl_deps.sh downloads; the
# Docker image keeps its own outside the repository and sets BIN_DIR
BIN_DIR ?= bin

GCC_VERSION ?= 2.8.1
CC1 ?= $(BIN_DIR)/gcc-$(GCC_VERSION)-psx/cc1

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
PSYQ_CC1 := $(TOOLS_BUILDDIR)/gcc-2.7.2-psx/cc1
$(BUILDDIR)/src/main/psyq/%.c.o: CC1 := $(PSYQ_CC1)
# Some objects come from a GCC 2.8.1 without split addresses (the same objects
# are listed in dcb_decomp): it keeps the address of a global in a register
# and reaches its fields from there, never used `return` insns (tools/sn_cc1.py)
# and filled the delay slot of `j $31` itself, which tools/unfill_epilogue.py
# undoes so that ASPSX's rule applies as for the rest.
PSYQ_GCC28 := libsnd_miditime libsnd_ssvol libspu_spu libsnd_ssopenp libspu_s_snc libspu_s_sca libsnd_cc_99 libsnd_vm_aloc1 libcd_bios_1 libcd_c_009 libsnd_vm_no1 libsnd_vm_nowon libsnd_vs_vh_2 libpad_pdresres_2 libpad_pddirres libgs_gs_108 libpad_pdtapres libcd_c_011 libc2_printf libsnd_vm_aloc2
SN_CC1 := $(TOOLS_BUILDDIR)/cc1-2.8.1-sn
CC1_PRE := cat
$(PSYQ_GCC28:%=$(BUILDDIR)/src/main/psyq/%.c.o): CC1 := $(SN_CC1)
$(PSYQ_GCC28:%=$(BUILDDIR)/src/main/psyq/%.c.o): PSYQ_CSE := -mno-split-addresses
$(PSYQ_GCC28:%=$(BUILDDIR)/src/main/psyq/%.c.o): CC1_PRE := $(PYTHON) tools/unfill_epilogue.py
$(PSYQ_GCC28:%=$(BUILDDIR)/src/main/psyq/%.c.o): $(SN_CC1)
MASPSX := $(PYTHON) external/maspsx/maspsx.py
OBJDIFF ?= $(BIN_DIR)/objdiff-cli-linux-x86_64

INC := -Iinclude -Iexternal/psyq_headers/psyq_lib47/include

# -DVERSION_<VERSION>: include/version.h turns it into VERSION_US and
# VERSION_EU, each 0 or 1, for #if; -Wundef warns about an #if on a name
# that isn't defined, such as a misspelt version
CPPFLAGS = $(INC) -undef -nostdinc -Wundef \
	    -D__GNUC__=2 -D__GNUC_MINOR__=$(word 2,$(subst ., ,$(GCC_VERSION))) -Dmips -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx \
	    -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D_LANGUAGE_C -DLANGUAGE_C \
	    -DVERSION_$(VERSION_UPPER) -DASM_DIR='"$(ASM_DIR)"'
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
# the assembly sees every version as 0 or 1 too: .if VERSION_EU
ASFLAGS := -EL -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0 $(INC) \
	   $(foreach v,$(VERSIONS),--defsym VERSION_$(shell echo $(v) | tr a-z A-Z)=$(if $(filter $(v),$(VERSION)),1,0))
# the hand-written symbols the executable links with (a version that is
# still blobs has none)
UNDEFINED_SYMS := $(wildcard $(CONFIG_DIR)/undefined_syms.txt)
LDFLAGS := -nostdlib --no-check-sections -Map $(MAP) \
	   -T $(GENDIR)/main.ld \
	   $(addprefix -T ,$(UNDEFINED_SYMS)) \
	   -T $(GENDIR)/undefined_syms_auto_main.txt \
	   -T $(GENDIR)/undefined_funcs_auto_main.txt

# C_SRC, from mk/version/<version>.mk, has every binary's C files
ALL_C_SRC := $(C_SRC)
MAIN_C_SRC := $(filter src/main/%,$(ALL_C_SRC))

# Target objects for objdiff: splat's full disassembly of every C unit (the
# executable's data files, src/main/data/, have none: objdiff_generate.py
# compares them with splat's data files)
TARGET_ASM := $(filter-out $(ASM_DIR)/main/data/%,$(ALL_C_SRC:src/%.c=$(ASM_DIR)/%.s))

ASM_SRC := $(filter-out $(TARGET_ASM),$(shell find $(ASM_DIR)/main -name '*.s' \
	   -not -path '*/nonmatchings/*' -not -path '*/matchings/*' 2> /dev/null))

C_OBJ := $(MAIN_C_SRC:%.c=$(BUILDDIR)/%.c.o)
ASM_OBJ := $(ASM_SRC:%.s=$(BUILDDIR)/%.s.o)
TARGET_OBJ := $(TARGET_ASM:%.s=$(BUILDDIR)/%.s.o)
BIN_OBJ := $(BUILDDIR)/$(ASSETS_DIR)/tail.bin.o
OBJ := $(C_OBJ) $(ASM_OBJ) $(BIN_OBJ)

# Overlays: the game's AAA/PRO/*.PRO files, loaded at 0x80082448 after the
# executable's .bss. Each one, from the version's OVERLAYS, has its own splat
# config ($(CONFIG_DIR)/<name>.yaml), sources (src/<name>, $(ASM_DIR)/<name>)
# and output ($(BUILDDIR)/AAA/PRO/<FILE>.PRO), and is linked against the
# executable's symbols (MAIN_SYMS).
$(foreach o,$(OVERLAYS),$(eval OVL_FILE_$(o) := $(shell echo $(o) | tr a-z A-Z).PRO))
OVL_PARENT_wfightmn := cardgame
OVL_PARENT_wfightts := cardgame

# The stage overlays (AAA/PRO/WSTAG###.PRO), listed in
# $(CONFIG_DIR)/stages.txt, load on top of FIELDSTG. Their splat configs are
# made by tools/stage_yaml.py and their sources are src/stages/<name>.c and
# $(ASM_DIR)/stages/.
STAGES := $(shell awk '!/^\#/ && NF { print tolower($$1) }' $(CONFIG_DIR)/stages.txt)
OVERLAYS += $(STAGES)
$(foreach s,$(STAGES),\
	$(eval OVL_FILE_$(s) := $(shell echo $(s) | tr a-z A-Z).PRO)\
	$(eval OVL_PARENT_$(s) := fieldstg)\
	$(eval OVL_YAML_$(s) := $(GENDIR)/stages/$(s).yaml)\
	$(eval OVL_C_SRC_$(s) := src/stages/$(s).c)\
	$(eval OVL_ASM_SRC_$(s) := $(wildcard $(ASM_DIR)/stages/data/$(s).*.s $(ASM_DIR)/stages/data/$(s).s $(ASM_DIR)/stages/data/$(s)_end.s $(ASM_DIR)/stages/$(s).s))\
	$(eval OVL_SYMBOLS_$(s) := $(wildcard $(CONFIG_DIR)/symbols_fieldstg.txt $(CONFIG_DIR)/stages/$(s).txt)))

$(GENDIR)/stages/%.yaml: $(CONFIG_DIR)/stages.txt tools/stage_yaml.py tools/version.py mk/version/$(VERSION).mk
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
$$(GENDIR)/$(1).ld: $$(or $$(OVL_YAML_$(1)),$$(CONFIG_DIR)/$(1).yaml) $$(CONFIG_DIR)/symbols.txt \
		$$(or $$(OVL_SYMBOLS_$(1)),$$(wildcard $$(CONFIG_DIR)/symbols_$(1).txt))
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
$(GENDIR)/main.ld: $(CONFIG_DIR)/main.yaml $(CONFIG_DIR)/symbols.txt
	$(SPLAT) $< --disassemble-all --make-full-disasm-for-code
	@touch $@

generate: $(GENDIR)/main.ld $(OVERLAYS:%=$(GENDIR)/%.ld)

regenerate: reset
	$(MAKE) generate

compare: $(EXE) $(OVL_BIN)
	@sha1sum -c $(CONFIG_DIR)/$(EXE_NAME).sha1 $(CONFIG_DIR)/overlays.sha1 $(CONFIG_DIR)/stages.sha1

$(EXE): $(ELF)
	$(OBJCOPY) -O binary $< $@
	@truncate -s %2048 $@

$(ELF): $(OBJ) $(GENDIR)/main.ld $(UNDEFINED_SYMS)
	$(LD) $(LDFLAGS) -o $@

$(PSYQ_CC1): $(BIN_DIR)/gcc-2.7.2-psx/cc1 tools/patch_cc1.py
	$(PYTHON) tools/patch_cc1.py $< $@

$(SN_CC1): $(BIN_DIR)/gcc-2.8.1-psx/cc1 tools/sn_cc1.py
	@mkdir -p $(dir $@)
	$(PYTHON) tools/sn_cc1.py $< $@

$(filter $(BUILDDIR)/src/main/psyq/%,$(C_OBJ)): $(PSYQ_CC1)

# The executable's .bss in C: maspsx turns its commons into definitions in
# order in .bss when they aren't kept as .comm
$(BUILDDIR)/src/main/data/game_bss.c.o: MASPSXFLAGS := $(filter-out --use-comm-section,$(MASPSXFLAGS))

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

$(BUILDDIR)/$(ASSETS_DIR)/%.bin.o: $(ASSETS_DIR)/%.bin
	@mkdir -p $(dir $@)
	$(LD) -r -b binary -o $@ $<

expected: $(TARGET_OBJ) $(C_OBJ) $(C_OVL_OBJ)
	rm -rf $(EXPECTEDDIR)
	@mkdir -p $(EXPECTEDDIR)
	cp -r $(BUILDDIR)/$(ASM_DIR) $(EXPECTEDDIR)/asm

objdiff: expected
	$(PYTHON) tools/objdiff_generate.py

report: objdiff
	$(OBJDIFF) report generate -o $(BUILDDIR)/report.json

clean:
	rm -rf $(BUILDDIR) $(TOOLS_BUILDDIR)

reset: clean
	rm -rf $(ASM_DIR) $(EXPECTEDDIR) $(ASSETS_DIR)

-include $(C_OBJ:.o=.d) $(C_OVL_OBJ:.o=.d)

.PHONY: all generate regenerate compare expected objdiff report clean reset
