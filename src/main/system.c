#include "game.h"
#include <libgs.h>

/* -G8 unit: small variables defined here are reached through $gp */
static u_char CD_MODE[8];
static RECT BOOT_IMAGE_RECT;
static void *ROOT_TASK;

extern void (*MEMCARD_FUNCS[])();
extern void (*PAD_INIT[])();
extern void (*PAD_UPDATE[])();
extern void (*FONT_LOAD[])();
extern void (*FILE_CACHE_UPDATE[])();
extern void (*SOUND_CONTROL[])();
void *createModeTask();
void func_8002DE28(s32);
void setSaveFileName(void);
int CdInit(void);
int SetVideoMode(long mode);
int ResetCallback(void);
int VSync(int mode);
void SsInit(void);
void MemCardInit(long val);
void MemCardStart(void);
int CdControl(u_char com, u_char *param, u_char *result);
int CdControlB(u_char com, u_char *param, u_char *result);

/* Starts opening (open != 0) or closing a panel */
void startPanel(PanelAnim *panel, s32 open) {
    panel->active = 1;
    if (open) {
        SOUND.playSound(0x40019);
        panel->level = 0;
        panel->step = 0x1000 / panel->duration;
    } else {
        SOUND.playSound(0x4001A);
        panel->level = 0x1000;
        panel->step = -((0x1000 / panel->duration) * 2);
    }
}

/* Advances a panel animation; 1 once it has finished */
s32 updatePanel(PanelAnim *panel) {
    if (!panel->active) {
        return 1;
    }
    panel->level += panel->step;
    if (panel->step > 0) {
        if (panel->level > 0x1000) {
            panel->level = 0x1000;
            panel->active = 0;
            return 1;
        }
    } else if (panel->level < 0) {
        panel->level = 0;
        panel->active = 0;
        return 1;
    }
    return 0;
}

extern WindowPos FIELD_MENU_LAYOUT[];
extern WindowPos PAGE_LABEL_LAYOUT[5];
extern WindowPos PAGE_VALUE_LAYOUT[5];
extern s32 PAGE_STATS[];

/* FieldMenu as createFieldMenuWindows declares it (the layer id as a halfword) */
typedef struct FieldMenuView {
    TASK_HEADER(FieldMenuView);
    /* 0x50 */ s16 layerId;
    /* 0x52 */ u8 unk52[6];
    /* 0x58 */ s32 cursor;
    /* 0x5C */ s32 count;
} FieldMenuView;

Cursor *createCursor(s16 layerId, s32 depth, s16 x, s16 y);

void createFieldMenuWindows(FieldMenuView *task, FieldMenuWindows *win) {
    s32 i;
    s32 j;
    WindowPos *pos;

    win->title = createTextWindow(task->layerId, 1, 0x98, 0x13);
    for (i = 0; i < task->count; i++) {
        win->options[i] = createTextWindow(task->layerId, 1, 0xBD, 0x31 + i * 14);
    }
    win->cursor = createCursor(task->layerId, 0, 0xB0, task->cursor * 14 + 0x31);
    win->cursor->setVisible(win->cursor, 0);
    win->moneyLabel = createTextWindow(task->layerId, 3, 0x46, 0xA6);
    win->money = createTextWindow(task->layerId, 3, 0x42, 0xA6);
    for (j = 0; j < 3; j++) {
        pos = &FIELD_MENU_LAYOUT[0];
        win->pages[j].name = createTextWindow(task->layerId, 1, pos->x, pos->y + j * 46);
        for (i = 0; i < 5; i++) {
            pos = &PAGE_LABEL_LAYOUT[i];
            win->pages[j].labels[i] = createTextWindow(task->layerId, 3, pos->x, pos->y + j * 46);
        }
        for (i = 0; i < 5; i++) {
            pos = &PAGE_VALUE_LAYOUT[i];
            win->pages[j].values[i] = createTextWindow(task->layerId, 3, pos->x, pos->y + j * 46);
        }
    }
}

