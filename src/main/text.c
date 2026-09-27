#include "game.h"

void func_80018FEC(Unk80019DFC *obj, TextBuffer *buf, char *text) {
    s16 len;
    s16 cap;
    u16 size;

    if (text != NULL) {
        len = strlen(text);
        buf->len = len;
        if (len == 0) {
            obj->unkC1 = 0;
            return;
        }
        obj->unkC1 = 1;
        buf->dirty = 1;
        if (buf->data != NULL) {
            if (buf->cap <= buf->len) {
                D_8004AD84.free(buf->data);
                buf->data = NULL;
                buf->cap = 0;
            }
            if (buf->data != NULL) {
                goto copy;
            }
        }
        size = buf->len;
        if (size & 3) {
            cap = (size & ~3) + 8;
        } else {
            cap = size + 4;
        }
        buf->cap = cap;
        buf->data = D_8004AD84.malloc(cap, 2);
    copy:
        D_8004AD84.bzero(buf->data, buf->cap);
        memcpy(buf->data, text, buf->len);
    } else {
        func_80018FEC(obj, buf, D_800101D8);
    }
    if (obj->unkAA == 0) {
        func_80019E34(obj, 0);
    }
}

void func_80019140(Unk80019DFC *obj, char *text) {
    func_80018FEC(obj, &obj->text[0], text);
}

void func_80019164(Unk80019DFC *obj, char *text, s32 id) {
    func_80019360(obj, text, id, 0);
}

void func_80019184(u8 *buf, s32 value) {
    s32 saved;
    s32 len;
    s32 div;
    s32 d;

    saved = value;
    if (value <= 0) {
        *buf = '0';
        return;
    }
    len = 0;
    div = 10;
    do {
        value -= value % div;
        len++;
        div *= 10;
    } while (value != 0);
    value = saved;
    while (value != 0) {
        d = value % 10;
        value -= d;
        value /= 10;
        buf[--len] = d + '0';
    }
}

void func_8001922C(Unk80019DFC *obj, u32 index, s32 value) {
    u8 buf[16];
    u8 *p;
    s32 i;

    if (index >= 6) {
        func_80019140(obj, D_800101FC);
        return;
    }
    for (i = 15, p = &buf[i]; i >= 0; i--) {
        *p-- = 0;
    }
    func_80019184(buf, value);
    for (i = 0; buf[i] != 0; i++) {
        buf[i] -= 0x2C;
    }
    func_80018FEC(obj, &obj->text[index], buf);
    obj->text[index].dirty = 0;
}

void func_80019308(Unk80019DFC *obj, char *text, s32 index) {
    if (index < 1 || index > 5) {
        func_80019140(obj, D_80010230);
    } else {
        func_80018FEC(obj, &obj->text[index], text);
    }
}

void func_80019360(Unk80019DFC *obj, char *text, s32 id, s32 index) {
    Obj8001F8F8 cls;
    char *str;

    if (id >= 0) {
        func_8001F8F8(&cls);
        str = cls.unk0(text, id);
        if (str == NULL) {
            return;
        }
        func_80018FEC(obj, &obj->text[index], str);
    } else {
        func_80018FEC(obj, &obj->text[index], text);
    }
    obj->text[index].dirty = 0;
}

INCLUDE_RODATA("asm/main/nonmatchings/text", D_800101D8);

INCLUDE_RODATA("asm/main/nonmatchings/text", D_800101FC);

INCLUDE_RODATA("asm/main/nonmatchings/text", D_80010230);

INCLUDE_RODATA("asm/main/nonmatchings/text", D_80010268);

