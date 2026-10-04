/* The second object of STGTRAIN.PRO (see stgtrain.c), the training's run
   and its result (func_800867A0): its rodata starts at 0x8008251C (USA). */

#include "stgtrain.h"

/* Raises a battle stat (1-5) by the training's gain, up to 999 */
s32 func_800858E0(TrainResult *result, s32 stat) {
    PartnerStats *stats = (PartnerStats *)GAME.funcs.getPartnerStats(result->partner);
    s32 column = 6;
    s16 *value;
    s32 gained;

    if ((u32)(stat - 1) >= 5) {
        return 0;
    }
    value = &stats->stats[stat + 5];
    if (result->training < 0xD) {
        column = 0;
    }
    column += result->unkD8 * 3 + result->screen->unk7C;
    if (D_8008B80C[column].range != 0) {
        gained = D_8008B80C[column].base + RANDOM.next() % D_8008B80C[column].range;
    } else {
        gained = D_8008B80C[column].base;
    }
    *value += gained;
    if (*value >= 1000) {
        *value = 999;
    }
    return gained;
}

/* Lowers a battle stat (1-5) by the training's loss, half of the time, down to 0 */
s32 func_800859F4(TrainResult *result, s32 stat) {
    PartnerStats *stats = (PartnerStats *)GAME.funcs.getPartnerStats(result->partner);
    s16 *value;
    s32 lost;
    s32 column;

    if ((u32)(stat - 1) >= 5 || (RANDOM.next() & 1)) {
        return 0;
    }
    value = &stats->stats[stat + 5];
    column = result->screen->unk7C;
    if (D_8008B86C[column].range != 0) {
        lost = D_8008B86C[column].base + RANDOM.next() % D_8008B86C[column].range;
    } else {
        lost = D_8008B86C[column].base;
    }
    *value -= lost;
    if (*value < 0) {
        *value = 0;
    }
    return lost;
}

/*
 * Raises a resistance (stat 8-14) by the training's gain, up to 999: the
 * table goes by the Digimon's growth of it and how high it already is.
 */
s32 func_80085AF8(TrainResult *result, s32 stat) {
    PartnerStats *stats;
    s16 *value;
    DigimonData *digimon;
    TrainGain *gains;
    s32 column;
    s32 gained;
    s32 resist = stat - 8;

    if ((u32)resist >= 7) {
        return 0;
    }
    stats = (PartnerStats *)GAME.funcs.getPartnerStats(result->partner);
    digimon = &DIGIMON_DATA[result->partner];
    value = &stats->stats[stat + 4];
    if (*value < 100) {
        gains = D_8008B95C[(digimon->resistGrowth[resist] - 1) * 3];
    } else if (*value < 300) {
        gains = D_8008B95C[(digimon->resistGrowth[resist] - 1) * 3 + 1];
    } else {
        gains = D_8008B95C[(digimon->resistGrowth[resist] - 1) * 3 + 2];
    }
    /* the match depends on column being set in each branch: set before the
       test, its delay slot copy keeps a0 live where the table's lui wants it */
    if (result->unkD8 == 0) {
        column = 0;
    } else if (result->training < 0xD) {
        column = 1;
    } else {
        column = 2;
    }
    column += result->screen->unk7C * 3;
    if (gains[column].range != 0) {
        gained = gains[column].base + RANDOM.next() % gains[column].range;
    } else {
        gained = gains[column].base;
    }
    *value += gained;
    if (*value >= 1000) {
        *value = 999;
    }
    return gained;
}


/*
 * Raises the maximum HP (stat 15) or MP (16) by the training's gain, up to
 * 9999; the US version also raises the current value, up to the maximum.
 */
s32 func_80085CC4(TrainResult *result, s32 stat) {
    PartnerStats *stats;
    s16 *value;
#if VERSION_US
    s16 *current;
#endif
    s32 column;
    s32 gained;

    if ((u32)(stat - 15) >= 2) {
        return 0;
    }
    stats = (PartnerStats *)GAME.funcs.getPartnerStats(result->partner);
    if (stat == 15) {
        value = &stats->stats[3];
#if VERSION_US
        current = &stats->stats[2];
#endif
    } else {
        value = &stats->stats[5];
#if VERSION_US
        current = &stats->stats[4];
#endif
    }
    column = 0;
    if (result->unkD8 != 0) {
        if (result->training < 0xD) {
            column = 1;
        } else {
            column = 2;
        }
    }
    column += result->screen->unk7C * 3;
    if (D_8008B998[column].range != 0) {
        gained = D_8008B998[column].base + RANDOM.next() % D_8008B998[column].range;
    } else {
        gained = D_8008B998[column].base;
    }
    *value += gained;
    if (*value >= 10000) {
        *value = 9999;
    }
#if VERSION_US
    *current += gained;
    if (*current > *value) {
        *current = *value;
    }
#endif
    return gained;
}