void showPartnerPage(void *menu, FieldMenuWindows *win, s32 page, s32 show) {
    PartnerTotals stats;
    PartnerVitals *info;
    s32 id;
    s32 i;

    if (show) {
        id = GAME.funcs.getPartyMember(page);
        if (id >= 0) {
            info = GAME.funcs.getPartnerStats(id);
            GAME.funcs.computeStats(id, &stats);
            win->pages[page].name->setString(win->pages[page].name, info, -1);
            for (i = 0; i < 5; i++) {
                win->pages[page].labels[i]->setString(win->pages[page].labels[i], FILE_CACHE.load(0xB1), PAGE_LABEL_LAYOUT[i].string);
                win->pages[page].values[i]->setNumber(win->pages[page].values[i], 0, ((s16 *)&stats)[PAGE_STATS[i]]);
                win->pages[page].values[i]->setRightAlign(win->pages[page].values[i], 1);
            }
        } else {
            win->pages[page].name->setString(win->pages[page].name, FILE_CACHE.load(0xB1), 0xC);
            for (i = 0; i < 5; i++) {
                win->pages[page].values[i]->setString(win->pages[page].values[i], FILE_CACHE.load(0xB1), FIELD_MENU_LAYOUT[6 + i].string);
                win->pages[page].values[i]->setRightAlign(win->pages[page].values[i], 1);
            }
        }
    } else {
        win->pages[page].name->setVisible(win->pages[page].name, 0);
        for (i = 0; i < 5; i++) {
            win->pages[page].labels[i]->setVisible(win->pages[page].labels[i], 0);
            win->pages[page].values[i]->setVisible(win->pages[page].values[i], 0);
        }
    }
}

s32 func_80012698(void) {
    s32 value = GAME.funcs.getMode();

    if (value == 0x1000) {
        value = GAME.fieldMode;
    }
    if (value >= 0x2D7) {
        return -1;
    }
    return value >= 0x270;
}

/*
 * The menu opened on the field: the three party members' pages, a list of
 * options (FIELD_MENU_OPTIONS, one more when the player has item 0x192)
 * and the money. Picking an option switches to mode 0x1000 with the choice
 * in FIELD_MENU_CHOICE; from mode 0x1000, cancelling goes back to
 * GAME.fieldMode. `step` tells whether a mode change follows (0) or not.
 */
typedef struct FieldMenu {
    TASK_HEADER(FieldMenu);
    /* 0x50 */ s32 layerId;
    /* 0x54 */ s32 depth;
    /* 0x58 */ s32 cursor;
    /* 0x5C */ s32 count;
    /* 0x60 */ s32 extraOption;
    /* 0x64 */ s32 option2Enabled;
    /* 0x68 */ s32 fadeRow;
    /* 0x6C */ s32 time;
    /* 0x70 */ PanelAnim panels[3];
} FieldMenu;

extern s32 FIELD_MENU_CHOICE;
extern s32 FIELD_MENU_EXTRA;
extern s32 FIELD_MENU_OPTIONS[][6];
extern s32 FIELD_MENU_SPRITES[];

