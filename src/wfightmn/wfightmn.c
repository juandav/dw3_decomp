#include "wfightmn.h"

/* Loads the battle menu's images into VRAM, one file a frame, then its
   other files, and ends */
void WFIGHTMN_loadFiles(Task *task) {
    switch (task->state) {
    case TASK_INIT:
    default:
        task->nextState(task);
    case TASK_RUN:
        switch (task->substate) {
        case 0:
        default:
            switch (task->step) {
            case 0:
            default:
                FILE_CACHE.request(FILE_BATTLE_IMAGES);
                FILE_CACHE.request(FILE_BATTLE_IMAGES_1);
                FILE_CACHE.request(FILE_BATTLE_IMAGES_2);
                FILE_CACHE.request(FILE_BATTLE_IMAGES_3);
                FILE_CACHE.request(FILE_BATTLE_IMAGES_4);
                task->nextStep(task);
                break;
            case 1:
                if (FILE_CACHE.isLoading(FILE_BATTLE_IMAGES) == 0) {
                    TimLoader loader;

                    initTimLoader(&loader);
                    loader.setImagePos(0x200, 0);
                    loader.loadArchive(FILE_CACHE.getEntry(FILE_BATTLE_IMAGES << 16 | 1));
                    loader.setImagePos(0, 0xF4);
                    loader.load(FILE_CACHE.getEntry(FILE_BATTLE_IMAGES << 16));
                    task->nextStep(task);
                }
                break;
            case 2:
                if (FILE_CACHE.isLoading(FILE_BATTLE_IMAGES_1) == 0) {
                    TimLoader loader;

                    initTimLoader(&loader);
                    loader.setImagePos(0x140, 0x100);
                    loader.loadArchive(FILE_CACHE.load(FILE_BATTLE_IMAGES_1));
                    task->nextStep(task);
                }
                break;
            case 3:
                if (FILE_CACHE.isLoading(FILE_BATTLE_IMAGES_2) == 0) {
                    TimLoader loader;

                    initTimLoader(&loader);
                    loader.setImagePos(0x1C0, 0x100);
                    loader.loadArchive(FILE_CACHE.load(FILE_BATTLE_IMAGES_2));
                    task->nextStep(task);
                }
                break;
            case 4:
                if (FILE_CACHE.isLoading(FILE_BATTLE_IMAGES_3) == 0) {
                    TimLoader loader;

                    initTimLoader(&loader);
                    loader.setImagePos(0x200, 0x100);
                    loader.loadArchive(FILE_CACHE.load(FILE_BATTLE_IMAGES_3));
                    task->nextStep(task);
                }
                break;
            case 5:
                if (FILE_CACHE.isLoading(FILE_BATTLE_IMAGES_4) == 0) {
                    TimLoader loader;

                    initTimLoader(&loader);
                    loader.setImagePos(0x240, 0x100);
                    loader.loadArchive(FILE_CACHE.load(FILE_BATTLE_IMAGES_4));
                    task->nextStep(task);
                }
                break;
            case 6:
                FILE_CACHE.free(FILE_BATTLE_IMAGES);
                FILE_CACHE.free(FILE_BATTLE_IMAGES_1);
                FILE_CACHE.free(FILE_BATTLE_IMAGES_2);
                FILE_CACHE.free(FILE_BATTLE_IMAGES_3);
                FILE_CACHE.free(FILE_BATTLE_IMAGES_4);
                task->nextSubstate(task);
                break;
            }
            break;
        case 1:
            switch (task->step) {
            case 0:
            default:
                FILE_CACHE.request(FILE_MENU_SPRITES);
                FILE_CACHE.request(FILE_BATTLE_MENU);
                FILE_CACHE.request(TEXT_FILE(0x80));
                FILE_CACHE.request(TEXT_FILE(0x4F));
                FILE_CACHE.request(TEXT_FILE(0xA3));
                FILE_CACHE.request(TEXT_FILE(0x9C));
                FILE_CACHE.request(TEXT_FILE(0x6B));
                FILE_CACHE.request(TEXT_FILE(0x64));
                task->nextStep(task);
                break;
            case 1:
                if (FILE_CACHE.isLoading(FILE_MENU_SPRITES) == 0 && FILE_CACHE.isLoading(FILE_BATTLE_MENU) == 0 &&
                    FILE_CACHE.isLoading(TEXT_FILE(0x80)) == 0 && FILE_CACHE.isLoading(TEXT_FILE(0x4F)) == 0 &&
                    FILE_CACHE.isLoading(TEXT_FILE(0xA3)) == 0 && FILE_CACHE.isLoading(TEXT_FILE(0x9C)) == 0 &&
                    FILE_CACHE.isLoading(TEXT_FILE(0x6B)) == 0 && FILE_CACHE.isLoading(TEXT_FILE(0x64)) == 0) {
                    task->setState(task, TASK_KILL);
                }
                break;
            }
            break;
        }
        break;
    case TASK_DONE:
    case TASK_KILL:
        break;
    }
}

Task *WFIGHTMN_createLoader(void) {
    return createTask(WFIGHTMN_loadFiles, 0x54, 0);
}
