#ifndef GAME_H
#define GAME_H

#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct Resource {
    /* 0x000 */ u8 unk0[0x138];
    /* 0x138 */ s32 (*unk138)(struct Resource *, s32);
} Resource;

/* Function tables in .data */
typedef struct Funcs80047F04 {
    /* 0x0 */ void (*unk0)();
    /* 0x4 */ s32 (*getFileSectors)(s32 file);
    /* 0x8 */ void (*unk8)();
    /* 0xC */ void (*unkC)();
} Funcs80047F04;

typedef struct Funcs8004ABD8 {
    /* 0x00 */ void (*unk0[9])();
    /* 0x24 */ void (*unk24)(s32, s32);
    /* 0x28 */ void (*unk28[14])();
} Funcs8004ABD8;

typedef struct MemFuncs {
    /* 0x00 */ void (*unk0)();
    /* 0x04 */ void (*free)(void *ptr);
    /* 0x08 */ void (*unk8)();
    /* 0x0C */ void *(*malloc)(s32 size, s32 tag);
    /* 0x10 */ void (*unk10)();
    /* 0x14 */ void (*unk14)();
    /* 0x18 */ void (*bzero)(void *ptr, s32 size);
    /* 0x1C */ void (*unk1C)();
    /* 0x20 */ void (*unk20)();
    /* 0x24 */ void (*unk24)();
} MemFuncs;

typedef struct TaskFuncs {
    /* 0x00 */ void (*unk0)();
    /* 0x04 */ void (*unk4)();
    /* 0x08 */ void (*unk8)();
    /* 0x0C */ void *(*unkC)(s32, s32, s32);
    /* 0x10 */ void (*unk10)();
    /* 0x14 */ void (*unk14)();
    /* 0x18 */ void (*unk18)(void *task);
    /* 0x1C */ void (*unk1C)();
} TaskFuncs;

typedef struct RandFuncs {
    /* 0x0 */ void (*srand)(s32 seed);
    /* 0x4 */ u16 (*rand)(void);
} RandFuncs;

typedef struct Funcs8004D708 {
    /* 0x00 */ void (*unk0[11])();
    /* 0x2C */ Resource *(*unk2C)(s32);
    /* 0x30 */ void (*unk30)();
    /* 0x34 */ void (*unk34)();
    /* 0x38 */ s32 (*unk38)(void);
    /* 0x3C */ void (*unk3C)();
} Funcs8004D708;

typedef struct SoundFuncs {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ void (*unk10)();
    /* 0x14 */ void (*playSound)(s32 id);
    /* 0x18 */ short (*keyOn)(s32 index, short prog, short note);
} SoundFuncs;

typedef struct Funcs800554D8 {
    /* 0x0 */ void (*unk0)();
    /* 0x4 */ void (*unk4)();
} Funcs800554D8;

typedef struct GfxState {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ void *unk24;
    /* 0x28 */ void *unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 buffer;
    /* 0x38 */ DISPENV disp[2];
} GfxState;

typedef struct Fade {
    s32 duration;
    s32 step;
    s32 level;
    s32 active;
} Fade;

typedef struct Task {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 state;
    /* 0x10 */ s32 substate;
    /* 0x14 */ s32 step;
    /* 0x18 */ s32 counter;
    /* 0x1C */ u8 unk1C[0xC];
    /* 0x28 */ void (*unk28)(struct Task *, s32);
    /* 0x2C */ void (*unk2C)(struct Task *, s32);
    /* 0x30 */ u8 unk30[0x20];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
} Task;

typedef struct Task80011FBC {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14[0x14];
    /* 0x28 */ void (*unk28)(struct Task80011FBC *, s32);
    /* 0x2C */ u8 unk2C[0x24];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 fadeOut;
    /* 0x5C */ s32 level;
    /* 0x60 */ s32 step;
    /* 0x64 */ void (*unk64)();
} Task80011FBC;

typedef struct Task8001ACC8 {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14[0x44];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 dirty;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
} Task8001ACC8;

typedef struct Task8001B3A0 {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14[0x18];
    /* 0x2C */ void (*unk2C)(struct Task8001B3A0 *, s32);
    /* 0x30 */ u8 unk30[0x20];
    /* 0x50 */ s32 *data;
    /* 0x54 */ s32 *unk54;
    /* 0x58 */ s32 compressed;
    /* 0x5C */ s32 size;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ void *unk64;
    /* 0x68 */ s32 *unk68;
    /* 0x6C */ void *unk6C;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ void (*unk74)();
    /* 0x78 */ void *(*unk78)();
    /* 0x7C */ void (*unk7C)();
    /* 0x80 */ void (*unk80)();
} Task8001B3A0;