void updateFieldMenu(FieldMenu *task, FieldMenuWindows *win) {
    SpriteDrawer obj;
    SpriteDrawer obj2;
    s32 prev;
    s32 done;
    s32 i;
    s32 y;
    s32 y2;
    s32 j;

    switch (task->state) {
    case 0:
    default:
        task->nextState(task);
        task->panels[0].duration = task->panels[1].duration = task->panels[2].duration = 10;
        startPanel(&task->panels[0], 1);
        startPanel(&task->panels[1], 1);
        startPanel(&task->panels[2], 1);
        if (GAME.items[0x192] != 0) {
            FIELD_MENU_EXTRA = 1;
            task->extraOption = 1;
        } else {
            FIELD_MENU_EXTRA = 0;
        }
        task->count = task->extraOption + 5;
        if (func_80012698() >= 0) {
            task->option2Enabled = 1;
        } else {
            task->option2Enabled = 0;
        }
        createFieldMenuWindows(task, win);
        break;
    case 1:
        switch (task->substate) {
        default:
        case 0:
            if (updatePanel(&task->panels[0])) {
                showPartnerPage(task, win, 0, 1);
                win->title->setString(win->title, FILE_CACHE_LOAD[0](0xB1), 0x13);
                SOUND.playSound(0x40019);
                task->substate++;
            }
            break;
        case 1:
            if (updatePanel(&task->panels[1])) {
                showPartnerPage(task, win, 1, 1);
                for (task->counter = 0; task->counter < task->count; task->counter++) {
                    win->options[task->counter]->setString(win->options[task->counter], FILE_CACHE.load(0xB1),
                                              FIELD_MENU_OPTIONS[task->extraOption][task->counter]);
                }
                SOUND.playSound(0x40019);
                if (task->option2Enabled == 0) {
                    win->options[2]->setPalette(win->options[2], 7);
                }
                task->substate++;
            }
            break;
        case 2:
            if (updatePanel(&task->panels[2])) {
                showPartnerPage(task, win, 2, 1);
                win->moneyLabel->setString(win->moneyLabel, FILE_CACHE_LOAD[0](0xB1), 5);
                win->money->setNumber(win->money, 0, GAME.money);
                win->money->setRightAlign(win->money, 1);
                win->cursor->setVisible(win->cursor, 1);
                task->substate++;
            }
            break;
        case 3:
            prev = task->cursor;
            if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_UP)) & 1) ||
                ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_UP)) & 1)) {
                if (--task->cursor < 0) {
                    task->cursor = 0;
                }
            } else if (((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_DOWN)) & 1) ||
                       ((PAD.getRepeated(0) >> PAD.getButtonBit(0, PAD_DOWN)) & 1)) {
                task->cursor++;
                if (task->cursor > task->count - 1) {
                    task->cursor = task->count - 1;
                }
            }
            if (prev != task->cursor) {
                SOUND.playSound(0x8004513E);
                win->cursor->setPos(win->cursor, 0xB0, task->cursor * 14 + 0x31);
                break;
            }
            done = 0;
            if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_CROSS)) & 1) {
                SOUND.playSound(0x8004503C);
                if (task->option2Enabled == 0 && task->cursor == 2) {
                    break;
                }
                done = 1;
                if (GAME_FUNCS.getMode() == 0x1000) {
                    task->step = 1;
                } else {
                    task->step = 0;
                }
                FIELD_MENU_CHOICE = task->cursor;
            } else if ((PAD.getPressed(0) >> PAD.getButtonBit(0, PAD_TRIANGLE)) & 1) {
                SOUND.playSound(0x800450BD);
                done = 1;
                if (GAME_FUNCS.getMode() == 0x1000) {
                    task->step = 0;
                } else {
                    task->step = 1;
                }
            }
            if (done) {
                startPanel(&task->panels[0], 0);
                startPanel(&task->panels[1], 0);
                startPanel(&task->panels[2], 0);
                showPartnerPage(task, win, 2, 0);
                win->moneyLabel->setVisible(win->moneyLabel, 0);
                win->money->setVisible(win->money, 0);
                win->cursor->setVisible(win->cursor, 0);
                task->substate++;
            }
            break;
        case 4:
            if (updatePanel(&task->panels[2])) {
                showPartnerPage(task, win, 1, 0);
                for (task->counter = 0; task->counter < task->count; task->counter++) {
                    win->options[task->counter]->setVisible(win->options[task->counter], 0);
                }
                SOUND.playSound(0x4001A);
                task->substate++;
            }
            break;
        case 5:
            if (updatePanel(&task->panels[1])) {
                showPartnerPage(task, win, 0, 0);
                win->title->setVisible(win->title, 0);
                SOUND.playSound(0x4001A);
                task->substate++;
            }
            break;
        case 6:
            if (updatePanel(&task->panels[0])) {
                if (task->step == 0) {
                    task->setState(task, TASK_DONE);
                    task->time = GFX_FUNCS.getTime();
                } else {
                    task->setState(task, TASK_KILL);
                }
            }
            break;
        }
        initSpriteDrawer(&obj);
        obj.setTexture(0x140, 0);
        obj.setLayerId(task->layerId, task->depth);
        obj.setFollowScroll(0);
        for (i = 0, y = 0x11, y2 = 0x25; i < 3; i++) {
            if (task->panels[i].level != 0) {
                if (task->panels[i].level != 0x1000) {
                    obj.setScale(task->panels[i].level, 0x1000, 0x1000);
                    obj.setPivot(0, y2);
                } else {
                    obj.setScale(0x1000, 0x1000, 0x1000);
                }
                obj.draw(FILE_CACHE.getEntry(0x02770000), 0x15, 0, y);
                obj.draw(FILE_CACHE.getEntry(0x02770000), 0x17, 0, y);
            }
            y += 0x2E;
            y2 += 0x2E;
        }
        if (task->panels[0].level != 0) {
            if (task->panels[0].level != 0x1000) {
                obj.setScale(task->panels[0].level, 0x1000, 0x1000);
                obj.setPivot(0x140, 0x19);
            } else {
                obj.setScale(0x1000, 0x1000, 0x1000);
            }
            obj.draw(FILE_CACHE_GET_ENTRY[0](0x02770000), 0x18, 0x22, 0xD);
        }
        if (task->panels[1].level != 0) {
            if (task->panels[1].level != 0x1000) {
                obj.setScale(task->panels[1].level, 0x1000, 0x1000);
                obj.setPivot(0x140, 0x52);
            } else {
                obj.setScale(0x1000, 0x1000, 0x1000);
            }
            obj.draw(FILE_CACHE_GET_ENTRY[0](0x02770000), 0x1C - task->extraOption, 0xA8, 0x28);
        }
        if (task->panels[2].level != 0) {
            if (task->panels[2].level != 0x1000) {
                obj.setScale(task->panels[2].level, 0x1000, 0x1000);
                obj.setPivot(0, 0xA8);
            } else {
                obj.setScale(0x1000, 0x1000, 0x1000);
            }
            obj.draw(FILE_CACHE_GET_ENTRY[0](0x02770000), 0x1A, 0, 0x9E);
        }
        break;
    case 2:
        switch (task->substate) {
        default:
            task->setState(task, TASK_DONE);
        case 0:
        case 1:
        case 2:
            if (GFX.funcs.getTime() - task->time >= 2) {
                task->time = GFX.funcs.getTime();
                if (++task->fadeRow >= 8) {
                    if (++task->substate != 3) {
                        task->fadeRow = 0;
                    } else {
                        task->fadeRow = 8;
                    }
                }
            }
            break;
        case 3:
        case 4:
        case 5:
            if (GFX.funcs.getTime() - task->time >= 2) {
                task->time = GFX.funcs.getTime();
                if (++task->fadeRow >= 0x10) {
                    if (++task->substate == 6) {
                        task->fadeRow = 0xF;
                    } else {
                        task->fadeRow = 8;
                    }
                }
            }
            break;
        case 6:
            if (GAME.funcs.getMode() == 0x1000) {
                GAME.funcs.requestMode(GAME.fieldMode, 0);
            } else {
                GAME.funcs.requestMode(0x1000, 0);
                FIELD_MENU_CHOICE = task->cursor;
            }
            task->substate++;
            break;
        case 7:
            break;
        }
        initSpriteDrawer(&obj2);
        obj2.setTexture(0x140, 0);
        obj2.setLayerId(task->layerId, task->depth);
        obj2.setFollowScroll(0);
        for (j = 0; j <= task->substate; j++) {
            if (j == 6) {
                break;
            }
            if (j == task->substate) {
                obj2.setClutRow(task->fadeRow);
            } else if (j < 3) {
                obj2.setClutRow(7);
            } else {
                obj2.setClutRow(0xF);
            }
            obj2.draw(FILE_CACHE.getEntry(0x02770000), FIELD_MENU_SPRITES[j], 0, 0);
        }
        break;
    case 3:
        break;
    }
}

