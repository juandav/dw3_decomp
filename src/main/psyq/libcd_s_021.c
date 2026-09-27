#include "psyq.h"

int func_8002E268(void *madr, int size) {
    return CD_getsector(madr, size) == 0;
}

OBJECT_END();
