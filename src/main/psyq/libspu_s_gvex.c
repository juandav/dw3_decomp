#include "psyq.h"

void SpuGetVoiceEnvelope(int vNum, short *envx) {
    *envx = D_8005BA28[vNum * 8 + 6];
}

OBJECT_END();
