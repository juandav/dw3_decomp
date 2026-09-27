#include "psyq.h"

extern long D_8005BFB8[];
extern u_char D_8005BA98[];
void func_8003A218(long event);
long _SpuIsInAllocateArea_(u_long addr);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libspu_s_crwa", SpuClearReverbWorkArea);

OBJECT_END();
