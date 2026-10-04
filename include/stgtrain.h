#ifndef STGTRAIN_H
#define STGTRAIN_H

/* STGTRAIN.PRO: the gyms, where the partners train their stats. The mode
   it was entered from (the gym's stage) picks the gym's sign; the screen
   shows the party, the selected partner's stats and the training menu. */

#include "game.h"

/* The overlay's files: the discs number them differently */
#if VERSION_US
#define STGTRAIN_TEXT 0x105 /* its strings */
#define STGTRAIN_FILE_SPRITES 0x27D
#define STGTRAIN_FILE_IMAGES 0x27E /* a TIM archive */
#elif VERSION_EU
#define STGTRAIN_TEXT (LANGUAGE + 0x10B)
#define STGTRAIN_FILE_SPRITES 0x28C
#define STGTRAIN_FILE_IMAGES 0x28D
#endif
#define STGTRAIN_SPRITES (STGTRAIN_FILE_SPRITES << 16 | 3) /* its sprite bank */

/* A frame of a sprite animation */
typedef struct TrainAnimFrame {
    /* 0x0 */ s16 sprite; /* into the sprite bank */
    /* 0x2 */ u8 duration; /* in ticks of GFX.funcs.getTime */
    /* 0x3 */ u8 unk3;
    /* 0x4 */ s16 x;
    /* 0x6 */ s16 y;
} TrainAnimFrame;

/* A sprite animation: its frames follow the header */
typedef struct TrainAnim {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 frameCount;
    /* 0x4 */ TrainAnimFrame frames[1];
} TrainAnim;

/* A part of a sprite: a rectangle of a texture page. A sprite is a count
   and its parts, and the bank's sprites follow each other. */
typedef struct TrainSpritePart {
    /* 0x00 */ u8 u;
    /* 0x01 */ u8 v;
    /* 0x02 */ u8 x;
    /* 0x03 */ u8 y;
    /* 0x04 */ u16 clut; /* bits 6-14: the CLUT's row; bit 15: semi-transparent */
    /* 0x06 */ u16 tpage; /* bits 0-4: the page's column, 64 pixels each; 5-8: getTPage's abr and tp */
    /* 0x08 */ u16 w;
    /* 0x0A */ u16 h;
    /* 0x0C */ u8 unkC[8];
} TrainSpritePart;

/* A sprite bank, as the animated sprite reads it */
typedef struct TrainSpriteBank {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ u16 unk4;
} TrainSpriteBank;

/* Draws an animated sprite, maybe rotated and scaled (func_80083018) */
typedef struct TrainSprite {
    TASK_HEADER(TrainSprite);
    /* 0x050 */ Layer *layer;
    /* 0x054 */ u_long *ot;
    /* 0x058 */ s32 layerId;
    /* 0x05C */ s32 depth;
    /* 0x060 */ s32 x;
    /* 0x064 */ s32 y;
    /* 0x068 */ s32 imageX;
    /* 0x06C */ s32 imageY;
    /* 0x070 */ s32 clutX;
    /* 0x074 */ s32 clutY;
    /* 0x078 */ s32 flags; /* bit 31: paused; the rest, ended */
    /* 0x07C */ s32 unk7C;
    /* 0x080 */ TrainSpriteBank *bank;
    /* 0x084 */ u16 unk84;
    /* 0x086 */ u16 unk86;
    /* 0x088 */ s32 bankOffset;
    /* 0x08C */ TrainAnim *anim;
    /* 0x090 */ s32 frame;
    /* 0x094 */ s32 frameCount;
    /* 0x098 */ s32 frameTime;
    /* 0x09C */ s32 transformed;
    /* 0x0A0 */ s32 pivotX;
    /* 0x0A4 */ s32 pivotY;
    /* 0x0A8 */ VECTOR scale;
    /* 0x0B8 */ SVECTOR rotation;
    /* 0x0C0 */ MATRIX matrix;
    /* 0x0E0 */ void (*setBank)(struct TrainSprite *sprite, TrainSpriteBank *bank, s32 offset);
    /* 0x0E4 */ void (*setAnim)(struct TrainSprite *sprite, TrainAnim *anim);
    /* 0x0E8 */ void (*setPos)(struct TrainSprite *sprite, s32 x, s32 y);
    /* 0x0EC */ void (*setImagePos)(struct TrainSprite *sprite, s32 x, s32 y);
    /* 0x0F0 */ void (*setLayer)(struct TrainSprite *sprite, s32 layerId, s32 depth);
    /* 0x0F4 */ void (*setClutPos)(struct TrainSprite *sprite, s32 x, s32 y);
    /* 0x0F8 */ void (*setScale)(struct TrainSprite *sprite, s32 x, s32 y, s32 z);
    /* 0x0FC */ void (*setPivot)(struct TrainSprite *sprite, s32 x, s32 y);
    /* 0x100 */ void (*setRotation)(struct TrainSprite *sprite, s16 x, s16 y, s16 z);
    /* 0x104 */ s32 (*getFlags)(struct TrainSprite *sprite);
    /* 0x108 */ void (*setPaused)(struct TrainSprite *sprite, s32 paused);
} TrainSprite;

