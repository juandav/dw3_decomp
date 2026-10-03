#include "common.h"
#include "stage.h"
extern s32 D_800A65A8[];
extern s32 D_800A6318[];
extern s32 D_800A64FC[];
extern u8 D_800A6334[];
extern u8 D_800A6544[];
extern u8 D_800A6520[];
extern void (*D_800A65A4[])(void);
void func_800A4ECC();
void func_800A5768();
extern AnimFrame D_800A60B0[];
extern AnimFrame D_800A6098[];
extern StageEffectSpot D_800A6068[];
StageEffect *func_800A55DC(s32 x, s32 y, s32 frame);
void *func_800A5638(s32 arg);
extern AnimFrame D_800A5FD8[];

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

/* Shows the record with animation 1, animated once, then hides it and kills itself */
void func_800A4D7C(StageTileTask *task) {
    StageTile *rec;
    StageTile *tile;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        for (rec = D_800990B4.unk10; rec->unk2 != 0; rec++) {
            if (rec->anim == 1) {
                task->obj.tile = rec;
            }
        }
        task->obj.anim.index = 0;
        task->obj.anim.timer = D_800A5FD8[0].duration;
        break;
    case TASK_RUN:
        tile = task->obj.tile;
        tile->visible = 1;
        frame = func_800A4CA4(&task->obj, D_800A5FD8, 0);
        if (frame != 0xFF) {
            tile->frame = frame;
        } else {
            tile->visible = 0;
            task->setState(task, TASK_KILL);
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

/* Creates the task of func_800A4D7C with the given id, with a sound */
void *func_800A4E78(s32 id) {
    void *task = createTaskWithId(func_800A4D7C, 0x58, 0, id);

    SOUND.playSound(0x4001D);
    return task;
}

/* Creates the stage's four objects and the event object of story progress 0x29 that applies */
void func_800A4ECC(StageTask *task, void **children) {
    s32 i;

    switch (task->state) {
    case TASK_INIT:
    default:
        for (i = 0; i < 4; i++) {
            if (D_800A6068[i].kind == 0) {
                children[i + 1] = func_800A55DC(D_800A6068[i].x, D_800A6068[i].y, D_800A6068[i].frame);
            } else if (D_800A6068[i].kind == 2) {
                children[i + 1] = func_800A5638(0x34D);
            }
        }
        do {
            if (GAME.progress == 0x29 && FLAGS_00.checkCondition(0x4074, 0)) {
                children[0] = func_80084B80(0x424);
                break;
            }
            if (GAME.progress == 0x29 && FLAGS_00.checkCondition(0x4074, 1) && FLAGS_00.checkCondition(0x4075, 0)) {
                children[0] = func_80084B80(0x42E);
                break;
            }
        } while (0);
        task->nextState(task);
        break;
    case TASK_RUN:
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

StageTask *func_800A5024(void *owner) {
    StageTask *task = createTask(func_800A4ECC, sizeof(StageTask), 0x14);

    task->owner = owner;
    D_800A65A4[0]();
    return task;
}

s32 func_800A5080(AnimState *anim, AnimFrame *frames, s32 once, s32 depth) {
    AnimFrame *frame = &frames[anim->index];
    s32 dt = GFX_FUNCS.getFrameTime();

    if (dt > 4) {
        dt = 4;
    }
    if (depth == 0) {
        anim->timer -= dt;
    }
    if (anim->timer <= 0) {
        frame++;
        anim->index++;
        anim->timer += frame->duration;
        if (once) {
            if (frame->frame == 0xFF) {
                return 0xFF;
            }
        } else if (frame->frame == 0xFF) {
            frame = frames;
            anim->index = 0;
            anim->timer += frame->duration;
        }
        func_800A5080(anim, frames, once, depth + 1);
    }
    return frame->frame;
}

void func_800A51A0(StageEffect *task, void *arg, s32 idx) {
    SpriteDrawer drawer;
    Layer *layer = arg;
    StageSprite *sprite = &task->sprites[idx];
    s32 y = task->y;
    s32 x = task->x;
    s32 depth;

    if (idx == 1) {
        y -= 0x20;
        depth = 4;
    } else {
        depth = 6;
    }
    initSpriteDrawer(&drawer);
    drawer.setTexture(0x140, 0x100);
    drawer.setLayer(layer, depth);
    drawer.setClutRow(sprite->clutRow);
    drawer.draw(FILE_CACHE_GET_ENTRY[0](D_800990B4.unkC), sprite->frame, x, y);
}

s32 func_800A5288(s32 x, s32 y, s32 w, s32 h) {
    RECT rect;
    struct Layer *layer = GFX_FUNCS.getLayer(0x1002);

    layer->getViewRect(layer, &rect);
    if (x + w < rect.x) {
        return 0;
    }
    if (rect.x + rect.w < x) {
        return 0;
    }
    if (y + h < rect.y) {
        return 0;
    }
    return rect.y + rect.h >= y;
}

void func_800A534C(StageEffect *task) {
    Layer *layer = GFX_FUNCS.getLayer(0x1002);
    s32 done;
    s32 frame;

    switch (task->state) {
    case TASK_INIT:
    default:
        task->key1 = task->x;
        task->key2 = task->y;
        task->anim.index = 0;
        task->anim.timer = D_800A60B0[0].duration;
        task->clutAnim.index = 0;
        task->clutAnim.timer = D_800A6098[0].duration;
        task->nextState(task);
        break;
    case TASK_RUN:
        task->sprites[0].frame = task->frame;
        task->sprites[0].clutRow = func_800A5080(&task->clutAnim, D_800A6098, 0, 0);
        if (task->sprites[0].frame != 0 && func_800A5288(task->x, task->y, 0x20, 0x20)) {
            layer->addSortedCallback(layer, func_800A51A0, task, task->y, 0);
        }
        break;
    case TASK_DONE:
        if (task->substate == 0) {
            task->anim.index = 0;
            task->anim.timer = D_800A60B0[0].duration;
            task->clutAnim.index = 0;
            task->clutAnim.timer = D_800A6098[0].duration;
            task->setSubstate(task, 1);
        }
        task->sprites[0].frame = task->frame;
        task->sprites[0].clutRow = func_800A5080(&task->clutAnim, D_800A6098, 0, 0);
        done = 0;
        frame = func_800A5080(&task->anim, D_800A60B0, 1, 0);
        switch (frame) {
        case 0xFF:
            task->sprites[1].frame = 0;
            done = 1;
            break;
        case 0x12C:
            task->sprites[1].frame = 0;
            break;
        default:
            task->sprites[1].frame = task->frame + frame;
            break;
        }
        if (done) {
            task->setState(task, TASK_RUN);
        }
        if (task->sprites[0].frame != 0 && func_800A5288(task->x, task->y, 0x20, 0x20)) {
            layer->addSortedCallback(layer, func_800A51A0, task, task->y, 0);
        }
        if (task->sprites[1].frame != 0 && func_800A5288(task->x, task->y - 0x20, 0x20, 0x40)) {
            layer->addSortedCallback(layer, func_800A51A0, task, task->y + 0x12, 1);
        }
        break;
    case TASK_KILL:
        break;
    }
}

StageEffect *func_800A55DC(s32 x, s32 y, s32 frame) {
    StageEffect *task = createTaskWithId(func_800A534C, sizeof(StageEffect), 0, 0x17);

    task->x = x;
    task->y = y;
    task->frame = frame;
    return task;
}

/* Creates the StageEffect of func_800A534C at (0x1CC, 0x1B4) with frame 0x3C */
void *func_800A5638(s32 id) {
    StageEffect *task = createTaskWithId(func_800A534C, sizeof(StageEffect), 0, id);

    task->x = 0x1CC;
    task->y = 0x1B4;
    task->frame = 0x3C;
    return task;
}

/* Sets the task to TASK_DONE when the id is 0x335 */
void func_800A5680(Task *task, s32 id) {
    if (task != NULL && id == 0x335) {
        task->setState(task, TASK_DONE);
    }
}

void func_800A56B8(void) {
    FLAGS_00.applyAction(0x4074, 1);
    FLAGS_00.applyAction(0x7400, 1);
}

void func_800A5704(void) {
    FLAGS_00.applyAction(0x4075, 1);
}

/* Sets the progress to 43 and applies flag action 0x7401 */
void func_800A5730(void) {
    GAME_PROGRESS = 43;
    FLAGS_00.applyAction(0x7401, 1);
}

#if VERSION_US
void func_800A5768(void) {
    D_800990B4.unk44 = 0xFE;
    D_800990B4.unk8 = 0x704;
    D_800990B4.unkC = 0x7050000;
    D_800990B4.unk10 = D_800A6520;
    D_800990B4.unk14 = D_800A6544;
    D_800990B4.unk1C = 0x703;
    DEBUG_LOG();
    D_800990B4.unk2C = 0x24700;
    D_800990B4.unk30 = 0x18C00;
    D_800990B4.unk28 = D_800A6334;
    D_800990B4.unk3C = 0x44;
    D_800990B4.unk4C = D_800A64FC;
    D_800990B4.unk20 = D_800A6318;
    D_800990B4.unk34 = 0;
    D_800990B4.unk40 = 0x61100001;
    D_800990B4.events = D_800A65A8;
    D_8009A70C.unk40(0, 0x7050001);
    D_8009A70C.unk40(7, 0x7050002);
    D_8009A70C.unk50(0);
}
#elif VERSION_EU
INCLUDE_ASM("stages/nonmatchings/wstag820", func_800A5768);
#endif

void func_800A5730();
extern s32 D_800A6108[];
extern s32 D_800A6114[];
extern s32 D_800A6120[];
extern s32 D_800A612C[];
extern s32 D_800A6138[];
extern s32 D_800A6144[];
extern s32 D_800A6150[];
extern s32 D_800A615C[];
extern s32 D_800A618C[];
extern s32 D_800A6198[];
extern s32 D_800A61A4[];
extern s32 D_800A61B0[];
extern s32 D_800A61BC[];
extern s32 D_800A61C8[];
extern s32 D_800A61D4[];
extern s32 D_800A61E0[];
extern s32 D_800A6210[];
extern s32 D_800A621C[];
extern s32 D_800A6228[];
extern s32 D_800A6234[];
extern s32 D_800A6240[];
extern s32 D_800A624C[];
extern s32 D_800A6258[];
extern s32 D_800A6264[];
extern s32 D_800A6294[];
extern s32 D_800A62A0[];
extern s32 D_800A62AC[];
extern s32 D_800A62B8[];
extern s32 D_800A62C4[];
extern s32 D_800A62D0[];
extern s32 D_800A62DC[];
extern s32 D_800A62E8[];
extern s32 D_800A6168[];
extern s32 D_800A61EC[];
extern s32 D_800A6270[];
extern s32 D_800A62F4[];
extern s32 D_800A6414[];
extern s32 D_800A6420[];
extern s32 D_800A6428[];
extern s32 D_800A6430[];
extern s32 D_800A6438[];
extern s32 D_800A6440[];
extern s32 D_800A6448[];
extern s32 D_800A6450[];
extern s32 D_800A645C[];
extern s32 D_800A6470[];
extern s32 D_800A6484[];
extern s32 D_800A6498[];
extern s32 D_800A64AC[];
extern s32 D_800A64C0[];
extern s32 D_800A64D4[];
extern s32 D_800A64E8[];
extern s32 D_800A5868[];
extern s32 D_800A5A1C[];
extern s32 D_800A5B10[];

s32 D_800A5868[] = {
    0x10100, 0x2280310, 0x10101, 0x30001,
    0x1880100, 0x1910242, 0x1880101, 0x30001,
    0x1E0300, 0x10102, 0x20402C8, 0x3020003,
    0x1020001, 0x2A80001, 0x301DD, 0x10302,
    0x10101, 0x30001, 0x3230101, 0x10325,
    0x3C0300, 0x3230101, 0x10326, 0x1E0300,
    0x10102, 0x1B60288, 0x3020003, 0x1020001,
    0x2780001, 0x301AE, 0x10302, 0x10101,
    0x30001, 0x1880101, 0x70001, 0x3C0300,
    512, 0xD50001, 0x3010004, 0x1E0300,
    512, 0x10002, 0x3010003, 0x3C0300,
    512, 0xD50003, 0x3010004, 0x1E0300,
    512, 0x10004, 0x1010003, 0x70001,
    0x3010003, 0x10101, 0x30001, 0x3C0300,
    512, 0xD50005, 0x3010004, 0x1E0300,
    0x3230101, 0x10325, 0x3C0300, 0x3230101,
    0x10326, 0x1E0300, 512, 0x10006,
    0x1010003, 0x70001, 0x3010003, 0x10101,
    0x30001, 0x3C0300, 512, 0xD50007,
    0x3010004, 0x1E0300, 512, 0x10008,
    0x1010003, 0x70001, 0x3010003, 0x10101,
    0x30001, 0x1E0300, 512, 0xD50009,
    0x3010004, 0x1E0300, 512, 0x1000A,
    0x1010003, 0xC0001, 0x3010003, 0x10101,
    0x30001, 0x3C0300, 512, 0xD5000B,
    0x3010004, 0x1E0300, 512, 0x1000C,
    0x1010003, 0xC0001, 0x3010003, 0x1E0300,
    0,
};
s32 D_800A5A1C[] = {
    0x20100, 0x1AE0278, 0x20101, 0x30001,
    0x1880100, 0x1910242, 0x1880101, 0x70001,
    0x780300, 512, 0x20001, 0x1010003,
    0x70002, 0x3010003, 0x20101, 0x30001,
    0x3C0300, 512, 0xD50002, 0x3010004,
    0x1E0300, 0x1880101, 0x10001, 0x1E0300,
    1537, 0x1AA0242, 0x20101, 0x20001,
    0x1880102, 0x1C001DF, 0x3020001, 0x1010188,
    0x10188, 0x3000007, 0x101001E, 0x37A032D,
    0x1010002, 0x335034D, 0x3000002, 0x1000048,
    392, 0x1010000, 0x10188, 0x1010001,
    0x3250323, 0x3000002, 0x101003C, 0x3260323,
    0x3000002, 0x200001E, 0x30000, 0x10002,
    0x20101, 0x20001, 0x3000301, 0x600001E,
    0x20000, 0x20101, 0x30001, 0x3C0300,
    0,
};
s32 D_800A5B10[] = {
    0x10601, 0x1000180, 0x20102, 0x1000180,
    0x1000003, 0x15000D5, 0x10100E8, 0x100D5,
    0x1000003, 0xF900D7, 0x10100B1, 0x100D7,
    0x1000007, 0x11900D8, 0x1010076, 0x100D8,
    0x1000007, 0x7800D9, 0x10100C5, 0x100D9,
    0x1000007, 0x7900DA, 0x1010075, 0x100DA,
    0x1010007, 0x337032D, 0x3000002, 0x101001E,
    0x10002, 0x3000003, 0x101001E, 0x3250323,
    0x3000002, 0x101003C, 0x3260323, 0x3000002,
    0x601001E, 0xF80000, 0x30000BC, 0x200005A,
    0x170000, 0x400D5, 0x1010301, 0x369032D,
    0x3000002, 0x300001E, 0x101003C, 0x5000D7,
    0x1010007, 0x5000D8, 0x1010007, 0x5000D9,
    0x1010007, 0x5000DA, 0x1010007, 0x36E032D,
    0x3030002, 0x10000D7, 215, 0x1010000,
    0x100D7, 0x1000000, 216, 0x1010000,
    0x100D8, 0x1000000, 217, 0x1010000,
    0x100D9, 0x1000000, 218, 0x1010000,
    0x100DA, 0x3000000, 0x601003C, 0x1200000,
    0x30000CE, 0x100003C, 0x12000D6, 0x10100CE,
    0x4F00D6, 0x1010007, 0x378032D, 0x3030002,
    0x10100D6, 0x100D6, 0x3000007, 0x200001E,
    0x10000, 0x200D6, 0x1010301, 0x100D5,
    0x3000007, 0x600001E, 0xD50000, 512,
    0xD50002, 0x3010004, 0x3230101, 0x20325,
    0x3C0300, 0x3230101, 0x20326, 0x1E0300,
    512, 0x20003, 0x1010001, 0x70002,
    0x3010003, 0x20101, 0x30001, 0x1E0300,
    1537, 0xCE0120, 0x3C0300, 512,
    0xD60004, 0x3010002, 0x1E0300, 0xD50101,
    0x30001, 0x1E0300, 512, 0xD50005,
    0x3010004, 0x1E0300, 512, 0xD60006,
    0x3010002, 0x3230101, 0x20325, 0x3C0300,
    0x3230101, 0x20326, 0x1E0300, 512,
    0xD50007, 0x3010004, 0x1E0300, 512,
    0xD60008, 0x3010002, 0x1E0300, 512,
    0xD50009, 0x3010004, 1537, 0xE80150,
    0x3C0300, 512, 0xD5000A, 0x1010004,
    0x5200D5, 0x1010001, 0x5100D6, 0x1010007,
    0x36F032D, 0x3030002, 0x10000D5, 213,
    0x1010000, 0x100D5, 0x1010000, 0x100D6,
    0x3000007, 0x200005A, 0xB0000, 0x10002,
    0x20101, 0x30007, 0x1010301, 0x10002,
    0x3000003, 0x200001E, 0xC0000, 0x100D6,
    0x3000301, 0x101001E, 0x5700D6, 0x1010007,
    0x379032D, 0x3030002, 0x10000D6, 214,
    0x1010000, 0x100D6, 0x3000000, 0x101003C,
    0x3250323, 0x3000002, 0x101003C, 0x3260323,
    0x3000002, 0x601001E, 0xE00000, 0x1020086,
    0x1200002, 0x300D0, 0x20302, 0x20101,
    0x30001, 0xD60100, 0x7400C2, 0xD60101,
    0x7004F, 0x32D0101, 0x20378, 0xD60303,
    0xD60101, 0x70001, 0x3C0300, 0x32D0101,
    0x20372, 0x5A0300, 0x3230101, 0x20325,
    0x5A0300, 0x3230101, 0x20326, 0x32D0101,
    0x32D0373, 0x1E0300, 512, 0x2000D,
    0x3010000, 0x1E0300, 512, 0xD6000E,
    0x3010001, 0x1E0300, 512, 0x2000F,
    0x3010000, 0x1E0300, 512, 0xD60010,
    0x3010001, 0x1E0300, 0x3230101, 0x20325,
    0x3C0300, 0x3230101, 0x20326, 0x1E0300,
    512, 0x20011, 0x1010000, 0x70002,
    0x3010003, 0x20101, 0x30001, 0x1E0300,
    512, 0xD60012, 0x3010001, 0x1E0300,
    512, 0x20013, 0x1010000, 0x70002,
    0x3010003, 0x20101, 0x30001, 0x1E0300,
    512, 0xD60014, 0x3010001, 0x1E0300,
    512, 0x20015, 0x1010000, 0x70002,
    0x3010003, 0x20101, 0x30001, 0x1E0300,
    512, 0xD60016, 0x3010001, 0x1E0300,
    0x32D0101, 0x32D0372, 0x5A0300, 0x3230101,
    0x20325, 0x3C0300, 0x3230101, 0x20326,
    0x3550101, 0x20335, 0x1E0300, 0x32D0101,
    0x20370, 0x3C0300, 0x20100, 0,
    0x20101, 0x30001, 0x3C0300, 0x32D0101,
    0x20371, 0x60300, 0x32D0101, 0x20373,
    0x1E0300, 0,
};
AnimFrame D_800A5FD8[] = {
    { 61, 6 }, { 62, 6 }, { 63, 6 }, { 64, 6 },
    { 65, 4 }, { 66, 4 }, { 67, 4 }, { 65, 4 },
    { 66, 4 }, { 67, 4 }, { 65, 4 }, { 66, 4 },
    { 67, 4 }, { 65, 4 }, { 66, 4 }, { 67, 4 },
    { 65, 4 }, { 66, 4 }, { 67, 4 }, { 65, 4 },
    { 66, 4 }, { 67, 4 }, { 65, 4 }, { 66, 4 },
    { 67, 4 }, { 65, 4 }, { 66, 4 }, { 67, 4 },
    { 65, 4 }, { 66, 4 }, { 67, 4 }, { 64, 6 },
    { 63, 6 }, { 62, 6 }, { 61, 6 }, { 255, 0x3E7 },
};
StageEffectSpot D_800A6068[] = {
    { 60, 2, 0x1CC, 0x1B4 },
    { 60, 0, 0x1CC, 0x1B4 },
    { 60, 0, 0x28C, 0x155 },
    { 44, 0, 0x16C, 242 },
};
AnimFrame D_800A6098[] = {
    { 0, 6 }, { 1, 6 }, { 2, 68 }, { 1, 4 },
    { 0, 4 }, { 255, 0 },
};
AnimFrame D_800A60B0[] = {
    { 0x12C, 18 }, { 1, 6 }, { 2, 6 }, { 3, 6 },
    { 4, 6 }, { 5, 4 }, { 6, 4 }, { 7, 4 },
    { 5, 4 }, { 6, 4 }, { 7, 4 }, { 5, 4 },
    { 6, 4 }, { 7, 4 }, { 5, 4 }, { 6, 4 },
    { 7, 4 }, { 4, 4 }, { 3, 4 }, { 2, 4 },
    { 1, 4 }, { 255, 0x3E7 },
};
s32 D_800A6108[] = {
    0, 0, 0x60040000,
};
s32 D_800A6114[] = {
    0, 0, 0x60040000,
};
s32 D_800A6120[] = {
    0, 0, 0x60040000,
};
s32 D_800A612C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6138[] = {
    0, 0, 0x60040000,
};
s32 D_800A6144[] = {
    0, 0, 0x60040000,
};
s32 D_800A6150[] = {
    0, 0, 0x60040000,
};
s32 D_800A615C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6168[] = {
    0, (s32)D_800A6108, (s32)D_800A6114, (s32)D_800A6120,
    (s32)D_800A612C, (s32)D_800A6138, (s32)D_800A6144, (s32)D_800A6150,
    (s32)D_800A615C,
};
s32 D_800A618C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6198[] = {
    0, 0, 0x60040000,
};
s32 D_800A61A4[] = {
    0, 0, 0x60040000,
};
s32 D_800A61B0[] = {
    0, 0, 0x60040000,
};
s32 D_800A61BC[] = {
    0, 0, 0x60040000,
};
s32 D_800A61C8[] = {
    0, 0, 0x60040000,
};
s32 D_800A61D4[] = {
    0, 0, 0x60040000,
};
s32 D_800A61E0[] = {
    0, 0, 0x60040000,
};
s32 D_800A61EC[] = {
    0, (s32)D_800A618C, (s32)D_800A6198, (s32)D_800A61A4,
    (s32)D_800A61B0, (s32)D_800A61BC, (s32)D_800A61C8, (s32)D_800A61D4,
    (s32)D_800A61E0,
};
s32 D_800A6210[] = {
    0, 0, 0x60040000,
};
s32 D_800A621C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6228[] = {
    0, 0, 0x60040000,
};
s32 D_800A6234[] = {
    0, 0, 0x60040000,
};
s32 D_800A6240[] = {
    0, 0, 0x60040000,
};
s32 D_800A624C[] = {
    0, 0, 0x60040000,
};
s32 D_800A6258[] = {
    0, 0, 0x60040000,
};
s32 D_800A6264[] = {
    0, 0, 0x60040000,
};
s32 D_800A6270[] = {
    0, (s32)D_800A6210, (s32)D_800A621C, (s32)D_800A6228,
    (s32)D_800A6234, (s32)D_800A6240, (s32)D_800A624C, (s32)D_800A6258,
    (s32)D_800A6264,
};
s32 D_800A6294[] = {
    33, 17, 0x608C0000,
};
s32 D_800A62A0[] = {
    324, 21, 0x60900000,
};
s32 D_800A62AC[] = {
    325, 22, 0x60980000,
};
s32 D_800A62B8[] = {
    326, 22, 0x60980000,
};
s32 D_800A62C4[] = {
    0, 0, 0x60040000,
};
s32 D_800A62D0[] = {
    0, 0, 0x60040000,
};
s32 D_800A62DC[] = {
    0, 0, 0x60040000,
};
s32 D_800A62E8[] = {
    0, 0, 0x60040000,
};
s32 D_800A62F4[] = {
    0, (s32)D_800A6294, (s32)D_800A62A0, (s32)D_800A62AC,
    (s32)D_800A62B8, (s32)D_800A62C4, (s32)D_800A62D0, (s32)D_800A62DC,
    (s32)D_800A62E8,
};
s32 D_800A6318[] = {
    141, 0, 0, (s32)D_800A6168,
    (s32)D_800A61EC, (s32)D_800A6270, (s32)D_800A62F4,
};
u8 D_800A6334[] = {
    0x00, 0x02, 0x00, 0x01, 0x1C, 0x02, 0xA6, 0x01,
    0x70, 0x00, 0xA6, 0x00, 0x30, 0x02, 0xFE, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x02, 0xFE, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x16, 0x02, 0x38, 0x01,
    0x58, 0x00, 0x38, 0x00, 0x00, 0x02, 0xFD, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x08, 0x02, 0xBC, 0x01,
    0x20, 0x00, 0xBC, 0x00, 0x10, 0x02, 0xFD, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x10, 0x02, 0xBC, 0x01,
    0x40, 0x00, 0xBC, 0x00, 0x20, 0x02, 0xFD, 0x01,
    0x00, 0x02, 0x00, 0x01, 0x00, 0x02, 0xBC, 0x01,
    0x00, 0x00, 0xBC, 0x00, 0x30, 0x02, 0xFD, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x4A, 0x01, 0x78, 0x01,
    0x28, 0x00, 0x78, 0x00, 0x60, 0x01, 0xFC, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x52, 0x01, 0x00, 0x01,
    0x48, 0x00, 0x00, 0x00, 0x70, 0x01, 0xFC, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x40, 0x01, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x40, 0x01, 0xFB, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x4A, 0x01, 0x58, 0x01,
    0x28, 0x00, 0x58, 0x00, 0x50, 0x01, 0xFB, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x5A, 0x01, 0xC0, 0x01,
    0x68, 0x00, 0xC0, 0x00, 0x60, 0x01, 0xFB, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x70, 0x01, 0x98, 0x01,
    0xC0, 0x00, 0x98, 0x00, 0x70, 0x01, 0xFB, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x6A, 0x01, 0xC0, 0x01,
    0xA8, 0x00, 0xC0, 0x00, 0x40, 0x01, 0xFA, 0x01,
    0x40, 0x01, 0x00, 0x01, 0x62, 0x01, 0x00, 0x01,
    0x88, 0x00, 0x00, 0x00, 0x50, 0x01, 0xF9, 0x01,
};
s32 D_800A6414[] = {
    0x16029, 16500, 65535,
};
s32 D_800A6420[] = {
    0x16029, 65535,
};
s32 D_800A6428[] = {
    0x16029, 65535,
};
s32 D_800A6430[] = {
    0x16029, 65535,
};
s32 D_800A6438[] = {
    0x16029, 65535,
};
s32 D_800A6440[] = {
    0x16029, 65535,
};
s32 D_800A6448[] = {
    0x16029, 65535,
};
s32 D_800A6450[] = {
    16501, 0x16029, 65535,
};
s32 D_800A645C[] = {
    (s32)D_800A6414, 0, 0x40001, 0,
    1,
};
s32 D_800A6470[] = {
    (s32)D_800A6420, 0, 0x500D5, 0xE80150,
    3,
};
s32 D_800A6484[] = {
    (s32)D_800A6428, 0, 0x600D6, 0,
    1,
};
s32 D_800A6498[] = {
    (s32)D_800A6430, 0, 0x700D7, 0xB100F9,
    7,
};
s32 D_800A64AC[] = {
    (s32)D_800A6438, 0, 0x800D8, 0x760119,
    7,
};
s32 D_800A64C0[] = {
    (s32)D_800A6440, 0, 0x900D9, 0xC50078,
    7,
};
s32 D_800A64D4[] = {
    (s32)D_800A6448, 0, 0xA00DA, 0x750079,
    7,
};
s32 D_800A64E8[] = {
    (s32)D_800A6450, 0, 0xB0188, 0x1910242,
    7,
};
s32 D_800A64FC[] = {
    (s32)D_800A645C, (s32)D_800A6470, (s32)D_800A6484, (s32)D_800A6498,
    (s32)D_800A64AC, (s32)D_800A64C0, (s32)D_800A64D4, (s32)D_800A64E8,
    0,
};
u8 D_800A6520[] = {
    0x00, 0x01, 0x40, 0x02, 0x3D, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0C, 0x01, 0xA4, 0x00, 0xD0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};
u8 D_800A6544[] = {
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0x00, 0xDE, 0x02, 0xA0, 0x00, 0x7C, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x0D, 0x00, 0xDF, 0x02, 0x80, 0x01, 0xFE, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xA5, 0x40, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x08, 0x00, 0x38, 0x04, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
void (*D_800A65A4[])(void) = {
    func_800A5768,
};
s32 D_800A65A8[] = {
    1060, (s32)D_800A5868,
#if VERSION_US
    0x14A000F,
#elif VERSION_EU
    0x151000F,
#endif
    0, (s32)func_800A56B8, 1070, (s32)D_800A5A1C,
#if VERSION_US
    0x14A0010,
#elif VERSION_EU
    0x1510010,
#endif
    0, (s32)func_800A5704, 1080, (s32)D_800A5B10,
#if VERSION_US
    0x14A0011,
#elif VERSION_EU
    0x1510011,
#endif
    0, (s32)func_800A5730, -1, 0,
    0, 0, 0,
};