/*
 * Applies the i-th try of a training (if it worked) and shows what it
 * changed: the stat it raises, and the one it lowers or also raises.
 */
void func_80085E30(TrainResult *result, s32 i) {
    TrainResultWindows *win = result->children;
    TrainEntry *entry = (TrainEntry *)D_8008C4D4.findTableEntry(result->modeArg, result->training);

    if (result->trained[i] != 0) {
        /* The match depends on stat (and other below) being s16 locals. */
        s16 stat = entry->stat;

        if (stat != 0) {
            if ((u16)stat - 1 < 5u) {
                result->gains[i] = func_800858E0(result, stat);
            } else {
                result->gains[i] = func_80085AF8(result, stat);
                stat = entry->other;
                if (stat != 0) {
                    if ((u16)stat - 1 < 5u) {
                        result->losses[i] = func_800859F4(result, stat);
                    } else {
                        result->losses[i] = func_80085CC4(result, stat);
                    }
                }
            }
        }
    }
    if (result->trained[i] != 0) {
        if ((u16)entry->stat - 1 < 5u) {
            win->message[0]->setString(win->message[0], FILE_CACHE.load(STGTRAIN_TEXT), 0x5C);
            win->message[0]->setSubString(win->message[0], FILE_CACHE.load(STGTRAIN_TEXT), entry->stat + 0x46, 1);
            win->message[0]->setNumber(win->message[0], 2, result->gains[i]);
            win->message[0]->setPalette(win->message[0], 1);
            win->message[1]->setVisible(win->message[1], 0);
        } else {
            s16 other;

            win->message[0]->setString(win->message[0], FILE_CACHE.load(STGTRAIN_TEXT), 0x5C);
            win->message[0]->setSubString(win->message[0], FILE_CACHE.load(STGTRAIN_TEXT), entry->stat + 0x4D, 1);
            win->message[0]->setNumber(win->message[0], 2, result->gains[i]);
            win->message[0]->setPalette(win->message[0], 1);
            other = entry->other;
            if (other != 0) {
                if ((u16)other - 1 < 5u) {
                    if (result->losses[i] != 0) {
                        win->message[1]->setString(win->message[1], FILE_CACHE.load(STGTRAIN_TEXT), 0x5D);
                        win->message[1]->setSubString(win->message[1], FILE_CACHE.load(STGTRAIN_TEXT), entry->other + 0x46, 1);
                        win->message[1]->setNumber(win->message[1], 2, result->losses[i]);
                        win->message[1]->setPalette(win->message[1], 5);
                    } else {
                        win->message[1]->setVisible(win->message[1], 0);
                    }
                } else {
                    win->message[1]->setString(win->message[1], FILE_CACHE.load(STGTRAIN_TEXT), 0x5C);
                    win->message[1]->setSubString(win->message[1], FILE_CACHE.load(STGTRAIN_TEXT), entry->other + 0x44, 1);
                    win->message[1]->setNumber(win->message[1], 2, result->losses[i]);
                    win->message[1]->setPalette(win->message[1], 1);
                }
            }
        }
    } else {
        win->message[0]->setString(win->message[0], FILE_CACHE.load(STGTRAIN_TEXT), 0x46);
        win->message[0]->setPalette(win->message[0], 0);
        win->message[1]->setVisible(win->message[1], 0);
    }
}

/* The bonus of the accessories 0x151 (3) and 0x152 (6) */
s32 func_800861F0(TrainResult *result) {
    PartnerStats *stats = (PartnerStats *)GAME.funcs.getPartnerStats(result->partner);

    if (stats->equip[4] == 0x151 || stats->equip[5] == 0x151) {
        return 3;
    }
    if (stats->equip[4] == 0x152 || stats->equip[5] == 0x152) {
        return 6;
    }
    return 0;
}

