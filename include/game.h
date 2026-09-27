#ifndef GAME_H
#define GAME_H

#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct Resource {
    /* 0x000 */ u8 unk0[0x138];
    /* 0x138 */ s32 (*unk138)(struct Resource *, s32);
    /* 0x13C */ u8 unk13C[0x2C];
    /* 0x168 */ void (*unk168)(struct Resource *);
} Resource;

/* Function tables in .data */
typedef struct Funcs80047F04 {
    /* 0x0 */ void (*unk0)();
    /* 0x4 */ s32 (*getFileSectors)(s32 file);
    /* 0x8 */ s32 (*unk8)(s32 file);
    /* 0xC */ void (*unkC)(s32 file, s32 offset, u8 *loc);
} Funcs80047F04;

typedef struct Funcs8004ABD8 {
    /* 0x00 */ void (*unk0[2])();
    /* 0x08 */ s32 (*unk8)();
    /* 0x0C */ void (*unkC[2])();
    /* 0x14 */ s32 (*unk14)();
    /* 0x18 */ s32 (*unk18)();
    /* 0x1C */ void (*unk1C[2])();
    /* 0x24 */ void (*unk24)(s32, s32);
    /* 0x28 */ void (*unk28[14])();
} Funcs8004ABD8;

/* Heap state and memory functions */
typedef struct MemManager {
    /* 0x00 */ s32 size;
    /* 0x04 */ struct MemBlock *first;
    /* 0x08 */ struct MemBlock *end;
    /* 0x0C */ void (*unkC)();
    /* 0x10 */ void (*free)(void *ptr);
    /* 0x14 */ void (*unk14)();
    /* 0x18 */ void *(*malloc)(s32 size, s32 tag);
    /* 0x1C */ void *(*unk1C)(s32 size, s32 tag);
    /* 0x20 */ void (*unk20)();
    /* 0x24 */ void (*bzero)(void *ptr, s32 size);
    /* 0x28 */ void (*unk28)();
    /* 0x2C */ void (*unk2C)();
    /* 0x30 */ void (*unk30)();
} MemManager;

typedef struct TaskFuncs {
    /* 0x00 */ void (*unk0)();
    /* 0x04 */ void (*unk4)();
    /* 0x08 */ void (*unk8)();
    /* 0x0C */ void *(*unkC)(s32, s32, s32);
    /* 0x10 */ void (*unk10)();
    /* 0x14 */ void (*unk14)();
    /* 0x18 */ void (*unk18)(void *task);
    /* 0x1C */ void (*unk1C)(s32);
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
    /* 0x00 */ void (*vsyncFunc)(s32 arg);
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ void *bufs[2];
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 buffer;
    /* 0x38 */ DISPENV disp[2];
    /* 0x60 */ Resource *resources[30];
    /* 0xD8 */ s32 resourceIds[30];
    /* 0x150 */ Funcs8004D708 funcs; /* D_8004D708 */
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
    /* 0x1C */ u8 unk1C[8];
    /* 0x24 */ void *unk24;
    /* 0x28 */ void (*unk28)(struct Task *, s32);
    /* 0x2C */ void (*unk2C)(struct Task *, s32);
    /* 0x30 */ u8 unk30[0x20];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
} Task;

typedef struct Task80011FBC {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 state;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14[0x14];
    /* 0x28 */ void (*unk28)(struct Task80011FBC *, s32);
    /* 0x2C */ u8 unk2C[0xC];
    /* 0x38 */ void (*unk38)(struct Task80011FBC *);
    /* 0x3C */ u8 unk3C[0x14];
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
    /* 0x14 */ u8 unk14[0x3C];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
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
    /* 0x80 */ void (*methods[6])();
} Task8001ACC8;

typedef struct Task8001B3A0 {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 state;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14[0x18];
    /* 0x2C */ void (*unk2C)(struct Task8001B3A0 *, s32);
    /* 0x30 */ u8 unk30[8];
    /* 0x38 */ void (*unk38)(struct Task8001B3A0 *);
    /* 0x3C */ u8 unk3C[0x14];
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
    /* 0x0 */ u8 *data;
    /* 0x4 */ s16 cap;
    /* 0x6 */ s16 len;
    /* 0x8 */ s16 pos;
    /* 0xA */ s16 dirty;
} TextBuffer;

