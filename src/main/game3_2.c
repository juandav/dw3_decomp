#include "game.h"

s32 func_800172E8(s32 slot, s32 id) {
    s32 i;

    for (i = 0; i < 44; i++) {
        if (D_800484E8.records[slot].entries[i].unk0 < 3) {
            continue;
        }
        if (D_800484E8.records[slot].entries[i].unk0 == id) {
            return i;
        }
    }
    return -1;
}

s32 func_80017348(s32 slot, s16 *out) {
    s32 i;
    s32 n;
    s32 index;

    for (i = 0, n = 0; i < 3; i++) {
        if (D_800484E8.records[slot].unk54[i] >= 3) {
            index = func_800172E8(slot, D_800484E8.records[slot].unk54[i]);
            if (index >= 0 && D_800484E8.records[slot].entries[index].unk0 >= 3) {
                out[n] = D_800484E8.records[slot].entries[index].unk0;
                n++;
            }
        }
    }
    for (i = n; i < 3; i++) {
        out[i] = -1;
    }
    return n;
}

void func_8001746C(s32 slot, s16 *ids) {
    s32 i;
    s32 index;

    for (i = 0; i < 3; i++) {
        index = func_800172E8(slot, ids[i]);
        if (index >= 0) {
            D_800484E8.records[slot].unk54[i] = D_800484E8.records[slot].entries[index].unk0;
        } else {
            D_800484E8.records[slot].unk54[i] = -1;
        }
    }
}

s32 func_80017534(s32 slot, u16 *out) {
    s32 i;
    s32 n;
    s32 count;

    for (n = i = 0; i < 44; i++) {
        if (D_800484E8.records[slot].entries[i].unk0 >= 3) {
            out[n] = D_800484E8.records[slot].entries[i].unk0;
            n++;
        }
    }
    count = n;
    for (; n < 44; n++) {
        out[n] = 0;
    }
    return count;
}

extern void (*D_8005C448)(s32 id);

s32 func_800175C0(s32 slot, s32 id) {
    s32 i;
    s32 index;

    if (func_800172E8(slot, id) != -1) {
        return 0;
    }
    for (i = 0, index = -1; i < 44; i++) {
        if (D_800484E8.records[slot].entries[i].unk0 == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        return 0;
    }
    D_8005C448(id);
    D_800484E8.records[slot].entries[index].unk0 = id;
    D_800484E8.records[slot].entries[index].unk2 = 1;
    return 1;
}

s32 func_800176B8(s32 slot, s32 id, Unk80048C50Entry *out) {
    s32 i = func_800172E8(slot, id);

    if (i != -1) {
        *out = D_800484E8.records[slot].entries[i];
    }
    return i;
}

s32 func_80017750(s32 slot, s32 id, Unk80048C50Entry *in) {
    s32 i = func_800172E8(slot, id);

    if (i != -1) {
        D_800484E8.records[slot].entries[i] = *in;
    }
    return i;
}

Unk80048C50 *func_800177E8(s32 index) {
    return &D_80048C50[index];
}

void func_8001780C(void *ptr) {
    MemBlock *block = (MemBlock *)ptr - 1;
    MemBlock *prev;
    MemBlock *next;

    if (ptr != NULL) {
        prev = block->prev;
        next = block->next;
        block->flags = 0;
        if (next->flags == 0) {
            block->next = next->next;
            next->next->prev = block;
        }
        if (prev->flags == 0) {
            prev->next = block->next;
            block->next->prev = prev;
        }
    }
}

void func_80017878(void) {
}

void func_80017880(s32 tag) {
    MemBlock *block;

    for (block = D_8004AD84.first; block->flags != 1; block = block->next) {
        if (block->flags == tag) {
            func_8001780C(block + 1);
        }
    }
}

void func_800178F8(void) {
    MemBlock *start;
    MemBlock *last;

    D_8004AD84.end = (MemBlock *)0x801FF000;
    last = (MemBlock *)0x801FEFF4;
    start = D_8005C2F8;
    D_8004AD84.first = start;
    D_8004AD84.size = (u8 *)0x801FF000 - (u8 *)start;
    start->prev = start;
    start->next = last;
    start->flags = 0;
    last->prev = start;
    last->flags = 1;
    last->next = D_8004AD84.end;
}

void func_8001794C(void *dst, s32 size) {
    s32 i;

    if (size & 3) {
        u8 *p = dst;

        for (i = 0; i < size; i++) {
            *p++ = 0;
        }
    } else {
        s32 *p = dst;

        size >>= 2;
        for (i = 0; i < size; i++) {
            *p++ = 0;
        }
    }
}

void func_800179A4(s8 *dst, s8 value, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        *dst++ = value;
    }
}

void *func_800179C8(u32 size, s32 tag) {
    MemBlock *b;
    MemBlock *new;
    u32 avail;
    u32 splitSize;

    size = (size + 3) >> 2 << 2;
    splitSize = size + 20;
    for (b = D_8004AD84.first; b->flags != 1; b = b->next) {
        if (b->flags == 0) {
            avail = (u8 *)b->next - (u8 *)b - sizeof(MemBlock);
            if (avail >= size) {
                if (avail > splitSize) {
                    new = (MemBlock *)((u8 *)b + size + sizeof(MemBlock));
                    new->prev = b;
                    new->next = b->next;
                    new->flags = 0;
                    b->next->prev = new;
                    b->next = new;
                }
                b->flags = tag;
                return b + 1;
            }
        }
    }
    return NULL;
}

