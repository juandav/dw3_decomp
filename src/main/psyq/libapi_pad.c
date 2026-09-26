#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libapi_pad", SetInitPadFlag);

long ReadInitPadFlag(void) {
    return D_8005C2B8;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libapi_pad", PAD_init);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libapi_pad", InitPAD);

long StartPAD(void) {
    func_8003B578();
    ChangeClearPAD(0);
    EnablePAD();
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libapi_pad", func_8003B444);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libapi_pad", func_8003B4BC);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libapi_pad", func_8003B524);

OBJECT_END();