typedef struct Unk80019DFC {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 unk1C[0x34];
    /* 0x50 */ u8 *unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ TextBuffer text[6];
    /* 0xA4 */ u16 unkA4;
    /* 0xA6 */ s16 unkA6;
    /* 0xA8 */ s16 unkA8;
    /* 0xAA */ s16 unkAA;
    /* 0xAC */ s16 unkAC;
    /* 0xAE */ s16 unkAE;
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ s16 unkB4;
    /* 0xB6 */ s16 unkB6;
    /* 0xB8 */ u8 unkB8[4];
    /* 0xBC */ s16 unkBC;
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
    /* 0xE8 */ u8 unkE8[0x28];
    /* 0x110 */ void (*methods[25])();
} Unk80019DFC;

typedef struct Unk8001BA7C {
    /* 0x0 */ Unk80019DFC *window;
    /* 0x4 */ struct Task *unk4;
} Unk8001BA7C;

typedef struct Unk80041444 {
    /* 0x0 */ u8 unk0[8];
    /* 0x8 */ u8 unk8;
    /* 0x9 */ u8 unk9;
    /* 0xA */ u8 unkA[2];
} Unk80041444;

typedef struct Unk8003EB68 {
    /* 0x00 */ u16 id;
    /* 0x02 */ u8 unk2[6];
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9[0x4F];
} Unk8003EB68;

typedef struct Unk80048C50Entry {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s32 unk4[4];
} Unk80048C50Entry;

typedef struct Unk628 {
    /* 0x00 */ u8 unk0[0x16];
    /* 0x16 */ u16 items[40];
} Unk628;

typedef struct Unk8004883C {
    /* 0x000 */ u8 unk0[4];
    /* 0x004 */ s32 unk4;
    /* 0x008 */ u8 unk8[0x4C];
    /* 0x054 */ s16 unk54[4];
    /* 0x05C */ Unk80048C50Entry entries[44];
    /* 0x3CC */ u8 unk3CC[0x10];
} Unk8004883C;

typedef struct Unk80048C50 {
    /* 0x000 */ u8 unk0[0x1C];
    /* 0x01C */ s16 stats[19];
    /* 0x042 */ u8 unk42[0xE];
    /* 0x050 */ Unk80048C50Entry unk50[44];
    /* 0x3C0 */ s16 equip[6];
    /* 0x3CC */ u8 unk3CC[0x10];
} Unk80048C50;

typedef struct DrawEntry {
    /* 0x00 */ s32 key;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ struct DrawEntry *next;
} DrawEntry;

/* Double-buffered ordering tables */
typedef struct DrawContext {
    /* 0x00 */ u8 unk0[0x5C];
    /* 0x5C */ u_long *ot[2];
    /* 0x64 */ s32 otLen;
    /* 0x68 */ s32 otShift;
    /* 0x6C */ u8 unk6C[0xC];
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ struct DrawEntry *unk80;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ s32 unk88;
    /* 0x8C */ MATRIX unk8C[2];
    /* 0xCC */ s32 unkCC;
    /* 0xD0 */ MATRIX matrices[2];
} DrawContext;

typedef struct SoundEntry {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s16 vabId;
    /* 0x06 */ s16 numSeqs;
    /* 0x08 */ s16 seqs[8];
} SoundEntry;

typedef struct Unk80051194 {
    /* 0x0000 */ u8 unk0[0x4200];
    /* 0x4200 */ SoundEntry sounds[3];
    /* 0x4248 */ s32 unk4248;
    /* 0x424C */ s32 unk424C;
} Unk80051194;

typedef struct Obj8001E7DC {
    /* 0x00 */ u8 *unk0;
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
    /* 0x28 */ CVECTOR color;
    /* 0x2C */ s32 scaleDirty;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 scaleX;
    /* 0x3C */ s32 scaleY;
    /* 0x40 */ s32 scaleZ;
    /* 0x44 */ u8 unk44[4];
    /* 0x48 */ s16 unk48;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ u8 unk4E[0x22];
    /* 0x70 */ void (*methods[12])();
} Obj8001F22C;

