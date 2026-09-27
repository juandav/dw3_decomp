#include "psyq.h"

void gte_init(void) {
    InitGeom();
    SetFarColor(0, 0, 0);
    SetGeomOffset(0, 0);
    D_80080A66 = 0;
    D_80080A64 = 0;
}

OBJECT_END();
