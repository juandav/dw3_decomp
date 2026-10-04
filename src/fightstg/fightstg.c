/* The first object of FIGHTSTG.PRO, the models and their meshes, and the
   overlay's data. FIGHTSTG.PRO was seven objects: each one's jump tables are
   aligned to 8 from the start of its own rodata, and they are 4 bytes past a
   multiple of 8 from 0x80082464 (USA) to 0x80082480, from 0x800825B4 to
   0x800825D0 and from 0x8008267C on. Where each object's code starts is
   only known to be between the function with the last jump table of the
   object before and the one with its first; the data is all here, and the
   last object (fightstg_7.c) differs between the versions. */

#include "fightstg.h"
#include "gte.h"

void func_80082A50(Model *model, ModelBone *bone) {
    s32 i;
    s32 archive;
    SVECTOR *key;
    SVECTOR *out;
    SVECTOR cur;
    SVECTOR prev;
    SVECTOR diff;
    SVECTOR step;

    archive = FILE_CACHE.getEntry(bone->unk8);
    for (i = 0; i < 9; i += 3) {
        key = (SVECTOR *)FILE_CACHE.getArchiveEntry(i / 3, archive);
        switch (i) {
        case 3:
            out = &bone->rot;
            break;
        case 6:
            out = &bone->scale;
            break;
        case 0:
        default:
            out = &bone->pos;
            break;
        }
        for (; key->pad < model->unk84; key++) {
        }
        cur = *key;
        switch (i) {
        case 0:
        default:
            prev = bone->prevPos;
            break;
        case 3:
            prev = bone->prevRot;
            break;
        case 6:
            prev = bone->prevScale;
            break;
        }
        if (i == 6 && (prev.vx == 0 || prev.vy == 0 || prev.vz == 0 || cur.vx == 0 || cur.vy == 0 || cur.vz == 0)) {
            *out = cur;
            return;
        }
        gte_lddp(model->unk98);
        diff.vx = cur.vx - prev.vx;
        diff.vy = cur.vy - prev.vy;
        diff.vz = cur.vz - prev.vz;
        gte_ldsv(&diff);
        gte_gpf12();
        *out = prev;
        gte_stsv(&step);
        out->vx += step.vx;
        out->vy += step.vy;
        out->vz += step.vz;
    }
}

void func_80082D74(Model *model, ModelBone *bone, s32 frame) {
    s32 i;
    s32 archive;
    SVECTOR *key;
    SVECTOR *out;
    s32 found;
    s32 span;
    SVECTOR cur;
    SVECTOR prev;
    SVECTOR diff;
    SVECTOR step;

    archive = FILE_CACHE.getEntry(bone->unk8);
    for (i = 0; i < 9; i += 3) {
        key = (SVECTOR *)FILE_CACHE.getArchiveEntry(i / 3, archive);
        found = 0;
        switch (i) {
        case 3:
            out = &bone->rot;
            break;
        case 6:
            out = &bone->scale;
            break;
        case 0:
        default:
            out = &bone->pos;
            break;
        }
        for (;; key++) {
            if (key->pad == frame) {
                found = 1;
                break;
            }
            if (key->pad >= frame) {
                break;
            }
        }
        if (found) {
            *out = *key;
        } else {
            cur = key[0];
            prev = key[-1];
            span = cur.pad - prev.pad;
            gte_lddp(((frame - prev.pad) << 12) / span);
            diff.vx = cur.vx - prev.vx;
            diff.vy = cur.vy - prev.vy;
            diff.vz = cur.vz - prev.vz;
            gte_ldsv(&diff);
            gte_gpf12();
            *out = prev;
            gte_stsv(&step);
            out->vx += step.vx;
            out->vy += step.vy;
            out->vz += step.vz;
        }
    }
}

void func_80082FD4(Model *model, Mesh **children) {
    ModelBone *bone = model->bones;
    VECTOR moved;
    s32 i;

    /* vx and vy as one word */
    if (*(s32 *)&model->move != 0 || model->move.vz != 0) {
        gte_SetRotMatrix(&bone->local);
        gte_ldv0(&model->move);
        gte_rtv0();
        gte_stlvnl(&moved);
        model->bones->pos.vx += moved.vx;
        model->bones->pos.vy += moved.vy;
        model->bones->pos.vz += moved.vz;
        model->move.vz = 0;
        model->move.vy = 0;
        model->move.vx = 0;
    }
    bone = model->bones;
    if (model->unk94 == 0) {
        for (i = 1, bone++; i < model->boneCount; i++, bone++) {
            func_80082D74(model, bone, model->unk84);
        }
    } else {
        for (i = 1, bone++; i < model->boneCount; i++, bone++) {
            func_80082A50(model, bone);
        }
    }
}

void FIGHTSTG_saveBlendPose(Model *model) {
    ModelBone *bone = model->bones;
    s32 i;

    for (i = 0; i < model->boneCount; i++, bone++) {
        bone->prevPos = bone->pos;
        bone->prevRot = bone->rot;
        bone->prevScale = bone->scale;
    }
}

/* Model.setMotion: lays out the motion's keyframes */
void func_800831D4(Model *model, s32 motion, s32 restart) {
    MotionStep *step;
    s32 count;
    s32 n;
    s32 i;
    s32 to;
    s32 from;

    if (restart != 1 && model->motion == motion) {
        return;
    }
    model->motion = motion;
    model->keyframe = 1;
    model->motionDone = 0;
    model->unk9C = 0;
    step = (MotionStep *)FILE_CACHE.getArchiveEntry(motion - 1, FILE_CACHE.getEntry(model->motionFile));
    count = 0;
    while (step->index != 0x7FFF) {
        n = step->count;
        if (n == 0) {
            model->keyframes[count] = step->frame;
            model->unkD24[count] = step->unk6;
            count++;
            break;
        }
        if (step->unk6 == 0) {
            to = step[1].frame;
            if (to == -1) {
                to = model->unk88[model->control->idleMotion];
                model->unk9C = 1;
            }
            if (step->index != 0) {
                from = step[-1].unk6;
            } else {
                from = 0xFFFF;
            }
            for (i = 0; i < n; i++) {
                model->unk19A4[count] = from;
                model->unkD24[count] = to;
                model->keyframes[count] = (((i + 1) << 12) / (n + 1)) | 0x8000;
                count++;
            }
        } else {
            for (i = 0; i < n; i++) {
                model->keyframes[count] = step->frame + i;
                model->unkD24[count] = 0;
                count++;
            }
        }
        step++;
    }
    model->keyframeCount = count;
    model->keyframe = 1;
}

/* Steps a model's motion by the frames gone by, blending into a new pose
   where a keyframe has 0x8000, and starts the idle motion when it ends */
void func_800833B0(Model *model) {
    s32 key = model->keyframe;
    ModelBone *bone;
    s32 i;

    if (model->motionDone == 0) {
        if (model->keyframes[key] & 0x8000) {
            if (model->unk90 != model->unkD24[key]) {
                model->unk90 = model->unkD24[key];
                if (model->unk19A4[key] != 0xFFFF) {
                    bone = model->bones;
                    for (i = 1, bone++; i < model->boneCount; i++, bone++) {
                        func_80082D74(model, bone, model->unk19A4[key]);
                    }
                }
                FIGHTSTG_saveBlendPose(model);
            }
            model->unk84 = model->unkD24[key];
            model->unk98 = model->keyframes[key] & 0x7FFF;
            model->unk94 = 1;
        } else {
            model->unk90 = 0;
            model->unk84 = model->keyframes[key];
            model->unk94 = 0;
        }
        model->keyframe += D_800A31E8.frames;
        if (model->keyframe >= model->keyframeCount) {
            model->keyframe = model->keyframeCount - 1;
        }
        key = model->keyframe;
        switch (model->keyframes[key]) {
        case 0x8000:
            model->keyframe = model->unkD24[key];
            break;
        case 0xFFFF:
            model->motionDone = 1;
            model->control->motionDone = 1;
            break;
        }
    } else {
        model->unk90 = 0;
        model->unk94 = 0;
        if (model->unk60 != 0 && model->unk9C != 0) {
            model->control->motion = model->control->idleMotion + 1;
            func_800831D4(model, model->control->idleMotion + 1, 0);
        }
    }
}

