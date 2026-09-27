/* libgpu was built against a SetIntrMask(long) prototype */
#define SetIntrMask SetIntrMask_libetc
#include "psyq.h"
#undef SetIntrMask
long SetIntrMask(long mask);

void func_80027FD0(u_char *dst, int value, int n);
void func_800264B8(DR_ENV *p, DRAWENV *env);
u_long func_80026728(int dfe, int dtd, int tpage);
u_long func_80026894(RECT *tw);
void func_80027978(void);
int func_800279AC(void);
int func_80027AF0(int mode);
void _GPU_ResetCallback(void);
u_long func_8002719C(u_long cmd);
void func_80027154(u_long addr);

extern u_long *D_800557B8;
extern u_long *D_800557BC;
extern u_long *D_800557C0;
extern u_long *D_800557C4;
extern volatile long D_800557C8; /* command queue write index */
extern volatile long D_800557CC; /* command queue read index */
extern long D_800557D8; /* interrupt mask saved by the reset */
typedef struct GpuQueue {
    /* 0x00 */ int (*func)();
    /* 0x04 */ u_long *param;
    /* 0x08 */ u_long value;
    /* 0x0C */ u_long data[21];
} GpuQueue;
extern volatile GpuQueue D_8007F198[64];
extern long D_800557D0; /* interrupt mask saved while queueing */
extern u_long D_8005574C[];
extern u_long D_80055760; /* terminator primitive of the ordering tables */
extern u_long D_80055740[]; /* words 2..4 of the 5-word MoveImage packet at D_80055740 - 8 */
extern char D_80010450[]; /* "MoveImage" */
extern u_long D_8007F148[]; /* clear/fill packet */
extern u_long D_8007F170[]; /* drawing-area restore packet */

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libgpu_sys", D_8001030C);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", ResetGraph);

int SetGraphDebug(int level) {
    int old = D_800556A0.level;

    D_800556A0.level = level;
    if (D_800556A0.level) {
        D_8005569C("SetGraphDebug:level:%d,type:%d reverse:%d\n", D_800556A0.level, D_800556A0.type,
                   D_800556A0.reverse);
    }
    return old;
}

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

void func_800254DC(char *name, RECT *rect) {
    switch (D_800556A0.level) {
    case 1:
        if (rect->w > D_800556A0.w || rect->w + rect->x > D_800556A0.w ||
            rect->y > D_800556A0.h || rect->y + rect->h > D_800556A0.h ||
            rect->w <= 0 || rect->x < 0 || rect->y < 0 || rect->h <= 0) {
            D_8005569C("%s:bad RECT", name);
            D_8005569C("(%d,%d)-(%d,%d)\n", rect->x, rect->y, rect->w, rect->h);
        }
        break;
    case 2:
        D_8005569C("%s:", name);
        D_8005569C("(%d,%d)-(%d,%d)\n", rect->x, rect->y, rect->w, rect->h);
        break;
    }
}

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

void SetDrawEnv(DR_ENV *dr_env, DRAWENV *env) {
    DR_ENV *p = dr_env;
    RECT r;
    int i;

    p->code[0] = func_80026748(env->clip.x, env->clip.y);
    p->code[1] = func_800267E0(env->clip.w + env->clip.x - 1, env->clip.y + env->clip.h - 1);
    p->code[2] = func_80026878(env->ofs[0], env->ofs[1]);
    p->code[3] = func_80026728(env->dfe, env->dtd, env->tpage);
    p->code[4] = func_80026894(&env->tw);
    p->code[5] = 0xE6000000;
    i = 7;
    if (env->isbg) {
        r.x = env->clip.x;
        r.y = env->clip.y;
        r.w = env->clip.w;
        r.h = env->clip.h;
        r.w = (r.w < 0) ? 0 : ((r.w > D_800556A0.w - 1) ? D_800556A0.w - 1 : r.w);
        r.h = (r.h < 0) ? 0 : ((r.h > D_800556A0.h - 1) ? D_800556A0.h - 1 : r.h);
        r.x -= env->ofs[0];
        r.y -= env->ofs[1];
        ((u_long *)p)[i++] = 0x60000000 | (env->b0 << 16) | (env->g0 << 8) | env->r0;
        ((u_long *)p)[i++] = *(u_long *)&r.x;
        ((u_long *)p)[i++] = *(u_long *)&r.w;
    }
    setlen(p, i - 1);
}

