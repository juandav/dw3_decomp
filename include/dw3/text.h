#ifndef DW3_TEXT_H
#define DW3_TEXT_H

/* Text windows, the font and the message boxes (text_window.c) */

#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "dw3/task.h"
#include "dw3/graphics.h"

/*
 * A menu cursor: a text window showing one of the CURSOR_FRAMES glyphs.
 * It waits idleDelay vsyncs, then plays the five frames (substate 1) at
 * frameDelay vsyncs each.
 */
typedef struct Cursor {
    TASK_HEADER(Cursor);
    /* 0x50 */ s32 layerId;
    /* 0x54 */ s32 depth;
    /* 0x58 */ s32 x;
    /* 0x5C */ s32 y;
    /* 0x60 */ s32 palette;
    /* 0x64 */ s32 visible;
    /* 0x68 */ s32 dirty;
    /* 0x6C */ s32 frame;
    /* 0x70 */ s32 time;
    /* 0x74 */ s32 idleDelay;
    /* 0x78 */ s32 frameDelay;
    /* 0x7C */ s32 still; /* stay on frame 0 */
    /* 0x80 */ void (*setVisible)(); /* (cursor, visible) */
    /* 0x84 */ void (*setPos)(); /* (cursor, x, y) */
    /* 0x88 */ void (*setPalette)();
    /* 0x8C */ void (*setIdleDelay)();
    /* 0x90 */ void (*setFrameDelay)();
    /* 0x94 */ void (*setStill)();
} Cursor;

/*
 * The frame of a message box: two halves of the bottom panel that grow from
 * the sides (substate 0), stay with a "next" arrow when showArrow is set
 * (substate 1), and fade out through five palette rows (substate 2).
 */
typedef struct MessageBoxFrame {
    TASK_HEADER(MessageBoxFrame);
    /* 0x50 */ s32 layerId;
    /* 0x54 */ s32 time;
    /* 0x58 */ s32 fadeRow;
    /* 0x5C */ s32 showArrow;
    /* 0x60 */ s32 arrowTime;
    /* 0x64 */ s32 arrowFrame;
    /* 0x68 */ s16 scale;
    /* 0x6A */ s16 scaleStep;
} MessageBoxFrame;

/* The children of a TalkBox */
typedef struct TalkBoxChildren {
    /* 0x00 */ struct ZoomBox *zoomBoxes[3];
    /* 0x0C */ struct TextWindow *windows[2]; /* speaker, message */
    /* 0x14 */ struct TalkBoxFrame *frame;
} TalkBoxChildren;

/*
 * A box with a speaker's name and a message (createTalkBox). It opens and
 * closes with three ZoomBox outlines (substate 0 opens, 1 closes) and
 * type (0-3) picks one of the TALK_BOX_LAYOUTS.
 */
typedef struct TalkBox {
    TASK_HEADER(TalkBox);
    /* 0x50 */ s32 strings;
    /* 0x54 */ s32 layerId;
    /* 0x58 */ s32 type;
    /* 0x5C */ s32 timer;
    /* 0x60 */ s16 x;
    /* 0x62 */ s16 y;
    /* 0x64 */ s16 w;
    /* 0x66 */ s16 h;
    /* 0x68 */ void (*setPos)(struct TalkBox *box, s32 x, s32 y);
} TalkBox;

/* Draws a TalkBox's panel */
typedef struct TalkBoxFrame {
    TASK_HEADER(TalkBoxFrame);
    /* 0x50 */ TalkBox *parent;
    /* 0x54 */ s32 arrowFrame;
    /* 0x58 */ s32 arrowTime;
    /* 0x5C */ u8 showArrow;
} TalkBoxFrame;

/*
 * Expands "RLEN" data (a run-length encoding: a byte n < 0x80 copies n
 * bytes, n | 0x80 repeats the next byte n times, 0 ends), all at once
 * (run) or chunkSize bytes a frame (start, then substate 1 until done).
 */
typedef struct Decompressor {
    TASK_HEADER(Decompressor);
    /* 0x50 */ s32 *data;
    /* 0x54 */ s32 *begin;
    /* 0x58 */ s32 compressed;
    /* 0x5C */ s32 size;
    /* 0x60 */ s32 bufferSize;
    /* 0x64 */ void *buffer;
    /* 0x68 */ s32 *src;
    /* 0x6C */ void *dst;
    /* 0x70 */ s32 chunkSize;
    /* 0x74 */ void (*run)();
    /* 0x78 */ void *(*getData)();
    /* 0x7C */ void (*start)();
    /* 0x80 */ void (*free)();
} Decompressor;

typedef struct TextBuffer {
    /* 0x0 */ u8 *data;
    /* 0x4 */ s16 cap;
    /* 0x6 */ s16 len;
    /* 0x8 */ s16 pos;
    /* 0xA */ s16 sjis; /* two bytes per character; else font codes */
} TextBuffer;

