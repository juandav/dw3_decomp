#include "psyq.h"

long SetVideoMode(long mode) {
    long old = D_8005B800;

    D_8005B800 = mode;
    return old;
}

long GetVideoMode(void) {
    return D_8005B800;
}

OBJECT_END();