void func_80019420(Unk80019DFC *obj) {
    TextWait wait;
    SVECTOR out;
    SVECTOR in[4];
    TextBuffer *text;
    u16 clut;
    u16 prevTpage;
    s32 rotated;
    s16 c;
    s16 x;
    s16 y;
    u16 tpage;
    u8 u;
    u8 v;
    s32 i;
    s32 j;

    prevTpage = 0;
    tpage = 0;
    rotated = 0;
    if (obj->text[0].data == NULL) {
        obj->unkC1 = 0;
        return;
    }
    for (i = 5; i >= 0; i--) {
        obj->text[i].pos = 0;
    }
    obj->unkC3 = 0;
    obj->unkB8 = -obj->unkBC;
    wait.unk18 = 0;
    text = obj->text;
    obj->unkBA = 0;
    if (obj->unkCC != 0) {
        if (obj->unkD0 == 0 && obj->unkD4 == 0) {
            return;
        }
        if (obj->unkD0 == 0x1000 && obj->unkD4 == obj->unkD0) {
            obj->unkCC = 0;
        } else {
            rotated = 1;
            RotMatrixYXZ_gte(&obj->rot, &obj->mat);
            ScaleMatrix(&obj->mat, (VECTOR *)&obj->unkD0);
        }
    }
    i = 0;
    wait.res = D_8004D5B8.funcs.unk2C(obj->unk54);
    wait.ot = (u_long *)wait.res->unk138(wait.res, obj->unk58);
    wait.prim = D_8004D5B8.funcs.allocPrim();
    text->pos = obj->unkA6;
    while (i < (s16)obj->unkA4 - obj->unkA6) {
        if (obj->unkC3 != 0) {
            break;
        }
        c = D_8004D5A8.decode(text->data + text->pos, (u8)text->dirty, obj->unk50);
        wait.unk14 = c;
        wait.unk16 = (u32)(c << 16) >> 24;
        switch (func_8001A108(obj, text, &wait, &text->pos)) {
        case 1:
            i++;
            goto draw;
        case 4:
            i++;
            continue;
        case 2:
        draw:
            if (wait.glyph->page == 0xFF) {
                wait.glyph = *(Glyph **)(obj->unk50 + 4);
            }
            x = obj->unkB8 + (obj->unkB0 + wait.glyph->dx);
            y = obj->unkBA + (obj->unkB2 + wait.glyph->dy);
            clut = getClut(obj->unkAC + wait.glyph->clutX, obj->unkC0 + (obj->unkAE + wait.glyph->clutY));
            u = wait.glyph->u;
            v = wait.glyph->v;
            if ((s8)obj->unkBE == -1) {
                tpage = getTPage(0, 1, obj->unkAC + (wait.glyph->page << 6), obj->unkAE);
            } else {
                tpage = getTPage(0, obj->unkBE & 3, obj->unkAC + (wait.glyph->page << 6), obj->unkAE);
            }
            if (!rotated) {
                if (i == 0) {
                    prevTpage = tpage;
                }
                if (tpage != prevTpage) {
                    SetDrawTPage(wait.prim, 0, 1, prevTpage);
                    addPrim(wait.ot, wait.prim);
                    prevTpage = tpage;
                    wait.prim = (DR_TPAGE *)wait.prim + 1;
                }
                setlen((SPRT *)wait.prim, 4);
                setcode((SPRT *)wait.prim, 0x64);
                if ((s8)obj->unkBE != -1) {
                    setSemiTrans((SPRT *)wait.prim, 1);
                }
                ((SPRT *)wait.prim)->r0 = ((SPRT *)wait.prim)->g0 = ((SPRT *)wait.prim)->b0 = 0x80;
                ((SPRT *)wait.prim)->x0 = x;
                ((SPRT *)wait.prim)->y0 = y;
                ((SPRT *)wait.prim)->u0 = u;
                ((SPRT *)wait.prim)->v0 = v;
                ((SPRT *)wait.prim)->w = wait.glyph->w;
                ((SPRT *)wait.prim)->h = wait.glyph->h;
                ((SPRT *)wait.prim)->clut = clut;
                addPrim(wait.ot, wait.prim);
                wait.prim = (SPRT *)wait.prim + 1;
                SetDrawTPage(wait.prim, 0, 1, tpage);
                addPrim(wait.ot, wait.prim);
                wait.prim = (DR_TPAGE *)wait.prim + 1;
            } else {
                setlen((POLY_FT4 *)wait.prim, 9);
                setcode((POLY_FT4 *)wait.prim, 0x2C);
                ((POLY_FT4 *)wait.prim)->r0 = ((POLY_FT4 *)wait.prim)->g0 = ((POLY_FT4 *)wait.prim)->b0 = 0x80;
                in[0].vx = in[2].vx = x - obj->unkE0;
                in[1].vx = in[3].vx = in[0].vx + wait.glyph->w;
                in[0].vy = in[1].vy = y - obj->unkE4;
                in[2].vy = in[3].vy = in[0].vy + wait.glyph->h;
                in[0].vz = in[1].vz = in[2].vz = in[3].vz = 0;
                for (j = 0; j < 4; j++) {
                    ApplyMatrixSV(&obj->mat, &in[j], &out);
                    (&((POLY_FT4 *)wait.prim)->x0)[j * 4] = out.vx + obj->unkE0;
                    (&((POLY_FT4 *)wait.prim)->y0)[j * 4] = out.vy + obj->unkE4;
                }
                ((POLY_FT4 *)wait.prim)->u0 = ((POLY_FT4 *)wait.prim)->u2 = u;
                ((POLY_FT4 *)wait.prim)->u1 = ((POLY_FT4 *)wait.prim)->u3 = ((POLY_FT4 *)wait.prim)->u0 + wait.glyph->w - 1;
                ((POLY_FT4 *)wait.prim)->v0 = ((POLY_FT4 *)wait.prim)->v1 = v;
                ((POLY_FT4 *)wait.prim)->v2 = ((POLY_FT4 *)wait.prim)->v3 = ((POLY_FT4 *)wait.prim)->v0 + wait.glyph->h - 1;
                if ((s8)obj->unkBE != -1) {
                    setSemiTrans((POLY_FT4 *)wait.prim, 1);
                }
                ((POLY_FT4 *)wait.prim)->tpage = tpage;
                ((POLY_FT4 *)wait.prim)->clut = clut;
                addPrim(wait.ot, wait.prim);
                wait.prim = (POLY_FT4 *)wait.prim + 1;
            }
            if (obj->unkC2 != 0) {
                obj->unkB8 += obj->unkB4;
            } else {
                obj->unkB8 += wait.glyph->advance + wait.glyph->dx;
            }
            break;
        case 3:
            break;
        case 0:
        default:
            goto end;
        }
    }
    if (!rotated) {
        SetDrawTPage(wait.prim, 0, 1, tpage);
        addPrim(wait.ot, wait.prim);
        wait.prim = (DR_TPAGE *)wait.prim + 1;
    }
end:
    D_8004D708.setPrimEnd(wait.prim);
}

void func_80019C2C(Unk80019DFC *obj) {
    s32 extra;
    s32 pos;
    s32 lines;
    s32 going;
    u8 *p;
    u8 index;
    s32 c;

    if (obj->unkC == 1) {
        pos = obj->unkA6;
        extra = 0;
        lines = 0;
        going = 1;
        do {
            switch ((s32)((u32)(D_8004D5A8.decode(obj->text[0].data + pos, (u8)obj->text[0].dirty, obj->unk50) << 16) >> 24)) {
            case 0:
            default:
                if (obj->text[0].dirty != 0) {
                    pos += 2;
                } else {
                    pos += 1;
                }
                break;
            case 1:
                pos += 2;
                break;
            case 2:
                p = (u8 *)(pos + (s32)obj->text[0].data);
                c = p[1];
                switch (c) {
                default:
                    pos += D_8004D5A8.codeLengths[c];
                    break;
                case 1:
                    if (++lines < obj->unkBF) {
                        pos += D_8004D5A8.codeLengths[1];
                    } else {
                        going = 0;
                    }
                    break;
                case 2:
                    if (p[2] < 5) {
                        going = 0;
                    }
                    pos += D_8004D5A8.codeLengths[2];
                    break;
                case 5:
                    index = p[2];
                    if (index < 6) {
                        extra += obj->text[index].len;
                        pos += D_8004D5A8.codeLengths[5];
                    } else {
                        going = 0;
                    }
                    break;
                case 3:
                    going = 0;
                    break;
                }
                break;
            case 4:
                going = 0;
                break;
            }
        } while (going != 0);
        obj->unkA4 = pos + extra;
    }
}

