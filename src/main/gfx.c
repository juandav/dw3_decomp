#include "game.h"

/* Small variables, addressed through $gp (see the Makefile) */
static s32 D_8005C47C;
static s32 D_8005C498;
static Obj8001E7DC *D_8005C4A0;
static Obj8001F22C *D_8005C4A8;
static Obj8001F8F8 *D_8005C4B0;
static Obj8001FBE0 *D_8005C4B8;

void func_8001D070(void) {
    D_8004D5B8.unk14 += 0x100;
    D_8004D5B8.unk1C += 0x100;
    D_800484E8.playFrames += 0x100;
    if (D_8004D5B8.vsyncFunc != NULL) {
        D_8004D5B8.vsyncFunc(D_8004D5B8.unk4);
    }
    if (D_8005C498 != 0) {
        D_8004D5B8.unk30 = !D_8004D5B8.unk30;
        PutDispEnv(&D_8004D5B8.disp[D_8004D5B8.unk30]);
    }
    SsSeqCalledTbyT();
    D_8005C498 = 0;
}

void func_8001D114(void) {
    VSyncCallback(func_8001D070);
}

void func_8001D138(s32 draw) {
    s32 i;
    DrawContext *ctx;

    if (draw) {
        s32 j;

        for (j = 0; j < 30; j++) {
            ctx = D_8004D5B8.resources[j];
            if (ctx != NULL) {
                if (ctx->unk84 != 0) {
                    ctx->unk158(ctx);
                }
                if (ctx->unkCC != 0) {
                    ctx->unk160(ctx);
                }
                ctx->unk154(ctx);
            }
        }
    }
    DrawSync(0);
    D_8005C498 = 1;
    while (*(volatile s32 *)&D_8005C498 != 0) {
    }
    if (D_8004D5B8.unk20 != 0) {
        for (i = 0; i < 30; i++) {
            if (D_8004D5B8.resources[i] != NULL) {
                D_8004D5B8.resources[i]->unk130(D_8004D5B8.resources[i]);
            }
        }
    }
    D_8004D5B8.buffer = D_8004D5B8.buffer == 0;
    D_8004D5B8.unkC += 0x100;
    D_8004D5B8.unk8 = D_8004D5B8.unkC >> 8;
    D_8004D5B8.unk10 = D_8004D5B8.unk14 >> 8;
    D_8004D5B8.unk18 = D_8004D5B8.unk1C >> 8;
    D_8004D5B8.unk1C &= 0xFF;
    D_8004ABD8.unk28[13]();
    D_8004D5B8.unk20 = (s32)D_8004D5B8.bufs[D_8004D5B8.buffer];
    for (i = 0; i < 30; i++) {
        if (D_8004D5B8.resources[i] != NULL) {
            D_8004D5B8.resources[i]->unk134(D_8004D5B8.resources[i]);
        }
    }
}

s32 func_8001D2EC(void) {
    return D_8004D5B8.unk8;
}

s32 func_8001D2FC(void) {
    return D_8004D5B8.unk10;
}

s32 func_8001D30C(void) {
    return D_8004D5B8.unk18;
}

void func_8001D31C(void) {
    s32 i;

    if (D_8005C47C != 0) {
        for (i = 0; i < 30; i++) {
            if (D_8004D5B8.resources[i] != NULL) {
                D_8004D5B8.funcs.unk10[4](D_8004D5B8.resourceIds[i]);
                i--;
            }
        }
        D_8004AD84.bzero(&D_8004D5B8.unk20, 0x18);
    } else {
        D_8004D5B8.buffer = 1;
        D_8004D5B8.unk30 = 0;
        D_8005C47C = 1;
    }
}

void func_8001D3CC(s32 size) {
    D_8004D5B8.unk2C = size;
    D_8004D5B8.bufs[0] = D_8004AD84.unk1C(size, 2);
    D_8004D5B8.bufs[1] = D_8004AD84.unk1C(size, 2);
    D_8004D5B8.unk20 = (s32)D_8004D5B8.bufs[D_8004D5B8.buffer];
}

