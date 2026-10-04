#include "psyq.h"

typedef struct CardDirEntry {
    long attr;
    long size;
    u_short next;
    char name[22];
} CardDirEntry;

extern u_char D_800823C8[128];
extern CardDirEntry D_80082188[15];
extern long D_80082368[20];
extern char D_800823B8[15];

void bzero(void *p, int n);
void _clr_card_event(void);
long _get_card_event_x(void);
long _get_card_event(void);
long _card_clear(long chan);
long func_8003D648(long chan);

static inline void _card_checksum(u_char *buf) {
    long i;
    u_char sum = 0;

    for (i = 0; i < 127; i++) {
        sum ^= *buf++;
    }
    *buf = sum;
}

static inline long _card_write_block(long chan, long block, u_char *buf) {
    long i = 0;
    long ret = 0;

    _card_checksum(buf);
    do {
        _clr_card_event();
        func_8003D698(chan, block, buf);
        ret = _get_card_event_x();
        if (ret == 0) {
            break;
        }
        if (ret == 4) {
            _clr_card_event();
            _card_clear(chan);
            _get_card_event_x();
        }
    } while (++i < 8);
    return ret;
}

long _card_format2(long chan) {
    long i;
    long ret;
    long load = 0;

    for (i = 0; i < 15; i++) {
        bzero(D_800823C8, 128);
        bzero(&D_80082188[i], 32);
        D_80082188[i].attr = 0xA0;
        D_80082188[i].size = 0;
        D_80082188[i].next = 0xFFFF;
        __builtin_memcpy(D_800823C8, &D_80082188[i], 32);
        ret = _card_write_block(chan, i + 1, D_800823C8);
        if (ret != 0) {
            break;
        }
    }
    if (ret != 0) {
        return ret;
    }
    for (i = 0; i < 20; i++) {
        long *p = &D_80082368[i];

        *p = -1;
        bzero(D_800823C8, 128);
        __builtin_memcpy(D_800823C8, p, 4);
        ret = _card_write_block(chan, i + 16, D_800823C8);
        if (ret != 0) {
            break;
        }
    }
    if (ret != 0) {
        return ret;
    }
    bzero(D_800823C8, 128);
    D_800823C8[0] = 'M';
    D_800823C8[1] = 'C';
    ret = _card_write_block(chan, 0, D_800823C8);
    if (ret != 0) {
        return ret;
    }
    do {
        _clr_card_event();
        func_8003D648(chan);
        ret = _get_card_event();
        if (ret == 0) {
            return 0;
        }
        _clr_card_event();
        _card_clear(chan);
        _get_card_event_x();
    } while (++load < 8);
    return ret;
}

INCLUDE_ASM("main/nonmatchings/psyq/libmcrd_low", _card_create2);

OBJECT_END();
