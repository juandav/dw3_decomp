#include "psyq.h"

typedef struct CardName {
    char s[6];
} CardName;

/* "Access Denied. : event multiple open\n" */
extern char D_80010C9C[];

long func_8003BAEC(UserFuncArg *arg);
long func_8003BE70(UserFuncArg *arg);

void PushCallbackFunc(void) {
    D_800820C0 = MemCardCallback(NULL);
}

void PullCallbackFunc(void) {
    MemCardCallback(D_800820C0);
}

void *McrdGetGlobalStructure(void) {
    return &D_80082068;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardStart);

void MemCardStop(void) {
    volatile long *busy = &D_80082068.unk0;

    while (*busy != 0) {
    }
    VSyncCallbacks(7, NULL);
    _card_stop();
}

long MemCardExist(long chan) {
    if (D_80082068.unk0 > 0) {
        printf(D_80010C9C);
        return 0;
    }
    D_80082068.unk0 = 1;
    D_80082068.unk4 = 0;
    D_80082068.unk8 = 0;
    D_80082068.unk10 = chan;
    UserFuncOpen(func_8003BAEC);
    return 1;
}

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libmcrd_libmcrd", D_80010C9C);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", func_8003BAEC);

long MemCardAccept(long chan) {
    if (D_80082068.unk0 > 0) {
        printf(D_80010C9C);
        return 0;
    }
    D_80082068.unk0 = 2;
    D_80082068.unk4 = 0;
    D_80082068.unk8 = 0;
    D_80082068.unk10 = chan;
    UserFuncOpen(func_8003BE70);
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", func_8003BE70);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardOpen);

void MemCardClose(void) {
    if (D_80082068.fd >= 0) {
        func_80024CE8(D_80082068.fd);
        D_80082068.fd = -1;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardReadData);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", func_8003C39C);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardWriteData);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", func_8003C604);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardReadFile);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", func_8003C8C8);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardWriteFile);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", func_8003CAE8);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardGetDirentry);

MemCB MemCardCallback(MemCB func) {
    MemCB old = D_80082068.callback;

    D_80082068.callback = func;
    return old;
}

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

void func_8003D1EC(long chan, char *name) {
    *(CardName *)name = *(CardName *)"bu00:";
    name[2] = '0' + chan / 16;
    name[3] = '0' + chan % 16;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", func_8003D248);

/* ASPSX padded the string table as well */
__asm__(".section .rodata\n\t.align 4\n");

OBJECT_END();
