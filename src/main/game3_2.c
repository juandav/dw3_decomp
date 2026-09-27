#include "game.h"

s32 findPartnerEntry(s32 partner, s32 id) {
    s32 i;

    for (i = 0; i < 44; i++) {
        if (GAME.partners[partner].entries[i].id < 3) {
            continue;
        }
        if (GAME.partners[partner].entries[i].id == id) {
            return i;
        }
    }
    return -1;
}

s32 getPartnerSlots(s32 partner, s16 *out) {
    s32 i;
    s32 n;
    s32 index;

    for (i = 0, n = 0; i < 3; i++) {
        if (GAME.partners[partner].slots[i] >= 3) {
            index = findPartnerEntry(partner, GAME.partners[partner].slots[i]);
            if (index >= 0 && GAME.partners[partner].entries[index].id >= 3) {
                out[n] = GAME.partners[partner].entries[index].id;
                n++;
            }
        }
    }
    for (i = n; i < 3; i++) {
        out[i] = -1;
    }
    return n;
}

void setPartnerSlots(s32 partner, s16 *ids) {
    s32 i;
    s32 index;

    for (i = 0; i < 3; i++) {
        index = findPartnerEntry(partner, ids[i]);
        if (index >= 0) {
            GAME.partners[partner].slots[i] = GAME.partners[partner].entries[index].id;
        } else {
            GAME.partners[partner].slots[i] = -1;
        }
    }
}

s32 listPartnerEntries(s32 partner, u16 *out) {
    s32 i;
    s32 n;
    s32 count;

    for (n = i = 0; i < 44; i++) {
        if (GAME.partners[partner].entries[i].id >= 3) {
            out[n] = GAME.partners[partner].entries[i].id;
            n++;
        }
    }
    count = n;
    for (; n < 44; n++) {
        out[n] = 0;
    }
    return count;
}

extern void (*ON_PARTNER_ENTRY_ADDED)(s32 id);

