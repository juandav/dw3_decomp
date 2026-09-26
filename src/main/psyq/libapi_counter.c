#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libapi_counter", SetRCnt);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libapi_counter", GetRCnt);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libapi_counter", StartRCnt);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libapi_counter", StopRCnt);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libapi_counter", ResetRCnt);

OBJECT_END();
