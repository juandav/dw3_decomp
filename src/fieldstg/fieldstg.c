#include "fieldstg.h"

void func_80082F1C(Task *task) {
    switch (task->state) {
    case 0:
    case 1:
    default:
        if (task->substate == 1) {
            func_80090154();
            task->setSubstate(task, 0);
        }
        break;
    case 2:
    case 3:
        break;
    }
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80082F84);

void func_80083470(void) {
    createTaskWithId(func_80082F1C, sizeof(Task), 0, 0x32D);
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800834A0);

void func_800838BC(Unk800834A0 *task, s32 arg1) {
    if (task != NULL) {
        switch (arg1) {
        case 0x348:
            task->setState(task, 2);
            task->unk58 = 0;
            break;
        case 0x349:
            task->setState(task, 2);
            task->unk58 = 1;
            break;
        }
    }
}

Unk800834A0 *func_80083930(s32 id) {
    Unk800834A0 *task = createTaskWithId(func_800834A0, sizeof(Unk800834A0), 0, id);

    if (FLAG_FUNCS.checkCondition(0x1C3D, 1)) {
        task->unk58 = 1;
    } else {
        task->unk58 = 0;
    }
    return task;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80083998);

void func_80083F8C(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 0;
}

void func_80083FBC(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 1;
}

void func_80083FF0(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 2;
}

void func_80084024(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 3;
}

void func_80084058(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 4;
}

void func_8008408C(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 5;
}

void func_800840C0(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 6;
}

void func_800840F4(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 7;
}

void func_80084128(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 8;
}

void func_8008415C(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 9;
}

void func_80084190(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 10;
}

void func_800841C4(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 11;
}

void func_800841F8(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 12;
}

void func_8008422C(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 13;
}

void func_80084260(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 14;
}

void func_80084294(void) {
    ChoiceTask *task = createTask(func_80083998, sizeof(ChoiceTask), 0x14);
    task->type = 15;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800842C8);

Unk800842C8 *func_800844B8(s32 arg0) {
    Unk800842C8 *task = createTask(func_800842C8, sizeof(Unk800842C8), 8);

    task->unk50 = arg0;
    D_80098B6C[0]();
    return task;
}

s32 func_80084514(Unk80084654 *arg0, s32 id) {
    s32 i;

    if (id < 0x320) {
        for (i = 0; i < 30; i++) {
            if (arg0->entries[i].id == 0) {
                break;
            }
            if (arg0->entries[i].id == id) {
                return arg0->entries[i].value;
            }
        }
    }
    return 0;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80084558);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80084654);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80084B80);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80084D0C);

void func_80085240(s32 arg0) {
    Unk80084D0C *task = createTask(func_80084D0C, sizeof(Unk80084D0C), 0);

    task->unk50 = arg0;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80085278);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80085350);

void func_80085588(s32 arg0, s32 arg1, s32 arg2) {
    Unk80085350 *task = createTask(func_80085350, sizeof(Unk80085350), 0);

    task->unk50 = arg0;
    task->unk54 = arg1;
    task->unk58 = arg2;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800855E0);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80085650);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800857DC);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80085A00);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80085A78);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80085EEC);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80086144);

Point *func_800863F4(Unk80086144 *arg0) {
    D_8009A938.x = arg0->unk68 << 7;
    D_8009A938.y = arg0->unk6C << 7;
    return &D_8009A938;
}

void func_80086418(s32 arg0) {
    Unk80086144 *task = createTaskWithId(func_80086144, sizeof(Unk80086144), 0x7C, 4);

    task->unk64 = arg0;
    task->unk130 = func_800863F4;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80086460);

void func_800864E8(StreamTask *task) {
    task->time = GFX_FUNCS.getTime();
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80086518);

s32 func_800865A0(StreamTask *task) {
    return task->loaded;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800865AC);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80086858);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800868AC);

void func_80086A3C(StreamTask *task) {
    task->unk70 = -1;
}

s32 func_80086A48(StreamTask *task) {
    return task->unk70;
}

s32 func_80086A54(StreamTask *task) {
    return task->frame;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80086A60);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80086B54);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80086C4C);

void func_80086CF4(void) {
    createTask(func_80086C4C, sizeof(Task), 0xC);
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80086D20);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80086E64);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80086FB4);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800870D4);

Task *func_800874C8(s32 arg0) {
    Task *task = createTaskWithId(func_800870D4, sizeof(Unk800870D4), 8, 9);

    task->key1 = arg0;
    D_800990B4.unk54 = 1;
    return task;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80087510);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800875DC);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800876E4);

