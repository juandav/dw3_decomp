#include "game.h"
#include "libsnd.h"

extern s32 MODE_OVERLAY_FILES[];

/* The slot (0-2) that holds bank `id`, or -1 */
s32 findSoundBank(s32 id) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (SOUND_STATE.banks[i].id == id) {
            return i;
        }
    }
    return -1;
}

/* Plays a packed sound id (see SoundFuncs); returns the voice of a key-on */
s32 playSound(s32 packed) {
    s32 id = (packed >> 18) & 0x7F;
    u32 keyOn = (u32)packed >> 31;
    s32 exclusive = (packed >> 30) & 1;
    s32 prog = (packed >> 11) & 0x7F;
    s32 tone = (packed >> 7) & 0xF;
    s32 note = packed & 0x7F;
    s32 seq = (packed >> 8) & 0xFF;
    s32 sep = packed & 0xFF;
    s32 slot = findSoundBank(id);
    s32 voice = -1;

    if (slot != -1) {
        if (slot != 0) {
            SOUND.lastSlot = slot;
        }
        if (exclusive) {
            if (SOUND_STATE.music == packed) {
                return 0;
            }
            if (SOUND_STATE.music != 0) {
                SOUND_STATE.stopSound(SOUND_STATE.music);
            }
            SOUND_STATE.music = packed;
        }
        if (keyOn) {
            voice = SsUtKeyOn(SOUND_STATE.banks[slot].vabId, prog, tone, note, 0, 0x7F, 0x7F);
        } else {
            id = sep;
            SsSepStop(SOUND_STATE.banks[slot].seqs[seq], id);
            SsSepSetVol(SOUND_STATE.banks[slot].seqs[seq], id, 0x7F, 0x7F);
            SsSepPlay(SOUND_STATE.banks[slot].seqs[seq], id, 1, 1);
        }
        return voice;
    }
    return 0;
}

void stopAllSounds(void) {
    s32 i;
    s32 j;
    s32 k;
    SoundBank *bank;

    for (i = 0; i < 3; i++) {
        bank = &SOUND_STATE.banks[i];
        if (bank->vabId != -1) {
            for (j = 0; j < bank->numSeqs; j++) {
                for (k = 0; k < 16; k++) {
                    SsSepStop(bank->seqs[j], k);
                }
            }
        }
    }
    SsUtAllKeyOff(0);
    SOUND.music = 0;
}

void stopSound(s32 packed) {
    s32 id = (packed >> 18) & 0x7F;
    u32 stopped = (u32)packed >> 31;
    s32 seq = (packed >> 8) & 0xFF;
    s32 sep = packed & 0xFF;
    s32 slot = findSoundBank(id);

    if (slot != -1 && !stopped) {
        SsSepStop(SOUND_STATE.banks[slot].seqs[seq], sep);
        if (SOUND_STATE.music == packed) {
            SOUND_STATE.music = 0;
        }
    }
}

void fadeOutSound(s32 packed) {
    s32 id = (packed >> 18) & 0x7F;
    u32 stopped = (u32)packed >> 31;
    s32 seq = (packed >> 8) & 0xFF;
    s32 sep = packed & 0xFF;
    s32 slot = findSoundBank(id);

    if (slot != -1 && !stopped) {
#if VERSION_US
        SsSepSetDecrescendo(SOUND_STATE.banks[slot].seqs[seq], sep, 0x80, 0x3C);
#elif VERSION_EU
        /* one second, in frames */
        SsSepSetDecrescendo(SOUND_STATE.banks[slot].seqs[seq], sep, 0x80, NTSC_MODE ? 0x3C : 0x32);
#endif
        if (SOUND_STATE.music == packed) {
            SOUND_STATE.music = 0;
        }
    }
}

s32 isSoundLoading(void) {
    return SOUND.loaderState != 0;
}