void createFieldMenu(s32 layerId, s32 cursor) {
    FieldMenu *task = createTask(updateFieldMenu, 0xA0, 0xAC);

    task->layerId = layerId;
    task->depth = 1;
    task->cursor = cursor;
}

s32 findDigimon(s32 id) {
    DigimonData *entry;
    s32 i;

    for (i = 0, entry = DIGIMON_DATA; i < 52; i++, entry++) {
        if (entry->id == id) {
            return i;
        }
    }
    return -1;
}

DigimonData *getDigimon(s32 id) {
    s32 index = findDigimon(id);

    if (index >= 0) {
        return &DIGIMON_DATA[index];
    }
    return NULL;
}

void func_8001350C(void) {
    s32 i;

    for (i = 7; i >= 0; i--) {
        D_80042728.unk58[i] = 0;
    }
}

ItemInfo *getItem(s32 id) {
    if (id <= 0) {
        return NULL;
    }
    return &ITEM_DATA[id];
}

u8 getItemCategory(s32 id) {
    return ITEM_TYPE_CATEGORIES[getItem(id)->type];
}

s32 func_80013590(s32 arg0, s32 arg1) {
    return getItem(arg0)->unk8 == arg1;
}

extern u16 *ITEM_LISTS[];

s32 listItems(s32 type, u16 *out) {
    s32 index;
    s32 all;
    u16 *p;
    s32 n;

    all = (type >> 31) != 0;
    index = type & 0x7FFFFFFF;

    if (index >= 5) {
        return 0;
    }
    n = 0;
    for (p = ITEM_LISTS[index]; *p != 0; p++) {
        if (GAME.items[*p] != 0 || (all && GAME.equippedItems[*p] != 0)) {
            *out++ = *p;
            n++;
        }
    }
    return n;
}