/* PartnerTotals with its fields named, as the training screen reads it */
typedef struct TrainTotals {
    /* 0x00 */ s16 level;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 hp;
    /* 0x06 */ s16 maxHp;
    /* 0x08 */ s16 mp;
    /* 0x0A */ s16 maxMp;
    /* 0x0C */ s16 stats[6];
    /* 0x18 */ s16 resistances[7];
    /* 0x26 */ s16 boosted[3]; /* stats 0, 1 and 4 are shown in another colour */
    /* 0x2C */ s32 unk2C; /* TrainResult keeps its yes/no cursor here */
} TrainTotals;

/* The training screen's main task (func_800854FC) */
typedef struct TrainScreen {
    TASK_HEADER(TrainScreen);
    /* 0x050 */ s32 layerId;
    /* 0x054 */ s32 depth;
    /* 0x058 */ s32 sign; /* the sprite of the gym, by the mode it came from */
    /* 0x05C */ s32 signPos;
    /* 0x060 */ s32 signTick;
    /* 0x064 */ s32 partyCount;
    /* 0x068 */ s32 partner; /* the one selected */
    /* 0x06C */ s32 cursorShown;
    /* 0x070 */ s32 cursorClut;
    /* 0x074 */ s32 cursorTime;
    /* 0x078 */ s32 unk78;
    /* 0x07C */ s32 unk7C;
    /* 0x080 */ struct {
        s32 frame;
        s32 time;
    } anims[3]; /* the party's sprites */
    /* 0x098 */ s32 frame; /* the selected partner's sprite */
    /* 0x09C */ s32 time;
    /* 0x0A0 */ PanelAnim panels[7];
    /* 0x110 */ void (*showStats)(struct TrainScreen *screen, TrainTotals *before);
} TrainScreen;

/* The children of the training screen */
typedef struct TrainScreenWindows {
    /* 0x00 */ TextWindow *name;
    /* 0x04 */ TextWindow *level[2];
    /* 0x0C */ TextWindow *hp[3];
    /* 0x18 */ TextWindow *mp[3];
    /* 0x24 */ TextWindow *slashes[2];
    /* 0x2C */ TextWindow *stats[6];
    /* 0x44 */ TextWindow *resistances[7];
    /* 0x60 */ TextWindow *unk60[2];
    /* 0x68 */ TextWindow *unk68;
    /* 0x6C */ TextWindow *unk6C;
    /* 0x70 */ struct TrainMenu *menu;
    /* 0x74 */ struct TrainSession *session;
    /* 0x78 */ struct TrainResult *result;
    /* 0x7C */ ScreenFade *fade;
} TrainScreenWindows;

