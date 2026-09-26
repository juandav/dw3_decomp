#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libetc_vmode", SetVideoMode);

long GetVideoMode(void) {
    return D_8005B800;
}

OBJECT_END();
