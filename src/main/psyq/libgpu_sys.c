#include "psyq.h"

void func_80027FD0(u_char *dst, int value, int n);
void func_800264B8(DR_ENV *p, DRAWENV *env);
void func_80027978(void);
int func_800279AC(void);
void _GPU_ResetCallback(void);

extern u_long *D_800557B8;
extern u_long *D_800557BC;
extern u_long *D_800557C0;
extern u_long *D_800557C4;
extern u_long D_8005574C[];
extern u_long D_80055760; /* terminator primitive of the ordering tables */
extern u_long D_80055740[]; /* words 2..4 of the 5-word MoveImage packet at D_80055740 - 8 */
extern char D_80010450[]; /* "MoveImage" */

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libgpu_sys", D_8001030C);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", ResetGraph);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", SetGraphDebug);

int SetGraphQueue(int mode) {
    u_char old = D_800556A0.unk1;

    if (D_800556A0.level >= 2) {
        D_8005569C("SetGrapQue(%d)...\n", mode);
    }
    if (mode != D_800556A0.unk1) {
        D_80055698->unk34(1);
        D_800556A0.unk1 = mode;
        DMACallback(2, NULL);
    }
    return old;
}

int GetGraphDebug(void) {
    return D_800556A0.level;
}

u_long DrawSyncCallback(void (*func)()) {
    void (*old)();

    if (D_800556A0.level >= 2) {
        D_8005569C("DrawSyncCallback(%08x)...\n", func);
    }
    old = D_800556A0.drawSyncCallback;
    D_800556A0.drawSyncCallback = func;
    return (u_long)old;
}

void SetDispMask(int mask) {
    if (D_800556A0.level >= 2) {
        D_8005569C("SetDispMask(%d)...\n", mask);
    }
    if (mask == 0) {
        func_80027FD0((u_char *)&D_800556A0.disp, -1, sizeof(DISPENV));
    }
    D_80055698->ctrl(mask ? 0x03000000 : 0x03000001);
}

int DrawSync(int mode) {
    if (D_800556A0.level >= 2) {
        D_8005569C("DrawSync(%d)...\n", mode);
    }
    return D_80055698->sync(mode);
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_800254DC);

int ClearImage(RECT *rect, u_char r, u_char g, u_char b) {
    func_800254DC("ClearImage", rect);
    return D_80055698->addque(D_80055698->unkC, rect, 8, (b << 16) | (g << 8) | r);
}

int ClearImage2(RECT *rect, u_char r, u_char g, u_char b) {
    func_800254DC("ClearImage2", rect);
    return D_80055698->addque(D_80055698->unkC, rect, 8, 0x80000000 | (b << 16) | (g << 8) | r);
}

int LoadImage(RECT *rect, u_long *p) {
    func_800254DC("LoadImage", rect);
    return D_80055698->addque(D_80055698->loadImage, rect, 8, (long)p);
}

int StoreImage(RECT *rect, u_long *p) {
    func_800254DC(D_80010444, rect);
    return D_80055698->addque(D_80055698->storeImage, rect, 8, (long)p);
}

int MoveImage(RECT *rect, int x, int y) {
    func_800254DC(D_80010450, rect);
    if (rect->w == 0 || rect->h == 0) {
        return -1;
    }
    D_80055740[0] = *(u_long *)&rect->x;
    D_80055740[1] = (y << 16) | (x & 0xFFFF);
    D_80055740[2] = *(u_long *)&rect->w;
    return D_80055698->addque(D_80055698->exeque, &D_80055740[-2], 0x14, 0);
}

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libgpu_sys", D_80010444);

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libgpu_sys", D_80010450);

u_long *ClearOTag(u_long *ot, int n) {
    u_long *term;

    if (D_800556A0.level >= 2) {
        D_8005569C("ClearOTag(%08x,%d)...\n", ot, n);
    }
    while (--n) {
        setlen(ot, 0);
        setaddr(ot, ot + 1);
        ot++;
    }
    term = &D_80055760;
    *term = ((u_long)D_8005574C & 0xFFFFFF) | 0x04000000;
    *ot = (u_long)term & 0xFFFFFF;
    return ot;
}

u_long *ClearOTagR(u_long *ot, int n) {
    u_long *term;

    if (D_800556A0.level >= 2) {
        D_8005569C("ClearOTagR(%08x,%d)...\n", ot, n);
    }
    D_80055698->unk2C(ot, n);
    term = &D_80055760;
    *term = ((u_long)D_8005574C & 0xFFFFFF) | 0x04000000;
    *ot = (u_long)term & 0xFFFFFF;
    return ot;
}

