#include "psyq.h"

u_long SpuGetReverbVoice(void) {
    return _SpuGetAnyVoice(0xCC, 0xCD);
}

OBJECT_END();