s32 func_8001D44C(void) {
    return D_8004D5B8.unk20;
}

void func_8001D45C(s32 arg0) {
    D_8004D5B8.unk20 = arg0;
}

void func_8001D468(void) {
    if (D_8004D5B8.bufs[0] != NULL) {
        D_8004AD84.free(D_8004D5B8.bufs[0]);
    }
    if (D_8004D5B8.bufs[1] != NULL) {
        D_8004AD84.free(D_8004D5B8.bufs[1]);
    }
    D_8004D5B8.bufs[0] = NULL;
    D_8004D5B8.bufs[1] = NULL;
}

void func_8001D4D4(s32 w, s32 h, s32 hires, s32 interlace) {
    if (hires != 0) {
        if (interlace != 0) {
            SetDefDispEnv(&D_8004D5B8.disp[0], 0, 0, 320, 480);
            D_8004D5B8.disp[0].isinter = 1;
            D_8004D5B8.disp[0].isrgb24 = 1;
            SetDefDispEnv(&D_8004D5B8.disp[1], 480, 0, 320, 480);
            D_8004D5B8.disp[1].isinter = 1;
            D_8004D5B8.disp[1].isrgb24 = 1;
        } else {
            SetDefDispEnv(&D_8004D5B8.disp[0], 0, 0, w, h);
            SetDefDispEnv(&D_8004D5B8.disp[1], w, 0, w, h);
        }
    } else {
        SetDefDispEnv(&D_8004D5B8.disp[0], 0, 0, w, h);
        SetDefDispEnv(&D_8004D5B8.disp[1], 0, 256, w, h);
    }
    GsInit3D();
    SetGeomOffset(0, 0);
}

void func_8001D5E4(s32 x, s32 y, s32 w, s32 h) {
    SetDefDispEnv(&D_8004D5B8.disp[0], x, y, w, h);
    SetDefDispEnv(&D_8004D5B8.disp[1], x, y, w, h);
}

Resource *func_8001D668(s32 id) {
    s32 i;

    for (i = 0; i < 30; i++) {
        if (D_8004D5B8.resources[i] != NULL && D_8004D5B8.resourceIds[i] == id) {
            return D_8004D5B8.resources[i];
        }
    }
    return NULL;
}

s32 func_8001D6B4(s32 id) {
    s32 i;

    for (i = 0; i < 30; i++) {
        if (id != 0) {
            if (D_8004D5B8.resources[i] != NULL && D_8004D5B8.resourceIds[i] == id) {
                return i;
            }
        } else if (D_8004D5B8.resources[i] == NULL) {
            return i;
        }
    }
    return -1;
}

void func_8001D718(s32 index) {
    for (; index < 29; index++) {
        D_8004D5B8.resources[index] = D_8004D5B8.resources[index + 1];
        D_8004D5B8.resourceIds[index] = D_8004D5B8.resourceIds[index + 1];
    }
}

void func_8001D768(s32 index, Resource *res, s32 id) {
    s32 i;

    for (i = 29; i != index; i--) {
        D_8004D5B8.resources[i] = D_8004D5B8.resources[i - 1];
        D_8004D5B8.resourceIds[i] = D_8004D5B8.resourceIds[i - 1];
    }
    D_8004D5B8.resources[index] = res;
    D_8004D5B8.resourceIds[index] = id;
}

Resource *func_8001D7C4(RECT *rect, s32 arg1, s32 id) {
    DRAWENV env;
    s32 index = func_8001D6B4(0);

    if (index != -1) {
        SetDefDrawEnv(&env, rect->x, rect->y, rect->w, rect->h);
        D_8004D5B8.resourceIds[index] = id;
        return D_8004D5B8.resources[index] = func_8001E1A0(&env, arg1);
    }
    return NULL;
}

s32 func_8001D860(s32 id) {
    s32 index = func_8001D6B4(id);
    Resource *res;

    if (index != -1) {
        res = D_8004D5B8.resources[index];
        res->unk168(res);
        D_8004AD84.free(D_8004D5B8.resources[index]);
        func_8001D718(index);
        return 1;
    }
    return 0;
}