void func_800878A4(s32 arg0, s32 arg1, s32 arg2) {
    Task *task = createTaskWithId(func_800876E4, 0x6C, 0, arg2);
    task->key1 = arg0;
    task->key2 = arg1;
}

void func_800878F0(s32 arg0) {
    func_800878A4(0, 0, arg0);
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80087918);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800879E8);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80087ACC);

INCLUDE_RODATA("asm/fieldstg/nonmatchings/fieldstg", D_80082624);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80087D28);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80087FDC);

void func_800881A0(s32 arg0) {
    Unk80087FDC *task = createTask(func_80087FDC, sizeof(Unk80087FDC), 8);

    task->unk50 = arg0;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800881D8);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800882D8);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800883F4);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008848C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80088640);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008878C);

void func_80088BE4(s32 arg0, s32 arg1) {
    Unk8008878C *task = createTask(func_8008878C, sizeof(Unk8008878C), 4);

    task->unk54 = arg1;
    task->unk50 = arg0;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80088C2C);

void func_80088C9C(s32 arg0) {
    D_8009A944 = arg0;
    D_8009A940 = D_800990B4.unk10;
    func_80088C2C();
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80088CD0);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80088D5C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80088E4C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008926C);

void func_800892E8(s32 arg0) {
    Task *task = createTask(func_8008926C, 0x54, 0);

    task->key2 = arg0;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80089320);

Unk80089320 *func_80089668(Actor *actor) {
    Unk80089320 *task;

    if (GAME_FUNCS.getMode() < 0x2D7) {
        task = createTaskWithId(func_80089320, sizeof(Unk80089320), 0, 0x16);
        task->actor = actor;
        return task;
    }
    return NULL;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800896C0);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80089D28);

s32 func_8008A0F4(void) {
    if (GAME.funcs.getMode() == 0x22D) {
        return 1;
    }
    return GAME.funcs.getMode() == 0x2DE;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008A154);

void func_8008ADE8(void) {
    createTaskWithId(func_8008A154, 0x80, 0x7C, 7);
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008AE18);

void func_8008AEB4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_8008AE18(arg0, arg1, arg2, arg3, arg4, 0);
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008AEDC);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008B258);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008B2C4);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008B320);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008B398);

s32 func_8008B410(s32 angle, s32 radius) {
    return rsin(angle >> 2) * radius / 4096;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008B450);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008B930);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008B9D8);

void func_8008BBD4(Point from, Point to) {
    Unk8008B9D8 *task = createTask(func_8008B9D8, sizeof(Unk8008B9D8), 0);

    task->from = from;
    task->to = to;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008BC30);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008BCAC);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008BFE8);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008C160);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008C23C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008C2F4);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008C388);

void func_8008C564(s32 arg0) {
    Task *task = createTask(func_8008C388, 0x64, 0);

    task->key1 = arg0;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008C59C);

void func_8008C9F8(Point pos) {
    Unk8008C59C *task = createTask(func_8008C59C, sizeof(Unk8008C59C), 0);

    task->pos = pos;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008CA3C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008CC4C);

void func_8008CF0C(void) {
    Unk8008CC4C *task = createTaskWithId(func_8008CC4C, sizeof(Unk8008CC4C), 0, 0x10);

    task->unk64 = -1;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008CF44);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008CFF4);

void func_8008D07C(s32 arg0) {
    Unk8008CC4C *task = TASK_FUNCS.find(0x10, -1, -1);

    if (task != NULL) {
        task->unk5C = arg0;
    }
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008D0C0);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008D2A0);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008D3F0);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008D4C4);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008D580);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008D710);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008DB60);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008DCF8);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008DD9C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008DFE0);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008E1A4);

void func_8008E284(Actor *actor, s32 arg1, s32 arg2, s32 arg3) {
    actor->unkEC = 1;
    actor->unkF0 = arg1;
    actor->unkF4 = arg2;
    actor->unkF8 = arg3;
}

s32 func_8008E29C(Actor *actor) {
    return actor->unkEC;
}

void func_8008E2A8(Actor *actor) {
    actor->unk108 = func_8008E1A4;
}

void func_8008E2B8(Actor *actor) {
    switch (actor->key2) {
    case 0:
        actor->unk108 = func_8008DB60;
        actor->unkBC = 0;
        break;
    case 1:
        actor->unk108 = NULL;
        break;
    case 2:
    case 4:
    case 8:
        actor->unk108 = func_8008DD9C;
        break;
    }
}

void func_8008E318(Actor *actor, s32 dir) {
    actor->unk108 = NULL;
    actor->setSubstate(actor, 5);
    actor->dir = dir;
}