void func_800264B8(DR_ENV *dr_env, DRAWENV *env) {
    DR_ENV *p = dr_env;
    RECT r;
    int i;

    p->code[0] = func_80026748(env->clip.x, env->clip.y);
    p->code[1] = func_800267E0(env->clip.w + env->clip.x - 1, env->clip.y + env->clip.h - 1);
    p->code[2] = func_80026878(env->ofs[0], env->ofs[1]);
    p->code[3] = func_80026728(env->dfe, env->dtd, env->tpage);
    p->code[4] = func_80026894(&env->tw);
    p->code[5] = 0xE6000000;
    i = 7;
    if (env->isbg) {
        r.x = env->clip.x;
        r.y = env->clip.y;
        r.w = env->clip.w;
        r.h = env->clip.h;
        r.w = (r.w < 0) ? 0 : ((r.w > D_800556A0.w - 1) ? D_800556A0.w - 1 : r.w);
        r.h = (r.h < 0) ? 0 : ((r.h > D_800556A0.h - 1) ? D_800556A0.h - 1 : r.h);
        if ((r.x & 0x3F) || (r.w & 0x3F)) {
            r.x -= env->ofs[0];
            r.y -= env->ofs[1];
            ((u_long *)p)[i++] = 0x60000000 | (env->b0 << 16) | (env->g0 << 8) | env->r0;
            ((u_long *)p)[i++] = *(u_long *)&r.x;
            ((u_long *)p)[i++] = *(u_long *)&r.w;
        } else {
            ((u_long *)p)[i++] = 0x02000000 | (env->b0 << 16) | (env->g0 << 8) | env->r0;
            ((u_long *)p)[i++] = *(u_long *)&r.x;
            ((u_long *)p)[i++] = *(u_long *)&r.w;
        }
    }
    setlen(p, i - 1);
}

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

int func_80026A0C(RECT *rect, u_long color) {
    rect->w = (rect->w < 0) ? 0 : ((rect->w > D_800556A0.w - 1) ? D_800556A0.w - 1 : rect->w);
    rect->h = (rect->h < 0) ? 0 : ((rect->h > D_800556A0.h - 1) ? D_800556A0.h - 1 : rect->h);
    if ((rect->x & 0x3F) || (rect->w & 0x3F)) {
        D_8007F148[0] = ((u_long)D_8007F170 & 0xFFFFFF) | 0x08000000;
        D_8007F148[1] = 0xE3000000;
        D_8007F148[2] = 0xE4FFFFFF;
        D_8007F148[3] = 0xE5000000;
        D_8007F148[4] = 0xE6000000;
        D_8007F148[5] = (*D_800557A8 & 0x7FF) | 0xE1000000 | ((color >> 31) << 10);
        D_8007F148[6] = (color & 0xFFFFFF) | 0x60000000;
        D_8007F148[7] = *(u_long *)&rect->x;
        D_8007F148[8] = *(u_long *)&rect->w;
        D_8007F170[0] = 0x03FFFFFF;
        D_8007F170[1] = func_8002719C(3) | 0xE3000000;
        D_8007F170[2] = func_8002719C(4) | 0xE4000000;
        D_8007F170[3] = func_8002719C(5) | 0xE5000000;
    } else {
        D_8007F148[0] = 0x05FFFFFF;
        D_8007F148[1] = 0xE6000000;
        D_8007F148[2] = (*D_800557A8 & 0x7FF) | 0xE1000000 | ((color >> 31) << 10);
        D_8007F148[3] = (color & 0xFFFFFF) | 0x02000000;
        D_8007F148[4] = *(u_long *)&rect->x;
        D_8007F148[5] = *(u_long *)&rect->w;
    }
    func_80027154((u_long)D_8007F148);
    return 0;
}

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

int func_800271CC(int (*func)(), u_long *param, u_long value) {
    return func_800271F0(func, param, 0, value);
}