/* The training menu (func_8008AD40) */
typedef struct TrainMenu {
    TASK_HEADER(TrainMenu);
    /* 0x050 */ TrainScreen *screen;
    /* 0x054 */ s32 layerId;
    /* 0x058 */ s32 depth;
    /* 0x05C */ s32 cursorShown;
    /* 0x060 */ s32 cursorClut;
    /* 0x064 */ s32 cursorTime;
    /* 0x068 */ s32 col; /* the cursor's */
    /* 0x06C */ s32 row;
    /* 0x070 */ s32 page;
    /* 0x074 */ s32 arrowShown; /* to the other page */
    /* 0x078 */ s32 arrowClut;
    /* 0x07C */ s32 arrowTime;
    /* 0x080 */ s32 iconFrame; /* the selected training's icon */
    /* 0x084 */ s32 iconTime;
    /* 0x088 */ s32 trainings[2][8]; /* [page][row * 4 + col], -1: none */
    /* 0x0C8 */ PanelAnim panels[4];
    /* 0x108 */ void (*open)(struct TrainMenu *menu);
    /* 0x10C */ void (*close)(struct TrainMenu *menu);
    /* 0x110 */ void (*unk110)(struct TrainMenu *menu);
} TrainMenu;

/* A training session (func_80088CA8) */
typedef struct TrainSession {
    TASK_HEADER(TrainSession);
    /* 0x050 */ TrainScreen *screen;
    /* 0x054 */ s32 layerId;
    /* 0x058 */ s32 depth;
    /* 0x05C */ s32 unk5C; /* the cursor's column, from the screen's unk7C */
    /* 0x060 */ s32 cursorClut;
    /* 0x064 */ s32 cursorTime;
    /* 0x068 */ s32 cursorShown;
    /* 0x06C */ s32 unk6C;
    /* 0x070 */ s32 iconFrame;
    /* 0x074 */ s32 iconTime;
    /* 0x078 */ PanelAnim panels[8];
    /* 0x0F8 */ void (*finish)(struct TrainSession *session);
} TrainSession;

/* The children of a training session */
typedef struct TrainSessionWindows {
    /* 0x00 */ TextWindow *text[3]; /* the message, the training and the intensity */
    /* 0x0C */ TextWindow *intensities[3];
    /* 0x18 */ TextWindow *notice; /* not enough points */
    /* 0x1C */ TextWindow *answers[2]; /* yes, no */
    /* 0x24 */ Cursor *cursor;
} TrainSessionWindows;

/* A task the overlay creates (func_80087744) that does nothing */
typedef struct TrainIdle {
    TASK_HEADER(TrainIdle);
    /* 0x50 */ TrainScreen *screen;
    /* 0x54 */ s32 layerId;
    /* 0x58 */ s32 depth;
    /* 0x5C */ u8 unk5C[0x10];
} TrainIdle;

/* An animated sprite of an image set, as a training shows it
   (func_800897B8): mode 1 idle, 2 scaling, 4 animating, 8 ending */
typedef struct TrainActor {
    TASK_HEADER(TrainActor);
    /* 0x50 */ s32 mode;
    /* 0x54 */ s32 set;
    /* 0x58 */ s32 file; /* of D_8008C344 */
    /* 0x5C */ s32 anim;
    /* 0x60 */ s32 result; /* the training worked */
    /* 0x64 */ s32 scale;
    /* 0x68 */ s32 scaleStep;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 scaleChanged;
    /* 0x74 */ s32 layerId;
    /* 0x78 */ s32 depth;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 pos[4]; /* x, y, clutX, clutY: for loadSet */
    /* 0x90 */ s32 savedX;
    /* 0x94 */ s32 posSet;
    /* 0x98 */ s32 clutSet;
    /* 0x9C */ s32 chance; /* of the training working, in % */
    /* 0xA0 */ s32 unkA0;
    /* 0xA4 */ void (*setPos)(struct TrainActor *actor, s32 x, s32 y);
    /* 0xA8 */ void (*setClutPos)(struct TrainActor *actor, s32 x, s32 y);
    /* 0xAC */ void (*setChance)(struct TrainActor *actor, s32 chance);
    /* 0xB0 */ void (*grow)(struct TrainActor *actor);
    /* 0xB4 */ void (*shrink)(struct TrainActor *actor);
    /* 0xB8 */ void (*play)(struct TrainActor *actor);
    /* 0xBC */ void (*pause)(struct TrainActor *actor);
    /* 0xC0 */ void (*setScale)(struct TrainActor *actor, s32 scale);
    /* 0xC4 */ s32 (*getResult)(struct TrainActor *actor);
    /* 0xC8 */ void (*end)(struct TrainActor *actor);
    /* 0xCC */ u8 unkCC[8];
} TrainActor;