/*
 * A text window (createTextWindow): up to six text buffers (0 is shown, 1-5
 * are "work" buffers that control code 5 inserts), drawn glyph by glyph as
 * sprites, optionally typed out one character every typeDelay frames.
 * Control codes are 0x02 <code> <args> (TEXT_CODE_HANDLERS). The game's
 * own debug strings call these "messages" (STR_NULL_MESSAGE...).
 * States: 1 shows the text, 2 waits (substate 0: `step` frames,
 * substate 1: button TEXT_WAIT_BUTTONS[step], then patches the code at
 * `counter` so that it does not wait again), 3 frees the buffers.
 */
typedef struct TextWindow {
    TASK_HEADER(TextWindow);
    /* 0x50 */ u8 *style;
    /* 0x54 */ s32 layerId;
    /* 0x58 */ s32 depth;
    /* 0x5C */ TextBuffer text[6];
    /* 0xA4 */ u16 visibleEnd;
    /* 0xA6 */ s16 start;
    /* 0xA8 */ s16 typeTimer;
    /* 0xAA */ s16 typeDelay;
    /* 0xAC */ s16 texX;
    /* 0xAE */ s16 texY;
    /* 0xB0 */ s16 x;
    /* 0xB2 */ s16 y;
    /* 0xB4 */ s16 spacingX;
    /* 0xB6 */ s16 spacingY;
    /* 0xB8 */ s16 cursorX;
    /* 0xBA */ u16 cursorY;
    /* 0xBC */ s16 alignWidth;
    /* 0xBE */ u8 blend;
    /* 0xBF */ u8 lines;
    /* 0xC0 */ u8 palette;
    /* 0xC1 */ u8 visible;
    /* 0xC2 */ u8 fixedSpacing;
    /* 0xC3 */ u8 finished;
    /* 0xC4 */ u8 unkC4;
    /* 0xC5 */ u8 unkC5[3];
    /* 0xC8 */ s32 typeSound;
    /* 0xCC */ s32 scaled;
    /* 0xD0 */ s32 scaleX;
    /* 0xD4 */ s32 scaleY;
    /* 0xD8 */ s32 scaleZ;
    /* 0xDC */ s32 unkDC;
    /* 0xE0 */ s32 pivotX;
    /* 0xE4 */ s32 pivotY;
    /* 0xE8 */ SVECTOR rot;
    /* 0xF0 */ MATRIX mat;
    /* 0x110 */ void (*setText)();
    /* 0x114 */ void (*setString)();
    /* 0x118 */ void (*setNumber)();
    /* 0x11C */ void (*setSubText)();
    /* 0x120 */ void (*setSubString)();
    /* 0x124 */ void (*draw)();
    /* 0x128 */ void (*showPage)();
    /* 0x12C */ void (*setStyle)();
    /* 0x130 */ void (*setTypeDelay)();
    /* 0x134 */ void (*setPos)(struct TextWindow *obj, s16 x, s16 y);
    /* 0x138 */ void (*setPalette)(struct TextWindow *obj, u8 arg);
    /* 0x13C */ void (*setBlend)();
    /* 0x140 */ void (*setSpacing)();
    /* 0x144 */ void (*setVisible)(struct TextWindow *obj, u8 arg);
    /* 0x148 */ void (*setRightAlign)();
    /* 0x14C */ void (*insertPlayerName)();
    /* 0x150 */ void (*setTypeSound)();
    /* 0x154 */ void (*setScale)();
    /* 0x158 */ void (*setPivot)();
    /* 0x15C */ void (*setDepth)();
    /* 0x160 */ void (*setLines)();
    /* 0x164 */ void (*setUnkC4)();
    /* 0x168 */ s32 (*isFinished)();
    /* 0x16C */ s32 (*isVisible)();
    /* 0x170 */ s32 (*isWaitingForButton)();
} TextWindow;

/* Where the parts of a TalkBox go, for each of its four types */
typedef struct TalkBoxLayout {
    /* 0x00 */ s32 sprite;
    /* 0x04 */ DVECTOR parts; /* four offsets (with the next fields) */
    /* 0x08 */ u16 zoomX;
    /* 0x0A */ u16 zoomY;
    /* 0x0C */ DVECTOR panel;
    /* 0x10 */ DVECTOR unk10;
    /* 0x14 */ s16 nameX;
    /* 0x16 */ s16 nameY;
    /* 0x18 */ s16 textX;
    /* 0x1A */ s16 textY;
    /* 0x1C */ s16 arrowX;
    /* 0x1E */ s16 arrowY;
} TalkBoxLayout;

/*
 * The font (FONT): three text styles, the length of each control code, and
 * decode(), which turns the next character into kind << 8 | value:
 * kind 0 a glyph (value - 4 indexes glyphs), 1 an icon, 2 a control code,
 * 3 a missing character, 4 the end.
 */
typedef struct Font {
    /* 0x0 */ u8 *styles; /* TextStyle[4], style 0 unused */
    /* 0x4 */ s32 *codeLengths;
    /* 0x8 */ void (*load)(); /* FONT_LOAD */
    /* 0xC */ s16 (*decode)(); /* FONT_DECODE: (text, sjis, style) */
} Font;

/* Maps a Shift-JIS character to a glyph */
typedef struct GlyphMap {
    /* 0x0 */ u16 code;
    /* 0x2 */ u8 index;
    /* 0x3 */ u8 pad;
} GlyphMap;