/* Checks that the sector just read is the next one (func_8002E268 = CdGetSector) */
s32 cdCheckSector(void) {
    s32 pos;

    func_8002E268(CD_SECTOR_HEADER, 3);
    pos = CdPosToInt(CD_SECTOR_HEADER);
    if (pos == CD_READER.nextSector) {
        CD_READER.nextSector = pos + 1;
        return 0;
    }
    return -1;
}

/* CdReadyCallback: copies each sector as it arrives, pauses at the end */
void cdReadyCallback(s32 status) {
    if (status == 1) {
        if (cdCheckSector() != 0) {
            goto error;
        }
        func_8002E268((void *)CD_READER.dst, 0x200);
        CD_READER.dst += 0x800;
        if (--CD_READER.sectorsLeft != 0) {
            return;
        }
    } else {
    error:
        CD_READER.sectorsLeft = -1;
    }
    func_8002DE88(0);
    CdControlF(9, 0);
}

/* CdSyncCallback: Setloc (2), Setmode 0xA0 (0xE), ReadN (6), Pause (9) */
void cdSyncCallback(s32 status) {
    switch (status) {
    case 5:
        if (CD_READER.state == 4) {
            CdControlF(9, 0);
        } else {
            startCdRead();
        }
        break;
    case 2:
        switch (CD_READER.state) {
        case 1:
            CD_MODE[0] = 0xA0;
            CdControlF(0xE, CD_MODE);
            CD_READER.state++;
            break;
        case 2:
            func_8002DE88((s32)cdReadyCallback);
            CdControlF(6, 0);
            CD_READER.state++;
            break;
        case 3:
            CD_READER.state = 4;
            break;
        case 4:
            func_8002DE68(0);
            if (CD_READER.sectorsLeft == 0) {
                CD_READER.state = 0;
                if (CD_READER.done != NULL) {
                    *CD_READER.done = 1;
                }
            } else {
                startCdRead();
            }
            break;
        }
        break;
    }
}

s32 isCdReading(void) {
    return CD_READER.state != 0;
}

void startCdRead(void) {
    CD_READER.state = 1;
    CD_READER.nextSector = CD_READER.sector;
    CD_READER.dst = CD_READER.buffer;
    CD_READER.sectorsLeft = CD_READER.sectorCount;
    func_8002DE68(cdSyncCallback);
    CdControlF(2, CD_READER.loc);
}

/* Starts reading `size` sectors (0: all) of a file into buffer; ignored while busy */
void readFile(s32 file, s32 offset, s32 size, s32 buffer, s32 *done) {
    if (isCdReading() == 0) {
        CD_READER.file = file;
        CD_READER.offset = offset;
        CD_READER.buffer = buffer;
        CD_READER.done = done;
        if (done != NULL) {
            *done = 0;
        }
        if (size == 0) {
            CD_READER.sectorCount = FILE_TABLE.getSectorCount(file);
        } else {
            CD_READER.sectorCount = size;
        }
        FILE_TABLE.getPos(file, offset, CD_READER.loc);
        CD_READER.sector = FILE_TABLE.getSector(file) + offset;
        startCdRead();
    }
}

