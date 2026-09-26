#include "psyq.h"

void InitCARD(long val) {
    int ret;

    ChangeClearPAD(0);
    VSync(0);
    ret = func_80024C98();
    if (ReadInitPadFlag() == 0) {
        val = 0;
    }
    func_8003B6A8(val);
    _copy_memcard_patch();
    _patch_card();
    _patch_card2();
    _patch_card_info();
    if (ret == 1) {
        func_80024CA8();
    }
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcard_init", StartCARD);

long StopCARD(void) {
    func_8003B6C8();
    _ExitCard();
    return 0;
}

OBJECT_END();
