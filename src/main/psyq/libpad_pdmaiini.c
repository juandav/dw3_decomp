#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pdmaiini", PadStartCom);

void PadStopCom(void) {
    func_80024C98();
    func_80024D18(3, 1);
    func_80024D08(2, D_80055578);
    func_80024CA8();
}

OBJECT_END();
