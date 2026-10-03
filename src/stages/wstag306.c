#include "common.h"
#include "stage.h"
void func_800A4D7C();
extern void (*D_800A5AD4[])(void);
void func_800A4F78();
extern AnimFrame D_800A55F4[];

s32 func_800A4CA4(StageTileAnim *obj, AnimFrame *frames, s32 depth) {
    AnimFrame *frame = &frames[obj->anim.index];
    s32 dt = GFX_FUNCS.getFrameTime();

    if (dt > 4) {
        dt = 4;
    }
    if (depth == 0) {
        obj->anim.timer -= dt;
    }
    if (obj->anim.timer <= 0) {
        frame++;
        obj->anim.index++;
        obj->anim.timer += frame->duration;
        if (frame->frame == 0xFF) {
            return 0xFF;
        }
        func_800A4CA4(obj, frames, depth + 1);
    }
    return frame->frame;
}

void func_800A4D7C(StageSoundTile *task) {
    StageTile *rec;
    StageTile *tile;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            if (rec->anim == 1) {
                task->obj.anim.index = 0;
                task->obj.anim.timer = D_800A55F4[0].duration;
                task->obj.tile = rec;
            }
        }
        task->nextState(task);
        break;
    case TASK_RUN:
        tile = task->obj.tile;
        switch (task->substate) {
        case 0:
        default:
            tile->frame = 5;
            tile->visible = 1;
            break;
        case 1:
            tile->visible = 1;
            frame = func_800A4CA4(&task->obj, D_800A55F4, 0);
            if (frame != 0xFF) {
                tile->frame = frame;
            } else {
                tile->frame = 10;
                task->nextSubstate(task);
                SOUND.keyOff(0xA0042FCB, task->voice);
            }
            break;
        case 2:
            tile->visible = 1;
            tile->frame = 10;
            break;
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

void func_800A4EDC(StageSoundTile *task, s32 id) {
    if (task != NULL && id == 0x335) {
        task->voice = SOUND_STATE.playSound(0xA0042FCB);
        task->obj.anim.index = 0;
        task->obj.anim.timer = D_800A55F4[0].duration;
        task->setSubstate(task, 1);
    }
}

void *func_800A4F48(s32 arg) {
    return createTaskWithId(func_800A4D7C, 0x5C, 0, arg);
}

/* Creates the event object of progress 0x25 or 0x27, and the stage helper task before progress 0x27 */
void func_800A4F78(StageTask *task, void **children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        switch (GAME_PROGRESS) {
        case 0x25:
            children[1] = func_80084B80(0x3A2);
            break;
        case 0x27:
            children[1] = func_80084B80(0x3D4);
            break;
        }
        if (GAME_PROGRESS < 0x27) {
            children[0] = func_800A4F48(0x353);
        }
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A5024(void *owner) {
    StageTask *task = createTask(func_800A4F78, sizeof(StageTask), 0x8);

    task->owner = owner;
    D_800A5AD4[0]();
    return task;
}

INCLUDE_ASM("stages/nonmatchings/wstag306", func_800A5080);

void func_800A5080();
extern s32 D_800A5834[];
extern s32 D_800A583C[];
extern s32 D_800A5844[];
extern s32 D_800A572C[];
extern s32 D_800A584C[];
extern s32 D_800A5744[];
extern s32 D_800A5854[];
extern s32 D_800A575C[];
extern s32 D_800A585C[];
extern s32 D_800A5774[];
extern s32 D_800A5864[];
extern s32 D_800A578C[];
extern s32 D_800A586C[];
extern s32 D_800A57A4[];
extern s32 D_800A5874[];
extern s32 D_800A57BC[];
extern s32 D_800A587C[];
extern s32 D_800A57D4[];
extern s32 D_800A5884[];
extern s32 D_800A57EC[];
extern s32 D_800A588C[];
extern s32 D_800A5804[];
extern s32 D_800A5894[];
extern s32 D_800A581C[];
extern s32 D_800A589C[];
extern s32 D_800A58B0[];
extern s32 D_800A58C4[];
extern s32 D_800A58D8[];
extern s32 D_800A58EC[];
extern s32 D_800A5900[];
extern s32 D_800A5914[];
extern s32 D_800A5928[];
extern s32 D_800A593C[];
extern s32 D_800A5950[];
extern s32 D_800A5964[];
extern s32 D_800A5978[];
extern s32 D_800A598C[];
extern s32 D_800A51B8[];
extern s32 D_800A52F8[];
extern s32 D_800A5348[];

s32 D_800A51B8[] = {
    0x10100, 0x191004F, 0x10101, 0x50001,
    0x1E0300, 0x10102, 0x1150148, 0x3020005,
    0x1010001, 0x10001, 0x3000001, 0x101001E,
    0x3A0001, 0x3000001, 0x10100B4, 0x10001,
    0x3000001, 0x200001E, 0x10000, 1,
    0x10101, 0x10007, 0x1010301, 0x10001,
    0x3000001, 0x101001E, 0x3A0001, 0x3000001,
    0x10100B4, 0x10001, 0x3000001, 0x101001E,
    0x3250323, 0x3000001, 0x101005A, 0x3260323,
    0x3000001, 0x200001E, 0x20000, 1,
    0x10101, 0x10007, 0x1010301, 0x10001,
    0x3000001, 0x101001E, 0x290001, 0x3000001,
    0x101003C, 0x2A0001, 0x3000001, 0x1010078,
    0x290001, 0x3000001, 0x101001E, 0x3350353,
    0x3000001, 0x101005A, 0x3250323, 0x3000001,
    0x101003C, 0x10001, 0x1010005, 0x3260323,
    0x3000001, 0x200001E, 0x30000, 1,
    0x10101, 0x50007, 0x1010301, 0x10001,
    0x3000005, 0x102001E, 0x1900001, 0x500F0,
    0x3C0300, 0x2880304, 0x20C0058, 5,
};
s32 D_800A52F8[] = {
    0x20102, 0xF50188, 0x1010005, 0x337032D,
    0x3020002, 0x1010002, 0x10002, 0x3000005,
    0x200001E, 0x10000, 0x20002, 0x20101,
    0x50007, 0x1010301, 0x10002, 0x3000005,
    0x304001E, 0x580288, 0x5020C, 0,
};
s32 D_800A5348[] = {
    0x10100, 0x190004F, 0x10101, 0x50001,
    0x9D0100, 0x1150168, 0x9D0101, 0x50001,
    0x9E0100, 0x1040148, 0x9E0101, 0x50001,
    0x1190100, 0x128014F, 0x1190101, 0x50001,
    0x13A0100, 0x1100120, 0x13A0101, 0x50001,
    0x1E0300, 0x10102, 0x15000D0, 0x3020005,
    0x1010001, 0x10001, 0x3000005, 0x101001E,
    0x3250323, 0x3000001, 0x101005A, 0x3260323,
    0x3000001, 0x101001E, 0x1009D, 0x1010001,
    0x1009E, 0x1010001, 0x10119, 0x1010001,
    0x1013A, 0x3000001, 0x102001E, 0x1170001,
    0x5012C, 0x10302, 0x10101, 0x50001,
    0x1E0300, 1537, 0x11B0136, 0x1190101,
    0x20001, 0x13A0101, 1, 0x1E0300,
    0x10200, 0x13A0002, 0x2000000, 0x10000,
    0x20119, 0x3000301, 0x200001E, 0x40001,
    158, 512, 0x9D0003, 0x3010002,
    0x1E0300, 0x10101, 0x40001, 0x1E0300,
    0x10101, 0x50001, 0x1E0300, 0x10101,
    0x60001, 0x1E0300, 0x10101, 0x50001,
    0x1E0300, 512, 0x10005, 0x1010000,
    0x70001, 0x3010005, 0x10101, 0x50001,
    0x1E0300, 0x10101, 0x60001, 0x1E0300,
    512, 0x1190006, 0x3010002, 0x1E0300,
    512, 0x10007, 0x1010000, 0x70001,
    0x3010006, 0x10101, 0x60001, 0x1E0300,
    0x10101, 0x50001, 0x1E0300, 1536,
    0x1020001, 0x13F0001, 0x50118, 0x10302,
    0x10102, 0xFF0171, 0x3020005, 0x1010001,
    0x10001, 0x3000005, 0x101001E, 0x1009D,
    0x1010005, 0x1009E, 0x1010005, 0x10119,
    0x1010005, 0x1013A, 0x3000005, 0x101001E,
    0x10001, 0x3000001, 0x200001E, 0x80000,
    1, 0x10101, 0x10007, 0x1010301,
    0x10001, 0x3000001, 0x601001E, 0x13F0000,
    0x2000118, 0xA0001, 314, 512,
    0x1190009, 0x3010002, 0x1E0300, 0x10200,
    0x9E000C, 0x2000000, 0xB0000, 0x2009D,
    0x3000301, 0x600001E, 0x10000, 0x10101,
    0x10009, 0x10303, 0x10101, 0x10001,
    0x1E0300, 0x10101, 0x50001, 0x1E0300,
    0x10102, 0xE801A0, 0x3000005, 0x3040006,
    0x600288, 0x50208, 0,
};
AnimFrame D_800A55F4[] = {
    { 5, 4 }, { 6, 4 }, { 7, 4 }, { 8, 4 },
    { 9, 4 }, { 255, 0x3E7 },
};
s32 D_800A560C[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x1000140, 0x18C0176, 0x8C00D8, 0x1FB0140,
    0, 0, 0, 0,
    0x1000180, 0x100019A, 360, 0x1FB0150,
    0x1000180, 0x10001A2, 392, 0x1FB0160,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0x1000180, 0x1140180, 0x140100, 0x1FA0150,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0x1000180, 0x1160188, 0x160120, 0x1FA0160,
};
s32 D_800A572C[] = {
    0, 0, 524, 0,
    0, 0,
};
s32 D_800A5744[] = {
    0, 0, 6, 0,
    0, 0,
};
s32 D_800A575C[] = {
    0, 0, 505, 0,
    0, 0,
};
s32 D_800A5774[] = {
    0, 0, 524, 0,
    0, 0,
};
s32 D_800A578C[] = {
    0, 0, 524, 0,
    0, 0,
};
s32 D_800A57A4[] = {
    0, 0, 4, 0,
    0, 0,
};
s32 D_800A57BC[] = {
    0, 0, 524, 0,
    0, 0,
};
s32 D_800A57D4[] = {
    0, 0, 524, 0,
    0, 0,
};
s32 D_800A57EC[] = {
    0, 0, 524, 0,
    0, 0,
};
s32 D_800A5804[] = {
    0, 0, 524, 0,
    0, 0,
};
s32 D_800A581C[] = {
    0, 0, 5, 0,
    0, 0,
};
s32 D_800A5834[] = {
    0x16025, 65535,
};
s32 D_800A583C[] = {
    0x16027, 65535,
};
s32 D_800A5844[] = {
    0x17094, 65535,
};
s32 D_800A584C[] = {
    0x1701A, 65535,
};
s32 D_800A5854[] = {
    0x1701A, 65535,
};
s32 D_800A585C[] = {
    0x17094, 65535,
};
s32 D_800A5864[] = {
    0x17094, 65535,
};
s32 D_800A586C[] = {
    0x1701A, 65535,
};
s32 D_800A5874[] = {
    0x17094, 65535,
};
s32 D_800A587C[] = {
    0x17094, 65535,
};
s32 D_800A5884[] = {
    0x17094, 65535,
};
s32 D_800A588C[] = {
    0x17094, 65535,
};
s32 D_800A5894[] = {
    0x1701A, 65535,
};
s32 D_800A589C[] = {
    (s32)D_800A5834, 0, 0x40001, 0,
    1,
};
s32 D_800A58B0[] = {
    (s32)D_800A583C, 0, 0x40001, 0,
    1,
};
s32 D_800A58C4[] = {
    (s32)D_800A5844, (s32)D_800A572C, 0x5003F, 0x1040079,
    7,
};
s32 D_800A58D8[] = {
    (s32)D_800A584C, (s32)D_800A5744, 0x6009D, 0x10801CF,
    1,
};
s32 D_800A58EC[] = {
    (s32)D_800A5854, (s32)D_800A575C, 0x7009E, 0x138016F,
    5,
};
s32 D_800A5900[] = {
    (s32)D_800A585C, (s32)D_800A5774, 0x800C6, 0xE500B9,
    7,
};
s32 D_800A5914[] = {
    (s32)D_800A5864, (s32)D_800A578C, 0x900C7, 0xC500F9,
    7,
};
s32 D_800A5928[] = {
    (s32)D_800A586C, (s32)D_800A57A4, 0xA0119, 0x11601AC,
    1,
};
s32 D_800A593C[] = {
    (s32)D_800A5874, (s32)D_800A57BC, 0xB0121, 0xBC0178,
    1,
};
s32 D_800A5950[] = {
    (s32)D_800A587C, (s32)D_800A57D4, 0xC0122, 0x17C0168,
    3,
};
s32 D_800A5964[] = {
    (s32)D_800A5884, (s32)D_800A57EC, 0xD0123, 0x15C01A8,
    3,
};
s32 D_800A5978[] = {
    (s32)D_800A588C, (s32)D_800A5804, 0xE0124, 0x13C01E8,
    3,
};
s32 D_800A598C[] = {
    (s32)D_800A5894, (s32)D_800A581C, 0xF013A, 0x12201C3,
    1,
};
s32 D_800A59A0[] = {
    (s32)D_800A589C, (s32)D_800A58B0, (s32)D_800A58C4, (s32)D_800A58D8,
    (s32)D_800A58EC, (s32)D_800A5900, (s32)D_800A5914, (s32)D_800A5928,
    (s32)D_800A593C, (s32)D_800A5950, (s32)D_800A5964, (s32)D_800A5978,
    (s32)D_800A598C, 0,
};
s32 D_800A59D8[] = {
    0x6400001, 0x3B320132, 0x1760006, 136,
    0x10000, 0x13C0640, 0x8453C, 0x690198,
    0, 0x6400001, 0x57460146, 0x1A20008,
    102, 0x1000000, 0x50640, 0x40A05,
    0xC4017E, 0, 0x4400001, 0,
    0x1C50000, 0xC700B9, 0x10000, 0x10440,
    0, 0xBE01C1, 204, 0x4580001,
    2, 0x15F0000, 0xDA0088, 0x10000,
    0x30440, 0, 0x12E00D7, 353,
    0x4480001, 4, 0x900000, 0x1420106,
    0, 0, 0, 0,
    0,
};
s32 D_800A5A8C[] = {
    65535, 65535, 0x2860001, 0xCC0398,
    1, 0, 0x1701A, 65535,
    0x3C60008, 0, 0, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*D_800A5AD4[])(void) = {
    func_800A5080,
};
s32 D_800A5AD8[] = {
    930, (s32)D_800A51B8,
#if VERSION_US
    0x120000F,
#elif VERSION_EU
    0x127000F,
#endif
    0, 0, 966, (s32)D_800A52F8,
#if VERSION_US
    0x1200015,
#elif VERSION_EU
    0x1270015,
#endif
    0, 0, 980, (s32)D_800A5348,
#if VERSION_US
    0x1200017,
#elif VERSION_EU
    0x1270017,
#endif
    0, 0, -1, 0,
    0, 0, 0,
};
