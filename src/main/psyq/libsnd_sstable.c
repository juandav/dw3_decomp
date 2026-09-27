#include "psyq.h"

extern long D_80080D30;
extern short D_800815B8;
extern short D_800815BA;

void SsSetTableSize(char *table, short s_max, short t_max) {
    int i;
    int j;

    i = s_max;
    D_800815B8 = i;
    D_800815BA = t_max;
    for (i = 0; i < s_max; i++) {
        D_80080D38[i] = &((SeqStruct *)table)[i * t_max];
    }
    for (i = s_max; i < 32; i++) {
        D_80080D30 |= 1 << i;
    }
    for (i = 0; i < D_800815B8; i++) {
        for (j = 0; j < D_800815BA; j++) {
            D_80080D38[i][j].flags = 0;
            D_80080D38[i][j].unk22 = -1;
            D_80080D38[i][j].unk23 = 0;
            D_80080D38[i][j].unk48 = 0;
            D_80080D38[i][j].unk4A = 0;
            D_80080D38[i][j].unk9C = 0;
            D_80080D38[i][j].unkA0 = 0;
            D_80080D38[i][j].unk4C = 0;
            D_80080D38[i][j].unkAC = 0;
            D_80080D38[i][j].unkA8 = 0;
            D_80080D38[i][j].unkA4 = 0;
            D_80080D38[i][j].unk4E = 0;
            D_80080D38[i][j].voll = 0x7F;
            D_80080D38[i][j].volr = 0x7F;
            D_80080D38[i][j].unk5C = 0x7F;
            D_80080D38[i][j].unk5E = 0x7F;
        }
    }
}

OBJECT_END();
