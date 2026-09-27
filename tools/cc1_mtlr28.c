/*
 * GCC 2.8.1's mark_target_live_regs / find_dead_or_set_registers (reorg.c),
 * written against the data structures of our GCC 2.7.2 cc1. tools/patch_cc1.py
 * compiles this for i386 and puts it over 2.7.2's mark_target_live_regs.
 *
 * The difference that matters: at a conditional jump the forward scan follows
 * both paths (at most one conditional jump) and a register is dead if it is
 * set before being used on both, where 2.7.2 stopped at the jump. The PsyQ
 * cc1 fills branch delay slots like this (prnt: `beqz v0,L; sll v0,s0,2`).
 */

typedef struct rtx_def *rtx;

typedef union rtunion_def {
    long rtwint;
    int rtint;
    char *rtstr;
    rtx rtx;
    struct rtvec_def *rtvec;
    int rttype;
} rtunion;

struct rtx_def {
    unsigned int code : 16;
    unsigned int mode : 8;
    unsigned int jump : 1;
    unsigned int call : 1;
    unsigned int unchanging : 1;
    unsigned int volatil : 1;
    unsigned int in_struct : 1;
    unsigned int used : 1;
    unsigned int integrated : 1;
    rtunion fld[1];
};

struct rtvec_def {
    unsigned num_elem;
    rtunion elem[1];
};

/* rtl.def (2.7.2) */
enum { SEQUENCE = 19, INSN = 27, JUMP_INSN = 28, CALL_INSN = 29, BARRIER = 30,
       CODE_LABEL = 31, NOTE = 32, USE = 42, CLOBBER = 43, RETURN = 45, REG = 52 };
enum { REG_DEAD = 1, REG_UNUSED = 10 };
#define NOTE_INSN_EPILOGUE_BEG -11

#define GET_CODE(X) ((X)->code)
#define GET_MODE(X) ((X)->mode)
#define XEXP(X, N) ((X)->fld[N].rtx)
#define XVECLEN(X, N) ((X)->fld[N].rtvec->num_elem)
#define XVECEXP(X, N, M) ((X)->fld[N].rtvec->elem[M].rtx)
#define INSN_UID(I) ((I)->fld[0].rtint)
#define PREV_INSN(I) ((I)->fld[1].rtx)
#define NEXT_INSN(I) ((I)->fld[2].rtx)
#define PATTERN(I) ((I)->fld[3].rtx)
#define REG_NOTES(I) ((I)->fld[6].rtx)
#define JUMP_LABEL(I) ((I)->fld[7].rtx)
#define NOTE_LINE_NUMBER(I) ((I)->fld[4].rtint)
#define REGNO(X) ((X)->fld[0].rtint)
#define REG_NOTE_KIND(L) (GET_MODE (L))
#define INSN_DELETED_P(I) ((I)->volatil)
#define INSN_ANNULLED_BRANCH_P(I) ((I)->unchanging)
#define INSN_FROM_TARGET_P(I) ((I)->in_struct)
#define GET_RTX_CLASS(C) (rtx_class[(int) (C)])

#define FIRST_PSEUDO_REGISTER 68
#define STACK_POINTER_REGNUM 29
#define FRAME_POINTER_REGNUM 30
#define ARG_POINTER_REGNUM 0
#define PIC_OFFSET_TABLE_REGNUM 28
#define FP_REG_P(R) ((unsigned) ((R) - 32) < 32)
#define HARD_REGNO_NREGS(R, MODE) ((mode_size[MODE] + 3) / 4)

