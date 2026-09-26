#include "psyq.h"

u_long SpuGetNoiseVoice(void) {
    return _SpuGetAnyVoice(0xCA, 0xCB);
}

OBJECT_END();