/* The children of a TrainActor */
typedef struct TrainActorSprites {
    /* 0x0 */ TrainSprite *sprite;
    /* 0x4 */ TrainSprite *effect; /* of set 8 */
    /* 0x8 */ void *unk8;
} TrainActorSprites;

/* The results of a training (func_800875E8) */
typedef struct TrainResult {
    TASK_HEADER(TrainResult);
    /* 0x050 */ TrainScreen *screen;
    /* 0x054 */ s32 layerId;
    /* 0x058 */ s32 depth;
    /* 0x05C */ s32 partner;
    /* 0x060 */ s32 training;
    /* 0x064 */ s32 trained[5];
    /* 0x078 */ s32 gains[5];
    /* 0x08C */ s32 losses[5];
    /* 0x0A0 */ s32 modeArg;
    /* 0x0A4 */ TrainTotals before;
    /* 0x0D4 */ s32 unkD4;
    /* 0x0D8 */ s32 unkD8;
    /* 0x0DC */ s32 unkDC;
    /* 0x0E0 */ s32 unkE0;
    /* 0x0E4 */ s32 unkE4;
    /* 0x0E8 */ s32 unkE8;
    /* 0x0EC */ s32 unkEC;
    /* 0x0F0 */ s16 unkF0; /* the slot of the bonus try's sound */
    /* 0x0F2 */ s16 unkF2;
    /* 0x0F4 */ PanelAnim panels[4];
} TrainResult;

/* The children of TrainResult */
typedef struct TrainResultWindows {
    /* 0x00 */ TextWindow *message[2];
    /* 0x08 */ TextWindow *unk8[3];
    /* 0x14 */ Cursor *cursor;
    /* 0x18 */ TrainActor *actor;
} TrainResultWindows;

/* A stat change of a training: base plus a random 0..range-1 */
typedef struct TrainGain {
    /* 0x0 */ s32 base;
    /* 0x4 */ s32 range;
} TrainGain;

/* An entry of D_8008C344: a file and where its image goes */
typedef struct TrainFile {
    /* 0x0 */ s32 file;
    /* 0x4 */ s32 x;
    /* 0x8 */ s32 y;
    /* 0xC */ s32 unkC;
} TrainFile;

/* An image set of the loaded file (func_8008B298) */
typedef struct TrainImageSet {
    /* 0x00 */ s32 id;
    /* 0x04 */ TrainSpriteBank *bank;
    /* 0x08 */ s32 bankOffset;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ TrainAnim *anims[6];
    /* 0x28 */ u8 *images[4];
    /* 0x38 */ s32 imageCount;
    /* 0x3C */ s32 imageX[4];
    /* 0x4C */ s32 imageY;
} TrainImageSet;

/* The header of an image set in the loaded file: offsets into it, then
   two values */
typedef struct TrainSetHeader {
    /* 0x00 */ s32 count; /* of the offsets */
    /* 0x04 */ s32 bank;
    /* 0x08 */ s32 anims[6];
    /* 0x20 */ s32 images[1];
} TrainSetHeader;

/* Where readSet and its helpers read the loaded file */
typedef union TrainCursor {
    s32 *w;
    TrainSetHeader *set;
} TrainCursor;

/* An entry of a gym level's trainings (D_8008B9EC) */
typedef struct TrainEntry {
    /* 0x0 */ s32 id;
    /* 0x4 */ s16 stat; /* 1-5 battle stats, 8-14 resistances */
    /* 0x6 */ s16 other; /* 1-5: lowered, 15 or 16: max HP or MP raised */
} TrainEntry;

/* A training (D_8008C0EC) */
typedef struct TrainInfo {
    /* 0x00 */ s32 name; /* strings of the text file */
    /* 0x04 */ s32 desc;
    /* 0x08 */ s32 icons[4]; /* frames of STGTRAIN_FILE_SPRITES */
} TrainInfo;