void func_8008358C(Model *model, Mesh **children) {
    TimLoader loader;
    VECTOR scale;
    ModelBone *bone;
    s32 archive;
    s32 i;
    s32 j;
    ModelBone *drawn;
    s32 b;
    ModelBone *linked;
    s32 c;
    s32 d;

    switch (model->state) {
    case TASK_INIT:
    default:
        if (model->texFile != 0) {
            initTimLoader(&loader);
            loader.setImagePos(model->texPos.x, model->texPos.y);
            loader.loadArchive(FILE_CACHE_GET_ENTRY[0](model->texFile));
        }
        for (b = 0, linked = model->bones; b < model->boneCount; b++, linked++) {
            if (b != 0) {
                linked->parentMatrix = &model->bones[linked->parent].world;
            }
        }
        for (c = 0; c < model->boneCount; c++) {
            if (c != 0) {
                children[c + 1] = func_8008588C(FILE_CACHE.getEntry(model->bones[c].file), model->texPos);
            }
        }
        children[0] = (Mesh *)FIGHTSTG_createFace(model, model->control->fighter);
        model->motion = 1;
        if (model->unk60 != 0) {
            archive = FILE_CACHE.getEntry(model->motionFile);
            model->unk88[0] = ((s16 *)FILE_CACHE.getArchiveEntry(0, archive))[2];
            model->unk88[1] = ((s16 *)FILE_CACHE.getArchiveEntry(1, archive))[2];
        }
        func_800831D4(model, model->control->idleMotion + 1, 1);
        model->control->motion = model->control->idleMotion + 1;
        model->nextState(model);
        break;
    case TASK_RUN:
        if (model->control->restart != 0 || model->motion != model->control->motion) {
            model->control->restart = 0;
            func_800831D4(model, model->control->motion, 1);
            switch (model->control->motion) {
            case 1:
                model->control->idleMotion = 0;
                break;
            case 2:
                model->control->idleMotion = 1;
                break;
            }
        }
        if (model->boneCount == 0) {
            break;
        }
        func_800833B0(model);
        func_80082FD4(model, children);
        model->bones[0].pos.vx = model->control->pos.x;
        model->bones[0].pos.vy = model->control->pos.y;
        model->bones[0].pos.vz = model->control->pos.z;
        model->bones[0].rot.vx = model->control->rot.x;
        model->bones[0].rot.vy = model->control->rot.y;
        model->bones[0].rot.vz = model->control->rot.z;
        for (i = 0, bone = model->bones; i < model->boneCount; i++, bone++) {
            scale.vx = bone->scale.vx;
            scale.vy = bone->scale.vy;
            scale.vz = bone->scale.vz;
            if ((scale.vx | scale.vy | scale.vz) <= 48) {
                bone->visible = 0;
            } else {
                bone->visible = 1;
                RotMatrixZYX_gte(&bone->rot, &bone->local);
                ScaleMatrix(&bone->local, &scale);
                bone->local.t[0] = bone->pos.vx;
                bone->local.t[1] = bone->pos.vy;
                bone->local.t[2] = bone->pos.vz;
                gte_CompMatrix(bone->parentMatrix, &bone->local, &bone->world);
            }
        }
        for (j = 0; j < 2; j++) {
            if (model->control->unk34[j].enabled) {
                for (d = 0, drawn = model->bones; d < model->boneCount; d++, drawn++) {
                    if (d != 0 && drawn->visible) {
                        if (model->control->unk34[j].alt) {
                            children[d + 1]->drawAlt(children[d + 1], model->control->unk34[j].arg, &drawn->world);
                        } else {
                            children[d + 1]->draw(children[d + 1], model->control->unk34[j].arg, &drawn->world);
                        }
                    }
                }
            }
        }
        break;
    case TASK_DONE:
        break;
    case TASK_KILL:
        if (model->bones != NULL) {
            HEAP.free(model->bones);
        }
        break;
    }
}

void FIGHTSTG_setModelColor(Model *model, s32 mode, CVECTOR *color) {
    Mesh **children = model->children;
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        if (model->control->unk34[i].enabled) {
            for (j = 0; j < model->boneCount; j++) {
                if (j != 0) {
                    children[j + 1]->colorMode = mode;
                    if (color != NULL) {
                        children[j + 1]->color = *color;
                    }
                }
            }
        }
    }
}

/* Model.unk2630: whether bone's Mesh skips the bounds check (unk50), set
   when either of the control's unk34 is enabled and bone isn't 0. The match
   depends on the pointer to the bone's slot, which children[bone + 1]
   computes with the addu's operands the other way round. */
void func_80083C78(Model *model, s32 bone, s32 value) {
    Mesh **meshes = (Mesh **)model->children + bone;
    s32 i;

    for (i = 0; i < 2; i++) {
        if (model->control->unk34[i].enabled && bone != 0) {
            meshes[1]->unk50 = value;
        }
    }
}

s32 func_80083CD4(Model *model) {
    return model->motionDone;
}

Model *func_80083CE0(s32 file, s32 motionFile, Vec2 texPos, ModelControl *control, s32 arg5) {
    s32 high = file & 0xFFFF0000;
    s32 *entry = (s32 *)FILE_CACHE_GET_ENTRY[0](file);
    s32 count = entry[1] + 1;
    Model *model = createTaskWithId(func_8008358C, sizeof(Model), (entry[1] + 2) * 4, 0x11);
    s32 i;

    model->bones = HEAP.alloc(count * sizeof(ModelBone), 2);
    model->control = control;
    model->unk60 = arg5;
    model->texPos = texPos;
    model->texFile = *entry++;
    if (model->texFile != 0) {
        model->texFile |= high;
    }
    model->boneCount = count;
    model->bones[0].parent = 0;
    model->bones[0].file = 0;
    model->bones[0].unk8 = 0;
    model->bones[0].parentMatrix = &D_8004D3C8;
    model->bones[0].pos.vx = 0;
    model->bones[0].pos.vy = 0;
    model->bones[0].pos.vz = 0;
    model->bones[0].rot.vx = 0;
    model->bones[0].rot.vy = 0;
    model->bones[0].rot.vz = 0;
    model->bones[0].scale.vx = 0x1000;
    model->bones[0].scale.vy = 0x1000;
    model->bones[0].scale.vz = 0x1000;
    entry++;
    for (i = 1; i < count; i++) {
        model->bones[i].parent = *entry++;
        model->bones[i].file = *entry++ | high;
        model->bones[i].unk8 = *entry++ | high;
    }
    model->setMotion = func_800831D4;
    model->isMotionDone = func_80083CD4;
    model->setColor = FIGHTSTG_setModelColor;
    model->motionFile = motionFile;
    model->unk2630 = func_80083C78;
    return model;
}

Model *func_80083F10(s32 file, s32 motionFile, Vec2 texPos, ModelControl *control) {
    return func_80083CE0(file, motionFile, texPos, control, 1);
}

Model *func_80083F44(s32 file, s32 motionFile, Vec2 texPos, ModelControl *control) {
    return func_80083CE0(file, motionFile, texPos, control, 0);
}

void func_80083F74(Mesh *mesh) {
    ShortVec3 *normal = (ShortVec3 *)mesh->unk64;
    s32 count = normal->x;
    MATRIX light;
    CVECTOR *color;
    s32 i;

    normal++;
    if (count == 0) {
        return;
    }
    gte_CompMatrix(&D_80080A90, &mesh->matrix, &light);
    gte_SetLightMatrix(&light);
    if (mesh->colors == NULL) {
        mesh->colors = HEAP.alloc(count * 4, 2);
    }
    color = mesh->colors;
    gte_ldv0_unaligned(normal);
    gte_ncs();
    gte_strgb(color);
    i = 1;
    normal++;
    while (i < count) {
        gte_ldv0_unaligned(normal);
        gte_ncs();
        normal++;
        color++;
        i++;
        gte_strgb(color);
    }
}

void func_800841D4(Mesh *mesh, Layer *layer) {
    ShortVec3 *vertex = (ShortVec3 *)mesh->unk60;
    s32 shift = 14 - layer->getOtShift(layer);
    s32 count = vertex->x;
    s32 *screen;
    s32 *depth;
    s32 i;
    s32 z;

    vertex++;
    if (mesh->screen == NULL) {
        mesh->screen = HEAP.alloc(count * 4, 2);
    }
    screen = mesh->screen;
    if (mesh->depth == NULL) {
        mesh->depth = HEAP.alloc(count * 4, 2);
    }
    depth = mesh->depth;
    gte_ldv0_unaligned(vertex);
    gte_rtps();
    gte_stsxy(screen);
    gte_stszotz(&z);
    i = 1;
    vertex++;
    while (i < count) {
        gte_ldv0_unaligned(vertex);
        gte_rtps();
        vertex++;
        screen++;
        i++;
        *depth++ = z >> shift;
        gte_stsxy(screen);
        gte_stszotz(&z);
    }
    *depth = z >> shift;
}

/* Adds the polygon in state as a gouraud-shaded textured triangle or quad;
   the colors, points and UVs are copied a word or a halfword at a time. */
void func_80084340(MeshDrawState *state) {
    *(CVECTOR *)&state->prim.gt4->r0 = state->colors[0];
    *(CVECTOR *)&state->prim.gt4->r1 = state->colors[1];
    *(CVECTOR *)&state->prim.gt4->r2 = state->colors[2];
    if (state->quad) {
        *(CVECTOR *)&state->prim.gt4->r3 = state->colors[3];
    }
    *(s32 *)&state->prim.gt4->x0 = state->sxy[0];
    *(s32 *)&state->prim.gt4->x1 = state->sxy[1];
    *(s32 *)&state->prim.gt4->x2 = state->sxy[2];
    *(u16 *)&state->prim.gt4->u0 = *(u16 *)state->uv[0];
    *(u16 *)&state->prim.gt4->u1 = *(u16 *)state->uv[1];
    *(u16 *)&state->prim.gt4->u2 = *(u16 *)state->uv[2];
    state->prim.gt4->clut = state->clut;
    state->prim.gt4->tpage = state->tpage;
    if (state->quad) {
        setPolyGT4(state->prim.gt4);
        if (state->abr) {
            setSemiTrans(state->prim.gt4, 1);
        }
        *(s32 *)&state->prim.gt4->x3 = state->sxy[3];
        *(u16 *)&state->prim.gt4->u3 = *(u16 *)state->uv[3];
        addPrim(state->ot, state->prim.gt4);
        state->prim.gt4++;
    } else {
        setPolyGT3(state->prim.gt3);
        if (state->abr) {
            setSemiTrans(state->prim.gt3, 1);
        }
        addPrim(state->ot, state->prim.gt3);
        state->prim.gt3++;
    }
}

