#include "psyq.h"

void StSetStream(u_long mode, u_long start_frame, u_long end_frame, void (*func1)(), void (*func2)()) {
    StSetMask(1, start_frame, end_frame);
    D_80080C10 = 0;
    D_80080C38 = func1;
    D_80080BE8 = mode & 1;
    D_80080BF8 = 0;
    D_80080BF0 = 0;
    D_80080BE4 = 0;
    D_80080BE0 = 0;
    D_80080C3C = func2;
}

OBJECT_END();