void func_80086258(TrainResult *result, TrainResultWindows *win) {
    win->message[0] = createTextWindow(result->layerId, 1, 0x74, 0xC0);
    win->message[0]->setLines(win->message[0], 2);
    win->message[1] = createTextWindow(result->layerId, 1, 0x74, 0xCE);
    win->unk8[0] = createTextWindow(0x1002, 1, 0xA2, 0x75);
    win->unk8[1] = createTextWindow(0x1002, 1, 0xA2, 0x91);
    win->unk8[2] = createTextWindow(0x1002, 1, 0xA2, 0xA1);
    win->cursor = createCursor(0x1002, result->depth - 1, 0x94, 0x91);
    win->cursor->setVisible(win->cursor, 0);
}

/*
 * Draws the training result: the blinking arrow, a mark for each try (0x45
 * worked, 0x46 failed) and the four panels.
 */
void func_80086340(TrainResult *result) {
    SpriteDrawer sprite;
    s32 i;

    if (result->unkE4 != 0) {
        initSpriteDrawer(&sprite);
        sprite.setLayerId(0x1002, 3);
        sprite.setTexture(0x140, 0);
        if (GFX.funcs.getTime() - result->unkEC >= 4) {
            result->unkEC = GFX.funcs.getTime();
            result->unkE8++;
            if (result->unkE8 >= 5) {
                result->unkE8 = 0;
            }
        }
        sprite.setClutRow(result->unkE8);
        sprite.draw(FILE_CACHE.getEntry(FILE_MENU_SPRITES << 16), 0xA, 0x124, 0xCD);
    }
    initSpriteDrawer(&sprite);
    sprite.setTexture(0x240, 0x100);
    sprite.setLayerId(result->layerId, result->depth);
    if (result->unkD4 != 0) {
        if (GFX.funcs.getTime() - result->unkE0 >= 3) {
            result->unkE0 = GFX.funcs.getTime();
            result->unkDC = 1 - result->unkDC;
        }
        sprite.setClutRow(result->unkDC + 1);
    }
    for (i = 0; i < 5; i++) {
        if (result->unkD8 != 0 && i == 3) {
            sprite.setClutRow(3);
        }
        if (result->trained[i] == 1) {
            sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x45, i * 0x11 + 0x80, 0x58);
        } else if (result->trained[i] == 0) {
            sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x46, i * 0x11 + 0x80, 0x58);
        }
    }
    sprite.setClutRow(0);
    if (result->panels[0].level != 0) {
        if (result->panels[0].level != 0x1000) {
            sprite.setScale(result->panels[0].level, result->panels[0].level, 0x1000);
            sprite.setPivot(0xCF, 0x7F);
        }
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x28, 0x72, 0x4B);
    }
    if (result->panels[1].level != 0) {
        if (result->panels[1].level != 0x1000) {
            sprite.setScale(result->panels[1].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0xCD);
        }
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x23, 0x46, 0xBA);
    }
    sprite.setLayerId(0x1002, result->depth);
    if (result->panels[2].level != 0) {
        if (result->panels[2].level != 0x1000) {
            sprite.setScale(result->panels[2].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x7B);
        }
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x26, 0x85, 0x70);
    }
    if (result->panels[3].level != 0) {
        if (result->panels[3].level != 0x1000) {
            sprite.setScale(result->panels[3].level, 0x1000, 0x1000);
            sprite.setPivot(0x140, 0x9F);
        }
        sprite.draw(FILE_CACHE.getEntry(STGTRAIN_SPRITES), 0x1D, 0x82, 0x8B);
    }
}

#if VERSION_EU
/* A battle stat (1-5) or a resistance (8-14) of TOTALS: the match depends on
   reading them through these (indexed in place, the stat's address is
   summed with the index first) */
static inline s16 getStat(TrainTotals *totals, s32 stat) {
    return totals->stats[stat - 1];
}

static inline s16 getResistance(TrainTotals *totals, s32 stat) {
    return totals->resistances[stat - 8];
}
#endif

/*
 * Runs a training: the partner tries it three times (five at the gyms'
 * second half), then shows what it gained. Three good tries in a row give
 * a bonus try, asked for (with the training as the partner's last) after
 * the gyms' first half.
 */
