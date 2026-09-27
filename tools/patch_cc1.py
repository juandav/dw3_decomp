#!/usr/bin/env python3
"""Binary-patch bin/gcc-2.7.2-psx/cc1 into the cc1 the PsyQ libraries were built with.

usage: tools/patch_cc1.py [in out]   (default: bin/gcc-2.7.2-psx/cc1 ->
                                       build/tools/gcc-2.7.2-psx/cc1)

Differences between our GCC 2.7.2 build and the compiler of the PsyQ 4.7
libraries (which also need -mhard-float, see FLOAT_ABI in the Makefile).
1 and 2 show up together: a short loaded once and used both sign-extended
and raw (`lh` + `lhu` of the same field in the ROM), and a bogus
`addiu $sp,-8/-16` frame (`.frame ... vars=8/16`) with no stack accesses.

1. try_combine: when three insns (load HI, sll 16, sra 16) combine into a
   sign-extending load while the HImode load is still needed, ours rewrites the
   second load as a SUBREG of the extended value; the ROM keeps both loads
   (the "two independent SETs" split). The SIGN_EXTEND special case is
   skipped here.
2. regclass: the combined-away shift temporaries keep stale reference counts.
   With no costs recorded their preferred class came out as ST_REGS (FP
   condition codes, no SImode), so global.c couldn't place them and reload
   gave them stack slots. The best-class search now starts below ST_REGS,
   which the PsyQ code (no floating point) never uses.
3. reorg's mark_target_live_regs stops its forward scan at a conditional
   jump before looking at the jump's own delay slot, so a register set there
   (`beqz v1,L; move v0,zero`) still counts as live and a branch just before
   can't take `li v0,K` from its target (libpad func_8002184C). The patched
   scan first records what that jump and its delay slot use and set (they
   run on both paths), then stops. Returns and other jumps are unchanged,
   and so is a conditional jump back to an earlier label (its label's UID is
   lower than the jump's): __fixsfsi's first `beqz` keeps its nop instead of
   stealing `move v0,zero` from the `j` at its target, because the
   fallthrough's `beqz v1,<earlier label>; negu v0,a2` still leaves v0 live.
   func_80066384 and GsSortObject4 need the forward case.
4. reorg's fill_simple_delay_slots never fills the slot of an unconditional
   jump from its target (2.7.2 only fills it from the insns before the jump);
   the ROM does, like GCC 2.8: `j L; <first insn at L>` with the jump
   redirected past it (_SsSetControlChange's four `j default; sra a0,a0,16`,
   the early `move v0,zero` of SsUtKeyOff, _SsVmInit's branch layout).
5. find_best_addr: a `reg + const_int` address (`4(p)` with p holding &sym)
   stays as it is instead of being folded into the constant `sym+4`.
6. alter_reg: a pseudo spilled to the stack gets a slot aligned to its own
   mode (4 bytes for SImode) instead of BIGGEST_ALIGNMENT (8), like GCC 2.8's
   `inherent_size == total_size ? 0 : -1`. Two spilled pseudos then sit at
   0x5C/0x60 instead of 0x60/0x68 (libmcrd MemCardGetDirentry's frame).
Patches 7-12 come from dcb_decomp, which links the same PsyQ 4.7 libraries
(the function names in their notes are dcb's).

7. mark_target_live_regs: its forward scan follows a simple jump to the
   label itself (GCC 2.8), so the label kills the registers a REG_DEAD note
   left pending before the jump. A branch can then take an insn that sets
   one of its own inputs from its target (prnt: `bne v1,v0,L; sltiu v0,..`).
8. expand_increment: a post-increment whose value is used, of a MEM that the
   add insn can't take (`if (count++ > N)` on a global), goes through
   GCC 2.8's queue path: the address goes to a register (`la v0,sym`), the old
   value is loaded into a temp, and the add and the store are queued
   (`lw v1,0(v0); move a0,v1; addiu v1,v1,1; ... sw v1,0(v0)`, trapIntr).
9. cse's COST macro uses GCC 2.8's notreg_cost: a lowpart SUBREG of a wider
   integer register costs what the register does, not rtx_cost * 2, so cse
   keeps `(subreg:HI (reg:SI n) 0)` over an equal HImode pseudo and a short
   field is loaded twice, `lh` for a compare and `lhu` for its raw value
   (libgpu func_80065C54/func_80065CEC).
10. local-alloc ties the register holding a called function pointer to the
   call's result register ($v0), as with GCC 2.8's mips.md, whose call
   patterns take the address as a register operand (libgpu func_800649E8).
11. combine re-enables volatile MEMs in the recognizer when it ends, as
   GCC 2.8 does, so sched1 can recognize and schedule insns with volatile
   MEMs (trapIntr's loop exit test).
12. -fforce-mem no longer loads a MEM into a register before extending it
   (GCC 2.8), so `(int)s.byte` is one `zero_extend (mem)` that cse doesn't
   replace with a value just stored there (SetGraphDebug reloads D.level).

13. try_combine: a three-insn combination whose I1 is a still-needed
    `sra 16` (sign extension) is refused instead of keeping I1 alongside:
    `(s & 0xFF00) >> 8` stays `andi; sra 8` like the ROM (and GCC 2.8), not
    `srl 24` plus a dead pseudo with a stack slot (libsnd vm functions).

14. reorg's mark_target_live_regs is GCC 2.8.1's (tools/cc1_mtlr28.c, bytes
    from tools/cc1_mtlr28.sh): its forward scan follows both paths of one
    conditional jump, so a register set before use on both paths is dead at
    the target (prnt: `beqz v0,exit; sll v0,s0,2` where the exit path's
    `bgez` and `j` both reach code that sets v0). It supersedes 3 and 7.

15. global-alloc's prune_preferences checks conflicts in both directions
    (GCC 2.8), so a pseudo doesn't take a register that a conflicting
    lower-priority pseudo prefers (dcb's _spu_note2pitch; dcb_decomp 92b3678).

The whole build matches with the patched cc1 (none of the functions that
already matched changes).
"""
import os
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
STOCK = f"{ROOT}/bin/gcc-2.7.2-psx/cc1"
PATCHED = f"{ROOT}/build/tools/gcc-2.7.2-psx/cc1"


