#include "psyq.h"

extern long D_8005B9C4;        /* reverb work area offset */
extern SpuRevAttrInternal D_8005B9CC;
extern long D_8005BFB8[];      /* work area start per mode */
extern SpuReverbRegs D_8005BFE8[];
long _SpuIsInAllocateArea_(u_long addr);
void _spu_setReverbAttr(SpuReverbRegs *attr);
long _spu_FsetRXX(long reg, u_long addr, long flag);

static inline void _memcpy(char *dst, char *src, int size) {
    while (size--) {
        *dst++ = *src++;
    }
}

long SpuSetReverbModeParam(SpuReverbAttr *attr) {
    SpuReverbRegs entry;
    u_long mode;
    int restart = 0;
    int setMode = 0;
    int setDelay = 0;
    int clearWA = 0;
    int setFeedback = 0;
    u_long mask = attr->mask;
    int all = attr->mask == 0;

    entry.mask = 0;
    if (all || (mask & SPU_REV_MODE)) {
        mode = attr->mode;
        if (attr->mode & SPU_REV_MODE_CLEAR_WA) {
            mode &= ~SPU_REV_MODE_CLEAR_WA;
            clearWA = 1;
        }
        if (mode >= 10 || _SpuIsInAllocateArea_(D_8005BFB8[mode])) {
            return -1;
        }
        setMode = 1;
        D_8005B9CC.mode = mode;
        D_8005B9C4 = D_8005BFB8[D_8005B9CC.mode];
        _memcpy((char *)&entry, (char *)&D_8005BFE8[D_8005B9CC.mode], sizeof(SpuReverbRegs));
        switch (D_8005B9CC.mode) {
        case SPU_REV_MODE_ECHO:
            D_8005B9CC.feedback = 0x7F;
            D_8005B9CC.delay = 0x7F;
            break;
        case SPU_REV_MODE_DELAY:
            D_8005B9CC.feedback = 0;
            D_8005B9CC.delay = 0x7F;
            break;
        default:
            D_8005B9CC.feedback = 0;
            D_8005B9CC.delay = 0;
            break;
        }
    }
    if (all || (mask & SPU_REV_DELAYTIME)) {
        switch (D_8005B9CC.mode) {
        case SPU_REV_MODE_ECHO:
        case SPU_REV_MODE_DELAY:
            setDelay = 1;
            if (!setMode) {
                _memcpy((char *)&entry, (char *)&D_8005BFE8[D_8005B9CC.mode], sizeof(SpuReverbRegs));
                entry.mask = 0x0C011C00;
            }
            D_8005B9CC.delay = attr->delay;
            entry.param[10] = ((D_8005B9CC.delay << 13) / 0x7F) - entry.param[0];
            entry.param[11] = ((D_8005B9CC.delay << 12) / 0x7F) - entry.param[1];
            entry.param[12] = ((D_8005B9CC.delay << 12) / 0x7F) + entry.param[13];
            entry.param[16] = ((D_8005B9CC.delay << 12) / 0x7F) + entry.param[17];
            entry.param[26] = ((D_8005B9CC.delay << 12) / 0x7F) + entry.param[28];
            entry.param[27] = ((D_8005B9CC.delay << 12) / 0x7F) + entry.param[29];
            break;
        default:
            break;
        }
    }
    if (all || (mask & SPU_REV_FEEDBACK)) {
        switch (D_8005B9CC.mode) {
        case SPU_REV_MODE_ECHO:
        case SPU_REV_MODE_DELAY:
            setFeedback = 1;
            if (!setMode) {
                if (!setDelay) {
                    _memcpy((char *)&entry, (char *)&D_8005BFE8[D_8005B9CC.mode], sizeof(SpuReverbRegs));
                    entry.mask = 0x80;
                } else {
                    entry.mask |= 0x80;
                }
            }
            D_8005B9CC.feedback = attr->feedback;
            entry.param[7] = (D_8005B9CC.feedback * 0x8100) / 0x7F;
            break;
        default:
            break;
        }
    }
    if (setMode) {
        restart = (D_8005BA28[0xD5] >> 7) & 1;
        if (restart) {
            D_8005BA28[0xD5] &= ~0x80;
        }
    }
    if (!setMode) {
        if (all || (mask & SPU_REV_DEPTHL)) {
            D_8005BA28[0xC2] = attr->depth.left;
            D_8005B9CC.depthLeft = attr->depth.left;
        }
        if (all || (mask & SPU_REV_DEPTHR)) {
            D_8005BA28[0xC3] = attr->depth.right;
            D_8005B9CC.depthRight = attr->depth.right;
        }
    } else {
        D_8005BA28[0xC2] = 0;
        D_8005BA28[0xC3] = 0;
        D_8005B9CC.depthLeft = 0;
        D_8005B9CC.depthRight = 0;
    }
    if (setMode || setDelay || setFeedback) {
        _spu_setReverbAttr(&entry);
    }
    if (clearWA) {
        SpuClearReverbWorkArea(D_8005B9CC.mode);
    }
    if (setMode) {
        _spu_FsetRXX(0xD1, D_8005B9C4, 0);
        if (restart) {
            D_8005BA28[0xD5] |= 0x80;
        }
    }
    return 0;
}

OBJECT_END();
