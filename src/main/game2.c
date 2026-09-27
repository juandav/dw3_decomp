#include "game.h"

const char D_800100CC[24] = "BISLPS-99999DMW3-JPN";

const char D_800100E4[6][24] = {
    "BASLUS-01436DMW3-USA",
    "BESLPS-99999DMW3-ENG",
    "BESLPS-99999DMW3-FRA",
    "BESLPS-99999DMW3-ITA",
    "BESLPS-99999DMW3-GER",
    "BESLPS-99999DMW3-SPN",
};

void func_80014884(void) {
    D_80047F14.fileName = (char *)D_800100E4[0];
}

void func_80014898(char *title, CardClut *clut, s32 count, s32 *icons) {
    s32 i;

    if (count >= 1 && count <= 3 && (u32)strlen(title) <= 64) {
        D_80047F14.iconCount = count;
        D_8004AD84.bzero(&D_80047F14.header, sizeof(CardHeader));
        D_80047F14.header.magic[0] = 'S';
        D_80047F14.header.magic[1] = 'C';
        D_80047F14.header.blocks = 4;
        D_80047F14.header.type = D_80047F14.iconCount | 0x10;
        strcpy(D_80047F14.header.title, title);
        D_80047F14.header.clut = *clut;
        for (i = 0; i < D_80047F14.iconCount; i++) {
            D_80047F14.icons[i] = icons[i];
        }
    }
}

s32 func_80014A10(void) {
    long cmds;
    u_long result;
    s32 ret = MemCardSync(1, &cmds, &result);

    if (ret == 1) {
        D_80047F14.cmd = cmds;
        D_80047F14.result = result;
        if (result < 2 || result == 3) {
            D_80047F14.retries = 0;
        } else {
            if (++D_80047F14.retries < D_80047F14.maxRetries) {
                D_80047F14.unkA0 = ret;
                return 0;
            }
            D_80047F14.retries = 0;
            D_80047F14.unkA0 = 0;
        }
    }
    return ret;
}

s32 func_80014AAC(s32 port) {
    switch (D_80047F14.state) {
    case 0:
    default:
        while (MemCardExist(port << 4) == 0) {
            func_80014A10();
        }
        D_80047F14.state = 1;
        break;
    case 1:
        if (func_80014A10() != 0) {
            D_80047F14.state = 0;
            if (D_80047F14.result == 0) {
                return 1;
            }
            return D_80047F14.result + 1;
        }
        if (D_80047F14.unkA0 != 0) {
            D_80047F14.unkA0 = 0;
            while (MemCardExist(port << 4) == 0) {
                func_80014A10();
            }
        }
        break;
    }
    return 0;
}

s32 func_80014B8C(s32 port) {
    switch (D_80047F14.state) {
    case 0:
    default:
        while (MemCardAccept(port << 4) == 0) {
            func_80014A10();
        }
        D_80047F14.state = 2;
        break;
    case 2:
        if (func_80014A10() != 0) {
            D_80047F14.state = 0;
            if (D_80047F14.result == 0) {
                return 1;
            }
            return D_80047F14.result + 1;
        }
        if (D_80047F14.unkA0 != 0) {
            D_80047F14.unkA0 = 0;
            while (MemCardAccept(port << 4) == 0) {
                func_80014A10();
            }
        }
        break;
    }
    return 0;
}

s32 func_80014C6C(s32 port, u8 *buf, s32 size, s32 slot) {
    u8 *dst;

    if (buf == NULL || size == 0) {
        return 1;
    }
    if ((u32)(D_80047F14.iconCount - 1) >= 3) {
        return 1;
    }
    dst = buf;
    switch (D_80047F14.state) {
    case 0:
    default:
        if (func_80014AAC(port) == 0) {
            return 0;
        }
        switch (D_80047F14.result) {
        case 0:
            D_80047F14.progress = 0;
            switch (slot) {
            case 0:
            default:
                D_80047F14.offset = 0;
                break;
            case 1:
                D_80047F14.offset = D_80047F14.iconCount * 128 + 128;
                break;
            case 2:
                D_80047F14.offset = D_80047F14.iconCount * 128 + 128 + D_80047F14.unk310;
                break;
            case 3:
                D_80047F14.offset = D_80047F14.iconCount * 128 + 128 + D_80047F14.unk310 + D_80047F14.unk30C;
                break;
            case 4:
                D_80047F14.offset = D_80047F14.iconCount * 128 + 128 + D_80047F14.unk310 + D_80047F14.unk30C * 2;
                break;
            }
            while (MemCardReadFile(port << 4, D_80047F14.fileName, dst, D_80047F14.offset, 128) == 0) {
                func_80014A10();
            }
            D_80047F14.state = 3;
            break;
        default:
            D_80047F14.state = 0;
            return D_80047F14.result + 1;
        }
        break;
    case 3:
        if (func_80014A10() != 0) {
            switch (D_80047F14.result) {
            case 0:
                D_80047F14.progress += 128;
                if (D_80047F14.progress >= size) {
                    D_80047F14.state = 0;
                    return 1;
                }
                while (1) {
                    if (MemCardReadFile(port << 4, D_80047F14.fileName, dst + D_80047F14.progress, D_80047F14.offset + D_80047F14.progress, 128) != 0) {
                        return 0;
                    }
                    func_80014A10();
                }
            default:
                D_80047F14.state = 0;
                return D_80047F14.result + 1;
            }
        }
        if (D_80047F14.unkA0 != 0) {
            D_80047F14.unkA0 = 0;
            D_80047F14.progress = 0;
            while (MemCardReadFile(port << 4, D_80047F14.fileName, dst, D_80047F14.offset, 128) == 0) {
                func_80014A10();
            }
            return 0;
        }
        break;
    }
    return 0;
}