void func_80019DFC(Unk80019DFC *arg0, s32 arg1) {
    u8 *entry;

    if (arg1 < 1 || arg1 > 3) {
        arg1 = 1;
    }
    entry = D_8004D5A8.styles + arg1 * 0x18;
    arg0->unk50 = entry;
    arg0->unkBE = *entry;
}

void func_80019E34(Unk80019DFC *obj, s32 arg1) {
    if (arg1 <= 0) {
        obj->unkA8 = 0;
        obj->unkAA = 0;
        obj->unkA4 = obj->text[0].len;
        return;
    }
    obj->unkA4 = 0;
    obj->unkA8 = 0;
    obj->unkAA = arg1;
    obj->unkA6 = 0;
}

void func_80019E64(Unk80019DFC *arg0, s16 arg1, s16 arg2) {
    arg0->unkB0 = arg1;
    arg0->unkB2 = arg2;
}

void func_80019E70(Unk80019DFC *arg0, u8 arg1) {
    arg0->unkC0 = arg1;
}

void func_80019E78(Unk80019DFC *arg0, u8 arg1) {
    arg0->unkBE = arg1;
}

void func_80019E80(Unk80019DFC *arg0, s16 arg1, s16 arg2) {
    if (arg1 != 0 || arg2 != 0) {
        arg0->unkC2 = 1;
        arg0->unkB4 = arg1;
        arg0->unkB6 = arg2;
    } else {
        arg0->unkC2 = 0;
        arg0->unkB4 = 0;
        arg0->unkB6 = 0;
    }
}

void func_80019EB8(Unk80019DFC *arg0, u8 arg1) {
    if (arg0->text[0].len == 0) {
        arg0->unkC1 = 0;
    } else {
        arg0->unkC1 = arg1;
    }
}

void func_80019ED8(Unk80019DFC *obj, u8 type) {
    Obj8001F8F8 cls;

    if (type != 0) {
        func_8001F8F8(&cls);
        obj->unkBC = cls.unk4(&obj->text[0], obj->unk50, obj->unkB4);
    } else {
        obj->unkBC = 0;
    }
}

void func_80019F28(Unk80019DFC *obj) {
    TextBuffer *text = &obj->text[0];
    s32 pos;
    u8 c;
    u8 index;

    if (obj->text[0].data != NULL) {
        for (pos = 0; pos < obj->text[0].len;) {
            switch ((s32)((u32)(D_8004D5A8.decode(text->data + pos, (u8)text->dirty, obj->unk50) << 16) >> 24)) {
            case 0:
            case 3:
            default:
                if (text->dirty != 0) {
                    pos += 2;
                } else {
                    pos += 1;
                }
                break;
            case 1:
                pos += 2;
                break;
            case 2:
                c = text->data[pos + 1];
                if (c == 4) {
                    break;
                }
                if (c == 8) {
                    index = text->data[pos + 2];
                    func_80019308(obj, D_8004853C, index);
                    obj->text[index].dirty = 0;
                    pos += D_8004D5A8.codeLengths[8];
                } else {
                    pos += D_8004D5A8.codeLengths[c];
                }
                break;
            case 4:
                return;
            }
        }
    }
}

void func_8001A094(Unk80019DFC *arg0, s32 arg1) {
    arg0->unkC8 = arg1;
}

void func_8001A09C(Unk80019DFC *arg0, s32 arg1, s32 arg2) {
    arg0->unkD8 = 0x1000;
    arg0->unkD0 = arg1;
    arg0->unkD4 = arg2;
    arg0->unkCC = 1;
}

void func_8001A0B8(Unk80019DFC *arg0, s32 arg1, s32 arg2) {
    arg0->unkE0 = arg1;
    arg0->unkE4 = arg2;
}

void func_8001A0C4(Unk80019DFC *arg0, s32 arg1) {
    arg0->unk58 = arg1;
}

void func_8001A0CC(Unk80019DFC *arg0, u8 arg1) {
    arg0->unkBF = arg1;
}

void func_8001A0D4(Unk80019DFC *arg0, u8 arg1) {
    arg0->unkC4 = arg1;
}

u8 func_8001A0DC(Unk80019DFC *arg0) {
    return arg0->unkC3;
}

u8 func_8001A0E8(Unk80019DFC *arg0) {
    return arg0->unkC1;
}

s32 func_8001A0F4(Unk80019DFC *arg0) {
    return arg0->unk10 == 1;
}

INCLUDE_ASM("asm/main/nonmatchings/text", func_8001A108);

s32 func_8001A364(Unk80019DFC *obj, TextBuffer *buf) {
    switch (buf->data[buf->pos + 1]) {
    case 0:
    default:
        func_80019C2C(obj);
        break;
    case 7:
        obj->unkA6 = buf->pos + 2;
        break;
    }
    return 0;
}

s32 func_8001A3B8(Unk80019DFC *obj, TextBuffer *buf, TextWait *wait) {
    if (++wait->unk18 == 1) {
        wait->unk10 = buf->pos + 2;
    } else if (wait->unk18 >= obj->unkBF) {
        obj->unkA6 = wait->unk10;
        if (obj->unkBF >= 2) {
            obj->unkBF--;
            func_80019C2C(obj);
            obj->unkBF++;
        }
        return 0x8000;
    }
    obj->unkB8 = 0;
    if (obj->unkC2 != 0) {
        obj->unkBA += obj->unkB6;
    } else {
        obj->unkBA += (s8)obj->unk50[1];
    }
    return 0x8004;
}