void func_8001D8E8(s32 idA, s32 idB, s32 delta) {
    s32 from = func_8001D6B4(idA);
    s32 to = func_8001D6B4(idB);
    s32 pos;
    Resource *res;
    s32 id;

    if (from != -1 && to != -1) {
        pos = to + delta;
        res = D_8004D5B8.resources[from];
        id = D_8004D5B8.resourceIds[from];
        if (pos <= 0) {
            pos = 0;
        }
        func_8001D718(from);
        func_8001D768(pos, res, id);
    }
}

void func_8001D984(DrawContext *ctx) {
    ClearOTagR(ctx->ot[D_8004D5B8.buffer], ctx->otLen);
}

void func_8001D9C0(DrawContext *ctx) {
    u_long mask = 0xFFFFFF;
    u_long *ot = ctx->ot[D_8004D5B8.buffer];
    u_long *p = ot + ctx->otLen - 1;
    u_long *q;

    while (p != ot) {
        q = p - 1;
        if ((*p & mask) == ((u_long)q & mask)) {
            while ((*q & mask) == ((u_long)(q - 1) & mask)) {
                q--;
            }
            *p = (u_long)q & mask;
        }
        p = q;
    }
}

void func_8001DA4C(DrawContext *ctx) {
    DRAWENV env = ctx->env;
    DR_ENV *dr;
    u_long *ot;
    u_long *tag;

    env.ofs[0] = ctx->unk6C;
    env.ofs[1] = ctx->unk6E;
    func_8001D9C0(ctx);
    dr = (DR_ENV *)D_8004D5B8.unk20;
    ot = ctx->ot[D_8004D5B8.buffer] + ctx->otLen;
    tag = ot - 1;
    if (D_8004D5B8.buffer != 0) {
        env.clip.y += 256;
        env.ofs[1] += 256;
    }
    SetDrawEnv(dr, &env);
    addPrim(ot - 1, dr);
    dr++;
    D_8004D5B8.unk20 = (s32)dr;
    DrawOTag(tag);
}

u_long *func_8001DB8C(DrawContext *ctx, s32 depth) {
    return ctx->ot[D_8004D5B8.buffer] + depth;
}

u_long *func_8001DBB0(DrawContext *ctx, s32 z) {
    s32 i = z >> (16 - ctx->otShift);

    return ctx->ot[D_8004D5B8.buffer] + i;
}

u_long *func_8001DBE0(DrawContext *ctx) {
    return ctx->ot[D_8004D5B8.buffer];
}

s32 func_8001DC00(Sprite *sprite) {
    return sprite->unk68;
}

void func_8001DC0C(Sprite *sprite, u8 r, u8 g, u8 b) {
    sprite->unk19 = r;
    sprite->unk1B = b;
    sprite->unk1A = g;
    if (r | g | b) {
        sprite->unk18 = 1;
    } else {
        sprite->unk18 = 0;
    }
}

void func_8001DC3C(Sprite *sprite, s16 x, s16 y) {
    sprite->unk6C = x;
    sprite->unk6E = y;
}

void func_8001DC48(Sprite *sprite, Vec2 *out) {
    out->x = sprite->unk70 >> 8;
    out->y = sprite->unk74 >> 8;
}

void func_8001DC6C(Sprite *sprite, s32 x, s32 y) {
    sprite->unk70 = x;
    sprite->unk74 = y;
}

void func_8001DC78(Sprite *sprite, s32 dx, s32 dy) {
    sprite->unk70 += dx;
    sprite->unk74 += dy;
}

void func_8001DC94(Sprite *sprite, s16 x, s16 y) {
    sprite->x = x;
    sprite->y = y;
}

void func_8001DCA0(Sprite *sprite, s16 w, s16 h) {
    sprite->w = w;
    sprite->h = h;
}

