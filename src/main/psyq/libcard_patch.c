#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcard_patch", _patch_card_info);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcard_patch", func_8003B71C);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcard_patch", func_8003B748);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcard_patch", func_8003B78C);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcard_patch", _patch_card);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcard_patch", _patch_card2);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcard_patch", _copy_memcard_patch);

OBJECT_END();