s32 func_8001A4A8(Unk80019DFC *obj, TextBuffer *buf) {
    if (buf->data[buf->pos + 2] < 5) {
        obj->unkC = 2;
        obj->unk10 = 1;
        if (buf->data[buf->pos + 2] < 1 || buf->data[buf->pos + 2] > 4) {
            obj->unk14 = 0;
        } else {
            obj->unk14 = buf->data[buf->pos + 2];
        }
        obj->unk18 = buf->pos + 2;
        return 0;
    }
    return 0x8003;
}

s32 func_8001A530(Unk80019DFC *obj, TextBuffer *buf) {
    u8 c;

    if (obj->unkAA != 0) {
        obj->unkA4 = buf->pos + 2;
    } else {
        obj->unkA4 = buf->len;
    }
    while (buf->pos < buf->len) {
        switch ((s32)((u32)(D_8004D5A8.decode(buf->data + buf->pos, (u8)buf->dirty, obj->unk50) << 16) >> 24)) {
        case 0:
        case 1:
        default:
            obj->unkA6 = buf->pos;
            buf->pos = buf->len + 1;
            break;
        case 2:
            c = buf->data[buf->pos + 1];
            if (c == 5 || c == 8) {
                obj->unkA6 = buf->pos;
                buf->pos = buf->len + 1;
            } else {
                buf->pos += D_8004D5A8.codeLengths[c];
            }
            break;
        case 4:
            obj->unkA6 = buf->pos - 1;
            return 3;
        }
    }
    return 0;
}

s32 func_8001A684(void) {
    return 0x8003;
}

s32 func_8001A68C(Unk80019DFC *obj, TextBuffer *buf, TextWait *wait) {
    u8 index = buf->data[buf->pos + 2];
    s16 c;
    s32 ret;

    if (obj->text[index].data == NULL) {
        func_80019308(obj, D_80010268, index);
        return 0x8003;
    }
    if (obj->text[index].pos >= obj->text[index].len) {
        return 0x8003;
    }
    c = D_8004D5B4(obj->text[index].data + obj->text[index].pos, (u8)obj->text[index].dirty, obj->unk50, obj->text[index].pos);
    wait->unk14 = c;
    wait->unk16 = (u32)(c << 16) >> 24;
    if (wait->unk16 == 2) {
        return 0x8000;
    }
    if (obj->unkAA != 0) {
        return func_8001A108(obj, &obj->text[index], wait, &obj->text[index].pos);
    }
    ret = func_8001A108(obj, &obj->text[index], wait, &obj->text[index].pos);
    if (ret == 1) {
        return 2;
    }
    return ret;
}

s32 func_8001A7AC(Unk80019DFC *obj, TextBuffer *buf) {
    if (buf->data[buf->pos + 2] < 0xFF) {
        obj->unkC = 2;
        obj->unk10 = 0;
        obj->unk14 = buf->data[buf->pos + 2];
        buf->data[buf->pos + 2] = 0xFF;
        obj->unkA8 = 0;
        return 0x8000;
    }
    return 0x8003;
}

s32 func_8001A820(s32 arg0, TextBuffer *buf) {
    if ((u8)buf->data[buf->pos + 2] < 6) {
        func_80019360(arg0, D_8004853C, -1, (u8)buf->data[buf->pos + 2]);
        buf->data[buf->pos + 2] = 6;
    }
    return 0x8003;
}

