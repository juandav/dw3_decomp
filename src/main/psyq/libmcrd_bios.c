#include "psyq.h"

long funcEvSpIOE(void) {
    D_80082168 = 1;
    return 0;
}

long funcEvSpError(void) {
    D_8008216C = 1;
    return 0;
}

long funcEvSpTimeout(void) {
    D_80082170 = 1;
    return 0;
}

long funcEvSpNewcard(void) {
    D_80082174 = 1;
    return 0;
}

long funcEvSpIOEx(void) {
    D_80082178 = 1;
    return 0;
}

long funcEvSpErrorx(void) {
    D_8008217C = 1;
    return 0;
}

long funcEvSpTimeoutx(void) {
    D_80082180 = 1;
    return 0;
}

long funcEvSpNewcardx(void) {
    D_80082184 = 1;
    return 0;
}

void _card_open(long val) {
    InitCARD(val);
    StartCARD();
    func_8003B1C8();
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_bios", _card_start);

void _card_close(void) {
    StopCARD();
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_bios", _card_stop);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_bios", _clr_card_event);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_bios", _get_card_event);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_bios", _get_card_event_x);

long _chk_card_event(void) {
    return D_80082168 + D_8008216C * 2 + D_80082170 * 4 + D_80082174 * 8;
}

long _chk_card_event_x(void) {
    return D_80082178 + D_8008217C * 2 + D_80082180 * 4 + D_80082184 * 8;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_bios", func_8003DE78);

OBJECT_END();