void func_800867A0(TrainResult *result, TrainResultWindows *win) {
    TrainEntry *entry;
    PartnerStats *stats;
    s32 sums[2];
#if VERSION_EU
    s32 shown[2]; /* the sums, up to the stats' limits */
    s16 other;
#endif
    s32 i;
    s32 last;

    switch (result->substate) {
    case 0:
    default:
        D_8008C4D4.startFade(&result->panels[0], 1);
        D_8008C4D4.startFade(&result->panels[1], 1);
        win->actor->grow(win->actor);
        result->substate++;
        break;
    case 1:
        D_8008C4D4.updateFade(&result->panels[1]);
        if (D_8008C4D4.updateFade(&result->panels[0]) && (win->actor->mode & 1)) {
            result->counter = 2;
            result->substate++;
            win->actor->play(win->actor);
            win->actor->setChance(win->actor, func_800861F0(result) + 0x4B);
        }
        break;
    case 2:
        result->trained[result->step] = win->actor->getResult(win->actor);
        if (result->trained[result->step] != -1) {
            if (result->trained[result->step] != 0) {
                SOUND.playSound(0x840001);
            } else {
                SOUND.playSound(0x840000);
            }
            func_80085E30(result, result->step);
            result->step++;
            if (result->counter < result->step) {
                if (result->counter == 2) {
                    if (result->trained[0] != 0 && result->trained[1] != 0 && result->trained[2] != 0) {
                        result->substate = 0xA;
                        break;
                    }
                    if (result->training >= 0xD) {
                        result->counter = 4;
                        win->actor->play(win->actor);
                        break;
                    }
                }
                result->setSubstate(result, 3);
            } else {
                win->actor->play(win->actor);
            }
        }
        break;
    case 3:
        win->actor->end(win->actor);
        result->substate++;
        break;
    case 4:
        if (win->actor->mode & 1) {
            result->unkE4 = 1;
            result->substate++;
        }
        break;
    case 5:
        if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x4001C);
            result->unkE4 = 0;
            entry = (TrainEntry *)D_8008C4D4.findTableEntry(result->modeArg, result->training);
            if (entry->stat != 0) {
                sums[0] = 0;
                for (i = 0; i < 5; i++) {
                    sums[0] += result->gains[i];
                }
                if ((u16)entry->stat - 8 < 7u) {
                    if (entry->other != 0) {
                        sums[1] = 0;
                        for (i = 0; i < 5; i++) {
                            sums[1] += result->losses[i];
                        }
                    }
                } else {
                    sums[1] = 0;
                }
            }
            if (sums[0] == 0 && sums[1] == 0) {
                win->message[0]->setString(win->message[0], FILE_CACHE.load(STGTRAIN_TEXT), 0x71);
            } else {
#if VERSION_EU
                for (i = 0; i < 2; i++) {
                    shown[i] = sums[i];
                }
                if (sums[0] != 0) {
                    if ((u16)entry->stat - 1 < 5u) {
                        if (getStat(&result->before, entry->stat) + sums[0] >= 1000) {
                            shown[0] = 999 - getStat(&result->before, entry->stat);
                        } else {
                            shown[0] = sums[0];
                        }
                    } else {
                        if (getResistance(&result->before, entry->stat) + sums[0] >= 1000) {
                            shown[0] = 999 - getResistance(&result->before, entry->stat);
                        } else {
                            shown[0] = sums[0];
                        }
                    }
                }
                if (sums[1] != 0) {
                    other = entry->other;
                    if ((u16)other - 1 < 5u) {
                        if (getStat(&result->before, other) - sums[1] < 0) {
                            shown[1] = getStat(&result->before, other);
                        } else {
                            shown[1] = sums[1];
                        }
                    } else if ((u16)(other - 8) < 7) {
                        if (getResistance(&result->before, other) + sums[1] >= 1000) {
                            shown[1] = 999 - getResistance(&result->before, other);
                        } else {
                            shown[1] = sums[1];
                        }
                    } else if (other == 15) {
                        if (result->before.maxHp + sums[1] >= 10000) {
                            shown[1] = 9999 - result->before.maxHp;
                        } else {
                            shown[1] = sums[1];
                        }
                    } else if (other == 16) {
                        if (result->before.maxMp + sums[1] >= 10000) {
                            shown[1] = 9999 - result->before.maxMp;
                        } else {
                            shown[1] = sums[1];
                        }
                    }
                }
#endif
                if ((u16)entry->stat - 1 < 5u) {
                    win->message[0]->setString(win->message[0], FILE_CACHE.load(STGTRAIN_TEXT), entry->stat + 0x5D);
#if VERSION_US
                    win->message[0]->setNumber(win->message[0], 1, sums[0]);
#elif VERSION_EU
                    win->message[0]->setNumber(win->message[0], 1, shown[0]);
#endif
                } else if (sums[1] != 0) {
                    win->message[0]->setString(win->message[0], FILE_CACHE.load(STGTRAIN_TEXT), entry->stat + 0x62);
#if VERSION_US
                    win->message[0]->setNumber(win->message[0], 1, sums[0]);
#elif VERSION_EU
                    win->message[0]->setNumber(win->message[0], 1, shown[0]);
#endif
#if VERSION_US
                    win->message[0]->setNumber(win->message[0], 2, sums[1]);
#elif VERSION_EU
                    win->message[0]->setNumber(win->message[0], 2, shown[1]);
#endif
                } else {
                    win->message[0]->setString(win->message[0], FILE_CACHE.load(STGTRAIN_TEXT), entry->stat + 0x5B);
#if VERSION_US
                    win->message[0]->setNumber(win->message[0], 1, sums[0]);
#elif VERSION_EU
                    win->message[0]->setNumber(win->message[0], 1, shown[0]);
#endif
                }
            }
            win->message[0]->setPalette(win->message[0], 0);
            win->message[0]->setTypeDelay(win->message[0], 6);
            win->message[1]->setVisible(win->message[1], 0);
            result->substate++;
            result->screen->showStats(result->screen, &result->before);
        }
        break;
    case 6:
        if (win->message[0]->isFinished(win->message[0])) {
            SOUND.playSound(0x4001C);
            result->substate = 0x32;
            result->unkE4 = 0;
            result->screen->showStats(result->screen, NULL);
        } else if (win->message[0]->isWaitingForButton(win->message[0])) {
            result->unkE4 = 1;
            if (PAD_PRESSED(PAD_CROSS)) {
                SOUND.playSound(0x4001C);
                result->unkE4 = 0;
            }
        } else {
            result->unkE4 = 0;
            if (PAD_PRESSED(PAD_CROSS)) {
                win->message[0]->showPage(win->message[0]);
            }
        }
        break;
    case 0xA:
        if (result->training < 0xD) {
            result->substate = 0x14;
            result->unkD4 = 1;
            win->actor->play(win->actor);
            result->unkF0 = SOUND.playSound(0xA084603C);
        } else {
            result->substate++;
        }
        break;
    case 0xB:
        D_8008C4D4.startFade(&result->panels[2], 1);
        result->substate++;
        break;
    case 0xC:
        if (D_8008C4D4.updateFade(&result->panels[2])) {
            win->unk8[0]->setString(win->unk8[0], FILE_CACHE.load(STGTRAIN_TEXT), 0x11);
            D_8008C4D4.startFade(&result->panels[3], 1);
            result->substate++;
        }
        break;
    case 0xD:
        if (D_8008C4D4.updateFade(&result->panels[3])) {
            win->unk8[1]->setString(win->unk8[1], FILE_CACHE.load(STGTRAIN_TEXT), 0xC);
            win->unk8[2]->setString(win->unk8[2], FILE_CACHE.load(STGTRAIN_TEXT), 0xD);
            win->cursor->setPos(win->cursor, 0x94, result->before.unk2C * 16 + 0x91);
            win->cursor->setVisible(win->cursor, 1);
            result->substate++;
        }
        break;
    case 0xE:
        last = result->before.unk2C;
        if (PAD_PRESSED(PAD_UP) || PAD_REPEATED(PAD_UP)) {
            result->before.unk2C = 0;
        } else if (PAD_PRESSED(PAD_DOWN) || PAD_REPEATED(PAD_DOWN)) {
            result->before.unk2C = 1;
        }
        if (last != result->before.unk2C) {
            SOUND.playSound(0x8004513E);
            win->cursor->setPos(win->cursor, 0x94, result->before.unk2C * 16 + 0x91);
        } else if (PAD_PRESSED(PAD_CROSS)) {
            SOUND.playSound(0x8004503C);
            if (result->before.unk2C == 0) {
                result->counter = 0;
                result->substate++;
            } else {
                result->counter = 4;
                result->substate++;
            }
        } else if (PAD_PRESSED(PAD_TRIANGLE)) {
            SOUND.playSound(0x800450BD);
            result->counter = 4;
            result->substate++;
        }
        break;
    case 0xF:
        D_8008C4D4.startFade(&result->panels[2], 0);
        D_8008C4D4.startFade(&result->panels[3], 0);
        win->unk8[0]->setVisible(win->unk8[0], 0);
        win->unk8[1]->setVisible(win->unk8[1], 0);
        win->unk8[2]->setVisible(win->unk8[2], 0);
        win->cursor->setVisible(win->cursor, 0);
        result->substate++;
        break;
    case 0x10:
        D_8008C4D4.updateFade(&result->panels[2]);
        if (D_8008C4D4.updateFade(&result->panels[3])) {
            if (result->counter == 0) {
                result->substate = 0x14;
                result->unkD4 = 1;
                win->actor->play(win->actor);
                result->unkF0 = SOUND.playSound(0xA084603C);
                stats = (PartnerStats *)GAME.funcs.getPartnerStats(result->partner);
                if (stats->unk3CC[0] != 0 && stats->unk3CC[0] == result->training) {
                    win->actor->setChance(win->actor, 0);
                } else {
                    stats->unk3CC[0] = 0;
                    win->actor->setChance(win->actor, 0x32);
                }
            } else {
                win->actor->play(win->actor);
                result->substate = 2;
            }
        }
        break;
    case 0x14:
        result->trained[3] = win->actor->getResult(win->actor);
        if (result->trained[3] != -1) {
            stats = (PartnerStats *)GAME.funcs.getPartnerStats(result->partner);
            if (result->trained[3] != 0) {
                stats->unk3CC[0] = result->training;
                result->unkD8 = 1;
            } else {
                stats->unk3CC[0] = 0;
            }
            if (result->trained[3] != 0) {
                SOUND.playSound(0x840001);
            } else {
                SOUND.playSound(0x840000);
            }
            SOUND.keyOff(0xA084603C, result->unkF0);
            func_80085E30(result, 3);
            result->unkE4 = 1;
            result->unkD4 = 0;
            result->setSubstate(result, 3);
        }
        break;
    case 0x32:
        result->state = TASK_KILL;
        break;
    }
}


