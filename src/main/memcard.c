#include "game.h"

const char SAVE_FILE_NAME_JP[24] = "BISLPS-99999DMW3-JPN";

const char SAVE_FILE_NAMES[6][24] = {
    "BASLUS-01436DMW3-USA",
    "BESLPS-99999DMW3-ENG",
    "BESLPS-99999DMW3-FRA",
    "BESLPS-99999DMW3-ITA",
    "BESLPS-99999DMW3-GER",
    "BESLPS-99999DMW3-SPN",
};

/* The US release saves as BASLUS-01436DMW3-USA */
void setSaveFileName(void) {
    MEMCARD.fileName = (char *)SAVE_FILE_NAMES[0];
}

/* The save file header: title (Shift-JIS), icon CLUT and 1-3 icon frames */
void setSaveHeader(char *title, CardClut *clut, s32 count, s32 *icons) {
    s32 i;

    if (count >= 1 && count <= 3 && (u32)strlen(title) <= 64) {
        MEMCARD.iconCount = count;
        HEAP.zero(&MEMCARD.header, sizeof(CardHeader));
        MEMCARD.header.magic[0] = 'S';
        MEMCARD.header.magic[1] = 'C';
        MEMCARD.header.blocks = 4;
        MEMCARD.header.type = MEMCARD.iconCount | 0x10;
        strcpy(MEMCARD.header.title, title);
        MEMCARD.header.clut = *clut;
        for (i = 0; i < MEMCARD.iconCount; i++) {
            MEMCARD.icons[i] = icons[i];
        }
    }
}

/* MemCardSync, retrying a failed command up to maxRetries times */
s32 syncMemCard(void) {
    long cmds;
    u_long result;
    s32 ret = MemCardSync(1, &cmds, &result);

    if (ret == 1) {
        MEMCARD.cmd = cmds;
        MEMCARD.result = result;
        if (result < 2 || result == 3) {
            MEMCARD.retries = 0;
        } else {
            if (++MEMCARD.retries < MEMCARD.maxRetries) {
                MEMCARD.restart = ret;
                return 0;
            }
            MEMCARD.retries = 0;
            MEMCARD.restart = 0;
        }
    }
    return ret;
}

s32 checkMemCard(s32 port) {
    switch (MEMCARD.state) {
    case 0:
    default:
        while (MemCardExist(port << 4) == 0) {
            syncMemCard();
        }
        MEMCARD.state = 1;
        break;
    case 1:
        if (syncMemCard() != 0) {
            MEMCARD.state = 0;
            if (MEMCARD.result == 0) {
                return 1;
            }
            return MEMCARD.result + 1;
        }
        if (MEMCARD.restart != 0) {
            MEMCARD.restart = 0;
            while (MemCardExist(port << 4) == 0) {
                syncMemCard();
            }
        }
        break;
    }
    return 0;
}

s32 acceptMemCard(s32 port) {
    switch (MEMCARD.state) {
    case 0:
    default:
        while (MemCardAccept(port << 4) == 0) {
            syncMemCard();
        }
        MEMCARD.state = 2;
        break;
    case 2:
        if (syncMemCard() != 0) {
            MEMCARD.state = 0;
            if (MEMCARD.result == 0) {
                return 1;
            }
            return MEMCARD.result + 1;
        }
        if (MEMCARD.restart != 0) {
            MEMCARD.restart = 0;
            while (MemCardAccept(port << 4) == 0) {
                syncMemCard();
            }
        }
        break;
    }
    return 0;
}

/* Reads a section of the save: 0 header, 1 info, 2-4 data (128 bytes a call) */
s32 readSave(s32 port, u8 *buf, s32 size, s32 section) {
    u8 *dst;

    if (buf == NULL || size == 0) {
        return 1;
    }
    if ((u32)(MEMCARD.iconCount - 1) >= 3) {
        return 1;
    }
    dst = buf;
    switch (MEMCARD.state) {
    case 0:
    default:
        if (checkMemCard(port) == 0) {
            return 0;
        }
        switch (MEMCARD.result) {
        case 0:
            MEMCARD.progress = 0;
            switch (section) {
            case 0:
            default:
                MEMCARD.offset = 0;
                break;
            case 1:
                MEMCARD.offset = MEMCARD.iconCount * 128 + 128;
                break;
            case 2:
                MEMCARD.offset = MEMCARD.iconCount * 128 + 128 + MEMCARD.infoSize;
                break;
            case 3:
                MEMCARD.offset = MEMCARD.iconCount * 128 + 128 + MEMCARD.infoSize + MEMCARD.dataSize;
                break;
            case 4:
                MEMCARD.offset = MEMCARD.iconCount * 128 + 128 + MEMCARD.infoSize + MEMCARD.dataSize * 2;
                break;
            }
            while (MemCardReadFile(port << 4, MEMCARD.fileName, dst, MEMCARD.offset, 128) == 0) {
                syncMemCard();
            }
            MEMCARD.state = 3;
            break;
        default:
            MEMCARD.state = 0;
            return MEMCARD.result + 1;
        }
        break;
    case 3:
        if (syncMemCard() != 0) {
            switch (MEMCARD.result) {
            case 0:
                MEMCARD.progress += 128;
                if (MEMCARD.progress >= size) {
                    MEMCARD.state = 0;
                    return 1;
                }
                while (1) {
                    if (MemCardReadFile(port << 4, MEMCARD.fileName, dst + MEMCARD.progress, MEMCARD.offset + MEMCARD.progress, 128) != 0) {
                        return 0;
                    }
                    syncMemCard();
                }
            default:
                MEMCARD.state = 0;
                return MEMCARD.result + 1;
            }
        }
        if (MEMCARD.restart != 0) {
            MEMCARD.restart = 0;
            MEMCARD.progress = 0;
            while (MemCardReadFile(port << 4, MEMCARD.fileName, dst, MEMCARD.offset, 128) == 0) {
                syncMemCard();
            }
            return 0;
        }
        break;
    }
    return 0;
}