void func_8001A890(Unk80019DFC *obj) {
    s32 i;

    switch (obj->unkC) {
    case 0:
    default:
        obj->unk38(obj);
        break;
    case 1:
        if (obj->unkC1 != 0) {
            if (obj->unkAA > 0 && obj->unkC3 == 0) {
                if (++obj->unkA8 > obj->unkAA) {
                    obj->unkA8 = 0;
                    obj->unkA4++;
                    if (obj->unkC8 != 0) {
                        D_800553DC.playSound(obj->unkC8);
                    }
                }
            }
            func_80019420(obj);
        }
        break;
    case 2:
        switch (obj->unk10) {
        case 0:
        default:
            func_80019420(obj);
            if (++obj->unkA8 > obj->unk14) {
                obj->unkA8 = 0;
                obj->unk28(obj, 1);
            }
            break;
        case 1:
            if ((D_8004AF78.getButtons(0) >> D_8004AF78.getButtonBit(0, D_8004D474[obj->unk14])) & 1) {
                obj->text[0].data[obj->unk18] = 5;
                obj->unkA8 = obj->unkAA;
                obj->unk28(obj, 1);
            }
            func_80019420(obj);
            break;
        }
        break;
    case 3:
        for (i = 0; i < 6; i++) {
            if (obj->text[i].data != NULL) {
                D_8004AD84.free(obj->text[i].data);
            }
        }
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/text", func_8001AAB4);

void func_8001ACC8(Task8001ACC8 *task, s32 arg1) {
    task->unk64 = arg1;
    if (arg1 == 0) {
        task->unk10 = 0;
        task->unk70 = 0;
    }
    task->dirty = 1;
}

void func_8001ACE4(Task8001ACC8 *task, s32 arg1, s32 arg2) {
    task->unk58 = arg1;
    task->unk5C = arg2;
    task->dirty = 1;
}

void func_8001ACF8(Task8001ACC8 *task, s32 arg1) {
    task->unk60 = arg1;
    task->dirty = 1;
}

void func_8001AD08(Task8001ACC8 *task, s32 arg1) {
    task->unk74 = arg1;
}

void func_8001AD10(Task8001ACC8 *task, s32 arg1) {
    task->unk78 = arg1;
}

void func_8001AD18(Task8001ACC8 *task, s32 arg1) {
    task->unk7C = arg1;
}

void func_8001AD20(Task8001ACC8 *task, Unk80019DFC **win) {
    switch (task->state) {
    case 0:
    default:
        if (*win == NULL) {
            *win = func_8001AAB4(task->unk50, 1, task->unk58, task->unk5C);
        }
        (*win)->m110(*win, D_8004D488[task->unk6C]);
        (*win)->m144(*win, task->unk64);
        (*win)->m15C(*win, task->unk54);
        task->unk70 = D_8004D708.unk38();
        task->unk38(task);
        break;
    case 1:
        if (task->dirty != 0) {
            (*win)->m144(*win, task->unk64);
            (*win)->setPos(*win, task->unk58, task->unk5C);
            (*win)->m138(*win, task->unk60);
            task->dirty = 0;
        }
        if (task->unk64 != 0) {
            if (task->unk7C != 0) {
                if (task->unk6C != 0) {
                    task->unk6C = 0;
                    (*win)->m110(*win, D_8004D488[0]);
                }
            } else if (task->unk10 == 0) {
                if ((D_8004D5B8.funcs.unk38() - task->unk70) / task->unk74 != 0) {
                    task->unk70 = D_8004D5B8.funcs.unk38();
                    task->unk6C = 1;
                    (*win)->m110(*win, D_8004D488[1]);
                    task->unk10 = 1;
                }
            } else if ((D_8004D5B8.funcs.unk38() - task->unk70) / task->unk78 != 0) {
                task->unk70 = D_8004D5B8.funcs.unk38();
                if (++task->unk6C >= 5) {
                    task->unk6C = 0;
                    task->unk10 = 0;
                }
                (*win)->m110(*win, D_8004D488[task->unk6C]);
            }
        }
        break;
    case 2:
    case 3:
        break;
    }
}

Task8001ACC8 *func_8001AFE0(s16 arg0, s32 arg1, s16 arg2, s16 arg3) {
    Task8001ACC8 *task = func_800144DC(func_8001AD20, 0x98, 4);

    task->unk50 = arg0;
    task->unk54 = arg1;
    task->unk58 = arg2;
    task->unk5C = arg3;
    task->unk64 = 1;
    task->unk74 = 0x20;
    task->unk78 = 6;
    task->methods[0] = func_8001ACC8;
    task->methods[1] = func_8001ACE4;
    task->methods[3] = func_8001AD08;
    task->methods[4] = func_8001AD10;
    task->methods[2] = func_8001ACF8;
    task->methods[5] = func_8001AD18;
    return task;
}

void func_8001B0C0(Task8001B3A0 *task) {
    if (task->unk64 != NULL) {
        D_8004AD84.free(task->unk64);
    }
    task->unk64 = NULL;
    task->unk60 = 0;
}

void func_8001B108(Task8001B3A0 *task, s32 *data) {
    task->data = data;
    if (data[0] == 0x4E454C52) {
        task->compressed = 1;
        task->size = data[1];
    } else {
        task->compressed = 0;
        task->size = 0;
    }
    data += 2;
    task->unk54 = data;
    task->unk68 = data;
}

void func_8001B148(Task8001B3A0 *task) {
    if (task->size > task->unk60) {
        if (task->unk64 != NULL) {
            D_8004AD84.free(task->unk64);
        }
        task->unk64 = D_8004AD84.malloc(task->size, 2);
        task->unk60 = task->size;
    }
    task->unk6C = task->unk64;
}

void func_8001B1D0(Task8001B3A0 *task) {
    u8 *src = (u8 *)task->unk68;
    u8 *dst = task->unk6C;
    s32 total = 0;
    s32 done = 0;
    s32 n;
    s32 i;

    while (*src != 0) {
        if (*src & 0x80) {
            n = *src++ & 0x7F;
            for (i = 0; i < n; i++) {
                *dst++ = *src;
            }
            src++;
            total += n;
        } else {
            n = *src++;
            for (i = 0; i < n; i++) {
                *dst++ = *src++;
            }
            total += n;
        }
        if (total >= task->unk70) {
            done = 1;
            task->unk68 = (s32 *)src;
            task->unk6C = dst;
            break;
        }
    }
    if (!done) {
        task->unk2C(task, 0);
    }
}

void *func_8001B2B8(Task8001B3A0 *task, s32 *data) {
    task->unk70 = 0x10000000;
    func_8001B108(task, data);
    if (task->compressed) {
        func_8001B148(task);
        func_8001B1D0(task);
        return task->unk64;
    }
    return data;
}

void func_8001B314(Task8001B3A0 *task, s32 *data, s32 arg2) {
    task->unk70 = arg2;
    func_8001B108(task, data);
    if (task->compressed) {
        func_8001B148(task);
        task->unk2C(task, 1);
    }
}

void *func_8001B368(Task8001B3A0 *task) {
    if (task->unk10 != 0) {
        return NULL;
    }
    if (task->compressed != 0) {
        return task->unk64;
    }
    return task->data;
}

void func_8001B3A0(Task8001B3A0 *task) {
    switch (task->state) {
    case 0:
    default:
        task->unk38(task);
        break;
    case 1:
        if (task->unk10 != 0 && task->unk10 == task->state) {
            func_8001B1D0(task);
        }
        break;
    case 2:
        break;
    case 3:
        if (task->unk64 != NULL) {
            D_8004AD84.free(task->unk64);
        }
        break;
    }
}

void func_8001B434(void) {
    Task8001B3A0 *task = func_800144DC(func_8001B3A0, 0x84, 0);

    task->unk74 = func_8001B2B8;
    task->unk80 = func_8001B0C0;
    task->unk7C = func_8001B314;
    task->unk78 = func_8001B368;
}

void func_8001B490(Task8001B6A8 *task) {
    Obj8001F22C obj;
    s32 i;
    s32 x;
    Unk80044744 *g;

    i = 0;
    g = &D_80044744;
    x = 0;
    for (; i < 2; i++) {
        func_8001F22C(&obj);
        obj.methods[3](task->unk50, 0);
        obj.methods[1](0x140, 0);
        if (task->unk10 == 0) {
            obj.methods[7](task->unk68, 0x1000, 0x1000);
            obj.methods[9](0x140 - x, 0xC4);
        } else if (task->unk10 == 2) {
            obj.methods[6](task->unk58);
        }
        obj.methods[5](g->unk424(0x02770000), i + 8, 0, 0xA6);
        x += 0x140;
    }
}

void func_8001B5AC(Task8001B6A8 *task) {
    Obj8001F22C obj;

    func_8001F22C(&obj);
    obj.methods[3](task->unk50, 0);
    obj.methods[1](0x140, 0);
    if (D_8004D5B8.funcs.unk38() - task->unk60 >= 4) {
        task->unk60 = D_8004D5B8.funcs.unk38();
        if (++task->unk64 >= 5) {
            task->unk64 = 0;
        }
    }
    obj.methods[6](task->unk64);
    obj.methods[5](D_80044B68[0](0x02770000), 10, 0x124, 0xCD);
}

void func_8001B6A8(Task8001B6A8 *task) {
    switch (task->state) {
    case 0:
    default:
        task->unk38(task);
        task->unk6A = 0x199;
        break;
    case 1:
        switch (task->unk10) {
        case 0:
        default:
            task->unk68 += task->unk6A;
            if (task->unk68 > 0x1000) {
                task->unk68 = 0x1000;
                task->unk3C(task);
            }
            break;
        case 1:
            if (task->unk5C != 0) {
                func_8001B5AC(task);
            }
            break;
        case 2:
            if (D_8004D5B8.funcs.unk38() - task->unk54 >= 3) {
                task->unk54 = D_8004D5B8.funcs.unk38();
                if (++task->unk58 >= 5) {
                    task->unk28(task, 3);
                    return;
                }
            }
            break;
        }
        func_8001B490(task);
        break;
    case 2:
    case 3:
        break;
    }
}

Task *func_8001B804(s32 arg0) {
    Task *task = func_800144DC(func_8001B6A8, 0x6C, 0);

    task->unk50 = arg0;
    D_800553DC.playSound(0x40019);
    return task;
}

void func_8001B864(Task8001B6A8 *task, Unk8001BA7C *data) {
    switch (task->state) {
    case 0:
    default:
        task->unk38(task);
        break;
    case 1:
        switch (task->unk10) {
        case 0:
        default:
            if (data->window->m16C(data->window) == 0 && data->unk4->unk10 == 1) {
                data->window->m144(data->window, 1);
                task->unk10++;
            }
            break;
        case 1:
            if (data->window->m168(data->window) != 0) {
                data->unk4->unk10 = 2;
                data->window->m144(data->window, 0);
                task->unk10++;
                D_800553DC.playSound(0x4001A);
                break;
            }
            if ((D_8004AF78.getButtons(0) >> D_8004AF78.getButtonBit(0, 13)) & 1) {
                data->window->m128(data->window);
            }
            if (data->window->m170(data->window) != 0) {
                data->unk4->unk5C = 1;
            } else {
                data->unk4->unk5C = 0;
            }
            break;
        case 2:
            if (data->unk4 == NULL) {
                task->unk28(task, 3);
            }
            break;
        }
        break;
    case 2:
    case 3:
        break;
    }
}

Task *func_8001BA7C(s32 id, s32 arg1, s32 arg2) {
    Task *task = func_800144DC(func_8001B864, 0x50, 8);
    Unk8001BA7C *data = task->unk24;

    data->window = func_8001AAB4(id, 1, 0x12, 0xB0);
    data->window->m160(data->window, 3);
    data->window->m114(data->window, arg1, arg2);
    data->window->m144(data->window, 0);
    data->window->m130(data->window, 6);
    data->unk4 = func_8001B804(id);
    return task;
}

INCLUDE_ASM("asm/main/nonmatchings/text", func_8001BB68);

void func_8001BCCC(Task8001BB68 *task) {
    Obj8001F22C obj;
    SVECTOR v[4];
    Unk8001BB68 *parent = task->parent;
    u32 type = parent->type;
    s32 pad;
    s32 i;
    s32 x;
    Unk80044744 *g;
    u_long *ot;
    Resource *res;
    POLY_FT4 *p;
    DVECTOR *pos;

    pad = 0;
    if (type < 2) {
        pad = parent->w;
    }
    pos = &D_8004D49C[type].unk4;
    func_8001F22C(&obj);
    obj.methods[3](task->parent->unk54, 0);
    obj.methods[1](0x140, 0);
    g = &D_80044744;
    for (i = 0; i < 4; pos++, i++) {
        switch (i) {
        case 0:
            obj.methods[5](g->unk424(0x02770000), D_8004D49C[type].unk0, task->parent->x + pos->vx,
                           task->parent->y + pos->vy);
            break;
        case 1:
            obj.methods[5](g->unk424(0x02770000), 0, task->parent->x + pos->vx - pad, task->parent->y + pos->vy);
            break;
        case 3:
            if (type < 2) {
                obj.methods[5](g->unk424(0x02770000), 2, task->parent->x + pos->vx, task->parent->y + pos->vy);
            } else {
                x = task->parent->w - 14;
                obj.methods[5](g->unk424(0x02770000), 2, task->parent->x + x, task->parent->y + pos->vy);
            }
            break;
        }
    }
    res = D_8004D5B8.funcs.unk2C(task->parent->unk54);
    ot = (u_long *)res->unk138(res, 0);
    pos = &D_8004D49C[type].unkC;
    v[0].vx = v[2].vx = task->parent->x + pos->vx - pad;
    v[1].vx = v[3].vx = v[0].vx + task->parent->w;
    v[0].vy = v[1].vy = task->parent->y + pos->vy;
    v[2].vy = v[3].vy = v[0].vy + task->parent->h;
    v[0].vz = v[1].vz = v[2].vz = v[3].vz = 0;
    p = D_8004D5B8.funcs.allocPrim();
    setPolyFT4(p);
    setRGB0(p, 0x80, 0x80, 0x80);
    p->tpage = 0x45;
    p->clut = 0x2E57;
    setSemiTrans(p, 1);
    p->x0 = v[0].vx;
    p->y0 = v[0].vy;
    p->x1 = v[1].vx;
    p->y1 = v[1].vy;
    p->x2 = v[2].vx;
    p->y2 = v[2].vy;
    p->x3 = v[3].vx;
    p->y3 = v[3].vy;
    setUV4(p, 0xBC, 0, 0xC7, 0, 0xBC, 0x3E, 0xC7, 0x3E);
    addPrim(ot, p);
    D_8004D5B8.funcs.setPrimEnd(p + 1);
}

void func_8001C0C4(Task *task) {
    switch (task->state) {
    case 0:
    default:
        task->unk28(task, 2);
        break;
    case 1:
        func_8001BB68(task);
        func_8001BCCC((Task8001BB68 *)task);
        break;
    case 2:
    case 3:
        break;
    }
}

Task8001BB68 *func_8001C130(Unk8001BB68 *parent) {
    Task8001BB68 *task = func_800144DC(func_8001C0C4, 0x60, 0);

    task->parent = parent;
    return task;
}

typedef struct Order4 {
    s32 next[4];
} Order4;

extern Order4 D_800102BC;

void func_8001C168(Task8001C454 *task) {
    Resource *res = D_8004D708.unk2C(task->unk64);
    u_long *ot = (u_long *)res->unk138(res, 0);
    SVECTOR out[4];
    SVECTOR in[4];
    LINE_F2 *line;
    Order4 order;
    s32 i;

    if (task->unkB8 == 0) {
        task->unk60 += task->unk5C;
        if (task->unk60 > 0x1000) {
            task->unk60 = 0x1000;
            task->unkBC = 1;
            task->unk28(task, 3);
        }
    } else {
        task->unk60 -= task->unk5C;
        if (task->unk60 < 0) {
            task->unk60 = 0;
            task->unk28(task, 3);
        }
    }
    task->scale.vz = 0;
    task->scale.vx = task->scale.vy = task->unk60;
    RotMatrixYXZ_gte(&task->rot, &task->matrix);
    ScaleMatrix(&task->matrix, &task->scale);
    in[0].vx = in[2].vx = task->unk50 - task->unk54;
    in[1].vx = in[3].vx = in[0].vx + task->unk58;
    in[0].vy = in[1].vy = task->unk52 - task->unk56;
    in[2].vy = in[3].vy = in[0].vy + task->unk5A;
    in[0].vz = in[1].vz = in[2].vz = in[3].vz = 0;
    for (i = 0; i < 4; i++) {
        ApplyMatrixSV(&task->matrix, &in[i], &out[i]);
        out[i].vx += task->unk54;
        out[i].vy += task->unk56;
    }
    line = D_8004D708.allocPrim();
    for (i = 0; i < 4; i++) {
        order = D_800102BC;
        setLineF2(line);
        setRGB0(line, 0, 0, 0xFF);
        line->x0 = out[i].vx;
        line->y0 = out[i].vy;
        line->x1 = out[order.next[i]].vx;
        line->y1 = out[order.next[i]].vy;
        addPrim(ot, line);
        line++;
    }
    D_8004D708.setPrimEnd(line);
}

void func_8001C454(Task8001C454 *task) {
    switch (task->state) {
    case 0:
    default:
        task->unk68 = 0;
        if (task->unkB8 == 0) {
            task->unk60 = 0;
        } else {
            task->unk60 = 0x1000;
        }
        task->unk90 = 0;
        task->unk88 = task->unk54;
        task->unk8C = task->unk56;
        task->unk38(task);
        break;
    case 1:
        func_8001C168(task);
        break;
    case 2:
    case 3:
        break;
    }
}

Task8001C454 *func_8001C4D8(s32 arg0, s16 x, s16 y, s32 w, s32 h, s32 type) {
    s16 pad = w;
    Task8001C454 *task = func_800144DC(func_8001C454, 0xC0, 0);

    task->unk64 = arg0;
    task->unk54 = x;
    task->unk56 = y;
    task->unk58 = w + 0x20;
    task->unk5A = h;
    if (type == 2 || type == 3) {
        pad = 0;
    }
    task->unk6C = D_8004D49C[type].unk8 - pad;
    task->unk6E = D_8004D49C[type].unkA;
    task->unk50 = x + task->unk6C;
    task->unk52 = y + task->unk6E;
    return task;
}

void func_8001C5C4(Unk8001BB68 *task, s32 x, s32 y) {
    Unk8001C5C4 *children = task->children;
    s32 i;
    u32 type;
    s32 wx;
    s32 wy;
    Task8001C454 *item;

    task->x = x;
    task->y = y;
    for (i = 0; i < 3; i++) {
        item = children->items[i];
        if (item != NULL && item->state == 1) {
            item->unk50 = item->unk6C + x;
            item->unk52 = item->unk6E + y;
        }
    }
    type = task->type;
    if (children->windows[0] != NULL) {
        wx = task->x + D_8004D49C[type].unk14;
        wy = task->y + D_8004D49C[type].unk16;
        if (type < 2) {
            wx -= task->w;
        }
        children->windows[0]->setPos(children->windows[0], wx, wy);
    }
    if (children->windows[1] != NULL) {
        wx = task->x + D_8004D49C[type].unk18;
        wy = task->y + D_8004D49C[type].unk1A;
        if (type < 2) {
            wx -= task->w;
        }
        children->windows[1]->setPos(children->windows[1], wx, wy);
    }
}

typedef struct Delays3 {
    s32 frames[3];
} Delays3;

extern Delays3 D_800102CC;

void func_8001C72C(Unk8001BB68 *task, Unk8001C5C4 *children) {
    Delays3 delays;

    switch (task->state) {
    case 0:
    default:
        task->unk28(task, 2);
        break;
    case 1:
        if (children->windows[1]->m168(children->windows[1]) != 0) {
            task->unk28(task, 2);
            task->unk2C(task, 1);
            children->unk14->unk28(children->unk14, 2);
            children->windows[0]->m144(children->windows[0], 0);
            children->windows[1]->m144(children->windows[1], 0);
        } else if ((D_8004AF78.getButtons(0) >> D_8004AF78.getButtonBit(0, 13)) & 1) {
            children->windows[1]->m128(children->windows[1]);
        }
        if (children->windows[1]->m170(children->windows[1]) != 0) {
            children->unk14->visible = 1;
        } else {
            children->unk14->visible = 0;
        }
        break;
    case 2:
        delays = D_800102CC;
        switch (task->step) {
        case 0:
        default:
            if (task->mode == 0) {
                D_800553DC.playSound(0x40019);
            } else {
                D_800553DC.playSound(0x4001A);
            }
        case 1:
        case 2:
            if (task->counter++ >= delays.frames[task->step]) {
                children->items[task->step] = func_8001C4D8(task->unk54, task->x, task->y, task->w, task->h, task->type);
                children->items[task->step]->unkB8 = task->mode;
                if (task->mode == 0) {
                    children->items[task->step]->unk5C = 0x199;
                } else {
                    children->items[task->step]->unk5C = 0x333;
                }
                task->unk40(task);
                task->counter = 0;
            }
            break;
        case 3:
            if (task->mode == 0) {
                if (children->items[2]->unkBC != 0) {
                    task->unk28(task, 1);
                    children->unk14->unk28(children->unk14, 1);
                    children->windows[0]->m144(children->windows[0], 1);
                    children->windows[1]->m144(children->windows[1], 1);
                }
            } else if (task->mode == 1) {
                if (children->items[2] == NULL) {
                    task->unk28(task, 3);
                }
            }
            break;
        }
        break;
    case 3:
        break;
    }
}

char *strncpy(char *dst, char *src, s32 n);

Unk8001BB68 *func_8001CAC0(s32 id, s16 x, s16 y, s32 file, s32 index, u32 type) {
    Obj8001F8F8 fn;
    char name[0x20];
    Unk8001BB68 *task;
    Unk8001C5C4 *children;
    s32 end;
    u8 *text;
    s32 w;
    s32 i;

    task = func_800144DC((void (*)(void *))func_8001C72C, 0x6C, 0x18);
    task->unk54 = id;
    task->x = x;
    task->y = y;
    children = task->children;
    task->setPos = func_8001C5C4;
    task->type = type;
    func_8001F8F8(&fn);
    i = 0;
    children->windows[0] = func_8001AAB4(task->unk54, 2, task->x + D_8004D49C[type].unk14, task->y + D_8004D49C[type].unk16);
    children->windows[0]->m160(children->windows[0], 3);
    children->windows[1] = func_8001AAB4(task->unk54, 1, task->x + D_8004D49C[type].unk18, task->y + D_8004D49C[type].unk1A);
    children->windows[1]->m160(children->windows[1], 3);
    task->file = file;
    text = (u8 *)fn.unk0(file, index);
    if (text[0] == 2 && text[1] == 7) {
        end = 2;
        while (text[end] != 2 && text[end + 1] != 7) {
            end++;
        }
        D_8004AD84.bzero(name, sizeof(name));
        if (text[i + 2] == 2 && text[i + 3] == 9) {
            strcpy(name, D_8004853C);
        } else {
            strncpy(name, &text[i + 2], -2 - i + end);
        }
        children->windows[0]->m114(children->windows[0], name, -1);
        children->windows[1]->m114(children->windows[1], &text[end + 2], -1);
    } else {
        children->windows[1]->m114(children->windows[1], text, -1);
    }
    children->windows[1]->m130(children->windows[1], 6);
    children->windows[1]->m14C(children->windows[1]);
    w = fn.unk4(children->windows[1]->text, children->windows[1]->unk50, 0);
    if (w < 0x5F) {
        w = 0x5F;
    } else if (w >= 0x8C) {
        w = 0x8B;
    }
    task->w = w;
    task->h = 0x3E;
    if (type < 2) {
        children->windows[0]->setPos(children->windows[0], children->windows[0]->unkB0 - task->w, children->windows[0]->unkB2);
        children->windows[1]->setPos(children->windows[1], children->windows[1]->unkB0 - task->w, children->windows[1]->unkB2);
    }
    for (i = 0; i < 2; i++) {
        children->windows[i]->m138(children->windows[i], 2);
        children->windows[i]->m144(children->windows[i], 0);
    }
    children->unk14 = func_8001C130(task);
    return task;
}

void func_8001CE60(void) {
    Obj8001FBE0 obj;

    func_8001FBE0(&obj);
    obj.methods[2](0x140, 0);
    obj.methods[4](D_80044744.unk424(0x2780000));
    D_80044744.unk418(0x278);
    D_80044744.unk40C(0x277);
}

typedef struct GlyphMap {
    /* 0x0 */ u16 code;
    /* 0x2 */ u8 index;
    /* 0x3 */ u8 pad;
} GlyphMap;

typedef struct FontInfo {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ GlyphMap *unkC;
    /* 0x10 */ GlyphMap *unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
} FontInfo;

s16 func_8001CEE0(u8 *s, u8 mode, FontInfo *font) {
    u16 code;
    GlyphMap *map;
    s32 i;

    if (s[0] == 0) {
        return 0x400;
    }
    if (mode != 0) {
        if (s[0] < 4) {
            return (s[0] << 8) | s[1];
        }
        if (s[0] == 0xA) {
            return 0x201;
        }
        code = s[0] << 8;
        code |= s[1];
        if ((u16)(code - 0x824F) < 0x146) {
            map = font->unkC;
            for (i = 4; map[i].code != 0xFFFF; i++) {
                if (code == map[i].code) {
                    return map[i].index;
                }
            }
        } else {
            map = font->unk10;
            for (i = 0; map[i].code != 0xFFFF; i++) {
                if (code == map[i].code) {
                    return map[i].index | 0x100;
                }
            }
        }
    } else {
        if (s[0] == 1) {
            if (s[1] > font->unk16) {
                return (((u16)font->unk16 + 1) & 0xFF) | 0x100;
            }
            return (s[0] << 8) | s[1];
        }
        if (s[0] < 4) {
            return (s[0] << 8) | s[1];
        }
        if (s[0] < font->unk14) {
            return s[0];
        }
    }
    return 0x300;
}
