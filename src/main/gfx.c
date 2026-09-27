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

INCLUDE_ASM("asm/main/nonmatchings/gfx", func_8001D138);

s32 func_8001D2EC(void) {
    return D_8004D5B8.unk8;
}

s32 func_8001D2FC(void) {
    return D_8004D5B8.unk10;
}

s32 func_8001D30C(void) {
    return D_8004D5B8.unk18;
}

INCLUDE_ASM("asm/main/nonmatchings/gfx", func_8001D31C);

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

INCLUDE_ASM("asm/main/nonmatchings/gfx", func_8001D4D4);

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

INCLUDE_ASM("asm/main/nonmatchings/gfx", func_8001D6B4);

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

INCLUDE_ASM("asm/main/nonmatchings/gfx", func_8001D9C0);

INCLUDE_ASM("asm/main/nonmatchings/gfx", func_8001DA4C);

u_long *func_8001DB8C(DrawContext *ctx, s32 depth) {
    return ctx->ot[D_8004D5B8.buffer] + depth;
}

INCLUDE_ASM("asm/main/nonmatchings/gfx", func_8001DBB0);

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

INCLUDE_ASM("asm/main/nonmatchings/gfx", func_8001DE24);

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

INCLUDE_ASM("asm/main/nonmatchings/gfx", func_8001E1A0);

void func_8001E3C4(Obj8001E7DC *obj) {
    D_8005C4A0 = obj;
}

INCLUDE_ASM("asm/main/nonmatchings/gfx", func_8001E3D0);

INCLUDE_ASM("asm/main/nonmatchings/gfx", func_8001E474);

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

INCLUDE_ASM("asm/main/nonmatchings/gfx", func_8001E5C4);

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

INCLUDE_RODATA("asm/main/nonmatchings/gfx", D_800102BC);

INCLUDE_RODATA("asm/main/nonmatchings/gfx", D_800102CC);

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

INCLUDE_ASM("asm/main/nonmatchings/gfx", func_8001F988);

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