void func_8008E358(Actor *actor, s32 dir) {
    if (actor->substate != 0x4F) {
        actor->unk108 = NULL;
        actor->setSubstate(actor, 0x4F);
        actor->dir = dir;
    }
}

void func_8008E3A4(Actor *actor) {
    if (actor->substate == 0x4F) {
        actor->setSubstate(actor, 0x50);
    }
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008E3DC);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008E488);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008E534);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008E5B8);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008E698);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008E700);

void func_8008E768(Actor *actor, s32 arg1) {
    actor->unkA0 = arg1;
    actor->unkCC = 0;
    actor->unkD0 = 0;
    actor->unkE8 = 0;
}

void func_8008E77C(Actor *actor, s32 arg1, s32 dir) {
    actor->unkEC = 0;
    actor->setSubstate(actor, 0);
    actor->dir = dir;
    func_8008E768(actor, arg1);
}

s32 func_8008E7D4(Actor *actor) {
    return actor->unkE8;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008E7E0);

void func_8008EC6C(Actor *actor, s32 arg1) {
    actor->dir = arg1;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008EC74);

void func_8008F014(Actor *actor) {
    actor->unk108 = func_8008DB60;
    actor->unk90 = 0;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008F028);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008F11C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008F184);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80090154);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800901D4);

void func_80090254(Actor *actor, Point *out) {
    Point *delta = &D_80097000[actor->dir];

    out->x = actor->tile.x + delta->x;
    out->y = actor->tile.y + delta->y;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80090294);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80090450);

void func_80090864(void) {
    FLAG_FUNCS.applyAction(0x707E, 1);
    FLAG_FUNCS.applyAction(0x8B19, 1);
    FLAG_FUNCS.applyAction(0x400, 1);
}

void func_800908C4(void) {
    FLAG_FUNCS.applyAction(0x400, 1);
}

void func_800908F0(void) {
    FLAG_FUNCS.applyAction(0x707E, 1);
    FLAG_FUNCS.applyAction(0x8B1F, 1);
    FLAG_FUNCS.applyAction(0x401, 1);
}

void func_80090950(void) {
    FLAG_FUNCS.applyAction(0x401, 1);
}

void func_8009097C(void) {
    FLAG_FUNCS.applyAction(0x707F, 1);
    FLAG_FUNCS.applyAction(0x8B1A, 1);
    FLAG_FUNCS.applyAction(0x402, 1);
}

void func_800909DC(void) {
    FLAG_FUNCS.applyAction(0x402, 1);
}

void func_80090A08(void) {
    FLAG_FUNCS.applyAction(0x707F, 1);
    FLAG_FUNCS.applyAction(0x8B20, 1);
    FLAG_FUNCS.applyAction(0x403, 1);
}

void func_80090A68(void) {
    FLAG_FUNCS.applyAction(0x403, 1);
}

void func_80090A94(void) {
    FLAG_FUNCS.applyAction(0x7080, 1);
    FLAG_FUNCS.applyAction(0x8489, 1);
    FLAG_FUNCS.applyAction(0x404, 1);
}

void func_80090AF4(void) {
    FLAG_FUNCS.applyAction(0x404, 1);
}

void func_80090B20(void) {
    FLAG_FUNCS.applyAction(0x7080, 1);
    FLAG_FUNCS.applyAction(0x8495, 1);
    FLAG_FUNCS.applyAction(0x405, 1);
}

void func_80090B80(void) {
    FLAG_FUNCS.applyAction(0x405, 1);
}

void func_80090BAC(void) {
    FLAG_FUNCS.applyAction(0x7081, 1);
    FLAG_FUNCS.applyAction(0x847C, 1);
    FLAG_FUNCS.applyAction(0x406, 1);
}

void func_80090C0C(void) {
    FLAG_FUNCS.applyAction(0x406, 1);
}

void func_80090C38(void) {
    FLAG_FUNCS.applyAction(0x7081, 1);
    FLAG_FUNCS.applyAction(0x8462, 1);
    FLAG_FUNCS.applyAction(0x407, 1);
}

void func_80090C98(void) {
    FLAG_FUNCS.applyAction(0x407, 1);
}

void func_80090CC4(void) {
    FLAG_FUNCS.applyAction(0x7082, 1);
    FLAG_FUNCS.applyAction(0x8ADE, 1);
    FLAG_FUNCS.applyAction(0x408, 1);
}

void func_80090D24(void) {
    FLAG_FUNCS.applyAction(0x408, 1);
}

void func_80090D50(void) {
    FLAG_FUNCS.applyAction(0x7082, 1);
    FLAG_FUNCS.applyAction(0x8AE8, 1);
    FLAG_FUNCS.applyAction(0x409, 1);
}