/* The overlay's helpers and the file they load (D_8008C4D4) */
typedef struct TrainState {
    /* 0x000 */ s32 tableCount; /* the entries of the last getTable */
    /* 0x004 */ u8 *data; /* the loaded file of D_8008C344 */
    /* 0x008 */ s32 fileIndex;
    /* 0x00C */ TrainImageSet sets[9];
    /* 0x2DC */ TrainInfo *trainings; /* D_8008C0EC */
    /* 0x2E0 */ void (*loadFiles)(void);
    /* 0x2E4 */ void (*startFade)(PanelAnim *fade, s32 fadeIn);
    /* 0x2E8 */ s32 (*updateFade)(PanelAnim *fade);
    /* 0x2EC */ void (*startLerp)(MenuLerp *lerp, s32 from, s32 to, s32 frames);
    /* 0x2F0 */ s32 (*updateLerp)(MenuLerp *lerp);
    /* 0x2F4 */ s32 (*requestFile)(s32 index);
    /* 0x2F8 */ u8 *(*getFile)(void);
    /* 0x2FC */ void (*freeFile)(void);
    /* 0x300 */ s32 (*readSet)(s32 set);
    /* 0x304 */ s32 (*loadSet)(s32 set, s32 *pos);
    /* 0x308 */ s32 (*getFileId)(s32 index);
    /* 0x30C */ s32 (*getFilePos)(s32 index); /* y << 16 | x */
    /* 0x310 */ s32 (*getFileUnkC)(s32 index);
    /* 0x314 */ TrainSpriteBank *(*getBank)(s32 set);
    /* 0x318 */ s32 (*getBankOffset)(s32 set);
    /* 0x31C */ s32 (*getSetUnkC)(s32 set);
    /* 0x320 */ TrainAnim *(*getAnim)(s32 set, s32 i);
    /* 0x324 */ s32 *(*getTable)(s32 index);
    /* 0x328 */ s32 *(*findTableEntry)(s32 index, s32 id);
} TrainState;

extern TrainState D_8008C4D4;

Cursor *createCursor(s16 layerId, s32 depth, s16 x, s16 y);

/* The overlay's data (stgtrain.c) and the functions its objects share */
extern s32 D_8008B72C[8][7];
extern TrainGain D_8008B80C[];
extern TrainGain D_8008B86C[];
extern TrainGain *D_8008B95C[];
extern TrainGain D_8008B998[];
extern s32 D_8008B9E0[]; /* the points each intensity of a training costs */
extern s32 D_8008B9EC[14][16][2];
extern TrainFile D_8008C344[];
extern TrainCursor D_8008C800;
extern TrainCursor D_8008C804;
extern TrainCursor D_8008C808;
extern TrainCursor D_8008C80C;
void func_800828E8(TrainSprite *sprite);
TrainSprite *func_80083018(void);
void func_80083ADC(TrainScreen *screen, TrainTotals *before);
void func_80083F8C(TrainScreen *screen);
void func_800848D0(TrainScreen *screen, TrainScreenWindows *win);
TrainScreen *func_800854FC(void);
ScreenFade *func_80085898(void);
TrainResult *func_800875E8(TrainScreen *screen, s32 partner, s32 training);
TrainSession *func_80088CA8(TrainScreen *screen);
TrainMenu *func_8008AD40(TrainScreen *screen);
s32 func_800859F4(TrainResult *result, s32 stat);
s32 func_80085AF8(TrainResult *result, s32 stat);
void func_80086258(TrainResult *result, TrainResultWindows *win);
void func_800874A0(TrainResult *result, TrainResultWindows *win);
void func_80086340(TrainResult *result);
void func_800867A0(TrainResult *result, TrainResultWindows *win);
void func_8008778C(TrainSession *session, TrainSessionWindows *win);
void func_800878C0(TrainSession *session);
void func_80087E34(TrainSession *session, TrainSessionWindows *win);
void func_80088CFC(TrainActor *actor, TrainActorSprites *sprites);
TrainActor *func_800897B8(s32 set, s32 file, s32 layerId, s32 depth);
void func_80089924(TrainMenu *menu, TextWindow **win, s32 show);
void func_8008AA28(TrainMenu *menu, TextWindow **win);
void func_8008A004(TrainMenu *menu, TextWindow **win);
void func_80089A54(TrainMenu *menu);

#endif /* STGTRAIN_H */