/* The same as a flat-shaded textured triangle or quad */
void func_8008458C(MeshDrawState *state) {
    *(CVECTOR *)&state->prim.ft4->r0 = state->colors[0];
    *(s32 *)&state->prim.ft4->x0 = state->sxy[0];
    *(s32 *)&state->prim.ft4->x1 = state->sxy[1];
    *(s32 *)&state->prim.ft4->x2 = state->sxy[2];
    *(u16 *)&state->prim.ft4->u0 = *(u16 *)state->uv[0];
    *(u16 *)&state->prim.ft4->u1 = *(u16 *)state->uv[1];
    *(u16 *)&state->prim.ft4->u2 = *(u16 *)state->uv[2];
    state->prim.ft4->clut = state->clut;
    state->prim.ft4->tpage = state->tpage;
    if (state->quad) {
        setPolyFT4(state->prim.ft4);
        if (state->abr) {
            setSemiTrans(state->prim.ft4, 1);
        }
        *(s32 *)&state->prim.ft4->x3 = state->sxy[3];
        *(u16 *)&state->prim.ft4->u3 = *(u16 *)state->uv[3];
        addPrim(state->ot, state->prim.ft4);
        state->prim.ft4++;
    } else {
        setPolyFT3(state->prim.ft3);
        if (state->abr) {
            setSemiTrans(state->prim.ft3, 1);
        }
        addPrim(state->ot, state->prim.ft3);
        state->prim.ft3++;
    }
}

/* Whether a Mesh may be on screen: the screen positions of the 9 points of
   its bounds (unk6C) against the layer's clip, 64 pixels bigger each way;
   unk50 skips the check. The match depends on the + 128s kept in w and h,
   which gcc otherwise folds into the - 64s. */
