/* The fourth object of FIELDSTG.PRO (see fieldstg.c): its rodata starts at
   0x800825CC (USA). */

#include "fieldstg.h"

/* Stretches a box toward from-to along one axis. The match depends on each
   case having its own variables. */
void func_80086E64(Unk800870D4 *task, Unk800870D4Box *box) {
    switch (box->stretch) {
    case 1: {
        s32 start = box->pos.vx;
        s32 end = start + box->size.vx;
        s32 from = box->from;
        s32 to = box->to;
        s32 speed = box->speed;

        if (start < from) {
            start += speed;
            if (start > from) {
                start = from;
            }
        } else if (start > from) {
            start -= speed;
            if (start < from) {
                start = from;
            }
        }
        if (end < to) {
            end += speed;
            if (end > to) {
                end = to;
            }
        } else if (end > to) {
            end -= speed;
            if (end < to) {
                end = to;
            }
        }
        box->pos.vx = start;
        box->size.vx = end - start;
        if (start == from && end == to) {
            box->stretch = 0;
        }
        break;
    }
    case 2: {
        s32 start = box->pos.vy;
        s32 end = start + box->size.vy;
        s32 from = box->from;
        s32 to = box->to;
        s32 speed = box->speed;

        if (start < from) {
            start += speed;
            if (start > from) {
                start = from;
            }
        } else if (start > from) {
            start -= speed;
            if (start < from) {
                start = from;
            }
        }
        if (end < to) {
            end += speed;
            if (end > to) {
                end = to;
            }
        } else if (end > to) {
            end -= speed;
            if (end < to) {
                end = to;
            }
        }
        box->pos.vy = start;
        box->size.vy = end - start;
        if (start == from && end == to) {
            box->stretch = 0;
        }
        break;
    }
    }
}

void func_80086FB4(Unk800870D4 *task, u_long *ot, DVECTOR pos, DVECTOR size, s32 color) {
    POLY_F4 *poly = GFX.funcs.getPrim();

    setlen(poly, 5);
    *(s32 *)&poly->r0 = color;
    poly->code = 0x28;
    poly->x0 = pos.vx;
    poly->x1 = pos.vx + size.vx;
    poly->x2 = pos.vx;
    poly->x3 = pos.vx + size.vx;
    poly->y0 = pos.vy;
    poly->y1 = pos.vy;
    poly->y2 = pos.vy + size.vy;
    poly->y3 = pos.vy + size.vy;
    addPrim(ot, poly);
    GFX.funcs.setPrim(poly + 1);
}

/*
 * The area name banner: on state 0 it copies its ten boxes from D_800967B8
 * and opens the area and place windows (func_80086D20); on state 1 the boxes
 * appear and stretch in turn until both windows have finished; on state 2
 * it closes the layer's clip from the top and the bottom.
 */
void func_800870D4(Unk800870D4 *task, AreaNameWindows *windows) {
    Layer *layer;
    u_long *ot;
    s32 i;

    switch (task->state) {
    default:
    case 0:
        if (task->key1 != 0) {
            s32 j;

            for (j = 0; j < 10; j++) {
                task->boxes[j] = D_800967B8[j];
            }
            func_80086D20((Task *)task, windows);
            task->nextState(task);
        } else {
            task->setState(task, 2);
        }
        break;
    case 1:
        switch (task->substate) {
        default:
        case 0:
            task->boxes[0].visible = 1;
            task->boxes[5].visible = 1;
            if (task->boxes[5].stretch != 0) {
                break;
            }
            task->nextSubstate(task);
        case 1:
            task->boxes[8].visible = 1;
            task->boxes[9].visible = 1;
            task->boxes[6].visible = 1;
            task->boxes[1].visible = 1;
            task->boxes[2].visible = 1;
            task->boxes[7].visible = 1;
            task->boxes[3].visible = 1;
            if (task->boxes[9].stretch != 0) {
                break;
            }
            task->nextSubstate(task);
        case 2:
            task->nextSubstate(task);
        case 3:
            task->boxes[4].visible = 1;
            if (task->boxes[4].stretch == 0) {
                task->nextSubstate(task);
            }
            break;
        case 4:
            if (windows->area->isFinished(windows->area) && windows->place->isFinished(windows->place)) {
                task->setState(task, 2);
            }
            break;
        }
        break;
    case 2:
        layer = GFX.funcs.getLayer(0x1003);
        /* the match depends on the empty case 0 */
        switch (task->substate) {
        case 0:
            break;
        case 1:
            task->step += GFX.funcs.getFrameTime();
            if (task->step < 60) {
                break;
            }
            task->nextSubstate(task);
        case 2:
            task->clip.w = 320;
            task->clip.x = 0;
            task->clip.y = 0;
            task->clip.h = 240;
            task->nextSubstate(task);
        case 3:
            task->clip.y += 8;
            task->clip.h -= 16;
            layer->setClipPos(layer, task->clip.x, task->clip.y);
            layer->setClipSize(layer, task->clip.w, task->clip.h);
            if (task->clip.h == 0) {
                task->setState(task, 3);
            }
            break;
        }
        break;
    case 3:
        D_800990B4.unk54 = 0;
        break;
    }
    if (task->state >= 1 && task->state <= 2 && task->key1 != 0) {
        Layer *top = GFX_FUNCS.getLayer(0x1003);

        ot = (u_long *)top->getOtEntry(top, 1);
        for (i = 0; i < 10; i++) {
            if (task->boxes[i].visible) {
                func_80086E64(task, &task->boxes[i]);
                func_80086FB4(task, ot, task->boxes[i].pos, task->boxes[i].size, task->boxes[i].color);
            }
        }
    }
}

