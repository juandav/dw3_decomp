#include "psyq.h"

/* ProgAtr as the loader fills it: reserved2 holds two SPU addresses */
typedef struct ProgAtrV {
    /* 0x0 */ u_char tones;
    /* 0x1 */ u8 unk1[7];
    /* 0x8 */ u_long reserved1;
    /* 0xC */ u_short reserved2;
    /* 0xE */ u_short reserved3;
} ProgAtrV;

extern short D_80081E78;
extern long D_80081DF8;
extern short D_80081DE2;
extern VabHdr *D_80081D58[16];
extern ProgAtrV *D_80081D18[16];
extern VagAtr *D_80081DA0[16];
extern u_long D_80081E80[16];
extern long D_80081E38[16];

int _spu_getInTransfer(void);
void _spu_setInTransfer(int);

short _SsVabOpenHeadWithMode(unsigned char *addr, short vabId, int (*alloc)(), unsigned long sbaddr) {
    long vagLens[256];
    long i;
    long size;
    short id;
    u_char *p;
    VabHdr *hdr;
    u_long magic;
    u_char vags;
    ProgAtrV *prog;
    u_long spuAddr;
    long len;

    id = 16;
    if (_spu_getInTransfer() == 1) {
        return -1;
    }
    _spu_setInTransfer(1);
    if (vabId >= 16) {
        _spu_setInTransfer(0);
        return -1;
    }
    if (vabId == -1) {
        for (i = 0; i < 16; i++) {
            if (D_80081E20[i] == 0) {
                D_80081E20[i] = 1;
                D_80081E78++;
                id = i;
                break;
            }
        }
    } else if (D_80081E20[vabId] == 0) {
        D_80081E20[vabId] = 1;
        D_80081E78++;
        id = vabId;
    }
    if (id >= 16) {
        _spu_setInTransfer(0);
        return -1;
    }
    p = addr;
    D_80081D58[id] = (VabHdr *)p;
    p += 0x20;
    hdr = (VabHdr *)addr;
    magic = hdr->form;
    D_80081DF8 = 0;
    if (magic >> 8 != ('V' << 16 | 'A' << 8 | 'B')) {
        D_80081E20[id] = 0;
        _spu_setInTransfer(0);
        D_80081E78--;
        return -1;
    }
    if ((magic & 0xFF) == 'p' && hdr->ver >= 5) {
        D_80081DE2 = 128;
    } else {
        D_80081DE2 = 64;
    }
    if (hdr->ps > D_80081DE2) {
        D_80081E20[id] = 0;
        _spu_setInTransfer(0);
        D_80081E78--;
        return -1;
    }
    D_80081D18[id] = (ProgAtrV *)p;
    prog = (ProgAtrV *)p;
    p += D_80081DE2 * 16;
    size = 0;
    for (i = 0; i < D_80081DE2; i++) {
        prog[i].reserved1 = size;
        if (prog[i].tones != 0) {
            size++;
        }
    }
    size = 0;
    D_80081DA0[id] = (VagAtr *)p;
    p += hdr->ps << 9;
    vags = hdr->vs;
    for (i = 0; i < 256; i++) {
        if (i <= vags) {
            len = *(u_short *)p;
            if (hdr->ver >= 5) {
                vagLens[i] = len * 8;
            } else {
                vagLens[i] = len * 4;
            }
            size += vagLens[i];
        }
        p += 2;
    }
    size = (size + 0x3F) & ~0x3F;
    spuAddr = alloc(size, sbaddr, id);
    if (spuAddr == -1) {
        return -1;
    }
    if (spuAddr + size > 0x80000) {
        D_80081E20[id] = 0;
        _spu_setInTransfer(0);
        D_80081E78--;
        return -1;
    }
    D_80081E80[id] = spuAddr;
    size = 0;
    for (i = 0; i <= vags; i++) {
        size += vagLens[i];
        if (!(i & 1)) {
            prog[i / 2].reserved2 = (spuAddr + size) >> 3;
        } else {
            prog[i / 2].reserved3 = (spuAddr + size) >> 3;
        }
    }
    D_80081E38[id] = size;
    D_80081E20[id] = 2;
    return id;
}

OBJECT_END();