/* Writes a section (as readSave; section 0 takes the offset from bits 8 and up) */
s32 writeSave(s32 port, u8 *buf, s32 size, s32 section) {
    u8 *dst;

    if (buf == NULL || size == 0) {
        return 1;
    }
    if ((u32)(MEMCARD.iconCount - 1) >= 3) {
        return 1;
    }
    dst = buf;
    switch (MEMCARD.state) {
    case 0:
    default:
        if (checkMemCard(port) == 0) {
            return 0;
        }
        switch (MEMCARD.result) {
        case 0:
            MEMCARD.progress = 0;
            switch (section & 0xFF) {
            case 0:
            default:
                MEMCARD.offset = section >> 8;
                break;
            case 1:
                MEMCARD.offset = MEMCARD.iconCount * 128 + 128;
                break;
            case 2:
                MEMCARD.offset = MEMCARD.iconCount * 128 + 128 + MEMCARD.infoSize;
                break;
            case 3:
                MEMCARD.offset = MEMCARD.iconCount * 128 + 128 + MEMCARD.infoSize + MEMCARD.dataSize;
                break;
            case 4:
                MEMCARD.offset = MEMCARD.iconCount * 128 + 128 + MEMCARD.infoSize + MEMCARD.dataSize * 2;
                break;
            }
            while (MemCardWriteFile(port << 4, MEMCARD.fileName, dst, MEMCARD.offset, 128) == 0) {
                syncMemCard();
            }
            MEMCARD.state = 4;
            break;
        default:
            MEMCARD.state = 0;
            return MEMCARD.result + 1;
        }
        break;
    case 4:
        if (syncMemCard() != 0) {
            switch (MEMCARD.result) {
            case 0:
                MEMCARD.progress += 128;
                if (MEMCARD.progress >= size) {
                    MEMCARD.state = 0;
                    return 1;
                }
                while (1) {
                    if (MemCardWriteFile(port << 4, MEMCARD.fileName, dst + MEMCARD.progress, MEMCARD.offset + MEMCARD.progress, 128) != 0) {
                        return 0;
                    }
                    syncMemCard();
                }
            default:
                MEMCARD.state = 0;
                return MEMCARD.result + 1;
            }
        }
        if (MEMCARD.restart != 0) {
            MEMCARD.restart = 0;
            MEMCARD.progress = 0;
            while (MemCardWriteFile(port << 4, MEMCARD.fileName, dst, MEMCARD.offset, 128) == 0) {
                syncMemCard();
            }
            return 0;
        }
        break;
    }
    return 0;
}

extern s32 MEMCARD_SYNC_CMDS[];
extern char STR_ALL_FILES[];

/* 0 read the directory, 1 create the save file, 2 format, 3 unformat */
s32 memCardCommand(s32 port, s32 cmd) {
    switch (MEMCARD.state) {
    case 0:
    default:
        if (acceptMemCard(port) == 0) {
            return 0;
        }
        switch (MEMCARD.result) {
        case 0:
            MEMCARD.state = 5;
            break;
        case 4:
            if (cmd == 2) {
                MEMCARD.state = 5;
                break;
            }
            MEMCARD.state = 0;
            return 5;
        default:
            MEMCARD.state = 0;
            return MEMCARD.result + 1;
        }
        break;
    case 5:
        if ((MEMCARD.result == 0 && (cmd == 0 || cmd == 1 || cmd == 3)) ||
            (MEMCARD.result == 4 && cmd == 2)) {
            HEAP.zero(&MEMCARD.fileCount, 0x25C);
            MEMCARD.cmd = MEMCARD_SYNC_CMDS[cmd];
            switch (cmd) {
            case 0:
            default:
                MEMCARD.result = MemCardGetDirentry(port << 4, STR_ALL_FILES, MEMCARD.files, (long *)&MEMCARD.fileCount, 0, 15);
                break;
            case 1:
                MEMCARD.result = MemCardCreateFile(port << 4, MEMCARD.fileName, 4);
                break;
            case 2:
                MEMCARD.result = MemCardFormat(port << 4);
                break;
            case 3:
                MEMCARD.result = MemCardUnformat(port << 4);
                break;
            }
            if (MEMCARD.result == -1) {
                MEMCARD.result = 8;
            }
        }
        MEMCARD.state = 0;
        if (MEMCARD.result == 0) {
            return 1;
        }
        return MEMCARD.result + 1;
    }
    return 0;
}

s32 listSaves(s32 port) {
    s32 ret = memCardCommand(port, 0);

    if (ret == 1) {
        return 1;
    }
    return ret;
}

s32 createSave(s32 port) {
    s32 ret = memCardCommand(port, 1);

    if (ret == 1) {
        return 1;
    }
    return ret;
}

s32 formatMemCard(s32 port) {
    s32 ret = memCardCommand(port, 2);

    if (ret == 1) {
        return 1;
    }
    return ret;
}

s32 func_80015490(void) {
    return 2;
}

/* XOR of every byte */
s32 verifyChecksum(u8 *data, s32 size, char expected) {
    u8 sum = 0;
    s32 i;

    for (i = 0; i < size; i++) {
        sum ^= *data++;
    }
    return ((expected ^ sum) & 0xFF) == 0;
}

u8 computeChecksum(u8 *data, s32 size) {
    u8 sum = 0;
    s32 i;

    for (i = 0; i < size; i++) {
        sum ^= *data++;
    }
    return sum;
}