int func_800271F0(int (*func)(), u_long *param, int size, u_long value) {
    int i;
    u_long v;
    GpuDebug *dbg;

    func_80027978();
    while (((D_800557C8 + 1) & 0x3F) == D_800557CC) {
        if (func_800279AC() != 0) {
            return -1;
        }
        func_800274A0();
    }
    D_800557D0 = SetIntrMask(0);
    dbg = &D_800556A0;
    dbg->unk8 = 1;
    if (dbg->unk1 == 0 || (D_800557C8 == D_800557CC && !(*(volatile u_long *)D_800557B4 & 0x01000000) &&
                           dbg->drawSyncCallback == NULL)) {
        do {
        } while (!(*(volatile u_long *)D_800557A8 & 0x04000000));
        func(param, value);
        SetIntrMask(D_800557D0);
        return 0;
    }
    DMACallback(2, func_800274A0);
    if (size != 0) {
        for (i = 0; i < size / 4; i++) {
            v = param[i];
            D_8007F198[D_800557C8].data[i] = v;
        }
        D_8007F198[D_800557C8].param = (u_long *)D_8007F198[D_800557C8].data;
    } else {
        D_8007F198[D_800557C8].param = param;
    }
    D_8007F198[D_800557C8].value = value;
    D_8007F198[D_800557C8].func = func;
    D_800557C8 = (D_800557C8 + 1) & 0x3F;
    SetIntrMask(D_800557D0);
    func_800274A0();
    return (D_800557C8 - D_800557CC) & 0x3F;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgpu_sys", func_800274A0);

inline int func_80027700(int mode) {
    D_800557D8 = SetIntrMask(0);
    D_800557C8 = D_800557CC = 0;
    switch (mode & 7) {
    case 0:
    case 5:
        *D_800557B4 = 0x401;
        *D_800557C4 |= 0x800;
        *D_800557A8 = 0;
        func_80027FD0((u_char *)D_8007F198, 0, sizeof(D_8007F198));
        break;
    case 1:
    case 3:
        *D_800557B4 = 0x401;
        *D_800557C4 |= 0x800;
        *D_800557A8 = 0x02000000;
        *D_800557A8 = 0x01000000;
        break;
    }
    SetIntrMask(D_800557D8);
    if (mode & 7) {
        return 0;
    }
    return func_80027AF0(mode);
}

int func_8002783C(int mode) {
    int n;

    if (mode == 0) {
        func_80027978();
        while (D_800557C8 != D_800557CC) {
            func_800274A0();
            if (func_800279AC() != 0) {
                return -1;
            }
        }
        while ((*(volatile u_long *)D_800557B4 & 0x01000000) ||
               !(*(volatile u_long *)D_800557A8 & 0x04000000)) {
            if (func_800279AC() != 0) {
                return -1;
            }
        }
        return 0;
    }
    n = (D_800557C8 - D_800557CC) & 0x3F;
    if (n != 0) {
        func_800274A0();
    }
    if (((*(volatile u_long *)D_800557B4 & 0x01000000) ||
         !(*(volatile u_long *)D_800557A8 & 0x04000000)) && n == 0) {
        return 1;
    }
    return n;
}

inline void func_80027978(void) {
    D_800557DC = VSync(-1) + 240;
    D_800557E0 = 0;
}

int func_800279AC(void) {
    if (D_800557DC < VSync(-1) || D_800557E0++ > 0xF0000) {
        *(volatile u_long *)D_800557A8;
        printf("GPU timeout:que=%d,stat=%08x,chcr=%08x,madr=%08x\n",
               (D_800557C8 - D_800557CC) & 0x3F, *(volatile u_long *)D_800557A8,
               *(volatile u_long *)D_800557B4, *(volatile u_long *)D_800557AC);
        func_80027700(1);
        return -1;
    }
    return 0;
}

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

int StoreImage2(RECT *rect, u_long *p) {
    func_800254DC(D_80010444, rect);
    func_80027978();
    while ((*(volatile u_long *)D_800557B4 & 0x01000000) ||
           !(*(volatile u_long *)D_800557A8 & 0x04000000)) {
        if (func_800279AC() != 0) {
            return -1;
        }
    }
    DMACallback(2, _GPU_ResetCallback);
    D_80055698->storeImage(rect, p);
    return 0;
}

int MoveImage2(RECT *rect, int x, int y) {
    func_800254DC(D_80010450, rect);
    func_80027978();
    while ((*(volatile u_long *)D_800557B4 & 0x01000000) ||
           !(*(volatile u_long *)D_800557A8 & 0x04000000)) {
        if (func_800279AC() != 0) {
            return -1;
        }
    }
    DMACallback(2, _GPU_ResetCallback);
    if (rect->w == 0 || rect->h == 0) {
        return -1;
    }
    D_80055740[0] = *(u_long *)&rect->x;
    D_80055740[1] = (y << 16) | (x & 0xFFFF);
    D_80055740[2] = *(u_long *)&rect->w;
    D_80055698->exeque(&D_80055740[-2]);
    return 0;
}

int DrawOTag2(u_long *p) {
    if (D_800556A0.level >= 2) {
        D_8005569C(D_8001048C, p);
    }
    func_80027978();
    while ((*(volatile u_long *)D_800557B4 & 0x01000000) ||
           !(*(volatile u_long *)D_800557A8 & 0x04000000)) {
        if (func_800279AC() != 0) {
            return -1;
        }
    }
    DMACallback(2, _GPU_ResetCallback);
    D_80055698->exeque(p);
    return 0;
}

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
