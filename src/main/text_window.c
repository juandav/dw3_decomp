#include "game.h"

void setTextBuffer(TextWindow *obj, TextBuffer *buf, char *text) {
    s16 len;
    s16 cap;
    u16 size;

    if (text != NULL) {
        len = strlen(text);
        buf->len = len;
        if (len == 0) {
            obj->visible = 0;
            return;
        }
        obj->visible = 1;
        buf->sjis = 1;
        if (buf->data != NULL) {
            if (buf->cap <= buf->len) {
                HEAP.free(buf->data);
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
        buf->data = HEAP.alloc(cap, 2);
    copy:
        HEAP.zero(buf->data, buf->cap);
        memcpy(buf->data, text, buf->len);
    } else {
        setTextBuffer(obj, buf, STR_NULL_MESSAGE);
    }
    if (obj->typeDelay == 0) {
        textWindowSetTypeDelay(obj, 0);
    }
}

void textWindowSetText(TextWindow *obj, char *text) {
    setTextBuffer(obj, &obj->text[0], text);
}

void textWindowSetString(TextWindow *obj, char *text, s32 id) {
    textWindowSetSubString(obj, text, id, 0);
}

void formatNumber(u8 *buf, s32 value) {
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

void textWindowSetNumber(TextWindow *obj, u32 index, s32 value) {
    u8 buf[16];
    u8 *p;
    s32 i;

    if (index >= 6) {
        textWindowSetText(obj, STR_BAD_DIGIT_BUFFER);
        return;
    }
    for (i = 15, p = &buf[i]; i >= 0; i--) {
        *p-- = 0;
    }
    formatNumber(buf, value);
    for (i = 0; buf[i] != 0; i++) {
        buf[i] -= 0x2C;
    }
    setTextBuffer(obj, &obj->text[index], buf);
    obj->text[index].sjis = 0;
}

void textWindowSetSubText(TextWindow *obj, char *text, s32 index) {
    if (index < 1 || index > 5) {
        textWindowSetText(obj, STR_BAD_EXT_BUFFER);
    } else {
        setTextBuffer(obj, &obj->text[index], text);
    }
}

void textWindowSetSubString(TextWindow *obj, char *text, s32 id, s32 index) {
    TextTools cls;
    char *str;

    if (id >= 0) {
        initTextTools(&cls);
        str = cls.getString(text, id);
        if (str == NULL) {
            return;
        }
        setTextBuffer(obj, &obj->text[index], str);
    } else {
        setTextBuffer(obj, &obj->text[index], text);
    }
    obj->text[index].sjis = 0;
}

INCLUDE_RODATA("main/nonmatchings/text_window", STR_NULL_MESSAGE);

INCLUDE_RODATA("main/nonmatchings/text_window", STR_BAD_DIGIT_BUFFER);

INCLUDE_RODATA("main/nonmatchings/text_window", STR_BAD_EXT_BUFFER);

INCLUDE_RODATA("main/nonmatchings/text_window", STR_MESSAGE_NOT_SET);

void textWindowDraw(TextWindow *obj) {
    TextDraw wait;
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
        obj->visible = 0;
        return;
    }
    for (i = 5; i >= 0; i--) {
        obj->text[i].pos = 0;
    }
    obj->finished = 0;
    obj->cursorX = -obj->alignWidth;
    wait.lineCount = 0;
    text = obj->text;
    obj->cursorY = 0;
    if (obj->scaled != 0) {
        if (obj->scaleX == 0 && obj->scaleY == 0) {
            return;
        }
        if (obj->scaleX == 0x1000 && obj->scaleY == obj->scaleX) {
            obj->scaled = 0;
        } else {
            rotated = 1;
            RotMatrixYXZ_gte(&obj->rot, &obj->mat);
            ScaleMatrix(&obj->mat, (VECTOR *)&obj->scaleX);
        }
    }
    i = 0;
    wait.layer = GFX.funcs.getLayer(obj->layerId);
    wait.ot = (u_long *)wait.layer->getOtEntry(wait.layer, obj->depth);
    wait.prim = GFX.funcs.getPrim();
    text->pos = obj->start;
    while (i < (s16)obj->visibleEnd - obj->start) {
        if (obj->finished != 0) {
            break;
        }
        c = FONT.decode(text->data + text->pos, (u8)text->sjis, obj->style);
        wait.code = c;
        wait.kind = (u32)(c << 16) >> 24;
        switch (processTextChar(obj, text, &wait, &text->pos)) {
        case 1:
            i++;
            goto draw;
        case 4:
            i++;
            continue;
        case 2:
        draw:
            if (wait.glyph->page == 0xFF) {
                wait.glyph = *(Glyph **)(obj->style + 4);
            }
            x = obj->cursorX + (obj->x + wait.glyph->dx);
            y = obj->cursorY + (obj->y + wait.glyph->dy);
            clut = getClut(obj->texX + wait.glyph->clutX, obj->palette + (obj->texY + wait.glyph->clutY));
            u = wait.glyph->u;
            v = wait.glyph->v;
            if ((s8)obj->blend == -1) {
                tpage = getTPage(0, 1, obj->texX + (wait.glyph->page << 6), obj->texY);
            } else {
                tpage = getTPage(0, obj->blend & 3, obj->texX + (wait.glyph->page << 6), obj->texY);
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
                if ((s8)obj->blend != -1) {
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
                in[0].vx = in[2].vx = x - obj->pivotX;
                in[1].vx = in[3].vx = in[0].vx + wait.glyph->w;
                in[0].vy = in[1].vy = y - obj->pivotY;
                in[2].vy = in[3].vy = in[0].vy + wait.glyph->h;
                in[0].vz = in[1].vz = in[2].vz = in[3].vz = 0;
                for (j = 0; j < 4; j++) {
                    ApplyMatrixSV(&obj->mat, &in[j], &out);
                    (&((POLY_FT4 *)wait.prim)->x0)[j * 4] = out.vx + obj->pivotX;
                    (&((POLY_FT4 *)wait.prim)->y0)[j * 4] = out.vy + obj->pivotY;
                }
                ((POLY_FT4 *)wait.prim)->u0 = ((POLY_FT4 *)wait.prim)->u2 = u;
                ((POLY_FT4 *)wait.prim)->u1 = ((POLY_FT4 *)wait.prim)->u3 = ((POLY_FT4 *)wait.prim)->u0 + wait.glyph->w - 1;
                ((POLY_FT4 *)wait.prim)->v0 = ((POLY_FT4 *)wait.prim)->v1 = v;
                ((POLY_FT4 *)wait.prim)->v2 = ((POLY_FT4 *)wait.prim)->v3 = ((POLY_FT4 *)wait.prim)->v0 + wait.glyph->h - 1;
                if ((s8)obj->blend != -1) {
                    setSemiTrans((POLY_FT4 *)wait.prim, 1);
                }
                ((POLY_FT4 *)wait.prim)->tpage = tpage;
                ((POLY_FT4 *)wait.prim)->clut = clut;
                addPrim(wait.ot, wait.prim);
                wait.prim = (POLY_FT4 *)wait.prim + 1;
            }
            if (obj->fixedSpacing != 0) {
                obj->cursorX += obj->spacingX;
            } else {
                obj->cursorX += wait.glyph->advance + wait.glyph->dx;
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
    GFX_FUNCS.setPrim(wait.prim);
}

void textWindowShowPage(TextWindow *obj) {
    s32 extra;
    s32 pos;
    s32 lines;
    s32 going;
    u8 *p;
    u8 index;
    s32 c;

    if (obj->state == 1) {
        pos = obj->start;
        extra = 0;
        lines = 0;
        going = 1;
        do {
            switch ((s32)((u32)(FONT.decode(obj->text[0].data + pos, (u8)obj->text[0].sjis, obj->style) << 16) >> 24)) {
            case 0:
            default:
                if (obj->text[0].sjis != 0) {
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
                    pos += FONT.codeLengths[c];
                    break;
                case 1:
                    if (++lines < obj->lines) {
                        pos += FONT.codeLengths[1];
                    } else {
                        going = 0;
                    }
                    break;
                case 2:
                    if (p[2] < 5) {
                        going = 0;
                    }
                    pos += FONT.codeLengths[2];
                    break;
                case 5:
                    index = p[2];
                    if (index < 6) {
                        extra += obj->text[index].len;
                        pos += FONT.codeLengths[5];
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
        obj->visibleEnd = pos + extra;
    }
}

void textWindowSetStyle(TextWindow *obj, s32 style) {
    u8 *entry;

    if (style < 1 || style > 3) {
        style = 1;
    }
    entry = FONT.styles + style * 0x18;
    obj->style = entry;
    obj->blend = *entry;
}

void textWindowSetTypeDelay(TextWindow *obj, s32 delay) {
    if (delay <= 0) {
        obj->typeTimer = 0;
        obj->typeDelay = 0;
        obj->visibleEnd = obj->text[0].len;
        return;
    }
    obj->visibleEnd = 0;
    obj->typeTimer = 0;
    obj->typeDelay = delay;
    obj->start = 0;
}

void textWindowSetPos(TextWindow *obj, s16 x, s16 y) {
    obj->x = x;
    obj->y = y;
}

void textWindowSetPalette(TextWindow *obj, u8 palette) {
    obj->palette = palette;
}

void textWindowSetBlend(TextWindow *obj, u8 blend) {
    obj->blend = blend;
}

void textWindowSetSpacing(TextWindow *obj, s16 x, s16 y) {
    if (x != 0 || y != 0) {
        obj->fixedSpacing = 1;
        obj->spacingX = x;
        obj->spacingY = y;
    } else {
        obj->fixedSpacing = 0;
        obj->spacingX = 0;
        obj->spacingY = 0;
    }
}

void textWindowSetVisible(TextWindow *obj, u8 visible) {
    if (obj->text[0].len == 0) {
        obj->visible = 0;
    } else {
        obj->visible = visible;
    }
}

void textWindowSetRightAlign(TextWindow *obj, u8 type) {
    TextTools cls;

    if (type != 0) {
        initTextTools(&cls);
        obj->alignWidth = cls.measure(&obj->text[0], obj->style, obj->spacingX);
    } else {
        obj->alignWidth = 0;
    }
}

void textWindowInsertPlayerName(TextWindow *obj) {
    TextBuffer *text = &obj->text[0];
    s32 pos;
    u8 c;
    u8 index;

    if (obj->text[0].data != NULL) {
        for (pos = 0; pos < obj->text[0].len;) {
            switch ((s32)((u32)(FONT.decode(text->data + pos, (u8)text->sjis, obj->style) << 16) >> 24)) {
            case 0:
            case 3:
            default:
                if (text->sjis != 0) {
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
                    textWindowSetSubText(obj, PLAYER_NAME, index);
                    obj->text[index].sjis = 0;
                    pos += FONT.codeLengths[8];
                } else {
                    pos += FONT.codeLengths[c];
                }
                break;
            case 4:
                return;
            }
        }
    }
}

void textWindowSetTypeSound(TextWindow *obj, s32 sound) {
    obj->typeSound = sound;
}

void textWindowSetScale(TextWindow *obj, s32 x, s32 y) {
    obj->scaleZ = 0x1000;
    obj->scaleX = x;
    obj->scaleY = y;
    obj->scaled = 1;
}

void textWindowSetPivot(TextWindow *obj, s32 x, s32 y) {
    obj->pivotX = x;
    obj->pivotY = y;
}

void textWindowSetDepth(TextWindow *obj, s32 depth) {
    obj->depth = depth;
}

void textWindowSetLines(TextWindow *obj, u8 lines) {
    obj->lines = lines;
}

void textWindowSetUnkC4(TextWindow *obj, u8 value) {
    obj->unkC4 = value;
}

u8 textWindowIsFinished(TextWindow *obj) {
    return obj->finished;
}

u8 textWindowIsVisible(TextWindow *obj) {
    return obj->visible;
}

s32 textWindowIsWaitingForButton(TextWindow *obj) {
    return obj->substate == 1;
}

extern s32 (*TEXT_CODE_HANDLERS[])(TextWindow *obj, TextBuffer *text, TextDraw *wait);

s32 processTextChar(TextWindow *obj, TextBuffer *text, TextDraw *wait, s16 *pos) {
    TextStyle *style;
    s32 c;
    s32 ret;
    s32 n;

    switch (wait->kind) {
    case 2:
        if (text->sjis != 0) {
            if ((u8)wait->code == 1) {
                ret = TEXT_CODE_HANDLERS[1](obj, text, wait);
                *pos += 1;
            } else {
                return TEXT_CODE_HANDLERS[0](obj, text, wait);
            }
        } else {
            c = text->data[*pos + 1];
            if (TEXT_CODE_HANDLERS[c] == NULL) {
                return TEXT_CODE_HANDLERS[0](obj, text, wait);
            }
            ret = TEXT_CODE_HANDLERS[c](obj, text, wait);
            if (ret & 0x8000) {
                *pos += FONT.codeLengths[c];
            }
        }
        return ret & ~0x8000;
    case 0:
        wait->glyph = &((Glyph *)((TextStyle *)obj->style)->glyphs)[wait->code - 4];
        if (text->sjis != 0) {
            *pos += 2;
        } else {
            *pos += 1;
        }
        break;
    case 1:
        style = (TextStyle *)obj->style;
        n = (u8)wait->code;
        if (n <= style->iconCount && n > 0) {
            wait->glyph = &((Glyph *)style->icons)[n - 1];
        } else {
            wait->glyph = (Glyph *)((TextStyle *)obj->style)->glyphs;
        }
        *pos += 2;
        break;
    case 4:
        obj->finished = 1;
        *pos += 1;
        return 3;
    default:
        wait->glyph = (Glyph *)((TextStyle *)obj->style)->glyphs;
        if (text->sjis != 0) {
            *pos += 2;
        } else {
            *pos += 1;
        }
        break;
    }
    return 1;
}

s32 textCodeDefault(TextWindow *obj, TextBuffer *buf) {
    switch (buf->data[buf->pos + 1]) {
    case 0:
    default:
        textWindowShowPage(obj);
        break;
    case 7:
        obj->start = buf->pos + 2;
        break;
    }
    return 0;
}

s32 textCodeNewLine(TextWindow *obj, TextBuffer *buf, TextDraw *wait) {
    if (++wait->lineCount == 1) {
        wait->pageStart = buf->pos + 2;
    } else if (wait->lineCount >= obj->lines) {
        obj->start = wait->pageStart;
        if (obj->lines >= 2) {
            obj->lines--;
            textWindowShowPage(obj);
            obj->lines++;
        }
        return 0x8000;
    }
    obj->cursorX = 0;
    if (obj->fixedSpacing != 0) {
        obj->cursorY += obj->spacingY;
    } else {
        obj->cursorY += (s8)obj->style[1];
    }
    return 0x8004;
}

s32 textCodeWaitButton(TextWindow *obj, TextBuffer *buf) {
    if (buf->data[buf->pos + 2] < 5) {
        obj->state = 2;
        obj->substate = 1;
        if (buf->data[buf->pos + 2] < 1 || buf->data[buf->pos + 2] > 4) {
            obj->step = 0;
        } else {
            obj->step = buf->data[buf->pos + 2];
        }
        obj->counter = buf->pos + 2;
        return 0;
    }
    return 0x8003;
}

s32 textCodePageBreak(TextWindow *obj, TextBuffer *buf) {
    u8 c;

    if (obj->typeDelay != 0) {
        obj->visibleEnd = buf->pos + 2;
    } else {
        obj->visibleEnd = buf->len;
    }
    while (buf->pos < buf->len) {
        switch ((s32)((u32)(FONT.decode(buf->data + buf->pos, (u8)buf->sjis, obj->style) << 16) >> 24)) {
        case 0:
        case 1:
        default:
            obj->start = buf->pos;
            buf->pos = buf->len + 1;
            break;
        case 2:
            c = buf->data[buf->pos + 1];
            if (c == 5 || c == 8) {
                obj->start = buf->pos;
                buf->pos = buf->len + 1;
            } else {
                buf->pos += FONT.codeLengths[c];
            }
            break;
        case 4:
            obj->start = buf->pos - 1;
            return 3;
        }
    }
    return 0;
}

s32 textCodeIgnore(void) {
    return 0x8003;
}

s32 textCodeInsert(TextWindow *obj, TextBuffer *buf, TextDraw *wait) {
    u8 index = buf->data[buf->pos + 2];
    s16 c;
    s32 ret;

    if (obj->text[index].data == NULL) {
        textWindowSetSubText(obj, STR_MESSAGE_NOT_SET, index);
        return 0x8003;
    }
    if (obj->text[index].pos >= obj->text[index].len) {
        return 0x8003;
    }
    c = FONT_DECODE(obj->text[index].data + obj->text[index].pos, (u8)obj->text[index].sjis, obj->style, obj->text[index].pos);
    wait->code = c;
    wait->kind = (u32)(c << 16) >> 24;
    if (wait->kind == 2) {
        return 0x8000;
    }
    if (obj->typeDelay != 0) {
        return processTextChar(obj, &obj->text[index], wait, &obj->text[index].pos);
    }
    ret = processTextChar(obj, &obj->text[index], wait, &obj->text[index].pos);
    if (ret == 1) {
        return 2;
    }
    return ret;
}

s32 textCodePause(TextWindow *obj, TextBuffer *buf) {
    if (buf->data[buf->pos + 2] < 0xFF) {
        obj->state = 2;
        obj->substate = 0;
        obj->step = buf->data[buf->pos + 2];
        buf->data[buf->pos + 2] = 0xFF;
        obj->typeTimer = 0;
        return 0x8000;
    }
    return 0x8003;
}

s32 textCodePlayerName(s32 obj, TextBuffer *buf) {
    if ((u8)buf->data[buf->pos + 2] < 6) {
        textWindowSetSubString(obj, PLAYER_NAME, -1, (u8)buf->data[buf->pos + 2]);
        buf->data[buf->pos + 2] = 6;
    }
    return 0x8003;
}

void updateTextWindow(TextWindow *obj) {
    s32 i;

    switch (obj->state) {
    case 0:
    default:
        obj->nextState(obj);
        break;
    case 1:
        if (obj->visible != 0) {
            if (obj->typeDelay > 0 && obj->finished == 0) {
                if (++obj->typeTimer > obj->typeDelay) {
                    obj->typeTimer = 0;
                    obj->visibleEnd++;
                    if (obj->typeSound != 0) {
                        SOUND.playSound(obj->typeSound);
                    }
                }
            }
            textWindowDraw(obj);
        }
        break;
    case 2:
        switch (obj->substate) {
        case 0:
        default:
            textWindowDraw(obj);
            if (++obj->typeTimer > obj->step) {
                obj->typeTimer = 0;
                obj->setState(obj, TASK_RUN);
            }
            break;
        case 1:
            if ((PAD.getPressed(0) >> PAD.getButtonBit(0, TEXT_WAIT_BUTTONS[obj->step])) & 1) {
                obj->text[0].data[obj->counter] = 5;
                obj->typeTimer = obj->typeDelay;
                obj->setState(obj, TASK_RUN);
            }
            textWindowDraw(obj);
            break;
        }
        break;
    case 3:
        for (i = 0; i < 6; i++) {
            if (obj->text[i].data != NULL) {
                HEAP.free(obj->text[i].data);
            }
        }
        break;
    }
}

TextWindow *createTextWindow(s16 layerId, s16 style, s16 x, s16 y) {
    TextWindow *ret;
    TextWindow *obj = createTask(updateTextWindow, 0x174, 0);

    obj->setText = textWindowSetText;
    obj->setString = textWindowSetString;
    obj->setNumber = textWindowSetNumber;
    obj->setSubText = textWindowSetSubText;
    obj->setSubString = textWindowSetSubString;
    obj->draw = textWindowDraw;
    obj->showPage = textWindowShowPage;
    obj->setStyle = textWindowSetStyle;
    obj->setTypeDelay = textWindowSetTypeDelay;
    obj->setPos = textWindowSetPos;
    obj->setPalette = textWindowSetPalette;
    obj->setBlend = textWindowSetBlend;
    obj->setSpacing = textWindowSetSpacing;
    obj->setVisible = textWindowSetVisible;
    obj->setRightAlign = textWindowSetRightAlign;
    obj->insertPlayerName = textWindowInsertPlayerName;
    obj->setTypeSound = textWindowSetTypeSound;
    obj->setScale = textWindowSetScale;
    obj->setPivot = textWindowSetPivot;
    obj->setDepth = textWindowSetDepth;
    obj->setLines = textWindowSetLines;
    obj->setUnkC4 = textWindowSetUnkC4;
    obj->isFinished = textWindowIsFinished;
    obj->isVisible = textWindowIsVisible;
    obj->isWaitingForButton = textWindowIsWaitingForButton;
    if (style < 1 || style > 3) {
        style = 1;
    }
    obj->layerId = layerId;
    ret = obj;
    ret->style = style * 0x18 + FONT.styles;
    ret->x = x;
    ret->texX = 0x140;
    ret->y = y;
    ret->texY = 0;
    ret->lines = 1;
    ret->blend = ret->style[0];
    ret->scaleX = ret->scaleY = ret->scaleZ = 0x1000;
    return ret;
}

void cursorSetVisible(Cursor *task, s32 visible) {
    task->visible = visible;
    if (visible == 0) {
        task->substate = 0;
        task->time = 0;
    }
    task->dirty = 1;
}

void cursorSetPos(Cursor *task, s32 x, s32 y) {
    task->x = x;
    task->y = y;
    task->dirty = 1;
}

void cursorSetPalette(Cursor *task, s32 palette) {
    task->palette = palette;
    task->dirty = 1;
}

void cursorSetIdleDelay(Cursor *task, s32 delay) {
    task->idleDelay = delay;
}

void cursorSetFrameDelay(Cursor *task, s32 delay) {
    task->frameDelay = delay;
}

void cursorSetStill(Cursor *task, s32 still) {
    task->still = still;
}

void updateCursor(Cursor *task, TextWindow **win) {
    switch (task->state) {
    case 0:
    default:
        if (*win == NULL) {
            *win = createTextWindow(task->layerId, 1, task->x, task->y);
        }
        (*win)->setText(*win, CURSOR_FRAMES[task->frame]);
        (*win)->setVisible(*win, task->visible);
        (*win)->setDepth(*win, task->depth);
        task->time = GFX_FUNCS.getTime();
        task->nextState(task);
        break;
    case 1:
        if (task->dirty != 0) {
            (*win)->setVisible(*win, task->visible);
            (*win)->setPos(*win, task->x, task->y);
            (*win)->setPalette(*win, task->palette);
            task->dirty = 0;
        }
        if (task->visible != 0) {
            if (task->still != 0) {
                if (task->frame != 0) {
                    task->frame = 0;
                    (*win)->setText(*win, CURSOR_FRAMES[0]);
                }
            } else if (task->substate == 0) {
                if ((GFX.funcs.getTime() - task->time) / task->idleDelay != 0) {
                    task->time = GFX.funcs.getTime();
                    task->frame = 1;
                    (*win)->setText(*win, CURSOR_FRAMES[1]);
                    task->substate = 1;
                }
            } else if ((GFX.funcs.getTime() - task->time) / task->frameDelay != 0) {
                task->time = GFX.funcs.getTime();
                if (++task->frame >= 5) {
                    task->frame = 0;
                    task->substate = 0;
                }
                (*win)->setText(*win, CURSOR_FRAMES[task->frame]);
            }
        }
        break;
    case 2:
    case 3:
        break;
    }
}

Cursor *createCursor(s16 layerId, s32 depth, s16 x, s16 y) {
    Cursor *task = createTask(updateCursor, 0x98, 4);

    task->layerId = layerId;
    task->depth = depth;
    task->x = x;
    task->y = y;
    task->visible = 1;
    task->idleDelay = 0x20;
    task->frameDelay = 6;
    task->setVisible = cursorSetVisible;
    task->setPos = cursorSetPos;
    task->setIdleDelay = cursorSetIdleDelay;
    task->setFrameDelay = cursorSetFrameDelay;
    task->setPalette = cursorSetPalette;
    task->setStill = cursorSetStill;
    return task;
}

void decompressorFree(Decompressor *task) {
    if (task->buffer != NULL) {
        HEAP.free(task->buffer);
    }
    task->buffer = NULL;
    task->bufferSize = 0;
}

void decompressorSetData(Decompressor *task, s32 *data) {
    task->data = data;
    if (data[0] == 0x4E454C52) {
        task->compressed = 1;
        task->size = data[1];
    } else {
        task->compressed = 0;
        task->size = 0;
    }
    data += 2;
    task->begin = data;
    task->src = data;
}

void decompressorAllocBuffer(Decompressor *task) {
    if (task->size > task->bufferSize) {
        if (task->buffer != NULL) {
            HEAP.free(task->buffer);
        }
        task->buffer = HEAP.alloc(task->size, 2);
        task->bufferSize = task->size;
    }
    task->dst = task->buffer;
}

void decompressorStep(Decompressor *task) {
    u8 *src = (u8 *)task->src;
    u8 *dst = task->dst;
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
        if (total >= task->chunkSize) {
            done = 1;
            task->src = (s32 *)src;
            task->dst = dst;
            break;
        }
    }
    if (!done) {
        task->setSubstate(task, 0);
    }
}

void *decompressorRun(Decompressor *task, s32 *data) {
    task->chunkSize = 0x10000000;
    decompressorSetData(task, data);
    if (task->compressed) {
        decompressorAllocBuffer(task);
        decompressorStep(task);
        return task->buffer;
    }
    return data;
}

void decompressorStart(Decompressor *task, s32 *data, s32 chunkSize) {
    task->chunkSize = chunkSize;
    decompressorSetData(task, data);
    if (task->compressed) {
        decompressorAllocBuffer(task);
        task->setSubstate(task, 1);
    }
}

void *decompressorGetData(Decompressor *task) {
    if (task->substate != 0) {
        return NULL;
    }
    if (task->compressed != 0) {
        return task->buffer;
    }
    return task->data;
}

void updateDecompressor(Decompressor *task) {
    switch (task->state) {
    case 0:
    default:
        task->nextState(task);
        break;
    case 1:
        if (task->substate != 0 && task->substate == task->state) {
            decompressorStep(task);
        }
        break;
    case 2:
        break;
    case 3:
        if (task->buffer != NULL) {
            HEAP.free(task->buffer);
        }
        break;
    }
}

void createDecompressor(void) {
    Decompressor *task = createTask(updateDecompressor, 0x84, 0);

    task->run = decompressorRun;
    task->free = decompressorFree;
    task->start = decompressorStart;
    task->getData = decompressorGetData;
}

void drawMessageBoxFrame(MessageBoxFrame *task) {
    SpriteDrawer obj;
    s32 i;
    s32 x;
    FileCache *cache;

    i = 0;
    cache = &FILE_CACHE;
    x = 0;
    for (; i < 2; i++) {
        initSpriteDrawer(&obj);
        obj.setLayerId(task->layerId, 0);
        obj.setTexture(0x140, 0);
        if (task->substate == 0) {
            obj.setScale(task->scale, 0x1000, 0x1000);
            obj.setPivot(0x140 - x, 0xC4);
        } else if (task->substate == 2) {
            obj.setClutRow(task->fadeRow);
        }
        obj.draw(cache->getEntry(FILE_MENU_SPRITES << 16), i + 8, 0, 0xA6);
        x += 0x140;
    }
}

void drawMessageBoxArrow(MessageBoxFrame *task) {
    SpriteDrawer obj;

    initSpriteDrawer(&obj);
    obj.setLayerId(task->layerId, 0);
    obj.setTexture(0x140, 0);
    if (GFX.funcs.getTime() - task->arrowTime >= 4) {
        task->arrowTime = GFX.funcs.getTime();
        if (++task->arrowFrame >= 5) {
            task->arrowFrame = 0;
        }
    }
    obj.setClutRow(task->arrowFrame);
    obj.draw(FILE_CACHE_GET_ENTRY[0](FILE_MENU_SPRITES << 16), 10, 0x124, 0xCD);
}

void updateMessageBoxFrame(MessageBoxFrame *task) {
    switch (task->state) {
    case 0:
    default:
        task->nextState(task);
        task->scaleStep = 0x199;
        break;
    case 1:
        switch (task->substate) {
        case 0:
        default:
            task->scale += task->scaleStep;
            if (task->scale > 0x1000) {
                task->scale = 0x1000;
                task->nextSubstate(task);
            }
            break;
        case 1:
            if (task->showArrow != 0) {
                drawMessageBoxArrow(task);
            }
            break;
        case 2:
            if (GFX.funcs.getTime() - task->time >= 3) {
                task->time = GFX.funcs.getTime();
                if (++task->fadeRow >= 5) {
                    task->setState(task, TASK_KILL);
                    return;
                }
            }
            break;
        }
        drawMessageBoxFrame(task);
        break;
    case 2:
    case 3:
        break;
    }
}

MessageBoxFrame *createMessageBoxFrame(s32 layerId) {
    MessageBoxFrame *task = createTask(updateMessageBoxFrame, 0x6C, 0);

    task->layerId = layerId;
    SOUND.playSound(0x40019);
    return task;
}

void updateMessageBox(MessageBoxFrame *task, MessageBox *data) {
    switch (task->state) {
    case 0:
    default:
        task->nextState(task);
        break;
    case 1:
        switch (task->substate) {
        case 0:
        default:
            if (data->window->isVisible(data->window) == 0 && data->frame->substate == 1) {
                data->window->setVisible(data->window, 1);
                task->substate++;
            }
            break;
        case 1:
            if (data->window->isFinished(data->window) != 0) {
                data->frame->substate = 2;
                data->window->setVisible(data->window, 0);
                task->substate++;
                SOUND.playSound(0x4001A);
                break;
            }
            if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1) {
                data->window->showPage(data->window);
            }
            if (data->window->isWaitingForButton(data->window) != 0) {
                data->frame->showArrow = 1;
            } else {
                data->frame->showArrow = 0;
            }
            break;
        case 2:
            if (data->frame == NULL) {
                task->setState(task, TASK_KILL);
            }
            break;
        }
        break;
    case 2:
    case 3:
        break;
    }
}

Task *createMessageBox(s32 layerId, s32 strings, s32 index) {
    Task *task = createTask(updateMessageBox, 0x50, 8);
    MessageBox *data = task->children;

    data->window = createTextWindow(layerId, 1, 0x12, 0xB0);
    data->window->setLines(data->window, 3);
    data->window->setString(data->window, strings, index);
    data->window->setVisible(data->window, 0);
    data->window->setTypeDelay(data->window, 6);
    data->frame = createMessageBoxFrame(layerId);
    return task;
}

INCLUDE_ASM("main/nonmatchings/text_window", drawTalkBoxArrow);

void drawTalkBoxFrame(TalkBoxFrame *task) {
    SpriteDrawer obj;
    SVECTOR v[4];
    TalkBox *parent = task->parent;
    u32 type = parent->type;
    s32 pad;
    s32 i;
    s32 x;
    FileCache *cache;
    u_long *ot;
    Layer *layer;
    POLY_FT4 *p;
    DVECTOR *pos;

    pad = 0;
    if (type < 2) {
        pad = parent->w;
    }
    pos = &TALK_BOX_LAYOUTS[type].parts;
    initSpriteDrawer(&obj);
    obj.setLayerId(task->parent->layerId, 0);
    obj.setTexture(0x140, 0);
    cache = &FILE_CACHE;
    for (i = 0; i < 4; pos++, i++) {
        switch (i) {
        case 0:
            obj.draw(cache->getEntry(FILE_MENU_SPRITES << 16), TALK_BOX_LAYOUTS[type].sprite, task->parent->x + pos->vx,
                           task->parent->y + pos->vy);
            break;
        case 1:
            obj.draw(cache->getEntry(FILE_MENU_SPRITES << 16), 0, task->parent->x + pos->vx - pad, task->parent->y + pos->vy);
            break;
        case 3:
            if (type < 2) {
                obj.draw(cache->getEntry(FILE_MENU_SPRITES << 16), 2, task->parent->x + pos->vx, task->parent->y + pos->vy);
            } else {
                x = task->parent->w - 14;
                obj.draw(cache->getEntry(FILE_MENU_SPRITES << 16), 2, task->parent->x + x, task->parent->y + pos->vy);
            }
            break;
        }
    }
    layer = GFX.funcs.getLayer(task->parent->layerId);
    ot = (u_long *)layer->getOtEntry(layer, 0);
    pos = &TALK_BOX_LAYOUTS[type].panel;
    v[0].vx = v[2].vx = task->parent->x + pos->vx - pad;
    v[1].vx = v[3].vx = v[0].vx + task->parent->w;
    v[0].vy = v[1].vy = task->parent->y + pos->vy;
    v[2].vy = v[3].vy = v[0].vy + task->parent->h;
    v[0].vz = v[1].vz = v[2].vz = v[3].vz = 0;
    p = GFX.funcs.getPrim();
    setPolyFT4(p);
    setRGB0(p, 0x80, 0x80, 0x80);
    p->tpage = 0x45;
#if VERSION_US
    p->clut = 0x2E57;
#elif VERSION_EU
    p->clut = 0x2C57;
#endif
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
    GFX.funcs.setPrim(p + 1);
}

void updateTalkBoxFrame(Task *task) {
    switch (task->state) {
    case 0:
    default:
        task->setState(task, TASK_DONE);
        break;
    case 1:
        drawTalkBoxArrow(task);
        drawTalkBoxFrame((TalkBoxFrame *)task);
        break;
    case 2:
    case 3:
        break;
    }
}

TalkBoxFrame *createTalkBoxFrame(TalkBox *parent) {
    TalkBoxFrame *task = createTask(updateTalkBoxFrame, 0x60, 0);

    task->parent = parent;
    return task;
}

typedef struct Order4 {
    s32 next[4];
} Order4;

extern Order4 OUTLINE_ORDER;

void drawZoomBox(ZoomBox *task) {
    Layer *layer = GFX_FUNCS.getLayer(task->layerId);
    u_long *ot = (u_long *)layer->getOtEntry(layer, 0);
    SVECTOR out[4];
    SVECTOR in[4];
    LINE_F2 *line;
    Order4 order;
    s32 i;

    if (task->closing == 0) {
        task->zoom += task->speed;
        if (task->zoom > 0x1000) {
            task->zoom = 0x1000;
            task->opened = 1;
            task->setState(task, TASK_KILL);
        }
    } else {
        task->zoom -= task->speed;
        if (task->zoom < 0) {
            task->zoom = 0;
            task->setState(task, TASK_KILL);
        }
    }
    task->scale.vz = 0;
    task->scale.vx = task->scale.vy = task->zoom;
    RotMatrixYXZ_gte(&task->rot, &task->matrix);
    ScaleMatrix(&task->matrix, &task->scale);
    in[0].vx = in[2].vx = task->left - task->x;
    in[1].vx = in[3].vx = in[0].vx + task->w;
    in[0].vy = in[1].vy = task->top - task->y;
    in[2].vy = in[3].vy = in[0].vy + task->h;
    in[0].vz = in[1].vz = in[2].vz = in[3].vz = 0;
    for (i = 0; i < 4; i++) {
        ApplyMatrixSV(&task->matrix, &in[i], &out[i]);
        out[i].vx += task->x;
        out[i].vy += task->y;
    }
    line = GFX_FUNCS.getPrim();
    for (i = 0; i < 4; i++) {
        order = OUTLINE_ORDER;
        setLineF2(line);
        setRGB0(line, 0, 0, 0xFF);
        line->x0 = out[i].vx;
        line->y0 = out[i].vy;
        line->x1 = out[order.next[i]].vx;
        line->y1 = out[order.next[i]].vy;
        addPrim(ot, line);
        line++;
    }
    GFX_FUNCS.setPrim(line);
}

void updateZoomBox(ZoomBox *task) {
    switch (task->state) {
    case 0:
    default:
        task->unk68 = 0;
        if (task->closing == 0) {
            task->zoom = 0;
        } else {
            task->zoom = 0x1000;
        }
        task->unk90 = 0;
        task->unk88 = task->x;
        task->unk8C = task->y;
        task->nextState(task);
        break;
    case 1:
        drawZoomBox(task);
        break;
    case 2:
    case 3:
        break;
    }
}

ZoomBox *createZoomBox(s32 layerId, s16 x, s16 y, s32 w, s32 h, s32 type) {
    s16 pad = w;
    ZoomBox *task = createTask(updateZoomBox, 0xC0, 0);

    task->layerId = layerId;
    task->x = x;
    task->y = y;
    task->w = w + 0x20;
    task->h = h;
    if (type == 2 || type == 3) {
        pad = 0;
    }
    task->offsetX = TALK_BOX_LAYOUTS[type].zoomX - pad;
    task->offsetY = TALK_BOX_LAYOUTS[type].zoomY;
    task->left = x + task->offsetX;
    task->top = y + task->offsetY;
    return task;
}

void talkBoxSetPos(TalkBox *task, s32 x, s32 y) {
    TalkBoxChildren *children = task->children;
    s32 i;
    u32 type;
    s32 wx;
    s32 wy;
    ZoomBox *item;

    task->x = x;
    task->y = y;
    for (i = 0; i < 3; i++) {
        item = children->zoomBoxes[i];
        if (item != NULL && item->state == 1) {
            item->left = item->offsetX + x;
            item->top = item->offsetY + y;
        }
    }
    type = task->type;
    if (children->windows[0] != NULL) {
        wx = task->x + TALK_BOX_LAYOUTS[type].nameX;
        wy = task->y + TALK_BOX_LAYOUTS[type].nameY;
        if (type < 2) {
            wx -= task->w;
        }
        children->windows[0]->setPos(children->windows[0], wx, wy);
    }
    if (children->windows[1] != NULL) {
        wx = task->x + TALK_BOX_LAYOUTS[type].textX;
        wy = task->y + TALK_BOX_LAYOUTS[type].textY;
        if (type < 2) {
            wx -= task->w;
        }
        children->windows[1]->setPos(children->windows[1], wx, wy);
    }
}

typedef struct Delays3 {
    s32 frames[3];
} Delays3;

extern Delays3 ZOOM_BOX_DELAYS;

void updateTalkBox(TalkBox *task, TalkBoxChildren *children) {
    Delays3 delays;

    switch (task->state) {
    case 0:
    default:
        task->setState(task, TASK_DONE);
        break;
    case 1:
        if (children->windows[1]->isFinished(children->windows[1]) != 0) {
            task->setState(task, TASK_DONE);
            task->setSubstate(task, 1);
            children->frame->setState(children->frame, TASK_DONE);
            children->windows[0]->setVisible(children->windows[0], 0);
            children->windows[1]->setVisible(children->windows[1], 0);
        } else if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1) {
            children->windows[1]->showPage(children->windows[1]);
        }
        if (children->windows[1]->isWaitingForButton(children->windows[1]) != 0) {
            children->frame->showArrow = 1;
        } else {
            children->frame->showArrow = 0;
        }
        break;
    case 2:
        delays = ZOOM_BOX_DELAYS;
        switch (task->step) {
        case 0:
        default:
            if (task->substate == 0) {
                SOUND.playSound(0x40019);
            } else {
                SOUND.playSound(0x4001A);
            }
        case 1:
        case 2:
            if (task->timer++ >= delays.frames[task->step]) {
                children->zoomBoxes[task->step] = createZoomBox(task->layerId, task->x, task->y, task->w, task->h, task->type);
                children->zoomBoxes[task->step]->closing = task->substate;
                if (task->substate == 0) {
                    children->zoomBoxes[task->step]->speed = 0x199;
                } else {
                    children->zoomBoxes[task->step]->speed = 0x333;
                }
                task->nextStep(task);
                task->timer = 0;
            }
            break;
        case 3:
            if (task->substate == 0) {
                if (children->zoomBoxes[2]->opened != 0) {
                    task->setState(task, TASK_RUN);
                    children->frame->setState(children->frame, TASK_RUN);
                    children->windows[0]->setVisible(children->windows[0], 1);
                    children->windows[1]->setVisible(children->windows[1], 1);
                }
            } else if (task->substate == 1) {
                if (children->zoomBoxes[2] == NULL) {
                    task->setState(task, TASK_KILL);
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

TalkBox *createTalkBox(s32 id, s16 x, s16 y, s32 file, s32 index, u32 type) {
    TextTools fn;
    char name[0x20];
    TalkBox *task;
    TalkBoxChildren *children;
    s32 end;
    u8 *text;
    s32 w;
    s32 i;

    task = createTask((void (*)(void *))updateTalkBox, 0x6C, 0x18);
    task->layerId = id;
    task->x = x;
    task->y = y;
    children = task->children;
    task->setPos = talkBoxSetPos;
    task->type = type;
    initTextTools(&fn);
    i = 0;
    children->windows[0] = createTextWindow(task->layerId, 2, task->x + TALK_BOX_LAYOUTS[type].nameX, task->y + TALK_BOX_LAYOUTS[type].nameY);
    children->windows[0]->setLines(children->windows[0], 3);
    children->windows[1] = createTextWindow(task->layerId, 1, task->x + TALK_BOX_LAYOUTS[type].textX, task->y + TALK_BOX_LAYOUTS[type].textY);
    children->windows[1]->setLines(children->windows[1], 3);
    task->strings = file;
    text = (u8 *)fn.getString(file, index);
    if (text[0] == 2 && text[1] == 7) {
        end = 2;
        while (text[end] != 2 && text[end + 1] != 7) {
            end++;
        }
        HEAP.zero(name, sizeof(name));
        if (text[i + 2] == 2 && text[i + 3] == 9) {
            strcpy(name, PLAYER_NAME);
        } else {
            strncpy(name, &text[i + 2], -2 - i + end);
        }
        children->windows[0]->setString(children->windows[0], name, -1);
        children->windows[1]->setString(children->windows[1], &text[end + 2], -1);
    } else {
        children->windows[1]->setString(children->windows[1], text, -1);
    }
    children->windows[1]->setTypeDelay(children->windows[1], 6);
    children->windows[1]->insertPlayerName(children->windows[1]);
    w = fn.measure(children->windows[1]->text, children->windows[1]->style, 0);
    if (w < 0x5F) {
        w = 0x5F;
    } else if (w >= 0x8C) {
        w = 0x8B;
    }
    task->w = w;
    task->h = 0x3E;
    if (type < 2) {
        children->windows[0]->setPos(children->windows[0], children->windows[0]->x - task->w, children->windows[0]->y);
        children->windows[1]->setPos(children->windows[1], children->windows[1]->x - task->w, children->windows[1]->y);
    }
    for (i = 0; i < 2; i++) {
        children->windows[i]->setPalette(children->windows[i], 2);
        children->windows[i]->setVisible(children->windows[i], 0);
    }
    children->frame = createTalkBoxFrame(task);
    return task;
}

void loadFont(void) {
    TimLoader obj;

    initTimLoader(&obj);
    obj.setImagePos(0x140, 0);
    obj.loadArchive(FILE_CACHE.getEntry(FILE_FONT << 16));
    FILE_CACHE.free(FILE_FONT);
    FILE_CACHE.request(FILE_MENU_SPRITES);
}


s16 decodeChar(u8 *s, u8 mode, TextStyle *font) {
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
            map = font->sjisMap;
            for (i = 4; map[i].code != 0xFFFF; i++) {
                if (code == map[i].code) {
                    return map[i].index;
                }
            }
        } else {
            map = font->iconMap;
            for (i = 0; map[i].code != 0xFFFF; i++) {
                if (code == map[i].code) {
                    return map[i].index | 0x100;
                }
            }
        }
    } else {
        if (s[0] == 1) {
            if (s[1] > font->iconCount) {
                return (((u16)font->iconCount + 1) & 0xFF) | 0x100;
            }
            return (s[0] << 8) | s[1];
        }
        if (s[0] < 4) {
            return (s[0] << 8) | s[1];
        }
        if (s[0] < font->glyphCount) {
            return s[0];
        }
    }
    return 0x300;
}

INCLUDE_RODATA("main/nonmatchings/text_window", OUTLINE_ORDER);

INCLUDE_RODATA("main/nonmatchings/text_window", ZOOM_BOX_DELAYS);