typedef struct Unk80015A34 {
    /* 0x00 */ u8 unk0[0x2C];
    /* 0x2C */ void (*unk2C)(struct Unk80015A34 *, s32);
} Unk80015A34;

typedef struct Slot {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
    /* 0xC */ void *unkC;
} Slot;

typedef struct Callback {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ void (*func)(s32, void *, s32);
    /* 0x0C */ s32 unkC;
    /* 0x10 */ struct Callback *next;
} Callback;

typedef struct Sprite {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ u16 w;
    /* 0x06 */ u16 h;
    /* 0x08 */ u8 unk8[0x10];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 unk1C[0x4C];
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s16 unk6C;
    /* 0x6E */ s16 unk6E;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 callbackCap;
    /* 0x7C */ s32 callbackNum;
    /* 0x80 */ Callback *callbacks;
} Sprite;

typedef struct Rect16 {
    s16 x;
    s16 y;
    u16 w;
    u16 h;
} Rect16;

typedef struct TextBuffer {
    /* 0x0 */ char *data;
    /* 0x4 */ s16 cap;
    /* 0x6 */ s16 len;
    /* 0x8 */ s16 pos;
    /* 0xA */ s16 dirty;
} TextBuffer;

typedef struct Unk80019DFC {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14[0x3C];
    /* 0x50 */ u8 *unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ TextBuffer text[6];
    /* 0xA4 */ u16 unkA4;
    /* 0xA6 */ s16 unkA6;
    /* 0xA8 */ s16 unkA8;
    /* 0xAA */ s16 unkAA;
    /* 0xAC */ u8 unkAC[4];
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ s16 unkB4;
    /* 0xB6 */ s16 unkB6;
    /* 0xB8 */ u8 unkB8[6];
    /* 0xBE */ u8 unkBE;
    /* 0xBF */ u8 unkBF;
    /* 0xC0 */ u8 unkC0;
    /* 0xC1 */ u8 unkC1;
    /* 0xC2 */ s8 unkC2;
    /* 0xC3 */ u8 unkC3;
    /* 0xC4 */ u8 unkC4;
    /* 0xC5 */ u8 unkC5[3];
    /* 0xC8 */ s32 unkC8;
    /* 0xCC */ s32 unkCC;
    /* 0xD0 */ s32 unkD0;
    /* 0xD4 */ s32 unkD4;
    /* 0xD8 */ s32 unkD8;
    /* 0xDC */ s32 unkDC;
    /* 0xE0 */ s32 unkE0;
    /* 0xE4 */ s32 unkE4;
} Unk80019DFC;

typedef struct Unk80041444 {
    /* 0x0 */ u8 unk0[8];
    /* 0x8 */ u8 unk8;
    /* 0x9 */ u8 unk9;
    /* 0xA */ u8 unkA[2];
} Unk80041444;

typedef struct Unk8003EB68 {
    /* 0x00 */ u8 unk0[8];
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9[0x4F];
} Unk8003EB68;

typedef struct Unk80048C50Entry {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 unk2[0x12];
} Unk80048C50Entry;

typedef struct Unk80048C50 {
    /* 0x000 */ u8 unk0[0x50];
    /* 0x050 */ Unk80048C50Entry unk50[44];
    /* 0x3C0 */ u8 unk3C0[0x1C];
} Unk80048C50;

/* Double-buffered ordering tables */
typedef struct DrawContext {
    /* 0x00 */ u8 unk0[0x5C];
    /* 0x5C */ u_long *ot[2];
    /* 0x64 */ s32 otLen;
} DrawContext;

typedef struct SoundEntry {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s16 vabId;
    /* 0x06 */ u8 unk6[0x12];
} SoundEntry;

typedef struct Unk80051194 {
    /* 0x0000 */ u8 unk0[0x4200];
    /* 0x4200 */ SoundEntry sounds[1];
} Unk80051194;

typedef struct Obj8001E7DC {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ Resource *unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ void (*methods[10])();
} Obj8001E7DC;

