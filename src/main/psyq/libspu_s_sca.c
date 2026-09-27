#include "psyq.h"

void SpuSetCommonAttr(SpuCommonAttr *attr) {
    u_short model;
    u_short moder;
    u_short voll;
    u_short volr;
    u_long mask;
    long all;
    u_short cnt;

    voll = 0;
    volr = 0;
    mask = attr->mask;
    all = attr->mask == 0;

    if (all || (mask & SPU_COMMON_MVOLL)) {
        if (all || (mask & SPU_COMMON_MVOLMODEL)) {
            switch (attr->mvolmode.left) {
            case 1:
                model = 0x8000;
                break;
            case 2:
                model = 0x9000;
                break;
            case 3:
                model = 0xA000;
                break;
            case 4:
                model = 0xB000;
                break;
            case 5:
                model = 0xC000;
                break;
            case 6:
                model = 0xD000;
                break;
            case 7:
                model = 0xE000;
                break;
            case 0:
                voll = attr->mvol.left;
                model = 0;
                break;
            default:
                voll = attr->mvol.left;
                model = 0;
                break;
            }
        } else {
            voll = attr->mvol.left;
            model = 0;
        }
        if (model != 0) {
            if (attr->mvol.left >= 0x80) {
                voll = 0x7F;
            } else if (attr->mvol.left < 0) {
                voll = 0;
            } else {
                voll = attr->mvol.left;
            }
        }
        voll &= 0x7FFF;
        D_8005BA28[0xC0] = voll | model;
    }
    if (all || (mask & SPU_COMMON_MVOLR)) {
        if (all || (mask & SPU_COMMON_MVOLMODER)) {
            switch (attr->mvolmode.right) {
            case 1:
                moder = 0x8000;
                break;
            case 2:
                moder = 0x9000;
                break;
            case 3:
                moder = 0xA000;
                break;
            case 4:
                moder = 0xB000;
                break;
            case 5:
                moder = 0xC000;
                break;
            case 6:
                moder = 0xD000;
                break;
            case 7:
                moder = 0xE000;
                break;
            case 0:
                volr = attr->mvol.right;
                moder = 0;
                break;
            default:
                volr = attr->mvol.right;
                moder = 0;
                break;
            }
        } else {
            volr = attr->mvol.right;
            moder = 0;
        }
        if (moder != 0) {
            if (attr->mvol.right >= 0x80) {
                volr = 0x7F;
            } else if (attr->mvol.right < 0) {
                volr = 0;
            } else {
                volr = attr->mvol.right;
            }
        }
        volr &= 0x7FFF;
        D_8005BA28[0xC1] = volr | moder;
    }
    if (all || (mask & SPU_COMMON_CDVOLL)) {
        D_8005BA28[0xD8] = attr->cd.volume.left;
    }
    if (all || (mask & SPU_COMMON_CDVOLR)) {
        D_8005BA28[0xD9] = attr->cd.volume.right;
    }
    if (all || (mask & SPU_COMMON_EXTVOLL)) {
        D_8005BA28[0xDA] = attr->ext.volume.left;
    }
    if (all || (mask & SPU_COMMON_EXTVOLR)) {
        D_8005BA28[0xDB] = attr->ext.volume.right;
    }
    if (all || (mask & SPU_COMMON_CDREV)) {
        if (attr->cd.reverb == 0) {
            cnt = D_8005BA28[0xD5];
            cnt &= ~4;
            D_8005BA28[0xD5] = cnt;
        } else {
            cnt = D_8005BA28[0xD5];
            cnt |= 4;
            D_8005BA28[0xD5] = cnt;
        }
    }
    if (all || (mask & SPU_COMMON_CDMIX)) {
        if (attr->cd.mix == 0) {
            cnt = D_8005BA28[0xD5];
            cnt &= ~1;
            D_8005BA28[0xD5] = cnt;
        } else {
            cnt = D_8005BA28[0xD5];
            cnt |= 1;
            D_8005BA28[0xD5] = cnt;
        }
    }
    if (all || (mask & SPU_COMMON_EXTREV)) {
        if (attr->ext.reverb == 0) {
            cnt = D_8005BA28[0xD5];
            cnt &= ~8;
            D_8005BA28[0xD5] = cnt;
        } else {
            cnt = D_8005BA28[0xD5];
            cnt |= 8;
            D_8005BA28[0xD5] = cnt;
        }
    }
    if (all || (mask & SPU_COMMON_EXTMIX)) {
        if (attr->ext.mix == 0) {
            cnt = D_8005BA28[0xD5];
            cnt &= ~2;
            D_8005BA28[0xD5] = cnt;
        } else {
            cnt = D_8005BA28[0xD5];
            cnt |= 2;
            D_8005BA28[0xD5] = cnt;
        }
    }
}

OBJECT_END();
