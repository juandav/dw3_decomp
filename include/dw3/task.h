#ifndef DW3_TASK_H
#define DW3_TASK_H

/* The task system (system.c, game3_2.c) */

#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

/* The task registry's methods (TASK_REGISTRY.funcs) */
typedef struct TaskFuncs {
    /* 0x00 */ void (*clear)();
    /* 0x04 */ void (*add)();
    /* 0x08 */ void (*remove)();
    /* 0x0C */ void *(*find)(s32 id, s32 key1, s32 key2);
    /* 0x10 */ void *(*findNext)(void);
    /* 0x14 */ void (*runChildren)();
    /* 0x18 */ void *(*run)(void *task);
    /* 0x1C */ void (*kill)(s32 task);
} TaskFuncs;

/*
 * Tasks: every game object is a task, a heap block that starts with this
 * header and is updated once per frame (createTask). A task owns an array of
 * child tasks (windows, cursors...), which run right after it, and it gets
 * that array as the second argument of its update. The state machine is
 * driven through the header: TASK_INIT runs once (usually just nextState),
 * TASK_RUN is the normal state, and TASK_KILL frees the task (and kills its
 * children) after its last update.
 */
#define TASK_INIT 0
#define TASK_RUN 1
#define TASK_DONE 2
#define TASK_KILL 3

#define TASK_HEADER(Type)                                                   \
    /* 0x00 */ s32 id; /* registered tasks only: findTask matches these */ \
    /* 0x04 */ s32 key1;                                                    \
    /* 0x08 */ s32 key2;                                                    \
    /* 0x0C */ s32 state;                                                   \
    /* 0x10 */ s32 substate;                                                \
    /* 0x14 */ s32 step;                                                    \
    /* 0x18 */ s32 counter;                                                 \
    /* 0x1C */ s32 paused; /* in TASK_RUN: skip the update and children */  \
    /* 0x20 */ s32 childCount;                                              \
    /* 0x24 */ void *children;                                              \
    /* 0x28 */ void (*setState)(struct Type *task, s32 state);              \
    /* 0x2C */ void (*setSubstate)(struct Type *task, s32 substate);        \
    /* 0x30 */ void (*setStep)(struct Type *task, s32 step);                \
    /* 0x34 */ void (*setCounter)(struct Type *task, s32 counter);          \
    /* 0x38 */ void (*nextState)(struct Type *task);                        \
    /* 0x3C */ void (*nextSubstate)(struct Type *task);                     \
    /* 0x40 */ void (*nextStep)(struct Type *task);                         \
    /* 0x44 */ void (*tickCounter)(struct Type *task);                      \
    /* 0x48 */ void (*update)(); /* (task, children) */                      \
    /* 0x4C */ void (*destroy)(struct Type *task)

/* Any task, seen through its header */
typedef struct Task {
    TASK_HEADER(Task);
} Task;

/* Tasks created with an id, so that other code can find them */
typedef struct TaskRegistry {
    /* 0x000 */ s32 tasks[100]; /* Task pointers, 0 for a free entry */
    /* 0x190 */ s32 findId; /* -1 matches anything */
    /* 0x194 */ s32 findKey1;
    /* 0x198 */ s32 findKey2;
    /* 0x19C */ s32 findNext;
    /* 0x1A0 */ TaskFuncs funcs; /* TASK_FUNCS */
} TaskRegistry;

void *createTask(void (*update)(), s32 size, s32 childrenSize);
void *createTaskWithId(void (*update)(), s32 size, s32 childrenSize, s32 id);
struct Task *executeTask(struct Task *task);
void *findNextTask(void);

extern TaskFuncs TASK_FUNCS;
extern TaskRegistry TASK_REGISTRY;

#endif /* DW3_TASK_H */
