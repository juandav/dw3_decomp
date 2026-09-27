#include "psyq.h"

typedef struct CardName {
    char s[6];
} CardName;

/* "Access Denied. : event multiple open\n" */
extern char D_80010C9C[];
/* "Access Denied. : system busy\n" */
extern char D_80010E40[];
extern char D_80010D98[];
extern char D_80010DC0[];
extern char D_80010DE4[];
extern char D_80010E10[];

long func_8003BAEC(UserFuncArg *arg);
long func_8003BE70(UserFuncArg *arg);
long func_8003D0EC(long event);
long func_8003C604(UserFuncArg *arg);
long func_8003C39C(UserFuncArg *arg);
long func_8003C8C8(UserFuncArg *arg);
long func_8003CAE8(UserFuncArg *arg);
void func_8003D1EC(long chan, char *name);
char *strcat(char *dst, char *src);
void func_8003D140(void);
void UserFuncInit(void);
void _card_start(void);
long _card_format2(long chan);

void PushCallbackFunc(void) {
    D_800820C0 = MemCardCallback(NULL);
}

void PullCallbackFunc(void) {
    MemCardCallback(D_800820C0);
}

void *McrdGetGlobalStructure(void) {
    return &D_80082068;
}

void MemCardStart(void) {
    volatile long *busy = &D_80082068.unk0;

    D_80082068.unkC = 0;
    D_80082068.callback = NULL;
    UserFuncInit();
    *busy = 0;
    *(volatile long *)&D_80082068.unk4 = 0;
    *(volatile long *)&D_80082068.unk8 = 0;
    D_80082068.unk50 = *(volatile long *)&D_80082068.unk54 = 0;
    D_80082068.fd = -1;
    D_80082068.unk4C = 1;
    D_80082068.unk48 = 1;
    _card_start();
    VSyncCallbacks(7, func_8003D140);
}

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

long MemCardReadData(u_long *adrs, long ofs, long bytes) {
    if (D_80082068.fd < 0) {
        printf(D_80010DC0);
        return 0;
    }
    if (D_80082068.unk0 > 0) {
        printf(D_80010C9C);
        return 0;
    }
    if (bytes & 0x7F) {
        printf(D_80010DE4);
        return 0;
    }
    if (ofs & 0x7F) {
        printf(D_80010E10);
        return 0;
    }
    D_80082068.unk0 = 5;
    D_80082068.unk4 = 0;
    D_80082068.unk8 = 0;
    D_80082068.unk18 = ofs;
    D_80082068.unk20 = (long)adrs;
    D_80082068.unk1C = bytes;
    UserFuncOpen(func_8003C39C);
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", func_8003C39C);

long MemCardWriteData(u_long *adrs, long ofs, long bytes) {
    if (D_80082068.fd < 0) {
        printf(D_80010DC0);
        return 0;
    }
    if (D_80082068.unk0 > 0) {
        printf(D_80010C9C);
        return 0;
    }
    if (bytes & 0x7F) {
        printf(D_80010DE4);
        return 0;
    }
    if (ofs & 0x7F) {
        printf(D_80010E10);
        return 0;
    }
    D_80082068.unk0 = 6;
    D_80082068.unk4 = 0;
    D_80082068.unk8 = 0;
    D_80082068.unk18 = ofs;
    D_80082068.unk20 = (long)adrs;
    D_80082068.unk1C = bytes;
    UserFuncOpen(func_8003C604);
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", func_8003C604);

long MemCardReadFile(long chan, char *file, u_long *adrs, long ofs, long bytes) {
    volatile long *busy = &D_80082068.unk0;

    if (*busy > 0) {
        printf(D_80010E40);
        return 0;
    }
    if (D_80082068.fd >= 0) {
        printf(D_80010D98);
        return 0;
    }
    if (bytes & 0x7F) {
        printf(D_80010DE4);
        return 0;
    }
    if (ofs & 0x7F) {
        printf(D_80010E10);
        return 0;
    }
    func_8003D1EC(chan, (char *)D_80082068.unk24);
    strcat((char *)D_80082068.unk24, file);
    *busy = 3;
    D_80082068.unk4 = 0;
    D_80082068.unk8 = 0;
    D_80082068.unk18 = ofs;
    D_80082068.unk20 = (long)adrs;
    D_80082068.unk1C = bytes;
    D_80082068.unk10 = chan;
    UserFuncOpen(func_8003C8C8);
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", func_8003C8C8);

long MemCardWriteFile(long chan, char *file, u_long *adrs, long ofs, long bytes) {
    volatile long *busy = &D_80082068.unk0;

    if (*busy > 0) {
        printf(D_80010E40);
        return 0;
    }
    if (D_80082068.fd >= 0) {
        printf(D_80010D98);
        return 0;
    }
    if (bytes & 0x7F) {
        printf(D_80010DE4);
        return 0;
    }
    if (ofs & 0x7F) {
        printf(D_80010E10);
        return 0;
    }
    func_8003D1EC(chan, (char *)D_80082068.unk24);
    strcat((char *)D_80082068.unk24, file);
    *busy = 4;
    D_80082068.unk4 = 0;
    D_80082068.unk8 = 0;
    D_80082068.unk18 = ofs;
    D_80082068.unk20 = (long)adrs;
    D_80082068.unk1C = bytes;
    D_80082068.unk10 = chan;
    UserFuncOpen(func_8003CAE8);
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", func_8003CAE8);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardGetDirentry);

MemCB MemCardCallback(MemCB func) {
    MemCB old = D_80082068.callback;

    D_80082068.callback = func;
    return old;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardSync);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libmcrd_libmcrd", MemCardCreateFile);

long MemCardFormat(long chan) {
    volatile long *busy = &D_80082068.unk0;
    long ret;

    if (*busy != 0) {
        printf(D_80010E40);
        return -1;
    }
    ret = _card_format2(chan);
    if (ret != 0) {
        if (ret == 4) {
            return 2;
        }
        return func_8003D0EC(ret);
    }
    return 0;
}

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