s32 addPartnerEntry(s32 partner, s32 id) {
    s32 i;
    s32 index;

    if (findPartnerEntry(partner, id) != -1) {
        return 0;
    }
    for (i = 0, index = -1; i < 44; i++) {
        if (GAME.partners[partner].entries[i].id == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        return 0;
    }
    ON_PARTNER_ENTRY_ADDED(id);
    GAME.partners[partner].entries[index].id = id;
    GAME.partners[partner].entries[index].isNew = 1;
    return 1;
}

s32 getPartnerEntry(s32 partner, s32 id, PartnerEntry *out) {
    s32 i = findPartnerEntry(partner, id);

    if (i != -1) {
        *out = GAME.partners[partner].entries[i];
    }
    return i;
}

s32 setPartnerEntry(s32 partner, s32 id, PartnerEntry *in) {
    s32 i = findPartnerEntry(partner, id);

    if (i != -1) {
        GAME.partners[partner].entries[i] = *in;
    }
    return i;
}

PartnerStats *getPartnerStats(s32 partner) {
    return &PARTNER_STATS[partner];
}

void freeMem(void *ptr) {
    MemBlock *block = (MemBlock *)ptr - 1;
    MemBlock *prev;
    MemBlock *next;

    if (ptr != NULL) {
        prev = block->prev;
        next = block->next;
        block->tag = 0;
        if (next->tag == 0) {
            block->next = next->next;
            next->next->prev = block;
        }
        if (prev->tag == 0) {
            prev->next = block->next;
            block->next->prev = prev;
        }
    }
}

void func_80017878(void) {
}

void freeMemByTag(s32 tag) {
    MemBlock *block;

    for (block = HEAP.first; block->tag != 1; block = block->next) {
        if (block->tag == tag) {
            freeMem(block + 1);
        }
    }
}

void initHeap(void) {
    MemBlock *start;
    MemBlock *last;

    HEAP.end = (MemBlock *)0x801FF000;
    last = (MemBlock *)0x801FEFF4;
    start = HEAP_START;
    HEAP.first = start;
    HEAP.size = (u8 *)0x801FF000 - (u8 *)start;
    start->prev = start;
    start->next = last;
    start->tag = 0;
    last->prev = start;
    last->tag = 1;
    last->next = HEAP.end;
}

void zeroMem(void *dst, s32 size) {
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

void fillMem(s8 *dst, s8 value, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        *dst++ = value;
    }
}

/* First fit from the start of the heap */
void *tryAllocMem(u32 size, s32 tag) {
    MemBlock *b;
    MemBlock *new;
    u32 avail;
    u32 splitSize;

    size = (size + 3) >> 2 << 2;
    splitSize = size + 20;
    for (b = HEAP.first; b->tag != 1; b = b->next) {
        if (b->tag == 0) {
            avail = (u8 *)b->next - (u8 *)b - sizeof(MemBlock);
            if (avail >= size) {
                if (avail > splitSize) {
                    new = (MemBlock *)((u8 *)b + size + sizeof(MemBlock));
                    new->prev = b;
                    new->next = b->next;
                    new->tag = 0;
                    b->next->prev = new;
                    b->next = new;
                }
                b->tag = tag;
                return b + 1;
            }
        }
    }
    return NULL;
}

/* First fit from the end of the heap */
void *tryAllocMemHigh(u32 size, s32 tag) {
    MemBlock *b;
    MemBlock *prev;
    MemBlock *new;
    u32 avail;

    size = ((size + 3) >> 2 << 2) + sizeof(MemBlock);
    for (b = HEAP.end - 1; HEAP.first != b; b = b->prev) {
        prev = b->prev;
        if (prev->tag == 0) {
            avail = (u8 *)b - (u8 *)prev;
            if (size == avail) {
                new = prev;
                new->tag = tag;
                return new + 1;
            }
            if (size < avail) {
                new = (MemBlock *)((u8 *)b - size);
                new->prev = prev;
                new->next = b;
                new->tag = tag;
                b->prev->next = new;
                b->prev = new;
                return new + 1;
            }
        }
    }
    return NULL;
}

/* Evicts cached files until the allocation fits */
void *allocMem(s32 size, s32 tag) {
    void *ptr;

    while ((ptr = tryAllocMem(size, tag)) == NULL) {
        FILE_CACHE.evictOldest();
    }
    return ptr;
}

/* The block is returned in v0, left there by tryAllocMemHigh */
void allocMemHigh(s32 size, s32 tag) {
    while (tryAllocMemHigh(size, tag) == 0) {
        FILE_CACHE.evictOldest();
    }
}

void *allocMemZeroed(s32 size, s32 tag) {
    void *ret = allocMem(size, tag);

    zeroMem(ret, size);
    return ret;
}

/* Keeps a block alive across mode changes (tag 4), or hands it back to tag 2 */
void lockMem(void *ptr, s32 lock) {
    MemBlock *block = (MemBlock *)ptr - 1;

    if (lock) {
        block->tag = 4;
    } else {
        block->tag = 2;
    }
}

void clearTaskRegistry(void) {
    s32 i;

    for (i = 99; i >= 0; i--) {
        TASK_REGISTRY.tasks[i] = 0;
    }
}

void registerTask(s32 task) {
    s32 i;
    s32 *p;

    for (i = 0, p = TASK_REGISTRY.tasks; i < 100; i++, p++) {
        if (*p == 0) {
            *p = task;
            return;
        }
    }
}

void unregisterTask(s32 task) {
    s32 i;
    s32 *p;

    for (i = 0, p = TASK_REGISTRY.tasks; i < 100; i++, p++) {
        if (*p == task) {
            *p = 0;
            return;
        }
    }
}

void *findNextTask(void) {
    s32 i;
    s32 *e;

    for (i = TASK_REGISTRY.findNext; i < 100; i++) {
        e = (s32 *)TASK_REGISTRY.tasks[i];
        if (e != NULL && (TASK_REGISTRY.findId == -1 || e[0] == TASK_REGISTRY.findId) &&
            (TASK_REGISTRY.findKey1 == -1 || e[1] == TASK_REGISTRY.findKey1) &&
            (TASK_REGISTRY.findKey2 == -1 || e[2] == TASK_REGISTRY.findKey2)) {
            TASK_REGISTRY.findNext = i + 1;
            return (void *)TASK_REGISTRY.tasks[i];
        }
    }
    return NULL;
}

/* Returns (in v0, through findNextTask) the first registered task that matches */
void findTask(s32 id, s32 key1, s32 key2) {
    TASK_REGISTRY.findId = id;
    TASK_REGISTRY.findKey1 = key1;
    TASK_REGISTRY.findKey2 = key2;
    TASK_REGISTRY.findNext = 0;
    findNextTask();
}

/* The update runs with its stack in the scratchpad */
#define SetSpadStack(addr) \
    __asm__ volatile("move $8,%0\n\tsw $29,0($8)\n\taddiu $8,$8,-16\n\tmove $29,$8" : : "r"(addr) : "$8", "memory")
#define ResetSpadStack() __asm__ volatile("addiu $29,$29,16\n\tlw $29,0($29)" : : : "memory")

/* One frame of a task and its children; returns NULL once the task is gone */
Task *executeTask(Task *task) {
    s32 dying = task->state == TASK_KILL;

    SetSpadStack(0x1F8003FC);
    if (task->state == TASK_RUN && task->paused != 0) {
        if (task->paused > 0) {
            task->paused = -1;
        }
    } else {
        task->update(task, task->children);
    }
    ResetSpadStack();
    if (!dying) {
        if (task->state != TASK_RUN || task->paused == 0) {
            TASK_FUNCS.runChildren(task);
        }
    } else {
        task->destroy(task);
        task = NULL;
    }
    return task;
}

void runChildTasks(Task *task) {
    s32 count = task->childCount;
    s32 *children = task->children;
    s32 i;

    for (i = 0; i < count; i++) {
        if (children[i] != 0) {
            children[i] = (s32)executeTask((Task *)children[i]);
        }
    }
}

s32 runTask(s32 task) {
    if (task != 0) {
        return (s32)executeTask((Task *)task);
    }
    return 0;
}

void killTask(Task *task) {
    if (task != NULL) {
        task->setState(task, TASK_KILL);
        TASK_FUNCS.run(task);
    }
}