s32 func_80084780(Mesh *mesh, Layer *layer) {
    ShortVec3 *corner;
    s32 left;
    s32 right;
    s32 top;
    s32 bottom;
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    s32 i;
    DVECTOR screen;
    s32 flag;

    if (mesh->unk50 != 0) {
        return 1;
    }
    corner = (ShortVec3 *)mesh->unk6C;
    left = 0;
    right = 0;
    top = 0;
    bottom = 0;
    for (i = 0; i < 9; ) {
        gte_ldv0_unaligned(corner);
        gte_rtps();
        if (i == 0) {
            x = layer->env.clip.x - 64;
            left = x - layer->offsetX;
            w = layer->env.clip.w + 128;
            right = x + w - layer->offsetX;
            y = layer->env.clip.y - 64;
            top = y - layer->offsetY;
            h = layer->env.clip.h + 128;
            bottom = y + h - layer->offsetY;
        }
        i++;
        corner++;
        gte_stsxy(&screen);
        gte_stflg(&flag);
        if (screen.vx >= left && screen.vx <= right && screen.vy >= top && screen.vy <= bottom) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("fightstg/nonmatchings/fightstg", func_80084890);

/* A primitive tag's word with its address replaced: the top byte of tag and
   the low 24 bits of addr. The match depends on word being set twice: as one
   expression, sched1 moves the tag's mask after the address's, which swaps
   their registers. */
static inline u_long linkTag(u_long tag, u_long addr) {
    u_long word = tag & 0xFF000000;
    word |= addr;
    return word;
}

/* Draws a Mesh as wireframe: each polygon of its command runs as a green
   LINE_F4 through its screen points, with a LINE_F2 to close a quad. Each
   addPrim is written out with linkTag. */
void func_800850D8(Mesh *mesh, Layer *layer) {
    MATRIX m;
    MeshDrawState state;
    u32 op;
    s32 hi;
    s32 lo;
    s32 i0, i1, i2, i3;
    s32 n;
    u_long tag;

    gte_CompMatrix(&D_80080AF0, &mesh->matrix, &m);
    gte_SetRotMatrix(&m);
    gte_SetTransMatrix(&m);
    if (func_80084780(mesh, layer) == 0) {
        return;
    }
    func_800841D4(mesh, layer);
    state.cmd = mesh->unk68;
    state.texPos = mesh->texPos;
    state.screen = mesh->screen;
    state.depth = mesh->depth;
    state.normalColors = mesh->colors;
    state.otBase = layer->getOt(layer);
    state.ot = state.otBase;
    state.prim.ptr = GFX_FUNCS.getPrim();
    while (*state.cmd != 0xFF) {
        op = *state.cmd;
        hi = op >> 4;
        lo = op & 0xF;
        if (hi != 0) {
            switch (hi) {
            case 8:
                state.quad = lo;
                break;
            case 9:
                state.textured = lo;
                break;
            case 12:
                state.lit = lo;
                break;
            }
            state.cmd++;
        } else {
            switch (lo) {
            case 1:
                state.cmd += 7;
                break;
            case 2:
            case 3:
            case 4:
            case 5:
                state.cmd += 4;
                break;
            case 0:
                do {
                    state.cmd++;
                    i0 = state.cmd[0];
                    i1 = state.cmd[1];
                    i2 = state.cmd[2];
                    i3 = 0;
                    if (state.quad) {
                        i3 = state.cmd[3];
                    }
                    state.sxy[0] = state.screen[i0];
                    state.sxy[1] = state.screen[i1];
                    state.sxy[2] = state.screen[i2];
                    if (state.quad) {
                        state.sxy[3] = state.screen[i3];
                    }
                    setLineF4(state.prim.lineF4);
                    setRGB0(state.prim.lineF4, 0, 0xFF, 0);
                    *(s32 *)&state.prim.lineF4->x0 = state.sxy[0];
                    *(s32 *)&state.prim.lineF4->x1 = state.sxy[1];
                    if (!state.quad) {
                        *(s32 *)&state.prim.lineF4->x2 = state.sxy[2];
                        *(s32 *)&state.prim.lineF4->x3 = state.sxy[0];
                    } else {
                        *(s32 *)&state.prim.lineF4->x2 = state.sxy[3];
                        *(s32 *)&state.prim.lineF4->x3 = state.sxy[2];
                    }
                    tag = *(u_long *)state.prim.ptr;
                    *(u_long *)state.prim.ptr = linkTag(tag, getaddr(state.ot));
                    tag = *state.ot;
                    *state.ot = linkTag(tag, (u_long)state.prim.ptr & 0xFFFFFF);
                    state.prim.lineF4++;
                    if (state.quad) {
                        setLineF2(state.prim.lineF2);
                        setRGB0(state.prim.lineF2, 0, 0xFF, 0);
                        *(s32 *)&state.prim.lineF2->x0 = state.sxy[2];
                        *(s32 *)&state.prim.lineF2->x1 = state.sxy[0];
                        tag = *(u_long *)state.prim.ptr;
                        *(u_long *)state.prim.ptr = linkTag(tag, getaddr(state.ot));
                        tag = *state.ot;
                        *state.ot = linkTag(tag, (u_long)state.prim.ptr & 0xFFFFFF);
                        state.prim.lineF2++;
                    }
                    n = state.quad + 3;
                    state.cmd += n;
                    if (state.lit) {
                        state.cmd += n;
                    }
                    if (state.textured) {
                        state.cmd += n * 2;
                    }
                } while (*state.cmd == 0);
                break;
            }
        }
    }
    GFX_FUNCS.setPrim(state.prim.ptr);
}

void func_800856BC(Mesh *mesh, s32 layerId, MATRIX *matrix) {
    Layer *layer = GFX_FUNCS.getLayer(layerId);

    layer->addCallback(layer, func_80084890, mesh);
    mesh->matrix = *matrix;
}

void func_80085754(Mesh *mesh, s32 layerId, MATRIX *matrix) {
    Layer *layer = GFX_FUNCS.getLayer(layerId);

    layer->addCallback(layer, func_800850D8, mesh);
    mesh->matrix = *matrix;
}

void func_800857EC(Mesh *mesh) {
    switch (mesh->state) {
    case TASK_INIT:
    case TASK_RUN:
    case TASK_DONE:
        break;
    case TASK_KILL:
        if (mesh->screen != NULL) {
            HEAP.free(mesh->screen);
        }
        if (mesh->depth != NULL) {
            HEAP.free(mesh->depth);
        }
        if (mesh->colors != NULL) {
            HEAP.free(mesh->colors);
        }
        break;
    }
}

Mesh *func_8008588C(s32 archive, Vec2 texPos) {
    Mesh *mesh = createTask(func_800857EC, sizeof(Mesh), 0);

    mesh->archive = archive;
    mesh->unk60 = FILE_CACHE.getArchiveEntry(0, archive);
    mesh->unk64 = FILE_CACHE.getArchiveEntry(1, archive);
    mesh->unk68 = FILE_CACHE.getArchiveEntry(2, archive);
    mesh->unk6C = FILE_CACHE.getArchiveEntry(5, archive);
    mesh->texPos = texPos;
    mesh->draw = func_800856BC;
    mesh->drawAlt = func_80085754;
    return mesh;
}

s32 func_8009AEA4();
void func_8009B430(u8 side, s32 fighter, s32 item);
void func_8009D204();
s32 func_8009D560();
s32 func_8009D648();
s32 func_8009DA88();
s32 func_8009DAA8();
FaceRect *FIGHTSTG_getFighterFace(s32 id);
s32 func_8009EA74();
s32 func_8009EBAC();
s32 func_8009EF04(s32 *args);
s32 func_8009F028();
s32 func_8009F1F0();
s32 func_8009F280(u8 side, s32 index, s32 big);
s32 func_8009F7A4();
s32 func_8009F9C0();
s32 func_8009FB10();
s32 func_8009FC90();
s32 func_8009FDF8();
s32 func_8009FF60();
s32 func_800A00A4();
s32 func_800A020C();
s32 func_800A0400();
s32 func_800A0494();
s32 func_800A052C();
s32 func_800A05DC();
s32 func_800A062C();
s32 func_800A067C();
#if VERSION_EU
s32 func_800A15A8();
#endif
s32 func_800A0830();
s32 func_800A0978();
s32 func_800A0A40(u8 side);
void func_800A0B10();
s32 func_800A0C80(s32 damage);
s32 func_800A0DA4();
void func_800A0EEC();
void FIGHTSTG_lerpVector();
s32 func_800A0FDC(s32 curve, s32 t, s32 value);

s32 D_800A1238[] = {
    0xA004E03C, 0xA004E0BD, 0xA004E13E, 0xA004E1BF,
    0xA004E240, 0xA004E2C1, 0xA004E342, 0xA004E3C3,
};
/* func_8008690C's shots: how long each lasts and the substate that makes it,
   in four lists that end with a time of -1 */
CameraShot D_800A1258[4][6] = {
    { { 1800, 1 }, { 480, 9 }, { 360, 3 }, { 300, 4 }, { 480, 9 }, { -1, 0 } },
    { { 360, 6 }, { 900, 1 }, { 300, 5 }, { 480, 9 }, { -1, 0 }, { 0, 0 } },
    { { 1920, 1 }, { 360, 6 }, { 180, 7 }, { 480, 9 }, { -1, 0 }, { 0, 0 } },
    { { 90, 10 }, { 90, 5 }, { -1, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
};
/* the lists that can follow each one */
u8 D_800A12B8[8][3] = {
    { 1, 2, 1 }, { 0, 2, 2 }, { 0, 1, 0 }, { 0, 1, 2 },
};
/* the fighters' models' texture places */
Vec2 D_800A12D0[] = {
    { 832, 0 }, { 896, 0 }, { 960, 0 }, { 960, 256 },
};
/* the European version's differ */
#if VERSION_US
EffectModelEntry D_800A12F0[] = {
    { 39, 0x7FE001A, 0x7FE0000 },
    { 65, 0x7600004, 0x7600000 },
    { 66, 0x8050004, 0x8050001 },
    { 85, 0x8290006, 0x8290000 },
    { 86, 0x82A0007, 0x82A0000 },
    { 87, 0x7C90016, 0x7C90000 },
    { 88, 0x76E0006, 0x76E0000 },
    { 89, 0x7EC0006, 0x7EC0000 },
    { 90, 0x7F8000A, 0x7F80000 },
    { 91, 0x7F90008, 0x7F90001 },
    { 92, 0x7FA0006, 0x7FA0000 },
    { 93, 0x74A001A, 0x74A0000 },
    { 94, 0x74C002C, 0x74C0000 },
    { 95, 0x763000A, 0x7630000 },
    { 96, 0x7D5001A, 0x7D50004 },
    { 97, 0x7F50003, 0x7F50000 },
    { 98, 0x7F70007, 0x7F70000 },
    { 99, 0x7FB0008, 0x7FB0001 },
    { 100, 0x7FC0005, 0x7FC0006 },
    { 101, 0x7ED0003, 0x7ED0001 },
    { 102, 0x7EE0006, 0x7EE0001 },
    { 103, 0x7EF0006, 0x7EF0001 },
    { 106, 0x7F0000E, 0x7F00002 },
    { 107, 0x7F1000A, 0x7F10001 },
    { 108, 0x7CA000C, 0x7CA0000 },
    { 109, 0x7CB001C, 0x7CB0005 },
    { 113, 0x7FD0005, 0x7FD0006 },
    { 114, 0x874000C, 0x8740002 },
    { 115, 0x87D0001, 0x87D0000 },
    { 116, 0x87E000A, 0x87E0000 },
    { 201, 0x80D0004, 0x80D0000 },
    { 202, 0x80E0004, 0x80E0000 },
    { 203, 0x80F0004, 0x80F0000 },
    { 204, 0x8100004, 0x8100000 },
    { 205, 0x8110004, 0x8110000 },
    { 206, 0x8120004, 0x8120000 },
    { 207, 0x8130004, 0x8130000 },
    { 208, 0x8140004, 0x8140000 },
    { 209, 0x8150004, 0x8150000 },
    { 210, 0x8160004, 0x8160000 },
    { 211, 0x8170004, 0x8170000 },
    { 212, 0x8180004, 0x8180000 },
    { 213, 0x8190004, 0x8190000 },
    { 214, 0x81A0004, 0x81A0000 },
    { 215, 0x81B0004, 0x81B0000 },
    { 216, 0x81C0004, 0x81C0000 },
    { 217, 0x81D0004, 0x81D0000 },
    { 218, 0x81E0004, 0x81E0000 },
    { 219, 0x81F0004, 0x81F0000 },
    { 220, 0x8200004, 0x8200000 },
    { 221, 0x7C00004, 0x7C00000 },
    { 222, 0x8210004, 0x8210000 },
    { 223, 0x8220004, 0x8220000 },
    { 224, 0x8230004, 0x8230000 },
    { 225, 0x8240004, 0x8240000 },
    { 226, 0x8250004, 0x8250000 },
    { 301, 0x82B000E, 0x82B0000 },
    { 302, 0x82D0015, 0x82D0016 },
    { 303, 0x82E0004, 0x82E0001 },
    { 306, 0x82F0004, 0x82F0000 },
    { 307, 0x8300006, 0x8300000 },
    { 308, 0x8310008, 0x8310000 },
    { 309, 0x8320004, 0x8320000 },
    { 310, 0x834000A, 0x8340000 },
    { 310, 0x834000A, 0x8340000 },
    { 311, 0x8350004, 0x8350000 },
    { 312, 0x8360004, 0x8360000 },
    { 313, 0x8370004, 0x8370000 },
    { 314, 0x8380004, 0x8380000 },
    { 315, 0x839000A, 0x8390000 },
    { 316, 0x83A0006, 0x83A0001 },
    { 317, 0x83B0001, 0x83B0000 },
    { 318, 0x83C0004, 0x83C0001 },
    { 319, 0x83D000A, 0x83D0006 },
    { 320, 0x83E000A, 0x83E0000 },
    { 321, 0x83F0004, 0x83F0000 },
    { 322, 0x8400004, 0x8400000 },
    { 323, 0x8410004, 0x8410000 },
    { 324, 0x8420004, 0x8420000 },
    { 325, 0x8430004, 0x8430000 },
    { 326, 0x8440006, 0x8440000 },
    { 327, 0x845000D, 0x845000E },
    { 328, 0x8460006, 0x8460000 },
    { 329, 0x8470006, 0x8470000 },
    { 330, 0x8480008, 0x8480000 },
    { 331, 0x8490008, 0x8490000 },
    { 332, 0x84A0008, 0x84A0000 },
    { 333, 0x84B000A, 0x84B0000 },
    { 334, 0x84C000A, 0x84C0000 },
    { 335, 0x84D0006, 0x84D0000 },
    { 336, 0x84E0005, 0x84E0006 },
    { 337, 0x84F000C, 0x84F0000 },
    { 338, 0x8500006, 0x8500000 },
    { 339, 0x8510007, 0x8510008 },
    { 340, 0x8520005, 0x8520006 },
    { 341, 0x853000C, 0x8530000 },
    { 342, 0x8540001, 0x8540000 },
    { 343, 0x8550001, 0x8550000 },
    { 344, 0x8560000, 0x8560008 },
    { 345, 0x8570000, 0x8570008 },
    { 346, 0x8580015, 0x8580016 },
    { 347, 0x8590004, 0x8590000 },
    { 348, 0x85A0001, 0x85A0000 },
    { 349, 0x85B000A, 0x85B0000 },
    { 350, 0x85C0019, 0x85C001A },
    { 351, 0x85D000A, 0x85D0000 },
    { 352, 0x85E0008, 0x85E0000 },
    { 353, 0x85F0008, 0x85F0000 },
    { 354, 0x8600009, 0x860000A },
    { 355, 0x8610001, 0x8610000 },
    { 356, 0x8620008, 0x8620000 },
    { 357, 0x8630001, 0x8630000 },
    { 358, 0x864000A, 0x8640000 },
    { 359, 0x8650008, 0x8650000 },
    { 360, 0x866000C, 0x8660002 },
    { 361, 0x8670011, 0x8670012 },
    { 362, 0x868000C, 0x8680000 },
    { 363, 0x8690011, 0x8690012 },
    { 364, 0x86A0031, 0x86A0032 },
    { 365, 0x86B001A, 0x86B0000 },
    { 366, 0x86C0006, 0x86C0000 },
    { 367, 0x86D0006, 0x86D0000 },
    { 368, 0x86E0004, 0x86E0001 },
    { 369, 0x86F0001, 0x86F0000 },
    { 370, 0x8700012, 0x8700000 },
    { 371, 0x8710008, 0x8710000 },
    { 372, 0x872000A, 0x8720000 },
    { 374, 0x8730012, 0x8730000 },
    { 375, 0x833000E, 0x8330003 },
    { 376, 0x8900012, 0x890000C },
    { 0, 0, 0 },
};
#elif VERSION_EU
EffectModelEntry D_800A12F0[] = {
    { 39, 0x80D001A, 0x80D0000 },
    { 65, 0x76F0004, 0x76F0000 },
    { 66, 0x8140004, 0x8140001 },
    { 85, 0x83A0006, 0x83A0000 },
    { 86, 0x83B0007, 0x83B0000 },
    { 87, 0x7D80016, 0x7D80000 },
    { 88, 0x77D0006, 0x77D0000 },
    { 89, 0x7FB0006, 0x7FB0000 },
    { 90, 0x807000A, 0x8070000 },
    { 91, 0x8080008, 0x8080001 },
    { 92, 0x8090006, 0x8090000 },
    { 93, 0x75A001A, 0x75A0000 },
    { 94, 0x75C002C, 0x75C0000 },
    { 95, 0x772000A, 0x7720000 },
    { 96, 0x7E4001A, 0x7E40004 },
    { 97, 0x8040003, 0x8040000 },
    { 98, 0x8060007, 0x8060000 },
    { 99, 0x80A0008, 0x80A0001 },
    { 100, 0x80B0005, 0x80B0006 },
    { 101, 0x7FC0003, 0x7FC0001 },
    { 102, 0x7FD0006, 0x7FD0001 },
    { 103, 0x7FE0006, 0x7FE0001 },
    { 106, 0x7FF000E, 0x7FF0002 },
    { 107, 0x800000A, 0x8000001 },
    { 108, 0x7D9000C, 0x7D90000 },
    { 109, 0x7DA001C, 0x7DA0005 },
    { 113, 0x80C0005, 0x80C0006 },
    { 114, 0x885000C, 0x8850002 },
    { 115, 0x88E0001, 0x88E0000 },
    { 116, 0x88F000A, 0x88F0000 },
    { 201, 0x81E0004, 0x81E0000 },
    { 202, 0x81F0004, 0x81F0000 },
    { 203, 0x8200004, 0x8200000 },
    { 204, 0x8210004, 0x8210000 },
    { 205, 0x8220004, 0x8220000 },
    { 206, 0x8230004, 0x8230000 },
    { 207, 0x8240004, 0x8240000 },
    { 208, 0x8250004, 0x8250000 },
    { 209, 0x8260004, 0x8260000 },
    { 210, 0x8270004, 0x8270000 },
    { 211, 0x8280004, 0x8280000 },
    { 212, 0x8290004, 0x8290000 },
    { 213, 0x82A0004, 0x82A0000 },
    { 214, 0x82B0004, 0x82B0000 },
    { 215, 0x82C0004, 0x82C0000 },
    { 216, 0x82D0004, 0x82D0000 },
    { 217, 0x82E0004, 0x82E0000 },
    { 218, 0x82F0004, 0x82F0000 },
    { 219, 0x8300004, 0x8300000 },
    { 220, 0x8310004, 0x8310000 },
    { 221, 0x7CF0004, 0x7CF0000 },
    { 222, 0x8320004, 0x8320000 },
    { 223, 0x8330004, 0x8330000 },
    { 224, 0x8340004, 0x8340000 },
    { 225, 0x8350004, 0x8350000 },
    { 226, 0x8360004, 0x8360000 },
    { 301, 0x83C000E, 0x83C0000 },
    { 302, 0x83E0015, 0x83E0016 },
    { 303, 0x83F0004, 0x83F0001 },
    { 306, 0x8400004, 0x8400000 },
    { 307, 0x8410006, 0x8410000 },
    { 308, 0x8420008, 0x8420000 },
    { 309, 0x8430004, 0x8430000 },
    { 310, 0x845000A, 0x8450000 },
    { 310, 0x845000A, 0x8450000 },
    { 311, 0x8460004, 0x8460000 },
    { 312, 0x8470004, 0x8470000 },
    { 313, 0x8480004, 0x8480000 },
    { 314, 0x8490004, 0x8490000 },
    { 315, 0x84A000A, 0x84A0000 },
    { 316, 0x84B0006, 0x84B0001 },
    { 317, 0x84C0001, 0x84C0000 },
    { 318, 0x84D0004, 0x84D0001 },
    { 319, 0x84E000A, 0x84E0006 },
    { 320, 0x84F000A, 0x84F0000 },
    { 321, 0x8500004, 0x8500000 },
    { 322, 0x8510004, 0x8510000 },
    { 323, 0x8520004, 0x8520000 },
    { 324, 0x8530004, 0x8530000 },
    { 325, 0x8540004, 0x8540000 },
    { 326, 0x8550006, 0x8550000 },
    { 327, 0x856000D, 0x856000E },
    { 328, 0x8570006, 0x8570000 },
    { 329, 0x8580006, 0x8580000 },
    { 330, 0x8590008, 0x8590000 },
    { 331, 0x85A0008, 0x85A0000 },
    { 332, 0x85B0008, 0x85B0000 },
    { 333, 0x85C000A, 0x85C0000 },
    { 334, 0x85D000A, 0x85D0000 },
    { 335, 0x85E0006, 0x85E0000 },
    { 336, 0x85F0005, 0x85F0006 },
    { 337, 0x860000C, 0x8600000 },
    { 338, 0x8610006, 0x8610000 },
    { 339, 0x8620007, 0x8620008 },
    { 340, 0x8630005, 0x8630006 },
    { 341, 0x864000C, 0x8640000 },
    { 342, 0x8650001, 0x8650000 },
    { 343, 0x8660001, 0x8660000 },
    { 344, 0x8670000, 0x8670008 },
    { 345, 0x8680000, 0x8680008 },
    { 346, 0x8690015, 0x8690016 },
    { 347, 0x86A0004, 0x86A0000 },
    { 348, 0x86B0001, 0x86B0000 },
    { 349, 0x86C000A, 0x86C0000 },
    { 350, 0x86D0019, 0x86D001A },
    { 351, 0x86E000A, 0x86E0000 },
    { 352, 0x86F0008, 0x86F0000 },
    { 353, 0x8700008, 0x8700000 },
    { 354, 0x8710009, 0x871000A },
    { 355, 0x8720001, 0x8720000 },
    { 356, 0x8730008, 0x8730000 },
    { 357, 0x8740001, 0x8740000 },
    { 358, 0x875000A, 0x8750000 },
    { 359, 0x8760008, 0x8760000 },
    { 360, 0x877000C, 0x8770002 },
    { 361, 0x8780011, 0x8780012 },
    { 362, 0x879000C, 0x8790000 },
    { 363, 0x87A0011, 0x87A0012 },
    { 364, 0x87B0031, 0x87B0032 },
    { 365, 0x87C001A, 0x87C0000 },
    { 366, 0x87D0006, 0x87D0000 },
    { 367, 0x87E0006, 0x87E0000 },
    { 368, 0x87F0004, 0x87F0001 },
    { 369, 0x8800001, 0x8800000 },
    { 370, 0x8810012, 0x8810000 },
    { 371, 0x8820008, 0x8820000 },
    { 372, 0x883000A, 0x8830000 },
    { 374, 0x8840012, 0x8840000 },
    { 375, 0x844000E, 0x8440003 },
    { 376, 0x8A10012, 0x8A1000C },
    { 0, 0, 0 },
};
#endif
/* the European version's differ */
#if VERSION_US
EffectSheet D_800A1914[] = {
    { 0, 0x78E0026, { 320, 256 } },
    { 0, 0x7940000, { 448, 256 } },
    { 0, 0x7D10000, { 512, 256 } },
    { 0, 0x7D30000, { 576, 256 } },
    { 0, 0, { 576, 256 } },
    { 0x7E60006, 0x7E60000, { 768, 256 } },
    { 0x8910005, 0x8910000, { 768, 256 } },
    { 0x8000002, 0x8000000, { 896, 256 } },
    { 0x77C0002, 0x77C0000, { 896, 256 } },
    { 0x7FF0003, 0x7FF0000, { 896, 256 } },
    { 0x77A0003, 0x77A0000, { 896, 256 } },
    { 0x80B0002, 0x80B0001, { 896, 256 } },
    { 0x7D60003, 0x7D60000, { 896, 256 } },
    { 0x6CA0002, 0x6CA0000, { 896, 256 } },
    { 0x7D70003, 0x7D70000, { 896, 256 } },
    { 0x8020002, 0x8020000, { 896, 256 } },
    { 0x80C0002, 0x80C0001, { 896, 256 } },
    { 0x77D0002, 0x77D0000, { 896, 256 } },
    { 0x7CC0002, 0x7CC0000, { 896, 256 } },
    { 0x7D80002, 0x7D80000, { 896, 256 } },
    { 0x8030002, 0x8030000, { 896, 256 } },
    { 0x7960002, 0x7960000, { 896, 256 } },
    { 0x8080002, 0x8080000, { 896, 256 } },
    { 0x77E0003, 0x77E0000, { 896, 256 } },
    { 0x77F0005, 0x77F0000, { 896, 256 } },
    { 0x88C0002, 0x88C0000, { 896, 256 } },
    { 0x7800004, 0x7800000, { 896, 256 } },
    { 0x7CD0002, 0x7CD0000, { 896, 256 } },
    { 0x8040003, 0x8040000, { 896, 256 } },
    { 0x8070002, 0x8070000, { 896, 256 } },
    { 0x80A0002, 0x80A0000, { 896, 256 } },
    { 0x77B0003, 0x77B0000, { 896, 256 } },
    { 0x7640002, 0x7640000, { 896, 256 } },
    { 0x82C0002, 0x82C0000, { 896, 256 } },
    { 0x7D90003, 0x7D90000, { 896, 256 } },
    { 0x7CE0003, 0x7CE0000, { 896, 256 } },
    { 0x7CF0002, 0x7CF0000, { 896, 256 } },
    { 0x7DA0004, 0x7DA0000, { 896, 256 } },
    { 0x7F20002, 0x7F20000, { 896, 256 } },
    { 0x7D00002, 0x7D00000, { 896, 256 } },
    { 0x7F40002, 0x7F40000, { 896, 256 } },
    { 0x7810001, 0x7810000, { 896, 256 } },
    { 0x7F60002, 0x7F60000, { 896, 256 } },
    { 0x7F30003, 0x7F30000, { 896, 256 } },
    { 0x87F0002, 0x87F0000, { 896, 256 } },
    { 0x8780002, 0x8780000, { 896, 256 } },
    { 0x8790004, 0x8790000, { 896, 256 } },
    { 0x8770002, 0x8770000, { 896, 256 } },
    { 0x87A0004, 0x87A0000, { 896, 256 } },
    { 0x8010002, 0x8010000, { 896, 256 } },
    { 0x8090002, 0x8090000, { 896, 256 } },
};
#elif VERSION_EU
EffectSheet D_800A1914[] = {
    { 0, 0x79D0026, { 320, 256 } },
    { 0, 0x7A30000, { 448, 256 } },
    { 0, 0x7E00000, { 512, 256 } },
    { 0, 0x7E20000, { 576, 256 } },
    { 0, 0, { 576, 256 } },
    { 0x7F50006, 0x7F50000, { 768, 256 } },
    { 0x8A20005, 0x8A20000, { 768, 256 } },
    { 0x80F0002, 0x80F0000, { 896, 256 } },
    { 0x78B0002, 0x78B0000, { 896, 256 } },
    { 0x80E0003, 0x80E0000, { 896, 256 } },
    { 0x7890003, 0x7890000, { 896, 256 } },
    { 0x81C0002, 0x81C0001, { 896, 256 } },
    { 0x7E50003, 0x7E50000, { 896, 256 } },
    { 0x6D90002, 0x6D90000, { 896, 256 } },
    { 0x7E60003, 0x7E60000, { 896, 256 } },
    { 0x8110002, 0x8110000, { 896, 256 } },
    { 0x81D0002, 0x81D0001, { 896, 256 } },
    { 0x78C0002, 0x78C0000, { 896, 256 } },
    { 0x7DB0002, 0x7DB0000, { 896, 256 } },
    { 0x7E70002, 0x7E70000, { 896, 256 } },
    { 0x8120002, 0x8120000, { 896, 256 } },
    { 0x7A50002, 0x7A50000, { 896, 256 } },
    { 0x8190002, 0x8190000, { 896, 256 } },
    { 0x78D0003, 0x78D0000, { 896, 256 } },
    { 0x78E0005, 0x78E0000, { 896, 256 } },
    { 0x89D0002, 0x89D0000, { 896, 256 } },
    { 0x78F0004, 0x78F0000, { 896, 256 } },
    { 0x7DC0002, 0x7DC0000, { 896, 256 } },
    { 0x8130003, 0x8130000, { 896, 256 } },
    { 0x8180002, 0x8180000, { 896, 256 } },
    { 0x81B0002, 0x81B0000, { 896, 256 } },
    { 0x78A0003, 0x78A0000, { 896, 256 } },
    { 0x7730002, 0x7730000, { 896, 256 } },
    { 0x83D0002, 0x83D0000, { 896, 256 } },
    { 0x7E80003, 0x7E80000, { 896, 256 } },
    { 0x7DD0003, 0x7DD0000, { 896, 256 } },
    { 0x7DE0002, 0x7DE0000, { 896, 256 } },
    { 0x7E90004, 0x7E90000, { 896, 256 } },
    { 0x8010002, 0x8010000, { 896, 256 } },
    { 0x7DF0002, 0x7DF0000, { 896, 256 } },
    { 0x8030002, 0x8030000, { 896, 256 } },
    { 0x7900001, 0x7900000, { 896, 256 } },
    { 0x8050002, 0x8050000, { 896, 256 } },
    { 0x8020003, 0x8020000, { 896, 256 } },
    { 0x8900002, 0x8900000, { 896, 256 } },
    { 0x8890002, 0x8890000, { 896, 256 } },
    { 0x88A0004, 0x88A0000, { 896, 256 } },
    { 0x8880002, 0x8880000, { 896, 256 } },
    { 0x88B0004, 0x88B0000, { 896, 256 } },
    { 0x8100002, 0x8100000, { 896, 256 } },
    { 0x81A0002, 0x81A0000, { 896, 256 } },
};
#endif
/* the European version's differ */
#if VERSION_US
SpriteEffectEntry D_800A1C44[] = {
    { 0, 0, 0x78E0000 },
    { 1, 0, 0x78E0001 },
    { 2, 0, 0x78E0002 },
    { 19, 0, 0x78E0003 },
    { 20, 0, 0x78E0028 },
    { 21, 0, 0x78E0004 },
    { 22, 0, 0x78E0005 },
    { 23, 0, 0x78E0006 },
    { 24, 0, 0x78E0007 },
    { 25, 0, 0x78E0027 },
    { 26, 0, 0x78E0008 },
    { 27, 0, 0x78E0009 },
    { 28, 0, 0x78E000A },
    { 29, 0, 0x78E000B },
    { 31, 0, 0x78E000C },
    { 32, 0, 0x78E000D },
    { 42, 0, 0x78E0017 },
    { 43, 0, 0x78E0018 },
    { 44, 0, 0x78E0019 },
    { 45, 0, 0x78E001A },
    { 46, 0, 0x78E001B },
    { 47, 0, 0x78E001C },
    { 57, 0, 0x78E0024 },
    { 58, 0, 0x78E0025 },
    { 33, 0, 0x78E000E },
    { 34, 0, 0x78E000F },
    { 35, 0, 0x78E0010 },
    { 36, 0, 0x78E0011 },
    { 37, 0, 0x78E0012 },
    { 38, 0, 0x78E0013 },
    { 39, 0, 0x78E0014 },
    { 40, 0, 0x78E0015 },
    { 41, 0, 0x78E0016 },
    { 50, 0, 0x78E001D },
    { 51, 0, 0x78E001E },
    { 52, 0, 0x78E001F },
    { 53, 0, 0x78E0020 },
    { 54, 0, 0x78E0021 },
    { 55, 0, 0x78E0022 },
    { 56, 0, 0x78E0023 },
    { 13, 1, 0x7940001 },
    { 14, 1, 0x7940002 },
    { 15, 1, 0x7940003 },
    { 16, 1, 0x7940004 },
    { 17, 1, 0x7940005 },
    { 18, 1, 0x7940006 },
    { 64, 1, 0x7940008 },
    { 65, 1, 0x7940009 },
    { 3, 2, 0x7D10001 },
    { 4, 2, 0x7D10002 },
    { 5, 2, 0x7D10003 },
    { 6, 2, 0x7D10004 },
    { 7, 2, 0x7D10005 },
    { 8, 2, 0x7D10006 },
    { 9, 2, 0x7D10007 },
    { 10, 2, 0x7D10008 },
    { 11, 2, 0x7D10009 },
    { 12, 2, 0x7D1000A },
    { 63, 2, 0x7D1000B },
    { 62, 3, 0x7D3000B },
    { 1009, 3, 0x7D30009 },
    { 1012, 3, 0x7D30003 },
    { 1013, 3, 0x7D30004 },
    { 1014, 3, 0x7D30005 },
    { 1017, 3, 0x7D30008 },
    { 1020, 3, 0x7D3000A },
    { 1004, 5, 0x7E60001 },
    { 1005, 5, 0x7E60002 },
    { 1006, 5, 0x7E60003 },
    { 1000, 6, 0x8910001 },
    { 1001, 6, 0x8910002 },
    { 1002, 6, 0x8910003 },
    { 1003, 6, 0x8910004 },
    { 1007, 6, 0x8910006 },
    { 1008, 6, 0x8910007 },
    { 1010, 7, 0x8000001 },
    { 59, 9, 0x7FF0001 },
    { 60, 9, 0x7FF0002 },
    { 1018, 9, 0x7FF0006 },
    { 1019, 9, 0x7FF0007 },
    { 2040, 8, 0x77C0001 },
    { 2036, 10, 0x77A0001 },
    { 2037, 10, 0x77A0002 },
    { 2058, 11, 0x80B0000 },
    { 1021, 12, 0x7D60004 },
    { 2027, 12, 0x7D60001 },
    { 2028, 12, 0x7D60002 },
    { 2043, 13, 0x6CA0001 },
    { 2011, 14, 0x7D70001 },
    { 2012, 14, 0x7D70002 },
    { 1015, 15, 0x8020001 },
    { 2059, 15, 0x8020003 },
    { 2060, 16, 0x80C0000 },
    { 2056, 17, 0x77D0003 },
    { 2031, 17, 0x77D0001 },
    { 2014, 18, 0x7CC0001 },
    { 2026, 19, 0x7D80001 },
    { 1016, 20, 0x8030001 },
    { 2044, 21, 0x7960001 },
    { 1022, 22, 0x8080001 },
    { 2019, 23, 0x77E0001 },
    { 2020, 23, 0x77E0002 },
    { 2008, 24, 0x77F0002 },
    { 2009, 24, 0x77F0003 },
    { 2010, 24, 0x77F0004 },
    { 2062, 25, 0x88C0001 },
    { 2000, 26, 0x7800001 },
    { 2001, 26, 0x7800002 },
    { 2002, 26, 0x7800003 },
    { 2004, 27, 0x7CD0001 },
    { 2046, 28, 0x8040001 },
    { 2047, 28, 0x8040002 },
    { 2061, 29, 0x8070001 },
    { 2057, 30, 0x80A0001 },
    { 2029, 31, 0x77B0001 },
    { 2030, 31, 0x77B0002 },
    { 2032, 32, 0x7640001 },
    { 2007, 33, 0x82C0001 },
    { 2041, 34, 0x7D90001 },
    { 2042, 34, 0x7D90002 },
    { 2024, 35, 0x7CE0001 },
    { 2025, 35, 0x7CE0002 },
    { 2005, 36, 0x7CF0001 },
    { 2006, 36, 0x7CF0003 },
    { 2016, 37, 0x7DA0001 },
    { 2017, 37, 0x7DA0002 },
    { 2018, 37, 0x7DA0003 },
    { 2038, 38, 0x7F20003 },
    { 2039, 38, 0x7F20004 },
    { 2003, 39, 0x7D00001 },
    { 2015, 40, 0x7F40001 },
    { 2021, 41, 0x7810002 },
    { 2022, 41, 0x7810003 },
    { 2023, 41, 0x7810004 },
    { 2013, 42, 0x7F60001 },
    { 2033, 43, 0x7F30001 },
    { 2034, 43, 0x7F30002 },
    { 2035, 44, 0x87F0001 },
    { 2049, 45, 0x8780001 },
    { 2050, 46, 0x8790001 },
    { 2051, 46, 0x8790002 },
    { 2052, 46, 0x8790003 },
    { 2048, 47, 0x8770001 },
    { 2053, 48, 0x87A0001 },
    { 2054, 48, 0x87A0002 },
    { 2055, 48, 0x87A0003 },
    { 1011, 49, 0x8010001 },
    { 2045, 50, 0x8090001 },
    { -1, 0, 0 },
};
#elif VERSION_EU
SpriteEffectEntry D_800A1C44[] = {
    { 0, 0, 0x79D0000 },
    { 1, 0, 0x79D0001 },
    { 2, 0, 0x79D0002 },
    { 19, 0, 0x79D0003 },
    { 20, 0, 0x79D0028 },
    { 21, 0, 0x79D0004 },
    { 22, 0, 0x79D0005 },
    { 23, 0, 0x79D0006 },
    { 24, 0, 0x79D0007 },
    { 25, 0, 0x79D0027 },
    { 26, 0, 0x79D0008 },
    { 27, 0, 0x79D0009 },
    { 28, 0, 0x79D000A },
    { 29, 0, 0x79D000B },
    { 31, 0, 0x79D000C },
    { 32, 0, 0x79D000D },
    { 42, 0, 0x79D0017 },
    { 43, 0, 0x79D0018 },
    { 44, 0, 0x79D0019 },
    { 45, 0, 0x79D001A },
    { 46, 0, 0x79D001B },
    { 47, 0, 0x79D001C },
    { 57, 0, 0x79D0024 },
    { 58, 0, 0x79D0025 },
    { 33, 0, 0x79D000E },
    { 34, 0, 0x79D000F },
    { 35, 0, 0x79D0010 },
    { 36, 0, 0x79D0011 },
    { 37, 0, 0x79D0012 },
    { 38, 0, 0x79D0013 },
    { 39, 0, 0x79D0014 },
    { 40, 0, 0x79D0015 },
    { 41, 0, 0x79D0016 },
    { 50, 0, 0x79D001D },
    { 51, 0, 0x79D001E },
    { 52, 0, 0x79D001F },
    { 53, 0, 0x79D0020 },
    { 54, 0, 0x79D0021 },
    { 55, 0, 0x79D0022 },
    { 56, 0, 0x79D0023 },
    { 13, 1, 0x7A30001 },
    { 14, 1, 0x7A30002 },
    { 15, 1, 0x7A30003 },
    { 16, 1, 0x7A30004 },
    { 17, 1, 0x7A30005 },
    { 18, 1, 0x7A30006 },
    { 64, 1, 0x7A30008 },
    { 65, 1, 0x7A30009 },
    { 3, 2, 0x7E00001 },
    { 4, 2, 0x7E00002 },
    { 5, 2, 0x7E00003 },
    { 6, 2, 0x7E00004 },
    { 7, 2, 0x7E00005 },
    { 8, 2, 0x7E00006 },
    { 9, 2, 0x7E00007 },
    { 10, 2, 0x7E00008 },
    { 11, 2, 0x7E00009 },
    { 12, 2, 0x7E0000A },
    { 63, 2, 0x7E0000B },
    { 62, 3, 0x7E2000B },
    { 1009, 3, 0x7E20009 },
    { 1012, 3, 0x7E20003 },
    { 1013, 3, 0x7E20004 },
    { 1014, 3, 0x7E20005 },
    { 1017, 3, 0x7E20008 },
    { 1020, 3, 0x7E2000A },
    { 1004, 5, 0x7F50001 },
    { 1005, 5, 0x7F50002 },
    { 1006, 5, 0x7F50003 },
    { 1000, 6, 0x8A20001 },
    { 1001, 6, 0x8A20002 },
    { 1002, 6, 0x8A20003 },
    { 1003, 6, 0x8A20004 },
    { 1007, 6, 0x8A20006 },
    { 1008, 6, 0x8A20007 },
    { 1010, 7, 0x80F0001 },
    { 59, 9, 0x80E0001 },
    { 60, 9, 0x80E0002 },
    { 1018, 9, 0x80E0006 },
    { 1019, 9, 0x80E0007 },
    { 2040, 8, 0x78B0001 },
    { 2036, 10, 0x7890001 },
    { 2037, 10, 0x7890002 },
    { 2058, 11, 0x81C0000 },
    { 1021, 12, 0x7E50004 },
    { 2027, 12, 0x7E50001 },
    { 2028, 12, 0x7E50002 },
    { 2043, 13, 0x6D90001 },
    { 2011, 14, 0x7E60001 },
    { 2012, 14, 0x7E60002 },
    { 1015, 15, 0x8110001 },
    { 2059, 15, 0x8110003 },
    { 2060, 16, 0x81D0000 },
    { 2056, 17, 0x78C0003 },
    { 2031, 17, 0x78C0001 },
    { 2014, 18, 0x7DB0001 },
    { 2026, 19, 0x7E70001 },
    { 1016, 20, 0x8120001 },
    { 2044, 21, 0x7A50001 },
    { 1022, 22, 0x8190001 },
    { 2019, 23, 0x78D0001 },
    { 2020, 23, 0x78D0002 },
    { 2008, 24, 0x78E0002 },
    { 2009, 24, 0x78E0003 },
    { 2010, 24, 0x78E0004 },
    { 2062, 25, 0x89D0001 },
    { 2000, 26, 0x78F0001 },
    { 2001, 26, 0x78F0002 },
    { 2002, 26, 0x78F0003 },
    { 2004, 27, 0x7DC0001 },
    { 2046, 28, 0x8130001 },
    { 2047, 28, 0x8130002 },
    { 2061, 29, 0x8180001 },
    { 2057, 30, 0x81B0001 },
    { 2029, 31, 0x78A0001 },
    { 2030, 31, 0x78A0002 },
    { 2032, 32, 0x7730001 },
    { 2007, 33, 0x83D0001 },
    { 2041, 34, 0x7E80001 },
    { 2042, 34, 0x7E80002 },
    { 2024, 35, 0x7DD0001 },
    { 2025, 35, 0x7DD0002 },
    { 2005, 36, 0x7DE0001 },
    { 2006, 36, 0x7DE0003 },
    { 2016, 37, 0x7E90001 },
    { 2017, 37, 0x7E90002 },
    { 2018, 37, 0x7E90003 },
    { 2038, 38, 0x8010003 },
    { 2039, 38, 0x8010004 },
    { 2003, 39, 0x7DF0001 },
    { 2015, 40, 0x8030001 },
    { 2021, 41, 0x7900002 },
    { 2022, 41, 0x7900003 },
    { 2023, 41, 0x7900004 },
    { 2013, 42, 0x8050001 },
    { 2033, 43, 0x8020001 },
    { 2034, 43, 0x8020002 },
    { 2035, 44, 0x8900001 },
    { 2049, 45, 0x8890001 },
    { 2050, 46, 0x88A0001 },
    { 2051, 46, 0x88A0002 },
    { 2052, 46, 0x88A0003 },
    { 2048, 47, 0x8880001 },
    { 2053, 48, 0x88B0001 },
    { 2054, 48, 0x88B0002 },
    { 2055, 48, 0x88B0003 },
    { 1011, 49, 0x8100001 },
    { 2045, 50, 0x81A0001 },
    { -1, 0, 0 },
};
#endif
s32 D_800A20EC[] = {
    0x10028, 190,
};
s32 D_800A20F4[] = {
    0x20029, 192,
};
s32 D_800A20FC[] = {
    0x4002A, 194,
};
s32 D_800A2104[] = {
    0x3F002C, 196,
};
u16 D_800A210C[] = {
    0x002B, 0x0021, 0x001F, 0x002C, 0x0021, 0x001F, 0x002D, 0x0021,
    0x001F, 0x002E, 0x0021, 0x001F, 0x0042, 0x0022, 0x001F, 0x0043,
    0x0022, 0x001F, 0x0044, 0x0022, 0x001F, 0x0045, 0x0022, 0x001F,
    0x0046, 0x0023, 0x001F, 0x0047, 0x0021, 0x001F, 0x0048, 0x0028,
    0x001F, 0x0049, 0x0024, 0x001F, 0x004A, 0x0026, 0x001F, 0x004B,
    0x002E, 0x001E, 0x004C, 0x002E, 0x001E, 0xFFFF, 0x0000, 0x0000,
};
TechBoost D_800A216C[] = {
    { 0xC6, 1, 0, 0x30 },
    { 0xC8, 1, 1, 0x31 },
    { 0xCA, 1, 2, 0x32 },
    { 0xCC, -1, 0, 0x33 },
    { 0xCD, -1, 1, 0x34 },
    { 0xCE, -1, 1, 0x34 },
    { 0xCF, -1, 2, 0x35 },
    { 0xD0, -1, 2, 0x35 },
    { -1, 0, 0, 0 },
};
TechBoost D_800A21B4[] = {
    { 0xC7, 1, 0, 0x30 },
    { 0xC9, 1, 1, 0x31 },
    { 0xCB, 1, 2, 0x32 },
    { -1, 0, 0, 0 },
};
u8 D_800A21D4[] = {
    0x01, 0x02, 0x04, 0x3F,
};
#if VERSION_EU
s32 FIGHTSTG_clearIds[] = {
    9, 10, 11, 12,
    16, 17,
};
#endif
s32 D_800A21D8[] = {
    1, 2, 3, 4,
};
s32 D_800A21E8[] = {
    40, 41, 42, 44,
};
/* the European version swaps two pairs */
#if VERSION_US
s32 D_800A21F8[] = {
    0x2500AF, 0x25012F, 0x2B00AF, 0x2B012F,
    0x25000F, 0x25008F, 0x2B000F, 0x2B008F,
};
#elif VERSION_EU
s32 D_800A21F8[] = {
    0x2500AF, 0x25012F, 0x2B00AF, 0x2B012F,
    0x25008F, 0x25000F, 0x2B008F, 0x2B000F,
};
#endif
s32 D_800A2218[] = {
    0x287100, 0x3EC800, 0x1637B3, 0xD37FF,
};
u16 D_800A2228[] = {
    0x0109, 0x003E, 0x0131, 0x003E, 0x0109, 0x0046, 0x0131, 0x0046,
};
s32 D_800A2238[] = {
    0, 0, 0, 0,
};
u16 D_800A2248[] = {
    0x010F, 0x011A, 0x0125, 0x0025, 0x001A, 0x000F,
};
Unk8009A214 D_800A2254 = {
    6, 17, 110, 19, 34, 16, 109, 19,
};
Unk8009A214 D_800A2274 = {
    0, 168, 147, 19, 36, 167, 146, 19,
};
StatLine D_800A2294[13] = {
    { 60, 82, 6 },
    { 60, 96, 7 },
    { 60, 110, 8 },
    { 60, 124, 9 },
    { 60, 138, 10 },
    { 60, 152, 11 },
    { 126, 82, 12 },
    { 126, 96, 13 },
    { 126, 110, 14 },
    { 126, 124, 15 },
    { 126, 138, 16 },
    { 126, 152, 17 },
    { 126, 166, 18 },
};
Unk8009A214 D_800A22BC = {
    1, 14, 69, 14, -1, 0, 0, 0,
};
Unk8009A214 D_800A22DC = {
    1, 14, 69, 14, -1, 0, 0, 0,
};
Unk8009A214 D_800A22FC = {
    2, 17, 78, 32, 47, 16, 77, 32,
};
Unk8009A214 D_800A231C[] = {
    { 4, 168, 147, 19, 36, 167, 146, 19 },
    { 2, 168, 166, 19, 34, 167, 165, 19 },
};
u16 D_800A235C[] = {
    0x00AC, 0x0000, 0x00D8, 0x0000, 0x00D9, 0x0000, 0x00FB, 0x0000,
};
s16 D_800A236C[][2] = {
    { 1, 0x73 }, { 2, 0x74 }, { 3, 0x75 }, { 4, 0x76 },
    { 5, 0x77 }, { 6, 0x78 }, { 7, 0x79 }, { 8, 0x7A },
    { 9, 0x7B }, { 10, 0x7C }, { 11, 0x7D }, { 12, 0x7E },
    { 13, 0x7F }, { 14, 0x80 }, { 15, 0x81 }, { 16, 0x82 },
};
s16 D_800A23AC[] = {
    7, 1, 0, 3, 2, 5, 4, 6,
};
Unk8009A214 D_800A23BC = {
    6, 17, 110, 19, 34, 16, 109, 19,
};
RECT D_800A23DC = { 0, 0xF4, 12, 12 };
JumpParams D_800A23E4[] = {
    { 640, 136 }, { 1280, 102 }, { 1920, 81 }, { 2560, 64 }, { 1280, 64 }, { 0, 42 },
};
s32 D_800A2414[] = {
    0x6004001E, 0x4001C, 0x40004, 0x4000A,
    0x4000B, 0x4000C, 0x4004000D, 0x40014,
    0x4001A, 0x40019, 0x40017, 0x40011,
    0x4000F, 0x4001F, 0x40016, 0x40010,
    0x4000E, 0x40012, 0x8004103C, 0x800410BD,
    0x8004213E, 0x800421BF, 0xA0042240, 0x80042342,
    0x80042444, 0x8004293E, 0x800429BF, 0x80042A40,
    0x40001, 0x80042B42, 0x80042C44, 0x80042CC5,
    0x80042D46, 0x80042DC7, 0x80042E48, 0xA0042F4A,
    0xA0042FCB, 0xA004303C, 0x800430BD, 0x8004313E,
    0xA00431BF, 0xA0043240, 0x800432C1, 0x80043342,
    0x800433C3, 0x800434C5, 0x80043546, 0xA00435C7,
    0x80043648, 0x8004374A, 0x800437CB, 0x8004383C,
    0x80043A40, 0xA0043BC3, 0xA0043C44, 0x800440BD,
    0x8004413E, 0x800441BF, 0x80044240, 0x800442C1,
    0x80044444, 0x800445C7, 0x80044648, 0x800446C9,
    0x8004474A, 0x8004483C, 0x41180000, 0x8004503C,
    0x800450BD, 0x8004513E, 0x800452C6, 0x80045341,
    0x4001B, 0x800454C4, 0x8004583C, 0x800458BD,
    0x8004593E, 0x800459BF, 0x80045A40, 0x80045AC1,
    0x80045B42, 0x80045BC3, 0x80045C44, 0x80045CC5,
    0x80045D46, 0x80045DC7, 0x8004603C, 0x800460BD,
    0x8004613E, 0x20040006, 0, 0,
};
BattleTableEntry *(*D_800A2584)(s32 id) = FIGHTSTG_getBattleTableEntry;
s32 D_800A2588[] = {
    0, 1, 1, 1,
    -1, 1, -1, 1,
    1, -1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 0,
};
EventQueue D_800A25F0 = {
    { { 0 } }, { 0 }, 0, 0, 0, 0,
    {
        0, 0, FIGHTSTG_pushEvent, FIGHTSTG_pushEventFirst, FIGHTSTG_popEvent,
        FIGHTSTG_findFirstEvent, FIGHTSTG_findNextEvent, FIGHTSTG_findEvent, FIGHTSTG_removeEvents,
        func_8009AEA4, func_8009B430,
    },
};
EventDelay D_800A310C[] = {
    { 1000, 707, 1414 }, { 250, 176, 353 }, { 2001, 1001, 0 }, { 2000, 0, 0 },
    { 2500, 0, 0 }, { 3000, 0, 0 }, { 3500, 0, 0 }, { 4000, 0, 0 },
    { 0, 2000, 6000 }, { 500, 1000, 0 }, { 500, 1000, 0 }, { 500, 500, 0 },
    { 2001, 0, 0 },
};
u8 D_800A315C[] = {
    0x09, 0x0A, 0x0B, 0x0C, 0x10, 0x11, 0x00, 0x00,
};
u8 D_800A3164[] = {
    0x01, 0x02, 0x04, 0x3F,
};
s32 D_800A3168[] = {
    13, 14, 15,
};
s32 D_800A3174[] = {
    16, 17,
};
BattleAction D_800A317C = {
    { 0 }, 0, { 0 }, 0, 0, 0, 0, { 0 }, 0, 0, { 0 }, { 0 }, func_8009D204,
};
Battle D_800A31E8 = {
    0, 0, { 0 }, { { { 0 } } }, 0, 0, 0, 0, 0, 0, 0, { 0, 0 },
    func_8009D560, func_8009D648, FIGHTSTG_projectPoint, func_8009DA88, func_8009DAA8,
};
FighterCache D_800A32E0 = {
    0, 0, 0, 0, NULL, NULL, { FIGHTSTG_getFighterInfo, FIGHTSTG_cacheFighter, FIGHTSTG_getFighterRange }, FIGHTSTG_getFighterFace,
};
Battle800A3308 D_800A3308 = {
    { { 0 }, { 0 } },
    FIGHTSTG_computeStats, func_8009EA74, func_8009EBAC, func_8009EF04,
    func_8009F028, func_8009F1F0, func_8009F280, func_8009F7A4,
    func_8009F9C0, func_8009FB10, func_8009FC90, func_8009FDF8,
    func_8009FF60, func_800A00A4, func_800A020C, func_800A0400,
    func_800A0494, func_800A052C, func_800A05DC, func_800A062C,
#if VERSION_EU
    func_800A15A8,
#endif
    func_800A067C, func_800A0830, func_800A0978, func_800A0A40,
    func_800A0B10, func_800A0C80, func_800A0DA4,
};
s32 D_800A33F4[] = {
    0, 0, 4, 2,
    5, 3, 7, 8,
    6,
};
s16 D_800A3418[] = {
    0x0000, 0x0001, 0x0004, 0x0000,
};
Methods800A3420 D_800A3420 = { func_800A0EEC, FIGHTSTG_lerpVector, func_800A0FDC };
#if VERSION_EU
/* the lists of shots of the European version's own camera (func_800A1FE0) */
CameraShot D_800A46A8[3][3] = {
    { { 64, 6 }, { 2, 3 }, { -1, 0 } },
    { { 32, 1 }, { 32, 4 }, { -1, 0 } },
    { { 32, 2 }, { 32, 4 }, { -1, 0 } },
};
#endif
s32 D_800A342C = 0;
s32 D_800A3430 = 0; /* the partner's idle motion while stage 0x1D is up */
s32 D_800A3434 = 0;
CameraView D_800A3438 = { 0 };
s32 D_800A346C = 0;
RECT D_800A3470 = { 0 }; /* func_800933EC's layer */
DR_MOVE D_800A3478[4] = { { 0 } };
u_long D_800A34D8[2] = { 0 };
BattleEvent D_800A34E0 = { 0 };