typedef struct Obj8001F8F8 {
    /* 0x0 */ char *(*unk0)();
    /* 0x4 */ s16 (*unk4)();
    /* 0x8 */ void (*unk8)();
} Obj8001F8F8;

typedef struct Obj8001FBE0 {
    /* 0x00 */ u16 w;
    /* 0x02 */ u16 h;
    /* 0x04 */ u8 unk4[4];
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
    /* 0x1A0 */ TaskFuncs funcs; /* D_8004AF58 */
} Unk8004ADB8;

typedef struct Unk80042728 {
    /* 0x00 */ u8 unk0[0x58];
    /* 0x58 */ s16 unk58[8];
} Unk80042728;

/* CD read state */
typedef struct CdReader {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 *unk14;
    /* 0x18 */ u8 loc[4];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 (*unk2C)(void);
} CdReader;

typedef struct Unk80044744 {
    /* 0x000 */ s32 unk0;
    /* 0x004 */ u8 unk4[0x404];
    /* 0x408 */ void (*outOfMemory)(void);
    /* 0x40C */ void (*unk40C)(s32);
    /* 0x410 */ u8 unk410[8];
    /* 0x418 */ void (*unk418)(s32);
    /* 0x41C */ u8 unk41C[8];
    /* 0x424 */ s32 (*unk424)(s32);
} Unk80044744;

typedef struct Unk80017ECC {
    /* 0x00 */ u8 unk0[0x20];
    /* 0x20 */ s32 count;
    /* 0x24 */ s32 *items;
} Unk80017ECC;

typedef struct Task8001C454 {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 state;
    /* 0x10 */ u8 unk10[0x28];
    /* 0x38 */ void (*unk38)(struct Task8001C454 *);
    /* 0x3C */ u8 unk3C[0x14];
    /* 0x50 */ s16 unk50;
    /* 0x52 */ s16 unk52;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ s16 unk56;
    /* 0x58 */ s16 unk58;
    /* 0x5A */ s16 unk5A;
    /* 0x5C */ u8 unk5C[4];
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ u16 unk6C;
    /* 0x6E */ u16 unk6E;
    /* 0x70 */ u8 unk70[0x18];
    /* 0x88 */ s32 unk88;
    /* 0x8C */ s32 unk8C;
    /* 0x90 */ s32 unk90;
    /* 0x94 */ u8 unk94[0x24];
    /* 0xB8 */ s32 unkB8;
} Task8001C454;

typedef struct Unk800554D0 {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 current;
} Unk800554D0;

typedef struct Unk2728 {
    /* 0x00 */ u8 unk0[0x16];
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u8 unk18[0x18];
} Unk2728;

typedef struct Unk2744 {
    /* 0x00 */ u8 unk0[0x20];
    /* 0x20 */ u16 unk20;
    /* 0x22 */ u16 unk22;
    /* 0x24 */ u16 unk24;
    /* 0x26 */ u16 unk26;
    /* 0x28 */ u8 unk28[0x1A];
    /* 0x42 */ s16 unk42[3];
} Unk2744;

/* Memory card state */
typedef struct Unk80047F14 {
    /* 0x00 */ s32 state;
    /* 0x04 */ u8 unk4[0x8C];
    /* 0x90 */ s32 cmd;
    /* 0x94 */ u32 result;
    /* 0x98 */ s32 retries;
    /* 0x9C */ s32 maxRetries;
    /* 0xA0 */ s32 unkA0;
} Unk80047F14;

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
    /* 0x050 */ u8 unk50[0x54];
    /* 0x0A4 */ u8 unkA4[0x11C];
} PadInfo;

