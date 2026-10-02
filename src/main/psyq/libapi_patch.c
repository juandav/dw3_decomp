#include "psyq.h"

INCLUDE_ASM("main/nonmatchings/psyq/libapi_patch", EnablePAD);

INCLUDE_ASM("main/nonmatchings/psyq/libapi_patch", DisablePAD);

INCLUDE_ASM("main/nonmatchings/psyq/libapi_patch", _patch_pad);

OBJECT_END();