void func_8001DCAC(Sprite *sprite, Rect16 *rect) {
    rect->x = sprite->x - sprite->unk6C + (sprite->unk70 >> 8);
    rect->y = sprite->y - sprite->unk6E + (sprite->unk74 >> 8);
    rect->w = sprite->w;
    rect->h = sprite->h;
}

void func_8001DCFC(DrawContext *ctx) {
    DrawSync(0);
    D_8004AD84.free(ctx->ot[0]);
    D_8004AD84.free(ctx->ot[1]);
    if (ctx->unk78 != 0) {
        D_8004AD84.free(ctx->unk80);
    }
}

void func_8001DD80(Sprite *sprite) {
    sprite->callbacks->unk0 = 0x7FFFFFFF;
    sprite->callbacks->unk4 = 0;
    sprite->callbacks->func = NULL;
    sprite->callbacks->unkC = 0;
    sprite->callbacks->next = NULL;
    sprite->callbackNum = 1;
}

void func_8001DDCC(Sprite *sprite, s32 count) {
    sprite->callbacks = D_8004AD84.malloc(count * sizeof(Callback), 2);
    sprite->callbackCap = count;
    func_8001DD80(sprite);
}

void func_8001DE24(DrawContext *ctx, s32 arg1, s32 arg2, s32 key, s32 arg4) {
    DrawEntry *cur;
    DrawEntry *prev;
    DrawEntry *e;
    s32 i;
    s32 cap;

    if (ctx->unk7C < ctx->unk78) {
        cur = ctx->unk80;
        e = &cur[ctx->unk7C];
        e->unk8 = arg1;
        e->unkC = arg2;
        e->key = key;
        e->unk4 = arg4;
        prev = NULL;
        if (ctx->unk7C != 0) {
            cap = ctx->unk78;
            for (i = 0; i < cap; i++) {
                if (cur->key < key) {
                    cur = prev;
                    break;
                }
                prev = cur;
                if (cur->next == NULL) {
                    break;
                }
                cur = cur->next;
            }
            if (cur->next == NULL) {
                cur->next = e;
                e->next = NULL;
            } else {
                e->next = cur->next;
                cur->next = e;
            }
        } else {
            e->next = NULL;
        }
        ctx->unk7C++;
    }
}

void func_8001DF08(Sprite *sprite, void (*func)(s32, void *, s32), s32 arg2) {
    Callback *cb;

    if (sprite->callbackNum < sprite->callbackCap) {
        cb = &sprite->callbacks[sprite->callbackNum];
        cb->func = func;
        cb->unkC = arg2;
        cb->unk0 = 0;
        cb->unk4 = 0;
        cb->next = NULL;
        if (sprite->callbackNum != 0) {
            cb[-1].next = cb;
        }
        sprite->callbackNum++;
    }
}

void func_8001DF70(Sprite *sprite) {
    Callback *cb;

    if (sprite->callbackNum) {
        cb = sprite->callbacks;
        do {
            if (cb->func != NULL) {
                cb->func(cb->unkC, sprite, cb->unk4);
            }
            cb = cb->next;
        } while (cb != NULL);
        func_8001DD80(sprite);
    }
}

void func_8001DFE8(DrawContext *ctx, s32 enable, s32 arg2) {
    ctx->unk84 = enable;
    if (enable) {
        ctx->unk88 = arg2;
        ctx->unk8C[D_8004D5B8.buffer] = D_80080AF0;
    }
}

void func_8001E054(DrawContext *ctx) {
    func_80029598(ctx->unk88);
    D_80080AF0 = ctx->unk8C[D_8004D5B8.buffer];
}

void func_8001E0D8(DrawContext *ctx, s32 enable) {
    ctx->unkCC = enable;
    if (enable) {
        ctx->matrices[D_8004D5B8.buffer] = D_80080A90;
    }
}

void func_8001E140(DrawContext *ctx) {
    D_80080A90 = ctx->matrices[D_8004D5B8.buffer];
}

