#include "psyq.h"

extern long D_80080C80;
extern CdlLOC D_80080C28;
extern long D_80080C2C;

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcd_c_004", data_ready_callback);

int StGetBackloc(CdlLOC *loc) {
    if (D_80080C80 != 0) {
        return -1;
    }
    CdIntToPos(CdPosToInt(&D_80080C28) + 1, loc);
    return D_80080C2C;
}

OBJECT_END();
