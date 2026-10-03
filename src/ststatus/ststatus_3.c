/* The third object of STSTATUS.PRO (see ststatus.c), the fifth screen's
   panel of func_800879C8: its rodata starts at 0x800826CC (USA). */

#include "ststatus.h"

void func_80085BD8(StatusPanel4B *panel, StatusPanel4BWindows *windows) {
    s32 i;

    windows->title = createTextWindow(panel->layer, 1, 0x98, 0x13);
    windows->cursor = createCursor(panel->layer, panel->depth - 1, 0xA5, 0x31);
    windows->cursor->setVisible(windows->cursor, 0);
    for (i = 0; i < 6; i++) {
        windows->slots[i] = createTextWindow(panel->layer, 1, 0xC0, i * 14 + 0x31);
    }
    windows->listTitle = createTextWindow(panel->layer, 1, 0x7F, 0x3B);
    windows->listCursor = createCursor(panel->layer, panel->depth - 1, 0x86, 0x4B);
    windows->listCursor->setVisible(windows->listCursor, 0);
    for (i = 0; i < 8; i++) {
        windows->rows[i].name = createTextWindow(panel->layer, 1, 0xA0, i * 14 + 0x4B);
        windows->rows[i].times = createTextWindow(panel->layer, 1, 0x10D, i * 14 + 0x4B);
        windows->rows[i].count = createTextWindow(panel->layer, 1, 0x120, i * 14 + 0x4B);
    }
    windows->help = createTextWindow(panel->layer, 1, 0x14, 0xC6);
    windows->kind = createTextWindow(panel->layer, 1, 0x14, 0xD5);
    windows->slotTitle = createTextWindow(panel->layer, 1, 0xA7, 0x13);
    windows->slotItem = createTextWindow(panel->layer, 1, 0xC0, 0x23);
}

/* The partner's equipment, or the slots' names where it has none */
void func_80085DC0(StatusPanel4B *panel, StatusPanel4BWindows *windows, s32 show) {
    PartnerStats *stats;
    s16 item;
    s32 i;

    if (show) {
        stats = (PartnerStats *)GAME_FUNCS.getPartnerStats(panel->partner);
        for (i = 0; i < 6; i++) {
            item = stats->equip[i];
            if (item > 0) {
                windows->slots[i]->setString(windows->slots[i], FILE_CACHE.load(TEXT_FILE(0x6B)), item);
            } else {
                windows->slots[i]->setString(windows->slots[i], FILE_CACHE.load(TEXT_FILE(0xB1)), D_80099AC0[i]);
            }
        }
    } else {
        for (i = 0; i < 6; i++) {
            windows->slots[i]->setVisible(windows->slots[i], 0);
        }
    }
}

/* An item's name and, for slots 2 and 3, its kind (none: string 0x51) */
void func_80085EE4(StatusPanel4B *panel, StatusPanel4BWindows *windows, s32 item) {
    u8 *data;

    if (item > 0) {
        windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0x64)), item);
        if (panel->slot == 2 || panel->slot == 3) {
            data = GET_ITEM[0](item)->data;
            windows->kind->setString(windows->kind, FILE_CACHE.load(TEXT_FILE(0xB1)), D_80099AD8[data[2] - 1]);
            return;
        }
    } else {
        windows->help->setString(windows->help, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x51);
    }
    windows->kind->setVisible(windows->kind, 0);
}