typedef struct PadState {
    /* 0x000 */ PadInfo pads[2];
    /* 0x380 */ u8 unk380[0x48];
    /* 0x3C8 */ u8 act[2][6];
    /* 0x3D4 */ u8 unk3D4[2];
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
    /* 0x0034 */ s32 unk34;
    /* 0x0038 */ u8 unk38[0xC];
    /* 0x0044 */ u16 unk44;
    /* 0x0046 */ u16 unk46;
    /* 0x0048 */ s32 playFrames;
    /* 0x004C */ s16 playHours;
    /* 0x004E */ s16 playMinutes;
    /* 0x0050 */ s16 playSeconds;
    /* 0x0052 */ s16 playTimeMaxed;
    /* 0x0054 */ u8 unk54[0x18];
    /* 0x006C */ s32 money;
    /* 0x0070 */ s32 unk70[3];
    /* 0x007C */ s8 unk7C[0x193];
    /* 0x020F */ s8 unk20F[0x193];
    /* 0x03A2 */ s8 itemCounts[0x13D];
    /* 0x04DF */ s8 itemFlags[0x149];
    /* 0x0628 */ Unk628 unk628[3];
    /* 0x075A */ u8 unk75A[2];
    /* 0x075C */ Unk8004883C records[8];
    /* 0x263C */ u8 unk263C[0x80];
    /* 0x26BC */ s32 unk26BC;
    /* 0x26C0 */ s32 unk26C0;
    /* 0x26C4 */ s32 unk26C4;
    /* 0x26C8 */ s32 unk26C8;
    /* 0x26CC */ s8 unk26CC;
    /* 0x26CD */ s8 unk26CD;
    /* 0x26CE */ s8 unk26CE;
    /* 0x26CF */ s8 unk26CF;
    /* 0x26D0 */ u8 unk26D0[0x28];
    /* 0x26F8 */ s32 (*unk26F8)(void);
    /* 0x26FC */ u8 unk26FC[0x10];
    /* 0x270C */ s32 (*unk270C)(s32);
    /* 0x2710 */ u8 unk2710[0x18];
    /* 0x2728 */ void (*unk2728)(s32, struct Unk2728 *);
    /* 0x272C */ u8 unk272C[0x18];
    /* 0x2744 */ struct Unk2744 *(*unk2744)(s32);
} Unk800484E8;

void PadStartCom(void);
void PadStopCom(void);
s32 VSyncCallback(void (*func)(void));

