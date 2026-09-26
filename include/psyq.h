#ifndef PSYQ_H
#define PSYQ_H

#include "common.h"
#include <sys/types.h>
#include <libapi.h>
#include <libetc.h>
#include <libgpu.h>
#include <libcd.h>
#include <libspu.h>
#include <libsnd.h>
#include <libmcrd.h>
#include <libpad.h>

/* libgpu driver entry points */
typedef struct GpuDriver {
    /* 0x00 */ u8 unk0[0x38];
    /* 0x38 */ u_long (*status)(void);
    /* 0x3C */ int (*sync)(int mode);
} GpuDriver;

/* libpad per-port command state */
typedef struct PadPort {
    /* 0x00 */ u8 unk0[0x24];
    /* 0x24 */ u_char param;
    /* 0x25 */ u8 unk25[7];
    /* 0x2C */ u_char *data;
    /* 0x30 */ u8 unk30[6];
    /* 0x36 */ u_char len;
    /* 0x37 */ u_char cmd;
    /* 0x38 */ u_char prevCmd;
    /* 0x39 */ u8 unk39[0xD];
    /* 0x46 */ u_char unk46;
    /* 0x47 */ u8 unk47[0xC];
    /* 0x53 */ u_char unk53;
} PadPort;

/* libetc interrupt handlers, reached through D_8005B780 */
typedef struct IntrFuncs {
    /* 0x00 */ void *unk0;
    /* 0x04 */ void *(*dmaCallback)(int dma, void (*func)());
    /* 0x08 */ void *(*interruptCallback)(int irq, void (*func)());
    /* 0x0C */ int (*resetCallback)(void);
    /* 0x10 */ int (*stopCallback)(void);
    /* 0x14 */ void *(*vsyncCallbacks)(int ch, void (*func)());
    /* 0x18 */ int (*restartCallback)(void);
} IntrFuncs;

/* libspu reverb register block, as passed to _spu_setReverbAttr */
typedef struct SpuReverbRegs {
    /* 0x00 */ long mask;
    /* 0x04 */ u_short param[32];
} SpuReverbRegs;

/* libsnd decoded ADSR */
typedef struct SsADSR {
    /* 0x00 */ short ar;
    /* 0x02 */ short dr;
    /* 0x04 */ short sl;
    /* 0x06 */ short sr;
    /* 0x08 */ short rr;
    /* 0x0A */ short arMode;
    /* 0x0C */ short srMode;
    /* 0x0E */ short rrMode;
    /* 0x10 */ short srDir;
} SsADSR;

int CD_getsector(void *madr, int size);
u_long func_80026748(short x, short y);
u_long func_800267E0(short x, short y);
u_long func_80026878(short x, short y);
int func_80024C98(void);
void func_80024CA8(void);
void func_8003B578(void);
void func_8003B6A8(long val);
void func_8003B6C8(void);
long func_8003D698(long chan, long block, u_char *buf);
void func_8003D6A8(void);
long ReadInitPadFlag(void);
void _ExitCard(void);
void _copy_memcard_patch(void);
void _patch_card(void);
void _patch_card2(void);
void _patch_card_info(void);

extern GpuDriver *D_80055698;
extern int (*D_8005569C)(char *fmt, ...);
extern u_char D_800556A2;
extern u_long *D_800557A8;
extern u_long *D_800557AC;
extern u_long *D_800557B0;
extern u_long *D_800557B4;
extern u_short D_8005A6FA;
extern u_short *D_8005B788;
extern long D_8005B800;
extern volatile u_short *D_8005BA28;
extern long D_8005BA5C;
extern long D_8005C2B8;
extern long D_8005C2E8;
extern u8 D_80082068[];

void *DMACallback(int dma, void (*func)());
void *InterruptCallback(int irq, void (*func)());
void *VSyncCallbacks(int ch, void (*func)());
u_short SetIntrMask(u_short mask);
int CD_ready();
void init_ring_status(int, int);
void _SsInit(void);
void _SsSeqPlay(short, short);
void _SsSndStop(short, short);
void _SsVmKeyOff(int, short, short, int);
void Snd_SetPlayMode(short, short, char, short);
void _SpuInit(int);
u_long _SpuGetAnyVoice(int, int);
int func_80024CD8(int fd, char *buf, int n);
void func_80024D08(int, u_char *);
void func_80024D18(int, int);
void func_8002B018(void);
void func_8002B6D8(u_long, int);
void func_8002EE10();
void func_8002EE7C();
void func_8002EEA8(void *, int);
void func_8002EF24();
void func_8002F0A4();
void func_8002F150(void *, int);
void func_8002FFF8(short);
void func_80032B98(int);
void func_80037FD8(void);
void func_8003B1C8(void);
void func_800274A0();

extern IntrFuncs *D_8005B780;
extern void (*D_8005551C)(void);
extern u_char D_80055578[];
extern u_long *D_800557A4;
extern long D_800557DC;
extern long D_800557E0;
extern long D_800557F4;
extern volatile u_char *D_8005A58C;
extern volatile u_char *D_8005A590;
extern volatile u_char *D_8005A598;
extern volatile u_char *D_8005A59C;
extern u_long *D_8005B7C4;
extern long D_8005B7C0;
extern u_char D_8005B7A0[];
extern u_long *D_8005B7D0;
extern u_char D_8005B7D4[];
extern u_long *D_8005BA3C;
extern short D_80080A64;
extern short D_80080A66;
extern char D_80080998[];
extern long D_80080BE0;
extern short D_80080BE4;
extern long D_80080BEC;
extern long D_80080BFC;
extern long D_80080C04;
extern long D_80080C08;
extern long D_80080C0C;
extern long D_80080C24;
extern MemCB D_800820C0;
extern long D_80082168;
extern long D_8008216C;
extern long D_80082170;
extern long D_80082174;
extern long D_80082178;
extern long D_8008217C;
extern long D_80082180;
extern long D_80082184;

#endif /* PSYQ_H */