def patch(src, dst):
    d = bytearray(open(src, "rb").read())
    phoff, = struct.unpack_from("<I", d, 0x1C)
    phentsize, phnum = struct.unpack_from("<HH", d, 0x2A)
    segs, phidx = [], []
    for i in range(phnum):
        t, off, va, _, fsz = struct.unpack_from("<5I", d, phoff + i * phentsize)
        if t == 1:
            segs.append((va, off, fsz))
            phidx.append(i)

    def fo(va):
        for v, o, s in segs:
            if v <= va < v + s:
                return va - v + o
        raise ValueError(hex(va))

    def put(va, old, new):
        o = fo(va)
        if d[o:o + len(old)] != bytes(old):
            sys.exit(f"patch_cc1: unexpected bytes at {va:#x}: {d[o:o + len(old)].hex()}")
        d[o:o + len(new)] = new

    # 1. try_combine+9186: `jne` after `cmp $SIGN_EXTEND` -> `jmp` to the same target
    va = 0x08128E9F
    o = fo(va)
    rel = int.from_bytes(d[o + 2:o + 6], "little", signed=True)
    put(va, b"\x0f\x85" + d[o + 2:o + 6],
        b"\xe9" + (rel + 1).to_bytes(4, "little", signed=True) + b"\x90")
    # 2. regclass+2986: `for (class = ALL_REGS - 1; ...)` -> start at MD_REGS (6)
    put(0x0814313C, b"\xbe\x07\x00\x00\x00", b"\xbe\x06\x00\x00\x00")

    # Patches 3 and 4 add code after the end of the text segment (the rest of
    # its last page is zero padding in the file) and grow the segment over it.
    ti = next(i for i, (v, o, s) in enumerate(segs) if v <= 0x08172000 < v + s)
    tva, toff, tsz = segs[ti]
    end = [tva + tsz]

    def append(build):
        """Place the code build(cave, jump, code) produces after the segment."""
        cave = (end[0] + 15) & ~15
        code = bytearray()

        def jump(opcode, target):  # opcode + rel32 to target
            code.extend(opcode)
            code.extend((target - (cave + len(code) + 4)).to_bytes(4, "little", signed=True))

        build(code, jump)
        o = cave - tva + toff
        if d[o:o + len(code)] != bytes(len(code)):
            sys.exit("patch_cc1: no room after the text segment")
        d[o:o + len(code)] = code
        end[0] = cave + len(code)
        for field in (16, 20):  # p_filesz, p_memsz
            struct.pack_into("<I", d, phoff + phidx[ti] * phentsize + field, end[0] - tva)
        return cave

    # 3. mark_target_live_regs+3810: the `jne` that leaves the forward scan for
    # a jump that is neither simple nor a return goes to new code: for a
    # conditional jump (SET of pc from IF_THEN_ELSE) to a label with a higher
    # UID than the jump (a forward jump) set next = 0 and run the
    # loop's marking code (+3873), which then ends the scan; anything else
    # leaves it as before (+4121).
    def scan_cond_jump(code, jump):
        code += b"\x8b\x45\x88"                    # mov -0x78(%ebp),%eax  (this_jump_insn)
        code += b"\x8b\x40\x10"                    # mov 0x10(%eax),%eax   (PATTERN)
        code += b"\x66\x83\x38\x29"                # cmpw $SET,(%eax)
        jump(b"\x0f\x85", 0x081725A6)             # jne break
        code += b"\x8b\x40\x08"                    # mov 0x8(%eax),%eax    (SET_SRC)
        code += b"\x66\x83\x38\x3e"                # cmpw $IF_THEN_ELSE,(%eax)
        jump(b"\x0f\x85", 0x081725A6)             # jne break
        code += b"\x8b\x45\x88"                    # mov this_jump_insn,%eax
        code += b"\x8b\x50\x20"                    # mov JUMP_LABEL,%edx
        code += b"\x85\xd2"                        # test %edx,%edx
        jump(b"\x0f\x84", 0x081725A6)             # je break
        code += b"\x8b\x52\x04\x3b\x50\x04"        # mov uid(label),%edx; cmp uid(jump),%edx
        jump(b"\x0f\x8c", 0x081725A6)             # jl break (backward jump)
        code += b"\xc7\x85\x5c\xff\xff\xff" + bytes(4)  # movl $0,-0xa4(%ebp)  (next = 0)
        jump(b"\xe9", 0x081724AE)                  # jmp to the marking code

    cave = append(scan_cond_jump)
    o = fo(0x0817246F)
    put(0x0817246F, b"\x0f\x85" + d[o + 2:o + 6],
        b"\x0f\x85" + (cave - (0x0817246F + 6)).to_bytes(4, "little", signed=True))

    # 4. fill_simple_delay_slots+2819 (`if (delay_list)` before
    # emit_delay_sequence): first, as GCC 2.8 does, fill an empty slot of an
    # unconditional jump from its target:
    #   if (GET_CODE (insn) == JUMP_INSN && slots_filled != slots_to_fill
    #       && simplejump_p (insn))
    #     delay_list = fill_slots_from_thread (insn, const_true_rtx,
    #         next_active_insn (JUMP_LABEL (insn)), 0, 1, 1,
    #         own_thread_p (JUMP_LABEL (insn), JUMP_LABEL (insn), 0), 0,
    #         slots_to_fill, &slots_filled);
    # Locals: insn -0x84, delay_list -0x78, slots_filled -0x80, slots_to_fill -0x8c.
    def fill_jump_from_target(code, jump):
        skip = []

        def jcc(opcode):  # forward branch to `done`, fixed up below
            code.extend(opcode)
            skip.append(len(code))
            code.extend(bytes(4))

        code += b"\x8b\x85\x7c\xff\xff\xff"        # mov -0x84(%ebp),%eax  (insn)
        code += b"\x66\x83\x38\x1c"                # cmpw $JUMP_INSN,(%eax)
        jcc(b"\x0f\x85")
        code += b"\x8b\x45\x80"                    # mov -0x80(%ebp),%eax
        code += b"\x3b\x85\x74\xff\xff\xff"        # cmp -0x8c(%ebp),%eax
        jcc(b"\x0f\x84")
        code += b"\xff\xb5\x7c\xff\xff\xff"        # push insn
        jump(b"\xe8", 0x080F6486)                  # call simplejump_p
        code += b"\x83\xc4\x04\x85\xc0"            # add $4,%esp; test %eax,%eax
        jcc(b"\x0f\x84")
        code += b"\x8b\x85\x7c\xff\xff\xff"        # mov insn,%eax
        code += b"\x8b\x40\x20"                    # mov 0x20(%eax),%eax   (JUMP_LABEL)
        code += b"\x6a\x00\x50\x50"                # push 0; push label; push label
        jump(b"\xe8", 0x08170F0F)                  # call own_thread_p
        code += b"\x83\xc4\x0c\x50"                # add $12,%esp; push own
        code += b"\x8b\x85\x7c\xff\xff\xff"        # mov insn,%eax
        code += b"\xff\x70\x20"                    # push JUMP_LABEL
        jump(b"\xe8", 0x080DBF36)                  # call next_active_insn
        code += b"\x83\xc4\x04\x59"                # add $4,%esp; pop %ecx (own)
        code += b"\x8d\x55\x80\x52"                # lea -0x80(%ebp),%edx; push (&slots_filled)
        code += b"\xff\xb5\x74\xff\xff\xff"        # push slots_to_fill
        code += b"\x6a\x00\x51"                    # push 0 (own_opposite); push own
        code += b"\x6a\x01\x6a\x01\x6a\x00\x50"    # push 1; push 1; push 0; push thread
        code += b"\xff\x35" + (0x082D3980).to_bytes(4, "little")  # push const_true_rtx
        code += b"\xff\xb5\x7c\xff\xff\xff"        # push insn
        jump(b"\xe8", 0x08173610)                  # call fill_slots_from_thread
        code += b"\x83\xc4\x28\x89\x45\x88"        # add $40,%esp; mov %eax,delay_list
        for f in skip:
            code[f:f + 4] = (len(code) - (f + 4)).to_bytes(4, "little", signed=True)
        code += b"\x83\x7d\x88\x00"                # cmpl $0,delay_list  (the replaced insns)
        jump(b"\x0f\x84", 0x08173331)             # je
        jump(b"\xe9", 0x081732EE)                  # jmp back

    cave = append(fill_jump_from_target)
    put(0x081732E8, bytes.fromhex("837d88007443"),
        b"\xe9" + (cave - (0x081732E8 + 5)).to_bytes(4, "little", signed=True) + b"\x90")

    # 5. find_best_addr: don't fold a `reg + const_int` address (e.g. `4(p)`
    #    with p a pseudo holding &sym) into a constant `sym+4`. GCC 2.8 only
    #    keeps a folded address when it is cheaper, and a small reg+offset is
    #    already the cheapest; the PsyQ cc1 behaved like that (libmcrd/libgs
    #    `addiu v1,s0,-4; sw v0,4(v1)`). The test `code == REG` before the
    #    fold jumps to a cave (the body of `trace`, only used by -mdebugb)
    #    that also skips PLUS with a CONST_INT second operand.
    cave, back_fold, back_skip = 0x081C96DA, 0x080FD1F3, 0x080FD221
    code = bytearray(
        b"\x66\x83\xf8\x34"      # cmp ax, REG
        b"\x74\x12"                # je skip
        b"\x66\x83\xf8\x41"      # cmp ax, PLUS
        b"\x75\x11"                # jne fold
        b"\x8b\x4d\xac"           # mov ecx, [ebp-0x54]   (addr)
        b"\x8b\x49\x08"           # mov ecx, [ecx+8]      (XEXP (addr, 1))
        b"\x66\x83\x39\x2f"      # cmp word [ecx], CONST_INT
        b"\x75\x05"                # jne fold
    )
    code += b"\xe9" + (back_skip - (cave + len(code) + 5)).to_bytes(4, "little", signed=True)
    code += b"\xe9" + (back_fold - (cave + len(code) + 5)).to_bytes(4, "little", signed=True)
    o = fo(cave)
    if d[o:o + 4] != b"\xf3\x0f\x1e\xfb":
        sys.exit("patch_cc1: unexpected bytes at trace")
    d[o:o + len(code)] = code
    site = 0x080FD1ED
    put(site, b"\x66\x83\xf8\x34\x74\x2e",
        b"\xe9" + (cave - (site + 5)).to_bytes(4, "little", signed=True) + b"\x90")

    # 6. alter_reg+348: `assign_stack_local (mode, total_size, -1)` for a
    #    pseudo with no slot to reuse -> align 0 (the mode's alignment).
    put(0x08161CD9, b"\x6a\xff", b"\x6a\x00")

    # 7. mark_target_live_regs+3822: the forward scan follows a simple jump
    #    to `JUMP_LABEL` itself, as GCC 2.8's find_dead_or_set_registers does,
    #    not to `next_active_insn (JUMP_LABEL)`: the label then kills the
    #    registers left pending dead (REG_DEAD) before the jump. Drop the call
    #    and keep JUMP_LABEL in %eax.
    o = fo(0x0817247B)
    put(0x0817247B, b"\x83\xec\x0c\x50\xe8" + d[o + 5:o + 9] + b"\x83\xc4\x10", b"\x90" * 12)

    # 8. expand_increment+1111 (the post-increment fallback, reached when the
    #    queued add can't take OP0): as GCC 2.8, for a MEM with an add insn
    #      addr = general_operand (XEXP (op0, 0), mode)
    #             ? force_reg (Pmode, XEXP (op0, 0)) : copy_to_reg (XEXP (op0, 0));
    #      op0 = change_address (op0, VOIDmode, addr);
    #      temp = force_reg (GET_MODE (op0), op0);
    #      if (! insn_operand_predicate[icode][2] (op1, mode))
    #        op1 = force_reg (mode, op1);
    #      enqueue_insn (op0, gen_move_insn (op0, temp));
    #      return enqueue_insn (temp, GEN_FCN (icode) (temp, temp, op1));
    #    Locals: op0 %edi, post 0xc(%ebp), mode -0x24, icode -0x1c, op1 -0x3c.
    #    The code goes over bc_expand_expr (only used with -fbytecode), since
    #    the page after the text segment is full.
    def increment_mem(code, jump):
        def short(opcode):  # 8-bit forward branch, fixed up by `here`
            code.extend(opcode + b"\x00")
            return len(code)

        def here(at):
            code[at - 1] = len(code) - at

        code += b"\x83\x7d\x0c\x00"                # cmpl $0,post  (the replaced insns)
        jump(b"\x0f\x84", 0x080AE8EE)             # je (preincrement)
        code += b"\x81\x7d\xe4\x51\x01\x00\x00"    # cmpl $CODE_FOR_nothing,icode
        jump(b"\x0f\x84", 0x080AE8DB)             # je back
        code += b"\x66\x83\x3f\x39"                # cmpw $MEM,(%edi)
        jump(b"\x0f\x85", 0x080AE8DB)             # jne back
        code += b"\xff\x75\xdc\xff\x77\x04"        # push mode; push XEXP (op0, 0)
        jump(b"\xe8", 0x08184AD9)                  # call general_operand
        code += b"\x83\xc4\x08\x8b\x57\x04\x85\xc0"  # add $8,%esp; mov 4(%edi),%edx; test
        copy = short(b"\x74")                      # je copy
        code += b"\x52\x6a\x04"                    # push addr; push $SImode
        jump(b"\xe8", 0x080C276E)                  # call force_reg
        code += b"\x83\xc4\x08"
        have = short(b"\xeb")                      # jmp have
        here(copy)
        code += b"\x52"                            # push addr
        jump(b"\xe8", 0x080C2639)                  # call copy_to_reg
        code += b"\x83\xc4\x04"
        here(have)
        code += b"\x50\x6a\x00\x57"                # push addr; push $VOIDmode; push op0
        jump(b"\xe8", 0x080DB2AB)                  # call change_address
        code += b"\x83\xc4\x0c\x89\xc7"            # add $12,%esp; mov %eax,%edi
        code += b"\x57\x0f\xb6\x47\x02\x50"        # push op0; push GET_MODE (op0)
        jump(b"\xe8", 0x080C276E)                  # call force_reg
        code += b"\x83\xc4\x08\x89\xc6"            # add $8,%esp; mov %eax,%esi  (temp)
        code += b"\x8b\x55\xe4\x8d\x04\x92"        # mov icode,%edx; lea (%edx,%edx,4),%eax
        code += b"\x8b\x04\xc5" + (0x082B7388).to_bytes(4, "little")  # insn_operand_predicate[icode][2]
        code += b"\xff\x75\xdc\xff\x75\xc4\xff\xd0"  # push mode; push op1; call *%eax
        code += b"\x83\xc4\x08\x85\xc0"            # add $8,%esp; test
        ok = short(b"\x75")                        # jne ok
        code += b"\xff\x75\xc4\xff\x75\xdc"        # push op1; push mode
        jump(b"\xe8", 0x080C276E)                  # call force_reg
        code += b"\x83\xc4\x08\x89\x45\xc4"        # add $8,%esp; mov %eax,op1
        here(ok)
        code += b"\x56\x57"                        # push temp; push op0
        jump(b"\xe8", 0x080C9ADD)                  # call gen_move_insn
        code += b"\x83\xc4\x08\x50\x57"            # add $8,%esp; push %eax; push op0
        jump(b"\xe8", 0x0809ECB6)                  # call enqueue_insn
        code += b"\x83\xc4\x08\x8b\x55\xe4"        # add $8,%esp; mov icode,%edx
        code += b"\x8b\x04\x95" + (0x082B6E20).to_bytes(4, "little")  # insn_gen_function[icode]
        code += b"\xff\x75\xc4\x56\x56\xff\xd0"    # push op1; push temp; push temp; call *%eax
        code += b"\x83\xc4\x0c\x50\x56"            # add $12,%esp; push %eax; push temp
        jump(b"\xe8", 0x0809ECB6)                  # call enqueue_insn
        code += b"\x83\xc4\x08"                    # add $8,%esp
        jump(b"\xe9", 0x080AE93F)                  # jmp to the epilogue (returns %eax)

    cave = 0x080AAEA3
    code = bytearray()

    def jump(opcode, target):
        code.extend(opcode)
        code.extend((target - (cave + len(code) + 4)).to_bytes(4, "little", signed=True))

    increment_mem(code, jump)
    if len(code) > 0x9B5:
        sys.exit("patch_cc1: increment_mem doesn't fit")
    put(cave, b"\xf3\x0f\x1e\xfb", code)
    put(0x080AE8D5, bytes.fromhex("837d0c007413"),
        b"\xe9" + (cave - (0x080AE8D5 + 5)).to_bytes(4, "little", signed=True) + b"\x90")

    # 9. cse's COST: GCC 2.8's notreg_cost. A lowpart SUBREG of a wider
    #    integer REG costs what the REG does (0 cheap, 1 pseudo, 2 hard)
    #    instead of rtx_cost (x, SET) * 2 = 4, so cse_insn takes it over an
    #    equivalent pseudo, e.g. `(subreg:HI (reg:SI 73) 0)` for a short
    #    that was loaded sign-extended, and keeps both loads of the field
    #    (libgpu func_80065C54: `lh` for the compare, `lhu` for the value).
    #    New function after increment_mem; the rtx_cost calls of the COST
    #    macro in cse.c go to it and their `* 2` becomes a plain move.
    def notreg_cost(code, jump):
        fix = {}

        def br(opcode, label):  # forward branch to a label below (rel8, or rel32 for 0f 8x)
            code.extend(opcode + bytes(1 if len(opcode) == 1 else 4))
            fix.setdefault(label, []).append((len(code), len(opcode)))

        def label(name):
            for at, n in fix.pop(name, []):
                if n == 1:
                    assert len(code) - at < 0x80
                    code[at - 1] = len(code) - at
                else:
                    code[at - 4:at] = (len(code) - at).to_bytes(4, "little")

        code += b"\x53"                            # push %ebx
        code += b"\x8b\x44\x24\x08"                # mov 8(%esp),%eax      (x)
        code += b"\x66\x83\x38\x36"                # cmpw $SUBREG,(%eax)
        br(b"\x0f\x85", "other")
        code += b"\x8b\x48\x04"                    # mov 4(%eax),%ecx      (SUBREG_REG)
        code += b"\x66\x83\x39\x34"                # cmpw $REG,(%ecx)
        br(b"\x0f\x85", "other")
        code += b"\x0f\xb6\x50\x02"                # movzbl 2(%eax),%edx   (GET_MODE (x))
        code += b"\x0f\xb6\x59\x02"                # movzbl 2(%ecx),%ebx   (its REG's mode)
        mode_class, mode_size = (0x082BCA80).to_bytes(4, "little"), (0x082BCB00).to_bytes(4, "little")
        code += b"\x83\x3c\x95" + mode_class + b"\x01"  # cmpl $MODE_INT,mode_class(,%edx,4)
        br(b"\x0f\x85", "other")
        code += b"\x83\x3c\x9d" + mode_class + b"\x01"  # cmpl $MODE_INT,mode_class(,%ebx,4)
        br(b"\x0f\x85", "other")
        code += b"\x8b\x14\x95" + mode_size        # mov mode_size(,%edx,4),%edx
        code += b"\x3b\x14\x9d" + mode_size        # cmp mode_size(,%ebx,4),%edx
        br(b"\x0f\x8d", "other")                   # jge (not narrower)
        code += b"\x50"                            # push x
        jump(b"\xe8", 0x080DAA26)                  # call subreg_lowpart_p
        code += b"\x83\xc4\x04\x85\xc0"            # add $4,%esp; test %eax,%eax
        br(b"\x0f\x84", "other")
        # TRULY_NOOP_TRUNCATION is 1 without -mips3. CHEAP_REG, as insert has it:
        code += b"\x8b\x44\x24\x08\x8b\x48\x04"    # mov x,%eax; mov 4(%eax),%ecx
        code += b"\x8b\x51\x04"                    # mov 4(%ecx),%edx      (REGNO)
        code += b"\xf6\x41\x03\x08"                # testb $8,3(%ecx)      (REG_USERVAR_P)
        br(b"\x74", "fixed")
        code += b"\x83\xfa\x43"                    # cmp $FIRST_PSEUDO_REGISTER-1,%edx
        br(b"\x7e", "zero")
        label("fixed")
        code += b"\x83\xfa\x1e"                    # cmp $FRAME_POINTER_REGNUM,%edx
        br(b"\x74", "zero")
        code += b"\x83\xfa\x1d"                    # cmp $STACK_POINTER_REGNUM,%edx
        br(b"\x74", "zero")
        code += b"\x85\xd2"                        # test %edx,%edx        (ARG_POINTER_REGNUM)
        br(b"\x74", "zero")
        code += b"\x83\xfa\x43"                    # cmp $FIRST_PSEUDO_REGISTER-1,%edx
        br(b"\x7e", "hard")
        code += b"\x83\xfa\x47"                    # cmp $LAST_VIRTUAL_REGISTER,%edx
        br(b"\x7e", "zero")
        code += b"\xb8\x01\x00\x00\x00\x5b\xc3"    # pseudo: return 1
        label("hard")
        code += b"\x80\xba" + (0x082D42E0).to_bytes(4, "little") + b"\x00"  # cmpb $0,fixed_regs(%edx)
        br(b"\x75", "class")
        code += b"\x80\xba" + (0x082D4220).to_bytes(4, "little") + b"\x00"  # cmpb $0,global_regs(%edx)
        br(b"\x74", "two")
        label("class")
        code += b"\x83\x3c\x95" + (0x082BE500).to_bytes(4, "little") + b"\x00"  # REGNO_REG_CLASS != NO_REGS
        br(b"\x75", "zero")
        label("two")
        code += b"\xb8\x02\x00\x00\x00\x5b\xc3"    # return 2
        label("zero")
        code += b"\x31\xc0\x5b\xc3"                # return 0
        label("other")
        code += b"\xff\x74\x24\x0c\xff\x74\x24\x0c"  # push outer_code; push x
        jump(b"\xe8", 0x080F8E96)                  # call rtx_cost
        code += b"\x83\xc4\x08\x01\xc0\x5b\xc3"    # add $8,%esp; add %eax,%eax; pop %ebx; ret
        assert not fix

    # Patches 9 and 10 go in the rest of bc_expand_expr, after increment_mem.
    free = [cave + len(code)]

    def in_bc(build):
        start = (free[0] + 15) & ~15
        code = bytearray()

        def jump(opcode, target):
            code.extend(opcode)
            code.extend((target - (start + len(code) + 4)).to_bytes(4, "little", signed=True))

        build(code, jump)
        if start + len(code) > 0x080AAEA3 + 0x9B5:
            sys.exit("patch_cc1: no room left in bc_expand_expr")
        d[fo(start):fo(start) + len(code)] = code
        free[0] = start + len(code)
        return start

    start = in_bc(notreg_cost)
    for site, double, move in (
            (0x080FA621, b"\x01\xc0", b"\x89\xc0"),          # insert
            (0x080FD7E7, b"\x01\xc0", b"\x89\xc0"),          # find_best_addr
            (0x080FD9DC, b"\x01\xc0", b"\x89\xc0"),
            (0x080FDB0B, b"\x01\xc0", b"\x89\xc0"),
            (0x08103FB1, b"\x01\xc0", b"\x89\xc0"),          # fold_rtx
            (0x081047B0, b"\x8d\x1c\x00", b"\x89\xc3\x90"),  # (lea (%eax,%eax),%ebx)
            (0x081048F4, b"\x01\xc0", b"\x89\xc0"),
            (0x08104C54, b"\x8d\x1c\x00", b"\x89\xc3\x90"),
            (0x08104DDD, b"\x01\xc0", b"\x89\xc0"),
            (0x08108B72, b"\x01\xc0", b"\x89\xc0"),          # cse_insn
            (0x08108CF4, b"\x01\xc0", b"\x89\xc0"),
            (0x08108E2C, b"\x01\xc0", b"\x89\xc0"),
            (0x08108FAE, b"\x01\xc0", b"\x89\xc0"),
            (0x08109759, b"\x8d\x1c\x00", b"\x89\xc3\x90"),
            (0x08109857, b"\x01\xc0", b"\x89\xc0"),
            (0x0810C394, b"\x8d\x34\x00", b"\x89\xc6\x90"),  # cse_set_around_loop
            (0x0810C4D9, b"\x01\xc0", b"\x89\xc0")):
        put(site, b"\xe8" + (0x080F8E96 - (site + 5)).to_bytes(4, "little", signed=True)
            + b"\x83\xc4\x10" + double,
            b"\xe8" + (start - (site + 5)).to_bytes(4, "little", signed=True)
            + b"\x83\xc4\x10" + move)

    # 10. block_alloc+1015, where an operand is tied to the output operand 0:
    #    GCC 2.8's mips.md matches the address of a call as
    #    `(call (mem (match_operand 1 "call_insn_operand" "ri")) ...)`, so the
    #    register holding a function pointer is an operand that dies in the
    #    call_value insn and local-alloc suggests $v0 (its output) for it; ours
    #    has the whole MEM as operand 1 ("m") and doesn't. For a CALL_INSN,
    #    take the register inside that MEM, as for a 'p' operand (libgpu
    #    func_800649E8: `lh v1,6(s0); lw v0,D_80076754; ... jalr v0`).
    #    Locals: r1 -0x60, insn -0x5c.
    def tie_call_address(code, jump):
        code += b"\x0f\xb6\x00\x3c\x70"            # movzbl (%eax),%eax; cmp $'p',%al (replaced)
        jump(b"\x0f\x84", 0x08147A53)             # je (the PLUS/MULT loop)
        code += b"\x8b\x45\xa4"                    # mov -0x5c(%ebp),%eax  (insn)
        code += b"\x66\x83\x38\x1d"                # cmpw $CALL_INSN,(%eax)
        jump(b"\x0f\x85", 0x08147A68)
        code += b"\x8b\x45\xa0"                    # mov -0x60(%ebp),%eax  (r1)
        code += b"\x66\x83\x38\x39"                # cmpw $MEM,(%eax)
        jump(b"\x0f\x85", 0x08147A68)
        code += b"\x8b\x40\x04\x89\x45\xa0"        # r1 = XEXP (r1, 0)
        jump(b"\xe9", 0x08147A68)

    start = in_bc(tie_call_address)
    put(0x08147A41, b"\x0f\xb6\x00\x3c\x70",
        b"\xe9" + (start - (0x08147A41 + 5)).to_bytes(4, "little", signed=True))

    # 11. combine_instructions+2332, at its end: call init_recog () first, as
    #    GCC 2.8's combine does ("Make recognizer allow volatile MEMs again").
    #    Ours leaves volatile_ok = 0 until regclass, so sched1 can't recognize
    #    insns with volatile MEMs and doesn't schedule them (trapIntr's loop
    #    exit test: `lw a0,D_80070AAC; lhu v1,enabled; lw v0,D_80070AB0; lhu;
    #    lhu` like the copy at the loop entry).
    site = 0x08125D77
    replaced = bytes.fromhex("c783c09c000000000000")  # movl $0,0x9cc0(%ebx)

    def recog_volatile(code, jump):
        jump(b"\xe8", 0x0818390F)                  # call init_recog
        code += replaced
        jump(b"\xe9", site + len(replaced))

    start = in_bc(recog_volatile)
    put(site, replaced, b"\xe9" + (start - (site + 5)).to_bytes(4, "little", signed=True) + b"\x90" * 5)
    # 12. -fforce-mem doesn't copy a MEM into a register before extending it,
    #    as in GCC 2.8: expand_expr's NOP_EXPR (+10954) drops its
    #    `if (flag_force_mem && GET_CODE (op0) == MEM) op0 = copy_to_reg (op0)`
    #    and emit_unop_insn (+93) skips force_not_mem for SIGN_EXTEND and
    #    ZERO_EXTEND ("extension from memory is often done specially on RISC
    #    machines"). `(int)s.byte` then expands to `(zero_extend:SI (mem:QI))`
    #    instead of a QImode load and an extension of that register, and cse
    #    doesn't replace it with a value stored before: SetGraphDebug reloads
    #    D.level for the printf.
    put(0x080A7DF5, b"\x74\x21", b"\xeb\x21")

    def extend_from_mem(code, jump):
        def short(opcode):
            code.extend(opcode + b"\x00")
            return len(code)

        code += b"\x83\x3d" + (0x082C1930).to_bytes(4, "little") + b"\x00"  # cmpl $0,flag_force_mem
        skip1 = short(b"\x74")
        code += b"\x8b\x45\x14\x83\xe8\x64\x83\xf8\x01"  # code - SIGN_EXTEND <= 1 (ZERO_EXTEND)?
        skip2 = short(b"\x76")
        code += b"\x83\xec\x0c\xff\x75\x10"        # sub $12,%esp; push op0
        jump(b"\xe8", 0x080C285E)                  # call force_not_mem
        code += b"\x83\xc4\x10\x89\x45\x10"        # add $16,%esp; mov %eax,op0
        for at in (skip1, skip2):
            code[at - 1] = len(code) - at
        jump(b"\xe9", 0x080C81B9)

    start = in_bc(extend_from_mem)
    put(0x080C819C, bytes.fromhex("c7c030192c08"),
        b"\xe9" + (start - (0x080C819C + 5)).to_bytes(4, "little", signed=True))

    # 13. try_combine+5233 (`if (added_sets_1 || added_sets_2)`): when I1's
    #    result is still needed after I3 and I1 is an `sra` (ASHIFTRT), give up
    #    (undo_all; return 0) instead of keeping I1 in a PARALLEL. Like GCC
    #    2.8, the PsyQ cc1 never folds a still-live sign extension into a later
    #    shift: `(s & 0xFF00) >> 8` of a short also used elsewhere stays
    #    `andi 0xFF00; sra 8` (ours made it `srl 24` of the `sll 16` and left a
    #    dead pseudo, i.e. a bogus stack frame) (libsnd _SsVmKeyOnNow...).
    #    Only for an I1 that is an arithmetic right shift (the second half
    #    of a sign extension): failing for every kept I1 breaks a dozen
    #    matched functions (kept constants, loads).
    def keep_live_i1(code, jump):
        code += b"\x83\xbd\xd4\xfe\xff\xff\x00"   # cmpl $0,added_sets_1
        jump(b"\x0f\x84", 0x08127F37)             # je -> test added_sets_2
        code += b"\x8b\x85\xb4\xfe\xff\xff"       # mov i1src,%eax
        code += b"\x66\x83\x38\x4f"                # cmpw $ASHIFTRT,(%eax)
        jump(b"\x0f\x84", 0x08127F1F)             # je -> undo_all; return 0
        jump(b"\xe9", 0x08127F44)                  # jmp -> build the PARALLEL

    cave = append(keep_live_i1)
    put(0x08127F2E, bytes.fromhex("83bdd4feffff00750d"),
        b"\xe9" + (cave - (0x08127F2E + 5)).to_bytes(4, "little", signed=True) + b"\x90" * 4)

    # 14. mark_target_live_regs is replaced by GCC 2.8.1's, whose forward
    #     scan follows both paths of a conditional jump (find_dead_or_set_
    #     registers). Source: tools/cc1_mtlr28.c, built by tools/cc1_mtlr28.sh
    #     for 0x08171590; the entry jumps there and the rest of the old body
    #     (with patches 3 and 7) becomes unreachable.
    blob = bytes.fromhex(
        "5589e553575683ec588b4d0c8b450885c00f8423020000c701010000008b4804ba817f807f89c8f7ea89d0c1e81fc1fa"
        "0701c289d0c1e00801d089ca29c2a1d4792c088b049085c0741590909090909039080f84060200008b400485c075f18b"
        "5d0853e824faffff83c40489c76a1ce81b51f0ff83c40489c68b43048906897e148b4b0489c8ba817f807ff7ea89d0c1"
        "e81fc1fa0701c289d0c1e00801d0ba817f807f8b1dd4792c0829c18b048b8946048b45088b480489c8f7ea89d0c1e81f"
        "c1fa0701c289d0c1e00801d029c189348bc705587a2c0800000000c705547a2c0800000000c705507a2c080000000083"
        "ffff8975ec0f84d5010000a1343a2d08897dc08b0cb88b01a3447a2c088b4104a3487a2c08894de88b4108a34c7a2c08"
        "a1483a2d088945b885c00f8ee8000000a1103a2d088945e4a130432d088945b031c9a188392d088945b431f6eb0f9090"
        "83c120463b75b80f84bb0000008b45e8833cb00074ea3b4de47de8ba010000008975bc90909090909090909090909090"
        "894df08b45e88514b0746a8b45b08b4df00fbf1c4885db785c8b45f08b4db48b34810fb64e02833c8d00cb2b08007e45"
        "89d89090909090909090909090909090bf0100000089c1d3e789c1c1e905093c8d447a2c08400fb64e028b0c8d00cb2b"
        "088d790383c10685ff0f49cfc1f90201d939c87ccb01d28b4df04185d274113b4de48b75bc0f8c75ffffffe943ffffff"
        "8b75bce93bffffff8b4dc085c90f84ca000000a1203a2d088b348866833e1b0f84c5000000e9cf000000a1cc792c0889"
        "410ca1c8792c08894108a1c4792c08894104a1c0792c088901e93e0500008945ec8b401483f8ff741289c6a1203a2d08"
        "8b04b0f640030889f77413ff7508e809f8ffff83c40489c78b45ec8b701439f70f95c083ffff0f94c108c10f85030500"
        "008b55ec8b42188b0dd8792c083b04b10f85f60400008b42088b4d0c8941048b420c8941088b421089410ce9cc040000"
        "8b5d0cc7430cffffffffc74308ffffffffc74304ffffffffe94c030000e80ba4f6ff89c666833e1b750f8b4610668338"
        "1375068b40048b70048b45086683381b75198b4010668338138b4d0889c8750bff7108e8b1a4f6ff83c40439c60f84d7"
        "0200008945f0eb5ea1507a2c08f7d02105447a2c08a1547a2c08f7d02105487a2c08a1587a2c08f7d021054c7a2c08c7"
        "05587a2c0800000000c705547a2c0800000000c705507a2c080000000090909056e8eafbffff83c40489c68b45f039c6"
        "0f84740200008b06a90000001075e16683f81b753b8b4e106683392abf01000060753f8b59048b0b0fb7d180ba80cc2b"
        "08690f44c10f45de6683f81d7430e9cf0000009090909090909090909090909089f3bf010000606683f81d7411e9b000"
        "000089f36683f81d0f85a400000031c9eb24b8feffffffd3c089cac1ea05210495447a2c089090909090909090909090"
        "4183f944741a80b9603d2d080074f183f91e77ce0fa3cf72e7ebc7909090909031c0eb14909090909090909090909090"
        "83c00283f844744880b820422d0800741889c180e11eba01000000d3e289c1c1e90509148d447a2c0880b821422d0800"
        "74ce8d4801ba01000000d3e289c1c1e90509148d447a2c08ebb69090909090908b030fb7c083c0e583f8050f87cffeff"
        "ffff2485b4211708895de88b431ceb038b400885c074690fb64802c1e11081f90000010075ea8b48048b116683fa3475"
        "df8b490483f9437fd7c1ea0e81e2fc0300008bba00cb2b088d5f038d570685db0f49d385ff7eb9c1fa0201ca90909090"
        "bf01000000d3e78d591f85c90f49d9c1fb05093c9d507a2c084139d17ce2eb9068151317088b7de8ff7710e8b062f6ff"
        "83c4088b471ceb0b90909090909090908b400885c00f8425feffff0fb64802c1e11081f900000a0075e68b48048b1166"
        "83fa3475db8b490483f9437fd3c1ea0e81e2fc0300008bba00cb2b088d5f038d570685db0f49d385ff7eb5c1fa0201ca"
        "bffeffffffd3c78d591f85c90f49d9c1fb05213c9d447a2c084139d17ce2eb908b43108b00b9feff000021c883f82a0f"
        "84abfdffffe9defeffff837b14f50f859cfdffffa1b4792c080905447a2c08a1b8792c080905487a2c08a1bc792c0809"
        "054c7a2c08e976fdffffa1447a2c088b5d0c894304a1487a2c08894308a14c7a2c0889430c8b4dec8b55c0895114a1d8"
        "792c088b0490894118c745c400000000c745d000000000c745cc00000000c745c800000000c745d400000000c745e000"
        "000000c745dc00000000c745d8000000008b45e08b4dd4894de88b7ddc8b4dd0894de48b4dc4894df08b75cc8b4d0889"
        "da50576a00ff75e8ff75e4566a00ff75f06a008d45ac50e83401000083c42885c00f84d000000050e8e9a2f6ff83c404"
        "89c6ff75ace8dca2f6ff83c4048d4d9c5150e829f9ffff83c408c745c400000000c745d000000000c745cc00000000c7"
        "45c800000000c745d400000000c745e000000000c745dc00000000c745d8000000008b450839f074548d5dc490909090"
        "6a018d4dd4515089c7e8eec0ffff83c40c8b45c8f7d02345d88b4dccf7d1234ddc8b55d0f7d22355e00945a0094da409"
        "55a86a016a005357e806c7ffff83c41057e840a2f6ff83c40439f075b38b5d0c8b43042345a08943048b4da4214b088b"
        "4da8214b0ceb038b43048b4dec8941088b430889410c8b430c89411083c4585e5f5b5dc38b75ece925f9ffffc705587a"
        "2c0800000000c705547a2c0800000000c705507a2c080000000089f7e92af9ffff909090909090909090909090909090"
        "5589e553575683ec5c8955d885c90f84cb01000089cb8b450c8945e0c745f000000000eb5c9090909090909090909090"
        "8d75106a018d7d205753e8fdbfffff83c40c6a016a005653e836c6ffff83c4108b4604f7d00b47048b4e08f7d10b4f08"
        "8b560cf7d20b570c8b75d8214604214e0821560c8b75dc85f689f30f84650100008b730c0fb7038d48e583f9050f87bd"
        "000000ff248dcc2117088b4b100fb71183fa2b74d283fa2a0f84fd0000008975dc83fa130f85190100008b49048b1185"
        "d289df0f848c000000be0100000090908b3cb10fb70783f81c747a39d68d760172eeeb71909090909090909090909090"
        "a1507a2c088d55208b4a08f7d1f7d00b4204210d547a2c088b4a0cf7d1210d587a2c088b4dd8214104a1547a2c08f7d0"
        "214108a1587a2c08f7d021410cc705587a2c0800000000c705547a2c0800000000c705507a2c0800000000e927ffffff"
        "8975dc89df83f81c0f85d2feffff837de0097f7b57e8ac45f8ff83c40485c075098b47106683382d7577ff45e08b7508"
        "85f60f94c08b55f085d20f95c10f44d38955f008c18b47208945dc0f858ffeffff8906895df0e985feffff8b41040fb7"
        "0880b980cc2b08690f85b9feffff6a016a00ff75d850e8b8c4ffff83c410e9a4feffff89df83f81c7484e951feffffc7"
        "45f0000000008b45f083c45c5e5f5b5dc357e87d45f8ff83c40485c0750d57e85046f8ff83c40485c074db8b45e083f8"
        "047fd383c0058945e06a018d45205053e817beffff83c40c8b4310668338137506f6470304752d6a016a008d75105653"
        "e83ec4ffff83c4108b460c8945c88b46088945c48b068b4e04894dc08945bce9830000008b4004833802721ab9010000"
        "008b448804813000000010418b43108b40043b0872eb8d4d108b410c8945c88b41088945c48b018b4904894dc08945bc"
        "8d45bc6a016a005053e8d5c3ffff83c4108b43108b4004833802721ab9010000008b448804813000000010418b43108b"
        "40043b0872eb6a016a008d45105053e89fc3ffff83c4108b5dd88b430c8945e48945a88b43088945ec8945a48b0b8b53"
        "048955a0894d9c8b75c0f7d68d4d208b41048945e809c621d68975a08b75c4f7d68b510809d62375ec8975a48b75c8f7"
        "d68d45208b480c09ce2375e48975a88b430c8945b88b43088945b48b038b73048975b08945ac8d75108b4604f7d00b45"
        "e82145b08b4608f7d009d02145b48b460cf7d009c82145b88b4f208d45208b500c8955ec8b50088955cc8b108955e48b"
        "78048b45c88945d08b45c48945d48b45bc8945e88b45c08d559cff75ecff75cc57ff75e4ff75d0ff75d450ff75e88b7d"
        "e0576a00e837fcffff83c4288d45208b480c894dec8b4808894dcc8b08894de48b40048945988b460c8945d08b460889"
        "45d48b068945e88b46048d55ac8b4ddcff75ecff75ccff7598ff75e4ff75d0ff75d450ff75e8576a00e8e2fbffff83c4"
        "288b45b08b4db40b45a00b4da48b55b80b55a8214304214b0821530ce9a5fdffffcccccc501b1708481a1708481a1708"
        "10191708c81817086a1b17080a1e1708c01e1708c01e1708e71d1708601e1708e71d1708"
    )
    o = fo(0x0817158D)
    if len(blob) > 0x081727E5 - 0x08171590:
        sys.exit("patch_cc1: mark_target_live_regs replacement too big")
    d[o:o + 3] = b"\xeb\x01\x90"  # jmp .+3
    d[o + 3:o + 3 + len(blob)] = blob

    # 15. prune_preferences+695: global.c records a conflict only in the row
    #    of the allocno that becomes live second, so `CONFLICTP (allocno, j)`
    #    misses half of them. GCC 2.8 tests both directions when it merges
    #    the preferences of conflicting lower-priority allocnos into
    #    regs_someone_prefers; with only one, a higher-priority pseudo takes
    #    a register a conflicting one prefers (dcb's libspu _spu_note2pitch:
    #    the n/12 quotient in a1 instead of v1). Locals: allocno -0x2c, j -0x30;
    #    %ebx is the function's GOT pointer.
    def conflict_both_ways(code, jump):
        code += b"\x8b\x83\x4c\xa4\x00\x00"        # mov allocno_order,%eax
        code += b"\x8b\x55\xd0\x8b\x04\x90"        # allocno_order[j]
        code += b"\x0f\xaf\x83\x5c\xa4\x00\x00"    # * allocno_row_words
        code += b"\x8b\x55\xd4\x89\xd1"            # mov allocno,%edx; mov %edx,%ecx
        code += b"\xc1\xfa\x05\x01\xd0"            # + allocno / INT_BITS
        code += b"\x8b\x93\x58\xa4\x00\x00"        # mov conflicts,%edx
        code += b"\x8b\x04\x82"                    # the word
        code += b"\x83\xe1\x1f\xd3\xe8\xa8\x01"    # >> allocno % INT_BITS; test $1
        jump(b"\x0f\x85", 0x0814C795)             # jne (merge)
        jump(b"\xe9", 0x0814C88F)                  # jmp (next j)

    start = in_bc(conflict_both_ways)
    o = fo(0x0814C78F)
    put(0x0814C78F, b"\x0f\x84" + d[o + 2:o + 6],
        b"\x0f\x84" + (start - (0x0814C78F + 6)).to_bytes(4, "little", signed=True))

    os.makedirs(os.path.dirname(dst), exist_ok=True)
    tmp = dst + ".tmp"
    with open(tmp, "wb") as f:
        f.write(d)
    os.chmod(tmp, 0o755)
    os.replace(tmp, dst)


def ensure():
    """Path of the patched cc1, (re)built when missing or stale."""
    me = os.path.abspath(__file__)
    if (not os.path.exists(PATCHED)
            or os.path.getmtime(PATCHED) < max(os.path.getmtime(STOCK), os.path.getmtime(me))):
        patch(STOCK, PATCHED)
    return PATCHED


if __name__ == "__main__":
    if len(sys.argv) == 3:
        patch(sys.argv[1], sys.argv[2])
    else:
        print(ensure())