s32 func_80014F2C(s32 port, u8 *buf, s32 size, s32 slot) {
    u8 *dst;

    if (buf == NULL || size == 0) {
        return 1;
    }
    if ((u32)(D_80047F14.iconCount - 1) >= 3) {
        return 1;
    }
    dst = buf;
    switch (D_80047F14.state) {
    case 0:
    default:
        if (func_80014AAC(port) == 0) {
            return 0;
        }
        switch (D_80047F14.result) {
        case 0:
            D_80047F14.progress = 0;
            switch (slot & 0xFF) {
            case 0:
            default:
                D_80047F14.offset = slot >> 8;
                break;
            case 1:
                D_80047F14.offset = D_80047F14.iconCount * 128 + 128;
                break;
            case 2:
                D_80047F14.offset = D_80047F14.iconCount * 128 + 128 + D_80047F14.unk310;
                break;
            case 3:
                D_80047F14.offset = D_80047F14.iconCount * 128 + 128 + D_80047F14.unk310 + D_80047F14.unk30C;
                break;
            case 4:
                D_80047F14.offset = D_80047F14.iconCount * 128 + 128 + D_80047F14.unk310 + D_80047F14.unk30C * 2;
                break;
            }
            while (MemCardWriteFile(port << 4, D_80047F14.fileName, dst, D_80047F14.offset, 128) == 0) {
                func_80014A10();
            }
            D_80047F14.state = 4;
            break;
        default:
            D_80047F14.state = 0;
            return D_80047F14.result + 1;
        }
        break;
    case 4:
        if (func_80014A10() != 0) {
            switch (D_80047F14.result) {
            case 0:
                D_80047F14.progress += 128;
                if (D_80047F14.progress >= size) {
                    D_80047F14.state = 0;
                    return 1;
                }
                while (1) {
                    if (MemCardWriteFile(port << 4, D_80047F14.fileName, dst + D_80047F14.progress, D_80047F14.offset + D_80047F14.progress, 128) != 0) {
                        return 0;
                    }
                    func_80014A10();
                }
            default:
                D_80047F14.state = 0;
                return D_80047F14.result + 1;
            }
        }
        if (D_80047F14.unkA0 != 0) {
            D_80047F14.unkA0 = 0;
            D_80047F14.progress = 0;
            while (MemCardWriteFile(port << 4, D_80047F14.fileName, dst, D_80047F14.offset, 128) == 0) {
                func_80014A10();
            }
            return 0;
        }
        break;
    }
    return 0;
}

extern s32 D_80048270[];
extern char D_8005C45C[];

s32 func_800151F0(s32 port, s32 cmd) {
    switch (D_80047F14.state) {
    case 0:
    default:
        if (func_80014B8C(port) == 0) {
            return 0;
        }
        switch (D_80047F14.result) {
        case 0:
            D_80047F14.state = 5;
            break;
        case 4:
            if (cmd == 2) {
                D_80047F14.state = 5;
                break;
            }
            D_80047F14.state = 0;
            return 5;
        default:
            D_80047F14.state = 0;
            return D_80047F14.result + 1;
        }
        break;
    case 5:
        if ((D_80047F14.result == 0 && (cmd == 0 || cmd == 1 || cmd == 3)) ||
            (D_80047F14.result == 4 && cmd == 2)) {
            D_8004AD84.bzero(&D_80047F14.fileCount, 0x25C);
            D_80047F14.cmd = D_80048270[cmd];
            switch (cmd) {
            case 0:
            default:
                D_80047F14.result = MemCardGetDirentry(port << 4, D_8005C45C, D_80047F14.files, (long *)&D_80047F14.fileCount, 0, 15);
                break;
            case 1:
                D_80047F14.result = MemCardCreateFile(port << 4, D_80047F14.fileName, 4);
                break;
            case 2:
                D_80047F14.result = MemCardFormat(port << 4);
                break;
            case 3:
                D_80047F14.result = MemCardUnformat(port << 4);
                break;
            }
            if (D_80047F14.result == -1) {
                D_80047F14.result = 8;
            }
        }
        D_80047F14.state = 0;
        if (D_80047F14.result == 0) {
            return 1;
        }
        return D_80047F14.result + 1;
    }
    return 0;
}

s32 func_800153E8(s32 arg0) {
    s32 ret = func_800151F0(arg0, 0);

    if (ret == 1) {
        return 1;
    }
    return ret;
}

s32 func_80015420(s32 arg0) {
    s32 ret = func_800151F0(arg0, 1);

    if (ret == 1) {
        return 1;
    }
    return ret;
}

s32 func_80015458(s32 arg0) {
    s32 ret = func_800151F0(arg0, 2);

    if (ret == 1) {
        return 1;
    }
    return ret;
}

s32 func_80015490(void) {
    return 2;
}

s32 func_80015498(u8 *data, s32 size, char expected) {
    u8 sum = 0;
    s32 i;

    for (i = 0; i < size; i++) {
        sum ^= *data++;
    }
    return ((expected ^ sum) & 0xFF) == 0;
}

u8 func_800154CC(u8 *data, s32 size) {
    u8 sum = 0;
    s32 i;

    for (i = 0; i < size; i++) {
        sum ^= *data++;
    }
    return sum;
}