FileSlot *findFileSlot(s32 file) {
    FileSlot *slot;
    s32 i;

    for (slot = FILE_CACHE_SLOTS, i = 0; i < 64; i++, slot++) {
        if (slot->file == file) {
            return slot;
        }
    }
    return NULL;
}

FileSlot *findFreeFileSlot(void) {
    FileSlot *slot;
    s32 i;

    for (slot = FILE_CACHE_SLOTS, i = 0; i < 64; i++, slot++) {
        if (slot->file == 0) {
            return slot;
        }
    }
    return NULL;
}

/* 0 once the file is in the cache; requests it if needed */
s32 isFileLoading(s32 file) {
    FileSlot *slot = findFileSlot(file);

    if (slot != NULL) {
        slot->lastUsed = GFX.funcs.getTime();
        if (slot->state == 3) {
            return 0;
        }
    } else {
        requestFile(file);
    }
    return 1;
}

/* The loaded file used least recently (the biggest one on a tie) */
FileSlot *findOldestFile(void) {
    FileSlot *best = NULL;
    s32 bestSize = 0;
    s32 i = 0;
    s32 time = GFX_FUNCS.getTime();
    FileSlot *slot;

    for (slot = FILE_CACHE_SLOTS; i < 64; i++, slot++) {
        if (slot->file != 0 && slot->state == 3 && time >= slot->lastUsed) {
            if (time != slot->lastUsed || FILE_TABLE.getSectorCount(slot->file) >= bestSize) {
                bestSize = FILE_TABLE.getSectorCount(slot->file);
                time = slot->lastUsed;
                best = slot;
            }
        }
    }
    return best;
}

void evictOldestFile(void) {
    FileSlot *slot = findOldestFile();

    HEAP.free(slot->data);
    slot->file = 0;
    slot->data = NULL;
    slot->lastUsed = 0;
    slot->marked = 0;
    slot->state = 0;
}

void requestFile(s32 file) {
    FileSlot *slot = findFileSlot(file);

    if (slot != NULL) {
        slot->lastUsed = GFX_FUNCS.getTime();
        return;
    }
    slot = findFreeFileSlot();
    slot->file = file;
    slot->data = HEAP.alloc(FILE_TABLE.getSectorCount(file) << 11, 3);
    slot->state = 1;
    slot->lastUsed = 0;
    slot->marked = 0;
    FILE_CACHE.pending = 1;
}

void updateFileCache(void) {
    FileSlot *slot;
    s32 i;
    s32 busy;
    s32 reading;

    if (FILE_CACHE.pending != 0 && CD_READER.isBusy() != 1) {
        slot = FILE_CACHE.slots;
        reading = 0;
        busy = 0;
        for (i = 0; i < 64; i++, slot++) {
            if (slot->file != 0) {
                switch (slot->state) {
                case 2:
                    slot->state = 3;
                    busy = 1;
                    slot->lastUsed = GFX.funcs.getTime();
                    break;
                case 1:
                    busy = 1;
                    if (!reading) {
                        CD_READER.read(slot->file, 0, 0, slot->data, NULL);
                        slot->state = 2;
                        reading = busy;
                        slot->lastUsed = GFX.funcs.getTime();
                    }
                    break;
                }
            }
        }
        if (!busy) {
            FILE_CACHE.pending = 0;
        }
    }
}

void waitForFile(s32 file) {
    requestFile(file);
    do {
        updateFileCache();
    } while (isFileLoading(file) != 0);
}

/* Returns the file's data, reading it now if it is not in the cache */
s32 *loadFile(u32 file) {
    FileSlot *slot = findFileSlot(file);

    if (slot != NULL && slot->state == 3) {
        slot->lastUsed = GFX_FUNCS.getTime();
        return slot->data;
    }
    while (CD_READER.isBusy() != 0) {
    }
    waitForFile(file);
    return findFileSlot(file)->data;
}

