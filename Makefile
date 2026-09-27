.EXTRA_PREREQS := $(abspath $(lastword $(MAKEFILE_LIST)))

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
PSYQ_RERUN_CSE := libc2_puts libgpu_break libcd_bios_2 libcd_c_007 libsnd_midiread libspu_s_m_f libapi_first libsnd_ssclose libsnd_vm_pb libsnd_sscall libsnd_sstable libpad_pdresres libspu_s_m_int libc2_strcmp libc2_strcspn libsnd_vm_f libspu_s_sva libsnd_vm_stav libgpu_sys libmcrd_libmcrd libc2_prnt libetc_intr
$(PSYQ_RERUN_CSE:%=$(BUILDDIR)/src/main/psyq/%.c.o): PSYQ_CSE :=
# Our GCC 2.7.2 binary-patched into the libraries' cc1 (see tools/patch_cc1.py)
PSYQ_CC1 := $(BUILDDIR)/tools/gcc-2.7.2-psx/cc1
$(BUILDDIR)/src/main/psyq/%.c.o: CC1 := $(PSYQ_CC1)
# Some objects come from a GCC 2.8.1 without split addresses (the same objects
# are listed in dcb_decomp): it keeps the address of a global in a register
# and reaches its fields from there, never used `return` insns (tools/sn_cc1.py)
# and filled the delay slot of `j $31` itself, which tools/unfill_epilogue.py
# undoes so that ASPSX's rule applies as for the rest.
PSYQ_GCC28 := libsnd_miditime libsnd_ssvol libspu_s_n2p libspu_spu libsnd_ssopenp libspu_s_snc libspu_s_sca libsnd_cc_99 libsnd_vm_aloc1 libcd_bios_1 libcd_c_009 libsnd_vm_no1 libsnd_vm_nowon libsnd_vs_vh_2 libpad_pdresres_2 libpad_pddirres libgs_gs_108 libpad_pdtapres
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

# Most of the game is built with -G0; gfx.c reads its own small variables
# through $gp. Declare those variables static in C: maspsx then emits them
# as common symbols that resolve to the definitions in the data asm.
SDATA_LIMIT := 0
$(BUILDDIR)/src/main/system.c.o: SDATA_LIMIT := 8
$(BUILDDIR)/src/main/gfx.c.o: SDATA_LIMIT := 8
$(BUILDDIR)/src/main/sound.c.o: SDATA_LIMIT := 8
$(BUILDDIR)/src/main/game3_2.c.o: SDATA_LIMIT := 8
ASFLAGS := -EL -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0 $(INC)
LDFLAGS := -nostdlib --no-check-sections -Map $(MAP) \
	   -T $(GENDIR)/main.ld \
	   -T config/undefined_syms.txt \
	   -T $(GENDIR)/undefined_syms_auto_main.txt \
	   -T $(GENDIR)/undefined_funcs_auto_main.txt

C_SRC := $(shell find src -name '*.c' 2> /dev/null)

# Target objects for objdiff: splat's full disassembly of every C unit
TARGET_ASM := $(C_SRC:src/%.c=$(ASM_DIR)/%.s)

ASM_SRC := $(filter-out $(TARGET_ASM),$(shell find $(ASM_DIR) -name '*.s' \
	   -not -path '*/nonmatchings/*' -not -path '*/matchings/*' 2> /dev/null))

C_OBJ := $(C_SRC:%.c=$(BUILDDIR)/%.c.o)
ASM_OBJ := $(ASM_SRC:%.s=$(BUILDDIR)/%.s.o)
TARGET_OBJ := $(TARGET_ASM:%.s=$(BUILDDIR)/%.s.o)
BIN_OBJ := $(BUILDDIR)/assets/tail.bin.o
OBJ := $(C_OBJ) $(ASM_OBJ) $(BIN_OBJ)

all: $(EXE)

# Only rerun splat when its own inputs change, never for Makefile edits
$(GENDIR)/main.ld: .EXTRA_PREREQS :=
$(GENDIR)/main.ld: config/main.yaml config/symbols.txt
	$(SPLAT) $< --disassemble-all --make-full-disasm-for-code

generate: $(GENDIR)/main.ld

regenerate: reset
	$(MAKE) generate

compare: $(EXE)
	@sha1sum -c config/SLUS_014.36.sha1

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
	$(CC1_PRE) < $(@:.o=.cc1.s) | $(MASPSX) $(MASPSXFLAGS) $(MASPSX_POST) > $(@:.o=.s)
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

expected: $(TARGET_OBJ) $(C_OBJ)
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

-include $(C_OBJ:.o=.d)

.PHONY: all generate regenerate compare expected objdiff report clean reset