Resource *func_8001E1A0(DRAWENV *env, s32 depth) {
    DrawContext *ctx = D_8004AD84.unk20(0x16C, 2);

    ctx->env = *env;
    ctx->otShift = depth;
    ctx->otLen = D_8004D748[depth - 1];
    ctx->ot[0] = D_8004AD84.malloc(ctx->otLen << 2, 2);
    ctx->ot[1] = D_8004AD84.malloc(ctx->otLen << 2, 2);
    ClearOTagR(ctx->ot[0], ctx->otLen);
    ClearOTagR(ctx->ot[1], ctx->otLen);
    ctx->unk12C = func_8001DC0C;
    ctx->unk130 = (void *)func_8001DA4C;
    ctx->unk134 = (void *)func_8001D984;
    ctx->unk138 = (void *)func_8001DB8C;
    ctx->unk13C = func_8001DBB0;
    ctx->unk168 = (void *)func_8001DCFC;
    ctx->unk110 = func_8001DC94;
    ctx->unk114 = func_8001DCA0;
    ctx->unk118 = func_8001DC3C;
    ctx->unk120 = func_8001DC6C;
    ctx->unk124 = func_8001DC78;
    ctx->unk11C = func_8001DC48;
    ctx->unk128 = func_8001DCAC;
    ctx->unk140 = func_8001DBE0;
    ctx->unk144 = func_8001DC00;
    ctx->unk148 = func_8001DDCC;
    ctx->unk14C = func_8001DE24;
    ctx->unk150 = func_8001DF08;
    ctx->unk154 = (void *)func_8001DF70;
    ctx->unk15C = func_8001DFE8;
    ctx->unk158 = (void *)func_8001E054;
    ctx->unk164 = func_8001E0D8;
    ctx->unk160 = (void *)func_8001E140;
    return ctx;
}

void func_8001E3C4(Obj8001E7DC *obj) {
    D_8005C4A0 = obj;
}

void func_8001E3D0(s32 id) {
    s32 n;
    s32 i;
    if (id > 0) {
        n = id - 1;
        i = n >> 6;
        D_8005C4A0->unk0 = D_80044B58[0](D_8004D760[i]) + (n & 0x3F) * 0x62C;
    } else {
        D_8005C4A0->unk0 = D_80044B58[0](D_8004D760[0]);
    }
}

void func_8001E474(void) {
    Obj8001FBE0 obj;

    func_8001FBE0(&obj);
    obj.methods[2](D_8005C4A0->unk4 + D_8005C4A0->unk14 * 16, D_8005C4A0->unk8 + (D_8005C4A0->unk18 << 5));
    obj.methods[3](D_8005C4A0->unkC, D_8005C4A0->unk10 + D_8005C4A0->unk14 * D_8005C4A0->unk1C + D_8005C4A0->unk18);
    obj.methods[1](D_8005C4A0->unk0 + 0xC);
}

void func_8001E51C(s32 id, s32 arg1) {
    Resource *res = D_8004D708.unk2C(id);

    D_8005C4A0->unk24 = res;
    D_8005C4A0->unk28 = res->unk138(res, arg1);
}

void func_8001E570(s32 arg0, s32 arg1) {
    D_8005C4A0->unk4 = arg0;
    D_8005C4A0->unk8 = arg1;
}

void func_8001E584(s32 arg0, s32 arg1) {
    D_8005C4A0->unkC = arg0;
    D_8005C4A0->unk10 = arg1;
}

void func_8001E598(s32 arg0, s32 arg1) {
    D_8005C4A0->unk14 = arg0;
    D_8005C4A0->unk18 = arg1;
}

void func_8001E5AC(s32 arg0) {
    D_8005C4A0->unk1C = arg0;
}

void func_8001E5B8(s32 arg0) {
    D_8005C4A0->unk20 = arg0;
}