typedef unsigned long HARD_REG_SET[3];
#define CLEAR_HARD_REG_SET(T) ((T)[0] = (T)[1] = (T)[2] = 0)
#define SET_HARD_REG_SET(T) ((T)[0] = (T)[1] = (T)[2] = ~0UL)
#define COPY_HARD_REG_SET(T, F) ((T)[0] = (F)[0], (T)[1] = (F)[1], (T)[2] = (F)[2])
#define AND_HARD_REG_SET(T, F) ((T)[0] &= (F)[0], (T)[1] &= (F)[1], (T)[2] &= (F)[2])
#define AND_COMPL_HARD_REG_SET(T, F) ((T)[0] &= ~(F)[0], (T)[1] &= ~(F)[1], (T)[2] &= ~(F)[2])
#define IOR_HARD_REG_SET(T, F) ((T)[0] |= (F)[0], (T)[1] |= (F)[1], (T)[2] |= (F)[2])
#define SET_HARD_REG_BIT(S, B) ((S)[(B) / 32] |= 1UL << ((B) % 32))
#define CLEAR_HARD_REG_BIT(S, B) ((S)[(B) / 32] &= ~(1UL << ((B) % 32)))

struct resources {
    char memory;
    char unch_memory;
    char volatil;
    char cc;
    HARD_REG_SET regs;
};
#define CLEAR_RESOURCE(R) ((R)->memory = (R)->unch_memory = (R)->volatil = (R)->cc = 0, CLEAR_HARD_REG_SET ((R)->regs))

struct target_info {
    int uid;
    struct target_info *next;
    HARD_REG_SET live_regs;
    int block;
    int bb_tick;
};
#define TARGET_HASH_PRIME 257

/* cc1's own functions and variables (addresses given to the linker) */
extern void mark_referenced_resources(rtx, struct resources *, int);
extern void mark_set_resources(rtx, struct resources *, int, int);
extern int find_basic_block(rtx);
extern rtx next_insn_no_annul(rtx);
extern rtx next_insn(rtx);
extern void update_live_status(rtx, rtx);
extern void note_stores(rtx, void (*)(rtx, rtx));
extern int simplejump_p(rtx);
extern int condjump_p(rtx);
extern int condjump_in_parallel_p(rtx);
extern rtx next_active_insn(rtx);
extern char *oballoc(int);
extern rtx get_insns(void);
extern struct target_info **target_hash_table;
extern int *bb_ticks;
extern unsigned long **basic_block_live_at_start;
extern rtx *basic_block_head;
extern short *reg_renumber;
extern int regset_size;
extern int max_regno;
extern HARD_REG_SET current_live_regs;
extern HARD_REG_SET pending_dead_regs;
extern struct resources end_of_function_needs;
extern struct resources start_of_epilogue_needs;
extern char call_used_regs[];
extern char global_regs[];
extern rtx *regno_reg_rtx;
extern int mode_size[];
extern char rtx_class[];

static rtx find_dead_or_set_registers(rtx, struct resources *, rtx *, int, struct resources, struct resources);