void loadSoundBankInto(s32 slot, s32 id) {
    SoundBank *bank = &SOUND_STATE.banks[slot];
    SoundLoader *loader = &SOUND_STATE.loader;
    s32 i;
    s32 j;

    bank->id = id;
    if (bank->vabId != -1) {
        for (i = 0; i < bank->numSeqs; i++) {
            for (j = 0; j < 16; j++) {
                SsSepStop(bank->seqs[i], j);
            }
            func_80030198(bank->seqs[i]);
        }
        SsVabClose(bank->vabId);
        bank->vabId = -1;
    }
    loader->state = 1;
    loader->files = SOUND_BANK_FILES[id];
    loader->slot = slot;
    FILE_CACHE_REQUEST(loader->files[1]);
}

/* Loads a bank into slot 1 or 2, whichever was not used last */
void loadSoundBank(s32 id) {
    if (SOUND_STATE.banks[1].id != id && SOUND_STATE.banks[2].id != id) {
        if (SOUND_STATE.lastSlot == 1) {
            loadSoundBankInto(2, id);
            SOUND_STATE.lastSlot = 2;
        } else {
            loadSoundBankInto(1, id);
            SOUND_STATE.lastSlot = 1;
        }
    }
}

/* What SoundLoader.files points to (SOUND_BANK_FILES[id]) */
typedef struct SoundFiles {
    /* 0x00 */ s32 bodyFile; /* VAB body, sent to the SPU */
    /* 0x04 */ s32 headFile; /* archive: VAB header and SEPs */
    /* 0x08 */ s32 vhIndex; /* of the VAB header in headFile */
    /* 0x0C */ s32 bodyEntry; /* (file << 16) | slot */
    /* 0x10 */ s32 seps[1]; /* indices in headFile, 0-terminated */
} SoundFiles;

/* Header: copied to the slot's buffer, then the body goes to the SPU */
void updateSoundLoading(void) {
    SoundLoader *loader = &SOUND_STATE.loader;
    s32 slot = loader->slot;
    SoundBank *bank = &SOUND_STATE.banks[slot];
    s32 *src;
    s32 *dst;
    s32 n;
    s32 i;
    s32 j;

    switch (loader->state) {
    case 0:
        break;
    case 1:
        if (FILE_CACHE.isLoading(((SoundFiles *)loader->files)->headFile) != 0) {
            return;
        }
        src = (s32 *)FILE_CACHE.load(((SoundFiles *)loader->files)->headFile);
        dst = (s32 *)bank->headBuffer;
        n = FILE_TABLE.getSectorCount(((SoundFiles *)loader->files)->headFile) << 9;
        for (j = 0; j < n; j++) {
            *dst++ = *src++;
        }
        FILE_CACHE.free(((SoundFiles *)loader->files)->headFile);
        bank->vabId = SsVabOpenHeadSticky(FILE_CACHE.getArchiveEntry(((SoundFiles *)loader->files)->vhIndex, bank->headBuffer), slot, bank->spuAddr);
        FILE_CACHE.request(((SoundFiles *)loader->files)->bodyFile);
        loader->state++;
    case 2:
        if (FILE_CACHE.isLoading(((SoundFiles *)loader->files)->bodyFile) != 0) {
            return;
        }
        HEAP.lock(FILE_CACHE.load(((SoundFiles *)loader->files)->bodyFile), 1);
        bank->vabId = SsVabTransBody((unsigned char *)FILE_CACHE.getEntry(((SoundFiles *)loader->files)->bodyEntry), bank->vabId);
        loader->state++;
    case 3:
        if (SsVabTransCompleted(0) == 0) {
            return;
        }
        i = 0;
        HEAP.lock(FILE_CACHE.load(((SoundFiles *)loader->files)->bodyFile), 0);
        FILE_CACHE.free(((SoundFiles *)loader->files)->bodyFile);
        for (; ((SoundFiles *)loader->files)->seps[i] != 0; i++) {
            bank->seqs[i] = SsSepOpen((unsigned long *)FILE_CACHE.getArchiveEntry(((SoundFiles *)loader->files)->seps[i], bank->headBuffer), bank->vabId, 16);
        }
        bank->numSeqs = i;
        loader->state = 0;
    }
}

