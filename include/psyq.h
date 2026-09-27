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
    /* 0x10 */ void (*ctrl)(u_long cmd);
    /* 0x14 */ int (*unk14)(u_long *p, int len);
    /* 0x18 */ int (*exeque)(u_long *p); /* runs an OT / packet */
    /* 0x1C */ int (*storeImage)(RECT *rect, u_long *p);
    /* 0x20 */ int (*loadImage)(RECT *rect, u_long *p);
    /* 0x24 */ void *unk24;
    /* 0x28 */ void *unk28;
    /* 0x2C */ int (*unk2C)(u_long *ot, int n);
    /* 0x30 */ void *unk30;
    /* 0x34 */ int (*unk34)(int mode);
    /* 0x38 */ u_long (*status)(void);
    /* 0x3C */ int (*sync)(int mode);
} GpuDriver;

/* libsnd voice state (_svm_voice), 0x38 bytes per voice */
typedef struct VmVoice {
    /* 0x00 */ short unk0;
    /* 0x02 */ short unk2;
    /* 0x04 */ short unk4;
    /* 0x06 */ u_short unk6;
    /* 0x08 */ short unk8;
    /* 0x0A */ u_char unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ short unkC;
    /* 0x0E */ short note;
    /* 0x10 */ short unk10;
    /* 0x12 */ short unk12;
    /* 0x14 */ short prog;
    /* 0x16 */ short tone;
    /* 0x18 */ short vabId;
    /* 0x1A */ short priority;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ char unk1D;
    /* 0x1E */ short unk1E;
    /* 0x20 */ short unk20;
    /* 0x22 */ short unk22;
    /* 0x24 */ short unk24;
    /* 0x26 */ short unk26;
    /* 0x28 */ short unk28;
    /* 0x2A */ short unk2A;
    /* 0x2C */ short unk2C;
    /* 0x2E */ short unk2E;
    /* 0x30 */ short unk30;
    /* 0x32 */ short unk32;
    /* 0x34 */ short unk34;
    /* 0x36 */ short unk36;
} VmVoice;
extern VmVoice D_800815D0[];

/* libpad per-port command state */
typedef struct PadPort {
    /* 0x00 */ long unk0;
    /* 0x04 */ long unk4;
    /* 0x08 */ long unk8;
    /* 0x0C */ struct PadPort *unkC;
    /* 0x10 */ struct PadPort *unk10;
    /* 0x14 */ void (*unk14)();
    /* 0x18 */ int (*unk18)();
    /* 0x1C */ u8 unk1C[4];
    /* 0x20 */ u_char *unk20;
    /* 0x24 */ u_char param;
    /* 0x25 */ u8 unk25[3];
    /* 0x28 */ u_char *actTable;
    /* 0x2C */ u_char *data;
    /* 0x30 */ u_char *unk30;
    /* 0x34 */ u_char actLen;
    /* 0x35 */ u8 unk35;
    /* 0x36 */ u_char len;
    /* 0x37 */ u_char cmd;
    /* 0x38 */ u_char prevCmd;
    /* 0x39 */ u_char unk39;
    /* 0x3A */ u8 unk3A[2];
    /* 0x3C */ u_char *unk3C;
    /* 0x40 */ u_char *unk40;
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u_char unk45;
    /* 0x46 */ u_char unk46;
    /* 0x47 */ u_char unk47[2];
    /* 0x49 */ u_char unk49;
    /* 0x4A */ u_char unk4A; /* retry counter */
    /* 0x4B */ u8 unk4B;
    /* 0x4C */ long unk4C; /* failure count */
    /* 0x50 */ u8 unk50;
    /* 0x51 */ u_char unk51[2];
    /* 0x53 */ u_char unk53;
    /* 0x54 */ u8 unk54[3];
    /* 0x57 */ u_char unk57[6];
    /* 0x5D */ u_char unk5D[6];
    /* 0x63 */ u8 unk63[0x80];
    /* 0xE3 */ u_char unkE3;
    /* 0xE4 */ u_char unkE4;
    /* 0xE5 */ u8 unkE5;
    /* 0xE6 */ u_short unkE6;
    /* 0xE8 */ u8 unkE8;
    /* 0xE9 */ u_char unkE9;
    /* 0xEA */ u_char unkEA;
    /* 0xEB */ u8 unkEB;
    /* 0xEC */ u_short unkEC;
    /* 0xEE */ u_short unkEE;
} PadPort;

