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
    /* 0x00 */ void *unk0;
    /* 0x04 */ void *unk4;
    /* 0x08 */ int (*addque)(void *func, void *param, int size, long arg);
    /* 0x0C */ void *unkC;
    /* 0x10 */ void *unk10;
    /* 0x14 */ int (*unk14)(u_long *p, int len);
    /* 0x18 */ void *unk18;
    /* 0x1C */ void *unk1C;
    /* 0x20 */ void *unk20;
    /* 0x24 */ u8 unk24[0x14];
    /* 0x38 */ u_long (*status)(void);
    /* 0x3C */ int (*sync)(int mode);
} GpuDriver;

/* libsnd voice state (_svm_voice), 0x38 bytes per voice */
typedef struct VmVoice {
    /* 0x00 */ short unk0;
    /* 0x02 */ short unk2;
    /* 0x04 */ short unk4;
    /* 0x06 */ u8 unk6[0x17];
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ u8 unk1E[0x1A];
} VmVoice;
extern VmVoice D_800815D0[];

/* libpad per-port command state */
typedef struct PadPort {
    /* 0x00 */ long unk0;
    /* 0x04 */ long unk4;
    /* 0x08 */ long unk8;
    /* 0x0C */ struct PadPort *unkC;
    /* 0x10 */ u8 unk10[4];
    /* 0x14 */ void (*unk14)();
    /* 0x18 */ void (*unk18)();
    /* 0x1C */ u8 unk1C[4];
    /* 0x20 */ u_char *unk20;
    /* 0x24 */ u_char param;
    /* 0x25 */ u8 unk25[3];
    /* 0x28 */ u_char *actTable;
    /* 0x2C */ u_char *data;
    /* 0x30 */ u8 unk30[4];
    /* 0x34 */ u_char actLen;
    /* 0x35 */ u8 unk35;
    /* 0x36 */ u_char len;
    /* 0x37 */ u_char cmd;
    /* 0x38 */ u_char prevCmd;
    /* 0x39 */ u_char unk39;
    /* 0x3A */ u8 unk3A[2];
    /* 0x3C */ u_char *unk3C;
    /* 0x40 */ u8 unk40[6];
    /* 0x46 */ u_char unk46;
    /* 0x47 */ u_char unk47[2];
    /* 0x49 */ u_char unk49;
    /* 0x4A */ u8 unk4A[9];
    /* 0x53 */ u_char unk53;
    /* 0x54 */ u8 unk54[9];
    /* 0x5D */ u_char unk5D[6];
    /* 0x63 */ u8 unk63[0x80];
    /* 0xE3 */ u_char unkE3;
    /* 0xE4 */ u_char unkE4;
    /* 0xE5 */ u8 unkE5;
    /* 0xE6 */ short unkE6;
    /* 0xE8 */ u8 unkE8;
    /* 0xE9 */ u_char unkE9;
    /* 0xEA */ u_char unkEA;
    /* 0xEB */ u8 unkEB;
    /* 0xEC */ u_short unkEC;
    /* 0xEE */ u8 unkEE[2];
} PadPort;

/* libmcrd global state, returned by McrdGetGlobalStructure */
typedef struct McrdGlobal {
    /* 0x00 */ long unk0;
    /* 0x04 */ u8 unk4[0x10];
    /* 0x14 */ long fd;
    /* 0x18 */ u8 unk18[0x2C];
    /* 0x44 */ MemCB callback;
} McrdGlobal;

/* serial port registers */
typedef struct SioRegs {
    /* 0x0 */ u_long data;
    /* 0x4 */ u_short stat;
} SioRegs;

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

/* libsnd per-sequence state, D_80080D38[seq][sep] */
typedef struct SeqStruct {
    /* 0x00 */ long unk0;
    /* 0x04 */ long unk4;
    /* 0x08 */ u8 unk8[0xC];
    /* 0x14 */ char unk14;
    /* 0x15 */ u8 unk15[2];
    /* 0x17 */ u_char channel;
    /* 0x18 */ u_char rpn1;
    /* 0x19 */ u_char rpn2;
    /* 0x1A */ u8 unk1A[4];
    /* 0x1E */ u_char unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ char unk20;
    /* 0x21 */ char unk21;
    /* 0x22 */ u8 unk22[4];
    /* 0x26 */ char vabId;
    /* 0x27 */ u_char panpot[16];
    /* 0x37 */ u_char programs[16];
    /* 0x47 */ u8 unk47[0x19];
    /* 0x60 */ u_short vol[16];
    /* 0x80 */ u8 unk80[0x10];
    /* 0x90 */ long delta;
    /* 0x94 */ u8 unk94[4];
    /* 0x98 */ long flags;
    /* 0x9C */ u8 unk9C[0x14];
} SeqStruct;

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
extern long D_8005B9B8;
extern long D_8005BA44;
extern volatile u_short *D_8005B86C;
extern long D_8005BA5C;
extern long D_8005C2B8;
extern long D_8005C2E8;
extern McrdGlobal D_80082068;