void *func_800144DC(void (*update)(void *), s32 size, s32 arg2);
void *func_800143B4(void (*update)(void *), s32 size, s32 arg2, s32 arg3);
s32 func_80013484(s32 id);
Unk80041444 *func_80013534(s32 id);
void func_80018FEC(struct Unk80019DFC *obj, struct TextBuffer *buf, char *text);
void func_80019360(struct Unk80019DFC *obj, char *text, s32 id, s32 index);
void *CdIntToPos(s32 i, void *p);
short SsUtKeyOn(short vabId, short prog, short tone, short note, short fine, short voll, short volr);
void func_800119AC(void *task);
void func_80011DF0(Task80011FBC *task, s32 fadeOut, s32 duration);
void func_80011E78(struct Task80011FBC *task);
void func_80011FBC(struct Task80011FBC *task);
void func_800126FC(void *task);
s32 func_80013A44(s32);
Slot *func_800139D4(s32 file);
Slot *func_80013A0C(void);
Slot *func_80013AB4(void);
void func_80013C08(s32);
void func_80013CB4(void);
void func_80016860(void);
void SsSepStop(short seq, short sep);
void SsSepSetDecrescendo(short seq, short sep, short vol, long frames);
void SsSeqCalledTbyT(void);
short SsUtKeyOff(short voice, short vabId, short prog, short tone, short note);
s32 func_8001FC68(s32 id);
void func_80016AC8(s32 item, s32 count);
long MemCardSync(long mode, long *cmds, u_long *result);
long MemCardExist(long chan);
long MemCardAccept(long chan);
Resource *func_8001E1A0(DRAWENV *env, s32 arg1);
s32 func_8001D6B4(s32 id);
s32 func_800172E8(s32 slot, s32 id);
void func_8001D718(s32 index);
void func_8001C168(Task8001C454 *task);
void func_80029598(s32);
void func_8001FBE0(Obj8001FBE0 *obj);
void func_80020074(s32, s32);
void func_8001BB68(Task *task);
void func_8001BCCC(Task *task);
s32 *func_80013E34(u32 id);
void func_80013758();
void func_8002DE68(void (*func)());
int CdControlF(u_char com, u_char *param);
void func_80019140(Unk80019DFC *obj, char *text);
void func_80019184(u8 *buf, s32 value);
void func_80016260(u16, u16);
s32 func_80017DDC(s32);
void *func_80017CE8(void);
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
s32 func_8001E7B0(void);
void func_8001E894(Obj8001F22C *obj);
void func_8001E8A0();
void func_8001E8BC();
void func_8001E8D0();
void func_8001E8DC(Resource *res, s32 arg1);
void func_8001E950();
void func_8001F1B4();
void func_8001F1D0(s16 x, s16 y, s16 z);
void func_8001F1EC();
void func_8001F200();
void func_8001F20C(CVECTOR *color);
void func_8001F31C(Obj8001F8F8 *obj);
s32 func_8001F328(s32 *table, s32 index);
s16 func_8001F354();
void func_8001F8F8(Obj8001F8F8 *obj);
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
void *func_80017B20();
void *func_800179C8(u32 size, s32 tag);
void *func_80017A78(u32 size, s32 tag);
s32 func_80016064(u16, u16);
void func_80017FAC(s32, s32);
void func_8001837C(s32, s32, s32, s32);
void *func_8001B2B8(Task8001B3A0 *task, s32 *data);
void func_8001B1D0(Task8001B3A0 *task);
void func_80019C2C(Unk80019DFC *obj);
int func_8002E268(void *buf, int size);
void func_8002DE88(s32 arg0);
s32 func_800151F0(s32 arg0, s32 arg1);
s32 func_8001366C(void);
s32 func_80013880(void);
void func_80013890(void);
void func_8001B864();
Unk80019DFC *func_8001AAB4(s16 id, s16 type, s16 x, s16 y);
int CdPosToInt(void *pos);
void func_8001B314(Task8001B3A0 *task, s32 *data, s32 arg2);
void *func_8001B368(Task8001B3A0 *task);
void func_8001B3A0(Task8001B3A0 *task);
void func_8001B6A8(void *task);
void func_8001C0C4(Task *task);
void func_80020764(struct Task80011FBC *task, s32 *out);
s32 func_80014A10(void);
void func_8008AEB4(s32, s32, s32, s32, s32);

extern Unk8003EB68 D_8003EB68[];
extern char D_800101D8[];
extern char D_800101FC[];
extern char D_80010230[];
extern Funcs80047F04 D_80047F04;
extern Funcs8004ABD8 D_8004ABD8;
extern TaskFuncs D_8004AF58;
extern RandFuncs D_8004D3B0;
extern Funcs8004D708 D_8004D708;
extern SoundFuncs D_800553DC;
extern Funcs800554D8 D_800554D8;
extern s32 (*D_80055418[])(void);
extern Unk80042728 D_80042728;
extern Unk80041444 D_80041444[];
extern u8 **(*D_800427A4)(s32 item);
extern u8 D_800427B4[];
extern s32 D_800483F8[];
extern s32 D_80048420[];
extern s32 D_80048440[];
extern u8 D_80048280[];
extern s32 D_80048284;
extern s32 D_8004ABB8;
extern CdReader D_80044710;
extern Unk80047F14 D_80047F14;
extern u8 *(*D_80044B58)(s32 file);
extern s32 D_8004D760[];
extern s32 D_8004AC44[40];
extern void *D_800100C8;
extern Unk800554D0 D_800554D0;
extern u8 D_8004AC38[][3];
extern s32 D_8004AB28;
extern u8 D_8005C4C0[];
extern u8 D_80048468[][2];
extern s32 D_8004AB24;
extern Slot D_80044748[64];
extern Unk80044744 D_80044744;
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
extern MemManager D_8004AD84;
extern MemBlock *D_8005C2F8;
extern s32 D_8004D774[];
extern MATRIX D_80080A90;
extern MATRIX D_80080AF0;

#endif /* GAME_H */