typedef struct Obj8001F22C {
    /* 0x00 */ Resource *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ u8 r;
    /* 0x29 */ u8 g;
    /* 0x2A */ u8 b;
    /* 0x2B */ u8 unk2B;
    /* 0x2C */ s32 scaleDirty;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 scaleX;
    /* 0x3C */ s32 scaleY;
    /* 0x40 */ s32 scaleZ;
    /* 0x44 */ u8 unk44[0x2C];
    /* 0x70 */ void (*methods[12])();
} Obj8001F22C;

typedef struct Obj8001F8F8 {
    /* 0x0 */ void (*methods[3])();
} Obj8001F8F8;

typedef struct Obj8001FBE0 {
    /* 0x00 */ u8 unk0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ void (*methods[6])();
} Obj8001FBE0;

typedef struct Unk8004ADB8 {
    /* 0x000 */ s32 list[100];
    /* 0x190 */ s32 unk190;
    /* 0x194 */ s32 unk194;
    /* 0x198 */ s32 unk198;
    /* 0x19C */ s32 unk19C;
} Unk8004ADB8;

typedef struct Unk80042728 {
    /* 0x00 */ u8 unk0[0x58];
    /* 0x58 */ s16 unk58[8];
} Unk80042728;

/* CD read state */
typedef struct CdReader {
    /* 0x00 */ s32 state;
    /* 0x04 */ u8 unk4[8];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14[4];
    /* 0x18 */ u8 loc[4];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
} CdReader;

typedef struct MemBlock {
    /* 0x0 */ struct MemBlock *prev;
    /* 0x4 */ struct MemBlock *next;
    /* 0x8 */ s32 flags;
} MemBlock;

typedef struct Vec2 {
    s32 x;
    s32 y;
} Vec2;

typedef struct PadInfo {
    /* 0x000 */ s32 flags;
    /* 0x004 */ u8 unk4[0x44];
    /* 0x048 */ u16 unk48;
    /* 0x04A */ u16 unk4A;
    /* 0x04C */ u8 unk4C[2];
    /* 0x04E */ u16 unk4E;
    /* 0x050 */ u8 unk50[0x170];
} PadInfo;

typedef struct PadState {
    /* 0x000 */ PadInfo pads[2];
    /* 0x380 */ u8 unk380[0x56];
    /* 0x3D6 */ s16 unk3D6;
    /* 0x3D8 */ s32 unk3D8;
    /* 0x3DC */ s16 unk3DC;
} PadState;

typedef struct Unk800484E8 {
    /* 0x0000 */ u8 unk0[4];
    /* 0x0004 */ s8 unk4;
    /* 0x0005 */ u8 unk5[7];
    /* 0x000C */ s32 unkC;
    /* 0x0010 */ u8 unk10[0x20];
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ u8 unk34[0x14];
    /* 0x0048 */ s32 playFrames;
    /* 0x004C */ s16 playHours;
    /* 0x004E */ s16 playMinutes;
    /* 0x0050 */ s16 playSeconds;
    /* 0x0052 */ s16 playTimeMaxed;
    /* 0x0054 */ u8 unk54[0x2F];
    /* 0x0083 */ s8 unk83;
    /* 0x0084 */ u8 unk84[0x51];
    /* 0x00D5 */ s8 unkD5;
    /* 0x00D6 */ u8 unkD6[0x4D];
    /* 0x0123 */ s8 unk123;
    /* 0x0124 */ u8 unk124[0xF2];
    /* 0x0216 */ s8 unk216;
    /* 0x0217 */ u8 unk217[0x51];
    /* 0x0268 */ s8 unk268;
    /* 0x0269 */ u8 unk269[0x4D];
    /* 0x02B6 */ s8 unk2B6;
    /* 0x02B7 */ u8 unk2B7[0xEB];
    /* 0x03A2 */ s8 itemCounts[0x13D];
    /* 0x04DF */ s8 itemFlags[0x289];
    /* 0x0768 */ Unk80048C50 unk768[8];
    /* 0x2648 */ u8 unk2648[0x74];
    /* 0x26BC */ s32 unk26BC;
    /* 0x26C0 */ s32 unk26C0;
    /* 0x26C4 */ s32 unk26C4;
    /* 0x26C8 */ s32 unk26C8;
    /* 0x26CC */ s8 unk26CC;
    /* 0x26CD */ s8 unk26CD;
    /* 0x26CE */ s8 unk26CE;
    /* 0x26CF */ s8 unk26CF;
} Unk800484E8;

