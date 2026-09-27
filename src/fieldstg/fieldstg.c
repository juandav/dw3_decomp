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

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800838BC);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80083930);

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

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800844B8);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80084514);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80084558);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80084654);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80084B80);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80084D0C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80085240);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80085278);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80085350);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80085588);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800855E0);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80085650);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800857DC);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80085A00);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80085A78);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80085EEC);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80086144);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800863F4);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80086418);

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

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800874C8);

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

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800881A0);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800881D8);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800882D8);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800883F4);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008848C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80088640);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008878C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80088BE4);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80088C2C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80088C9C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80088CD0);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80088D5C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80088E4C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008926C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800892E8);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80089320);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80089668);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800896C0);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80089D28);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008A0F4);

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

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008B410);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008B450);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008B930);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008B9D8);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008BBD4);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008BC30);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008BCAC);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008BFE8);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008C160);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008C23C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008C2F4);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008C388);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008C564);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008C59C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008C9F8);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008CA3C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008CC4C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008CF0C);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008CF44);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008CFF4);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008D07C);

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

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008E2B8);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008E318);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008E358);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008E3A4);

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

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8008E77C);

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

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80090254);

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

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80090A08);

void func_80090A68(void) {
    FLAG_FUNCS.applyAction(0x403, 1);
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80090A94);

void func_80090AF4(void) {
    FLAG_FUNCS.applyAction(0x404, 1);
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80090B20);

void func_80090B80(void) {
    FLAG_FUNCS.applyAction(0x405, 1);
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80090BAC);

void func_80090C0C(void) {
    FLAG_FUNCS.applyAction(0x406, 1);
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80090C38);

void func_80090C98(void) {
    FLAG_FUNCS.applyAction(0x407, 1);
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80090CC4);

void func_80090D24(void) {
    FLAG_FUNCS.applyAction(0x408, 1);
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80090D50);

void func_80090DB0(void) {
    FLAG_FUNCS.applyAction(0x409, 1);
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80090DDC);

void func_80090E3C(void) {
    FLAG_FUNCS.applyAction(0x40A, 1);
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80090E68);

void func_80090EC8(void) {
    FLAG_FUNCS.applyAction(0x40B, 1);
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80090EF4);

void func_80090F54(void) {
    FLAG_FUNCS.applyAction(0x40C, 1);
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80090F80);

void func_80090FE0(void) {
    FLAG_FUNCS.applyAction(0x40D, 1);
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8009100C);

void func_8009106C(void) {
    FLAG_FUNCS.applyAction(0x40E, 1);
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80091098);

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
    HEAP.zero(D_8009A424, 8);
}

void *func_800914F0(s32 arg0) {
    return TASK_FUNCS.find(5, arg0, -1);
}

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80091520);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800915B0);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800915FC);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80091648);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800916B4);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_800916E8);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80091730);

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_80091774);

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

INCLUDE_ASM("asm/fieldstg/nonmatchings/fieldstg", func_8009204C);