void DrawPrim(void *p) {
    int len = getlen(p);

    D_80055698->sync(0);
    D_80055698->unk14((u_long *)p + 1, len);
}

void DrawOTag(u_long *p) {
    if (D_800556A0.level >= 2) {
        D_8005569C(D_8001048C, p);
    }
    D_80055698->addque(D_80055698->exeque, p, 0, 0);
}

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libgpu_sys", D_8001048C);

DRAWENV *PutDrawEnv(DRAWENV *env) {
    if (D_800556A0.level >= 2) {
        D_8005569C("PutDrawEnv(%08x)...\n", env);
    }
    func_800264B8(&env->dr_env, env);
    env->dr_env.tag |= 0xFFFFFF;
    D_80055698->addque(D_80055698->exeque, &env->dr_env, sizeof(DR_ENV), 0);
    memcpy((u_char *)&D_800556A0.draw, (u_char *)env, sizeof(DRAWENV));
    return env;
}

void DrawOTagEnv(u_long *p, DRAWENV *env) {
    if (D_800556A0.level >= 2) {
        D_8005569C("DrawOTagEnv(%08x,&08x)...\n", p, env);
    }
    func_800264B8(&env->dr_env, env);
    env->dr_env.tag = (env->dr_env.tag & 0xFF000000) | ((u_long)p & 0xFFFFFF);
    D_80055698->addque(D_80055698->exeque, &env->dr_env, sizeof(DR_ENV), 0);
    memcpy((u_char *)&D_800556A0.draw, (u_char *)env, sizeof(DRAWENV));
}

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

u_long func_80026728(int dfe, int dtd, int tpage) {
    return (dtd ? 0xE1000200 : 0xE1000000) | (dfe ? 0x400 : 0) | (tpage & 0x9FF);
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_80026748);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_800267E0);

u_long func_80026878(short x, short y) {
    return 0xE5000000 | ((y & 0x7FF) << 11) | (x & 0x7FF);
}

u_long func_80026894(RECT *tw) {
    u_long code[4];
    u_long ret;

    if (tw == NULL) {
        ret = 0;
    } else {
        code[0] = (u_char)tw->x >> 3;
        code[2] = (-tw->w & 0xFF) >> 3;
        code[1] = (u_char)tw->y >> 3;
        code[3] = (-tw->h & 0xFF) >> 3;
        ret = 0xE2000000 | (code[1] << 15) | (code[0] << 10) | (code[3] << 5) | code[2];
    }
    return ret;
}

u_long func_80026914(void) {
    return *D_800557A8;
}

int func_8002692C(u_long *p, int n) {
    *D_800557C4 |= 0x08000000;
    *D_800557C0 = 0;
    *D_800557B8 = (u_long)&p[n - 1];
    *D_800557BC = n;
    *D_800557C0 = 0x11000002;
    func_80027978();
    while (*D_800557C0 & 0x01000000) {
        if (func_800279AC() != 0) {
            return -1;
        }
    }
    return n;
}

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

inline void func_80027978(void) {
    D_800557DC = VSync(-1) + 240;
    D_800557E0 = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_800279AC);

int func_80027AF0(int mode) {
    *D_800557A8 = 0x10000007;
    if ((*D_800557A4 & 0xFFFFFF) != 2) {
        *D_800557A4 = (*D_800557A8 & 0x3FFF) | 0xE1001000;
        *(volatile u_long *)D_800557A4;
        return 0;
    }
    if (!(mode & 8)) {
        return 1;
    }
    *D_800557A8 = 0x09000001;
    return 2;
}

int LoadImage2(RECT *rect, u_long *p) {
    func_800254DC("LoadImage2", rect);
    func_80027978();
    while ((*(volatile u_long *)D_800557B4 & 0x01000000) ||
           !(*(volatile u_long *)D_800557A8 & 0x04000000)) {
        if (func_800279AC() != 0) {
            return -1;
        }
    }
    DMACallback(2, _GPU_ResetCallback);
    D_80055698->loadImage(rect, p);
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", StoreImage2);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", MoveImage2);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", DrawOTag2);

void _GPU_ResetCallback(void) {
    DMACallback(2, func_800274A0);
}

void func_80027FD0(u_char *dst, int value, int n) {
    u_char *p = dst;
    int i = n - 1;

    if (n != 0) {
        do {
            *p++ = value;
        } while (i-- != 0);
    }
}

OBJECT_END();
