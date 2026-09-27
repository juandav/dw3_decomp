#include "stdwtitl.h"

s32 STDWTITL_getEdgeFadeLevel(s32 time) {
    if (time >= 30) {
        return 255;
    }
    return rsin(time * 1024 / 30) * 30 / 4096 * 255 / 30;
}

void STDWTITL_drawEdgeFade(s32 level) {
    Layer *layer = GFX.funcs.getLayer(STDWTITL_TITLE_LAYER);
    u_long *ot = (u_long *)layer->getOtEntry(layer, 0);
    POLY_G3 *poly = GFX.funcs.getPrim();
    DR_TPAGE *mode;
    s32 edge;
    s32 i;

    edge = level * 2;
    for (i = 0; i < 4; i++) {
        setPolyG3(poly);
        setSemiTrans(poly, 1);
        poly->r0 = poly->g0 = poly->b0 = level;
        if (edge >= 256) {
            edge = 255;
        }
        poly->r1 = poly->g1 = poly->b1 = poly->r2 = poly->g2 = poly->b2 = edge;
        /* From the centre of the screen to one of its edges */
        poly->x0 = 160;
        poly->y0 = 120;
        poly->x1 = STDWTITL_edgeFadeLines[i].x1;
        poly->y1 = STDWTITL_edgeFadeLines[i].y1;
        poly->x2 = STDWTITL_edgeFadeLines[i].x2;
        poly->y2 = STDWTITL_edgeFadeLines[i].y2;
        addPrim(ot, poly);
        poly++;
    }
    mode = (DR_TPAGE *)poly;
    setDrawTPage(mode, 0, 1, getTPage(0, 2, 320, 0));
    addPrim(ot, mode);
    GFX.funcs.setPrim(mode + 1);
}

void STDWTITL_startEdgeFade(EdgeFadeTask *task) {
    task->done = 0;
    task->time = 0;
    task->setSubstate(task, 1);
}

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_isEdgeFadeDone);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_tickEdgeFade);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_startEdgeFadeTask);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_stepLoopingAnimation);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_drawBackground);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_drawBackgroundSprites);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_tickBackground);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_animateBackground);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_startBackgroundTask);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_leaveTitle);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_stepTitle);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_tickTitle);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_startTitleTask);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_loadTitleImages);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_startFade);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_stepFade);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_startTween);

INCLUDE_ASM("asm/stdwtitl/nonmatchings/stdwtitl_2", STDWTITL_stepTween);
