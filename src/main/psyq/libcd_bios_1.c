#include "psyq.h"

typedef struct {
    u_char sync;
    u_char ready;
    u_char c;
} CD_intr;

typedef struct {
    int unk0;
    int unk4;
    char *unk8;
} Alarm_t;

extern volatile CD_intr D_8005A5A4[1];
extern volatile Alarm_t D_80080C68;

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libcd_bios_1", D_8001083C);

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libcd_bios_1", D_80010978);

INCLUDE_RODATA("asm/main/nonmatchings/psyq/libcd_bios_1", D_80010988);

extern long D_8005A2DC;
extern u_char D_8005A2E4;
extern u_char D_8005A2E5;
extern char *D_8005A2EC[];
extern char *D_8005A36C[];
extern int D_8005A38C[];
extern int D_8005A48C[];
extern u_char D_80080C50[8];
extern u_char D_80080C58[8];
extern u_char D_80080C60[8];

static inline void _memcpy(u_char *dst, u_char *src, int n) {
    if (dst != NULL) {
        while (n--) {
            *dst++ = *src++;
        }
    }
}

int func_8002C738(void) {
    volatile u_char nReg;
    volatile u_char buf[8];
    int i, j;
    int err;

    *D_8005A58C = 1;
    nReg = *D_8005A590 & 7;
    if (nReg == 0) {
        return 0;
    }
    err = 0;
    while (nReg != (*D_8005A590 & 7)) {
        nReg = *D_8005A590 & 7;
    }
    for (i = 0; i < 8; i++) {
        if (!(*D_8005A58C & 0x20)) {
            break;
        }
        buf[i] = *D_8005A598;
    }
    for (j = i; j < 8; j++) {
        buf[j] = 0;
    }
    *D_8005A58C = 1;
    *D_8005A590 = 7;
    *D_8005A59C = 7;
    if (nReg != 3 || D_8005A48C[D_8005A2E5]) {
        if (!(D_8005A2D4 & CdlStatShellOpen) && (buf[0] & CdlStatShellOpen)) {
            D_8005A2DC++;
        }
        D_8005A2D4 = buf[0];
        D_8005A2D8 = buf[1];
        err = D_8005A2D4 & 0x1D;
    }
    if (nReg == 5) {
        if (D_8005A2D0 > 2) {
            printf("DiskError: ");
        }
        if (D_8005A2D0 > 2) {
            printf("com=%s,code=(%02x:%02x)\n", D_8005A2EC[D_8005A2E5], D_8005A2D4, D_8005A2D8);
        }
    }
    switch (nReg) {
    case 3:
        if (err) {
            D_8005A5A4->sync = CdlDiskError;
            _memcpy(D_80080C50, (u_char *)buf, 8);
            return 2;
        }
        if (D_8005A38C[D_8005A2E5]) {
            D_8005A5A4->sync = CdlAcknowledge;
            _memcpy(D_80080C50, (u_char *)buf, 8);
            return 1;
        }
        D_8005A5A4->sync = CdlComplete;
        _memcpy(D_80080C50, (u_char *)buf, 8);
        return 2;
    case 2:
        D_8005A5A4->sync = err ? CdlDiskError : CdlComplete;
        _memcpy(D_80080C50, (u_char *)buf, 8);
        return 2;
    case 1:
        if (err && i == 1) {
            err = 0;
        }
        D_8005A5A4->ready = err ? CdlDiskError : CdlDataReady;
        _memcpy(D_80080C58, (u_char *)buf, 8);
        *D_8005A58C = 0;
        *D_8005A590 = 0;
        return 4;
    case 4:
        D_8005A5A4->ready = D_8005A5A4->c = CdlDataEnd;
        _memcpy(D_80080C60, (u_char *)buf, 8);
        _memcpy(D_80080C58, (u_char *)buf, 8);
        return 4;
    case 5:
        D_8005A5A4->sync = D_8005A5A4->ready = CdlDiskError;
        _memcpy(D_80080C50, (u_char *)buf, 8);
        _memcpy(D_80080C58, (u_char *)buf, 8);
        return 6;
    default:
        puts("CDROM: unknown intr");
        printf("(%d)\n", nReg);
        return 0;
    }
}

void CD_flush(void);
extern char D_80010978[];
extern char D_80010988[];

static inline void set_alarm(char *name) {
    ((Alarm_t *)&D_80080C68)->unk0 = VSync(-1) + 960;
    ((Alarm_t *)&D_80080C68)->unk4 = 0;
    ((Alarm_t *)&D_80080C68)->unk8 = name;
}