short soundKeyOn(s32 slot, short prog, short note) {
    return SsUtKeyOn(SOUND_STATE.banks[slot].vabId, prog, 0, note, 0, 0x7F, 0x7F);
}

void soundKeyOff(s32 packed, s16 voice) {
    s32 id = (packed >> 18) & 0x7F;
    s32 prog = (packed >> 11) & 0x7F;
    s32 tone = (packed >> 7) & 0xF;
    s32 note = packed & 0x7F;
    s32 slot = findSoundBank(id);

    if (voice != -1 && slot != -1) {
        SsUtKeyOff(voice, SOUND_STATE.banks[slot].vabId, prog, tone, note);
    }
}

void initSound(void) {
    s32 i;

    SsSetTableSize(SOUND_STATE.seqTable, 6, 16);
#if VERSION_US
    SsSetTickMode(0x1000);
#elif VERSION_EU
    if (NTSC_MODE) {
        SsSetTickMode(0x1000);
    } else {
        SsSetTickMode(0x1032); /* SS_NOTICK, 50 ticks a second */
    }
#endif
    SsStart2();
    SsSetMVol(0x7F, 0x7F);
    SsSetSerialAttr(0, 0, 1);
    SsSetSerialVol(0, 0x7F, 0x7F);
    SsUtSetReverbType(3);
    SsUtSetReverbDepth(0, 0);
    func_800345B8();
    for (i = 0; i < 3; i++) {
        SOUND_STATE.banks[i].vabId = -1;
        SOUND_STATE.banks[i].numSeqs = 0;
        SOUND_STATE.banks[i].headBuffer = SOUND_HEAD_BUFFERS[i];
        SOUND_STATE.banks[i].spuAddr = SOUND_SPU_ADDRS[i];
    }
    SOUND_STATE.loader.slot = 0;
    SOUND_STATE.loader.state = 0;
    SOUND_STATE.loader.files = NULL;
    loadSoundBankInto(0, 1);
    while (isSoundLoading() != 0) {
        FILE_CACHE.update();
        updateSoundLoading();
    }
}

/*
 * The root task (created by main): loads the overlay of the current game
 * mode and calls its entry point, which returns the mode's top task. Once a
 * new mode is requested it dies, and main creates it again.
 */
void updateModeTask(Task *task, s32 *children) {
    switch (task->state) {
    case 0:
    default:
        OVERLAY_FUNCS->loadModeOverlay();
        children[0] = MODE_ENTRY_POINTS[GAME_FUNCS.getMode() >> 8]();
        task->nextState(task);
        break;
    case 1:
        if (GAME_FUNCS.isModeChangePending() != 0) {
            task->setState(task, TASK_KILL);
        }
        break;
    case 2:
    case 3:
        break;
    }
}

/* The task is returned in v0, left there by createTask */
void createModeTask(void) {
    createTask(updateModeTask, 0x50, 4);
}

/* Copies the overlay of the current mode (mode >> 8) to 0x80082448 */
void loadModeOverlay(void) {
    s32 id = GAME_FUNCS.getMode() >> 8;
    u8 *src;
    void *dst;

    if (OVERLAY_STATE->mode != id) {
        OVERLAY_STATE->mode = id;
        OVERLAY_STATE->subOverlay = -1;
        src = FILE_CACHE_LOAD[0](MODE_OVERLAY_FILES[id]);
        dst = OVERLAY_ADDRESS;
        memcpy(dst, src, FILE_TABLE.getSectorCount(MODE_OVERLAY_FILES[id]) << 11);
    }
}

/* Copies a file to the second overlay area */
void loadSubOverlay(s32 id) {
    u8 *src;
    void *dst;

    if (OVERLAY_STATE->subOverlay != id) {
        OVERLAY_STATE->subOverlay = id;
        src = FILE_CACHE_LOAD[0](id);
        dst = SUB_OVERLAY_ADDRESS;
        memcpy(dst, src, FILE_TABLE.getSectorCount(id) << 11);
    }
}