void freeFile(s32 file) {
    FileSlot *slot = findFileSlot(file);

    if (slot != NULL && slot->state == 3) {
        HEAP.free(slot->data);
        slot->file = 0;
        slot->data = NULL;
        slot->lastUsed = 0;
        slot->marked = 0;
        slot->state = 0;
    }
}

void freeAllFiles(void) {
    FileSlot *slot;
    s32 i;

    for (slot = FILE_CACHE_SLOTS, i = 0; i < 64; i++, slot++) {
        if (slot->file != 0) {
            HEAP.free(slot->data);
            slot->file = 0;
            slot->data = NULL;
            slot->lastUsed = 0;
            slot->marked = 0;
            slot->state = 0;
        }
    }
}

/* Frees the files that reach past addr (to load something there) */
void freeFilesFrom(u32 addr) {
    FileSlot *slot = FILE_CACHE_SLOTS;
    s32 i;
    u32 end;

    for (i = 0; i < 64; i++, slot++) {
        if (slot->file != 0) {
            end = (u32)slot->data + 0x20;
            end += FILE_TABLE.getSectorCount(slot->file) << 11;
            if (end >= addr) {
                HEAP.free(slot->data);
                slot->file = 0;
                slot->data = 0;
                slot->lastUsed = 0;
                slot->marked = 0;
                slot->state = 0;
            }
        }
    }
}

/*
 * Files are often archives: a table of offsets from the start of the file.
 * getFileEntry((file << 16) | index) loads the file and returns that entry.
 */
s32 getFileEntry(u32 fileAndIndex) {
    s32 index = fileAndIndex & 0xFFFF;
    s32 *table = loadFile(fileAndIndex >> 16);

    return table[index] + (s32)table;
}

s32 getArchiveEntry(u32 index, s32 *archive) {
    return archive[index & 0xFFFF] + (s32)archive;
}

/* markCachedFiles + touchMarkedFiles: refresh the files cached before a load */
void markCachedFiles(void) {
    FileSlot *slot;
    s32 i;

    for (i = 0, slot = FILE_CACHE_SLOTS; i < 64; i++, slot++) {
        if (slot->file == 0) {
            slot->marked = 0;
        } else {
            slot->marked = 1;
        }
    }
}

void touchMarkedFiles(void) {
    FileSlot *slot = FILE_CACHE_SLOTS;
    s32 now = GFX_FUNCS.getTime();
    s32 i;

    for (i = 0; i < 64; i++, slot++) {
        if (slot->file != 0 && slot->marked != 0) {
            slot->lastUsed = now;
            slot->marked = 0;
        }
    }
}

s32 fileExists(s32 file) {
    return FILE_SECTORS[file] != 0;
}

u16 getFileSectorCount(s32 file) {
    return FILE_SECTOR_COUNTS[file];
}

s32 getFileSector(s32 file) {
    return FILE_SECTORS[file];
}

void getFilePos(s32 file, s32 offset, void *pos) {
    CdIntToPos(FILE_SECTORS[file] + offset, pos);
}

void taskSetState(Task *task, s32 state) {
    task->state = state;
    task->substate = 0;
    task->step = 0;
    task->counter = 0;
}

void taskSetSubstate(Task *task, s32 substate) {
    task->substate = substate;
    task->step = 0;
    task->counter = 0;
}

void taskSetStep(Task *task, s32 step) {
    task->step = step;
    task->counter = 0;
}

void taskSetCounter(Task *task, s32 counter) {
    task->counter = counter;
}

void taskNextState(Task *task) {
    task->substate = 0;
    task->step = 0;
    task->counter = 0;
    task->state++;
}

void taskNextSubstate(Task *task) {
    task->step = 0;
    task->counter = 0;
    task->substate++;
}

void taskNextStep(Task *task) {
    task->counter = 0;
    task->step++;
}

void taskTickCounter(Task *task) {
    task->counter++;
}

/* Default destructor: kills the children, then frees the task */
void destroyTask(Task *task) {
    s32 i;
    s32 *children;

    if (task->childCount != 0) {
        children = task->children;
        for (i = 0; i < task->childCount; i++) {
            if (children[i] != 0) {
                TASK_REGISTRY.funcs.kill(children[i]);
            }
        }
        HEAP.free(task->children);
    }
    TASK_FUNCS.remove(task);
    HEAP.free(task);
}

