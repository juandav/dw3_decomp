#include "psyq.h"

void SsSepPlay(short seq, short sep, char mode, short count) {
    Snd_SetPlayMode(seq, sep, mode, count);
}

OBJECT_END();