void PadStartCom(void);
void PadStopCom(void);
s32 VSyncCallback(void (*func)(void));

void *func_800144DC(void (*update)(void *), s32 size, s32 arg2);
void *func_800143B4(void (*update)(void *), s32 size, s32 arg2, s32 arg3);
s32 func_80013484(void);
Unk80041444 *func_80013534(s32 id);
void func_80019360(s32, void *, s32, s32);
void *CdIntToPos(s32 i, void *p);
short SsUtKeyOn(short vabId, short prog, short tone, short note, short fine, short voll, short volr);
void func_800119AC(void *task);
void func_80011DF0(Task80011FBC *task, s32 fadeOut, s32 duration);
void func_80011FBC(void *task);
void func_800126FC(void *task);
s32 func_80013A44(s32);
Slot *func_800139D4(s32 file);
Slot *func_80013A0C(void);
Slot *func_80013AB4(void);
void func_80013C08(s32);
void func_80013CB4(void);
void func_80016860(void);
void func_80013758();
void func_8002DE68(void (*func)());
int CdControlF(u_char com, u_char *param);
void func_80019140(Unk80019DFC *obj, char *text);
void func_80016260(u16, u16);
s32 func_80017DDC(s32);
void func_80017CE8(void);
void func_8001816C(void);
void func_8001D070(void);
void func_80019E34(Unk80019DFC *, s32);
void func_8001E3C4(Obj8001E7DC *obj);
void func_8001E3D0();
void func_8001E474();
void func_8001E51C();
void func_8001E570();
void func_8001E584();
void func_8001E598();
void func_8001E5AC();
void func_8001E5B8();
void func_8001E5C4();
void func_8001E7B0();
void func_8001E894(Obj8001F22C *obj);
void func_8001E8A0();
void func_8001E8BC();
void func_8001E8D0();
void func_8001E8DC(Resource *res, s32 arg1);
void func_8001E950();
void func_8001F1B4();
void func_8001F1D0();
void func_8001F1EC();
void func_8001F200();
void func_8001F20C();
void func_8001F31C(Obj8001F8F8 *obj);
void func_8001F328();
void func_8001F354();
void func_8001F658();
void func_8001F954(Obj8001FBE0 *obj);
void func_8001F960();
void func_8001F974();
void func_8001F988();
void func_8001FA70();
void func_8001FBD4();
int strlen(char *);
void *memcpy(void *, void *, int);
void func_8001794C(void *dst, s32 size);
void *func_80017B20(void);
void func_80017FAC(s32, s32);
void func_8001837C(s32, s32, s32, s32);
void func_8001B2B8(void *task);
void func_8001B314(Task8001B3A0 *task, s32 *data, s32 arg2);
void *func_8001B368(Task8001B3A0 *task);
void func_8001B3A0(void *task);
void func_8001B6A8(void *task);
void func_8001C0C4(void *task);
void func_80020764(void *task);
void func_8008AEB4(s32, s32, s32, s32, s32);

extern Unk8003EB68 D_8003EB68[];
extern char D_800101D8[];
extern char D_80010230[];
extern Funcs80047F04 D_80047F04;
extern Funcs8004ABD8 D_8004ABD8;
extern MemFuncs D_8004AD90;
extern TaskFuncs D_8004AF58;
extern RandFuncs D_8004D3B0;
extern Funcs8004D708 D_8004D708;
extern SoundFuncs D_800553DC;
extern Funcs800554D8 D_800554D8;
extern Unk80042728 D_80042728;
extern Unk80041444 D_80041444[];
extern u8 D_800427B4[];
extern CdReader D_80044710;
extern Slot D_80044748[64];
extern s32 D_80044744;
extern s32 D_80044B78[];
extern u16 D_80046DD4[];
extern Unk80048C50 D_80048C50[];
extern Unk800484E8 D_800484E8;
extern u8 D_8004853C[];
extern s32 D_8004ABA4;
extern s32 D_8004ABA8;
extern s32 D_8004ABAC;
extern s32 D_8004ABB0;
extern Unk8004ADB8 D_8004ADB8;
extern PadState D_8004AF78;
extern u16 D_8004B3AC[0x1000];
extern s32 D_8004D3AC;
extern u8 *D_8004D5A8;
extern GfxState D_8004D5B8;
extern Unk80051194 D_80051194;

#endif /* GAME_H */
