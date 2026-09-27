#include "psyq.h"

extern long D_80080D2C;
extern long D_80080D30;
extern short D_800815B8;
extern short D_800815BA;
void _SsVmFlush(void);
void func_8002F6C8(short sep, short seq);
void _SsSndCrescendo(short sep, short seq);
void _SsSndTempo(short sep, short seq);
void _SsSndPause(short sep, short seq);
void _SsSndReplay(short sep, short seq);

void SsSeqCalledTbyT(void) {
    int i;
    int j;

    if (D_80080D2C == 1) {
        return;
    }
    D_80080D2C = 1;
    _SsVmFlush();
    for (i = 0; i < D_800815B8; i++) {
        if (D_80080D30 & (1 << i)) {
            for (j = 0; j < D_800815BA; j++) {
                if (D_80080D38[i][j].flags & 1) {
                    func_8002F6C8(i, j);
                    if (D_80080D38[i][j].flags & 0x10) {
                        _SsSndCrescendo(i, j);
                    }
                    if (D_80080D38[i][j].flags & 0x20) {
                        _SsSndCrescendo(i, j);
                    }
                    if (D_80080D38[i][j].flags & 0x40) {
                        _SsSndTempo(i, j);
                    }
                    if (D_80080D38[i][j].flags & 0x80) {
                        _SsSndTempo(i, j);
                    }
                }
                if (D_80080D38[i][j].flags & 2) {
                    _SsSndPause(i, j);
                }
                if (D_80080D38[i][j].flags & 8) {
                    _SsSndReplay(i, j);
                }
                if (D_80080D38[i][j].flags & 4) {
                    _SsSndStop(i, j);
                    D_80080D38[i][j].flags = 0;
                }
            }
        }
    }
    D_80080D2C = 0;
}

OBJECT_END();