void mark_target_live_regs(rtx target, struct resources *res)
{
    int b = -1;
    int i;
    struct target_info *tinfo;
    rtx insn;
    rtx jump_insn = 0;
    rtx jump_target;
    HARD_REG_SET scratch;
    struct resources set, needed;

    /* Handle end of function.  */
    if (target == 0) {
        *res = end_of_function_needs;
        return;
    }

    /* We have to assume memory is needed, but the CC isn't.  */
    res->memory = 1;
    res->volatil = res->unch_memory = 0;
    res->cc = 0;

    /* See if we have computed this value already.  */
    for (tinfo = target_hash_table[INSN_UID (target) % TARGET_HASH_PRIME]; tinfo; tinfo = tinfo->next)
        if (tinfo->uid == INSN_UID (target))
            break;

    if (tinfo && tinfo->block != -1 && !INSN_DELETED_P (basic_block_head[tinfo->block]))
        b = tinfo->block;

    if (b == -1)
        b = find_basic_block (target);

    if (tinfo) {
        if (b == tinfo->block && b != -1 && tinfo->bb_tick == bb_ticks[b]) {
            COPY_HARD_REG_SET (res->regs, tinfo->live_regs);
            return;
        }
    } else {
        tinfo = (struct target_info *) oballoc (sizeof (struct target_info));
        tinfo->uid = INSN_UID (target);
        tinfo->block = b;
        tinfo->next = target_hash_table[INSN_UID (target) % TARGET_HASH_PRIME];
        target_hash_table[INSN_UID (target) % TARGET_HASH_PRIME] = tinfo;
    }

    CLEAR_HARD_REG_SET (pending_dead_regs);

    if (b != -1) {
        unsigned long *regs_live = basic_block_live_at_start[b];
        int offset, j, regno;
        unsigned long bit;
        rtx start_insn, stop_insn;

        COPY_HARD_REG_SET (current_live_regs, regs_live);

        for (offset = 0, i = 0; offset < regset_size; offset++) {
            if (regs_live[offset] == 0)
                i += 32;
            else
                for (bit = 1; bit && i < max_regno; bit <<= 1, i++)
                    if ((regs_live[offset] & bit) && (regno = reg_renumber[i]) >= 0)
                        for (j = regno; j < regno + HARD_REGNO_NREGS (regno, GET_MODE (regno_reg_rtx[i])); j++)
                            SET_HARD_REG_BIT (current_live_regs, j);
        }

        start_insn = (b == 0 ? get_insns () : basic_block_head[b]);
        stop_insn = target;

        if (GET_CODE (start_insn) == INSN && GET_CODE (PATTERN (start_insn)) == SEQUENCE)
            start_insn = XVECEXP (PATTERN (start_insn), 0, 0);

        if (GET_CODE (stop_insn) == INSN && GET_CODE (PATTERN (stop_insn)) == SEQUENCE)
            stop_insn = next_insn (PREV_INSN (stop_insn));

        for (insn = start_insn; insn != stop_insn; insn = next_insn_no_annul (insn)) {
            rtx link;
            rtx real_insn = insn;

            if (INSN_FROM_TARGET_P (insn))
                continue;

            if (GET_CODE (insn) == INSN && GET_CODE (PATTERN (insn)) == USE
                && GET_RTX_CLASS (GET_CODE (XEXP (PATTERN (insn), 0))) == 'i')
                real_insn = XEXP (PATTERN (insn), 0);

            if (GET_CODE (real_insn) == CALL_INSN) {
                for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
                    if (call_used_regs[i] && i != STACK_POINTER_REGNUM && i != FRAME_POINTER_REGNUM
                        && i != ARG_POINTER_REGNUM)
                        CLEAR_HARD_REG_BIT (current_live_regs, i);

                for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
                    if (global_regs[i])
                        SET_HARD_REG_BIT (current_live_regs, i);
            }

            if ((GET_CODE (real_insn) == INSN && GET_CODE (PATTERN (real_insn)) != USE
                 && GET_CODE (PATTERN (real_insn)) != CLOBBER)
                || GET_CODE (real_insn) == JUMP_INSN || GET_CODE (real_insn) == CALL_INSN) {
                for (link = REG_NOTES (real_insn); link; link = XEXP (link, 1))
                    if (REG_NOTE_KIND (link) == REG_DEAD && GET_CODE (XEXP (link, 0)) == REG
                        && REGNO (XEXP (link, 0)) < FIRST_PSEUDO_REGISTER) {
                        int first_regno = REGNO (XEXP (link, 0));
                        int last_regno = first_regno + HARD_REGNO_NREGS (first_regno, GET_MODE (XEXP (link, 0)));

                        for (i = first_regno; i < last_regno; i++)
                            SET_HARD_REG_BIT (pending_dead_regs, i);
                    }

                note_stores (PATTERN (real_insn), update_live_status);

                for (link = REG_NOTES (real_insn); link; link = XEXP (link, 1))
                    if (REG_NOTE_KIND (link) == REG_UNUSED && GET_CODE (XEXP (link, 0)) == REG
                        && REGNO (XEXP (link, 0)) < FIRST_PSEUDO_REGISTER) {
                        int first_regno = REGNO (XEXP (link, 0));
                        int last_regno = first_regno + HARD_REGNO_NREGS (first_regno, GET_MODE (XEXP (link, 0)));

                        for (i = first_regno; i < last_regno; i++)
                            CLEAR_HARD_REG_BIT (current_live_regs, i);
                    }
            } else if (GET_CODE (real_insn) == CODE_LABEL) {
                AND_COMPL_HARD_REG_SET (current_live_regs, pending_dead_regs);
                CLEAR_HARD_REG_SET (pending_dead_regs);
            } else if (GET_CODE (real_insn) == NOTE && NOTE_LINE_NUMBER (real_insn) == NOTE_INSN_EPILOGUE_BEG)
                IOR_HARD_REG_SET (current_live_regs, start_of_epilogue_needs.regs);
        }

        COPY_HARD_REG_SET (res->regs, current_live_regs);
        tinfo->block = b;
        tinfo->bb_tick = bb_ticks[b];
    } else
        SET_HARD_REG_SET (res->regs);

    CLEAR_RESOURCE (&set);
    CLEAR_RESOURCE (&needed);

    jump_insn = find_dead_or_set_registers (target, res, &jump_target, 0, set, needed);

    /* If we hit an unconditional branch, we have another way of finding out
       what is live: we can see what is live at the branch target and include
       anything used but not set before the branch.  */
    if (jump_insn) {
        struct resources new_resources;
        rtx stop_insn = next_active_insn (jump_insn);

        mark_target_live_regs (next_active_insn (jump_target), &new_resources);
        CLEAR_RESOURCE (&set);
        CLEAR_RESOURCE (&needed);

        for (insn = target; insn != stop_insn; insn = next_active_insn (insn)) {
            mark_referenced_resources (insn, &needed, 1);

            COPY_HARD_REG_SET (scratch, needed.regs);
            AND_COMPL_HARD_REG_SET (scratch, set.regs);
            IOR_HARD_REG_SET (new_resources.regs, scratch);

            mark_set_resources (insn, &set, 0, 1);
        }

        AND_HARD_REG_SET (res->regs, new_resources.regs);
    }

    COPY_HARD_REG_SET (tinfo->live_regs, res->regs);
}