void func_80090DB0(void) {
    FLAG_FUNCS.applyAction(0x409, 1);
}

void func_80090DDC(void) {
    FLAG_FUNCS.applyAction(0x7083, 1);
    FLAG_FUNCS.applyAction(0x8AF4, 1);
    FLAG_FUNCS.applyAction(0x40A, 1);
}

void func_80090E3C(void) {
    FLAG_FUNCS.applyAction(0x40A, 1);
}

void func_80090E68(void) {
    FLAG_FUNCS.applyAction(0x7083, 1);
    FLAG_FUNCS.applyAction(0x8AF3, 1);
    FLAG_FUNCS.applyAction(0x40B, 1);
}

void func_80090EC8(void) {
    FLAG_FUNCS.applyAction(0x40B, 1);
}

void func_80090EF4(void) {
    FLAG_FUNCS.applyAction(0x7084, 1);
    FLAG_FUNCS.applyAction(0x8B01, 1);
    FLAG_FUNCS.applyAction(0x40C, 1);
}

void func_80090F54(void) {
    FLAG_FUNCS.applyAction(0x40C, 1);
}

void func_80090F80(void) {
    FLAG_FUNCS.applyAction(0x7085, 1);
    FLAG_FUNCS.applyAction(0x8B0D, 1);
    FLAG_FUNCS.applyAction(0x40D, 1);
}

void func_80090FE0(void) {
    FLAG_FUNCS.applyAction(0x40D, 1);
}

void func_8009100C(void) {
    FLAG_FUNCS.applyAction(0x7086, 1);
    FLAG_FUNCS.applyAction(0x8B02, 1);
    FLAG_FUNCS.applyAction(0x40E, 1);
}

void func_8009106C(void) {
    FLAG_FUNCS.applyAction(0x40E, 1);
}

void func_80091098(void) {
    FLAG_FUNCS.applyAction(0x7087, 1);
    FLAG_FUNCS.applyAction(0x8B0F, 1);
    FLAG_FUNCS.applyAction(0x40F, 1);
}

void func_800910F8(void) {
    FLAG_FUNCS.applyAction(0x40F, 1);
}

INCLUDE_RODATA("asm/fieldstg/nonmatchings/fieldstg", D_80082E88);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80091124);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80091298);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8009132C);

s32 func_80091398(s32 index) {
    return D_80099134[index];
}

u8 func_800913B4(s32 index) {
    return D_80099758[index];
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800913CC);

void *func_80091490(u8 *list, s32 id) {
    s32 i;

    for (i = 0; i < 30; i++) {
        if (*(s32 *)(list + 4) == id) {
            return list;
        }
        list += 0x1C;
    }
    return NULL;
}

void func_800914C0(void) {
    HEAP.zero(&D_8009A424, 8);
}

Actor *func_800914F0(s32 arg0) {
    return TASK_FUNCS.find(5, arg0, -1);
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80091520);

void func_800915B0(s32 id, s32 *pc) {
    Actor *actor = func_800914F0(id);

    if (actor->unk138(actor) != 0) {
        (*pc)++;
    }
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800915FC);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80091648);

void func_800916B4(void) {
    Actor *actor = func_800914F0(1);

    if (actor == NULL) {
        actor = func_800914F0(2);
    }
    actor->unk10C = 0;
}

ScriptCommand *func_800916E8(s32 id) {
    ScriptCommand *cmd;

    for (cmd = D_8009A448; cmd->id != 0; cmd++) {
        if (cmd->id == id) {
            return cmd;
        }
    }
    return NULL;
}

s32 func_80091730(s32 id) {
    ScriptCommand *cmd = func_800916E8(id);
    s32 ret = 0;

    if (cmd != NULL) {
        ret = cmd->create(id);
    }
    return ret;
}

void func_80091774(s32 arg0, s32 id, s32 arg2, s32 arg3) {
    ScriptCommand *cmd = func_800916E8(id);

    if (cmd != NULL && cmd->handle != NULL) {
        cmd->handle(arg0, arg2, arg3);
    }
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800917D8);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80091854);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80091910);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80091A4C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80091AA8);

void func_80091B78(s32 index, s32 value) {
    D_8009A70C[index] = value;
}

void func_80091B90(s32 arg0) {
    if (GAME.clearTempFlags != 0) {
        GAME.unk26D8 = arg0;
    }
}

void func_80091BB4(s32 arg0) {
    GAME.unk26D8 = arg0;
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80091BC0);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80091D3C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80091F4C);

void func_8009204C(s32 arg0, s32 scale, s32 index, Point *out) {
    out->x = D_8009A76C[index].x * scale / 4096;
    out->y = D_8009A76C[index].y * scale / 4096;
}