void func_8001E5C4(s32 x, s32 y) {
    SPRT *sprt = D_8004D5B8.funcs.allocPrim();
    SPRT *base = sprt;
    u8 *end;
    u16 tpage;
    u16 clut;

    clut = getClut(D_8005C4A0->unkC, D_8005C4A0->unk10 + D_8005C4A0->unk14 * D_8005C4A0->unk1C + D_8005C4A0->unk18);
    tpage = (1 << 7) | (1 << 5) | ((D_8005C4A0->unk8 & 0x100) >> 4) | (((D_8005C4A0->unk4 + D_8005C4A0->unk14 * 16) & 0x3C0) >> 6) | ((D_8005C4A0->unk8 & 0x200) << 2);
    setSprt(sprt);
    if (D_8005C4A0->unk20 != 0) {
        setSemiTrans(sprt, 1);
    }
    setRGB0(sprt, 0x80, 0x80, 0x80);
    setXY0(sprt, x, y);
    setUV0(sprt, (D_8005C4A0->unk14 & 3) * 32, D_8005C4A0->unk18 * 32);
    setWH(sprt, 32, 32);
    sprt->clut = clut;
    addPrim(D_8005C4A0->unk28, sprt);
    sprt++;
    SetDrawTPage((DR_TPAGE *)sprt, 0, 1, tpage);
    end = (u8 *)base + 0x1C;
    /* addPrim, with the tag written through the start of the block */
    setaddr(base + 1, getaddr(D_8005C4A0->unk28));
    setaddr(D_8005C4A0->unk28, sprt);
    D_8004D5B8.funcs.setPrimEnd(end);
}

s32 func_8001E7B0(void) {
    return D_8004D774[D_8005C4A0->unk0[3]];
}

void func_8001E7DC(Obj8001E7DC *obj) {
    D_8004AD84.bzero(obj, sizeof(Obj8001E7DC));
    obj->methods[0] = func_8001E3D0;
    obj->methods[1] = func_8001E474;
    obj->methods[3] = func_8001E51C;
    obj->methods[4] = func_8001E570;
    obj->methods[5] = func_8001E584;
    obj->methods[6] = func_8001E598;
    obj->methods[7] = func_8001E5AC;
    obj->methods[8] = func_8001E5B8;
    obj->methods[2] = func_8001E5C4;
    obj->methods[9] = func_8001E7B0;
    func_8001E3C4(obj);
    obj->unk1C = 8;
}

void func_8001E894(Obj8001F22C *obj) {
    D_8005C4A8 = obj;
}

void func_8001E8A0(s32 arg0, s32 arg1) {
    D_8005C4A8->unk8 = arg0;
    D_8005C4A8->unkC = arg1;
    D_8005C4A8->unk10 = arg0;
    D_8005C4A8->unk14 = arg1;
}

void func_8001E8BC(s32 arg0, s32 arg1) {
    D_8005C4A8->unk18 = arg0;
    D_8005C4A8->unk1C = arg1 - 0x100;
}

void func_8001E8D0(s32 arg0) {
    D_8005C4A8->unk20 = arg0;
}

void func_8001E8DC(Resource *res, s32 arg1) {
    D_8005C4A8->unk0 = res;
    D_8005C4A8->unk4 = res->unk138(res, arg1);
}

void func_8001E918(s32 arg0, s32 arg1) {
    func_8001E8DC(D_8004D708.unk2C(arg0), arg1);
}

INCLUDE_ASM("asm/main/nonmatchings/gfx", func_8001E950);

void func_8001F1B4(s32 x, s32 y, s32 z) {
    D_8005C4A8->scaleX = x;
    D_8005C4A8->scaleY = y;
    D_8005C4A8->scaleZ = z;
    D_8005C4A8->scaleDirty = 1;
}

void func_8001F1D0(s16 x, s16 y, s16 z) {
    D_8005C4A8->unk48 = x;
    D_8005C4A8->unk4A = y;
    D_8005C4A8->unk4C = z;
    D_8005C4A8->scaleDirty = 1;
}

void func_8001F1EC(s32 arg0, s32 arg1) {
    D_8005C4A8->unk30 = arg0;
    D_8005C4A8->unk34 = arg1;
}

void func_8001F200(s32 arg0) {
    D_8005C4A8->unk24 = arg0;
}

