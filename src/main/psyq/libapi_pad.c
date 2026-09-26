#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libapi_pad", SetInitPadFlag);

long ReadInitPadFlag(void) {
    return D_8005C2B8;
}

void PAD_init(char *bufA, long lenA, char *bufB, long lenB) {
    _remove_ChgclrPAD();
    func_80024C98();
    _patch_pad();
    func_80024CA8();
    ChangeClearPAD(0);
    func_8003B444();
    func_8003B588(bufA, lenA, bufB, lenB);
    D_8005C2B8 = 1;
}

long InitPAD(char *bufA, long lenA, char *bufB, long lenB) {
    _remove_ChgclrPAD();
    func_80024C98();
    _patch_pad();
    func_80024CA8();
    ChangeClearPAD(0);
    func_8003B444();
    func_8003B568(bufA, lenA, bufB, lenB);
    D_8005C2B8 = 1;
}

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