static inline int get_alarm(void) {
    if (((Alarm_t *)&D_80080C68)->unk0 < VSync(-1) || ((Alarm_t *)&D_80080C68)->unk4++ > 0x3C0000) {
        puts(D_80010978);
        printf(D_80010988, ((Alarm_t *)&D_80080C68)->unk8, *(D_8005A2EC + D_8005A2E5),
               *(D_8005A36C + D_8005A5A4->sync), *(D_8005A36C + D_8005A5A4->ready));
        CD_flush();
        return -1;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcd_bios_1", CD_sync);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcd_bios_1", CD_ready);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcd_bios_1", CD_cw);

int CD_vol(CdlATV *vol) {
    *D_8005A58C = 2;
    *D_8005A59C = vol->val0;
    *D_8005A590 = vol->val1;
    *D_8005A58C = 3;
    *D_8005A598 = vol->val2;
    *D_8005A59C = vol->val3;
    *D_8005A590 = 0x20;
    return 0;
}

extern volatile u_long *D_8005A594;

void CD_flush(void) {
    *D_8005A58C = 1;
    while (*D_8005A590 & 7) {
        *D_8005A58C = 1;
        *D_8005A590 = 7;
        *D_8005A59C = 7;
    }
    D_8005A5A4->ready = D_8005A5A4->c = CdlNoIntr;
    D_8005A5A4->sync = CdlComplete;
    *D_8005A58C = 0;
    *D_8005A590 = 0;
    *D_8005A594 = 0x1325;
}

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
    *D_8005A58C = 2;
    *D_8005A59C = vol.val0;
    *D_8005A590 = vol.val1;
    *D_8005A58C = 3;
    *D_8005A598 = vol.val2;
    *D_8005A59C = vol.val3;
    *D_8005A590 = 0x20;
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

extern char D_8005A5A8[];
int CD_cw(u_char com, u_char *param, u_char *result, int async);
int CD_sync(int mode, u_char *result);

/* CD_vol, CD_initintr and CD_flush are written out in CD_initvol and CD_init:
   GCC 2.8 would move `inline` functions to the end of the object */
int CD_init(void) {
    puts("CD_init:");
    printf("addr=%08x\n", D_8005A5A8);
    D_8005A2E5 = 0;
    D_8005A2E4 = 0;
    D_8005A2CC = 0;
    D_8005A2C8 = 0;
    D_8005A2D8 = 0;
    D_8005A2D4 = 0;
    ResetCallback();
    InterruptCallback(2, func_8002DBDC);
    *D_8005A58C = 1;
    while (*D_8005A590 & 7) {
        *D_8005A58C = 1;
        *D_8005A590 = 7;
        *D_8005A59C = 7;
    }
    D_8005A5A4->ready = D_8005A5A4->c = CdlNoIntr;
    D_8005A5A4->sync = CdlComplete;
    *D_8005A58C = 0;
    *D_8005A590 = 0;
    *D_8005A594 = 0x1325;
    CD_cw(CdlNop, NULL, NULL, 0);
    if (D_8005A2D4 & CdlStatShellOpen) {
        CD_cw(CdlNop, NULL, NULL, 0);
    }
    if (CD_cw(0x0A, NULL, NULL, 0)) {
        return -1;
    }
    if (CD_cw(CdlDemute, NULL, NULL, 0)) {
        return -1;
    }
    if (CD_sync(0, NULL) != CdlComplete) {
        return -1;
    }
    return 0;
}

extern volatile u_long *D_8005A5C0;

int CD_datasync(int mode) {
    int ret;
    int m = mode;

    set_alarm("CD_datasync");
    while (1) {
        if (get_alarm()) {
            ret = -1;
            break;
        }
        if (!(*D_8005A5C0 & 0x01000000)) {
            ret = 0;
            break;
        }
        if (m != 0) {
            ret = 1;
            break;
        }
    }
    return ret;
}

void CD_set_test_parmnum(int num) {
    D_8005A570 = num;
}


void func_8002DBDC(void) {
    u_char mask;
    int intr;

    mask = *D_8005A58C & 3;

    while ((intr = func_8002C738()) != 0) {
        if ((intr & 4) && D_8005A2CC != 0) {
            ((void (*)(u_char, u_char *))D_8005A2CC)(D_8005A5A4[0].ready, D_80080C58);
        }
        if ((intr & 2) && D_8005A2C8 != 0) {
            ((void (*)(u_char, u_char *))D_8005A2C8)(D_8005A5A4[0].sync, D_80080C50);
        }
    }
    *D_8005A58C = mask;
}

__asm__(".section .rodata\n\t.align 4\n");
OBJECT_END();