static rtx find_dead_or_set_registers(rtx target, struct resources *res, rtx *jump_target, int jump_count,
                                      struct resources set, struct resources needed)
{
    HARD_REG_SET scratch;
    rtx insn, next;
    rtx jump_insn = 0;
    int i;

    for (insn = target; insn; insn = next) {
        rtx this_jump_insn = insn;

        next = NEXT_INSN (insn);
        switch (GET_CODE (insn)) {
        case CODE_LABEL:
            /* After a label, any pending dead registers that weren't yet
               used can be made dead.  */
            AND_COMPL_HARD_REG_SET (pending_dead_regs, needed.regs);
            AND_COMPL_HARD_REG_SET (res->regs, pending_dead_regs);
            CLEAR_HARD_REG_SET (pending_dead_regs);
            continue;

        case BARRIER:
        case NOTE:
            continue;

        case INSN:
            if (GET_CODE (PATTERN (insn)) == USE) {
                /* If INSN is a USE made by update_block, we care about the
                   underlying insn.  Any registers set by the underlying insn
                   are live since the insn is being done somewhere else.  */
                if (GET_RTX_CLASS (GET_CODE (XEXP (PATTERN (insn), 0))) == 'i')
                    mark_set_resources (XEXP (PATTERN (insn), 0), res, 0, 1);

                /* All other USE insns are to be ignored.  */
                continue;
            } else if (GET_CODE (PATTERN (insn)) == CLOBBER)
                continue;
            else if (GET_CODE (PATTERN (insn)) == SEQUENCE) {
                /* An unconditional jump can be used to fill the delay slot
                   of a call, so search for a JUMP_INSN in any position.  */
                for (i = 0; i < XVECLEN (PATTERN (insn), 0); i++) {
                    this_jump_insn = XVECEXP (PATTERN (insn), 0, i);
                    if (GET_CODE (this_jump_insn) == JUMP_INSN)
                        break;
                }
            }
        }

        if (GET_CODE (this_jump_insn) == JUMP_INSN) {
            if (jump_count++ < 10) {
                if (simplejump_p (this_jump_insn) || GET_CODE (PATTERN (this_jump_insn)) == RETURN) {
                    next = JUMP_LABEL (this_jump_insn);
                    if (jump_insn == 0) {
                        jump_insn = insn;
                        if (jump_target)
                            *jump_target = JUMP_LABEL (this_jump_insn);
                    }
                } else if (condjump_p (this_jump_insn) || condjump_in_parallel_p (this_jump_insn)) {
                    struct resources target_set, target_res;
                    struct resources fallthrough_res;

                    /* Follow both paths, and then IOR the results of the two
                       paths together, which gives the registers that are dead
                       on both paths.  At most one conditional branch.  */
                    jump_count += 4;
                    if (jump_count >= 10)
                        break;

                    mark_referenced_resources (insn, &needed, 1);

                    if (GET_CODE (PATTERN (insn)) == SEQUENCE && INSN_ANNULLED_BRANCH_P (this_jump_insn)) {
                        for (i = 1; i < XVECLEN (PATTERN (insn), 0); i++)
                            INSN_FROM_TARGET_P (XVECEXP (PATTERN (insn), 0, i))
                                = !INSN_FROM_TARGET_P (XVECEXP (PATTERN (insn), 0, i));

                        target_set = set;
                        mark_set_resources (insn, &target_set, 0, 1);

                        for (i = 1; i < XVECLEN (PATTERN (insn), 0); i++)
                            INSN_FROM_TARGET_P (XVECEXP (PATTERN (insn), 0, i))
                                = !INSN_FROM_TARGET_P (XVECEXP (PATTERN (insn), 0, i));

                        mark_set_resources (insn, &set, 0, 1);
                    } else {
                        mark_set_resources (insn, &set, 0, 1);
                        target_set = set;
                    }

                    target_res = *res;
                    COPY_HARD_REG_SET (scratch, target_set.regs);
                    AND_COMPL_HARD_REG_SET (scratch, needed.regs);
                    AND_COMPL_HARD_REG_SET (target_res.regs, scratch);

                    fallthrough_res = *res;
                    COPY_HARD_REG_SET (scratch, set.regs);
                    AND_COMPL_HARD_REG_SET (scratch, needed.regs);
                    AND_COMPL_HARD_REG_SET (fallthrough_res.regs, scratch);

                    find_dead_or_set_registers (JUMP_LABEL (this_jump_insn), &target_res, 0, jump_count,
                                                target_set, needed);
                    find_dead_or_set_registers (next, &fallthrough_res, 0, jump_count, set, needed);
                    IOR_HARD_REG_SET (fallthrough_res.regs, target_res.regs);
                    AND_HARD_REG_SET (res->regs, fallthrough_res.regs);
                    break;
                } else
                    break;
            } else {
                /* Don't try this optimization if we expired our jump count
                   above, since that would mean there may be an infinite loop
                   in the function being compiled.  */
                jump_insn = 0;
                break;
            }
        }

        mark_referenced_resources (insn, &needed, 1);
        mark_set_resources (insn, &set, 0, 1);

        COPY_HARD_REG_SET (scratch, set.regs);
        AND_COMPL_HARD_REG_SET (scratch, needed.regs);
        AND_COMPL_HARD_REG_SET (res->regs, scratch);
    }

    return jump_insn;
}