typedef struct TextStyle {
    /* 0x00 */ u8 blend; /* 0xFF: opaque */
    /* 0x01 */ s8 lineHeight;
    /* 0x02 */ u8 unk2[2];
    /* 0x04 */ s32 glyphs; /* Glyph[] */
    /* 0x08 */ s32 icons; /* Glyph[] */
    /* 0x0C */ GlyphMap *sjisMap;
    /* 0x10 */ GlyphMap *iconMap;
    /* 0x14 */ s16 glyphCount;
    /* 0x16 */ s16 iconCount;
} TextStyle;

/* One glyph of a font sheet */
typedef struct Glyph {
    /* 0x0 */ u8 page; /* 0xFF: missing glyph */
    /* 0x1 */ u8 u;
    /* 0x2 */ u8 v;
    /* 0x3 */ u8 clutX;
    /* 0x4 */ u8 clutY;
    /* 0x5 */ u8 w;
    /* 0x6 */ u8 h;
    /* 0x7 */ s8 dx;
    /* 0x8 */ s8 dy;
    /* 0x9 */ u8 advance;
    /* 0xA */ u8 unkA;
} Glyph;

/* Drawing state shared with the control-code handlers */
typedef struct TextDraw {
    /* 0x00 */ void *prim;
    /* 0x04 */ Layer *layer;
    /* 0x08 */ u_long *ot;
    /* 0x0C */ Glyph *glyph;
    /* 0x10 */ s32 pageStart;
    /* 0x14 */ s16 code; /* from Font.decode */
    /* 0x16 */ s16 kind;
    /* 0x18 */ s16 lineCount;
} TextDraw;

/* The children of a message box (createMessageBox) */
typedef struct MessageBox {
    /* 0x0 */ struct TextWindow *window;
    /* 0x4 */ struct MessageBoxFrame *frame;
} MessageBox;

/* A blue rectangle outline that zooms in (or out, when closing) around a TalkBox */
typedef struct ZoomBox {
    TASK_HEADER(ZoomBox);
    /* 0x50 */ s16 left;
    /* 0x52 */ s16 top;
    /* 0x54 */ s16 x; /* the zoom's centre */
    /* 0x56 */ s16 y;
    /* 0x58 */ s16 w;
    /* 0x5A */ s16 h;
    /* 0x5C */ s16 speed;
    /* 0x5E */ u8 unk5E[2];
    /* 0x60 */ s32 zoom; /* 0-0x1000 */
    /* 0x64 */ s32 layerId;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ u16 offsetX;
    /* 0x6E */ u16 offsetY;
    /* 0x70 */ VECTOR scale;
    /* 0x80 */ SVECTOR rot;
    /* 0x88 */ s32 unk88;
    /* 0x8C */ s32 unk8C;
    /* 0x90 */ s32 unk90;
    /* 0x94 */ u8 unk94[4];
    /* 0x98 */ MATRIX matrix;
    /* 0xB8 */ s32 closing;
    /* 0xBC */ s32 opened;
} ZoomBox;

void drawMessageBoxFrame(struct MessageBoxFrame *task);
void drawMessageBoxArrow(struct MessageBoxFrame *task);
void setTextBuffer(struct TextWindow *obj, struct TextBuffer *buf, char *text);
void textWindowSetSubString(struct TextWindow *obj, char *text, s32 id, s32 index);
void drawZoomBox(ZoomBox *task);
void drawTalkBoxArrow(struct TalkBoxFrame *task);
void drawTalkBoxFrame(struct TalkBoxFrame *task);
void textWindowSetText(TextWindow *obj, char *text);
void formatNumber(u8 *buf, s32 value);
void textWindowSetTypeDelay(TextWindow *, s32);
void *decompressorRun(Decompressor *task, s32 *data);
void decompressorStep(Decompressor *task);
void textWindowShowPage(TextWindow *obj);
void textWindowDraw(struct TextWindow *obj);
void updateMessageBox(struct MessageBoxFrame *task, struct MessageBox *data);
s32 processTextChar(TextWindow *obj, TextBuffer *text, TextDraw *wait, s16 *pos);
void updateZoomBox(struct ZoomBox *task);
TextWindow *createTextWindow(s16 id, s16 type, s16 x, s16 y);
void decompressorStart(Decompressor *task, s32 *data, s32 arg2);
void *decompressorGetData(Decompressor *task);
void updateDecompressor(Decompressor *task);
void updateMessageBoxFrame(struct MessageBoxFrame *task);
void updateTalkBoxFrame(Task *task);

extern char STR_NULL_MESSAGE[];
extern char STR_BAD_DIGIT_BUFFER[];
extern char STR_BAD_EXT_BUFFER[];
extern char STR_MESSAGE_NOT_SET[];
extern s16 (*FONT_DECODE)(u8 *text, s32 arg1, u8 *arg2, s32 pos);
extern char *CURSOR_FRAMES[];
extern s32 TEXT_WAIT_BUTTONS[];
extern Font FONT;
extern TalkBoxLayout TALK_BOX_LAYOUTS[];

#endif /* DW3_TEXT_H */
