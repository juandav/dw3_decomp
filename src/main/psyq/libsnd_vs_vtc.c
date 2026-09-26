#include "psyq.h"

short SsVabTransCompleted(short flag) {
    return SpuIsTransferCompleted(flag);
}

OBJECT_END();
