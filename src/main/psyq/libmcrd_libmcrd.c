#include "psyq.h"

typedef struct CardName {
    char s[6];
} CardName;

/* "Access Denied. : event multiple open\n" */
extern char D_80010C9C[];
extern char D_80010D98[];

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

inline void PushCallbackFunc(void) {
    D_800820C0 = MemCardCallback(NULL);
}

inline void PullCallbackFunc(void) {
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

INCLUDE_RODATA("main/nonmatchings/psyq/libmcrd_libmcrd", D_80010C9C);

INCLUDE_ASM("main/nonmatchings/psyq/libmcrd_libmcrd", func_8003BAEC);

inline long MemCardAccept(long chan) {
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

INCLUDE_ASM("main/nonmatchings/psyq/libmcrd_libmcrd", func_8003BE70);

INCLUDE_ASM("main/nonmatchings/psyq/libmcrd_libmcrd", MemCardOpen);

INCLUDE_RODATA("main/nonmatchings/psyq/libmcrd_libmcrd", D_80010D98);

void MemCardClose(void) {
    if (D_80082068.fd >= 0) {
        func_80024CE8(D_80082068.fd);
        D_80082068.fd = -1;
    }
}

long MemCardReadData(u_long *adrs, long ofs, long bytes) {
    if (D_80082068.fd < 0) {
        printf("Access Denied. : file not open.\n");
        return 0;
    }
    if (D_80082068.unk0 > 0) {
        printf(D_80010C9C);
        return 0;
    }
    if (bytes & 0x7F) {
        printf("Access Denied. : invalid data size align\n");
        return 0;
    }
    if (ofs & 0x7F) {
        printf("Access Denied. : invalid offset value align\n");
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

extern long MCRD_READ_RETRIES;
long func_8003D248(long a, long b, long c);
long func_80024CC8(long fd, long a, long b);
long _chk_card_event(void);
long _get_card_event(void);
long _chk_card_event_x(void);
long _get_card_event_x(void);
void _clr_card_event(void);

long func_8003C39C(UserFuncArg *arg) {
    long ev;

    switch (arg->data[0]) {
    case 0:
        MCRD_READ_RETRIES = 0;
        arg->data[0] = 10;
        UserFuncOpen(func_8003BAEC);
        return 0;
    case 10:
        if (D_80082068.unk4 != 0) {
            return 1;
        }
        while (func_8003D248(D_80082068.fd, D_80082068.unk18, 0) != D_80082068.unk18) {
        }
        _clr_card_event();
        while (func_80024CC8(D_80082068.fd, D_80082068.unk20, D_80082068.unk1C) != 0) {
        }
        arg->data[0] = 30;
        break;
    case 30:
        if (_chk_card_event() == 0) {
            return 0;
        }
        ev = _get_card_event();
        if (ev != 0) {
            if (++MCRD_READ_RETRIES < 4) {
                arg->data[0] = 10;
                break;
            }
            if (ev == 4) {
                _clr_card_event();
                _card_clear(D_80082068.unk10);
                arg->data[0] = 32;
                break;
            }
        }
        ((volatile McrdGlobal *)&D_80082068)->unk4 = func_8003D0EC(ev);
        return 1;
    case 32:
        if (_chk_card_event_x() == 0) {
            return 0;
        }
        _get_card_event_x();
        arg->data[0] = 0;
        break;
    }
    return 0;
}

long MemCardWriteData(u_long *adrs, long ofs, long bytes) {
    if (D_80082068.fd < 0) {
        printf("Access Denied. : file not open.\n");
        return 0;
    }
    if (D_80082068.unk0 > 0) {
        printf(D_80010C9C);
        return 0;
    }
    if (bytes & 0x7F) {
        printf("Access Denied. : invalid data size align\n");
        return 0;
    }
    if (ofs & 0x7F) {
        printf("Access Denied. : invalid offset value align\n");
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

extern long MCRD_WRITE_RETRIES;

long func_8003C604(UserFuncArg *arg) {
    long ev;

    switch (arg->data[0]) {
    case 0:
        MCRD_WRITE_RETRIES = 0;
        UserFuncOpen(func_8003BAEC);
        arg->data[0] = 10;
        break;
    case 10:
        if (D_80082068.unk4 != 0) {
            return 1;
        }
        while (func_8003D248(D_80082068.fd, D_80082068.unk18, 0) != D_80082068.unk18) {
        }
        _clr_card_event();
        while (write(D_80082068.fd, D_80082068.unk20, D_80082068.unk1C) != 0) {
        }
        arg->data[0] = 30;
        break;
    case 30:
        if (_chk_card_event() == 0) {
            return 0;
        }
        ev = _get_card_event();
        if (ev != 0) {
            if (++MCRD_WRITE_RETRIES < 4) {
                arg->data[0] = 10;
                break;
            }
            if (ev == 4) {
                _clr_card_event();
                _card_clear(D_80082068.unk10);
                arg->data[0] = 32;
                break;
            }
        }
        ((volatile McrdGlobal *)&D_80082068)->unk4 = func_8003D0EC(ev);
        return 1;
    case 32:
        if (_chk_card_event_x() == 0) {
            return 0;
        }
        _get_card_event_x();
        arg->data[0] = 0;
        break;
    }
    return 0;
}

long MemCardReadFile(long chan, char *file, u_long *adrs, long ofs, long bytes) {
    volatile long *busy = &D_80082068.unk0;

    if (*busy > 0) {
        printf("Access Denied. : system busy\n");
        return 0;
    }
    if (D_80082068.fd >= 0) {
        printf(D_80010D98);
        return 0;
    }
    if (bytes & 0x7F) {
        printf("Access Denied. : invalid data size align\n");
        return 0;
    }
    if (ofs & 0x7F) {
        printf("Access Denied. : invalid offset value align\n");
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

extern long MCRD_READ_FILE_RETRIES;
long func_80024CB8(char *name, long mode);

long func_8003C8C8(UserFuncArg *arg) {
    switch (arg->data[0]) {
    case 0:
        MCRD_READ_FILE_RETRIES = 0;
        UserFuncOpen(func_8003BAEC);
        arg->data[0] = 10;
        break;
    case 10:
        if (D_80082068.unk4 != 0) {
            return 1;
        }
        D_80082068.fd = func_80024CB8((char *)D_80082068.unk24, 0x8001);
        if (D_80082068.fd < 0) {
            ((volatile McrdGlobal *)&D_80082068)->unk4 = 5;
            return 1;
        }
    case 11:
        arg->data[0] = 20;
        UserFuncOpen(func_8003C39C);
        return 0;
    case 20:
        func_80024CE8(D_80082068.fd);
        D_80082068.fd = -1;
        return 1;
    }
    return 0;
}

long MemCardWriteFile(long chan, char *file, u_long *adrs, long ofs, long bytes) {
    volatile long *busy = &D_80082068.unk0;

    if (*busy > 0) {
        printf("Access Denied. : system busy\n");
        return 0;
    }
    if (D_80082068.fd >= 0) {
        printf(D_80010D98);
        return 0;
    }
    if (bytes & 0x7F) {
        printf("Access Denied. : invalid data size align\n");
        return 0;
    }
    if (ofs & 0x7F) {
        printf("Access Denied. : invalid offset value align\n");
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

extern long MCRD_WRITE_FILE_RETRIES;

long func_8003CAE8(UserFuncArg *arg) {
    switch (arg->data[0]) {
    case 0:
        MCRD_WRITE_FILE_RETRIES = 0;
        UserFuncOpen(func_8003BAEC);
        arg->data[0] = 10;
        break;
    case 10:
        if (D_80082068.unk4 != 0) {
            return 1;
        }
        D_80082068.fd = func_80024CB8((char *)D_80082068.unk24, 0x8001);
        if (D_80082068.fd < 0) {
            ((volatile McrdGlobal *)&D_80082068)->unk4 = 5;
            return 1;
        }
    case 11:
        arg->data[0] = 20;
        UserFuncOpen(func_8003C604);
        return 0;
    case 20:
        func_80024CE8(D_80082068.fd);
        D_80082068.fd = -1;
        return 1;
    }
    return 0;
}

extern long D_80082078;
struct DIRENTRY *firstfile(char *name, struct DIRENTRY *dir);
struct DIRENTRY *func_8003D258(struct DIRENTRY *dir); /* nextfile */

long MemCardGetDirentry(long chan, char *name, struct DIRENTRY *dir, long *files, long ofs, long max) {
    char key[32];
    struct DIRENTRY d;
    long ret;
    long i;
    long retry;
    long n;
    struct DIRENTRY *p;
    volatile long *busy = &D_80082068.unk0;

    if (*busy != 0) {
        printf("Access Denied. : system busy\n");
        return -1;
    }
    func_8003D1EC(chan, key);
    strcat(key, name);
    retry = 0;
    i = 0;
    ret = 0;
    D_80082068.unkC |= 1 << chan;
    for (n = 0; i < ofs + max; i++) {
        if (i == 0) {
            for (;;) {
                _clr_card_event();
                p = firstfile(key, &d);
                if (p != NULL) {
                    break;
                }
                ret = func_8003D0EC(_get_card_event_x());
                if (ret == 0) {
                    break;
                }
                if (++retry >= 4) {
                    PushCallbackFunc();
                    if (D_80082068.unk0 > 0) {
                        printf(D_80010C9C);
                    } else {
                        D_80082068.unk0 = 2;
                        D_80082068.unk4 = 0;
                        D_80082068.unk8 = 0;
                        D_80082078 = chan;
                        UserFuncOpen(func_8003BE70);
                    }
                    MemCardSync(0, 0, &ret);
                    PullCallbackFunc();
                    return ret;
                }
            }
        } else {
            p = func_8003D258(&d);
        }
        if (p == NULL) {
            break;
        }
        if (i >= ofs && dir != NULL) {
            dir[n] = d;
            n++;
        }
    }
    if (files != NULL) {
        *files = n;
    }
    return 0;
}
/* needs RERUN=1 (libmcrd_libmcrd in PSYQ_RERUN_CSE), extern long D_80082078 (unk10 as a separate
   symbol inside the inlined MemCardAccept body), patch_cc1 #5 (spill slots). 20 diffs left: our reorg
   puts `move s7,a2` (prologue param copy) into the first beqz slot; the ROM leaves it and takes
   `addu a0,s6` from the branch target. */

MemCB MemCardCallback(MemCB func) {
    MemCB old = D_80082068.callback;

    D_80082068.callback = func;
    return old;
}

extern volatile long D_80082058[2]; /* last command and result, passed to the callback */

long MemCardSync(long mode, long *cmds, long *rslt) {
    volatile McrdGlobal *g = &D_80082068;
    long cmd, res;
    volatile long *done;

    if (g->unk0 == 0 && g->unk8 == 0) {
        return -1;
    }
    cmd = g->unk0;
    res = g->unk4;
    if (mode == 0) {
        if (g->unk8 == 0) {
            done = &g->unk8;
            do {
            } while (*done == 0);
        }
        if (rslt != NULL) {
            *rslt = D_80082058[1];
        }
        if (cmds != NULL) {
            *cmds = D_80082058[0];
        }
        ((volatile McrdGlobal *)&D_80082068)->unk8 = 0;
        return 1;
    }
    if (g->unk8 == 0) {
        if (rslt != NULL) {
            *rslt = res;
        }
        if (cmds != NULL) {
            *cmds = cmd;
        }
        return 0;
    }
    if (rslt != NULL) {
        *rslt = D_80082058[1];
    }
    if (cmds != NULL) {
        *cmds = D_80082058[0];
    }
    g->unk8 = 0;
    return 1;
}

long _card_create2(long chan, char *file, long blocks);

long MemCardCreateFile(long chan, char *file, long blocks) {
    volatile long *busy = &D_80082068.unk0;
    char name[32];
    long ret;

    if (*busy != 0) {
        printf("Access Denied. : system busy\n");
        return -1;
    }
    func_8003D1EC(chan, name);
    strcat(name, file);
    D_80082068.unkC |= 1 << chan;
    for (;;) {
        ret = _card_create2(chan, file, blocks);
        if (ret == 0) {
            break;
        }
        if (ret == -1) {
            return 7;
        }
        if (ret == -2) {
            return 4;
        }
        if (ret == -3) {
            return 6;
        }
        if (ret == 4) {
            return 2;
        }
        return func_8003D0EC(ret);
    }
    return 0;
}

long MemCardFormat(long chan) {
    volatile long *busy = &D_80082068.unk0;
    long ret;

    if (*busy != 0) {
        printf("Access Denied. : system busy\n");
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

void UserFuncExecute(void);
long UserFuncComplete(void);

void func_8003D140(void) {
    MemCB cb;

    if (UserFuncComplete() == 0) {
        UserFuncExecute();
        if (UserFuncComplete() != 0) {
            volatile McrdGlobal *g = &D_80082068;

            g->unk8 = 1;
            D_80082058[0] = g->unk0;
            D_80082058[1] = g->unk4;
            cb = D_80082068.callback;
            g->unk0 = 0;
            g->unk4 = 0;
            if (cb != NULL) {
                cb(D_80082058[0], D_80082058[1]);
            }
        }
    }
    {
        volatile McrdGlobal *g = &D_80082068;

        g->unk50 = g->unk50 + 1;
        g->unk54 = g->unk54 + 1;
    }
}

void func_8003D1EC(long chan, char *name) {
    *(CardName *)name = *(CardName *)"bu00:";
    name[2] = '0' + chan / 16;
    name[3] = '0' + chan % 16;
}

INCLUDE_ASM("main/nonmatchings/psyq/libmcrd_libmcrd", func_8003D248);

/* ASPSX padded the string table as well */
__asm__(".section .rodata\n\t.align 4\n");

OBJECT_END();