void *func_80017A78(u32 size, s32 tag) {
    MemBlock *b;
    MemBlock *prev;
    MemBlock *new;
    u32 avail;

    size = ((size + 3) >> 2 << 2) + sizeof(MemBlock);
    for (b = D_8004AD84.end - 1; D_8004AD84.first != b; b = b->prev) {
        prev = b->prev;
        if (prev->flags == 0) {
            avail = (u8 *)b - (u8 *)prev;
            if (size == avail) {
                new = prev;
                new->flags = tag;
                return new + 1;
            }
            if (size < avail) {
                new = (MemBlock *)((u8 *)b - size);
                new->prev = prev;
                new->next = b;
                new->flags = tag;
                b->prev->next = new;
                b->prev = new;
                return new + 1;
            }
        }
    }
    return NULL;
}

void *func_80017B20(s32 size, s32 tag) {
    void *ptr;

    while ((ptr = func_800179C8(size, tag)) == NULL) {
        D_80044744.outOfMemory();
    }
    return ptr;
}

void func_80017B88(s32 arg0, s32 arg1) {
    while (func_80017A78(arg0, arg1) == 0) {
        D_80044744.outOfMemory();
    }
}

void *func_80017BF0(s32 size, s32 tag) {
    void *ret = func_80017B20(size, tag);

    func_8001794C(ret, size);
    return ret;
}

void func_80017C30(void *ptr, s32 arg1) {
    MemBlock *block = (MemBlock *)ptr - 1;

    if (arg1) {
        block->flags = 4;
    } else {
        block->flags = 2;
    }
}

void func_80017C50(void) {
    s32 i;

    for (i = 99; i >= 0; i--) {
        D_8004ADB8.list[i] = 0;
    }
}

void func_80017C78(s32 arg0) {
    s32 i;
    s32 *p;

    for (i = 0, p = D_8004ADB8.list; i < 100; i++, p++) {
        if (*p == 0) {
            *p = arg0;
            return;
        }
    }
}

void func_80017CB0(s32 arg0) {
    s32 i;
    s32 *p;

    for (i = 0, p = D_8004ADB8.list; i < 100; i++, p++) {
        if (*p == arg0) {
            *p = 0;
            return;
        }
    }
}

void *func_80017CE8(void) {
    s32 i;
    s32 *e;

    for (i = D_8004ADB8.unk19C; i < 100; i++) {
        e = (s32 *)D_8004ADB8.list[i];
        if (e != NULL && (D_8004ADB8.unk190 == -1 || e[0] == D_8004ADB8.unk190) &&
            (D_8004ADB8.unk194 == -1 || e[1] == D_8004ADB8.unk194) &&
            (D_8004ADB8.unk198 == -1 || e[2] == D_8004ADB8.unk198)) {
            D_8004ADB8.unk19C = i + 1;
            return (void *)D_8004ADB8.list[i];
        }
    }
    return NULL;
}

void func_80017DA8(s32 arg0, s32 arg1, s32 arg2) {
    D_8004ADB8.unk190 = arg0;
    D_8004ADB8.unk194 = arg1;
    D_8004ADB8.unk198 = arg2;
    D_8004ADB8.unk19C = 0;
    func_80017CE8();
}

/* Runs the task's update with the stack in the scratchpad. */
#define SetSpadStack(addr) \
    __asm__ volatile("move $8,%0\n\tsw $29,0($8)\n\taddiu $8,$8,-16\n\tmove $29,$8" : : "r"(addr) : "$8", "memory")
#define ResetSpadStack() __asm__ volatile("addiu $29,$29,16\n\tlw $29,0($29)" : : : "memory")

Unk80017ECC *func_80017DDC(Unk80017ECC *task) {
    s32 done = task->state == 3;

    SetSpadStack(0x1F8003FC);
    if (task->state == 1 && task->wait != 0) {
        if (task->wait > 0) {
            task->wait = -1;
        }
    } else {
        task->update(task, task->items);
    }
    ResetSpadStack();
    if (!done) {
        if (task->state != 1 || task->wait == 0) {
            D_8004AF58.unk14(task);
        }
    } else {
        task->destroy(task);
        task = NULL;
    }
    return task;
}

void func_80017ECC(Unk80017ECC *obj) {
    s32 count = obj->count;
    s32 *items = obj->items;
    s32 i;

    for (i = 0; i < count; i++) {
        if (items[i] != 0) {
            items[i] = (s32)func_80017DDC((Unk80017ECC *)items[i]);
        }
    }
}

s32 func_80017F38(s32 arg0) {
    if (arg0 != 0) {
        return (s32)func_80017DDC((Unk80017ECC *)arg0);
    }
    return 0;
}

void func_80017F64(Task *task) {
    if (task != NULL) {
        task->unk28(task, 3);
        D_8004AF58.unk18(task);
    }
}
