#ifndef GAME_H
#define GAME_H

#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libcd.h>

#include "dw3/task.h"
#include "dw3/heap.h"
#include "dw3/graphics.h"
#include "dw3/files.h"
#include "dw3/pad.h"
#include "dw3/sound.h"
#include "dw3/text.h"
#include "dw3/game_state.h"
#include "dw3/memcard.h"
#include "dw3/menus.h"

/* SDK functions without a PsyQ 4.7 header here, and overlay functions */
void PadStartCom(void);
int PadInitMtap(unsigned char *p1, unsigned char *p2);
void PadInitDirect(unsigned char *p1, unsigned char *p2);
int PadInfoAct(int port, int acno, int term);
int PadSetActAlign(int port, unsigned char *data);
void PadSetAct(int port, unsigned char *data, int len);
void func_800345B8(void);
void SsVabClose(short vabId);
void func_80030198(short seq);
int PadInfoMode(int port, int term, int offs);
int PadSetMainMode(int port, int offs, int lock);
void PadStopCom(void);
s32 VSyncCallback(void (*func)(void));
short SsUtKeyOn(short vabId, short prog, short tone, short note, short fine, short voll, short volr);
void SsSepStop(short seq, short sep);
void SsSepSetDecrescendo(short seq, short sep, short vol, long frames);
void SsSeqCalledTbyT(void);
short SsUtKeyOff(short voice, short vabId, short prog, short tone, short note);
long MemCardSync(long mode, long *cmds, u_long *result);
long MemCardExist(long chan);
long MemCardAccept(long chan);
long MemCardCreateFile(long chan, char *file, long blocks);
long MemCardFormat(long chan);
long MemCardReadFile(long chan, char *file, void *adrs, long ofs, long bytes);
long MemCardWriteFile(long chan, char *file, void *adrs, long ofs, long bytes);
long MemCardUnformat(long chan);
long MemCardGetDirentry(long chan, char *name, CardDirEntry *dir, long *files, long ofs, long max);
void func_80029598(s32);
void func_8002DE68(void (*func)());
int CdControlF(u_char com, u_char *param);
int strlen(char *);
char *strcpy(char *dst, char *src);
void *memcpy(void *, void *, int);
int func_8002E268(void *buf, int size);
void func_8002DE88(s32 arg0);
void func_8008AEB4(s32, s32, s32, s32, s32);

#endif /* GAME_H */
