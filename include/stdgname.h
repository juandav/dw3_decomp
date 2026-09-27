#ifndef STDGNAME_H
#define STDGNAME_H

#include "game.h"

/* A full-screen fade */
typedef struct FadeTask {
    TASK_HEADER(FadeTask);
    /* 0x50 */ s32 layer;
    /* 0x54 */ s32 depth;
    /* 0x58 */ s32 fadeIn;
    /* 0x5C */ s32 level; /* 8.8 fixed point */
    /* 0x60 */ s32 delta; /* added to level each frame */
    /* 0x64 */ void (*start)(struct FadeTask *task, s32 fadeIn, s32 duration);
} FadeTask;

/* A linear tween of a scale, 0 to 0x1000 */
typedef struct Tween {
    /* 0x0 */ s32 duration;
    /* 0x4 */ s32 step;
    /* 0x8 */ s32 value;
    /* 0xC */ s32 active;
} Tween;

void func_80082724(Task *task, void **children);
Task *func_8008281C(void);
void func_80082848(FadeTask *task, s32 fadeIn, s32 duration);
void func_800828D0(FadeTask *task);
void func_80082A14(FadeTask *task);
FadeTask *func_80082AC8(void);
void func_80082B10(Tween *tween, s32 open);
s32 func_80082BA4(Tween *tween);
void *func_80085B20(void);

#endif /* STDGNAME_H */
