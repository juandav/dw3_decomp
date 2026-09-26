#include "psyq.h"

void PushCallbackFunc(void) {
    D_800820C0 = MemCardCallback(NULL);
}

void PullCallbackFunc(void) {
    MemCardCallback(D_800820C0);
}

void *McrdGetGlobalStructure(void) {
    return D_80082068;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardStart);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardStop);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardExist);

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libmcrd_libmcrd", D_80010C9C);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", func_8003BAEC);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardAccept);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", func_8003BE70);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardOpen);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardClose);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardReadData);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", func_8003C39C);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardWriteData);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", func_8003C604);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardReadFile);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", func_8003C8C8);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardWriteFile);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", func_8003CAE8);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardGetDirentry);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardCallback);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardSync);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardCreateFile);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardFormat);

long func_8003D0EC(long event) {
    long ret = 0;

    if (event != 1) {
        if (event < 2) {
            if (event != 0) {
                ret = event | 0x8000;
            }
        } else {
            ret = 1;
            if (event != 2) {
                ret = event | 0x8000;
                if (event == 4) {
                    ret = 3;
                }
            }
        }
    } else {
        ret = 2;
    }
    return ret;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", func_8003D140);

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libmcrd_libmcrd", D_80010D98);

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libmcrd_libmcrd", D_80010DC0);

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libmcrd_libmcrd", D_80010DE4);

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libmcrd_libmcrd", D_80010E10);

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libmcrd_libmcrd", D_80010E40);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", func_8003D1EC);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", func_8003D248);

OBJECT_END();
