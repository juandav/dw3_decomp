#include "common.h"
#include "stage.h"
void func_800A4FFC();
extern void (*D_800A583C[])(void);
void func_800A5150();
void *func_800A4FCC(s32 arg);
StageTile *func_80088C9C(s32 anim);

/*
 * Once the substate is set to 1, moves the records of animations 2, 3, 4 and
 * 7 and shows those of 5 to 9 in turn
 */
void func_800A4CB8(StageTileGroup *task) {
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        for (i = 0; i < 8; i++) {
            task->tiles[i] = func_80088C9C(i + 2);
        }
        task->nextState(task);
        break;
    case TASK_RUN:
        switch (task->substate) {
        case 0:
            break;
        case 1:
            switch (task->step) {
            case 0:
                SOUND.playSound(0x8100383C);
                task->nextStep(task);
            case 1:
                if (task->counter & 1) {
                    task->tiles[0]->unkC++;
                    task->tiles[1]->unkC++;
                    task->tiles[2]->unkC++;
                    task->tiles[5]->unkC++;
                }
                if (++task->counter != 8) {
                    break;
                }
                task->nextStep(task);
            case 2:
                if (task->counter & 1) {
                    task->tiles[1]->unkC++;
                    task->tiles[5]->unkC++;
                }
                if (++task->counter != 0x10) {
                    break;
                }
                task->nextStep(task);
            case 3:
                if (task->counter == 0) {
                    task->tiles[3]->visible = 1;
                    SOUND.playSound(0x1000002);
                    task->tickCounter(task);
                }
                if (task->tiles[3]->unk9 == 0xF) {
                    task->nextStep(task);
                }
                break;
            case 4:
                if (task->counter == 0) {
                    task->tiles[3]->visible = 0;
                    task->tiles[4]->visible = 1;
                    task->tiles[5]->visible = 0;
                    task->tiles[6]->visible = 1;
                    task->tickCounter(task);
                }
                if (task->tiles[6]->unk9 == 0xF) {
                    task->tiles[6]->visible = 0;
                    task->tiles[7]->visible = 1;
                    task->nextStep(task);
                }
                break;
            }
            break;
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

/* Starts the task (substate 1) when map object 0x32C is triggered */
void func_800A4F94(StageTask *task, s32 id) {
    if (task != NULL && id == 0x32C) {
        task->setSubstate(task, 1);
    }
}

/* Creates the task of func_800A4CB8 with id 0x329 */
void *func_800A4FCC(s32 arg) {
    return createTaskWithId(func_800A4CB8, 0x70, 0, 0x329);
}

/* Once the substate is set to 1, animates the frame of the record of animation 1 for 20 frames, then plays a sound */
void func_800A4FFC(StageFrameTask *task) {
    StageTile *tile;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
    case TASK_RUN:
        switch (task->substate) {
        case 0:
            break;
        case 1:
            switch (task->step) {
            case 0:
                task->frame = (task->counter >> 2) + 5;
                if (++task->counter >= 0x14) {
                    SOUND.playSound(0x8100303C);
                    task->nextStep(task);
                } else {
                    tile = func_80088C9C(1);
                    if (tile != NULL) {
                        tile->frame = task->frame;
                    }
                }
                break;
            }
            break;
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

/* Starts the task (substate 1) when map object 0x32E is triggered */
void func_800A50E8(StageTask *task, s32 id) {
    if (task != NULL && id == 0x32E) {
        task->setSubstate(task, 1);
    }
}

void *func_800A5120(s32 arg) {
    return createTaskWithId(func_800A4FFC, 0x5C, 0, arg);
}

/* Creates two objects and the event object of story progress 1 */
void func_800A5150(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        children[2] = func_800A4FCC(0x329);
        children[1] = func_800A5120(0x328);
        if (GAME_PROGRESS == 1) {
            children[0] = func_80084B80(4);
        }
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A51E0(void *owner) {
    StageTask *task = createTask(func_800A5150, sizeof(StageTask), 0xC);

    task->owner = owner;
    D_800A583C[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag790", func_800A523C);

void func_800A523C();
extern s32 D_800A5670[];
extern s32 D_800A5678[];
extern s32 D_800A5680[];
extern s32 D_800A5694[];
extern s32 D_800A56A8[];
extern s32 D_800A56BC[];
extern s32 D_800A5310[];

s32 D_800A5310[] = {
    0x10601, 0x1210157, 0x10100, 0,
    0x10101, 0x10001, 0xB0100, 0,
    0xB0101, 0x10001, 0xC0100, 0,
    0xC0101, 0x10001, 0xD0100, 0xF6018A,
    0xD0101, 0x30001, 0x3280101, 0x328032D,
    0x3290101, 0x328032D, 0x3C0300, 0x10100,
    0x15900E5, 0x10101, 0x50001, 0x1E0300,
    0x10102, 0x1210157, 0x3020000, 0x6000001,
    0x10001, 0x10101, 0x1003A, 0x780300,
    512, 0x10001, 0x1010003, 0x70001,
    0x3010000, 0x10101, 1, 0x1E0300,
    0x10102, 0xFF019B, 0x3020005, 0x1010001,
    0x10001, 0x1010003, 0x1000D, 0x3000007,
    0x200001E, 0x20000, 13, 0xD0101,
    0x70007, 0x1010301, 0x1000D, 0x3000007,
    0x200001E, 0x30000, 0x10001, 0x10101,
    0x30007, 0x1010301, 0x10001, 0x3000003,
    0x101001E, 0x10001, 0x1010007, 0x2000D,
    0x3000003, 0x101003C, 0x290001, 0x3000007,
    0x101005A, 0x2A0001, 0x1010007, 0x1000D,
    0x1010003, 0x3250323, 0x300000D, 0x101003C,
    0x10001, 0x1010007, 0x1000D, 0x1010007,
    0x3260323, 0x300000D, 0x101001E, 0x10001,
    0x3000003, 0x200001E, 0x40000, 13,
    0xD0101, 0x70007, 0x3290101, 0x1032B,
    0x1010301, 0x1000D, 0x3000007, 0x200001E,
    0x50000, 0x10001, 0x10101, 0x30007,
    0x1010301, 0x10001, 0x3000003, 0x601001E,
    0x19B0001, 0x10200FF, 0x1D50001, 0x500E1,
    0xD0101, 0x30001, 0x10302, 0x10100,
    0, 0x10101, 1, 0xD0101,
    0x30002, 0x3C0300, 0xB0100, 0x15100EB,
    0xB0101, 0x50001, 0x1E0300, 0xB0102,
    0x14800FE, 0x1000005, 0xEB000C, 0x1010151,
    0x1000C, 0x3020005, 0x102000B, 0x171000B,
    0x5010F, 0xC0102, 0x11B015A, 0x3020005,
    0x101000C, 0x1000B, 0x1010005, 0x1000C,
    0x1010005, 0x32E0328, 0x3000001, 0x101003C,
    0x33000B, 0x3000005, 0x200003C, 0x70000,
    0x2000B, 0xB0101, 0x5000C, 0x1010301,
    0x1000B, 0x3000005, 0x200001E, 0x80000,
    0x2000C, 0xC0101, 0x50007, 0x1010301,
    0x1000C, 0x1010005, 0x32C0329, 0x3000001,
    0x304012C,
#if VERSION_US
    0x1700E02,
#elif VERSION_EU
    0x1700E03,
#endif
    0x1011F, 0,
};
s32 D_800A55D0[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x1D00166, 0xD00098, 0x1FB0170,
    0x1000180, 0x13001B6, 0x3001D8, 0x1FA0170,
    0x1000180, 0x1A301B4, 0xA301D0, 0x1F90170,
    0x1000180, 0x13001A6, 0x300198, 0x1F80170,
};
s32 D_800A5670[] = {
    0x16001, 65535,
};
s32 D_800A5678[] = {
    0x16001, 65535,
};
s32 D_800A5680[] = {
    0, 0, 0x40001, 0,
    0,
};
s32 D_800A5694[] = {
    (s32)D_800A5670, 0, 0x5000B, 0,
    0,
};
s32 D_800A56A8[] = {
    0, 0, 0x6000C, 0,
    0,
};
s32 D_800A56BC[] = {
    (s32)D_800A5678, 0, 0x7000D, 0,
    0,
};
s32 D_800A56D0[] = {
    (s32)D_800A5680, (s32)D_800A5694, (s32)D_800A56A8, (s32)D_800A56BC,
    0,
};
s32 D_800A56E4[] = {
    0x2400401, 12, 0x1DF0000, 117,
    0x7010000, 0x390240, 0, 0x7E0197,
    0, 0x2400800, 0xF000234, 0x1970005,
    138, 0x9000000, 0x2380240, 0xE040F0E,
    0x8A0197, 0, 0x2900301, 11,
    0x19F0000, 79, 0x2010000, 0xA0240,
    0, 0x4C0183, 0, 0x2400500,
    0xF000233, 0x1AC0004, 172, 0x6000000,
    0x2370240, 0xE040F0E, 0xAC01AC, 0,
    0x2400101, 4, 0x1A20000, 191,
    0x10000, 0x2320240, 0x20300, 0x9200FE,
    0, 0x2400001, 0x3000232, 0x1BA0002,
    241, 0x10000, 0x2320240, 0x20300,
    0x120021A, 0, 0x6400001, 0x7000036,
    0x169000A, 205, 0x10000, 0x350A40,
    0, 150, 0, 0x4400001,
    0, 0x18E0000, 0x1280117, 0x10000,
    0x10440, 0, 0xF701AE, 264,
    0x4400001, 2, 0x18D0000, 0x1190107,
    0x10000, 0x30440, 0, 0xE801AD,
    247, 0, 0, 0,
    0, 0,
};
void (*D_800A583C[])(void) = {
    func_800A523C,
};
s32 D_800A5840[] = {
    4, (s32)D_800A5310,
#if VERSION_US
    0x1430003,
#elif VERSION_EU
    0x14A0003,
#endif
    0, 0, -1, 0,
    0, 0, 0,
};