void *DMACallback(int dma, void (*func)());
void *InterruptCallback(int irq, void (*func)());
void *VSyncCallbacks(int ch, void (*func)());
u_short SetIntrMask(u_short mask);
int CD_ready();
void init_ring_status(int start, u_int count);
void _SsInit(void);
void _SsSeqPlay(short, short);
void _SsSndStop(short, short);
void _SsVmKeyOff(int, short, short, int);
void Snd_SetPlayMode(short, short, char, short);
void _SpuInit(int);
u_long _SpuGetAnyVoice(int, int);
void _padSetCmd(PadPort *port, u_char cmd, u_char *data, u_char len);
void func_80024CE8(long fd);
int CD_init(void);
int CD_initvol(void);
int func_80037AF0(int arg0, int arg1);
short _SsVabOpenHeadWithMode(unsigned char *addr, short vabId, int (*func)(int, int), unsigned long sbaddr);
void SysDeqIntRP(int, u_char *);
void ChangeClearRCnt(int, int);
void func_8002B018(void);
void func_8002B6D8(u_long, int);
void func_8002EE10();
void *func_8002EE7C();
void func_8002EEA8(long *p, int n);
void func_8002EF24();
void func_8002F0A4();
void func_8002F150(long *p, int n);
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
extern void (*D_8005B7A0[8])();
extern int D_8007F138;
extern int D_8007F134;
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

int func_800254DC(char *name, RECT *rect);
void func_8003B444(void);
void func_8003B568(char *bufA, long lenA, char *bufB, long lenB);
void func_8003B588(char *bufA, long lenA, char *bufB, long lenB);
void func_8003B6B8(void);
void func_80028E6C(u_short, u_short, u_short, u_short, u_short);
void func_80028FF0(u_short, u_short);
void gte_init(void);
void GsSetDrawBuffClip(void);
void GsSetDrawBuffOffset(void);
void _remove_ChgclrPAD(void);
void _patch_pad(void);

extern char D_80010444[];
extern char D_8001048C[];
extern short D_80080A74;
extern long D_80082148;
extern long D_8008214C;
extern long D_80082150;
extern long D_80082154;
extern long D_80082158;
extern long D_8008215C;
extern long D_80082160;
extern long D_80082164;

extern PadPort *(*D_8005552C)(int port);
extern long D_80055588;
extern long D_8005A2C8;
extern long D_8005A2CC;
extern long D_8005A2D0;
extern long D_8005A570;
extern PadPort D_8007E4D0[2];
extern short D_80081D98;

long _SsReadDeltaValue(short seq, short sep);
void _SsVmSetProgVol(char vab, u_char prog, u_char vol);
void _SsVmSetVol(short seq_sep, char vab, u_char prog, u_short vol, u_char pan);
void _SsSndSetVolData();
u_long _SpuSetAnyVoice(long on_off, u_long bits, int addr1, int addr2);
int func_800271F0(int, int, int, int);

extern SeqStruct *D_80080D38[];

void *memcpy(u_char *dst, u_char *src, int n);
void func_8002425C(PadPort *port);
void func_80024270(PadPort *port, u_char param);
void func_80024290(PadPort *port, u_char param);
void func_800242B0(PadPort *port, u_char param);
void func_800242D0(PadPort *port);

extern DRAWENV D_800556B0;
extern DISPENV D_8005570C;

void _spu_Fw(u_char *addr, u_long size);
void func_8002E388(void (*func)());
void func_8002E3D8(void (*func)());
long func_8002DE88(long value);
long func_8002E3B8(long value);

extern volatile SioRegs *D_80055590;
extern volatile u_char *D_8005A200;
extern volatile u_char *D_8005A20C;
extern long D_8005A2E8;
extern u_long *D_8005B868;
extern u_long D_8005B870[];
extern long D_8005BA50;
extern long D_8005BA60;
extern long D_80080BE8;
extern long D_80080BF0;
extern long D_80080BF4;
extern long D_80080BF8;
extern long D_80080C10;
extern long D_80080C14;
extern long D_80080C18;
extern void (*D_80080C38)();
extern void (*D_80080C3C)();
extern long D_80080C8C[];

void _clr_card_event(void);
void _SpuDataCallback(void (*func)());
long funcEvSpIOE(void);
long funcEvSpError(void);
long funcEvSpTimeout(void);
long funcEvSpNewcard(void);
long funcEvSpIOEx(void);
long funcEvSpErrorx(void);
long funcEvSpTimeoutx(void);
long funcEvSpNewcardx(void);
void func_8002DBDC();
void _spu_FiDMA();

extern long D_8005A2D4;
extern long D_8005A2D8;
extern long D_8005B9B0;
extern long D_8005BA18;
extern long D_80080C20;

void func_80034598(void);
void func_80034BE8(void);
extern u_char D_800555C1[];

#endif /* PSYQ_H */