Task *func_800874C8(s32 arg0) {
    Task *task = createTaskWithId(func_800870D4, sizeof(Unk800870D4), 8, 9);

    task->key1 = arg0;
    D_800990B4.unk54 = 1;
    return task;
}

s32 func_80087510(Unk800876E4 *task) {
    task->time -= GFX_FUNCS.getFrameTime();
    if (task->time < 0) {
        task->frame += 2;
        if (D_80096920[task->key2][task->frame] == 0xFF) {
            task->frame = 0;
        }
        task->time = D_80096920[task->key2][task->frame + 1];
    }
    return D_80096920[task->key2][task->frame];
}

void func_800875DC(Unk800876E4 *task) {
    SpriteDrawer sprite;
    Point pos;
    s32 frame;

    pos.x = task->actor->tile.x;
    pos.y = task->actor->tile.y - (task->actor->unk64 >> 8);
    initSpriteDrawer(&sprite);
    sprite.setLayerId(0x1002, 1);
    sprite.setTexture(0x200, 0x100);
    if (task->substate == 2) {
        frame = func_80087510(task);
        sprite.draw(FILE_CACHE_GET_ENTRY[0](FIELD_SPRITES_FILE << 16), frame, pos.x, pos.y - 0x1B);
    }
    sprite.draw(FILE_CACHE_GET_ENTRY[0](FIELD_SPRITES_FILE << 16), task->unk60 >> 2, pos.x, pos.y - 0x1B);
}

void func_800876E4(Unk800876E4 *task) {
    switch (task->state) {
        default:
        case 0:
            if (task->actor == NULL) {
                task->actor = TASK_FUNCS.find(5, -1, 0);
                if (task->actor == NULL) {
                    break;
                }
            }
            if (task->key1 == 0) {
                task->unk54 = 0xC8;
                task->unk58 = 0xD4;
                task->unk5C = 0xDC;
            } else {
                task->unk54 = 0x104;
                task->unk58 = 0x10C;
                task->unk5C = 0x114;
            }
            if (task->key2 != 1) {
                SOUND.playSound(0x40007);
            }
            task->nextState(task);
            /* fallthrough */
        case 1:
            if (D_800990B4.unk50 != 0) {
                break;
            }
            switch (task->substate) {
                default:
                case 0:
                    task->unk60 = task->unk54;
                    task->nextSubstate(task);
                    /* fallthrough */
                case 1:
                    task->unk60 += GFX_FUNCS.getFrameTime();
                    if (task->unk60 >= task->unk58) {
                        task->unk60 = task->unk58;
                        task->nextSubstate(task);
                    }
                    break;
                case 2:
                    break;
            }
            func_800875DC(task);
            break;
        case 2:
            task->unk60 += GFX_FUNCS.getFrameTime();
            if (task->unk60 >= task->unk5C) {
                task->unk60 = task->unk5C;
                task->setState(task, 3);
            }
            func_800875DC(task);
            break;
        case 3:
            break;
    }
}

Unk800876E4 *func_800878A4(s32 arg0, s32 arg1, s32 arg2) {
    Unk800876E4 *task = createTaskWithId(func_800876E4, sizeof(Unk800876E4), 0, arg2);
    task->key1 = arg0;
    task->key2 = arg1;
    return task;
}

void func_800878F0(s32 arg0) {
    func_800878A4(0, 0, arg0);
}

void func_80087918(Unk800876E4 *task, s32 command, s32 id) {
    if (task != NULL) {
        switch (command) {
        case 0x325:
            task->key2 = 0;
            break;
        case 0x327:
            task->key2 = 1;
            break;
        case 0x326:
            task->setState(task, 2);
            break;
        }
        if (command == 0x325 || command == 0x327) {
            task->actor = TASK_FUNCS.find(5, id, -1);
        }
    }
}