/* libmcrd global state, returned by McrdGetGlobalStructure */
typedef struct McrdGlobal {
    /* 0x00 */ long unk0;
    /* 0x04 */ long unk4;
    /* 0x08 */ long unk8;
    /* 0x0C */ long unkC;
    /* 0x10 */ long unk10;
    /* 0x14 */ long fd;
    /* 0x18 */ long unk18;
    /* 0x1C */ long unk1C;
    /* 0x20 */ long unk20;
    /* 0x24 */ u8 unk24[0x20];
    /* 0x44 */ MemCB callback;
    /* 0x48 */ long unk48;
    /* 0x4C */ long unk4C;
    /* 0x50 */ long unk50;
    /* 0x54 */ long unk54;
} McrdGlobal;

/* serial port registers */
typedef struct SioRegs {
    /* 0x0 */ u_char data;
    /* 0x1 */ u8 unk1[3];
    /* 0x4 */ u_short stat;
    /* 0x6 */ u_short unk6;
    /* 0x8 */ u_short mode;
    /* 0xA */ u_short ctrl;
    /* 0xC */ u_short unkC;
    /* 0xE */ u_short baud;
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

/* libspu current reverb attributes, D_8005B9CC */
typedef struct {
    long mode;
    short depthLeft;
    short depthRight;
    long delay;
    long feedback;
} SpuRevAttrInternal;

/* libspu reverb register block, as passed to _spu_setReverbAttr */
typedef struct SpuReverbRegs {
    /* 0x00 */ long mask;
    /* 0x04 */ u_short param[32];
} SpuReverbRegs;

/* libsnd per-sequence state, D_80080D38[seq][sep] */
typedef struct SeqStruct {
    /* 0x00 */ u_char *readPos;
    /* 0x04 */ u_char *startPos;
    /* 0x08 */ u_char *loopPos;
    /* 0x0C */ u_char *unkC;
    /* 0x10 */ u_char *endPos;
    /* 0x14 */ char unk14;
    /* 0x15 */ u_char unk15;
    /* 0x16 */ u_char status;
    /* 0x17 */ u_char channel;
    /* 0x18 */ u_char rpn1;
    /* 0x19 */ u_char rpn2;
    /* 0x1A */ u_char nrpn1;
    /* 0x1B */ u_char nrpn2;
    /* 0x1C */ u_char unk1C;
    /* 0x1D */ u_char unk1D;
    /* 0x1E */ u_char unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ char unk20;
    /* 0x21 */ char unk21;
    /* 0x22 */ char unk22;
    /* 0x23 */ char unk23;
    /* 0x24 */ u8 unk24[2];
    /* 0x26 */ char vabId;
    /* 0x27 */ u_char panpot[16];
    /* 0x37 */ u_char programs[16];
    /* 0x47 */ u8 unk47;
    /* 0x48 */ short unk48;
    /* 0x4A */ short unk4A;
    /* 0x4C */ short unk4C;
    /* 0x4E */ short unk4E;
    /* 0x50 */ short unk50;
    /* 0x52 */ short unk52;
    /* 0x54 */ short unk54;
    /* 0x56 */ short unk56;
    /* 0x58 */ u_short voll;
    /* 0x5A */ u_short volr;
    /* 0x5C */ short unk5C;
    /* 0x5E */ short unk5E;
    /* 0x60 */ u_short vol[16];
    /* 0x80 */ short channelMute;
    /* 0x82 */ u8 unk82[2];
    /* 0x84 */ long unk84;
    /* 0x88 */ long unk88;
    /* 0x8C */ long unk8C;
    /* 0x90 */ long delta;
    /* 0x94 */ long unk94;
    /* 0x98 */ long flags;
    /* 0x9C */ long unk9C;
    /* 0xA0 */ long unkA0;
    /* 0xA4 */ long unkA4;
    /* 0xA8 */ long unkA8;
    /* 0xAC */ long unkAC;
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
typedef struct GpuDebug {
    /* 0x0 */ u_char type;
    /* 0x1 */ u_char unk1;
    /* 0x2 */ u_char level;
    /* 0x3 */ u_char reverse;
    /* 0x4 */ short w;
    /* 0x6 */ short h;
    /* 0x8 */ long unk8;
    /* 0x0C */ void (*drawSyncCallback)();
    /* 0x10 */ DRAWENV draw; /* also reached as D_800556B0 */
    /* 0x6C */ DISPENV disp; /* also reached as D_8005570C */
} GpuDebug;
extern GpuDebug D_800556A0;
extern volatile u_long *D_800557A8;
extern volatile u_long *D_800557AC;
extern volatile u_long *D_800557B0;
extern volatile u_long *D_800557B4;
extern u_short D_8005A6FA;
extern volatile u_short *D_8005B788;
extern long D_8005B800;
extern volatile u_short *D_8005BA28;
extern long D_8005B9B8;
extern long D_8005BA44;
extern volatile u_short *D_8005B86C;
extern long D_8005BA5C;
extern long D_8005C2B8;
extern long D_8005C2E8;
extern McrdGlobal D_80082068;

/* argument block of a pending libmcrd event */
typedef struct UserFuncArg {
    long data[4];
} UserFuncArg;

void UserFuncOpen(long (*func)(UserFuncArg *arg));

void *DMACallback(int dma, void (*func)());
void *InterruptCallback(int irq, void (*func)());
void *VSyncCallbacks(int ch, void (*func)());
u_short SetIntrMask(u_short mask);
int CD_ready();
void init_ring_status(int start, u_int count);
long sin_1(long a);
void _card_stop(void);
long _spu_FsetRXXa(long reg, u_long addr);
void _putchar(char c);
void _putchar_flash(void);
int printf(char *fmt, ...);
char tolower(char c);
void _SsInit(void);
void _SsSeqPlay(short, short);
void _SsSndStop(short, short);
int _SsVmKeyOff(short seq_sep, short vab, short prog, u_short note);
void Snd_SetPlayMode(short, short, char, short);
void _SpuInit(int);
u_long _SpuGetAnyVoice(int, int);
void _padSetCmd(PadPort *port, u_char cmd, u_char *data, u_char len);
void func_80024CE8(long fd);
int CD_init(void);
int CD_initvol(void);
int func_80037AF0(int arg0, int arg1);
short _SsVabOpenHeadWithMode(unsigned char *addr, short vabId, int (*alloc)(), unsigned long sbaddr);
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
extern void (*D_8005551C)(PadPort *p);
extern u_char D_80055578[];
extern volatile u_long *D_800557A4;
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

void func_800254DC(char *name, RECT *rect);
int func_8003B444(void);
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
long _SsVmVSetUp(short vab, short prog);
/* libsnd's current voice state */
typedef struct SvmCur {
    /* 0x00 */ char tones;
    /* 0x01 */ char vabId;
    /* 0x02 */ char note;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ char vol;
    /* 0x05 */ char pan;
    /* 0x06 */ char progNum;
    /* 0x07 */ char prog;
    /* 0x08 */ u8 unk8[2];
    /* 0x0A */ char progVol;
    /* 0x0B */ char progPan;
    /* 0x0C */ char tone;
    /* 0x0D */ char toneVol;
    /* 0x0E */ char tonePan;
    /* 0x0F */ char priority;
    /* 0x10 */ char center;
    /* 0x11 */ u_char shift;
    /* 0x12 */ char mode;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ short seqSep;
    /* 0x16 */ short vag;
    /* 0x18 */ short voice;
} SvmCur;

extern SvmCur D_80081E00;
extern VagAtr *D_80081DF0;
extern u_char D_80081E20[];
extern ProgAtr *D_80081DE4;
long _SsVmSetProgVol(short vab, short prog, u_char vol);
void _SsVmSetVol(short seq_sep, char vab, u_char prog, u_short vol, u_char pan);
void _SsSndSetVolData(short seq, short sep, int vol, long count);
u_long _SpuSetAnyVoice(long on_off, u_long bits, int addr1, int addr2);
int func_800271F0(int (*func)(), u_long *param, int size, u_long value);

extern SeqStruct *D_80080D38[];

void *memcpy(u_char *dst, u_char *src, int n);
void func_8002425C(PadPort *port);
void func_80024270(PadPort *port, u_char param);
void func_80024290(PadPort *port, u_char param);
void func_800242B0(PadPort *port, u_char param);
void func_800242D0(PadPort *port);

extern DRAWENV D_800556B0;
extern DISPENV D_8005570C;

u_long _spu_Fw(u_char *addr, u_long size);
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
extern volatile u_short *D_8005C2BC;
void _spu_t();
extern void (*D_80055540)(void);
extern volatile u_long *D_8005558C;
extern volatile u_short D_8005BA40;
extern volatile long D_8005BA60;
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
