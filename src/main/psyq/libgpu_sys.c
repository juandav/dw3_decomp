#include "psyq.h"

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libgpu_sys", D_8001030C);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", ResetGraph);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", SetGraphDebug);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", SetGraphQueue);

int GetGraphDebug(void) {
    return D_800556A2;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", DrawSyncCallback);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", SetDispMask);

int DrawSync(int mode) {
    if (D_800556A2 >= 2) {
        D_8005569C("DrawSync(%d)...\n", mode);
    }
    return D_80055698->sync(mode);
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_800254DC);

int ClearImage(RECT *rect, u_char r, u_char g, u_char b) {
    func_800254DC("ClearImage", rect);
    return D_80055698->addque(D_80055698->unkC, rect, 8, (b << 16) | (g << 8) | r);
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", ClearImage2);

int LoadImage(RECT *rect, u_long *p) {
    func_800254DC("LoadImage", rect);
    return D_80055698->addque(D_80055698->unk20, rect, 8, (long)p);
}

int StoreImage(RECT *rect, u_long *p) {
    func_800254DC(D_80010444, rect);
    return D_80055698->addque(D_80055698->unk1C, rect, 8, (long)p);
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", MoveImage);

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libgpu_sys", D_80010444);

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libgpu_sys", D_80010450);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", ClearOTag);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", ClearOTagR);

void DrawPrim(void *p) {
    int len = getlen(p);

    D_80055698->sync(0);
    D_80055698->unk14((u_long *)p + 1, len);
}

void DrawOTag(u_long *p) {
    if (D_800556A2 >= 2) {
        D_8005569C(D_8001048C, p);
    }
    D_80055698->addque(D_80055698->unk18, p, 0, 0);
}

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libgpu_sys", D_8001048C);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", PutDrawEnv);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", DrawOTagEnv);

DRAWENV *GetDrawEnv(DRAWENV *env) {
    memcpy((u_char *)env, (u_char *)&D_800556B0, sizeof(DRAWENV));
    return env;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", PutDispEnv);

DISPENV *GetDispEnv(DISPENV *env) {
    memcpy((u_char *)env, (u_char *)&D_8005570C, sizeof(DISPENV));
    return env;
}

int GetODE(void) {
    return D_80055698->status() >> 31;
}

void SetDrawArea(DR_AREA *p, RECT *r) {
    setlen(p, 2);
    p->code[0] = func_80026748(r->x, r->y);
    p->code[1] = func_800267E0(r->x + r->w - 1, r->y + r->h - 1);
}

void SetDrawOffset(DR_OFFSET *p, u_short *ofs) {
    setlen(p, 2);
    p->code[0] = func_80026878(ofs[0], ofs[1]);
    p->code[1] = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", SetDrawEnv);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_800264B8);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_80026728);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_80026748);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_800267E0);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_80026878);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_80026894);

u_long func_80026914(void) {
    return *D_800557A8;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_8002692C);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_80026A0C);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_80026C3C);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_80026E78);

void func_800270F8(u_long value) {
    *D_800557A8 = value;
}

void func_8002710C(void) {
}

int func_80027114(u_long *p, int n) {
    int i = n - 1;

    *D_800557A8 = 0x04000000;
    if (n != 0) {
        do {
            *D_800557A4 = *p++;
        } while (i-- != 0);
    }
    return 0;
}

void func_80027154(u_long addr) {
    *D_800557A8 = 0x04000002;
    *D_800557AC = addr;
    *D_800557B0 = 0;
    *D_800557B4 = 0x01000401;
}

u_long func_8002719C(u_long cmd) {
    *D_800557A8 = cmd | 0x10000000;
    return *D_800557A4 & 0xFFFFFF;
}

int func_800271CC(int arg0, int arg1, int arg2) {
    return func_800271F0(arg0, arg1, 0, arg2);
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_800271F0);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_800274A0);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_80027700);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_8002783C);

void func_80027978(void) {
    D_800557DC = VSync(-1) + 240;
    D_800557E0 = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_800279AC);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_80027AF0);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", LoadImage2);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", StoreImage2);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", MoveImage2);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", DrawOTag2);

void _GPU_ResetCallback(void) {
    DMACallback(2, func_800274A0);
}

void func_80027FD0(u_char *dst, u_char value, int n) {
    u_char *p = dst;
    int i = n - 1;

    if (n != 0) {
        do {
            *p++ = value;
        } while (i-- != 0);
    }
}

OBJECT_END();