void func_8001F20C(CVECTOR *color) {
    D_8005C4A8->color = *color;
}

void func_8001F22C(Obj8001F22C *obj) {
    D_8004AD84.bzero(obj, sizeof(Obj8001F22C));
    obj->scaleX = 0x1000;
    obj->scaleY = 0x1000;
    obj->scaleZ = 0x1000;
    obj->unk24 = 1;
    obj->color.b = 0x80;
    obj->color.g = 0x80;
    obj->color.r = 0x80;
    obj->methods[1] = func_8001E8A0;
    obj->methods[5] = func_8001E950;
    obj->methods[2] = func_8001E8BC;
    obj->methods[3] = func_8001E918;
    obj->methods[4] = func_8001E8DC;
    obj->methods[0] = func_8001E894;
    obj->methods[6] = func_8001E8D0;
    obj->methods[7] = func_8001F1B4;
    obj->methods[8] = func_8001F1D0;
    obj->methods[9] = func_8001F1EC;
    obj->methods[10] = func_8001F200;
    obj->methods[11] = func_8001F20C;
    func_8001E894(obj);
}

void func_8001F31C(Obj8001F8F8 *obj) {
    D_8005C4B0 = obj;
}

s32 func_8001F328(s32 *table, s32 index) {
    s32 count = table[0];

    if (index < 0 || count < index) {
        return 0;
    }
    return (s32)table + table[index + 1];
}

INCLUDE_ASM("asm/main/nonmatchings/gfx", func_8001F354);

INCLUDE_ASM("asm/main/nonmatchings/gfx", func_8001F658);

void func_8001F8F8(Obj8001F8F8 *obj) {
    D_8004AD84.bzero(obj, sizeof(Obj8001F8F8));
    obj->unk0 = func_8001F328;
    obj->unk4 = func_8001F354;
    obj->unk8 = func_8001F658;
    func_8001F31C(obj);
}

void func_8001F954(Obj8001FBE0 *obj) {
    D_8005C4B8 = obj;
}

void func_8001F960(s32 arg0, s32 arg1) {
    D_8005C4B8->unk8 = arg0;
    D_8005C4B8->unkC = arg1;
}

void func_8001F974(s32 arg0, s32 arg1) {
    D_8005C4B8->unk10 = arg0;
    D_8005C4B8->unk14 = arg1;
}

void func_8001F988(u_long *tim) {
    RECT clut;
    RECT image;
    u_long *p = tim;
    s32 flag;
    s32 mode;
    s32 hasClut;

    p++;
    flag = *p++;
    hasClut = flag & 8;
    mode = flag & 7;
    if (hasClut) {
        switch (mode) {
        case 0:
        case 1:
            clut.x = D_8005C4B8->unk10;
            clut.y = D_8005C4B8->unk14;
            clut.w = ((u16 *)p)[4];
            clut.h = ((u16 *)p)[5];
            LoadImage(&clut, p + 3);
            break;
        }
        p = (u_long *)((u8 *)p + *p);
    }
    image.x = D_8005C4B8->unk8;
    image.y = D_8005C4B8->unkC;
    image.w = ((u16 *)p)[4];
    image.h = ((u16 *)p)[5];
    LoadImage(&image, p + 3);
    D_8005C4B8->w = image.w;
    D_8005C4B8->h = image.h;
}

INCLUDE_ASM("asm/main/nonmatchings/gfx", func_8001FA70);

void func_8001FBD4(s32 arg0) {
    D_8005C4B8->unk18 = arg0;
}

void func_8001FBE0(Obj8001FBE0 *obj) {
    D_8004AD84.bzero(obj, sizeof(Obj8001FBE0));
    obj->methods[1] = func_8001F988;
    obj->methods[3] = func_8001F974;
    obj->methods[2] = func_8001F960;
    obj->methods[0] = func_8001F954;
    obj->methods[4] = func_8001FA70;
    obj->methods[5] = func_8001FBD4;
    func_8001F954(obj);
    obj->unk18 = 0xA800;
}