/*
 * Allocates a zeroed task of `size` bytes (header included) with room for
 * childrenSize / 4 child tasks. A nonzero id also registers it (findTask).
 */
void *createTaskWithId(void (*update)(), s32 size, s32 childrenSize, s32 id) {
    Task *task = HEAP.allocZeroed(size, 2);

    if (childrenSize != 0) {
        task->children = HEAP.allocZeroed(childrenSize, 2);
        task->childCount = childrenSize / 4;
    }
    task->setState = taskSetState;
    task->setSubstate = taskSetSubstate;
    task->setStep = taskSetStep;
    task->setCounter = taskSetCounter;
    task->nextState = taskNextState;
    task->nextSubstate = taskNextSubstate;
    task->nextStep = taskNextStep;
    task->tickCounter = taskTickCounter;
    task->update = update;
    task->destroy = destroyTask;
    if (id != 0) {
        task->id = id;
        TASK_FUNCS.add(task);
    }
    return task;
}

void *createTask(void (*update)(), s32 size, s32 childrenSize) {
    return createTaskWithId(update, size, childrenSize, 0);
}

int main(void) {
    RECT rect;
    GsIMAGE tim;
    u_char param[8];

    SetVideoMode(0);
    ResetCallback();
    VSync(0);
    SetDispMask(0);
    ResetGraph(0);
    GFX.funcs.reset();
    GFX.funcs.startVSync();
    rect.x = 0;
    rect.y = 0;
    rect.w = 0x280;
    rect.h = 0x1FF;
    ClearImage(&rect, 0, 0, 0);
    DrawSync(0);
    GsInitGraph(320, 240, 1, 1, 0);
    GsInit3D();
    SsInit();
    InitGeom();
    GFX.funcs.setDisplayMode(320, 640, 1, 0);
    PutDispEnv(&GFX.disp[0]);
    VSync(0);
    GsGetTimInfo((u_long *)SUB_OVERLAY_ADDRESS + 1, &tim);
    VSync(0);
    LoadImage(&BOOT_IMAGE_RECT, tim.pixel);
    DrawSync(0);
    VSync(0);
    SetDispMask(1);
    CdInit();
    func_8002DE28(0);
    SetGraphDebug(0);
    param[0] = 0x80;
    while (CdControl(0xE, param, 0) == 0) {
    }
    VSync(3);
    CdControlB(9, 0, 0);
    HEAP.init();
    SOUND.init();
    RANDOM.seed(0);
    MEMCARD_FUNCS[0]();
    PAD_INIT[0](0, 0x12);
    GAME_FUNCS.newGame();
    FONT_LOAD[0]();
    /*
     * One frame per iteration: when the mode task has died (a new mode was
     * requested), free everything the mode allocated and start the new one.
     */
    for (;;) {
        if (ROOT_TASK == NULL) {
            GFX.funcs.freePrimBuffers();
            GFX.funcs.reset();
            TASK_REGISTRY.funcs.clear();
            HEAP.freeByTag(2);
            GAME_FUNCS.commitMode();
            ROOT_TASK = createModeTask();
        }
        ROOT_TASK = TASK_REGISTRY.funcs.run(ROOT_TASK);
        GFX.funcs.drawFrame(ROOT_TASK);
        PAD_UPDATE[0]();
        RANDOM.next();
        FILE_CACHE_UPDATE[0]();
        SOUND_CONTROL[0]();
    }
}

void initMemCard(void) {
    MemCardInit(0);
    MemCardStart();
    HEAP.zero(&MEMCARD, sizeof(MemCard));
    MEMCARD.maxRetries = 3;
    MEMCARD.iconCount = -1;
    setSaveFileName();
    MEMCARD.infoSize = 0x100;
    MEMCARD.dataSize = 0x2700;
}

INCLUDE_RODATA("asm/main/nonmatchings/system", OVERLAY_ADDRESS);

INCLUDE_RODATA("asm/main/nonmatchings/system", SUB_OVERLAY_ADDRESS);
