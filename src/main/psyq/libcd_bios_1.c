#include "psyq.h"

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libcd_bios_1", D_80010978);

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libcd_bios_1", D_80010988);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcd_bios_1", func_8002C738);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcd_bios_1", CD_sync);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcd_bios_1", CD_ready);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcd_bios_1", CD_cw);

inline int CD_vol(CdlATV *vol) {
    *D_8005A58C = 2;
    *D_8005A59C = vol->val0;
    *D_8005A590 = vol->val1;
    *D_8005A58C = 3;
    *D_8005A598 = vol->val2;
    *D_8005A59C = vol->val3;
    *D_8005A590 = 0x20;
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcd_bios_1", CD_flush);

extern volatile u_short *D_8005A5A0;

int CD_initvol(void) {
    CdlATV vol;

    if (D_8005A5A0[0xDC] == 0 && D_8005A5A0[0xDD] == 0) {
        D_8005A5A0[0xC0] = 0x3FFF;
        D_8005A5A0[0xC1] = 0x3FFF;
    }
    D_8005A5A0[0xD8] = 0x3FFF;
    D_8005A5A0[0xD9] = 0x3FFF;
    D_8005A5A0[0xD5] = 0xC001;
    vol.val0 = vol.val2 = 0x80;
    vol.val1 = vol.val3 = 0;
    CD_vol(&vol);
    return 0;
}

void CD_initintr(void) {
    D_8005A2CC = 0;
    D_8005A2C8 = 0;
    D_8005A2D8 = 0;
    D_8005A2D4 = 0;
    ResetCallback();
    InterruptCallback(2, func_8002DBDC);
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcd_bios_1", CD_init);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcd_bios_1", CD_datasync);

void CD_set_test_parmnum(int num) {
    D_8005A570 = num;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcd_bios_1", func_8002DBDC);

OBJECT_END();
