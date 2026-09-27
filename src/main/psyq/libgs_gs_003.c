#include "psyq.h"
#include <libgte.h>
#include <libgs.h>

extern short D_800809D8[2]; /* PSDBASEX */
extern short D_800809DC[2]; /* PSDBASEY */
extern DRAWENV D_800809F0;  /* GsDRAWENV */
extern RECT D_80080A68;     /* CLIP2 */
extern short D_80080A74;    /* PSDIDX */

void GsSetDrawBuffClip(void) {
    int x, y;

    x = D_80080A68.x + D_800809D8[D_80080A74];
    y = D_80080A68.y + D_800809DC[D_80080A74];
    D_800809F0.clip.x = x;
    D_800809F0.clip.y = y;
    D_800809F0.clip.w = D_80080A68.w;
    D_800809F0.clip.h = D_80080A68.h;
    PutDrawEnv(&D_800809F0);
}

OBJECT_END();
