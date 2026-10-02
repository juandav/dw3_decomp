/* the event flags are set from the BIOS event handlers */
#define D_80082168 D_80082168_plain
#define D_8008216C D_8008216C_plain
#define D_80082170 D_80082170_plain
#define D_80082174 D_80082174_plain
#define D_80082178 D_80082178_plain
#define D_8008217C D_8008217C_plain
#define D_80082180 D_80082180_plain
#define D_80082184 D_80082184_plain
#include "psyq.h"
#undef D_80082168
#undef D_8008216C
#undef D_80082170
#undef D_80082174
#undef D_80082178
#undef D_8008217C
#undef D_80082180
#undef D_80082184

extern volatile long D_80082168;
extern volatile long D_8008216C;
extern volatile long D_80082170;
extern volatile long D_80082174;
extern volatile long D_80082178;
extern volatile long D_8008217C;
extern volatile long D_80082180;
extern volatile long D_80082184;

long func_8003A588(long event); /* TestEvent */

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

void _card_start(void) {
    int ret = EnterCriticalSection();

    D_80082148 = OpenEvent(0xF4000001, 4, 0x1000, funcEvSpIOE);
    D_8008214C = OpenEvent(0xF4000001, 0x8000, 0x1000, funcEvSpError);
    D_80082150 = OpenEvent(0xF4000001, 0x100, 0x1000, funcEvSpTimeout);
    D_80082154 = OpenEvent(0xF4000001, 0x2000, 0x1000, funcEvSpNewcard);
    D_80082158 = OpenEvent(0xF0000011, 4, 0x1000, funcEvSpIOEx);
    D_8008215C = OpenEvent(0xF0000011, 0x8000, 0x1000, funcEvSpErrorx);
    D_80082160 = OpenEvent(0xF0000011, 0x100, 0x1000, funcEvSpTimeoutx);
    D_80082164 = OpenEvent(0xF0000011, 0x2000, 0x1000, funcEvSpNewcardx);
    EnableEvent(D_80082148);
    EnableEvent(D_8008214C);
    EnableEvent(D_80082150);
    EnableEvent(D_80082154);
    EnableEvent(D_80082158);
    EnableEvent(D_8008215C);
    EnableEvent(D_80082160);
    EnableEvent(D_80082164);
    _clr_card_event();
    if (ret == 1) {
        ExitCriticalSection();
    }
}

void _card_close(void) {
    StopCARD();
}

void _card_stop(void) {
    int ret = EnterCriticalSection();

    CloseEvent(D_80082148);
    CloseEvent(D_8008214C);
    CloseEvent(D_80082150);
    CloseEvent(D_80082154);
    CloseEvent(D_80082158);
    CloseEvent(D_8008215C);
    CloseEvent(D_80082160);
    CloseEvent(D_80082164);
    if (ret == 1) {
        ExitCriticalSection();
    }
}

void _clr_card_event(void) {
    func_8003A588(D_80082148);
    func_8003A588(D_8008214C);
    func_8003A588(D_80082150);
    func_8003A588(D_80082154);
    func_8003A588(D_80082158);
    func_8003A588(D_8008215C);
    func_8003A588(D_80082160);
    func_8003A588(D_80082164);
    D_80082168 = D_8008216C = D_80082170 = D_80082174 = 0;
    D_80082178 = D_8008217C = D_80082180 = D_80082184 = 0;
}

long _get_card_event(void) {
    long ev;

retry:
    ev = D_80082168 + D_8008216C * 2 + D_80082170 * 4 + D_80082174 * 8;
    if (ev == 0) {
        goto retry;
    }
    func_8003A588(D_80082158);
    func_8003A588(D_8008215C);
    func_8003A588(D_80082160);
    func_8003A588(D_80082164);
    D_80082168 = D_8008216C = D_80082170 = D_80082174 = 0;
    return ev >> 1;
}

long _get_card_event_x(void) {
    long ev;

retry:
    ev = D_80082178 + D_8008217C * 2 + D_80082180 * 4 + D_80082184 * 8;
    if (ev == 0) {
        goto retry;
    }
    func_8003A588(D_80082148);
    func_8003A588(D_8008214C);
    func_8003A588(D_80082150);
    func_8003A588(D_80082154);
    D_80082178 = D_8008217C = D_80082180 = D_80082184 = 0;
    return ev >> 1;
}

long _chk_card_event(void) {
    return D_80082168 + D_8008216C * 2 + D_80082170 * 4 + D_80082174 * 8;
}

long _chk_card_event_x(void) {
    return D_80082178 + D_8008217C * 2 + D_80082180 * 4 + D_80082184 * 8;
}

INCLUDE_ASM("main/nonmatchings/psyq/libmcrd_bios", CloseEvent);

OBJECT_END();
