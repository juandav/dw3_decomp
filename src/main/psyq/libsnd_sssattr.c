#include "psyq.h"

void SsSetSerialAttr(char s_num, char attr, char mode) {
    SpuCommonAttr c;

    if (s_num == SS_SERIAL_A) {
        if (attr == SS_MIX) {
            c.mask = SPU_COMMON_CDMIX;
            c.cd.mix = mode;
        }
        if (attr == SS_REV) {
            c.mask = SPU_COMMON_CDREV;
            c.cd.reverb = mode;
        }
    }
    if (s_num == SS_SERIAL_B) {
        if (attr == SS_MIX) {
            c.mask = SPU_COMMON_EXTMIX;
            c.ext.mix = mode;
        }
        if (attr == SS_REV) {
            c.mask = SPU_COMMON_EXTREV;
            c.ext.reverb = mode;
        }
    }
    SpuSetCommonAttr(&c);
}

OBJECT_END();