/* The training result's task. The match depends on the -1 being in a variable. */
void func_800874A0(TrainResult *result, TrainResultWindows *win) {
    s32 i;

    switch (result->state) {
    case TASK_INIT:
    default:
        result->nextState(result);
        func_80086258(result, win);
        result->panels[0].duration = 10;
        result->panels[1].duration = 10;
        result->panels[2].duration = 10;
        result->panels[3].duration = 10;
        {
            s32 none = -1;
            for (i = 4; i >= 0; i--) {
                result->trained[i] = none;
            }
        }
        win->actor = func_800897B8(result->partner, result->training, result->layerId, result->depth - 3);
        win->actor->setPos(win->actor, 0x300, 0);
        win->actor->setClutPos(win->actor, 0x2C0, 0);
        win->actor->pause(win->actor);
        win->actor->setScale(win->actor, 0);
        GAME.funcs.computeStats(result->partner, (PartnerTotals *)&result->before);
        break;
    case TASK_RUN:
        func_800867A0(result, win);
        func_80086340(result);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

/* Creates the results of a training of a partner */
TrainResult *func_800875E8(TrainScreen *screen, s32 partner, s32 training) {
    TrainResult *result = createTask(func_800874A0, sizeof(TrainResult), sizeof(TrainResultWindows));

    result->layerId = 0x1000;
    result->depth = 6;
    result->screen = screen;
    result->partner = partner;
    result->training = training;
    result->modeArg = GAME.funcs.getModeArg();
    return result;
}

void func_80087678(TrainIdle *task, void *children) {
}

void func_80087680(TrainIdle *task, void *children, s32 arg2) {
}

void func_80087688(TrainIdle *task) {
    SpriteDrawer sprite;

    initSpriteDrawer(&sprite);
}

void func_800876A8(TrainIdle *task, void *children) {
}

void func_800876B0(TrainIdle *task, void *children) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
        func_80087678(task, children);
        func_80087680(task, children, 1);
        break;
    case TASK_RUN:
        func_800876A8(task, children);
        func_80087688(task);
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

TrainIdle *func_80087744(TrainScreen *screen) {
    TrainIdle *task = createTask(func_800876B0, sizeof(TrainIdle), 0);

    task->layerId = 0x1000;
    task->depth = 6;
    task->screen = screen;
    return task;
}