/* Fills the list of the items that fit the slot */
void func_80086010(StatusPanel4B *panel, StatusPanel4BWindows *windows, s32 show) {
    s32 i;
    s32 row;
    s32 item;

    if (show) {
        windows->listTitle->setString(windows->listTitle, FILE_CACHE.load(TEXT_FILE(0xB1)), D_80099AC0[panel->slot]);
        for (i = 0; i < 8; i++) {
            row = panel->scroll + i;
            if (row > panel->count - 1) {
                break;
            }
            item = panel->items[row];
            if (item > 0) {
                if (STSTATUS_data.funcs.canEquip(panel->partner, panel->slot, item)) {
                    windows->rows[i].name->setPalette(windows->rows[i].name, 0);
                } else {
                    windows->rows[i].name->setPalette(windows->rows[i].name, 7);
                }
                windows->rows[i].name->setString(windows->rows[i].name, FILE_CACHE.load(TEXT_FILE(0x6B)), item);
                windows->rows[i].times->setString(windows->rows[i].times, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x40);
                windows->rows[i].times->setRightAlign(windows->rows[i].times, 1);
                windows->rows[i].count->setNumber(windows->rows[i].count, 0, GAME.items[item]);
                windows->rows[i].count->setRightAlign(windows->rows[i].count, 1);
            } else {
                if (item == -1) {
                    windows->rows[i].name->setString(windows->rows[i].name, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x45);
                    windows->rows[i].name->setPalette(windows->rows[i].name, 0);
                } else {
                    windows->rows[i].name->setVisible(windows->rows[i].name, 0);
                }
                windows->help->setVisible(windows->help, 0);
                windows->kind->setVisible(windows->kind, 0);
                windows->rows[i].times->setVisible(windows->rows[i].times, 0);
                windows->rows[i].count->setVisible(windows->rows[i].count, 0);
            }
        }
        func_80085EE4(panel, windows, panel->items[panel->cursor + panel->scroll]);
    } else {
        windows->listTitle->setVisible(windows->listTitle, 0);
        for (i = 0; i < 8; i++) {
            windows->rows[i].name->setVisible(windows->rows[i].name, 0);
            windows->rows[i].times->setVisible(windows->rows[i].times, 0);
            windows->rows[i].count->setVisible(windows->rows[i].count, 0);
        }
        windows->help->setVisible(windows->help, 0);
        windows->kind->setVisible(windows->kind, 0);
    }
}

/* The item in the slot being changed, or the slot's name if it's empty */
void func_80086368(StatusPanel4B *panel, StatusPanel4BWindows *windows, s32 show) {
    PartnerStats *stats;
    s32 item;

    if (show) {
        stats = (PartnerStats *)GAME_FUNCS.getPartnerStats(panel->partner);
        item = *(stats->equip + panel->slot); /* the match depends on this form */
        windows->slotTitle->setString(windows->slotTitle, FILE_CACHE.load(TEXT_FILE(0xB1)), 0x20);
        if (item > 0) {
            windows->slotItem->setString(windows->slotItem, FILE_CACHE.load(TEXT_FILE(0x6B)), item);
        } else {
            windows->slotItem->setString(windows->slotItem, FILE_CACHE.load(TEXT_FILE(0xB1)), D_80099AC0[panel->slot]);
        }
    } else {
        windows->slotTitle->setVisible(windows->slotTitle, 0);
        windows->slotItem->setVisible(windows->slotItem, 0);
    }
}

INCLUDE_ASM("ststatus/nonmatchings/ststatus_3", func_800864B0);

INCLUDE_ASM("ststatus/nonmatchings/ststatus_3", func_80086B28);

void func_80087914(StatusPanel4B *panel, void *children) {
    switch (panel->state) {
    case TASK_INIT:
    default:
        panel->nextState(panel);
        panel->scroll = 0;
        func_80085BD8(panel, children);
        panel->panels[3].duration = 10;
        panel->panels[1].duration = 10;
        panel->panels[2].duration = 10;
        panel->panels[0].duration = 10;
        break;
    case TASK_RUN:
        func_80086B28(panel, children);
        func_800864B0(panel);
        break;
    case TASK_KILL:
        panel->screen->unk70 = 0;
        /* fallthrough */
    case TASK_DONE:
        break;
    }
}

StatusPanel4B *func_800879C8(StatusScreen4 *screen) {
    StatusPanel4B *panel = createTask(func_80087914, sizeof(StatusPanel4B), 0xA4);

    panel->layer = 0x1000;
    panel->depth = 4;
    panel->screen = screen;
    panel->partner = GAME_FUNCS.getPartyMember(screen->member);
    return panel;
}
