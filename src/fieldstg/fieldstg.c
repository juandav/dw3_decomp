/* The first object of FIELDSTG.PRO, and the overlay's data. FIELDSTG.PRO was
   at least five objects: each one's jump tables are aligned to 8 from the
   start of its own rodata, and the tables at 0x800824C4, 0x80082598,
   0x800825CC and 0x800825E0 (USA) each start right where the one before
   ends, 4 bytes past a multiple of 8 from the start of the object before, so
   each one starts a new object. Where each object's code starts is only
   known to be between the function with the last jump table of the object
   before and the one with its first; the data is all here. */

#include "fieldstg.h"

void func_80082F1C(Task *task) {
    switch (task->state) {
    case 0:
    case 1:
    default:
        if (task->substate == 1) {
            func_80090154();
            task->setSubstate(task, 0);
        }
        break;
    case 2:
    case 3:
        break;
    }
}

/*
 * The field's commands (0x337 to 0x386) that the stage overlays send: the
 * field task's substate, map objects 100 to 105 hidden or shown, and
 * sounds, three of which are held to be keyed off later.
 */
void func_80082F84(Task *task, s32 command) {
    MapObject *object;
    Task *field;
    s32 n;

    if (task == NULL) {
        return;
    }
    n = 0;
    if (command == 0x337) {
        task->setSubstate(task, 1);
    }
    switch (command) {
    case 0x34A:
        n++;
    case 0x339:
        n++;
    case 0x338:
        n++;
        field = TASK_FUNCS.find(0x16, -1, -1);
        field->setSubstate(field, n);
        break;
    }
    switch (command) {
    case 0x34D ... 0x352:
        for (object = (MapObject *)D_800990B4.unk10; object->unk2 != 0; object++) {
            if (object->id == command - 0x2E9) {
                object->unk0 = 0;
            }
        }
        break;
    case 0x353 ... 0x358:
        for (object = (MapObject *)D_800990B4.unk10; object->unk2 != 0; object++) {
            if (object->id == command - 0x2EF) {
                object->unk0 = 1;
            }
        }
        break;
    }
    switch (command) {
    case 0x372:
        func_8008D07C(1);
        break;
    case 0x373:
        func_8008D07C(0);
        break;
    }
    if (command == 0x376) {
        func_8008C23C();
    }
    switch (command) {
    case 0x365:
        SOUND.playSound(0xB80001);
        break;
    case 0x368:
        SOUND.playSound(0x80E8383C);
        break;
    case 0x369:
        SOUND.playSound(0x60040002);
        break;
    case 0x36A:
        SOUND.playSound(0xA40006);
        break;
    case 0x36B:
        SOUND.playSound(0x805458BD);
        break;
    case 0x36C:
        SOUND.playSound(0x800410BD);
        break;
    case 0x36D:
        SOUND.playSound(0x803C503C);
        break;
    case 0x36E:
        SOUND.playSound(0x01100000);
        break;
    case 0x36F:
        SOUND.playSound(0x01100002);
        break;
    case 0x374:
        SOUND.playSound(0x700001);
        break;
    case 0x375:
        SOUND.playSound(0x40015);
        break;
    case 0x377:
        SOUND.playSound(0x8004113E);
        break;
    case 0x378:
        SOUND.playSound(0x8110303C);
        break;
    case 0x379:
        SOUND.playSound(0x81103240);
        break;
    case 0x37A:
        SOUND.playSound(0x4001D);
        break;
    case 0x37C:
        SOUND.playSound(0x440001);
        break;
    case 0x37D:
        SOUND.playSound(0x340004);
        break;
    case 0x37E:
        SOUND.playSound(0x40013);
        break;
    case 0x37F:
        SOUND.playSound(0x800429BF);
        break;
    case 0x380:
        SOUND.playSound(0x800430BD);
        break;
    case 0x381:
        SOUND.playSound(0x80042DC7);
        break;
    case 0x383:
        SOUND.playSound(0x8004103C);
        break;
    }
    switch (command) {
    case 0x366:
        D_8009A934 = SOUND.playSound(0xA10C703C);
        break;
    case 0x370:
        D_8009A934 = SOUND.playSound(0xA0045EC9);
        break;
    case 0x382:
        D_8009A934 = SOUND.playSound(0xA054583C);
        break;
    case 0x384:
        D_8009A934 = SOUND.playSound(0xA0042FCB);
        break;
    }
    switch (command) {
    case 0x367:
        SOUND.keyOff(0xA10C703C, D_8009A934);
        break;
    case 0x371:
        SOUND.keyOff(0xA0045EC9, D_8009A934);
        break;
    case 0x385:
        SOUND.keyOff(0xA0042FCB, D_8009A934);
        break;
    case 0x386:
        SOUND.keyOff(0xA054583C, D_8009A934);
        break;
    }
}

void func_80083470(void) {
    createTaskWithId(func_80082F1C, sizeof(Task), 0, 0x32D);
}

/*
 * The field's data, after the code that uses it: its tables point to each
 * other and to the functions above (and to the stage overlay's, at fixed
 * addresses). The versions differ where #if says.
 */

extern BattleEnemy D_800920A8;
extern BattleEnemy D_800920B4;
extern BattleEnemy D_800920C0;
extern BattleEnemy D_800920CC;
extern BattleEnemy D_800920D8;
extern BattleEnemy D_800920E4;
extern BattleEnemy D_800920F0;
extern BattleEnemy D_800920FC;
extern BattleEnemy D_80092108;
extern BattleEnemy D_80092114;
extern BattleEnemy D_80092120;
extern BattleEnemy D_8009212C;
extern BattleEnemy D_80092138;
extern BattleEnemy D_80092144;
extern BattleEnemy D_80092150;
extern BattleEnemy D_8009215C;
extern BattleEnemy D_80092168;
extern BattleEnemy D_80092174;
extern BattleEnemy D_80092180;
extern BattleEnemy D_8009218C;
extern BattleEnemy D_80092198;
extern BattleEnemy D_800921A4;
extern BattleEnemy D_800921B0;
extern BattleEnemy D_800921BC;
extern BattleEnemy D_800921C8;
extern BattleEnemy D_800921D4;
extern BattleEnemy D_800921E0;
extern BattleEnemy D_800921EC;
extern BattleEnemy D_800921F8;
extern BattleEnemy D_80092204;
extern BattleEnemy D_80092210;
extern BattleEnemy D_8009221C;
extern BattleEnemy D_80092228;
extern BattleEnemy D_80092234;
extern BattleEnemy D_80092240;
extern BattleEnemy D_8009224C;
extern BattleEnemy D_80092258;
extern BattleEnemy D_80092264;
extern BattleEnemy D_80092270;
extern BattleEnemy D_8009227C;
extern BattleEnemy D_80092288;
extern BattleEnemy D_80092294;
extern BattleEnemy D_800922A0;
extern BattleEnemy D_800922AC;
extern BattleEnemy D_800922B8;
extern BattleEnemy D_800922C4;
extern BattleEnemy D_800922D0;
extern BattleEnemy D_800922DC;
extern BattleEnemy D_800922E8;
extern BattleEnemy D_800922F4;
extern BattleEnemy D_80092300;
extern BattleEnemy D_8009230C;
extern BattleEnemy D_80092318;
extern BattleEnemy D_80092324;
extern BattleEnemy D_80092330;
extern BattleEnemy D_8009233C;
extern BattleEnemy D_80092348;
extern BattleEnemy D_80092354;
extern BattleEnemy D_80092360;
extern BattleEnemy D_8009236C;
extern BattleEnemy D_80092378;
extern BattleEnemy D_80092384;
extern BattleEnemy D_80092390;
extern BattleEnemy D_8009239C;
extern BattleEnemy D_800923A8;
extern BattleEnemy D_800923B4;
extern BattleEnemy D_800923C0;
extern BattleEnemy D_800923CC;
extern BattleEnemy D_800923D8;
extern BattleEnemy D_800923E4;
extern BattleEnemy D_800923F0;
extern BattleEnemy D_800923FC;
extern BattleEnemy D_80092408;
extern BattleEnemy D_80092414;
extern BattleEnemy D_80092420;
extern BattleEnemy D_8009242C;
extern BattleEnemy D_80092438;
extern BattleEnemy D_80092444;
extern BattleEnemy D_80092450;
extern BattleEnemy D_8009245C;
extern BattleEnemy D_80092468;
extern BattleEnemy D_80092474;
extern BattleEnemy D_80092480;
extern BattleEnemy D_8009248C;
extern BattleEnemy D_80092498;
extern BattleEnemy D_800924A4;
extern BattleEnemy D_800924B0;
extern BattleEnemy D_800924BC;
extern BattleEnemy D_800924C8;
extern BattleEnemy D_800924D4;
extern BattleEnemy D_800924E0;
extern BattleEnemy D_800924EC;
extern BattleEnemy D_800924F8;
extern BattleEnemy D_80092504;
extern BattleEnemy D_80092510;
extern BattleEnemy D_8009251C;
extern BattleEnemy D_80092528;
extern BattleEnemy D_80092534;
extern BattleEnemy D_80092540;
extern BattleEnemy D_8009254C;
extern BattleEnemy D_80092558;
extern BattleEnemy D_80092564;
extern BattleEnemy D_80092570;
extern BattleEnemy D_8009257C;
extern BattleEnemy D_80092588;
extern BattleEnemy D_80092594;
extern BattleEnemy D_800925A0;
extern BattleEnemy D_800925AC;
extern BattleEnemy D_800925B8;
extern BattleEnemy D_800925C4;
extern BattleEnemy D_800925D0;
extern BattleEnemy D_800925DC;
extern BattleEnemy D_800925E8;
extern BattleEnemy D_800925F4;
extern BattleEnemy D_80092600;
extern BattleEnemy D_8009260C;
extern BattleEnemy D_80092618;
extern BattleEnemy D_80092624;
extern BattleEnemy D_80092630;
extern BattleEnemy D_8009263C;
extern BattleEnemy D_80092648;
extern BattleEnemy D_80092654;
extern BattleEnemy D_80092660;
extern BattleEnemy D_8009266C;
extern BattleEnemy D_80092678;
extern BattleEnemy D_80092684;
extern BattleEnemy D_80092690;
extern BattleEnemy D_8009269C;
extern BattleEnemy D_800926A8;
extern BattleEnemy D_800926B4;
extern BattleEnemy D_800926C0;
extern BattleEnemy D_800926CC;
extern BattleEnemy D_800926D8;
extern BattleEnemy D_800926E4;
extern BattleEnemy D_800926F0;
extern BattleEnemy D_800926FC;
extern BattleEnemy D_80092708;
extern BattleEnemy D_80092714;
extern BattleEnemy D_80092720;
extern BattleEnemy D_8009272C;
extern BattleEnemy D_80092738;
extern BattleEnemy D_80092744;
extern BattleEnemy D_80092750;
extern BattleEnemy D_8009275C;
extern BattleEnemy D_80092768;
extern BattleEnemy D_80092774;
extern BattleEnemy D_80092780;
extern BattleEnemy D_8009278C;
extern BattleEnemy D_80092798;
extern BattleEnemy D_800927A4;
extern BattleEnemy D_800927B0;
extern BattleEnemy D_800927BC;
extern BattleEnemy D_800927C8;
extern BattleEnemy D_800927D4;
extern BattleEnemy D_800927E0;
extern BattleEnemy D_800927EC;
extern BattleEnemy D_800927F8;
extern BattleEnemy D_80092804;
extern BattleEnemy D_80092810;
extern BattleEnemy D_8009281C;
extern BattleEnemy D_80092828;
extern BattleEnemy D_80092834;
extern BattleEnemy D_80092840;
extern BattleEnemy D_8009284C;
extern BattleEnemy D_80092858;
extern BattleEnemy D_80092864;
extern BattleEnemy D_80092870;
extern BattleEnemy D_8009287C;
extern BattleEnemy D_80092888;
extern BattleEnemy D_80092894;
extern BattleEnemy D_800928A0;
extern BattleEnemy D_800928AC;
extern BattleEnemy D_800928B8;
extern BattleEnemy D_800928C4;
extern BattleEnemy D_800928D0;
extern BattleEnemy D_800928DC;
extern BattleEnemy D_800928E8;
extern BattleEnemy D_800928F4;
extern BattleEnemy D_80092900;
extern BattleEnemy D_8009290C;
extern BattleEnemy D_80092918;
extern BattleEnemy D_80092924;
extern BattleEnemy D_80092930;
extern BattleEnemy D_8009293C;
extern BattleEnemy D_80092948;
extern BattleEnemy D_80092954;
extern BattleEnemy D_80092960;
extern BattleEnemy D_8009296C;
extern BattleEnemy D_80092978;
extern BattleEnemy D_80092984;
extern BattleEnemy D_80092990;
extern BattleEnemy D_8009299C;
extern BattleEnemy D_800929A8;
extern BattleEnemy D_800929B4;
extern BattleEnemy D_800929C0;
extern BattleEnemy D_800929CC;
extern BattleEnemy D_800929D8;
extern BattleEnemy D_800929E4;
extern BattleEnemy D_800929F0;
extern BattleEnemy D_800929FC;
extern BattleEnemy D_80092A08;
extern BattleEnemy D_80092A14;
extern BattleEnemy D_80092A20;
extern BattleEnemy D_80092A2C;
extern BattleEnemy D_80092A38;
extern BattleEnemy D_80092A44;
extern BattleEnemy D_80092A50;
extern BattleEnemy D_80092A5C;
extern BattleEnemy D_80092A68;
extern BattleEnemy D_80092A74;
extern BattleEnemy D_80092A80;
extern BattleEnemy D_80092A8C;
extern BattleEnemy D_80092A98;
extern BattleEnemy D_80092AA4;
extern BattleEnemy D_80092AB0;
extern BattleEnemy D_80092ABC;
extern BattleEnemy D_80092AC8;
extern BattleEnemy D_80092AD4;
extern BattleEnemy D_80092AE0;
extern BattleEnemy D_80092AEC;
extern BattleEnemy D_80092AF8;
extern BattleEnemy D_80092B04;
extern BattleEnemy D_80092B10;
extern BattleEnemy D_80092B1C;
extern BattleEnemy D_80092B28;
extern BattleEnemy D_80092B34;
extern BattleEnemy D_80092B40;
extern BattleEnemy D_80092B4C;
extern BattleEnemy D_80092B58;
extern BattleEnemy D_80092B64;
extern BattleEnemy D_80092B70;
extern BattleEnemy D_80092B7C;
extern BattleEnemy D_80092B88;
extern BattleEnemy D_80092B94;
extern BattleEnemy D_80092BA0;
extern BattleEnemy D_80092BAC;
extern BattleEnemy D_80092BB8;
extern BattleEnemy D_80092BC4;
extern BattleEnemy D_80092BD0;
extern BattleEnemy D_80092BDC;
extern BattleEnemy D_80092BE8;
extern BattleEnemy D_80092BF4;
extern BattleEnemy D_80092C00;
extern BattleEnemy D_80092C0C;
extern BattleEnemy D_80092C18;
extern BattleEnemy D_80092C24;
extern BattleEnemy D_80092C30;
extern BattleEnemy D_80092C3C;
extern BattleEnemy D_80092C48;
extern BattleEnemy D_80092C54;
extern BattleEnemy D_80092C60;
extern BattleEnemy D_80092C6C;
extern BattleEnemy D_80092C78;
extern BattleEnemy D_80092C84;
extern BattleEnemy D_80092C90;
extern BattleEnemy D_80092C9C;
extern BattleEnemy D_80092CA8;
extern BattleEnemy D_80092CB4;
extern BattleEnemy D_80092CC0;
extern BattleEnemy D_80092CCC;
extern BattleEnemy D_80092CD8;
extern BattleEnemy D_80092CE4;
extern BattleEnemy D_80092CF0;
extern BattleEnemy D_80092CFC;
extern BattleEnemy D_80092D08;
extern BattleEnemy D_80092D14;
extern BattleEnemy D_80092D20;
extern BattleEnemy D_80092D2C;
extern BattleEnemy D_80092D38;
extern BattleEnemy D_80092D44;
extern BattleEnemy D_80092D50;
extern BattleEnemy D_80092D5C;
extern BattleEnemy D_80092D68;
extern BattleEnemy D_80092D74;
extern BattleEnemy D_80092D80;
extern BattleEnemy D_80092D8C;
extern BattleEnemy D_80092D98;
extern BattleEnemy D_80092DA4;
extern BattleEnemy D_80092DB0;
extern BattleEnemy D_80092DBC;
extern BattleEnemy D_80092DC8;
extern BattleEnemy D_80092DD4;
extern BattleEnemy D_80092DE0;
extern BattleEnemy D_80092DEC;
extern BattleEnemy D_80092DF8;
extern BattleEnemy D_80092E04;
extern BattleEnemy D_80092E10;
extern BattleEnemy D_80092E1C;
extern BattleEnemy D_80092E28;
extern BattleEnemy D_80092E34;
extern BattleEnemy D_80092E40;
extern BattleEnemy D_80092E4C;
extern BattleEnemy D_80092E58;
extern BattleEnemy D_80092E64;
extern BattleEnemy D_80092E70;
extern BattleEnemy D_80092E7C;
extern BattleEnemy D_80092E88;
extern BattleEnemy D_80092E94;
extern BattleEnemy D_80092EA0;
extern BattleEnemy D_80092EAC;
extern BattleEnemy D_80092EB8;
extern BattleEnemy D_80092EC4;
extern BattleEnemy D_80092ED0;
extern BattleEnemy D_80092EDC;
extern BattleEnemy D_80092EE8;
extern BattleEnemy D_80092EF4;
extern BattleEnemy D_80092F00;
extern BattleEnemy D_80092F0C;
extern BattleEnemy D_80092F18;
extern BattleEnemy D_80092F24;
extern BattleEnemy D_80092F30;
extern BattleEnemy D_80092F3C;
extern BattleEnemy D_80092F48;
extern BattleEnemy D_80092F54;
extern BattleEnemy D_80092F60;
extern BattleEnemy D_80092F6C;
extern BattleEnemy D_80092F78;
extern BattleEnemy D_80092F84;
extern BattleEnemy D_80092F90;
extern BattleEnemy D_80092F9C;
extern BattleEnemy D_80092FA8;
extern BattleEnemy D_80092FB4;
extern BattleEnemy D_80092FC0;
extern BattleEnemy D_80092FCC;
extern BattleEnemy D_80092FD8;
extern BattleEnemy D_80092FE4;
extern BattleEnemy D_80092FF0;
extern BattleEnemy D_80092FFC;
extern BattleEnemy D_80093008;
extern BattleEnemy D_80093014;
extern BattleEnemy D_80093020;
extern BattleEnemy D_8009302C;
extern BattleEnemy D_80093038;
extern BattleEnemy D_80093044;
extern BattleEnemy D_80093050;
extern BattleEnemy D_8009305C;
extern BattleEnemy D_80093068;
extern BattleEnemy D_80093074;
extern BattleEnemy D_80093080;
extern BattleEnemy D_8009308C;
extern BattleEnemy D_80093098;
extern BattleEnemy D_800930A4;
extern BattleEnemy D_800930B0;
extern BattleEnemy D_800930BC;
extern BattleEnemy D_800930C8;
extern BattleEnemy D_800930D4;
extern BattleEnemy D_800930E0;
extern BattleEnemy D_800930EC;
extern BattleEnemy D_800930F8;
extern BattleEnemy D_80093104;
extern BattleEnemy D_80093110;
extern BattleEnemy D_8009311C;
extern BattleEnemy D_80093128;
extern BattleEnemy D_80093134;
extern BattleEnemy D_80093140;
extern BattleEnemy D_8009314C;
extern BattleEnemy D_80093158;
extern BattleEnemy D_80093164;
extern BattleEnemy D_80093170;
extern BattleEnemy D_8009317C;
extern BattleEnemy D_80093188;
extern BattleEnemy D_80093194;
extern BattleEnemy D_800931A0;
extern BattleEnemy D_800931AC;
extern BattleEnemy D_800931B8;
extern BattleEnemy D_800931C4;
extern BattleEnemy D_800931D0;
extern BattleEnemy D_800931DC;
extern BattleEnemy D_800931E8;
extern BattleEnemy D_800931F4;
extern BattleEnemy D_80093200;
extern BattleEnemy D_8009320C;
extern BattleEnemy D_80093218;
extern BattleEnemy D_80093224;
extern BattleEnemy D_80093230;
extern BattleEnemy D_8009323C;
extern BattleEnemy D_80093248;
extern BattleEnemy D_80093254;
extern BattleEnemy D_80093260;
extern BattleEnemy D_8009326C;
extern BattleEnemy D_80093278;
extern BattleEnemy D_80093284;
extern BattleEnemy D_80093290;
extern BattleEnemy D_8009329C;
extern BattleEnemy D_800932A8;
extern BattleEnemy D_800932B4;
extern BattleEnemy D_800932C0;
extern BattleEnemy D_800932CC;
extern BattleEnemy D_800932D8;
extern BattleEnemy D_800932E4;
extern BattleEnemy D_800932F0;
extern BattleEnemy D_800932FC;
extern BattleEnemy D_80093308;
extern BattleEnemy D_80093314;
extern BattleEnemy D_80093320;
extern BattleEnemy D_8009332C;
extern BattleEnemy D_80093338;
extern BattleEnemy D_80093344;
extern BattleEnemy D_80093350;
extern BattleEnemy D_8009335C;
extern BattleEnemy D_80093368;
extern BattleEnemy D_80093374;
extern BattleEnemy D_80093380;
extern BattleEnemy D_8009338C;
extern BattleEnemy D_80093398;
extern BattleEnemy D_800933A4;
extern BattleEnemy D_800933B0;
extern BattleEnemy D_800933BC;
extern BattleEnemy D_800933C8;
extern BattleEnemy D_800933D4;
extern BattleEnemy D_800933E0;
extern BattleEnemy D_800933EC;
extern BattleEnemy D_800933F8;
extern BattleEnemy D_80093404;
extern BattleEnemy D_80093410;
extern BattleEnemy D_8009341C;
extern BattleEnemy D_80093428;
extern BattleEnemy D_80093434;
extern BattleEnemy D_80093440;
extern BattleEnemy D_8009344C;
extern BattleEnemy D_80093458;
extern BattleEnemy D_80093464;
extern BattleEnemy D_80093470;
extern BattleEnemy D_8009347C;
extern BattleEnemy D_80093488;
extern BattleEnemy D_80093494;
extern BattleEnemy D_800934A0;
extern BattleEnemy D_800934AC;
extern BattleEnemy D_800934B8;
extern BattleEnemy D_800934C4;
extern BattleEnemy D_800934D0;
extern BattleEnemy D_800934DC;
extern BattleEnemy D_800934E8;
extern BattleEnemy D_800934F4;
extern BattleEnemy D_80093500;
extern BattleEnemy D_8009350C;
extern BattleEnemy D_80093518;
extern BattleEnemy D_80093524;
extern BattleEnemy D_80093530;
extern BattleEnemy D_8009353C;
extern BattleEnemy D_80093548;
extern BattleEnemy D_80093554;
extern BattleEnemy D_80093560;
extern BattleEnemy D_8009356C;
extern BattleEnemy D_80093578;
extern BattleEnemy D_80093584;
extern BattleEnemy D_80093590;
extern BattleEnemy D_8009359C;
extern BattleEnemy D_800935A8;
extern BattleEnemy D_800935B4;
extern BattleEnemy D_800935C0;
extern BattleEnemy D_800935CC;
extern BattleEnemy D_800935D8;
extern BattleEnemy D_800935E4;
extern BattleEnemy D_800935F0;
extern BattleEnemy D_800935FC;
extern BattleEnemy D_80093608;
extern BattleEnemy D_80093614;
extern BattleEnemy D_80093620;
extern BattleEnemy D_8009362C;
extern BattleEnemy D_80093638;
extern BattleEnemy D_80093644;
extern BattleEnemy D_80093650;
extern BattleEnemy D_8009365C;
extern BattleEnemy D_80093668;
extern BattleEnemy D_80093674;
extern BattleEnemy D_80093680;
extern BattleEnemy D_8009368C;
extern BattleEnemy D_80093698;
extern BattleEnemy D_800936A4;
extern BattleEnemy D_800936B0;
extern BattleEnemy D_800936BC;
extern BattleEnemy D_800936C8;
extern BattleEnemy D_800936D4;
extern BattleEnemy D_800936E0;
extern BattleEnemy D_800936EC;
extern BattleEnemy D_800936F8;
extern BattleEnemy D_80093704;
extern BattleEnemy D_80093710;
extern BattleEnemy D_8009371C;
extern BattleEnemy D_80093728;
extern BattleEnemy D_80093734;
extern BattleEnemy D_80093740;
extern BattleEnemy D_8009374C;
extern BattleEnemy D_80093758;
extern BattleEnemy D_80093764;
extern BattleEnemy D_80093770;
extern BattleEnemy D_8009377C;
extern BattleEnemy D_80093788;
extern BattleEnemy D_80093794;
extern BattleEnemy D_800937A0;
extern BattleEnemy D_800937AC;
extern BattleEnemy D_800937B8;
extern BattleEnemy D_800937C4;
extern BattleEnemy D_800937D0;
extern BattleEnemy D_800937DC;
extern BattleEnemy D_800937E8;
extern BattleEnemy D_800937F4;
extern BattleEnemy D_80093800;
extern BattleEnemy D_8009380C;
extern BattleEnemy D_80093818;
extern BattleEnemy D_80093824;
extern BattleEnemy D_80093830;
extern BattleEnemy D_8009383C;
extern BattleEnemy D_80093848;
extern BattleEnemy D_80093854;
extern BattleEnemy D_80093860;
extern BattleEnemy D_8009386C;
extern BattleEnemy D_80093878;
extern BattleEnemy D_80093884;
extern BattleEnemy D_80093890;
extern BattleEnemy D_8009389C;
extern BattleEnemy D_800938A8;
extern BattleEnemy D_800938B4;
extern BattleEnemy D_800938C0;
extern BattleEnemy D_800938CC;
extern BattleEnemy D_800938D8;
extern BattleEnemy D_800938E4;
extern BattleEnemy D_800938F0;
extern BattleEnemy D_800938FC;
extern BattleEnemy D_80093908;
extern BattleEnemy D_80093914;
extern BattleEnemy D_80093920;
extern BattleEnemy D_8009392C;
extern BattleEnemy D_80093938;
extern BattleEnemy D_80093944;
extern BattleEnemy D_80093950;
extern BattleEnemy D_8009395C;
extern BattleEnemy D_80093968;
extern BattleEnemy D_80093974;
extern BattleEnemy D_80093980;
extern BattleEnemy D_8009398C;
extern BattleEnemy D_80093998;
extern BattleEnemy D_800939A4;
extern BattleEnemy D_800939B0;
extern BattleEnemy D_800939BC;
extern BattleEnemy D_800939C8;
extern BattleEnemy D_800939D4;
extern AnimFrame D_800960C8[];
extern AnimFrame D_8009614C[];
extern AnimFrame D_80096174[];
extern AnimFrame D_800961B4[];
extern AnimFrame D_80096160[];
extern AnimFrame D_80096194[];
extern u8 D_80096D2C[];
extern u8 D_80096D3C[];
extern u8 D_80096D4C[];
extern u8 D_80096D5C[];
extern u8 D_80096D6C[];
extern u8 D_80096D7C[];
extern u8 D_80096D8C[];
extern u8 D_80096D9C[];
extern s32 D_80096DEC[];
extern s32 D_80096DF8[];
extern s32 D_80096E04[];
extern s32 D_80096E10[];
extern s32 D_80096E1C[];
extern s32 D_80096E28[];
extern s32 D_80096E34[];
extern s32 D_80096E40[];
extern s32 D_800971A0[];
extern s32 D_800971A8[];
extern s32 D_800971B4[];
extern s32 D_800971BC[];
extern s32 D_800971C8[];
extern s32 D_800971D0[];
extern s32 D_800971DC[];
extern s32 D_800971E4[];
extern s32 D_80097B50[];
extern s32 D_80097B58[];
extern s32 D_80097B60[];
extern s32 D_80097B68[];
extern s32 D_80097B70[];
extern s32 D_80097B78[];
extern s32 D_80097B80[];
extern s32 D_80097B88[];
extern s32 D_80097B90[];
extern s32 D_80097B98[];
extern s32 D_80097BA0[];
extern s32 D_80097BA8[];
extern s32 D_80097BB0[];
extern s32 D_80097BB8[];
extern s32 D_80097BC0[];
extern s32 D_80097BC8[];
extern s32 D_800971F0[];
extern s32 D_80097BD0[];
extern s32 D_80097208[];
extern s32 D_80097BD8[];
extern s32 D_80097220[];
extern s32 D_80097BE0[];
extern s32 D_80097238[];
extern s32 D_80097BE8[];
extern s32 D_80097250[];
extern s32 D_80097BF0[];
extern s32 D_80097268[];
extern s32 D_80097BF8[];
extern s32 D_80097280[];
extern s32 D_80097C00[];
extern s32 D_80097298[];
extern s32 D_80097C08[];
extern s32 D_800972B0[];
extern s32 D_80097C10[];
extern s32 D_800972C8[];
extern s32 D_80097C18[];
extern s32 D_800972E0[];
extern s32 D_80097C20[];
extern s32 D_800972F8[];
extern s32 D_80097C28[];
extern s32 D_80097310[];
extern s32 D_80097C30[];
extern s32 D_80097328[];
extern s32 D_80097C38[];
extern s32 D_80097340[];
extern s32 D_80097C40[];
extern s32 D_80097358[];
extern s32 D_80097C48[];
extern s32 D_80097370[];
extern s32 D_80097C50[];
extern s32 D_80097388[];
extern s32 D_80097C58[];
extern s32 D_800973A0[];
extern s32 D_80097C60[];
extern s32 D_800973B8[];
extern s32 D_80097C68[];
extern s32 D_800973D0[];
extern s32 D_80097C70[];
extern s32 D_800973E8[];
extern s32 D_80097C78[];
extern s32 D_80097400[];
extern s32 D_80097C80[];
extern s32 D_80097418[];
extern s32 D_80097C88[];
extern s32 D_80097430[];
extern s32 D_80097C90[];
extern s32 D_80097448[];
extern s32 D_80097C98[];
extern s32 D_80097460[];
extern s32 D_80097CA0[];
extern s32 D_80097478[];
extern s32 D_80097CA8[];
extern s32 D_80097490[];
extern s32 D_80097CB0[];
extern s32 D_800974A8[];
extern s32 D_80097CB8[];
extern s32 D_800974C0[];
extern s32 D_80097CC0[];
extern s32 D_800974D8[];
extern s32 D_80097CC8[];
extern s32 D_800974F0[];
extern s32 D_80097CD0[];
extern s32 D_80097508[];
extern s32 D_80097CD8[];
extern s32 D_80097520[];
extern s32 D_80097CE0[];
extern s32 D_80097538[];
extern s32 D_80097CE8[];
extern s32 D_80097550[];
extern s32 D_80097CF0[];
extern s32 D_80097568[];
extern s32 D_80097CF8[];
extern s32 D_80097580[];
extern s32 D_80097D00[];
extern s32 D_80097598[];
extern s32 D_80097D08[];
extern s32 D_800975B0[];
extern s32 D_80097D10[];
extern s32 D_800975C8[];
extern s32 D_80097D18[];
extern s32 D_800975E0[];
extern s32 D_80097D20[];
extern s32 D_800975F8[];
extern s32 D_80097D28[];
extern s32 D_80097610[];
extern s32 D_80097D30[];
extern s32 D_80097628[];
extern s32 D_80097D38[];
extern s32 D_80097640[];
extern s32 D_80097D40[];
extern s32 D_80097658[];
extern s32 D_80097D48[];
extern s32 D_80097670[];
extern s32 D_80097D50[];
extern s32 D_80097688[];
extern s32 D_80097D58[];
extern s32 D_800976A0[];
extern s32 D_80097D60[];
extern s32 D_800976B8[];
extern s32 D_80097D68[];
extern s32 D_800976D0[];
extern s32 D_80097D70[];
extern s32 D_800976E8[];
extern s32 D_80097D78[];
extern s32 D_80097700[];
extern s32 D_80097D80[];
extern s32 D_80097718[];
extern s32 D_80097D88[];
extern s32 D_80097730[];
extern s32 D_80097D90[];
extern s32 D_80097748[];
extern s32 D_80097D98[];
extern s32 D_80097760[];
extern s32 D_80097DA0[];
extern s32 D_80097778[];
extern s32 D_80097DA8[];
extern s32 D_80097790[];
extern s32 D_80097DB0[];
extern s32 D_800977A8[];
extern s32 D_80097DB8[];
extern s32 D_800977C0[];
extern s32 D_80097DC0[];
extern s32 D_800977D8[];
extern s32 D_80097DC8[];
extern s32 D_800977F0[];
extern s32 D_80097DD0[];
extern s32 D_80097808[];
extern s32 D_80097DD8[];
extern s32 D_80097820[];
extern s32 D_80097DE0[];
extern s32 D_80097838[];
extern s32 D_80097DE8[];
extern s32 D_80097850[];
extern s32 D_80097DF0[];
extern s32 D_80097868[];
extern s32 D_80097DF8[];
extern s32 D_80097880[];
extern s32 D_80097E00[];
extern s32 D_80097898[];
extern s32 D_80097E08[];
extern s32 D_800978B0[];
extern s32 D_80097E10[];
extern s32 D_800978C8[];
extern s32 D_80097E18[];
extern s32 D_800978E0[];
extern s32 D_80097E20[];
extern s32 D_800978F8[];
extern s32 D_80097E28[];
extern s32 D_80097910[];
extern s32 D_80097E30[];
extern s32 D_80097928[];
extern s32 D_80097E38[];
extern s32 D_80097940[];
extern s32 D_80097E40[];
extern s32 D_80097958[];
extern s32 D_80097E48[];
extern s32 D_80097970[];
extern s32 D_80097E50[];
extern s32 D_80097988[];
extern s32 D_80097E58[];
extern s32 D_800979A0[];
extern s32 D_80097E60[];
extern s32 D_800979B8[];
extern s32 D_80097E68[];
extern s32 D_800979D0[];
extern s32 D_80097E70[];
extern s32 D_800979E8[];
extern s32 D_80097E78[];
extern s32 D_80097A00[];
extern s32 D_80097E80[];
extern s32 D_80097A18[];
extern s32 D_80097E88[];
extern s32 D_80097A30[];
extern s32 D_80097E90[];
extern s32 D_80097A48[];
extern s32 D_80097E98[];
extern s32 D_80097A60[];
extern s32 D_80097EA0[];
extern s32 D_80097A78[];
extern s32 D_80097EEC[];
extern s32 D_80097A9C[];
extern s32 D_80097EF4[];
extern s32 D_80097AC0[];
extern s32 D_80097EFC[];
extern s32 D_80097F04[];
extern s32 D_80097AD8[];
extern s32 D_80097F0C[];
extern s32 D_80097AF0[];
extern s32 D_80097F14[];
extern s32 D_80097B08[];
extern s32 D_80097F1C[];
extern s32 D_80097B20[];
extern s32 D_80097F24[];
extern s32 D_80097B38[];
extern s32 D_80097F2C[];
extern s32 D_80097F40[];
extern s32 D_80097F54[];
extern s32 D_80097F68[];
extern s32 D_80097F7C[];
extern s32 D_80097F90[];
extern s32 D_80097FA4[];
extern s32 D_80097FB8[];
extern s32 D_80097FCC[];
extern s32 D_80097FE0[];
extern s32 D_80097FF4[];
extern s32 D_80098008[];
extern s32 D_8009801C[];
extern s32 D_80098030[];
extern s32 D_80098044[];
extern s32 D_80098058[];
extern s32 D_8009806C[];
extern s32 D_80098080[];
extern s32 D_80098094[];
extern s32 D_800980A8[];
extern s32 D_800980BC[];
extern s32 D_800980D0[];
extern s32 D_800980E4[];
extern s32 D_800980F8[];
extern s32 D_8009810C[];
extern s32 D_80098120[];
extern s32 D_80098134[];
extern s32 D_80098148[];
extern s32 D_8009815C[];
extern s32 D_80098170[];
extern s32 D_80098184[];
extern s32 D_80098198[];
extern s32 D_800981AC[];
extern s32 D_800981C0[];
extern s32 D_800981D4[];
extern s32 D_800981E8[];
extern s32 D_800981FC[];
extern s32 D_80098210[];
extern s32 D_80098224[];
extern s32 D_80098238[];
extern s32 D_8009824C[];
extern s32 D_80098260[];
extern s32 D_80098274[];
extern s32 D_80098288[];
extern s32 D_8009829C[];
extern s32 D_800982B0[];
extern s32 D_800982C4[];
extern s32 D_800982D8[];
extern s32 D_800982EC[];
extern s32 D_80098300[];
extern s32 D_80098314[];
extern s32 D_80098328[];
extern s32 D_8009833C[];
extern s32 D_80098350[];
extern s32 D_80098364[];
extern s32 D_80098378[];
extern s32 D_8009838C[];
extern s32 D_800983A0[];
extern s32 D_800983B4[];
extern s32 D_800983C8[];
extern s32 D_800983DC[];
extern s32 D_800983F0[];
extern s32 D_80098404[];
extern s32 D_80098418[];
extern s32 D_8009842C[];
extern s32 D_80098440[];
extern s32 D_80098454[];
extern s32 D_80098468[];
extern s32 D_8009847C[];
extern s32 D_80098490[];
extern s32 D_800984A4[];
extern s32 D_800984B8[];
extern s32 D_800984CC[];
extern s32 D_800984E0[];
extern s32 D_800984F4[];
extern s32 D_80098508[];
extern s32 D_8009851C[];
extern s32 D_80098530[];
extern s32 D_80098544[];
extern s32 D_80098558[];
extern s32 D_8009856C[];
extern s32 D_80098580[];
extern s32 D_80098594[];
extern s32 D_800985A8[];
extern s32 D_800985BC[];
extern s32 D_800985D0[];
extern s32 D_800985E4[];
extern s32 D_800985F8[];
extern s32 D_8009860C[];
extern s32 D_80098620[];
extern s32 D_80098634[];
extern s32 D_80098648[];
extern s32 D_8009865C[];
extern s32 D_80098670[];
extern s32 D_80098684[];
extern s32 D_80098698[];
extern s32 D_800986AC[];
extern s32 D_800986C0[];
extern s32 D_800986D4[];
extern s32 D_800986E8[];
extern s32 D_800986FC[];
extern s32 D_80098710[];
extern s32 D_80098724[];
extern s32 D_80098738[];
extern s32 D_8009874C[];
extern s32 D_80098760[];
extern s32 D_80098774[];
extern s32 D_80098788[];
extern s32 D_8009879C[];
extern s32 D_800987B0[];
extern s32 D_800987C4[];
extern s32 D_800987D8[];
extern s32 D_800987EC[];
extern s32 D_80098800[];
extern s32 D_80098814[];
void func_80091124();
void func_80082F84();
void func_80091910();
s32 func_80091BC0(s32, Point *);
s32 func_80091D3C(Point *pos);
void func_80083F8C(void), func_80083FBC(void), func_80083FF0(void), func_80084024(void);
void func_80084058(void), func_8008408C(void), func_800840C0(void), func_800840F4(void);
void func_80084128(void), func_8008415C(void), func_80084190(void), func_800841C4(void);
void func_800841F8(void), func_8008422C(void), func_80084260(void), func_80084294(void);
void func_80090864(void), func_800908C4(void), func_800908F0(void), func_80090950(void);
void func_8009097C(void), func_800909DC(void), func_80090A08(void), func_80090A68(void);
void func_80090A94(void), func_80090AF4(void), func_80090B20(void), func_80090B80(void);
void func_80090BAC(void), func_80090C0C(void), func_80090C38(void), func_80090C98(void);
void func_80090CC4(void), func_80090D24(void), func_80090D50(void), func_80090DB0(void);
void func_80090DDC(void), func_80090E3C(void), func_80090E68(void), func_80090EC8(void);
void func_80090EF4(void), func_80090F54(void), func_80090F80(void), func_80090FE0(void);
void func_8009100C(void), func_8009106C(void), func_80091098(void), func_800910F8(void);
void func_800913CC(void), func_800914C0(void), func_800916B4(void), func_800917D8(void);
void func_80091854(void);
void func_800838BC(Unk800834A0 *task, s32 arg1);
Unk800834A0 *func_80083930(s32 id);
Unk800842C8 *func_800844B8(s32 arg0);
void func_800878F0(s32 arg0);
void func_80087918(Unk800876E4 *task, s32 command, s32 id);
void func_80091298(Tween *tween, s32 in);
s32 func_8009132C(Tween *tween);
s32 func_80091398(s32 index);
s32 func_800913B4(s32 index);
void *func_80091490(u8 *list, s32 id);
void func_80091520(s32 time, s32 *pc);
void func_800915B0(s32 id, s32 *pc);
void func_800915FC(s32 id, s32 *pc);
void func_80091648(Point *pos);
void func_80091A4C(s32 index);
void func_80091B78(s32 index, s32 value);
void func_80091B90(s32 arg0);
void func_80091BB4(s32 arg0);
void func_80091F4C(Point *pos, s32 scale, s32 index, Point *out);
void func_8009204C(Point *pos, s32 scale, s32 index, Point *out);
#if VERSION_EU
extern BattleEnemy D_800940A4;
extern BattleEnemy D_800940B0;
#endif

BattleEnemy D_800920A8 = {0, 0, 0, 0, 0};
BattleEnemy D_800920B4 = {358, 12, 816, 9999, 16};
BattleEnemy D_800920C0 = {124, 14, 912, 9999, 16};
BattleEnemy D_800920CC = {172, 9, 504, 9999, 22};
BattleEnemy D_800920D8 = {8, 11, 576, 9999, 23};
BattleEnemy D_800920E4 = {207, 14, 684, 9999, 20};
BattleEnemy D_800920F0 = {222, 12, 612, 9999, 27};
BattleEnemy D_800920FC = {77, 14, 684, 9999, 22};
BattleEnemy D_80092108 = {119, 17, 792, 200, 14};
BattleEnemy D_80092114 = {11, 27, 768, 9999, 17};
BattleEnemy D_80092120 = {11, 27, 768, 9999, 17};
BattleEnemy D_8009212C = {400, 29, 1224, 9999, 14};
BattleEnemy D_80092138 = {208, 29, 1224, 9999, 16};
BattleEnemy D_80092144 = {13, 29, 1088, 9999, 18};
BattleEnemy D_80092150 = {356, 32, 1776, 280, 16};
BattleEnemy D_8009215C = {70, 32, 1776, 9999, 16};
BattleEnemy D_80092168 = {141, 34, 1872, 9999, 16};
BattleEnemy D_80092174 = {399, 33, 912, 9999, 16};
BattleEnemy D_80092180 = {302, 34, 1404, 9999, 16};
BattleEnemy D_8009218C = {437, 38, 3096, 40, 16};
BattleEnemy D_80092198 = {337, 40, 2160, 9999, 16};
BattleEnemy D_800921A4 = {436, 43, 2304, 960, 16};
BattleEnemy D_800921B0 = {443, 45, 2400, 9999, 16};
BattleEnemy D_800921BC = {138, 40, 1620, 9999, 18};
BattleEnemy D_800921C8 = {402, 41, 2484, 9999, 16};
BattleEnemy D_800921D4 = {237, 44, 1764, 9999, 16};
BattleEnemy D_800921E0 = {444, 46, 2448, 9999, 16};
BattleEnemy D_800921EC = {425, 41, 1656, 9999, 16};
BattleEnemy D_800921F8 = {202, 43, 1728, 9999, 16};
BattleEnemy D_80092204 = {238, 46, 1836, 9999, 17};
BattleEnemy D_80092210 = {447, 47, 2496, 9999, 16};
BattleEnemy D_8009221C = {270, 45, 1800, 9999, 17};
BattleEnemy D_80092228 = {65, 46, 1836, 296, 17};
BattleEnemy D_80092234 = {360, 49, 1944, 9999, 18};
BattleEnemy D_80092240 = {23, 45, 1200, 9999, 17};
BattleEnemy D_8009224C = {427, 46, 1224, 9999, 17};
BattleEnemy D_80092258 = {409, 49, 1296, 9999, 17};
BattleEnemy D_80092264 = {9, 45, 1200, 9999, 17};
BattleEnemy D_80092270 = {189, 47, 1248, 9999, 17};
BattleEnemy D_8009227C = {104, 50, 1320, 1800, 17};
BattleEnemy D_80092288 = {244, 46, 1224, 9999, 19};
BattleEnemy D_80092294 = {135, 48, 1272, 9999, 18};
BattleEnemy D_800922A0 = {429, 50, 1320, 9999, 17};
BattleEnemy D_800922AC = {24, 47, 1872, 9999, 17};
BattleEnemy D_800922B8 = {410, 49, 1296, 4, 17};
BattleEnemy D_800922C4 = {115, 51, 1344, 9999, 17};
BattleEnemy D_800922D0 = {445, 55, 2880, 9999, 16};
BattleEnemy D_800922DC = {446, 57, 2976, 8, 16};
BattleEnemy D_800922E8 = {108, 49, 1944, 9999, 18};
BattleEnemy D_800922F4 = {193, 50, 1980, 9999, 18};
BattleEnemy D_80092300 = {428, 52, 2052, 9999, 17};
BattleEnemy D_8009230C = {190, 50, 1980, 9999, 17};
BattleEnemy D_80092318 = {215, 52, 2052, 9999, 17};
BattleEnemy D_80092324 = {231, 54, 2124, 9999, 16};
BattleEnemy D_80092330 = {431, 50, 1980, 9999, 17};
BattleEnemy D_8009233C = {434, 52, 1368, 9999, 17};
BattleEnemy D_80092348 = {433, 54, 1416, 9999, 16};
BattleEnemy D_80092354 = {327, 52, 1368, 9999, 17};
BattleEnemy D_80092360 = {327, 52, 1368, 9999, 17};
BattleEnemy D_8009236C = {247, 55, 1440, 9999, 16};
BattleEnemy D_80092378 = {312, 54, 1133, 9999, 17};
BattleEnemy D_80092384 = {228, 56, 1464, 9999, 16};
BattleEnemy D_80092390 = {245, 58, 1512, 9999, 17};
BattleEnemy D_8009239C = {178, 99, 9999, 9999, 29};
BattleEnemy D_800923A8 = {448, 53, 2784, 9999, 16};
BattleEnemy D_800923B4 = {432, 54, 1416, 9999, 16};
BattleEnemy D_800923C0 = {236, 57, 1488, 9999, 17};
BattleEnemy D_800923CC = {438, 60, 3120, 9999, 16};
BattleEnemy D_800923D8 = {439, 57, 4464, 9999, 16};
BattleEnemy D_800923E4 = {440, 57, 2976, 9999, 16};
BattleEnemy D_800923F0 = {441, 57, 2976, 9999, 16};
BattleEnemy D_800923FC = {32, 1, 120, 9999, 16};
BattleEnemy D_80092408 = {206, 1, 120, 9999, 16};
BattleEnemy D_80092414 = {197, 3, 168, 9999, 16};
BattleEnemy D_80092420 = {132, 4, 192, 9999, 16};
BattleEnemy D_8009242C = {217, 8, 312, 9999, 16};
BattleEnemy D_80092438 = {4, 2, 144, 9999, 16};
BattleEnemy D_80092444 = {25, 4, 192, 9999, 16};
BattleEnemy D_80092450 = {51, 2, 144, 9999, 16};
BattleEnemy D_8009245C = {67, 3, 168, 9999, 16};
BattleEnemy D_80092468 = {198, 3, 168, 9999, 16};
BattleEnemy D_80092474 = {166, 4, 192, 9999, 16};
BattleEnemy D_80092480 = {80, 4, 192, 9999, 16};
BattleEnemy D_8009248C = {277, 16, 504, 9999, 16};
BattleEnemy D_80092498 = {172, 5, 240, 9999, 16};
BattleEnemy D_800924A4 = {137, 13, 432, 9999, 16};
BattleEnemy D_800924B0 = {222, 5, 240, 9999, 16};
BattleEnemy D_800924BC = {8, 6, 264, 9999, 16};
BattleEnemy D_800924C8 = {203, 6, 396, 9999, 16};
BattleEnemy D_800924D4 = {7, 6, 264, 9999, 16};
BattleEnemy D_800924E0 = {110, 8, 312, 9999, 16};
BattleEnemy D_800924EC = {49, 8, 312, 9999, 16};
BattleEnemy D_800924F8 = {37, 9, 336, 9999, 16};
BattleEnemy D_80092504 = {223, 31, 864, 9999, 16};
BattleEnemy D_80092510 = {50, 13, 432, 9999, 16};
BattleEnemy D_8009251C = {207, 10, 360, 9999, 16};
BattleEnemy D_80092528 = {35, 18, 552, 9999, 16};
BattleEnemy D_80092534 = {208, 29, 816, 9999, 16};
BattleEnemy D_80092540 = {210, 20, 600, 120, 16};
BattleEnemy D_8009254C = {220, 27, 768, 9999, 16};
BattleEnemy D_80092558 = {221, 40, 1080, 9999, 16};
BattleEnemy D_80092564 = {241, 24, 696, 9999, 16};
BattleEnemy D_80092570 = {119, 20, 600, 200, 16};
BattleEnemy D_8009257C = {10, 12, 408, 9999, 16};
BattleEnemy D_80092588 = {212, 23, 672, 9999, 16};
BattleEnemy D_80092594 = {42, 20, 600, 64, 16};
BattleEnemy D_800925A0 = {34, 20, 600, 9999, 16};
BattleEnemy D_800925AC = {136, 22, 972, 9999, 16};
BattleEnemy D_800925B8 = {108, 44, 1176, 9999, 16};
BattleEnemy D_800925C4 = {273, 45, 1200, 9999, 16};
BattleEnemy D_800925D0 = {28, 22, 648, 9999, 16};
BattleEnemy D_800925DC = {334, 22, 648, 9999, 16};
BattleEnemy D_800925E8 = {13, 25, 480, 9999, 16};
BattleEnemy D_800925F4 = {435, 29, 816, 9999, 16};
BattleEnemy D_80092600 = {176, 23, 672, 150, 16};
BattleEnemy D_8009260C = {122, 23, 672, 336, 16};
BattleEnemy D_80092618 = {143, 24, 696, 9999, 16};
BattleEnemy D_80092624 = {40, 24, 696, 9999, 16};
BattleEnemy D_80092630 = {11, 25, 720, 9999, 16};
BattleEnemy D_8009263C = {39, 26, 744, 9999, 16};
BattleEnemy D_80092648 = {227, 47, 1248, 9999, 16};
BattleEnemy D_80092654 = {171, 47, 1248, 9999, 16};
BattleEnemy D_80092660 = {139, 27, 768, 270, 16};
BattleEnemy D_8009266C = {134, 27, 768, 9999, 16};
BattleEnemy D_80092678 = {54, 46, 1224, 9999, 16};
BattleEnemy D_80092684 = {14, 29, 816, 9999, 16};
BattleEnemy D_80092690 = {76, 30, 840, 9999, 16};
BattleEnemy D_8009269C = {53, 29, 816, 9999, 16};
BattleEnemy D_800926A8 = {173, 31, 864, 9999, 16};
BattleEnemy D_800926B4 = {175, 36, 984, 9999, 16};
BattleEnemy D_800926C0 = {238, 43, 1152, 9999, 16};
BattleEnemy D_800926CC = {200, 34, 936, 9999, 16};
BattleEnemy D_800926D8 = {121, 38, 1032, 9999, 16};
BattleEnemy D_800926E4 = {302, 35, 960, 9999, 16};
BattleEnemy D_800926F0 = {364, 35, 960, 9999, 16};
BattleEnemy D_800926FC = {365, 45, 1200, 9999, 16};
BattleEnemy D_80092708 = {226, 34, 936, 9999, 16};
BattleEnemy D_80092714 = {140, 36, 984, 9999, 16};
BattleEnemy D_80092720 = {138, 36, 984, 9999, 16};
BattleEnemy D_8009272C = {24, 45, 1800, 9999, 16};
BattleEnemy D_80092738 = {224, 37, 1008, 9999, 16};
BattleEnemy D_80092744 = {225, 44, 1176, 9999, 16};
BattleEnemy D_80092750 = {61, 35, 960, 9999, 16};
BattleEnemy D_8009275C = {165, 34, 936, 9999, 16};
BattleEnemy D_80092768 = {170, 36, 984, 96, 16};
BattleEnemy D_80092774 = {244, 39, 1056, 9999, 16};
BattleEnemy D_80092780 = {126, 36, 984, 9999, 16};
BattleEnemy D_8009278C = {38, 41, 1104, 9999, 16};
BattleEnemy D_80092798 = {69, 41, 1104, 9999, 16};
BattleEnemy D_800927A4 = {9, 41, 1104, 9999, 16};
BattleEnemy D_800927B0 = {52, 41, 1104, 9999, 16};
BattleEnemy D_800927BC = {23, 41, 1104, 9999, 16};
BattleEnemy D_800927C8 = {94, 43, 1152, 9999, 16};
BattleEnemy D_800927D4 = {41, 46, 1224, 9999, 16};
BattleEnemy D_800927E0 = {270, 43, 1152, 9999, 16};
BattleEnemy D_800927EC = {327, 49, 1296, 9999, 16};
BattleEnemy D_800927F8 = {189, 43, 1152, 9999, 16};
BattleEnemy D_80092804 = {135, 43, 1152, 9999, 16};
BattleEnemy D_80092810 = {237, 44, 1176, 9999, 16};
BattleEnemy D_8009281C = {229, 44, 1176, 9999, 16};
BattleEnemy D_80092828 = {204, 44, 1176, 9999, 16};
BattleEnemy D_80092834 = {281, 43, 1152, 9999, 16};
BattleEnemy D_80092840 = {202, 43, 1152, 9999, 16};
BattleEnemy D_8009284C = {360, 44, 1176, 9999, 16};
BattleEnemy D_80092858 = {60, 44, 1176, 9999, 16};
BattleEnemy D_80092864 = {231, 54, 1416, 9999, 16};
BattleEnemy D_80092870 = {215, 49, 1296, 9999, 16};
BattleEnemy D_8009287C = {269, 45, 1200, 9999, 16};
BattleEnemy D_80092888 = {177, 45, 1200, 9999, 16};
BattleEnemy D_80092894 = {65, 44, 1176, 296, 16};
BattleEnemy D_800928A0 = {250, 45, 1200, 9999, 16};
BattleEnemy D_800928AC = {193, 45, 1200, 9999, 16};
BattleEnemy D_800928B8 = {245, 55, 1440, 9999, 16};
BattleEnemy D_800928C4 = {272, 47, 1248, 9999, 16};
BattleEnemy D_800928D0 = {190, 48, 1272, 9999, 16};
BattleEnemy D_800928DC = {228, 56, 1464, 9999, 16};
BattleEnemy D_800928E8 = {115, 47, 1248, 9999, 16};
BattleEnemy D_800928F4 = {236, 55, 1440, 9999, 16};
BattleEnemy D_80092900 = {251, 56, 1464, 9999, 16};
BattleEnemy D_8009290C = {312, 49, 1037, 9999, 16};
BattleEnemy D_80092918 = {247, 55, 1440, 9999, 16};
BattleEnemy D_80092924 = {382, 56, 2196, 9999, 16};
BattleEnemy D_80092930 = {77, 9, 336, 9999, 16};
BattleEnemy D_8009293C = {395, 30, 840, 9999, 16};
BattleEnemy D_80092948 = {396, 8, 312, 9999, 16};
BattleEnemy D_80092954 = {397, 21, 624, 9999, 16};
BattleEnemy D_80092960 = {398, 22, 648, 9999, 16};
BattleEnemy D_8009296C = {399, 33, 608, 9999, 16};
BattleEnemy D_80092978 = {400, 33, 912, 9999, 16};
BattleEnemy D_80092984 = {401, 19, 576, 9999, 16};
BattleEnemy D_80092990 = {402, 41, 1656, 9999, 16};
BattleEnemy D_8009299C = {403, 21, 624, 9999, 16};
BattleEnemy D_800929A8 = {404, 37, 1008, 9999, 16};
BattleEnemy D_800929B4 = {405, 22, 648, 9999, 16};
BattleEnemy D_800929C0 = {406, 36, 984, 9999, 16};
BattleEnemy D_800929CC = {407, 37, 1008, 360, 16};
BattleEnemy D_800929D8 = {408, 35, 960, 9999, 16};
BattleEnemy D_800929E4 = {409, 47, 1248, 9999, 16};
BattleEnemy D_800929F0 = {89, 42, 1128, 9999, 16};
BattleEnemy D_800929FC = {410, 46, 1224, 4, 16};
BattleEnemy D_80092A08 = {411, 48, 1272, 9999, 16};
BattleEnemy D_80092A14 = {412, 46, 1224, 9999, 16};
BattleEnemy D_80092A20 = {413, 31, 864, 9999, 16};
BattleEnemy D_80092A2C = {414, 39, 1056, 9999, 16};
BattleEnemy D_80092A38 = {415, 43, 1152, 9999, 16};
BattleEnemy D_80092A44 = {416, 43, 1152, 9999, 16};
BattleEnemy D_80092A50 = {417, 44, 1176, 9999, 16};
BattleEnemy D_80092A5C = {418, 40, 1080, 9999, 16};
BattleEnemy D_80092A68 = {419, 43, 1152, 9999, 16};
BattleEnemy D_80092A74 = {420, 45, 1200, 9999, 16};
BattleEnemy D_80092A80 = {421, 32, 888, 9999, 16};
BattleEnemy D_80092A8C = {422, 40, 1080, 9999, 16};
BattleEnemy D_80092A98 = {423, 48, 1272, 9999, 16};
BattleEnemy D_80092AA4 = {424, 36, 984, 9999, 16};
BattleEnemy D_80092AB0 = {425, 41, 1104, 9999, 16};
BattleEnemy D_80092ABC = {426, 47, 1872, 9999, 16};
BattleEnemy D_80092AC8 = {427, 44, 1176, 9999, 16};
BattleEnemy D_80092AD4 = {428, 48, 1272, 9999, 16};
BattleEnemy D_80092AE0 = {429, 48, 1272, 9999, 16};
BattleEnemy D_80092AEC = {430, 44, 1176, 9999, 16};
BattleEnemy D_80092AF8 = {104, 48, 1272, 1800, 16};
BattleEnemy D_80092B04 = {431, 47, 1872, 9999, 16};
BattleEnemy D_80092B10 = {432, 54, 1416, 9999, 16};
BattleEnemy D_80092B1C = {433, 54, 1416, 9999, 16};
BattleEnemy D_80092B28 = {434, 49, 1296, 9999, 16};
BattleEnemy D_80092B34 = {14, 29, 816, 9999, 16};
BattleEnemy D_80092B40 = {53, 29, 816, 9999, 16};
BattleEnemy D_80092B4C = {435, 29, 816, 9999, 16};
BattleEnemy D_80092B58 = {76, 30, 840, 9999, 16};
BattleEnemy D_80092B64 = {435, 29, 816, 9999, 16};
BattleEnemy D_80092B70 = {76, 30, 840, 9999, 16};
BattleEnemy D_80092B7C = {76, 30, 840, 9999, 16};
BattleEnemy D_80092B88 = {334, 32, 888, 9999, 22};
BattleEnemy D_80092B94 = {139, 29, 816, 270, 17};
BattleEnemy D_80092BA0 = {134, 29, 816, 9999, 17};
BattleEnemy D_80092BAC = {225, 44, 1176, 9999, 16};
BattleEnemy D_80092BB8 = {229, 44, 1176, 9999, 16};
BattleEnemy D_80092BC4 = {41, 46, 1224, 9999, 16};
BattleEnemy D_80092BD0 = {245, 55, 1440, 9999, 16};
BattleEnemy D_80092BDC = {251, 56, 1464, 9999, 16};
BattleEnemy D_80092BE8 = {427, 48, 1272, 9999, 17};
BattleEnemy D_80092BF4 = {411, 50, 1320, 9999, 17};
BattleEnemy D_80092C00 = {411, 50, 1320, 9999, 17};
BattleEnemy D_80092C0C = {412, 50, 1320, 9999, 17};
BattleEnemy D_80092C18 = {231, 50, 1320, 9999, 15};
BattleEnemy D_80092C24 = {228, 51, 1344, 9999, 15};
BattleEnemy D_80092C30 = {247, 52, 1368, 9999, 15};
BattleEnemy D_80092C3C = {178, 53, 2784, 9999, 16};
BattleEnemy D_80092C48 = {231, 50, 1320, 9999, 15};
BattleEnemy D_80092C54 = {228, 51, 1344, 9999, 15};
BattleEnemy D_80092C60 = {51, 1, 100, 9999, 12};
BattleEnemy D_80092C6C = {4, 4, 192, 9999, 21};
BattleEnemy D_80092C78 = {25, 4, 192, 9999, 16};
BattleEnemy D_80092C84 = {198, 5, 240, 9999, 23};
BattleEnemy D_80092C90 = {67, 40, 1080, 9999, 103};
BattleEnemy D_80092C9C = {51, 40, 1080, 9999, 120};
BattleEnemy D_80092CA8 = {137, 45, 1200, 9999, 44};
BattleEnemy D_80092CB4 = {32, 6, 264, 9999, 35};
BattleEnemy D_80092CC0 = {32, 7, 288, 9999, 38};
BattleEnemy D_80092CCC = {166, 9, 336, 9999, 28};
BattleEnemy D_80092CD8 = {80, 7, 288, 9999, 24};
BattleEnemy D_80092CE4 = {34, 8, 312, 9999, 8};
BattleEnemy D_80092CF0 = {197, 6, 264, 9999, 25};
BattleEnemy D_80092CFC = {132, 7, 288, 9999, 24};
BattleEnemy D_80092D08 = {110, 7, 288, 9999, 15};
BattleEnemy D_80092D14 = {206, 9, 336, 9999, 45};
BattleEnemy D_80092D20 = {49, 40, 1080, 9999, 55};
BattleEnemy D_80092D2C = {50, 40, 1080, 9999, 40};
BattleEnemy D_80092D38 = {7, 50, 1320, 9999, 80};
BattleEnemy D_80092D44 = {4, 6, 264, 9999, 29};
BattleEnemy D_80092D50 = {198, 7, 288, 9999, 27};
BattleEnemy D_80092D5C = {77, 7, 288, 9999, 14};
BattleEnemy D_80092D68 = {51, 7, 288, 9999, 32};
BattleEnemy D_80092D74 = {137, 7, 288, 9999, 11};
BattleEnemy D_80092D80 = {396, 7, 288, 9999, 15};
BattleEnemy D_80092D8C = {203, 10, 540, 9999, 22};
BattleEnemy D_80092D98 = {136, 10, 540, 9999, 9};
BattleEnemy D_80092DA4 = {28, 10, 360, 9999, 9};
BattleEnemy D_80092DB0 = {176, 11, 384, 150, 9};
BattleEnemy D_80092DBC = {217, 10, 360, 9999, 18};
BattleEnemy D_80092DC8 = {37, 10, 360, 9999, 17};
BattleEnemy D_80092DD4 = {10, 40, 1080, 9999, 42};
BattleEnemy D_80092DE0 = {50, 42, 1128, 9999, 42};
BattleEnemy D_80092DEC = {35, 39, 1056, 9999, 31};
BattleEnemy D_80092DF8 = {197, 17, 528, 9999, 50};
BattleEnemy D_80092E04 = {132, 17, 528, 9999, 44};
BattleEnemy D_80092E10 = {110, 18, 552, 9999, 28};
BattleEnemy D_80092E1C = {32, 9, 336, 9999, 45};
BattleEnemy D_80092E28 = {166, 10, 360, 9999, 30};
BattleEnemy D_80092E34 = {166, 10, 360, 9999, 30};
BattleEnemy D_80092E40 = {206, 41, 1104, 9999, 147};
BattleEnemy D_80092E4C = {170, 37, 1008, 96, 16};
BattleEnemy D_80092E58 = {223, 38, 1032, 9999, 19};
BattleEnemy D_80092E64 = {364, 39, 1056, 9999, 18};
BattleEnemy D_80092E70 = {210, 37, 1008, 120, 27};
BattleEnemy D_80092E7C = {14, 38, 1032, 9999, 20};
BattleEnemy D_80092E88 = {407, 39, 1056, 360, 17};
BattleEnemy D_80092E94 = {51, 36, 984, 9999, 109};
BattleEnemy D_80092EA0 = {395, 39, 1056, 9999, 20};
BattleEnemy D_80092EAC = {226, 40, 1080, 9999, 18};
BattleEnemy D_80092EB8 = {126, 40, 1080, 9999, 18};
BattleEnemy D_80092EC4 = {138, 40, 1080, 9999, 18};
BattleEnemy D_80092ED0 = {140, 41, 1104, 9999, 18};
BattleEnemy D_80092EDC = {405, 38, 1032, 9999, 25};
BattleEnemy D_80092EE8 = {408, 41, 1104, 9999, 18};
BattleEnemy D_80092EF4 = {121, 41, 1104, 9999, 17};
BattleEnemy D_80092F00 = {197, 41, 1104, 9999, 105};
BattleEnemy D_80092F0C = {132, 41, 1104, 9999, 92};
BattleEnemy D_80092F18 = {110, 42, 1128, 9999, 58};
BattleEnemy D_80092F24 = {206, 42, 1128, 9999, 150};
BattleEnemy D_80092F30 = {51, 57, 1488, 9999, 165};
BattleEnemy D_80092F3C = {396, 58, 1512, 9999, 78};
BattleEnemy D_80092F48 = {395, 60, 1560, 9999, 30};
BattleEnemy D_80092F54 = {203, 42, 1692, 9999, 68};
BattleEnemy D_80092F60 = {136, 42, 1692, 9999, 28};
BattleEnemy D_80092F6C = {8, 42, 1128, 9999, 68};
BattleEnemy D_80092F78 = {166, 41, 1104, 9999, 92};
BattleEnemy D_80092F84 = {397, 43, 1152, 9999, 30};
BattleEnemy D_80092F90 = {39, 42, 1128, 9999, 24};
BattleEnemy D_80092F9C = {210, 34, 936, 120, 25};
BattleEnemy D_80092FA8 = {14, 35, 960, 9999, 19};
BattleEnemy D_80092FB4 = {35, 35, 960, 9999, 28};
BattleEnemy D_80092FC0 = {241, 34, 936, 9999, 22};
BattleEnemy D_80092FCC = {165, 36, 984, 9999, 17};
BattleEnemy D_80092FD8 = {37, 35, 960, 9999, 46};
BattleEnemy D_80092FE4 = {223, 35, 960, 9999, 18};
BattleEnemy D_80092FF0 = {364, 36, 984, 9999, 16};
BattleEnemy D_80092FFC = {122, 35, 960, 336, 23};
BattleEnemy D_80093008 = {143, 35, 960, 9999, 22};
BattleEnemy D_80093014 = {61, 35, 960, 9999, 16};
BattleEnemy D_80093020 = {408, 35, 960, 9999, 16};
BattleEnemy D_8009302C = {121, 35, 960, 9999, 15};
BattleEnemy D_80093038 = {220, 36, 984, 9999, 20};
BattleEnemy D_80093044 = {221, 36, 984, 9999, 15};
BattleEnemy D_80093050 = {126, 36, 984, 9999, 16};
BattleEnemy D_8009305C = {8, 34, 936, 9999, 57};
BattleEnemy D_80093068 = {140, 37, 1008, 9999, 16};
BattleEnemy D_80093074 = {170, 44, 1176, 96, 19};
BattleEnemy D_80093080 = {223, 44, 1176, 9999, 22};
BattleEnemy D_8009308C = {404, 45, 1200, 9999, 19};
BattleEnemy D_80093098 = {4, 44, 1176, 9999, 131};
BattleEnemy D_800930A4 = {198, 44, 1176, 9999, 112};
BattleEnemy D_800930B0 = {424, 45, 1200, 9999, 20};
BattleEnemy D_800930BC = {210, 43, 1152, 120, 31};
BattleEnemy D_800930C8 = {14, 44, 1176, 9999, 23};
BattleEnemy D_800930D4 = {269, 45, 1200, 9999, 16};
BattleEnemy D_800930E0 = {397, 45, 1200, 9999, 31};
BattleEnemy D_800930EC = {171, 46, 1224, 9999, 16};
BattleEnemy D_800930F8 = {126, 44, 1176, 9999, 19};
BattleEnemy D_80093104 = {138, 45, 1200, 9999, 20};
BattleEnemy D_80093110 = {212, 45, 1200, 9999, 29};
BattleEnemy D_8009311C = {28, 44, 1176, 9999, 29};
BattleEnemy D_80093128 = {176, 44, 1176, 150, 28};
BattleEnemy D_80093134 = {229, 46, 1224, 9999, 17};
BattleEnemy D_80093140 = {395, 44, 1176, 9999, 22};
BattleEnemy D_8009314C = {226, 45, 1200, 9999, 21};
BattleEnemy D_80093158 = {60, 46, 1224, 9999, 17};
BattleEnemy D_80093164 = {224, 45, 1200, 9999, 19};
BattleEnemy D_80093170 = {225, 46, 1224, 9999, 17};
BattleEnemy D_8009317C = {419, 45, 1200, 9999, 17};
BattleEnemy D_80093188 = {54, 46, 1224, 9999, 16};
BattleEnemy D_80093194 = {176, 52, 1368, 150, 33};
BattleEnemy D_800931A0 = {229, 53, 1392, 9999, 19};
BattleEnemy D_800931AC = {41, 53, 1392, 9999, 18};
BattleEnemy D_800931B8 = {203, 52, 2052, 9999, 83};
BattleEnemy D_800931C4 = {8, 52, 1368, 9999, 83};
BattleEnemy D_800931D0 = {409, 54, 1416, 9999, 18};
BattleEnemy D_800931DC = {206, 52, 1368, 9999, 182};
BattleEnemy D_800931E8 = {365, 53, 1392, 9999, 19};
BattleEnemy D_800931F4 = {197, 52, 1368, 9999, 130};
BattleEnemy D_80093200 = {132, 52, 1368, 9999, 114};
BattleEnemy D_8009320C = {110, 53, 1392, 9999, 71};
BattleEnemy D_80093218 = {224, 52, 1368, 9999, 22};
BattleEnemy D_80093224 = {225, 52, 1368, 9999, 19};
BattleEnemy D_80093230 = {281, 53, 1392, 9999, 19};
BattleEnemy D_8009323C = {226, 52, 1368, 9999, 23};
BattleEnemy D_80093248 = {60, 52, 1368, 9999, 19};
BattleEnemy D_80093254 = {423, 53, 1392, 9999, 18};
BattleEnemy D_80093260 = {122, 53, 1392, 336, 33};
BattleEnemy D_8009326C = {143, 53, 1392, 9999, 32};
BattleEnemy D_80093278 = {250, 54, 1416, 9999, 19};
BattleEnemy D_80093284 = {405, 55, 1440, 9999, 36};
BattleEnemy D_80093290 = {425, 57, 1488, 9999, 22};
BattleEnemy D_8009329C = {428, 60, 1560, 9999, 20};
BattleEnemy D_800932A8 = {364, 53, 1392, 9999, 23};
BattleEnemy D_800932B4 = {177, 53, 1392, 9999, 19};
BattleEnemy D_800932C0 = {206, 53, 1392, 9999, 186};
BattleEnemy D_800932CC = {365, 54, 1416, 9999, 19};
BattleEnemy D_800932D8 = {32, 1, 120, 9999, 16};
BattleEnemy D_800932E4 = {32, 1, 120, 9999, 16};
BattleEnemy D_800932F0 = {32, 1, 120, 9999, 16};
BattleEnemy D_800932FC = {32, 1, 120, 9999, 16};
BattleEnemy D_80093308 = {32, 1, 120, 9999, 16};
BattleEnemy D_80093314 = {32, 1, 120, 9999, 16};
BattleEnemy D_80093320 = {32, 1, 120, 9999, 16};
BattleEnemy D_8009332C = {32, 1, 120, 9999, 16};
BattleEnemy D_80093338 = {32, 1, 120, 9999, 16};
#if VERSION_US
BattleEnemy D_80093344 = {32, 1, 120, 9999, 16};
#elif VERSION_EU
BattleEnemy D_80093344 = {141, 90, 4560, 9999, 39};
BattleEnemy D_800940A4 = {436, 95, 4800, 960, 33};
BattleEnemy D_800940B0 = {382, 99, 7488, 9999, 27};
#endif
BattleEnemy D_80093350 = {203, 14, 684, 9999, 28};
BattleEnemy D_8009335C = {51, 10, 360, 9999, 40};
BattleEnemy D_80093368 = {32, 6, 264, 9999, 35};
BattleEnemy D_80093374 = {449, 17, 1056, 9999, 16};
BattleEnemy D_80093380 = {451, 26, 1488, 9999, 16};
BattleEnemy D_8009338C = {452, 28, 1584, 9999, 16};
BattleEnemy D_80093398 = {453, 29, 1632, 9999, 16};
BattleEnemy D_800933A4 = {454, 28, 1584, 9999, 16};
BattleEnemy D_800933B0 = {456, 28, 1584, 9999, 16};
BattleEnemy D_800933BC = {455, 28, 1584, 9999, 16};
BattleEnemy D_800933C8 = {450, 19, 1152, 9999, 16};
BattleEnemy D_800933D4 = {51, 5, 240, 9999, 27};
BattleEnemy D_800933E0 = {395, 7, 288, 9999, 5};
#if VERSION_US
BattleEnemy D_800933EC = {203, 6, 396, 9999, 16};
BattleEnemy D_800933F8 = {136, 22, 972, 9999, 16};
BattleEnemy D_80093404 = {8, 6, 264, 9999, 16};
BattleEnemy D_80093410 = {166, 4, 192, 9999, 16};
BattleEnemy D_8009341C = {397, 21, 624, 9999, 16};
BattleEnemy D_80093428 = {39, 26, 744, 9999, 16};
BattleEnemy D_80093434 = {210, 20, 600, 120, 16};
BattleEnemy D_80093440 = {14, 29, 816, 9999, 16};
BattleEnemy D_8009344C = {35, 18, 552, 9999, 16};
BattleEnemy D_80093458 = {241, 24, 696, 9999, 16};
BattleEnemy D_80093464 = {165, 34, 936, 9999, 16};
BattleEnemy D_80093470 = {37, 9, 336, 9999, 16};
BattleEnemy D_8009347C = {223, 31, 864, 9999, 16};
BattleEnemy D_80093488 = {364, 35, 960, 9999, 16};
#elif VERSION_EU
BattleEnemy D_800933EC = {281, 43, 1152, 9999, 16};
BattleEnemy D_800933F8 = {202, 43, 1152, 9999, 16};
BattleEnemy D_80093404 = {204, 44, 1176, 9999, 16};
BattleEnemy D_80093410 = {229, 44, 1176, 9999, 16};
BattleEnemy D_8009341C = {24, 45, 1800, 9999, 16};
#endif
BattleEnemy D_80093494 = {122, 23, 672, 336, 16};
BattleEnemy D_800934A0 = {143, 24, 696, 9999, 16};
BattleEnemy D_800934AC = {61, 35, 960, 9999, 16};
BattleEnemy D_800934B8 = {408, 35, 960, 9999, 16};
BattleEnemy D_800934C4 = {121, 38, 1032, 9999, 16};
BattleEnemy D_800934D0 = {220, 27, 768, 9999, 16};
BattleEnemy D_800934DC = {221, 40, 1080, 9999, 16};
BattleEnemy D_800934E8 = {126, 36, 984, 9999, 16};
BattleEnemy D_800934F4 = {8, 6, 264, 9999, 16};
BattleEnemy D_80093500 = {140, 36, 984, 9999, 16};
BattleEnemy D_8009350C = {170, 36, 984, 96, 16};
BattleEnemy D_80093518 = {223, 31, 864, 9999, 16};
BattleEnemy D_80093524 = {404, 37, 1008, 9999, 16};
BattleEnemy D_80093530 = {4, 2, 144, 9999, 16};
BattleEnemy D_8009353C = {198, 3, 168, 9999, 16};
BattleEnemy D_80093548 = {424, 36, 984, 9999, 16};
BattleEnemy D_80093554 = {210, 20, 600, 120, 16};
BattleEnemy D_80093560 = {14, 29, 816, 9999, 16};
BattleEnemy D_8009356C = {269, 45, 1200, 9999, 16};
BattleEnemy D_80093578 = {397, 21, 624, 9999, 16};
BattleEnemy D_80093584 = {171, 47, 1248, 9999, 16};
BattleEnemy D_80093590 = {126, 36, 984, 9999, 16};
BattleEnemy D_8009359C = {138, 36, 984, 9999, 16};
BattleEnemy D_800935A8 = {212, 23, 672, 9999, 16};
BattleEnemy D_800935B4 = {28, 22, 648, 9999, 16};
BattleEnemy D_800935C0 = {176, 23, 672, 150, 16};
BattleEnemy D_800935CC = {229, 44, 1176, 9999, 16};
BattleEnemy D_800935D8 = {395, 30, 840, 9999, 16};
BattleEnemy D_800935E4 = {226, 34, 936, 9999, 16};
BattleEnemy D_800935F0 = {60, 44, 1176, 9999, 16};
BattleEnemy D_800935FC = {224, 37, 1008, 9999, 16};
BattleEnemy D_80093608 = {225, 44, 1176, 9999, 16};
BattleEnemy D_80093614 = {419, 43, 1152, 9999, 16};
BattleEnemy D_80093620 = {54, 46, 1224, 9999, 16};
BattleEnemy D_8009362C = {176, 23, 672, 150, 16};
BattleEnemy D_80093638 = {229, 44, 1176, 9999, 16};
BattleEnemy D_80093644 = {41, 46, 1224, 9999, 16};
BattleEnemy D_80093650 = {203, 6, 396, 9999, 16};
BattleEnemy D_8009365C = {8, 6, 264, 9999, 16};
BattleEnemy D_80093668 = {409, 47, 1248, 9999, 16};
BattleEnemy D_80093674 = {206, 1, 120, 9999, 16};
BattleEnemy D_80093680 = {365, 45, 1200, 9999, 16};
BattleEnemy D_8009368C = {197, 3, 168, 9999, 16};
BattleEnemy D_80093698 = {132, 4, 192, 9999, 16};
BattleEnemy D_800936A4 = {110, 8, 312, 9999, 16};
BattleEnemy D_800936B0 = {224, 37, 1008, 9999, 16};
BattleEnemy D_800936BC = {225, 44, 1176, 9999, 16};
BattleEnemy D_800936C8 = {281, 43, 1152, 9999, 16};
BattleEnemy D_800936D4 = {226, 34, 936, 9999, 16};
BattleEnemy D_800936E0 = {60, 44, 1176, 9999, 16};
BattleEnemy D_800936EC = {423, 48, 1272, 9999, 16};
BattleEnemy D_800936F8 = {122, 23, 672, 336, 16};
BattleEnemy D_80093704 = {143, 24, 696, 9999, 16};
BattleEnemy D_80093710 = {250, 45, 1200, 9999, 16};
BattleEnemy D_8009371C = {405, 22, 648, 9999, 16};
BattleEnemy D_80093728 = {425, 41, 1104, 9999, 16};
BattleEnemy D_80093734 = {428, 48, 1272, 9999, 16};
BattleEnemy D_80093740 = {364, 35, 960, 9999, 16};
BattleEnemy D_8009374C = {177, 45, 1200, 9999, 16};
BattleEnemy D_80093758 = {206, 1, 120, 9999, 16};
BattleEnemy D_80093764 = {365, 45, 1200, 9999, 16};
#if VERSION_US
BattleEnemy D_80093770 = {172, 5, 240, 9999, 16};
BattleEnemy D_8009377C = {8, 6, 264, 9999, 16};
BattleEnemy D_80093788 = {207, 10, 360, 9999, 16};
BattleEnemy D_80093794 = {222, 5, 240, 9999, 16};
BattleEnemy D_800937A0 = {77, 9, 336, 9999, 16};
BattleEnemy D_800937AC = {119, 20, 600, 200, 16};
BattleEnemy D_800937B8 = {400, 33, 912, 9999, 16};
BattleEnemy D_800937C4 = {208, 29, 816, 9999, 16};
BattleEnemy D_800937D0 = {13, 25, 480, 9999, 16};
BattleEnemy D_800937DC = {270, 43, 1152, 9999, 16};
BattleEnemy D_800937E8 = {65, 44, 1176, 296, 16};
BattleEnemy D_800937F4 = {360, 44, 1176, 9999, 16};
BattleEnemy D_80093800 = {138, 36, 984, 9999, 16};
BattleEnemy D_8009380C = {402, 41, 1656, 9999, 16};
BattleEnemy D_80093818 = {237, 44, 1176, 9999, 16};
BattleEnemy D_80093824 = {425, 41, 1104, 9999, 16};
BattleEnemy D_80093830 = {202, 43, 1152, 9999, 16};
BattleEnemy D_8009383C = {238, 43, 1152, 9999, 16};
BattleEnemy D_80093848 = {108, 44, 1176, 9999, 16};
BattleEnemy D_80093854 = {193, 45, 1200, 9999, 16};
BattleEnemy D_80093860 = {428, 48, 1272, 9999, 16};
BattleEnemy D_8009386C = {190, 48, 1272, 9999, 16};
BattleEnemy D_80093878 = {215, 49, 1296, 9999, 16};
BattleEnemy D_80093884 = {231, 54, 1416, 9999, 16};
BattleEnemy D_80093890 = {358, 12, 816, 9999, 16};
BattleEnemy D_8009389C = {124, 14, 912, 9999, 16};
BattleEnemy D_800938A8 = {356, 32, 1776, 280, 16};
BattleEnemy D_800938B4 = {70, 32, 1776, 9999, 16};
#elif VERSION_EU
BattleEnemy D_80093770 = {449, 60, 3120, 9999, 47};
BattleEnemy D_8009377C = {451, 60, 3120, 9999, 34};
BattleEnemy D_80093788 = {450, 65, 3360, 9999, 47};
BattleEnemy D_80093794 = {453, 60, 3120, 9999, 31};
BattleEnemy D_800937A0 = {358, 70, 3600, 9999, 71};
BattleEnemy D_800937AC = {124, 75, 3840, 9999, 67};
BattleEnemy D_800937B8 = {237, 80, 4080, 9999, 28};
BattleEnemy D_800937C4 = {425, 70, 2700, 9999, 26};
BattleEnemy D_800937D0 = {437, 75, 5760, 40, 30};
BattleEnemy D_800937DC = {337, 80, 4080, 9999, 30};
BattleEnemy D_800937E8 = {193, 70, 2700, 9999, 24};
BattleEnemy D_800937F4 = {432, 75, 2880, 9999, 22};
BattleEnemy D_80093800 = {356, 80, 4080, 280, 37};
BattleEnemy D_8009380C = {215, 70, 2700, 9999, 22};
BattleEnemy D_80093818 = {70, 75, 3840, 9999, 35};
BattleEnemy D_80093824 = {24, 80, 6120, 9999, 27};
BattleEnemy D_80093830 = {452, 60, 3120, 9999, 32};
BattleEnemy D_8009383C = {454, 70, 3600, 9999, 36};
BattleEnemy D_80093848 = {455, 70, 3600, 9999, 36};
BattleEnemy D_80093854 = {456, 70, 1776, 9999, 16};
#endif
BattleEnemy D_800938C0 = {141, 34, 1872, 9999, 16};
BattleEnemy D_800938CC = {337, 40, 2160, 9999, 16};
BattleEnemy D_800938D8 = {436, 44, 2352, 960, 16};
#if VERSION_US
BattleEnemy D_800938E4 = {443, 45, 2400, 9999, 16};
BattleEnemy D_800938F0 = {444, 46, 2448, 9999, 16};
BattleEnemy D_800938FC = {447, 47, 2496, 9999, 16};
BattleEnemy D_80093908 = {445, 55, 2880, 9999, 16};
BattleEnemy D_80093914 = {446, 57, 2976, 8, 16};
BattleEnemy D_80093920 = {448, 53, 2784, 9999, 16};
#elif VERSION_EU
BattleEnemy D_800938E4 = {443, 65, 3360, 9999, 22};
BattleEnemy D_800938F0 = {444, 65, 3360, 9999, 22};
BattleEnemy D_800938FC = {447, 70, 3600, 9999, 23};
BattleEnemy D_80093908 = {445, 70, 3600, 9999, 20};
BattleEnemy D_80093914 = {446, 75, 3840, 8, 21};
BattleEnemy D_80093920 = {448, 75, 3840, 9999, 22};
#endif
BattleEnemy D_8009392C = {465, 28, 792, 9999, 16};
BattleEnemy D_80093938 = {436, 15, 960, 960, 7};
BattleEnemy D_80093944 = {442, 65, 5040, 9999, 16};
BattleEnemy D_80093950 = {466, 70, 3600, 9999, 16};
BattleEnemy D_8009395C = {467, 70, 5400, 9999, 16};
BattleEnemy D_80093968 = {466, 70, 3600, 9999, 16};
BattleEnemy D_80093974 = {467, 70, 5400, 9999, 16};
BattleEnemy D_80093980 = {457, 7, 288, 9999, 16};
BattleEnemy D_8009398C = {458, 12, 408, 9999, 16};
BattleEnemy D_80093998 = {459, 17, 528, 9999, 16};
BattleEnemy D_800939A4 = {460, 27, 768, 9999, 16};
BattleEnemy D_800939B0 = {461, 37, 1008, 9999, 16};
BattleEnemy D_800939BC = {462, 42, 1128, 9999, 16};
BattleEnemy D_800939C8 = {463, 47, 1248, 9999, 16};
BattleEnemy D_800939D4 = {464, 47, 1248, 9999, 16};
#if VERSION_US
Encounter D_800939E0[] = {
    {{&D_800920A8, &D_800920A8, &D_800920A8}, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800920B4, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800920C0, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800920CC, &D_800920D8, &D_800920E4}, 0, 2, {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800920F0, &D_800920FC, &D_80092108}, 127, 2, {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092114, &D_80092120, &D_800920A8}, 0, 2, {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009212C, &D_80092138, &D_80092144}, 0, 2, {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092150, &D_800920A8, &D_800920A8}, 0, 2, {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009215C, &D_800920A8, &D_800920A8}, 0, 2, {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092168, &D_800920A8, &D_800920A8}, 0, 2, {0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1}},
    {{&D_80092174, &D_80092180, &D_8009218C}, 0, 2, {1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1}},
    {{&D_80092198, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800921A4, &D_800920A8, &D_800920A8}, 0, 2, {0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1}},
    {{&D_800921B0, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800921BC, &D_800921C8, &D_800921D4}, 0, 2, {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800921E0, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1}},
    {{&D_800921EC, &D_800921F8, &D_80092204}, 127, 2, {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092210, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009221C, &D_80092228, &D_80092234}, 0, 2, {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092240, &D_8009224C, &D_80092258}, 0, 2, {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092264, &D_80092270, &D_8009227C}, 0, 2, {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092288, &D_80092294, &D_800922A0}, 0, 2, {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800922AC, &D_800922B8, &D_800922C4}, 0, 2, {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800922D0, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1}},
    {{&D_800922DC, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800922E8, &D_800922F4, &D_80092300}, 0, 2, {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009230C, &D_80092318, &D_80092324}, 0, 2, {1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1}},
    {{&D_80092330, &D_8009233C, &D_80092348}, 0, 2, {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092354, &D_80092360, &D_8009236C}, 0, 2, {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092378, &D_80092384, &D_80092390}, 0, 2, {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009239C, &D_800920A8, &D_800920A8}, 127, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_800923A8, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1}},
    {{&D_800923B4, &D_800923C0, &D_800923CC}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1}},
    {{&D_800923D8, &D_800923E4, &D_800923F0}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1}},
    {{&D_800923FC, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092408, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092414, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092420, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009242C, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092438, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092444, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092450, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009245C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092468, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092474, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092480, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009248C, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092498, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800924A4, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800924B0, &D_800920A8, &D_800920A8}, 32, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800924BC, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800924C8, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800924D4, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800924E0, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800924EC, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800924F8, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092504, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092510, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009251C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092528, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092534, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092540, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009254C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092558, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092564, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092570, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009257C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092588, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092594, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800925A0, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800925AC, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800925B8, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800925C4, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800925D0, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800925DC, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800925E8, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800925F4, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092600, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009260C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092618, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092624, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092630, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009263C, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092648, &D_800920A8, &D_800920A8}, 32, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092654, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092660, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009266C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092678, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092684, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092690, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009269C, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800926A8, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800926B4, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800926C0, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800926CC, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800926D8, &D_800920A8, &D_800920A8}, 32, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800926E4, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800926F0, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800926FC, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_80092708, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092714, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092720, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009272C, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092738, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092744, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092750, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009275C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092768, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092774, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092780, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009278C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092798, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800927A4, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800927B0, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800927BC, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800927C8, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800927D4, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800927E0, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800927EC, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800927F8, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092804, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092810, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009281C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092828, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092834, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092840, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009284C, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092858, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092864, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092870, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009287C, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092888, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_80092894, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800928A0, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800928AC, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800928B8, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800928C4, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800928D0, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800928DC, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800928E8, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800928F4, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092900, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009290C, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092918, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092924, &D_800920A8, &D_800920A8}, 127, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092930, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009293C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092948, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092954, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092960, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009296C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092978, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092984, &D_800920A8, &D_800920A8}, 32, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092990, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009299C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800929A8, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800929B4, &D_800920A8, &D_800920A8}, 32, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800929C0, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800929CC, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800929D8, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800929E4, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800929F0, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800929FC, &D_800920A8, &D_800920A8}, 32, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A08, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A14, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A20, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A2C, &D_800920A8, &D_800920A8}, 20, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A38, &D_800920A8, &D_800920A8}, 24, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A44, &D_800920A8, &D_800920A8}, 28, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A50, &D_800920A8, &D_800920A8}, 32, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A5C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A68, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A74, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A80, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A8C, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A98, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_80092AA4, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092AB0, &D_800920A8, &D_800920A8}, 32, 1, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_80092ABC, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092AC8, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092AD4, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_80092AE0, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092AEC, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092AF8, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092B04, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092B10, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092B1C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_80092B28, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092B34, &D_80092B40, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092B4C, &D_80092B58, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092B64, &D_80092B70, &D_80092B7C}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092B88, &D_800920A8, &D_800920A8}, 0, 3, {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092B94, &D_80092BA0, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092BAC, &D_80092BB8, &D_80092BC4}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092BD0, &D_80092BDC, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092BE8, &D_80092BF4, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092C00, &D_80092C0C, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092C18, &D_80092C24, &D_80092C30}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092C3C, &D_800920A8, &D_800920A8}, 0, 3, {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092C48, &D_80092C54, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092C60, &D_800920A8, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092C6C, &D_80092C78, &D_80092C84}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092C90, &D_80092C9C, &D_80092CA8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092CB4, &D_80092CC0, &D_80092CCC}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092CD8, &D_80092CE4, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092CF0, &D_80092CFC, &D_80092D08}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092D14, &D_800920A8, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092D20, &D_80092D2C, &D_80092D38}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092D44, &D_80092D50, &D_80092D5C}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092D68, &D_80092D74, &D_80092D80}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092D8C, &D_80092D98, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092DA4, &D_80092DB0, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092DBC, &D_80092DC8, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092DD4, &D_80092DE0, &D_80092DEC}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092DF8, &D_80092E04, &D_80092E10}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092E1C, &D_80092E28, &D_80092E34}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092E40, &D_800920A8, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092E4C, &D_80092E58, &D_80092E64}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092E70, &D_80092E7C, &D_80092E88}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092E94, &D_80092EA0, &D_80092EAC}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092EB8, &D_80092EC4, &D_80092ED0}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092EDC, &D_80092EE8, &D_80092EF4}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092F00, &D_80092F0C, &D_80092F18}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092F24, &D_800920A8, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092F30, &D_80092F3C, &D_80092F48}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092F54, &D_80092F60, &D_80092F6C}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092F78, &D_80092F84, &D_80092F90}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092F9C, &D_80092FA8, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092FB4, &D_80092FC0, &D_80092FCC}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092FD8, &D_80092FE4, &D_80092FF0}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092FFC, &D_80093008, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093014, &D_80093020, &D_8009302C}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093038, &D_80093044, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093050, &D_8009305C, &D_80093068}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093074, &D_80093080, &D_8009308C}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093098, &D_800930A4, &D_800930B0}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800930BC, &D_800930C8, &D_800930D4}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800930E0, &D_800930EC, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800930F8, &D_80093104, &D_80093110}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009311C, &D_80093128, &D_80093134}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093140, &D_8009314C, &D_80093158}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093164, &D_80093170, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009317C, &D_80093188, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093194, &D_800931A0, &D_800931AC}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800931B8, &D_800931C4, &D_800931D0}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800931DC, &D_800931E8, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}},
    {{&D_800931F4, &D_80093200, &D_8009320C}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093218, &D_80093224, &D_80093230}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009323C, &D_80093248, &D_80093254}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093260, &D_8009326C, &D_80093278}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093284, &D_80093290, &D_8009329C}, 0, 3, {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1}},
    {{&D_800932A8, &D_800932B4, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}},
    {{&D_800932C0, &D_800932CC, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}},
    {{&D_800932D8, &D_800920A8, &D_800920A8}, 0, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800932E4, &D_800920A8, &D_800920A8}, 0, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800932F0, &D_800920A8, &D_800920A8}, 0, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800932FC, &D_800920A8, &D_800920A8}, 0, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093308, &D_800920A8, &D_800920A8}, 0, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093314, &D_800920A8, &D_800920A8}, 0, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093320, &D_800920A8, &D_800920A8}, 0, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009332C, &D_800920A8, &D_800920A8}, 0, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093338, &D_800920A8, &D_800920A8}, 0, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093344, &D_800920A8, &D_800920A8}, 0, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093350, &D_8009335C, &D_80093368}, 0, 2, {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093374, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093380, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009338C, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093398, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800933A4, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800933B0, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800933BC, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800933C8, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800933D4, &D_800933E0, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800933EC, &D_800933F8, &D_80093404}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093410, &D_8009341C, &D_80093428}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093434, &D_80093440, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009344C, &D_80093458, &D_80093464}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093470, &D_8009347C, &D_80093488}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093494, &D_800934A0, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800934AC, &D_800934B8, &D_800934C4}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800934D0, &D_800934DC, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800934E8, &D_800934F4, &D_80093500}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009350C, &D_80093518, &D_80093524}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093530, &D_8009353C, &D_80093548}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093554, &D_80093560, &D_8009356C}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093578, &D_80093584, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093590, &D_8009359C, &D_800935A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800935B4, &D_800935C0, &D_800935CC}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800935D8, &D_800935E4, &D_800935F0}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800935FC, &D_80093608, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093614, &D_80093620, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009362C, &D_80093638, &D_80093644}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093650, &D_8009365C, &D_80093668}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093674, &D_80093680, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009368C, &D_80093698, &D_800936A4}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800936B0, &D_800936BC, &D_800936C8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800936D4, &D_800936E0, &D_800936EC}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800936F8, &D_80093704, &D_80093710}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009371C, &D_80093728, &D_80093734}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093740, &D_8009374C, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093758, &D_80093764, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093770, &D_8009377C, &D_80093788}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_80093794, &D_800937A0, &D_800937AC}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_800937B8, &D_800937C4, &D_800937D0}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_800937DC, &D_800937E8, &D_800937F4}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_80093800, &D_8009380C, &D_80093818}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_80093824, &D_80093830, &D_8009383C}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_80093848, &D_80093854, &D_80093860}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_8009386C, &D_80093878, &D_80093884}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_80093890, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_8009389C, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_800938A8, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_800938B4, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_800938C0, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_800938CC, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_800938D8, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_800938E4, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_800938F0, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_800938FC, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_80093908, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_80093914, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_80093920, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_8009392C, &D_800920A8, &D_800920A8}, 0, 3, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_80093938, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_80093944, &D_80093950, &D_8009395C}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_80093968, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_80093974, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_80093980, &D_800920A8, &D_800920A8}, 8, 5, {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_8009398C, &D_800920A8, &D_800920A8}, 8, 5, {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_80093998, &D_800920A8, &D_800920A8}, 16, 5, {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_800939A4, &D_800920A8, &D_800920A8}, 16, 5, {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_800939B0, &D_800920A8, &D_800920A8}, 24, 5, {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_800939BC, &D_800920A8, &D_800920A8}, 24, 5, {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_800939C8, &D_800920A8, &D_800920A8}, 32, 5, {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_800939D4, &D_800920A8, &D_800920A8}, 32, 5, {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0}},
};
#elif VERSION_EU
Encounter D_800939E0[] = {
    {{&D_800920A8, &D_800920A8, &D_800920A8}, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800920B4, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800920C0, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800920CC, &D_800920D8, &D_800920E4}, 0, 2, {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800920F0, &D_800920FC, &D_80092108}, 127, 2, {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092114, &D_80092120, &D_800920A8}, 0, 2, {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009212C, &D_80092138, &D_80092144}, 0, 2, {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092150, &D_800920A8, &D_800920A8}, 0, 2, {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009215C, &D_800920A8, &D_800920A8}, 0, 2, {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092168, &D_800920A8, &D_800920A8}, 0, 2, {0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1}},
    {{&D_80092174, &D_80092180, &D_8009218C}, 0, 2, {1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1}},
    {{&D_80092198, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800921A4, &D_800920A8, &D_800920A8}, 0, 2, {0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1}},
    {{&D_800921B0, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800921BC, &D_800921C8, &D_800921D4}, 0, 2, {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800921E0, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1}},
    {{&D_800921EC, &D_800921F8, &D_80092204}, 127, 2, {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092210, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009221C, &D_80092228, &D_80092234}, 0, 2, {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092240, &D_8009224C, &D_80092258}, 0, 2, {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092264, &D_80092270, &D_8009227C}, 0, 2, {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092288, &D_80092294, &D_800922A0}, 0, 2, {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800922AC, &D_800922B8, &D_800922C4}, 0, 2, {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800922D0, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1}},
    {{&D_800922DC, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800922E8, &D_800922F4, &D_80092300}, 0, 2, {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009230C, &D_80092318, &D_80092324}, 0, 2, {1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1}},
    {{&D_80092330, &D_8009233C, &D_80092348}, 0, 2, {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092354, &D_80092360, &D_8009236C}, 0, 2, {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092378, &D_80092384, &D_80092390}, 0, 2, {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009239C, &D_800920A8, &D_800920A8}, 127, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_800923A8, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1}},
    {{&D_800923B4, &D_800923C0, &D_800923CC}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1}},
    {{&D_800923D8, &D_800923E4, &D_800923F0}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1}},
    {{&D_800923FC, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092408, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092414, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092420, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009242C, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092438, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092444, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092450, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009245C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092468, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092474, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092480, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009248C, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092498, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800924A4, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800924B0, &D_800920A8, &D_800920A8}, 32, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800924BC, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800924C8, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800924D4, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800924E0, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800924EC, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800924F8, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092504, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092510, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009251C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092528, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092534, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092540, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009254C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092558, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092564, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092570, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009257C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092588, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092594, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800925A0, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800925AC, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800925B8, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800925C4, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800925D0, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800925DC, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800925E8, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800925F4, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092600, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009260C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092618, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092624, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092630, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009263C, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092648, &D_800920A8, &D_800920A8}, 32, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092654, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092660, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009266C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092678, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092684, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092690, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009269C, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800926A8, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800926B4, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800926C0, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800926CC, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800926D8, &D_800920A8, &D_800920A8}, 32, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800926E4, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800926F0, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800926FC, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_80092708, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092714, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092720, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009272C, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092738, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092744, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092750, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009275C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092768, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092774, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092780, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009278C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092798, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800927A4, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800927B0, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800927BC, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800927C8, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800927D4, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800927E0, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800927EC, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800927F8, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092804, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092810, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009281C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092828, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092834, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092840, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009284C, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092858, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092864, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092870, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009287C, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092888, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_80092894, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800928A0, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800928AC, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800928B8, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800928C4, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800928D0, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800928DC, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800928E8, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800928F4, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092900, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009290C, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092918, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092924, &D_800920A8, &D_800920A8}, 127, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092930, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009293C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092948, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092954, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092960, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009296C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092978, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092984, &D_800920A8, &D_800920A8}, 32, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092990, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_8009299C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800929A8, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800929B4, &D_800920A8, &D_800920A8}, 32, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800929C0, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800929CC, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800929D8, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800929E4, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800929F0, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_800929FC, &D_800920A8, &D_800920A8}, 32, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A08, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A14, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A20, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A2C, &D_800920A8, &D_800920A8}, 20, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A38, &D_800920A8, &D_800920A8}, 24, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A44, &D_800920A8, &D_800920A8}, 28, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A50, &D_800920A8, &D_800920A8}, 32, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A5C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A68, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A74, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A80, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A8C, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092A98, &D_800920A8, &D_800920A8}, 16, 1, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_80092AA4, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092AB0, &D_800920A8, &D_800920A8}, 32, 1, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_80092ABC, &D_800920A8, &D_800920A8}, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092AC8, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092AD4, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_80092AE0, &D_800920A8, &D_800920A8}, 12, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092AEC, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092AF8, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092B04, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092B10, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092B1C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_80092B28, &D_800920A8, &D_800920A8}, 4, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{&D_80092B34, &D_80092B40, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092B4C, &D_80092B58, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092B64, &D_80092B70, &D_80092B7C}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092B88, &D_800920A8, &D_800920A8}, 0, 3, {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092B94, &D_80092BA0, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092BAC, &D_80092BB8, &D_80092BC4}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092BD0, &D_80092BDC, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092BE8, &D_80092BF4, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092C00, &D_80092C0C, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092C18, &D_80092C24, &D_80092C30}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092C3C, &D_800920A8, &D_800920A8}, 0, 3, {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092C48, &D_80092C54, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092C60, &D_800920A8, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092C6C, &D_80092C78, &D_80092C84}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092C90, &D_80092C9C, &D_80092CA8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092CB4, &D_80092CC0, &D_80092CCC}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092CD8, &D_80092CE4, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092CF0, &D_80092CFC, &D_80092D08}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092D14, &D_800920A8, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092D20, &D_80092D2C, &D_80092D38}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092D44, &D_80092D50, &D_80092D5C}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092D68, &D_80092D74, &D_80092D80}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092D8C, &D_80092D98, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092DA4, &D_80092DB0, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092DBC, &D_80092DC8, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092DD4, &D_80092DE0, &D_80092DEC}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092DF8, &D_80092E04, &D_80092E10}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092E1C, &D_80092E28, &D_80092E34}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092E40, &D_800920A8, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092E4C, &D_80092E58, &D_80092E64}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092E70, &D_80092E7C, &D_80092E88}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092E94, &D_80092EA0, &D_80092EAC}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092EB8, &D_80092EC4, &D_80092ED0}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092EDC, &D_80092EE8, &D_80092EF4}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092F00, &D_80092F0C, &D_80092F18}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092F24, &D_800920A8, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092F30, &D_80092F3C, &D_80092F48}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092F54, &D_80092F60, &D_80092F6C}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092F78, &D_80092F84, &D_80092F90}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092F9C, &D_80092FA8, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092FB4, &D_80092FC0, &D_80092FCC}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092FD8, &D_80092FE4, &D_80092FF0}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80092FFC, &D_80093008, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093014, &D_80093020, &D_8009302C}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093038, &D_80093044, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093050, &D_8009305C, &D_80093068}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093074, &D_80093080, &D_8009308C}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093098, &D_800930A4, &D_800930B0}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800930BC, &D_800930C8, &D_800930D4}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800930E0, &D_800930EC, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800930F8, &D_80093104, &D_80093110}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009311C, &D_80093128, &D_80093134}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093140, &D_8009314C, &D_80093158}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093164, &D_80093170, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009317C, &D_80093188, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093194, &D_800931A0, &D_800931AC}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800931B8, &D_800931C4, &D_800931D0}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800931DC, &D_800931E8, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}},
    {{&D_800931F4, &D_80093200, &D_8009320C}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093218, &D_80093224, &D_80093230}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009323C, &D_80093248, &D_80093254}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093260, &D_8009326C, &D_80093278}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093284, &D_80093290, &D_8009329C}, 0, 3, {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1}},
    {{&D_800932A8, &D_800932B4, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}},
    {{&D_800932C0, &D_800932CC, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}},
    {{&D_800932D8, &D_800920A8, &D_800920A8}, 0, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800932E4, &D_800920A8, &D_800920A8}, 0, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800932F0, &D_800920A8, &D_800920A8}, 0, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800932FC, &D_800920A8, &D_800920A8}, 0, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093308, &D_800920A8, &D_800920A8}, 0, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093314, &D_800920A8, &D_800920A8}, 0, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093320, &D_800920A8, &D_800920A8}, 0, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009332C, &D_800920A8, &D_800920A8}, 0, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093338, &D_800920A8, &D_800920A8}, 0, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093344, &D_800940A4, &D_800940B0}, 0, 4, {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1}},
    {{&D_80093350, &D_8009335C, &D_80093368}, 0, 2, {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093374, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093380, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009338C, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093398, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800933A4, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800933B0, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800933BC, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800933C8, &D_800920A8, &D_800920A8}, 0, 2, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800933D4, &D_800933E0, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800933EC, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_800933F8, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_80093404, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_80093410, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_8009341C, &D_800920A8, &D_800920A8}, 8, 1, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_80093494, &D_800934A0, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800934AC, &D_800934B8, &D_800934C4}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800934D0, &D_800934DC, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800934E8, &D_800934F4, &D_80093500}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009350C, &D_80093518, &D_80093524}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093530, &D_8009353C, &D_80093548}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093554, &D_80093560, &D_8009356C}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093578, &D_80093584, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093590, &D_8009359C, &D_800935A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800935B4, &D_800935C0, &D_800935CC}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800935D8, &D_800935E4, &D_800935F0}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800935FC, &D_80093608, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093614, &D_80093620, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009362C, &D_80093638, &D_80093644}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093650, &D_8009365C, &D_80093668}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093674, &D_80093680, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009368C, &D_80093698, &D_800936A4}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800936B0, &D_800936BC, &D_800936C8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800936D4, &D_800936E0, &D_800936EC}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_800936F8, &D_80093704, &D_80093710}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_8009371C, &D_80093728, &D_80093734}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093740, &D_8009374C, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093758, &D_80093764, &D_800920A8}, 0, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    {{&D_80093770, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}},
    {{&D_8009377C, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}},
    {{&D_80093788, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}},
    {{&D_80093794, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}},
    {{&D_800937A0, &D_800937AC, &D_800937B8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1}},
    {{&D_800937C4, &D_800937D0, &D_800937DC}, 127, 2, {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1}},
    {{&D_800937E8, &D_800937F4, &D_80093800}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1}},
    {{&D_8009380C, &D_80093818, &D_80093824}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1}},
    {{&D_80093830, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}},
    {{&D_8009383C, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}},
    {{&D_80093848, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}},
    {{&D_80093854, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}},
    {{&D_800938C0, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_800938CC, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_800938D8, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_800938E4, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}},
    {{&D_800938F0, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}},
    {{&D_800938FC, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}},
    {{&D_80093908, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}},
    {{&D_80093914, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}},
    {{&D_80093920, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}},
    {{&D_8009392C, &D_800920A8, &D_800920A8}, 0, 3, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_80093938, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_80093944, &D_80093950, &D_8009395C}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_80093968, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_80093974, &D_800920A8, &D_800920A8}, 0, 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    {{&D_80093980, &D_800920A8, &D_800920A8}, 8, 5, {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_8009398C, &D_800920A8, &D_800920A8}, 8, 5, {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_80093998, &D_800920A8, &D_800920A8}, 16, 5, {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_800939A4, &D_800920A8, &D_800920A8}, 16, 5, {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_800939B0, &D_800920A8, &D_800920A8}, 24, 5, {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_800939BC, &D_800920A8, &D_800920A8}, 24, 5, {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_800939C8, &D_800920A8, &D_800920A8}, 32, 5, {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0}},
    {{&D_800939D4, &D_800920A8, &D_800920A8}, 32, 5, {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0}},
};
#endif
s16 D_80095E84[] = {
    1, 2, 1, 0, -1, -2, -1, 0, 1000, 0,
};
#if VERSION_US
ChoiceText D_80095E98[16] = {
    {0x1120002, {0x535, 0x536}},
    {0x1120005, {0x53A, 0x53B}},
    {0x1120009, {0x53F, 0x540}},
    {0x112000D, {0x544, 0x545}},
    {0x1120011, {0x549, 0x54A}},
    {0x1120015, {0x54E, 0x54F}},
    {0x1120019, {0x553, 0x554}},
    {0x112001D, {0x558, 0x559}},
    {0x1120021, {0x55D, 0x55E}},
    {0x1120025, {0x562, 0x563}},
    {0x1120029, {0x567, 0x568}},
    {0x112002D, {0x56C, 0x56D}},
    {0x1120031, {0x571, 0x572}},
    {0x1120035, {0x576, 0x577}},
    {0x1120039, {0x57B, 0x57C}},
    {0x112003D, {0x580, 0x581}},
};
#elif VERSION_EU
ChoiceText D_80095E98[16] = {
    {0x1190002, {0x535, 0x536}},
    {0x1190005, {0x53A, 0x53B}},
    {0x1190009, {0x53F, 0x540}},
    {0x119000D, {0x544, 0x545}},
    {0x1190011, {0x549, 0x54A}},
    {0x1190015, {0x54E, 0x54F}},
    {0x1190019, {0x553, 0x554}},
    {0x119001D, {0x558, 0x559}},
    {0x1190021, {0x55D, 0x55E}},
    {0x1190025, {0x562, 0x563}},
    {0x1190029, {0x567, 0x568}},
    {0x119002D, {0x56C, 0x56D}},
    {0x1190031, {0x571, 0x572}},
    {0x1190035, {0x576, 0x577}},
    {0x1190039, {0x57B, 0x57C}},
    {0x119003D, {0x580, 0x581}},
};
#endif
ProgressEvent D_80095F18[] = {
    {5, 0x400, 0x7074, 0x533, 0x534},
    {8, 0x401, 0x7074, 0x538, 0x539},
    {12, 0x402, 0x7075, 0x53D, 0x53E},
    {14, 0x403, 0x7075, 0x542, 0x543},
    {16, 0x404, 0x7076, 0x547, 0x548},
    {22, 0x405, 0x7076, 0x54C, 0x54D},
    {24, 0x406, 0x7077, 0x551, 0x552},
    {26, 0x407, 0x7077, 0x556, 0x557},
    {28, 0x408, 0x7078, 0x55B, 0x55C},
    {30, 0x409, 0x7078, 0x560, 0x561},
    {31, 0x40A, 0x7079, 0x565, 0x566},
    {34, 0x40B, 0x7079, 0x56A, 0x56B},
    {36, 0x40C, 0x707A, 0x56F, 0x570},
    {37, 0x40D, 0x707B, 0x574, 0x575},
    {38, 0x40E, 0x707C, 0x579, 0x57A},
    {39, 0x40F, 0x707D, 0x57E, 0x57F},
    {-1, 0, 0, 0, 0},
};
AnimFrame D_80096028[] = {
    {0, 1}, {0, 13}, {1, 14}, {2, 15},
    {3, 14}, {0, 13}, {1, 14}, {2, 15},
    {3, 14}, {0, 6}, {1, 6}, {2, 6},
    {4, 7}, {5, 5}, {6, 4}, {7, 4},
    {8, 4}, {9, 4}, {-1, -1},
};
AnimFrame D_80096074[] = {
    {0, 1}, {1, 8}, {2, 6}, {3, 4},
    {4, 4}, {3, 4}, {4, 4}, {3, 6},
    {4, 4}, {3, 4}, {-1, 7},
};
AnimFrame D_800960A0[] = {
    {0, 1}, {9, 18}, {5, 4}, {6, 5},
    {7, 4}, {8, 4}, {6, 4}, {7, 4},
    {8, 4}, {-1, 5},
};
AnimFrame D_800960C8[] = {
    {0, 4}, {1, 4}, {2, 4}, {3, 4},
    {4, 4}, {5, 4}, {6, 4}, {7, 4},
    {8, 4}, {9, 4}, {10, 4}, {11, 4},
    {12, 4}, {13, 4}, {14, 4}, {15, 4},
    {16, 4}, {17, 4}, {18, 4}, {19, 4},
    {20, 4}, {21, 4}, {22, 4}, {23, 4},
    {24, 4}, {25, 4}, {26, 4}, {27, 4},
    {28, 4}, {29, 4}, {30, 4}, {31, 4},
    {0xFF, 999},
};
AnimFrame D_8009614C[] = {
    {0x12C, 28}, {32, 4}, {33, 24}, {34, 4},
    {0xFF, 999},
};
AnimFrame D_80096160[] = {
    {0x12C, 28}, {35, 4}, {36, 24}, {37, 4},
    {0xFF, 999},
};
AnimFrame D_80096174[] = {
    {0x12C, 104}, {38, 4}, {39, 4}, {40, 4},
    {41, 4}, {42, 4}, {43, 4}, {0xFF, 999},
};
AnimFrame D_80096194[] = {
    {0x12C, 104}, {44, 4}, {45, 4}, {46, 4},
    {47, 4}, {48, 4}, {49, 4}, {0xFF, 0},
};
AnimFrame D_800961B4[] = {
    {0x12C, 128}, {50, 4}, {51, 4}, {52, 4},
    {53, 4}, {54, 4}, {55, 4}, {56, 4},
    {57, 4}, {58, 4}, {59, 4}, {0xFF, 999},
};
AnimFrame *D_800961E4[][4] = {
    {D_800960C8, D_8009614C, D_80096174, D_800961B4},
    {D_800960C8, D_80096160, D_80096194, D_800961B4},
};
u8 D_80096204[] = {
    0x19, 0x0E, 0x09, 0x0A, 0x0B, 0x0F, 0x1A, 0x0C,
    0x06, 0x07, 0x08, 0x0D, 0x1B, 0x10, 0x02, 0x00,
    0x03, 0x11, 0x1C, 0x12, 0x04, 0x01, 0x05, 0x13,
    0x1D, 0x14, 0x15, 0x16, 0x17, 0x18, 0x14, 0x0C,
    0x0D, 0x0E, 0x0F, 0x15, 0x10, 0x08, 0x09, 0x0A,
    0x0B, 0x11, 0x12, 0x04, 0x00, 0x01, 0x05, 0x13,
    0x16, 0x06, 0x02, 0x03, 0x07, 0x17, 0x18, 0x19,
    0x1A, 0x1B, 0x1C, 0x1D, 0x19, 0x0C, 0x09, 0x0A,
    0x0B, 0x0D, 0x1A, 0x0E, 0x02, 0x01, 0x03, 0x0F,
    0x1B, 0x10, 0x04, 0x00, 0x05, 0x11, 0x1C, 0x12,
    0x06, 0x07, 0x08, 0x13, 0x1D, 0x14, 0x15, 0x16,
    0x17, 0x18, 0x10, 0x0C, 0x0D, 0x0E, 0x0F, 0x11,
    0x12, 0x04, 0x02, 0x03, 0x05, 0x13, 0x14, 0x06,
    0x00, 0x01, 0x07, 0x15, 0x16, 0x08, 0x09, 0x0A,
    0x0B, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x0C, 0x0A,
    0x0E, 0x10, 0x12, 0x14, 0x08, 0x06, 0x02, 0x00,
    0x04, 0x15, 0x09, 0x07, 0x03, 0x01, 0x05, 0x16,
    0x0D, 0x0B, 0x0F, 0x11, 0x13, 0x17, 0x18, 0x19,
    0x1A, 0x1B, 0x1C, 0x1D, 0x0C, 0x0A, 0x0E, 0x10,
    0x12, 0x14, 0x08, 0x04, 0x00, 0x01, 0x06, 0x15,
    0x09, 0x05, 0x02, 0x03, 0x07, 0x16, 0x0D, 0x0B,
    0x0F, 0x11, 0x13, 0x17, 0x17, 0x0F, 0x11, 0x13,
    0x15, 0x19, 0x0C, 0x09, 0x03, 0x01, 0x06, 0x1A,
    0x0D, 0x0A, 0x04, 0x00, 0x07, 0x1B, 0x0E, 0x0B,
    0x05, 0x02, 0x08, 0x1C, 0x18, 0x10, 0x12, 0x14,
    0x16, 0x1D, 0x0F, 0x11, 0x13, 0x15, 0x17, 0x19,
    0x0C, 0x04, 0x02, 0x07, 0x09, 0x1A, 0x0D, 0x05,
    0x00, 0x01, 0x0A, 0x1B, 0x0E, 0x06, 0x03, 0x08,
    0x0B, 0x1C, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1D,
    0x0C, 0x0F, 0x10, 0x11, 0x13, 0x15, 0x0D, 0x06,
    0x08, 0x0A, 0x0B, 0x17, 0x0E, 0x07, 0x02, 0x00,
    0x04, 0x19, 0x12, 0x09, 0x03, 0x01, 0x05, 0x1B,
    0x14, 0x16, 0x18, 0x1A, 0x1C, 0x1D, 0x18, 0x19,
    0x1A, 0x1B, 0x1C, 0x1D, 0x08, 0x0A, 0x0C, 0x0D,
    0x0E, 0x10, 0x09, 0x04, 0x00, 0x01, 0x06, 0x12,
    0x0B, 0x05, 0x02, 0x03, 0x07, 0x14, 0x0F, 0x11,
    0x13, 0x15, 0x16, 0x17, 0x19, 0x09, 0x0C, 0x0D,
    0x0F, 0x11, 0x1A, 0x0A, 0x03, 0x02, 0x05, 0x13,
    0x1B, 0x0B, 0x01, 0x00, 0x07, 0x15, 0x1C, 0x0E,
    0x04, 0x06, 0x08, 0x17, 0x1D, 0x10, 0x12, 0x14,
    0x16, 0x18, 0x0C, 0x0F, 0x10, 0x12, 0x13, 0x15,
    0x0D, 0x04, 0x03, 0x05, 0x08, 0x17, 0x0E, 0x02,
    0x00, 0x01, 0x0A, 0x19, 0x11, 0x06, 0x07, 0x09,
    0x0B, 0x1C, 0x14, 0x16, 0x18, 0x1A, 0x1B, 0x1D,
};
u8 D_8009636C[][2] = {
    {0x00, 0x01}, {0x02, 0x01}, {0x01, 0x00}, {0x02, 0x00},
    {0x00, 0x00}, {0x02, 0x02}, {0x01, 0x02}, {0x02, 0x03},
};
u8 D_8009637C[][4] = {
    {0x02, 0x01, 0x02, 0x01},
    {0x01, 0x01, 0x02, 0x01},
    {0x02, 0x01, 0x01, 0x01},
    {0x01, 0x01, 0x01, 0x01},
};
s32 D_8009638C[] = {
    7, 3, 11,
};
Point D_80096398[] = {
    {640, 0},
    {640, 128},
    {768, 0},
    {768, 128},
    {896, 0},
    {896, 128},
    {640, 256},
    {640, 384},
    {768, 256},
    {768, 384},
    {896, 256},
    {896, 384},
};
AreaName D_800963F8[] = {
    {11, 1, 512},
    {11, 118, 624},
    {11, 1, 513},
    {11, 118, 625},
    {11, 2, 514},
    {11, 119, 626},
    {1, 3, 515},
    {6, 3, 627},
    {1, 3, 516},
    {11, 1, 517},
    {11, 118, 628},
    {1, 4, 518},
    {6, 4, 629},
    {1, 5, 519},
    {6, 5, 630},
    {1, 6, 520},
    {6, 6, 631},
    {1, 7, 521},
    {6, 7, 632},
    {1, 8, 522},
    {6, 120, 633},
    {1, 135, 523},
    {6, 135, 634},
    {1, 9, 524},
    {6, 121, 635},
    {1, 10, 525},
    {6, 122, 636},
    {1, 11, 526},
    {6, 11, 637},
    {1, 12, 527},
    {6, 12, 638},
    {1, 13, 528},
    {6, 13, 639},
    {1, 14, 529},
    {6, 14, 640},
    {1, 15, 530},
    {6, 15, 641},
    {1, 16, 531},
    {6, 16, 642},
    {1, 17, 532},
    {6, 17, 643},
    {1, 18, 533},
    {6, 18, 644},
    {1, 19, 534},
    {6, 19, 645},
    {1, 20, 535},
    {6, 20, 646},
    {1, 21, 536},
    {6, 21, 647},
    {1, 22, 537},
    {6, 22, 648},
    {1, 23, 538},
    {6, 23, 649},
    {1, 24, 539},
    {6, 123, 650},
    {1, 25, 540},
    {6, 25, 651},
    {11, 26, 541},
    {11, 26, 652},
    {11, 27, 542},
    {11, 27, 653},
    {11, 28, 543},
    {11, 28, 654},
    {11, 29, 544},
    {11, 29, 655},
    {12, 30, 545},
    {12, 30, 656},
    {12, 31, 546},
    {12, 31, 657},
    {12, 32, 547},
    {12, 32, 658},
    {12, 33, 548},
    {12, 33, 659},
    {12, 34, 549},
    {12, 34, 660},
    {12, 35, 550},
    {12, 35, 661},
    {12, 36, 551},
    {12, 36, 662},
    {12, 37, 552},
    {12, 37, 663},
    {12, 38, 553},
    {12, 38, 664},
    {12, 39, 554},
    {12, 39, 665},
    {12, 40, 555},
    {12, 40, 666},
    {12, 41, 556},
    {12, 41, 667},
    {12, 42, 557},
    {12, 43, 558},
    {12, 124, 668},
    {2, 44, 559},
    {7, 44, 669},
    {2, 45, 560},
    {7, 125, 670},
    {2, 46, 561},
    {7, 46, 671},
    {13, 47, 562},
    {13, 47, 672},
    {13, 48, 563},
    {13, 48, 673},
    {13, 49, 564},
    {13, 49, 674},
    {13, 50, 565},
    {13, 50, 675},
    {13, 51, 566},
    {13, 52, 567},
    {13, 52, 676},
    {13, 53, 568},
    {13, 53, 677},
    {13, 54, 569},
    {13, 54, 678},
    {13, 55, 570},
    {13, 55, 679},
    {13, 56, 571},
    {13, 56, 680},
    {13, 57, 572},
    {13, 57, 681},
    {13, 58, 573},
    {13, 58, 682},
    {13, 59, 574},
    {13, 126, 683},
    {3, 60, 575},
    {8, 127, 684},
    {3, 61, 576},
    {8, 128, 685},
    {13, 62, 577},
    {13, 129, 686},
    {13, 63, 578},
    {13, 63, 687},
    {13, 64, 579},
    {13, 64, 580},
    {13, 64, 688},
    {16, 66, 581},
    {16, 67, 582},
    {14, 68, 583},
    {14, 68, 689},
    {14, 69, 584},
    {14, 69, 690},
    {14, 70, 585},
    {14, 70, 691},
    {14, 71, 586},
    {14, 71, 692},
    {14, 72, 587},
    {14, 72, 693},
    {14, 73, 588},
    {14, 73, 694},
    {14, 74, 589},
    {14, 74, 695},
    {14, 75, 590},
    {14, 75, 696},
    {14, 76, 591},
    {14, 76, 697},
    {14, 77, 592},
    {14, 77, 698},
    {14, 78, 593},
    {14, 78, 699},
    {14, 79, 594},
    {14, 79, 700},
    {14, 80, 595},
    {14, 80, 701},
    {14, 81, 596},
    {14, 81, 702},
    {14, 83, 597},
    {14, 83, 703},
    {14, 83, 598},
    {14, 84, 599},
    {14, 84, 704},
    {14, 85, 600},
    {14, 86, 705},
    {14, 86, 601},
    {14, 86, 706},
    {14, 87, 602},
    {14, 87, 707},
    {14, 88, 603},
    {14, 88, 708},
    {14, 89, 604},
    {14, 89, 709},
    {14, 90, 605},
    {14, 130, 710},
    {4, 91, 606},
    {9, 131, 711},
    {4, 92, 607},
    {4, 93, 608},
    {9, 93, 712},
    {15, 94, 609},
    {15, 94, 713},
    {15, 95, 610},
    {15, 95, 714},
    {15, 96, 611},
    {15, 96, 715},
    {15, 97, 612},
    {15, 97, 716},
    {15, 98, 613},
    {15, 98, 717},
    {15, 99, 614},
    {15, 99, 718},
    {15, 100, 615},
    {15, 100, 719},
    {15, 101, 616},
    {15, 101, 720},
    {15, 102, 617},
    {15, 102, 721},
    {15, 103, 618},
    {15, 103, 722},
    {15, 104, 619},
    {15, 104, 723},
    {15, 105, 620},
    {15, 105, 724},
    {15, 106, 621},
    {15, 107, 622},
    {15, 107, 725},
    {15, 108, 623},
    {15, 132, 726},
    {17, 109, 727},
    {17, 110, 728},
    {17, 106, 729},
    {18, 112, 730},
    {18, 113, 731},
    {18, 114, 732},
    {19, 115, 733},
    {19, 116, 734},
    {19, 117, 735},
    {21, 133, 736},
    {21, 133, 737},
    {21, 133, 738},
    {21, 133, 739},
    {21, 133, 740},
    {21, 133, 741},
    {21, 133, 742},
    {21, 133, 743},
    {21, 134, 744},
    {21, 134, 745},
    {21, 134, 746},
    {21, 134, 747},
    {21, 134, 748},
    {21, 134, 749},
    {21, 134, 750},
    {0, 0, 0},
};
Unk800870D4Box D_800967B8[10] = {
    {0, {320, 41}, {0, 1}, 0xFFE400, 1, 124, 320, 8, 0},
    {0, {0, 87}, {320, 0}, 0xFFE400, 2, 86, 88, 2, 0},
    {0, {0, 0}, {2, 240}, 0xFFE400, 1, 31, 32, 2, 0},
    {0, {0, 0}, {1, 240}, 0xFFE400, 1, 13, 14, 2, 0},
    {0, {227, 0}, {1, 0}, 0xFFE400, 2, 0, 240, 16, 0},
    {0, {320, 40}, {0, 3}, 0xC83E3E, 1, 124, 320, 8, 0},
    {0, {0, 87}, {320, 0}, 0xC83E3E, 2, 81, 93, 2, 0},
    {0, {0, 0}, {8, 240}, 0xC83E3E, 1, 27, 36, 2, 0},
    {0, {125, 16}, {116, 0}, 0x800000, 2, 16, 47, 2, 0},
    {0, {0, 87}, {320, 0}, 0x800000, 2, 66, 97, 2, 0},
};
u8 D_80096920[][9] = {
    {0x00, 0x3C, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x01, 0x0A, 0x02, 0x0A, 0xFF, 0x00, 0x00, 0x00, 0x00},
    {0x03, 0x16, 0x04, 0x16, 0xFF, 0x00, 0x00, 0x00, 0x00},
    {0x05, 0x04, 0x06, 0x05, 0x07, 0x04, 0x35, 0x3C, 0xFF},
    {0x08, 0x16, 0x09, 0x16, 0xFF, 0x00, 0x00, 0x00, 0x00},
    {0x0A, 0x16, 0x0B, 0x16, 0xFF, 0x00, 0x00, 0x00, 0x00},
    {0x10, 0x16, 0x11, 0x16, 0xFF, 0x00, 0x00, 0x00, 0x00},
    {0x0E, 0x16, 0x0F, 0x16, 0xFF, 0x00, 0x00, 0x00, 0x00},
    {0x0C, 0x16, 0x0D, 0x16, 0xFF, 0x00, 0x00, 0x00, 0x00},
    {0x12, 0x16, 0x13, 0x16, 0xFF, 0x00, 0x00, 0x00, 0x00},
    {0x45, 0x16, 0x46, 0x16, 0xFF, 0x00, 0x00, 0x00, 0x00},
};
#if VERSION_US
u8 D_80096983 = 0x8E;
#elif VERSION_EU
u8 D_80096983 = 0x03;
#endif
u8 D_80096984[][8] = {
    {0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01},
    {0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01},
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01},
};
s16 D_800969C4[] = {
    0x020A, 0x0223, 0x022F, 0x0238, 0x023F, 0x025B, 0x025D, 0x0263,
    0x026F, 0x026D, 0x0279, 0x0292, 0x029D, 0x02A5, 0x02AC, 0x02C4,
    0x02C6, 0x02CB, 0x02D6, 0x0249, 0x02B3, 0x0000,
};
u8 D_800969F0[][2] = {
    {0x23, 8}, {0x24, 8}, {0x25, 8}, {0x26, 8},
    {0xFF, 0}, {0x00, 0},
};
u8 D_800969FC[][2] = {
    {0x23, 3}, {0x27, 4}, {0x28, 4}, {0x2D, 4},
    {0x2E, 4}, {0x2F, 3}, {0x30, 2}, {0x2E, 2},
    {0x2D, 2}, {0x2E, 2}, {0x30, 2}, {0x2E, 2},
    {0x2D, 2}, {0x2E, 2}, {0x30, 2}, {0x2E, 2},
    {0x2D, 2}, {0x2E, 2}, {0x30, 2}, {0x31, 2},
    {0x2B, 2}, {0x29, 2}, {0x2A, 2}, {0xFF, 19},
};
u8 D_80096A2C[][2] = {
    {0x29, 6}, {0x2E, 3}, {0x30, 3}, {0x28, 6},
    {0x2C, 8}, {0x23, 8}, {0x24, 8}, {0x25, 8},
    {0x26, 8}, {0xFF, 5},
};
u8 D_80096A40[][2] = {
    {0x23, 3}, {0x27, 4}, {0x28, 4}, {0x2D, 4},
    {0x2E, 4}, {0x2F, 3}, {0x30, 2}, {0x2E, 2},
    {0x2D, 2}, {0x2E, 2}, {0x30, 2}, {0x2E, 2},
    {0x2D, 2}, {0x2E, 2}, {0x30, 2}, {0x2E, 2},
    {0x2D, 2}, {0x2E, 2}, {0x30, 2}, {0x2F, 2},
    {0x2E, 2}, {0x2D, 2}, {0x28, 3}, {0x23, 3},
    {0x23, 8}, {0x24, 8}, {0x25, 8}, {0x26, 8},
    {0xFF, 24}, {0x00, 0},
};
u8 (*D_80096A7C[])[2] = {
    D_800969F0, D_800969FC, D_80096A2C, D_80096A40,
};
s16 D_80096A8C[][2] = {
    {-5, -4}, {-5, -4}, {-5, -4}, {-5, -9},
    {-6, -13}, {-8, -17}, {-10, -20}, {-12, -23},
    {-13, -23}, {-14, -23}, {-15, -22}, {-16, -21},
    {-17, -20}, {-16, -22}, {-16, -22}, {0, 0},
};
s32 D_80096ACC = 0;
TileMove FIELDSTG_tileMoves[] = {
    {&FIELDSTG_tiles[4][0].x, -1, 192},
    {&FIELDSTG_tiles[3][0].x, -1, 128},
    {&FIELDSTG_tiles[2][0].x, -1, 64},
    {&FIELDSTG_tiles[1][0].x, -1, 0},
    {&FIELDSTG_tiles[0][0].y, 1, 40},
    {&FIELDSTG_tiles[0][1].y, 1, 80},
    {&FIELDSTG_tiles[0][2].y, 1, 120},
    {&FIELDSTG_tiles[0][3].y, 1, 160},
    {&FIELDSTG_tiles[0][4].y, 1, 200},
    {&FIELDSTG_tiles[0][5].x, 1, 64},
    {&FIELDSTG_tiles[1][5].x, 1, 128},
    {&FIELDSTG_tiles[2][5].x, 1, 192},
    {&FIELDSTG_tiles[3][5].x, 1, 256},
    {&FIELDSTG_tiles[4][5].y, -1, 160},
    {&FIELDSTG_tiles[4][4].y, -1, 120},
    {&FIELDSTG_tiles[4][3].y, -1, 80},
    {&FIELDSTG_tiles[4][2].y, -1, 40},
    {&FIELDSTG_tiles[4][1].x, -1, 192},
    {&FIELDSTG_tiles[3][1].x, -1, 128},
    {&FIELDSTG_tiles[2][1].x, -1, 64},
    {&FIELDSTG_tiles[1][1].y, 1, 80},
    {&FIELDSTG_tiles[1][2].y, 1, 120},
    {&FIELDSTG_tiles[1][3].y, 1, 160},
    {&FIELDSTG_tiles[1][4].x, 1, 128},
    {&FIELDSTG_tiles[2][4].x, 1, 192},
    {&FIELDSTG_tiles[3][4].y, -1, 120},
    {&FIELDSTG_tiles[3][3].y, -1, 80},
    {&FIELDSTG_tiles[3][2].x, -1, 192},
    {&FIELDSTG_tiles[2][2].y, 1, 120},
    {NULL, 0, 0},
};
#if VERSION_US
s16 D_80096C38[] = {
    1522, 1200, 1201, 8, 9, 1512, 54, 1514,
    1516, 140, 142, 1205, 1210, 1211, 1215, 1220,
    1221, 1457, 1458, 1230, 1231, 1235, 1236, 1240,
    1241, 1245, 1510, 1518, 1520, 1250, 1251, 240,
    205, 290, 67, 890, 560, 1265, 1267, 1269,
    1271, 1273, 1275, 1277, 1279, 300, 70, 60,
    1299, 1301, 1302, 1303, 1304, 1260, 1262, 950,
    1281, 1283, 1285, 1287, 1289, 1291, 320, 320,
    695, 375, 260, 690, 430, 820, 735, 1310,
    736, 750, 745, 895, 1320, 1325, 13, 14,
    1421, 1423, 1425, 1427, 1429, 1430, 1436, 1438,
    1440, 1442, 1444, 1445, 1415, 220, 510, 143,
    144, 1450, 1321, 1326, 1455, 1459, 1460, 1461,
    1462, 1463, 1464, 1431, 1446, -20560,
};
u8 D_80096D14[][2] = {
    {0x00, 0x00},
    {0x39, 0x06},
    {0x3A, 0x04},
    {0x3B, 0x04},
    {0x3C, 0x08},
    {0x3D, 0x08},
    {0x3E, 0x08},
    {0x3F, 0x0A},
    {0x40, 0x08},
    {0x38, 0x08},
    {0xFF, 0x00},
    {0x62, 0x28},
};
#elif VERSION_EU
s16 D_80096C38[] = {
    1522, 1200, 1201, 8, 9, 1512, 54, 1514,
    1516, 140, 142, 1205, 1210, 1211, 1215, 1220,
    1221, 1457, 1458, 1230, 1231, 1235, 1236, 1240,
    1241, 1245, 1510, 1518, 1520, 1250, 1251, 240,
    205, 290, 67, 890, 560, 1265, 1267, 1269,
    1271, 1273, 1275, 1277, 1279, 300, 70, 60,
    1299, 1301, 1302, 1303, 1304, 1260, 1262, 950,
    1281, 1283, 1285, 1287, 1289, 1291, 320, 320,
    695, 375, 260, 690, 430, 820, 735, 1310,
    736, 750, 745, 895, 1320, 1325, 13, 14,
    1421, 1423, 1425, 1427, 1429, 1430, 1436, 1438,
    1440, 1442, 1444, 1445, 1415, 220, 510, 143,
    144, 1450, 1321, 1326, 1455, 1459, 1460, 1461,
    1462, 1463, 1464, 1431, 1446, 1602, 1604, 1606,
    1612, 1614, 1616, 1618, 1620, 1622, 1624, 1626,
    1628, 1646, 1648, 785,
};
u8 D_80096D14[][2] = {
    {0x00, 0x00},
    {0x39, 0x06},
    {0x3A, 0x04},
    {0x3B, 0x04},
    {0x3C, 0x08},
    {0x3D, 0x08},
    {0x3E, 0x08},
    {0x3F, 0x0A},
    {0x40, 0x08},
    {0x38, 0x08},
    {0xFF, 0x00},
    {0x05, 0x00},
};
#endif
u8 D_80096D2C[] = {
    0x00, 0x08, 0x5B, 0x04, 0x5C, 0x04, 0x5D, 0x04,
    0x5E, 0x04, 0x5F, 0x04, 0xFF, 0x00, 0x00, 0x00,
};
u8 D_80096D3C[] = {
    0x00, 0x08, 0x56, 0x04, 0x57, 0x04, 0x58, 0x04,
    0x59, 0x04, 0x5A, 0x04, 0xFF, 0x00, 0x00, 0x00,
};
u8 D_80096D4C[] = {
    0x00, 0x08, 0x51, 0x04, 0x52, 0x04, 0x53, 0x04,
    0x54, 0x04, 0x55, 0x04, 0xFF, 0x00, 0x00, 0x00,
};
u8 D_80096D5C[] = {
    0x00, 0x08, 0x4C, 0x04, 0x4D, 0x04, 0x4E, 0x04,
    0x4F, 0x04, 0x50, 0x04, 0xFF, 0x00, 0x00, 0x00,
};
u8 D_80096D6C[] = {
    0x00, 0x08, 0x47, 0x04, 0x48, 0x04, 0x49, 0x04,
    0x4A, 0x04, 0x4B, 0x04, 0xFF, 0x00, 0x00, 0x00,
};
u8 D_80096D7C[] = {
    0x00, 0x08, 0x14, 0x04, 0x15, 0x04, 0x16, 0x04,
    0x17, 0x04, 0x18, 0x04, 0xFF, 0x00, 0x00, 0x00,
};
u8 D_80096D8C[] = {
    0x00, 0x08, 0x19, 0x04, 0x1A, 0x04, 0x1B, 0x04,
    0x1C, 0x04, 0x1D, 0x04, 0xFF, 0x00, 0x00, 0x00,
};
u8 D_80096D9C[] = {
    0x00, 0x08, 0x1E, 0x04, 0x1F, 0x04, 0x20, 0x04,
    0x21, 0x04, 0x22, 0x04, 0xFF, 0x00, 0x00, 0x00,
};
u8 *D_80096DAC[] = {
    D_80096D2C, D_80096D3C, D_80096D4C, D_80096D5C,
    D_80096D6C, D_80096D7C, D_80096D8C, D_80096D9C,
};
s32 D_80096DCC[] = {
    1, 1, 1, -1,
    -1, -1, 1, 1,
};
s32 D_80096DEC[] = {
    0, 0xAAAA0000, 0xAAA95,
};
s32 D_80096DF8[] = {
    0x950015AA, 0x150015AA, 0x56AA5400,
};
s32 D_80096E04[] = {
    0xAAAA56AA, 682, 0xAAA80000,
};
s32 D_80096E10[] = {
    0x2AAA80, 0xAAAAAAA8, 0x5400AAAA,
};
s32 D_80096E1C[] = {
    0xAAAAAAAA, 0xAAA95AAA, 0xAAAAAAAA,
};
s32 D_80096E28[] = {
    2730, 0xAAA80000, 0x56AAAAAA,
};
s32 D_80096E34[] = {
    0xAAAAAAAA, 0xAAAAAAAA, 0xAAA8002A,
};
s32 D_80096E40[] = {
    0, 0xAAAAA555, 0xAAAAAAAA,
};
#if VERSION_EU
s32 FIELDSTG_gaugeRow8[] = {
    0, 0, 0,
};
#endif
/* The rows of func_8008C59C's gauges, 2 bits a cell. The USA version has no
   row 8 (for GAME.unk26F8 used up) and reads past the table, a null
   pointer */
u8 *FIELDSTG_gaugeRows[] = {
    (u8 *)D_80096DEC, (u8 *)D_80096DF8, (u8 *)D_80096E04, (u8 *)D_80096E10,
    (u8 *)D_80096E1C, (u8 *)D_80096E28, (u8 *)D_80096E34, (u8 *)D_80096E40,
#if VERSION_EU
    (u8 *)FIELDSTG_gaugeRow8,
#endif
};
Point D_80096E6C[] = {
    {0, 0},
    {-1, -1},
    {-1, 1},
    {1, -1},
    {1, 1},
};
u8 D_80096E94[][5] = {
    {0x0A, 0x05, 0x04, 0x06, 0x03},
    {0x0E, 0x06, 0x05, 0x07, 0x04},
    {0x0B, 0x07, 0x06, 0x00, 0x05},
    {0x0F, 0x07, 0x00, 0x06, 0x01},
    {0x08, 0x00, 0x01, 0x07, 0x02},
    {0x0C, 0x02, 0x01, 0x03, 0x00},
    {0x09, 0x02, 0x03, 0x01, 0x04},
    {0x0D, 0x03, 0x04, 0x02, 0x05},
};
Point D_80096EBC[] = {
    {-6, -8},
    {6, -8},
    {8, -6},
    {8, 6},
    {6, 8},
    {-6, 8},
    {-8, 6},
    {-8, -6},
    {0, -8},
    {8, 0},
    {0, 8},
    {-8, 0},
    {8, -8},
    {8, 8},
    {-8, 8},
    {-8, -8},
};
u8 D_80096F3C[][2] = {
    {0x00, 0x81},
    {0x00, 0x81},
    {0x01, 0x00},
    {0x01, 0x00},
    {0x00, 0x01},
    {0x00, 0x01},
    {0x81, 0x00},
    {0x81, 0x00},
    {0x00, 0x81},
    {0x01, 0x00},
    {0x00, 0x01},
    {0x81, 0x00},
    {0x01, 0x81},
    {0x01, 0x01},
    {0x81, 0x01},
    {0x81, 0x81},
};
s32 D_80096F5C[] = {
    0, 4, 6, 5,
    0, 0, 7, 0,
    2, 3, 0, 0,
    1, 0, 0, 0,
};
s16 D_80096F9C[][2] = {
    {0x0070, 0x0020},
    {0x0071, 0x0024},
    {0x00DB, 0x0014},
    {0x00DC, 0x00CE},
    {0x00DD, 0x0029},
    {0x00DE, 0x0028},
    {0x00DF, 0x002A},
    {0x00E0, 0x0019},
    {0x00E1, 0x0033},
    {0x0100, 0x0034},
    {0x010C, 0x010B},
    {0x010E, 0x009D},
    {0x010F, 0x009E},
    {0x011C, 0x004B},
    {0x0120, 0x000C},
    {0x0000, 0x0000},
};
s32 D_80096FDC[] = {
    2, 4, 8,
};
s32 D_80096FE8[] = {
    2, 4, 8,
};
s32 D_80096FF4[] = {
    2, 4, 8,
};
Point D_80097000[] = {
    {0, 16},
    {-11, 11},
    {-16, 0},
    {-11, -11},
    {0, -16},
    {11, -11},
    {16, 0},
    {11, 11},
};
s32 D_80097040[] = {
    0x1000200, 0x1A6021C, 0xA60070, 0x1FE0230,
    0x1000200, 0x1000200, 0, 0x1FE0220,
    0x1000200, 0x1380216, 0x380058, 0x1FD0200,
    0x1000200, 0x1BC0208, 0xBC0020, 0x1FD0210,
    0x1000200, 0x1BC0210, 0xBC0040, 0x1FD0220,
    0x1000200, 0x1BC0200, 0xBC0000, 0x1FD0230,
    0x10001C0, 0x13E01E2, 0x3E0288, 0x1FE0160,
    0x10001C0, 0x13E01EA, 0x3E02A8, 0x1FE0170,
    0x10001C0, 0x13E01F2, 0x3E02C8, 0x1FD0140,
    0x10001C0, 0x14001CA, 0x400228, 0x1FD0150,
    0x10001C0, 0x15C01D2, 0x5C0248, 0x1FD0160,
    0x10001C0, 0x15C01DA, 0x5C0268, 0x1FD0170,
    0x10001C0, 0x16201C0, 0x620200, 0x1FC0140,
    0x1000180, 0x1DB01A0, 0xDB0180, 0x1FC0150,
    0, 0, 0, 0,
    0x10001C0, 0x18A01C0, 0x8A0200, 0x1FC0160,
    0x10001C0, 0x19601EA, 0x9602A8, 0x1FC0170,
    0x10001C0, 0x19801C8, 0x980220, 0x1FB0140,
    0x10001C0, 0x19901DC, 0x990270, 0x1FB0150,
    0x10001C0, 0x19C01D0, 0x9C0240, 0x1FB0160,
    0x10001C0, 0x1A601F2, 0xA602C8, 0x1FB0170,
    0x10001C0, 0x1AA01C0, 0xAA0200, 0x1FA0140,
};
s32 D_800971A0[] = {
    7229, 65535,
};
s32 D_800971A8[] = {
    0x1904C, 0x11C3D, 65535,
};
s32 D_800971B4[] = {
    0x11C3D, 65535,
};
s32 D_800971BC[] = {
    0x1904D, 7229, 65535,
};
s32 D_800971C8[] = {
    7229, 65535,
};
s32 D_800971D0[] = {
    0x1904C, 0x11C3D, 65535,
};
s32 D_800971DC[] = {
    0x11C3D, 65535,
};
s32 D_800971E4[] = {
    0x1904D, 7229, 65535,
};
s32 D_800971F0[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097208[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097220[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097238[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097250[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097268[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097280[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097298[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_800972B0[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_800972C8[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_800972E0[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_800972F8[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097310[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097328[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097340[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097358[] = {
    0, 0, 29, 0,
    0, 0,
};
s32 D_80097370[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_80097388[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_800973A0[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_800973B8[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_800973D0[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_800973E8[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_80097400[] = {
    0, 0, 1037, 0,
    0, 0,
};
s32 D_80097418[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_80097430[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_80097448[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_80097460[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_80097478[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_80097490[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_800974A8[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_800974C0[] = {
    0, 0, 1156, 0,
    0, 0,
};
s32 D_800974D8[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_800974F0[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_80097508[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_80097520[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_80097538[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_80097550[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_80097568[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_80097580[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_80097598[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_800975B0[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_800975C8[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_800975E0[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_800975F8[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_80097610[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_80097628[] = {
    0, 0, 1155, 0,
    0, 0,
};
s32 D_80097640[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_80097658[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_80097670[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_80097688[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_800976A0[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_800976B8[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_800976D0[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_800976E8[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_80097700[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_80097718[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_80097730[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_80097748[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_80097760[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_80097778[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_80097790[] = {
    0, 0, 1151, 0,
    0, 0,
};
s32 D_800977A8[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_800977C0[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_800977D8[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_800977F0[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_80097808[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_80097820[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_80097838[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_80097850[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_80097868[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_80097880[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_80097898[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_800978B0[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_800978C8[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_800978E0[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_800978F8[] = {
    0, 0, 1154, 0,
    0, 0,
};
s32 D_80097910[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097928[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097940[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097958[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097970[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097988[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_800979A0[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_800979B8[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_800979D0[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_800979E8[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097A00[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097A18[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097A30[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097A48[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097A60[] = {
    0, 0, 1153, 0,
    0, 0,
};
s32 D_80097A78[] = {
    (s32)D_800971A0, (s32)D_800971A8, 97, (s32)D_800971B4,
    (s32)D_800971BC, 98, 0, 0,
    0,
};
s32 D_80097A9C[] = {
    (s32)D_800971C8, (s32)D_800971D0, 97, (s32)D_800971DC,
    (s32)D_800971E4, 98, 0, 0,
    0,
};
s32 D_80097AC0[] = {
    0, 0, 192, 0,
    0, 0,
};
s32 D_80097AD8[] = {
    0, 0, 193, 0,
    0, 0,
};
s32 D_80097AF0[] = {
    0, 0, 194, 0,
    0, 0,
};
s32 D_80097B08[] = {
    0, 0, 195, 0,
    0, 0,
};
s32 D_80097B20[] = {
    0, 0, 196, 0,
    0, 0,
};
s32 D_80097B38[] = {
    0, 0, 197, 0,
    0, 0,
};
s32 D_80097B50[] = {
    0x16008, 65535,
};
s32 D_80097B58[] = {
    0x1600E, 65535,
};
s32 D_80097B60[] = {
    0x16016, 65535,
};
s32 D_80097B68[] = {
    0x1601A, 65535,
};
s32 D_80097B70[] = {
    0x1601E, 65535,
};
s32 D_80097B78[] = {
    0x16022, 65535,
};
s32 D_80097B80[] = {
    0x16025, 65535,
};
s32 D_80097B88[] = {
    0x16005, 65535,
};
s32 D_80097B90[] = {
    0x1600C, 65535,
};
s32 D_80097B98[] = {
    0x16010, 65535,
};
s32 D_80097BA0[] = {
    0x16018, 65535,
};
s32 D_80097BA8[] = {
    0x1601C, 65535,
};
s32 D_80097BB0[] = {
    0x1601F, 65535,
};
s32 D_80097BB8[] = {
    0x16024, 65535,
};
s32 D_80097BC0[] = {
    0x16026, 65535,
};
s32 D_80097BC8[] = {
    0x16008, 65535,
};
s32 D_80097BD0[] = {
    0x1600C, 65535,
};
s32 D_80097BD8[] = {
    0x1600E, 65535,
};
s32 D_80097BE0[] = {
    0x16010, 65535,
};
s32 D_80097BE8[] = {
    0x16016, 65535,
};
s32 D_80097BF0[] = {
    0x16018, 65535,
};
s32 D_80097BF8[] = {
    0x1601A, 65535,
};
s32 D_80097C00[] = {
    0x1601C, 65535,
};
s32 D_80097C08[] = {
    0x1601E, 65535,
};
s32 D_80097C10[] = {
    0x1601F, 65535,
};
s32 D_80097C18[] = {
    0x16022, 65535,
};
s32 D_80097C20[] = {
    0x16024, 65535,
};
s32 D_80097C28[] = {
    0x16025, 65535,
};
s32 D_80097C30[] = {
    0x16026, 65535,
};
s32 D_80097C38[] = {
    0x16005, 65535,
};
s32 D_80097C40[] = {
    0x16009, 65535,
};
s32 D_80097C48[] = {
    0x1600C, 65535,
};
s32 D_80097C50[] = {
    0x16008, 65535,
};
s32 D_80097C58[] = {
    0x1600E, 65535,
};
s32 D_80097C60[] = {
    0x16010, 65535,
};
s32 D_80097C68[] = {
    0x16016, 65535,
};
s32 D_80097C70[] = {
    0x16018, 65535,
};
s32 D_80097C78[] = {
    0x1601A, 65535,
};
s32 D_80097C80[] = {
    0x1601C, 65535,
};
s32 D_80097C88[] = {
    0x1601E, 65535,
};
s32 D_80097C90[] = {
    0x1601F, 65535,
};
s32 D_80097C98[] = {
    0x16022, 65535,
};
s32 D_80097CA0[] = {
    0x16024, 65535,
};
s32 D_80097CA8[] = {
    0x16025, 65535,
};
s32 D_80097CB0[] = {
    0x16005, 65535,
};
s32 D_80097CB8[] = {
    0x16026, 65535,
};
s32 D_80097CC0[] = {
    0x16005, 65535,
};
s32 D_80097CC8[] = {
    0x16008, 65535,
};
s32 D_80097CD0[] = {
    0x1600C, 65535,
};
s32 D_80097CD8[] = {
    0x1600E, 65535,
};
s32 D_80097CE0[] = {
    0x16010, 65535,
};
s32 D_80097CE8[] = {
    0x16016, 65535,
};
s32 D_80097CF0[] = {
    0x16018, 65535,
};
s32 D_80097CF8[] = {
    0x1601A, 65535,
};
s32 D_80097D00[] = {
    0x1601C, 65535,
};
s32 D_80097D08[] = {
    0x1601E, 65535,
};
s32 D_80097D10[] = {
    0x1601F, 65535,
};
s32 D_80097D18[] = {
    0x16022, 65535,
};
s32 D_80097D20[] = {
    0x16024, 65535,
};
s32 D_80097D28[] = {
    0x16025, 65535,
};
s32 D_80097D30[] = {
    0x16026, 65535,
};
s32 D_80097D38[] = {
    0x1600C, 65535,
};
s32 D_80097D40[] = {
    0x16010, 65535,
};
s32 D_80097D48[] = {
    0x16018, 65535,
};
s32 D_80097D50[] = {
    0x1601C, 65535,
};
s32 D_80097D58[] = {
    0x1601F, 65535,
};
s32 D_80097D60[] = {
    0x16024, 65535,
};
s32 D_80097D68[] = {
    0x16026, 65535,
};
s32 D_80097D70[] = {
    0x16005, 65535,
};
s32 D_80097D78[] = {
    0x16008, 65535,
};
s32 D_80097D80[] = {
    0x1600E, 65535,
};
s32 D_80097D88[] = {
    0x16016, 65535,
};
s32 D_80097D90[] = {
    0x1601A, 65535,
};
s32 D_80097D98[] = {
    0x1601E, 65535,
};
s32 D_80097DA0[] = {
    0x16022, 65535,
};
s32 D_80097DA8[] = {
    0x16025, 65535,
};
s32 D_80097DB0[] = {
    0x16005, 65535,
};
s32 D_80097DB8[] = {
    0x1600C, 65535,
};
s32 D_80097DC0[] = {
    0x16008, 65535,
};
s32 D_80097DC8[] = {
    0x1600E, 65535,
};
s32 D_80097DD0[] = {
    0x16010, 65535,
};
s32 D_80097DD8[] = {
    0x16016, 65535,
};
s32 D_80097DE0[] = {
    0x16018, 65535,
};
s32 D_80097DE8[] = {
    0x1601A, 65535,
};
s32 D_80097DF0[] = {
    0x1601C, 65535,
};
s32 D_80097DF8[] = {
    0x1601E, 65535,
};
s32 D_80097E00[] = {
    0x1601F, 65535,
};
s32 D_80097E08[] = {
    0x16022, 65535,
};
s32 D_80097E10[] = {
    0x16024, 65535,
};
s32 D_80097E18[] = {
    0x16025, 65535,
};
s32 D_80097E20[] = {
    0x16026, 65535,
};
s32 D_80097E28[] = {
    0x16005, 65535,
};
s32 D_80097E30[] = {
    0x1600C, 65535,
};
s32 D_80097E38[] = {
    0x16010, 65535,
};
s32 D_80097E40[] = {
    0x16018, 65535,
};
s32 D_80097E48[] = {
    0x1601A, 65535,
};
s32 D_80097E50[] = {
    0x1601C, 65535,
};
s32 D_80097E58[] = {
    0x1601E, 65535,
};
s32 D_80097E60[] = {
    0x1601F, 65535,
};
s32 D_80097E68[] = {
    0x16022, 65535,
};
s32 D_80097E70[] = {
    0x16024, 65535,
};
s32 D_80097E78[] = {
    0x16025, 65535,
};
s32 D_80097E80[] = {
    0x16026, 65535,
};
s32 D_80097E88[] = {
    0x16008, 65535,
};
s32 D_80097E90[] = {
    0x1600E, 65535,
};
s32 D_80097E98[] = {
    0x16016, 65535,
};
s32 D_80097EA0[] = {
    0x17009, 24581, 24584, 24588,
    24590, 24592, 24598, 24600,
    24602, 24604, 24606, 24607,
    24610, 24612, 24613, 24614,
    24615, 7229, 65535,
};
s32 D_80097EEC[] = {
    0x11C3D, 65535,
};
s32 D_80097EF4[] = {
    0x16027, 65535,
};
s32 D_80097EFC[] = {
    0x16027, 65535,
};
s32 D_80097F04[] = {
    0x16027, 65535,
};
s32 D_80097F0C[] = {
    0x16027, 65535,
};
s32 D_80097F14[] = {
    0x16027, 65535,
};
s32 D_80097F1C[] = {
    0x16027, 65535,
};
s32 D_80097F24[] = {
    0x16027, 65535,
};
s32 D_80097F2C[] = {
    (s32)D_80097B50, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80097F40[] = {
    (s32)D_80097B58, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80097F54[] = {
    (s32)D_80097B60, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80097F68[] = {
    (s32)D_80097B68, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80097F7C[] = {
    (s32)D_80097B70, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80097F90[] = {
    (s32)D_80097B78, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80097FA4[] = {
    (s32)D_80097B80, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80097FB8[] = {
    (s32)D_80097B88, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80097FCC[] = {
    (s32)D_80097B90, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80097FE0[] = {
    (s32)D_80097B98, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80097FF4[] = {
    (s32)D_80097BA0, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80098008[] = {
    (s32)D_80097BA8, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_8009801C[] = {
    (s32)D_80097BB0, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80098030[] = {
    (s32)D_80097BB8, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80098044[] = {
    (s32)D_80097BC0, 0, 0x4001E, 0x1490150,
    1,
};
s32 D_80098058[] = {
    (s32)D_80097BC8, (s32)D_800971F0, 0x50032, 0x19200C0,
    5,
};
s32 D_8009806C[] = {
    (s32)D_80097BD0, (s32)D_80097208, 0x50032, 0x19200C0,
    5,
};
s32 D_80098080[] = {
    (s32)D_80097BD8, (s32)D_80097220, 0x50032, 0x19200C0,
    5,
};
s32 D_80098094[] = {
    (s32)D_80097BE0, (s32)D_80097238, 0x50032, 0x19200C0,
    5,
};
s32 D_800980A8[] = {
    (s32)D_80097BE8, (s32)D_80097250, 0x50032, 0x19200C0,
    5,
};
s32 D_800980BC[] = {
    (s32)D_80097BF0, (s32)D_80097268, 0x50032, 0x19200C0,
    5,
};
s32 D_800980D0[] = {
    (s32)D_80097BF8, (s32)D_80097280, 0x50032, 0x19200C0,
    5,
};
s32 D_800980E4[] = {
    (s32)D_80097C00, (s32)D_80097298, 0x50032, 0x19200C0,
    5,
};
s32 D_800980F8[] = {
    (s32)D_80097C08, (s32)D_800972B0, 0x50032, 0x19200C0,
    5,
};
s32 D_8009810C[] = {
    (s32)D_80097C10, (s32)D_800972C8, 0x50032, 0x19200C0,
    5,
};
s32 D_80098120[] = {
    (s32)D_80097C18, (s32)D_800972E0, 0x50032, 0x19200C0,
    5,
};
s32 D_80098134[] = {
    (s32)D_80097C20, (s32)D_800972F8, 0x50032, 0x19200C0,
    5,
};
s32 D_80098148[] = {
    (s32)D_80097C28, (s32)D_80097310, 0x50032, 0x19200C0,
    5,
};
s32 D_8009815C[] = {
    (s32)D_80097C30, (s32)D_80097328, 0x50032, 0x19200C0,
    5,
};
s32 D_80098170[] = {
    (s32)D_80097C38, (s32)D_80097340, 0x50032, 0x19200C0,
    5,
};
s32 D_80098184[] = {
    (s32)D_80097C40, (s32)D_80097358, 0x60033, 0x8B00F2,
    1,
};
s32 D_80098198[] = {
    (s32)D_80097C48, (s32)D_80097370, 0x70034, 0x178012F,
    5,
};
s32 D_800981AC[] = {
    (s32)D_80097C50, (s32)D_80097388, 0x70034, 0x178012F,
    5,
};
s32 D_800981C0[] = {
    (s32)D_80097C58, (s32)D_800973A0, 0x70034, 0x178012F,
    5,
};
s32 D_800981D4[] = {
    (s32)D_80097C60, (s32)D_800973B8, 0x70034, 0x178012F,
    5,
};
s32 D_800981E8[] = {
    (s32)D_80097C68, (s32)D_800973D0, 0x70034, 0x178012F,
    5,
};
s32 D_800981FC[] = {
    (s32)D_80097C70, (s32)D_800973E8, 0x70034, 0x178012F,
    5,
};
s32 D_80098210[] = {
    (s32)D_80097C78, (s32)D_80097400, 0x70034, 0x178012F,
    5,
};
s32 D_80098224[] = {
    (s32)D_80097C80, (s32)D_80097418, 0x70034, 0x178012F,
    5,
};
s32 D_80098238[] = {
    (s32)D_80097C88, (s32)D_80097430, 0x70034, 0x178012F,
    5,
};
s32 D_8009824C[] = {
    (s32)D_80097C90, (s32)D_80097448, 0x70034, 0x178012F,
    5,
};
s32 D_80098260[] = {
    (s32)D_80097C98, (s32)D_80097460, 0x70034, 0x178012F,
    5,
};
s32 D_80098274[] = {
    (s32)D_80097CA0, (s32)D_80097478, 0x70034, 0x178012F,
    5,
};
s32 D_80098288[] = {
    (s32)D_80097CA8, (s32)D_80097490, 0x70034, 0x178012F,
    5,
};
s32 D_8009829C[] = {
    (s32)D_80097CB0, (s32)D_800974A8, 0x70034, 0x178012F,
    5,
};
s32 D_800982B0[] = {
    (s32)D_80097CB8, (s32)D_800974C0, 0x70034, 0x178012F,
    5,
};
s32 D_800982C4[] = {
    (s32)D_80097CC0, (s32)D_800974D8, 0x80035, 0x17000E0,
    5,
};
s32 D_800982D8[] = {
    (s32)D_80097CC8, (s32)D_800974F0, 0x80035, 0x17000E0,
    5,
};
s32 D_800982EC[] = {
    (s32)D_80097CD0, (s32)D_80097508, 0x80035, 0x17000E0,
    5,
};
s32 D_80098300[] = {
    (s32)D_80097CD8, (s32)D_80097520, 0x80035, 0x17000E0,
    5,
};
s32 D_80098314[] = {
    (s32)D_80097CE0, (s32)D_80097538, 0x80035, 0x17000E0,
    5,
};
s32 D_80098328[] = {
    (s32)D_80097CE8, (s32)D_80097550, 0x80035, 0x17000E0,
    5,
};
s32 D_8009833C[] = {
    (s32)D_80097CF0, (s32)D_80097568, 0x80035, 0x17000E0,
    5,
};
s32 D_80098350[] = {
    (s32)D_80097CF8, (s32)D_80097580, 0x80035, 0x17000E0,
    5,
};
s32 D_80098364[] = {
    (s32)D_80097D00, (s32)D_80097598, 0x80035, 0x17000E0,
    5,
};
s32 D_80098378[] = {
    (s32)D_80097D08, (s32)D_800975B0, 0x80035, 0x17000E0,
    5,
};
s32 D_8009838C[] = {
    (s32)D_80097D10, (s32)D_800975C8, 0x80035, 0x17000E0,
    5,
};
s32 D_800983A0[] = {
    (s32)D_80097D18, (s32)D_800975E0, 0x80035, 0x17000E0,
    5,
};
s32 D_800983B4[] = {
    (s32)D_80097D20, (s32)D_800975F8, 0x80035, 0x17000E0,
    5,
};
s32 D_800983C8[] = {
    (s32)D_80097D28, (s32)D_80097610, 0x80035, 0x17000E0,
    5,
};
s32 D_800983DC[] = {
    (s32)D_80097D30, (s32)D_80097628, 0x80035, 0x17000E0,
    5,
};
s32 D_800983F0[] = {
    (s32)D_80097D38, (s32)D_80097640, 0x90036, 0x1800100,
    5,
};
s32 D_80098404[] = {
    (s32)D_80097D40, (s32)D_80097658, 0x90036, 0x1800100,
    5,
};
s32 D_80098418[] = {
    (s32)D_80097D48, (s32)D_80097670, 0x90036, 0x1800100,
    5,
};
s32 D_8009842C[] = {
    (s32)D_80097D50, (s32)D_80097688, 0x90036, 0x1800100,
    5,
};
s32 D_80098440[] = {
    (s32)D_80097D58, (s32)D_800976A0, 0x90036, 0x1800100,
    5,
};
s32 D_80098454[] = {
    (s32)D_80097D60, (s32)D_800976B8, 0x90036, 0x1800100,
    5,
};
s32 D_80098468[] = {
    (s32)D_80097D68, (s32)D_800976D0, 0x90036, 0x1800100,
    5,
};
s32 D_8009847C[] = {
    (s32)D_80097D70, (s32)D_800976E8, 0x90036, 0x1800100,
    5,
};
s32 D_80098490[] = {
    (s32)D_80097D78, (s32)D_80097700, 0x90036, 0x1800100,
    5,
};
s32 D_800984A4[] = {
    (s32)D_80097D80, (s32)D_80097718, 0x90036, 0x1800100,
    5,
};
s32 D_800984B8[] = {
    (s32)D_80097D88, (s32)D_80097730, 0x90036, 0x1800100,
    5,
};
s32 D_800984CC[] = {
    (s32)D_80097D90, (s32)D_80097748, 0x90036, 0x1800100,
    5,
};
s32 D_800984E0[] = {
    (s32)D_80097D98, (s32)D_80097760, 0x90036, 0x1800100,
    5,
};
s32 D_800984F4[] = {
    (s32)D_80097DA0, (s32)D_80097778, 0x90036, 0x1800100,
    5,
};
s32 D_80098508[] = {
    (s32)D_80097DA8, (s32)D_80097790, 0x90036, 0x1800100,
    5,
};
s32 D_8009851C[] = {
    (s32)D_80097DB0, (s32)D_800977A8, 0xA0037, 0x1680110,
    5,
};
s32 D_80098530[] = {
    (s32)D_80097DB8, (s32)D_800977C0, 0xA0037, 0x1680110,
    5,
};
s32 D_80098544[] = {
    (s32)D_80097DC0, (s32)D_800977D8, 0xA0037, 0x1680110,
    5,
};
s32 D_80098558[] = {
    (s32)D_80097DC8, (s32)D_800977F0, 0xA0037, 0x1680110,
    5,
};
s32 D_8009856C[] = {
    (s32)D_80097DD0, (s32)D_80097808, 0xA0037, 0x1680110,
    5,
};
s32 D_80098580[] = {
    (s32)D_80097DD8, (s32)D_80097820, 0xA0037, 0x1680110,
    5,
};
s32 D_80098594[] = {
    (s32)D_80097DE0, (s32)D_80097838, 0xA0037, 0x1680110,
    5,
};
s32 D_800985A8[] = {
    (s32)D_80097DE8, (s32)D_80097850, 0xA0037, 0x1680110,
    5,
};
s32 D_800985BC[] = {
    (s32)D_80097DF0, (s32)D_80097868, 0xA0037, 0x1680110,
    5,
};
s32 D_800985D0[] = {
    (s32)D_80097DF8, (s32)D_80097880, 0xA0037, 0x1680110,
    5,
};
s32 D_800985E4[] = {
    (s32)D_80097E00, (s32)D_80097898, 0xA0037, 0x1680110,
    5,
};
s32 D_800985F8[] = {
    (s32)D_80097E08, (s32)D_800978B0, 0xA0037, 0x1680110,
    5,
};
s32 D_8009860C[] = {
    (s32)D_80097E10, (s32)D_800978C8, 0xA0037, 0x1680110,
    5,
};
s32 D_80098620[] = {
    (s32)D_80097E18, (s32)D_800978E0, 0xA0037, 0x1680110,
    5,
};
s32 D_80098634[] = {
    (s32)D_80097E20, (s32)D_800978F8, 0xA0037, 0x1680110,
    5,
};
s32 D_80098648[] = {
    (s32)D_80097E28, (s32)D_80097910, 0xB0039, 0x198012F,
    5,
};
s32 D_8009865C[] = {
    (s32)D_80097E30, (s32)D_80097928, 0xB0039, 0x198012F,
    5,
};
s32 D_80098670[] = {
    (s32)D_80097E38, (s32)D_80097940, 0xB0039, 0x198012F,
    5,
};
s32 D_80098684[] = {
    (s32)D_80097E40, (s32)D_80097958, 0xB0039, 0x198012F,
    5,
};
s32 D_80098698[] = {
    (s32)D_80097E48, (s32)D_80097970, 0xB0039, 0x198012F,
    5,
};
s32 D_800986AC[] = {
    (s32)D_80097E50, (s32)D_80097988, 0xB0039, 0x198012F,
    5,
};
s32 D_800986C0[] = {
    (s32)D_80097E58, (s32)D_800979A0, 0xB0039, 0x198012F,
    5,
};
s32 D_800986D4[] = {
    (s32)D_80097E60, (s32)D_800979B8, 0xB0039, 0x198012F,
    5,
};
s32 D_800986E8[] = {
    (s32)D_80097E68, (s32)D_800979D0, 0xB0039, 0x198012F,
    5,
};
s32 D_800986FC[] = {
    (s32)D_80097E70, (s32)D_800979E8, 0xB0039, 0x198012F,
    5,
};
s32 D_80098710[] = {
    (s32)D_80097E78, (s32)D_80097A00, 0xB0039, 0x198012F,
    5,
};
s32 D_80098724[] = {
    (s32)D_80097E80, (s32)D_80097A18, 0xB0039, 0x198012F,
    5,
};
s32 D_80098738[] = {
    (s32)D_80097E88, (s32)D_80097A30, 0xB0039, 0x198012F,
    5,
};
s32 D_8009874C[] = {
    (s32)D_80097E90, (s32)D_80097A48, 0xB0039, 0x198012F,
    5,
};
s32 D_80098760[] = {
    (s32)D_80097E98, (s32)D_80097A60, 0xB0039, 0x198012F,
    5,
};
s32 D_80098774[] = {
    (s32)D_80097EA0, (s32)D_80097A78, 0xC003F, 0x18800B0,
    1,
};
s32 D_80098788[] = {
    (s32)D_80097EEC, (s32)D_80097A9C, 0xC003F, 0x10900B0,
    1,
};
s32 D_8009879C[] = {
    (s32)D_80097EF4, (s32)D_80097AC0, 0xD009D, 0x1800100,
    5,
};
s32 D_800987B0[] = {
    (s32)D_80097EFC, 0, 0xE009E, 0x1490150,
    1,
};
s32 D_800987C4[] = {
    (s32)D_80097F04, (s32)D_80097AD8, 0xF009F, 0x198012F,
    5,
};
s32 D_800987D8[] = {
    (s32)D_80097F0C, (s32)D_80097AF0, 0x1000A0, 0x1680110,
    5,
};
s32 D_800987EC[] = {
    (s32)D_80097F14, (s32)D_80097B08, 0x1100A1, 0x17000E0,
    5,
};
s32 D_80098800[] = {
    (s32)D_80097F1C, (s32)D_80097B20, 0x1200A2, 0x178012F,
    5,
};
s32 D_80098814[] = {
    (s32)D_80097F24, (s32)D_80097B38, 0x1300AE, 0x19200C0,
    5,
};
s32 D_80098828[] = {
    (s32)D_80097F2C, (s32)D_80097F40, (s32)D_80097F54, (s32)D_80097F68,
    (s32)D_80097F7C, (s32)D_80097F90, (s32)D_80097FA4, (s32)D_80097FB8,
    (s32)D_80097FCC, (s32)D_80097FE0, (s32)D_80097FF4, (s32)D_80098008,
    (s32)D_8009801C, (s32)D_80098030, (s32)D_80098044, (s32)D_80098058,
    (s32)D_8009806C, (s32)D_80098080, (s32)D_80098094, (s32)D_800980A8,
    (s32)D_800980BC, (s32)D_800980D0, (s32)D_800980E4, (s32)D_800980F8,
    (s32)D_8009810C, (s32)D_80098120, (s32)D_80098134, (s32)D_80098148,
    (s32)D_8009815C, (s32)D_80098170, (s32)D_80098184, (s32)D_80098198,
    (s32)D_800981AC, (s32)D_800981C0, (s32)D_800981D4, (s32)D_800981E8,
    (s32)D_800981FC, (s32)D_80098210, (s32)D_80098224, (s32)D_80098238,
    (s32)D_8009824C, (s32)D_80098260, (s32)D_80098274, (s32)D_80098288,
    (s32)D_8009829C, (s32)D_800982B0, (s32)D_800982C4, (s32)D_800982D8,
    (s32)D_800982EC, (s32)D_80098300, (s32)D_80098314, (s32)D_80098328,
    (s32)D_8009833C, (s32)D_80098350, (s32)D_80098364, (s32)D_80098378,
    (s32)D_8009838C, (s32)D_800983A0, (s32)D_800983B4, (s32)D_800983C8,
    (s32)D_800983DC, (s32)D_800983F0, (s32)D_80098404, (s32)D_80098418,
    (s32)D_8009842C, (s32)D_80098440, (s32)D_80098454, (s32)D_80098468,
    (s32)D_8009847C, (s32)D_80098490, (s32)D_800984A4, (s32)D_800984B8,
    (s32)D_800984CC, (s32)D_800984E0, (s32)D_800984F4, (s32)D_80098508,
    (s32)D_8009851C, (s32)D_80098530, (s32)D_80098544, (s32)D_80098558,
    (s32)D_8009856C, (s32)D_80098580, (s32)D_80098594, (s32)D_800985A8,
    (s32)D_800985BC, (s32)D_800985D0, (s32)D_800985E4, (s32)D_800985F8,
    (s32)D_8009860C, (s32)D_80098620, (s32)D_80098634, (s32)D_80098648,
    (s32)D_8009865C, (s32)D_80098670, (s32)D_80098684, (s32)D_80098698,
    (s32)D_800986AC, (s32)D_800986C0, (s32)D_800986D4, (s32)D_800986E8,
    (s32)D_800986FC, (s32)D_80098710, (s32)D_80098724, (s32)D_80098738,
    (s32)D_8009874C, (s32)D_80098760, (s32)D_80098774, (s32)D_80098788,
    (s32)D_8009879C, (s32)D_800987B0, (s32)D_800987C4, (s32)D_800987D8,
    (s32)D_800987EC, (s32)D_80098800, (s32)D_80098814, 0,
};
s32 D_800989F8[] = {
    0x2440101, 0x1000252, 0x1380004, 282,
    0x2010000, 0x14A0240, 0x4514A, 0x1660087,
    0, 0x6400001, 0x433E013E, 0x1650004,
    161, 0x10000, 0x10640, 0,
    0x1A100C0, 0, 0x6400001, 0x7020102,
    0x1650004, 161, 0x3010000, 1741,
    0, 0x15200A0, 0, 0xA400001,
    0x49440144, 0x1650004, 241, 0x10000,
    0x1080A40, 0x40D08, 0xF10165, 0,
    0xA400001, 0x130F010F, 0x3E0004, 326,
    0x10000, 0x140A48, 0, 0xCA0080,
    0, 0xA490001, 21, 0xC80000,
    183, 0x10000, 0x1320440, 0x43732,
    0xA10165, 200, 0x8400001, 0x3D380138,
    0x1650004, 0x11800F1, 0, 0,
    0, 0, 0,
};
s32 D_80098AF4[] = {
    65535, 65535, 0x2010001, 0xF40368,
    1, 0, 65535, 65535,
    0x2120001, 0xA502FE, 1, 0,
    65535, 65535, 0x10006, 0,
    0, 0, 65535, 65535,
    0x80005, 0, 0, 0,
    65535, 65535, 0, 0,
    0, 0,
};
void (*FIELDSTG_initFuncs[])(void) = {func_80091124};
void (*D_80098B70)(Tween *tween, s32 in) = func_80091298;
s32 (*D_80098B74)(Tween *tween) = func_8009132C;
#if VERSION_US
s32 D_80098B78[] = {
    1320, 0x800A4CA4, 0x1120040, 0,
    0, 1325, 0x800A4D88, 0x1120041,
    0, 0, 1331, 0x800A4E6C,
    0x1120000, 0, 0, 1332,
    0, 0, (s32)func_80083F8C, 0,
    1333, 0x800A4FE8, 0x1120001, 0,
    (s32)func_80090864, 1334, 0x800A5180, 0x1120003,
    0, (s32)func_800908C4, 1336, 0x800A5264,
    0x1120004, 0, 0, 1337,
    0, 0, (s32)func_80083FBC, 0,
    1338, 0x800A53E0, 0x1120006, 0,
    (s32)func_800908F0, 1339, 0x800A5578, 0x1120007,
    0, (s32)func_80090950, 1341, 0x800A565C,
    0x1120008, 0, 0, 1342,
    0, 0, (s32)func_80083FF0, 0,
    1343, 0x800A57D8, 0x112000A, 0,
    (s32)func_8009097C, 1344, 0x800A5970, 0x112000B,
    0, (s32)func_800909DC, 1346, 0x800A5A54,
    0x112000C, 0, 0, 1347,
    0, 0, (s32)func_80084024, 0,
    1348, 0x800A5BD0, 0x112000E, 0,
    (s32)func_80090A08, 1349, 0x800A5D68, 0x112000F,
    0, (s32)func_80090A68, 1351, 0x800A5E4C,
    0x1120010, 0, 0, 1352,
    0, 0, (s32)func_80084058, 0,
    1353, 0x800A5FC8, 0x1120012, 0,
    (s32)func_80090A94, 1354, 0x800A6160, 0x1120013,
    0, (s32)func_80090AF4, 1356, 0x800A624C,
    0x1120014, 0, 0, 1357,
    0, 0, (s32)func_8008408C, 0,
    1358, 0x800A63C8, 0x1120016, 0,
    (s32)func_80090B20, 1359, 0x800A6560, 0x1120017,
    0, (s32)func_80090B80, 1361, 0x800A6644,
    0x1120018, 0, 0, 1362,
    0, 0, (s32)func_800840C0, 0,
    1363, 0x800A67C0, 0x112001A, 0,
    (s32)func_80090BAC, 1364, 0x800A6960, 0x112001B,
    0, (s32)func_80090C0C, 1366, 0x800A6A44,
    0x112001C, 0, 0, 1367,
    0, 0, (s32)func_800840F4, 0,
    1368, 0x800A6BC0, 0x112001E, 0,
    (s32)func_80090C38, 1369, 0x800A6D58, 0x112001F,
    0, (s32)func_80090C98, 1371, 0x800A6E3C,
    0x1120020, 0, 0, 1372,
    0, 0, (s32)func_80084128, 0,
    1373, 0x800A6FB8, 0x1120022, 0,
    (s32)func_80090CC4, 1374, 0x800A7150, 0x1120023,
    0, (s32)func_80090D24, 1376, 0x800A7234,
    0x1120024, 0, 0, 1377,
    0, 0, (s32)func_8008415C, 0,
    1378, 0x800A73B0, 0x1120026, 0,
    (s32)func_80090D50, 1379, 0x800A7548, 0x1120027,
    0, (s32)func_80090DB0, 1381, 0x800A762C,
    0x1120028, 0, 0, 1382,
    0, 0, (s32)func_80084190, 0,
    1383, 0x800A77A8, 0x112002A, 0,
    (s32)func_80090DDC, 1384, 0x800A7940, 0x112002B,
    0, (s32)func_80090E3C, 1386, 0x800A7A24,
    0x112002C, 0, 0, 1387,
    0, 0, (s32)func_800841C4, 0,
    1388, 0x800A7BA0, 0x112002E, 0,
    (s32)func_80090E68, 1389, 0x800A7D4C, 0x112002F,
    0, (s32)func_80090EC8, 1391, 0x800A7E30,
    0x1120030, 0, 0, 1392,
    0, 0, (s32)func_800841F8, 0,
    1393, 0x800A7FAC, 0x1120032, 0,
    (s32)func_80090EF4, 1394, 0x800A8134, 0x1120033,
    0, (s32)func_80090F54, 1396, 0x800A8218,
    0x1120034, 0, 0, 1397,
    0, 0, (s32)func_8008422C, 0,
    1398, 0x800A8398, 0x1120036, 0,
    (s32)func_80090F80, 1399, 0x800A8520, 0x1120037,
    0, (s32)func_80090FE0, 1401, 0x800A8604,
    0x1120038, 0, 0, 1402,
    0, 0, (s32)func_80084260, 0,
    1403, 0x800A8780, 0x112003A, 0,
    (s32)func_8009100C, 1404, 0x800A8928, 0x112003B,
    0, (s32)func_8009106C, 1406, 0x800A8A0C,
    0x112003C, 0, 0, 1407,
    0, 0, (s32)func_80084294, 0,
    1408, 0x800A8B8C, 0x112003E, 0,
    (s32)func_80091098, 1409, 0x800A8D24, 0x112003F,
    0, (s32)func_800910F8, -1, 0,
    0, 0, 0,
};
#elif VERSION_EU
s32 D_80098B78[] = {
    1320, 0x800A5DE0, 0x1190040, 0,
    0, 1325, 0x800A5EC4, 0x1190041,
    0, 0, 1331, 0x800A5FA8,
    0x1190000, 0, 0, 1332,
    0, 0, (s32)func_80083F8C, 0,
    1333, 0x800A6124, 0x1190001, 0,
    (s32)func_80090864, 1334, 0x800A62BC, 0x1190003,
    0, (s32)func_800908C4, 1336, 0x800A63A0,
    0x1190004, 0, 0, 1337,
    0, 0, (s32)func_80083FBC, 0,
    1338, 0x800A651C, 0x1190006, 0,
    (s32)func_800908F0, 1339, 0x800A66B4, 0x1190007,
    0, (s32)func_80090950, 1341, 0x800A6798,
    0x1190008, 0, 0, 1342,
    0, 0, (s32)func_80083FF0, 0,
    1343, 0x800A6914, 0x119000A, 0,
    (s32)func_8009097C, 1344, 0x800A6AAC, 0x119000B,
    0, (s32)func_800909DC, 1346, 0x800A6B90,
    0x119000C, 0, 0, 1347,
    0, 0, (s32)func_80084024, 0,
    1348, 0x800A6D0C, 0x119000E, 0,
    (s32)func_80090A08, 1349, 0x800A6EA4, 0x119000F,
    0, (s32)func_80090A68, 1351, 0x800A6F88,
    0x1190010, 0, 0, 1352,
    0, 0, (s32)func_80084058, 0,
    1353, 0x800A7104, 0x1190012, 0,
    (s32)func_80090A94, 1354, 0x800A729C, 0x1190013,
    0, (s32)func_80090AF4, 1356, 0x800A7388,
    0x1190014, 0, 0, 1357,
    0, 0, (s32)func_8008408C, 0,
    1358, 0x800A7504, 0x1190016, 0,
    (s32)func_80090B20, 1359, 0x800A769C, 0x1190017,
    0, (s32)func_80090B80, 1361, 0x800A7780,
    0x1190018, 0, 0, 1362,
    0, 0, (s32)func_800840C0, 0,
    1363, 0x800A78FC, 0x119001A, 0,
    (s32)func_80090BAC, 1364, 0x800A7A9C, 0x119001B,
    0, (s32)func_80090C0C, 1366, 0x800A7B80,
    0x119001C, 0, 0, 1367,
    0, 0, (s32)func_800840F4, 0,
    1368, 0x800A7CFC, 0x119001E, 0,
    (s32)func_80090C38, 1369, 0x800A7E94, 0x119001F,
    0, (s32)func_80090C98, 1371, 0x800A7F78,
    0x1190020, 0, 0, 1372,
    0, 0, (s32)func_80084128, 0,
    1373, 0x800A80F4, 0x1190022, 0,
    (s32)func_80090CC4, 1374, 0x800A828C, 0x1190023,
    0, (s32)func_80090D24, 1376, 0x800A8370,
    0x1190024, 0, 0, 1377,
    0, 0, (s32)func_8008415C, 0,
    1378, 0x800A84EC, 0x1190026, 0,
    (s32)func_80090D50, 1379, 0x800A8684, 0x1190027,
    0, (s32)func_80090DB0, 1381, 0x800A8768,
    0x1190028, 0, 0, 1382,
    0, 0, (s32)func_80084190, 0,
    1383, 0x800A88E4, 0x119002A, 0,
    (s32)func_80090DDC, 1384, 0x800A8A7C, 0x119002B,
    0, (s32)func_80090E3C, 1386, 0x800A8B60,
    0x119002C, 0, 0, 1387,
    0, 0, (s32)func_800841C4, 0,
    1388, 0x800A8CDC, 0x119002E, 0,
    (s32)func_80090E68, 1389, 0x800A8E88, 0x119002F,
    0, (s32)func_80090EC8, 1391, 0x800A8F6C,
    0x1190030, 0, 0, 1392,
    0, 0, (s32)func_800841F8, 0,
    1393, 0x800A90E8, 0x1190032, 0,
    (s32)func_80090EF4, 1394, 0x800A9270, 0x1190033,
    0, (s32)func_80090F54, 1396, 0x800A9354,
    0x1190034, 0, 0, 1397,
    0, 0, (s32)func_8008422C, 0,
    1398, 0x800A94D4, 0x1190036, 0,
    (s32)func_80090F80, 1399, 0x800A965C, 0x1190037,
    0, (s32)func_80090FE0, 1401, 0x800A9740,
    0x1190038, 0, 0, 1402,
    0, 0, (s32)func_80084260, 0,
    1403, 0x800A98BC, 0x119003A, 0,
    (s32)func_8009100C, 1404, 0x800A9A64, 0x119003B,
    0, (s32)func_8009106C, 1406, 0x800A9B48,
    0x119003C, 0, 0, 1407,
    0, 0, (s32)func_80084294, 0,
    1408, 0x800A9CC8, 0x119003E, 0,
    (s32)func_80091098, 1409, 0x800A9E60, 0x119003F,
    0, (s32)func_800910F8, -1, 0,
    0, 0, 0,
};
#endif
FieldState D_800990B4 = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, {0, 0},
    0, {0}, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, {0, 0}, 0,
    func_800913CC, func_80091398, func_800913B4, func_80091490,
};
#if VERSION_US
s32 FIELDSTG_fileEntries[] = {
    0, 0x17800CA, 0x1790070, 0x17A0071,
    0x17B005F, 0x17C005F, 0x17D0073, 0x17E006E,
    0x17F006B, 0x1800072, 0x181009B, 0x18200A8,
    0x18300AD, 0x184003D, 0x184003D, 0x184003D,
    0x185002A, 0x3050020, 0x3040020, 0x3690020,
    0x2E60010, 0x30D002D, 0x2E70010, 0x2E50021,
    0x2E8001E, 0x30A0010, 0x30B0021, 0x308000E,
    0x3780007, 0x4160012, 0x2D30020, 0x3180008,
    0x3F10014, 0x3EC0015, 0x2EC003C, 0x2EB0037,
    0x3F10014, 0x30C0020, 0x30C0020, 0x30C0020,
    0x2FC0004, 0x2FD0004, 0x2FE0004, 0x2FB0020,
    0x2FB0020, 0x3070020, 0x3050020, 0x3060020,
    0x2F60015, 0x3030020, 0x3010020, 0x3040020,
    0x3000020, 0x3020020, 0x2FF0020, 0x3690020,
    0x3670020, 0x3680025, 0x3750020, 0x3760008,
    0x2D60020, 0x3660008, 0x40B0005, 0,
    0x2ED0032, 0x2EE003B, 0x2EF005A, 0x2E0001E,
    0x30B0021, 0x3490020, 0x3490020, 0x3490020,
    0x3490020, 0x3490020, 0x3490020, 0x40A0014,
    0x40A0014, 0x3EC0015, 0x3EC0015, 0x3EC0015,
    0x3EC0015, 0x3EC0015, 0x3EC0015, 0x3EC0015,
    0x3EC0015, 0x3EC0015, 0x3EC0015, 0x3EC0015,
    0x40A0014, 0x3F10014, 0x3770004, 0x4160012,
    0x4160012, 0x4160012, 0x4160012, 0x4160012,
    0x4160012, 0x3640012, 0x3640012, 0x4E40004,
    0x4090008, 0x5410042, 0x4E50032, 0x63B0032,
    0x4E0002E, 0x3630037, 0x63C006E, 0x63E006E,
    0x4E20020, 0x3470020, 0x3470020, 0x30C0020,
    0, 0, 0x63D0008, 0x3460020,
    0x3460020, 0x3460020, 0x3D30032, 0x3470020,
    0x2E60010, 0x2E60010, 0x2D70020, 0x37B0008,
    0x37C0008, 0x41D0008, 0x37E0008, 0x37D0008,
    0x4080008, 0x41C0008, 0x7C20011, 0x7C30011,
    0x3650008, 0x3DE000F, 0x309000F, 0x34D000E,
    0x34B0010, 0x34E000E, 0x40C0011, 0x34A0012,
    0x34C000E, 0x2D50020, 0x2D80022, 0x2D90020,
    0x2DB0020, 0x2DC0020, 0x2DA0022, 0x3610009,
    0x3610009, 0x3610009, 0x3DF0008, 0x3DC000A,
    0x3480020, 0x7870002, 0x7860008, 0x7860008,
    0x7860008, 0x402002D, 0x402002D, 0x402002D,
    0x402002D, 0x402002D, 0x402002D, 0x2FB0020,
    0x3490020, 0x3DD0008, 0x4050008, 0x4040009,
    0x4010006, 0x4060009, 0x4030008, 0x37A0009,
    0x3790009, 0x4070009, 0x402002D, 0x402002D,
    0x402002D, 0x402002D, 0x2E90026, 0x2EA0026,
    0x7830032, 0x7840032, 0x785003A, 0x7300008,
    0x3640012, 0x3640012, 0x3640012, 0x3640012,
    0x3640012, 0x3640012, 0x3640012, 0x3640012,
    0x3600016, 0x3620012, 0x3440023, 0x3440023,
    0x3440023, 0x799000C, 0, 0,
    0x2DE001E, 0x2DF001E, 0x2E1001E, 0x2E2001E,
    0x2DF001E, 0x2D4001E, 0x4160012, 0x3620012,
    0x3450022, 0x3450022, 0x36A0020, 0x36A0020,
    0x36A0020, 0x72E0019, 0x7980021, 0x7C60013,
    0x7C60013, 0x7C60013, 0x7C60013, 0,
    0, 0, 0, 0,
    0, 0, 0x2EC003C, 0x2EC003C,
    0x2EB0037, 0x2EB0037, 0x30C0020, 0x2ED0032,
    0x2ED0032, 0x2EF005A, 0x2EF005A, 0x2EE003B,
    0x2EE003B, 0x785003A, 0x785003A, 0x7840032,
    0x7840032, 0x7830032, 0x7830032, 0x3DA0008,
    0x3DA0008, 0x3DA0008, 0x3DA0008, 0x3DA0008,
    0x3DA0008, 0x3DA0008, 0x3DA0008, 0x402002D,
    0x3490020, 0x3490020, 0x2E0001E, 0x2DD001C,
    0, 0x3460020, 0x4E10020, 0x3460020,
    0x3460020, 0x3D40008, 0x3DB0008, 0x3D70008,
    0x3D90008, 0x3D80008, 0x4E30004, 0x3780007,
    0, 0x3490020, 0, 0,
    0x3D30032, 0x3D30032, 0x3D30032, 0x3D30032,
    0x3D30032, 0x3D30032, 0x3D30032, 0x3D30032,
    0x3030020, 0x402002D, 0x79E0029, 0x72F0026,
    0, 0x3630037, 0x3DC000A, 0x79B0004,
    0, 0, 0, 0,
    0, 0x3690020, 0x3070020, 0x4160012,
    0x4160012, 0x3640012, 0x3620012, 0x3460020,
    0x1800072, 0x3440023, 0x3440023, 0x3460020,
    0x3460020, 0x3460020, 0x3490020, 0x3490020,
    0x3490020, 0x3490020, 0x3490020, 0x3490020,
    0x3440023, 0x3440023, 0x402002D, 0x3040020,
    0x8060008, 0x7C5002D, 0x7C4002D, 0x79A0002,
    0x4160012, 0x4160012, 0x4160012, 0x3640012,
    0x3640012, 0x3640012, 0x3D6005F, 0x3D50023,
    0x828000E, 0x72C0037, 0x72D0037, 0x7C70005,
    0x7C80008, 0x4E6006E, 0x4E6006E, 0x4E6006E,
    0x4E6006E, 0x4E6006E, 0x4E6006E, 0x4E6006E,
    0x3EC0015, 0x3EC0015, 0x3EC0015, 0x3EC0015,
    0x3EC0015, 0x3630037, 0x3630037, 0x3EC0015,
    0x3630037, 0x3630037, 0x3630037, 0x828000E,
    0x828000E, 0x828000E, 0x828000E, 0x828000E,
    0x828000E, 0x828000E, 0x828000E, 0x828000E,
    0x828000E, 0x4160012, 0x4160012, 0x3640012,
    0x3640012, 0x8830019, 0x8830019, 0x8880019,
    0x8880019, 0x8840014, 0x8840014, 0x8860032,
    0x8860032, 0x8850019, 0x8850019, 0x8800019,
    0x8800019, 0x8820014, 0x8810014, 0x8810014,
    0x8810014, 0x30C0020, 0x30C0020, 0x30C0020,
    0x88B0002, 0x88B0002, 0x88B0002, 0x3640012,
    0x3640012, 0x88F0008, 0x30C0020, 0x30C0020,
    0x72E0019,
};
u8 D_80099758[] = {
    0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x30, 0x20, 0x28,
    0x20, 0x20, 0x28, 0x20, 0x20, 0x28, 0x38, 0x28,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x28, 0x28, 0x20, 0x20, 0x20, 0x18, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x28, 0x20, 0x20, 0x40, 0x20,
    0x20, 0x20, 0x20, 0x18, 0x28, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x28, 0x28, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x28, 0x20, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
    0x28, 0x20, 0x20, 0x28, 0x30, 0x20, 0x18, 0x20,
    0x18, 0x20, 0x20, 0x20, 0x18, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x50, 0x40, 0x30, 0x48, 0x40,
    0x40, 0x28, 0x10, 0x18, 0x30, 0x38, 0x28, 0x20,
    0x20, 0x20, 0x28, 0x30, 0x20, 0x28, 0x20, 0x20,
    0x28, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x30,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x28, 0x20, 0x28,
    0x20, 0x28, 0x28, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x38,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x18, 0x18, 0x20, 0x18, 0x18, 0x20, 0x28, 0x20,
    0x30, 0x30, 0x28, 0x28, 0x28, 0x40, 0x38, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x20, 0x20, 0x20, 0x18, 0x38,
    0x20, 0x20, 0x18, 0x20, 0x20, 0x38, 0x38, 0x40,
    0x50, 0x48, 0x38, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x38, 0x38, 0x20, 0x20, 0x20, 0x20, 0x30, 0x18,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x38, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x38, 0x14, 0x20, 0x20, 0x14,
    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x28, 0x20,
    0x50, 0x20, 0x20, 0x14, 0x14, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x60,
    0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
    0x60, 0x38, 0x38, 0x38, 0x38, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x38, 0x38, 0x38,
    0x40, 0x40, 0x40, 0x38, 0x38, 0x14, 0x20, 0x20,
    0x40, 0x00, 0x00, 0x00,
};
StageEntry D_800998E4[] = {
    {512, 451, (void *)0x800A4D40},
    {513, 509, (void *)0x800A4CF0},
    {514, 452, (void *)0x800A5058},
    {515, 453, (void *)0x800A6310},
    {516, 545, (void *)0x800A52A0},
    {517, 549, (void *)0x800A4CF0},
    {518, 454, (void *)0x800A5ED8},
    {519, 455, (void *)0x800A5178},
    {520, 456, (void *)0x800A4CEC},
    {521, 580, (void *)0x800A4F20},
    {522, 457, (void *)0x800A4CEC},
    {523, 652, (void *)0x800A4CEC},
    {524, 458, (void *)0x800A4CEC},
    {525, 459, (void *)0x800A4CEC},
    {526, 460, (void *)0x800A4CEC},
    {527, 461, (void *)0x800A4CEC},
    {528, 462, (void *)(s32)func_800844B8},
    {529, 463, (void *)0x800A58DC},
    {530, 464, (void *)0x800A4CF0},
    {531, 465, (void *)0x800A535C},
    {532, 679, (void *)0x800A4D70},
    {533, 670, (void *)0x800A4CEC},
    {534, 859, (void *)0x800A4DA4},
    {535, 833, (void *)0x800A4D9C},
    {536, 829, (void *)0x800A526C},
    {537, 821, (void *)0x800A5C40},
    {538, 1014, (void *)0x800A4CEC},
    {539, 662, (void *)0x800A4D4C},
    {540, 1084, (void *)0x800A4F2C},
    {541, 466, (void *)0x800A4CF0},
    {542, 467, (void *)0x800A4D00},
    {543, 915, (void *)0x800A4CF0},
    {544, 919, (void *)0x800A4CF0},
    {545, 468, (void *)0x800A4CEC},
    {546, 469, (void *)0x800A4CEC},
    {547, 480, (void *)0x800A4CEC},
    {548, 526, (void *)0x800A4CEC},
    {549, 470, (void *)0x800A4CEC},
    {550, 471, (void *)0x800A4EDC},
    {551, 685, (void *)0x800A4CF0},
    {552, 1220, (void *)0x800A4D48},
    {553, 478, (void *)0x800A4D7C},
    {554, 1019, (void *)0x800A4D50},
    {555, 558, (void *)0x800A4F5C},
    {556, 910, (void *)0x800A4CF0},
    {557, 1245, (void *)0x800A5E84},
    {558, 1257, (void *)0x800A4D38},
    {559, 551, (void *)0x800A4CEC},
    {560, 481, (void *)0x800A4CEC},
    {561, 472, (void *)0x800A4CEC},
    {562, 878, (void *)0x800A4D14},
    {563, 1282, (void *)0x800A4D48},
    {564, 906, (void *)0x800A4D48},
    {565, 898, (void *)0x800A4F98},
    {566, 853, (void *)0x800A5EE0},
    {567, 473, (void *)0x800A4CF0},
    {568, 518, (void *)0x800A4CEC},
    {569, 482, (void *)0x800A4E4C},
    {570, 856, (void *)0x800A50F4},
    {571, 935, (void *)0x800A4CF0},
    {572, 1008, (void *)0x800A4D8C},
    {573, 952, (void *)0x800A4CEC},
    {574, 1023, (void *)0x800A4CEC},
    {575, 525, (void *)0x800A4CEC},
    {576, 532, (void *)0x800A4D38},
    {577, 948, (void *)0x800A4D44},
    {578, 574, (void *)0x800A4CEC},
    {579, 646, (void *)0x800A4D44},
    {580, 1349, (void *)0x800A4D4C},
    {581, 1394, (void *)0x800A4CEC},
    {582, 559, (void *)0x800A5848},
    {583, 1119, (void *)0x800A4D48},
    {584, 529, (void *)0x800A4F94},
    {585, 674, (void *)0x800A4CF0},
    {586, 1292, (void *)0x800A4D44},
    {587, 1045, (void *)0x800A4CF0},
    {588, 1138, (void *)0x800A4D38},
    {589, 1419, (void *)0x800A4D6C},
    {590, 1276, (void *)0x800A4D4C},
    {591, 1277, (void *)0x800A4CEC},
    {592, 1278, (void *)0x800A4CEC},
    {593, 1266, (void *)0x800A4CEC},
    {594, 1142, (void *)0x800A4D2C},
    {595, 1201, (void *)0x800A4CEC},
    {596, 1358, (void *)0x800A4D3C},
    {597, 1149, (void *)0x800A51D8},
    {598, 1150, (void *)0x800A50C8},
    {599, 1157, (void *)0x800A4F94},
    {600, 1165, (void *)0x800A50B8},
    {601, 1169, (void *)0x800A50B8},
    {602, 1177, (void *)0x800A4F94},
    {603, 1343, (void *)0x800A4CEC},
    {604, 1161, (void *)0x800A4D38},
    {605, 1208, (void *)0x800A4CF0},
    {606, 1185, (void *)0x800A4D38},
    {607, 1488, (void *)0x800A5318},
    {608, 1209, (void *)0x800A4D1C},
    {609, 1496, (void *)0x800A4CEC},
    {610, 1504, (void *)0x800A4CEC},
    {611, 1512, (void *)0x800A4CEC},
    {612, 1520, (void *)0x800A4CEC},
    {613, 666, (void *)0x800A4CEC},
    {614, 1528, (void *)0x800A4CEC},
    {615, 1540, (void *)0x800A4CEC},
    {616, 1548, (void *)0x800A4CEC},
    {617, 1556, (void *)(s32)func_800A4EE8},
    {618, 1603, (void *)0x800A4DA8},
    {619, 1605, (void *)0x800A4FFC},
    {620, 1607, (void *)0x800A517C},
    {621, 1609, (void *)0x800A52E8},
    {622, 1610, (void *)0x800A4D30},
    {623, 1615, (void *)0x800A4CEC},
    {624, 508, (void *)0x800A4CF0},
    {625, 510, (void *)0x800A4CF0},
    {626, 520, (void *)0x800A4D84},
    {627, 521, (void *)0x800A4CF0},
    {628, 575, (void *)0x800A4CF0},
    {629, 577, (void *)0x800A4CF0},
    {630, 578, (void *)0x800A518C},
    {631, 579, (void *)0x800A4CEC},
    {632, 609, (void *)0x800A4F20},
    {633, 624, (void *)0x800A4CEC},
    {634, 657, (void *)0x800A4CEC},
    {635, 682, (void *)0x800A4CEC},
    {636, 686, (void *)0x800A4CEC},
    {637, 687, (void *)0x800A4CEC},
    {638, 643, (void *)0x800A4CEC},
    {639, 696, (void *)0x800A5210},
    {640, 794, (void *)0x800A4CEC},
    {641, 795, (void *)0x800A4CF0},
    {642, 811, (void *)0x800A4CEC},
    {643, 815, (void *)0x800A4CEC},
    {644, 825, (void *)0x800A4CEC},
    {645, 860, (void *)0x800A4CEC},
    {646, 861, (void *)0x800A4CEC},
    {647, 920, (void *)0x800A5024},
    {648, 921, (void *)0x800A5C94},
    {649, 1015, (void *)0x800A4CEC},
    {650, 1061, (void *)0x800A4CF0},
    {651, 1104, (void *)0x800A4F2C},
    {652, 1105, (void *)0x800A4CF0},
    {653, 1106, (void *)0x800A4CEC},
    {654, 1107, (void *)0x800A4CEC},
    {655, 1124, (void *)0x800A4CEC},
    {656, 1134, (void *)0x800A4CEC},
    {657, 1173, (void *)0x800A4CEC},
    {658, 1181, (void *)0x800A4CEC},
    {659, 1189, (void *)0x800A4CEC},
    {660, 1193, (void *)0x800A4CEC},
    {661, 1215, (void *)0x800A4D48},
    {662, 1219, (void *)0x800A4CF0},
    {663, 1225, (void *)0x800A4CEC},
    {664, 1229, (void *)0x800A4CEC},
    {665, 1233, (void *)0x800A4CF0},
    {666, 1243, (void *)0x800A4F48},
    {667, 1244, (void *)0x800A4CF0},
    {668, 1262, (void *)0x800A4DE0},
    {669, 1284, (void *)0x800A4CEC},
    {670, 1288, (void *)0x800A4CEC},
    {671, 1296, (void *)0x800A4CEC},
    {672, 1300, (void *)0x800A4CF0},
    {673, 1304, (void *)0x800A4CF0},
    {674, 1308, (void *)0x800A4CF0},
    {675, 1312, (void *)0x800A4CF0},
    {676, 1316, (void *)0x800A4CF0},
    {677, 1335, (void *)0x800A4CEC},
    {678, 1336, (void *)0x800A4CEC},
    {679, 1337, (void *)0x800A50B8},
    {680, 1338, (void *)0x800A4CF0},
    {681, 1339, (void *)0x800A4CEC},
    {682, 1344, (void *)0x800A4CEC},
    {683, 1370, (void *)0x800A4CEC},
    {684, 1374, (void *)0x800A4CEC},
    {685, 1378, (void *)0x800A4D38},
    {686, 1382, (void *)0x800A6324},
    {687, 1386, (void *)0x800A4CEC},
    {688, 1390, (void *)0x800A4D44},
    {689, 1398, (void *)0x800A4CEC},
    {690, 1402, (void *)0x800A4CEC},
    {691, 1406, (void *)0x800A4CEC},
    {692, 1410, (void *)0x800A4CEC},
    {693, 1414, (void *)0x800A4CEC},
    {694, 1415, (void *)0x800A4CEC},
    {695, 1423, (void *)0x800A4CEC},
    {696, 1427, (void *)0x800A4CEC},
    {697, 1431, (void *)0x800A4CEC},
    {698, 1435, (void *)0x800A4CEC},
    {699, 1439, (void *)0x800A4CEC},
    {700, 1443, (void *)0x800A4D44},
    {701, 1447, (void *)0x800A4CEC},
    {702, 1451, (void *)0x800A4D48},
    {703, 1455, (void *)0x800A4CEC},
    {704, 1459, (void *)0x800A4CEC},
    {705, 1463, (void *)0x800A4E18},
    {706, 1467, (void *)0x800A4E18},
    {707, 1471, (void *)0x800A4CEC},
    {708, 1475, (void *)0x800A4CEC},
    {709, 1479, (void *)0x800A4CEC},
    {710, 1483, (void *)0x800A4CF0},
    {711, 1487, (void *)0x800A4D2C},
    {712, 1492, (void *)0x800A4CEC},
    {713, 1500, (void *)0x800A4CEC},
    {714, 1508, (void *)0x800A4CEC},
    {715, 1516, (void *)0x800A4CEC},
    {716, 1524, (void *)0x800A4CEC},
    {717, 1527, (void *)0x800A4CEC},
    {718, 1536, (void *)0x800A4CEC},
    {719, 1544, (void *)0x800A4CEC},
    {720, 1552, (void *)0x800A4CEC},
    {721, 1572, (void *)(s32)func_800A4EE8},
    {722, 1604, (void *)0x800A4DA8},
    {723, 1606, (void *)0x800A4FFC},
    {724, 1608, (void *)0x800A517C},
    {725, 1611, (void *)0x800A4D64},
    {726, 1619, (void *)0x800A4CEC},
    {727, 474, (void *)0x800A6474},
    {728, 475, (void *)0x800A5574},
    {729, 476, (void *)0x800A51E0},
    {730, 1623, (void *)0x800A5518},
    {731, 1627, (void *)0x800A5890},
    {732, 1631, (void *)0x800A5A08},
    {733, 1635, (void *)0x800A52DC},
    {734, 1639, (void *)0x800A5048},
    {735, 1643, (void *)0x800A5024},
    {736, 1649, (void *)0x800A4E14},
    {737, 1653, (void *)0x800A4E1C},
    {738, 1657, (void *)0x800A4E14},
    {739, 1681, (void *)0x800A4E14},
    {740, 1685, (void *)0x800A4E14},
    {741, 1689, (void *)0x800A4E14},
    {742, 1693, (void *)0x800A4E14},
    {743, 1705, (void *)0x800A4E14},
    {744, 1697, (void *)0x800A4E18},
    {745, 1701, (void *)0x800A4E18},
    {746, 1661, (void *)0x800A4E18},
    {747, 1674, (void *)0x800A4E18},
    {748, 1675, (void *)0x800A4E18},
    {749, 1676, (void *)0x800A4E18},
    {750, 1677, (void *)0x800A4E18},
    {0, 0, 0},
};
#elif VERSION_EU
s32 FIELDSTG_fileEntries[] = {
    0, 0x18600CA, 0x1870070, 0x1880071,
    0x189005F, 0x18A005F, 0x18B0073, 0x18C006E,
    0x18D006B, 0x18E0072, 0x18F009B, 0x19000A8,
    0x19100AD, 0x192003D, 0x192003D, 0x192003D,
    0x193002A, 0x3140020, 0x3130020, 0x3790020,
    0x2F50010, 0x31C002D, 0x2F60010, 0x2F40021,
    0x2F7001E, 0x3190010, 0x31A0021, 0x317000E,
    0x3880007, 0x4260012, 0x2E20020, 0x3270008,
    0x4010014, 0x3FC0015, 0x2FB003C, 0x2FA0037,
    0x4010014, 0x31B0020, 0x31B0020, 0x31B0020,
    0x30B0004, 0x30C0004, 0x30D0004, 0x30A0020,
    0x30A0020, 0x3160020, 0x3140020, 0x3150020,
    0x3050015, 0x3120020, 0x3100020, 0x3130020,
    0x30F0020, 0x3110020, 0x30E0020, 0x3790020,
    0x3770020, 0x3780025, 0x3850020, 0x3860008,
    0x2E50020, 0x3760008, 0x41B0005, 0,
    0x2FC0032, 0x2FD003B, 0x2FE005A, 0x2EF001E,
    0x31A0021, 0x3580020, 0x3580020, 0x3580020,
    0x3580020, 0x3580020, 0x3580020, 0x41A0014,
    0x41A0014, 0x3FC0015, 0x3FC0015, 0x3FC0015,
    0x3FC0015, 0x3FC0015, 0x3FC0015, 0x3FC0015,
    0x3FC0015, 0x3FC0015, 0x3FC0015, 0x3FC0015,
    0x41A0014, 0x4010014, 0x3870004, 0x4260012,
    0x4260012, 0x4260012, 0x4260012, 0x4260012,
    0x4260012, 0x3740012, 0x3740012, 0x4F40004,
    0x4190008, 0x5510042, 0x4F50032, 0x64B0032,
    0x4F0002E, 0x3730037, 0x64C006E, 0x64E006E,
    0x4F20020, 0x3560020, 0x3560020, 0x31B0020,
    0, 0, 0x64D0008, 0x3550020,
    0x3550020, 0x3550020, 0x3E30032, 0x3560020,
    0x2F50010, 0x2F50010, 0x2E60020, 0x38B0008,
    0x38C0008, 0x42D0008, 0x38E0008, 0x38D0008,
    0x4180008, 0x42C0008, 0x7D10011, 0x7D20011,
    0x3750008, 0x3EE000F, 0x318000F, 0x35C000E,
    0x35A0010, 0x35D000E, 0x41C0011, 0x3590012,
    0x35B000E, 0x2E40020, 0x2E70022, 0x2E80020,
    0x2EA0020, 0x2EB0020, 0x2E90022, 0x3710009,
    0x3710009, 0x3710009, 0x3EF0008, 0x3EC000A,
    0x3570020, 0x7960002, 0x7950008, 0x7950008,
    0x7950008, 0x412002D, 0x412002D, 0x412002D,
    0x412002D, 0x412002D, 0x412002D, 0x30A0020,
    0x3580020, 0x3ED0008, 0x4150008, 0x4140009,
    0x4110006, 0x4160009, 0x4130008, 0x38A0009,
    0x3890009, 0x4170009, 0x412002D, 0x412002D,
    0x412002D, 0x412002D, 0x2F80026, 0x2F90026,
    0x7920032, 0x7930032, 0x794003A, 0x7400008,
    0x3740012, 0x3740012, 0x3740012, 0x3740012,
    0x3740012, 0x3740012, 0x3740012, 0x3740012,
    0x3700016, 0x3720012, 0x3530023, 0x3530023,
    0x3530023, 0x7A8000C, 0, 0,
    0x2ED001E, 0x2EE001E, 0x2F0001E, 0x2F1001E,
    0x2EE001E, 0x2E3001E, 0x4260012, 0x3720012,
    0x3540022, 0x3540022, 0x37A0020, 0x37A0020,
    0x37A0020, 0x73E0019, 0x7A70021, 0x7D50013,
    0x7D50013, 0x7D50013, 0x7D50013, 0,
    0, 0, 0, 0,
    0, 0, 0x2FB003C, 0x2FB003C,
    0x2FA0037, 0x2FA0037, 0x31B0020, 0x2FC0032,
    0x2FC0032, 0x2FE005A, 0x2FE005A, 0x2FD003B,
    0x2FD003B, 0x794003A, 0x794003A, 0x7930032,
    0x7930032, 0x7920032, 0x7920032, 0x3EA0008,
    0x3EA0008, 0x3EA0008, 0x3EA0008, 0x3EA0008,
    0x3EA0008, 0x3EA0008, 0x3EA0008, 0x412002D,
    0x3580020, 0x3580020, 0x2EF001E, 0x2EC001C,
    0, 0x3550020, 0x4F10020, 0x3550020,
    0x3550020, 0x3E40008, 0x3EB0008, 0x3E70008,
    0x3E90008, 0x3E80008, 0x4F30004, 0x3880007,
    0, 0x3580020, 0, 0,
    0x3E30032, 0x3E30032, 0x3E30032, 0x3E30032,
    0x3E30032, 0x3E30032, 0x3E30032, 0x3E30032,
    0x3120020, 0x412002D, 0x7AD0029, 0x73F0026,
    0, 0x3730037, 0x3EC000A, 0x7AA0004,
    0, 0, 0, 0,
    0, 0x3790020, 0x3160020, 0x4260012,
    0x4260012, 0x3740012, 0x3720012, 0x3550020,
    0x18E0072, 0x3530023, 0x3530023, 0x3550020,
    0x3550020, 0x3550020, 0x3580020, 0x3580020,
    0x3580020, 0x3580020, 0x3580020, 0x3580020,
    0x3530023, 0x3530023, 0x412002D, 0x3130020,
    0x8150008, 0x7D4002D, 0x7D3002D, 0x7A90002,
    0x4260012, 0x4260012, 0x4260012, 0x3740012,
    0x3740012, 0x3740012, 0x3E6005F, 0x3E50023,
    0x839000E, 0x73C0037, 0x73D0037, 0x7D60005,
    0x7D70008, 0x4F6006E, 0x4F6006E, 0x4F6006E,
    0x4F6006E, 0x4F6006E, 0x4F6006E, 0x4F6006E,
    0x3FC0015, 0x3FC0015, 0x3FC0015, 0x3FC0015,
    0x3FC0015, 0x3730037, 0x3730037, 0x3FC0015,
    0x3730037, 0x3730037, 0x3730037, 0x839000E,
    0x839000E, 0x839000E, 0x839000E, 0x839000E,
    0x839000E, 0x839000E, 0x839000E, 0x839000E,
    0x839000E, 0x4260012, 0x4260012, 0x3740012,
    0x3740012, 0x8940019, 0x8940019, 0x8990019,
    0x8990019, 0x8950014, 0x8950014, 0x8970032,
    0x8970032, 0x8960019, 0x8960019, 0x8910019,
    0x8910019, 0x8930014, 0x8920014, 0x8920014,
    0x8920014, 0x31B0020, 0x31B0020, 0x31B0020,
    0x89C0002, 0x89C0002, 0x89C0002, 0x3740012,
    0x3740012, 0x8A00008, 0x31B0020, 0x31B0020,
    0x73E0019, 0x3EB0008, 0x3E90008, 0x3E70008,
    0x3E80008, 0x3E40008, 0x4F30004, 0x3140020,
    0x3780025, 0x3110020, 0x30F0020, 0x3100020,
    0x8960019, 0x8970032,
};
u8 D_80099758[] = {
    0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x30, 0x20, 0x28,
    0x20, 0x20, 0x28, 0x20, 0x20, 0x28, 0x38, 0x28,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x28, 0x28, 0x20, 0x20, 0x20, 0x18, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x28, 0x20, 0x20, 0x40, 0x20,
    0x20, 0x20, 0x20, 0x18, 0x28, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x28, 0x28, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x28, 0x20, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
    0x28, 0x20, 0x20, 0x28, 0x30, 0x20, 0x18, 0x20,
    0x18, 0x20, 0x20, 0x20, 0x18, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x50, 0x40, 0x30, 0x48, 0x40,
    0x40, 0x28, 0x10, 0x18, 0x30, 0x38, 0x28, 0x20,
    0x20, 0x20, 0x28, 0x30, 0x20, 0x28, 0x20, 0x20,
    0x28, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x30,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x28, 0x20, 0x28,
    0x20, 0x28, 0x28, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x38,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x18, 0x18, 0x20, 0x18, 0x18, 0x20, 0x28, 0x20,
    0x30, 0x30, 0x28, 0x28, 0x28, 0x40, 0x38, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x20, 0x20, 0x20, 0x18, 0x38,
    0x20, 0x20, 0x18, 0x20, 0x20, 0x38, 0x38, 0x40,
    0x50, 0x48, 0x38, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x38, 0x38, 0x20, 0x20, 0x20, 0x20, 0x30, 0x18,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x38, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x38, 0x14, 0x20, 0x20, 0x14,
    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x28, 0x20,
    0x50, 0x20, 0x20, 0x14, 0x14, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x60,
    0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
    0x60, 0x38, 0x38, 0x38, 0x38, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x38, 0x38, 0x38,
    0x40, 0x40, 0x40, 0x38, 0x38, 0x14, 0x20, 0x20,
    0x40, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x38,
    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x00, 0x00,
};
StageEntry D_800998E4[] = {
    {624, 1851, (void *)0x800A5E2C},
    {625, 2217, (void *)0x800A5E2C},
    {626, 2219, (void *)0x800A5E2C},
    {627, 2220, (void *)0x800A5E2C},
    {629, 2221, (void *)0x800A5E8C},
    {630, 2222, (void *)0x800A5E64},
    {631, 2223, (void *)0x800A5E28},
    {632, 2224, (void *)0x800A60BC},
    {633, 2225, (void *)0x800A5E28},
    {634, 2226, (void *)0x800A5E28},
    {635, 2227, (void *)0x800A5E28},
    {636, 2228, (void *)0x800A5E28},
    {637, 2229, (void *)0x800A5E28},
    {638, 2230, (void *)0x800A5E28},
    {639, 2231, (void *)0x800A633C},
    {640, 2232, (void *)0x800A5E88},
    {641, 2233, (void *)0x800A5E2C},
    {642, 2234, (void *)0x800A5E28},
    {650, 2235, (void *)0x800A5E2C},
    {651, 2236, (void *)0x800A5E28},
    {652, 2237, (void *)0x800A5E2C},
    {653, 2238, (void *)0x800A5E28},
    {654, 2239, (void *)0x800A5E2C},
    {655, 2240, (void *)0x800A5E2C},
    {656, 2241, (void *)0x800A5E28},
    {657, 2242, (void *)0x800A5E28},
    {658, 2243, (void *)0x800A5E28},
    {659, 2244, (void *)0x800A5E28},
    {660, 2245, (void *)0x800A5E28},
    {661, 2246, (void *)0x800A5FC8},
    {662, 2247, (void *)0x800A5E2C},
    {663, 2248, (void *)0x800A5E2C},
    {664, 2249, (void *)0x800A5E28},
    {665, 2250, (void *)0x800A5E2C},
    {666, 2251, (void *)0x800A6038},
    {667, 2252, (void *)0x800A5E2C},
    {668, 2253, (void *)0x800A5E28},
    {669, 2254, (void *)0x800A5E28},
    {670, 2255, (void *)0x800A5E28},
    {671, 2256, (void *)0x800A5E28},
    {736, 2257, (void *)0x800A5F58},
    {737, 2258, (void *)0x800A5F58},
    {738, 2259, (void *)0x800A5F58},
    {739, 2260, (void *)0x800A5F58},
    {740, 2261, (void *)0x800A5F58},
    {741, 2262, (void *)0x800A5F58},
    {742, 2263, (void *)0x800A5F58},
    {743, 2264, (void *)0x800A5F58},
    {744, 2265, (void *)0x800A5F54},
    {745, 2266, (void *)0x800A5F54},
    {746, 2267, (void *)0x800A5F54},
    {747, 2268, (void *)0x800A5F54},
    {748, 2269, (void *)0x800A5F54},
    {749, 2270, (void *)0x800A5F54},
    {750, 2271, (void *)0x800A5F54},
};
StageEntry D_8009A884[] = {
    {512, 466, (void *)0x800A5E7C},
    {513, 523, (void *)0x800A5E2C},
    {514, 467, (void *)0x800A6194},
    {515, 468, (void *)0x800A74A4},
    {516, 536, (void *)0x800A63DC},
    {517, 560, (void *)0x800A5E2C},
    {518, 469, (void *)0x800A7074},
    {519, 470, (void *)0x800A62B4},
    {520, 471, (void *)0x800A5E28},
    {521, 594, (void *)0x800A605C},
    {522, 472, (void *)0x800A5E28},
    {523, 639, (void *)0x800A5E28},
    {524, 473, (void *)0x800A5E28},
    {525, 474, (void *)0x800A5E28},
    {526, 475, (void *)0x800A5E28},
    {527, 476, (void *)0x800A5E28},
    {528, 477, (void *)(s32)func_800844B8},
    {529, 478, (void *)0x800A6A58},
    {530, 479, (void *)0x800A5E2C},
    {531, 480, (void *)0x800A64B8},
    {532, 694, (void *)0x800A5EAC},
    {533, 685, (void *)0x800A5E28},
    {534, 840, (void *)0x800A5EE0},
    {535, 848, (void *)0x800A5ED8},
    {536, 844, (void *)0x800A63A8},
    {537, 836, (void *)0x800A6D7C},
    {538, 936, (void *)0x800A5E28},
    {539, 677, (void *)0x800A5E88},
    {540, 1031, (void *)0x800A6068},
    {541, 481, (void *)0x800A5E2C},
    {542, 482, (void *)0x800A5E3C},
    {543, 931, (void *)0x800A5E2C},
    {544, 935, (void *)0x800A5E2C},
    {545, 483, (void *)0x800A5E28},
    {546, 484, (void *)0x800A5E28},
    {547, 495, (void *)0x800A5E28},
    {548, 541, (void *)0x800A5E28},
    {549, 485, (void *)0x800A5E28},
    {550, 486, (void *)0x800A6018},
    {551, 700, (void *)0x800A5E2C},
    {552, 1231, (void *)0x800A5E84},
    {553, 493, (void *)0x800A5EB8},
    {554, 1035, (void *)0x800A5E8C},
    {555, 573, (void *)0x800A6098},
    {556, 926, (void *)0x800A5E2C},
    {557, 1259, (void *)0x800A6FC0},
    {558, 1260, (void *)0x800A5E74},
    {559, 566, (void *)0x800A5E28},
    {560, 496, (void *)0x800A5E28},
    {561, 487, (void *)0x800A5E28},
    {562, 894, (void *)0x800A5E50},
    {563, 1298, (void *)0x800A5E84},
    {564, 922, (void *)0x800A5E84},
    {565, 914, (void *)0x800A60D4},
    {566, 868, (void *)0x800A701C},
    {567, 488, (void *)0x800A5E2C},
    {568, 533, (void *)0x800A5E28},
    {569, 497, (void *)0x800A5F88},
    {570, 871, (void *)0x800A6230},
    {571, 951, (void *)0x800A5E2C},
    {572, 1024, (void *)0x800A5EC8},
    {573, 968, (void *)0x800A5E28},
    {574, 1039, (void *)0x800A5E28},
    {575, 540, (void *)0x800A5E28},
    {576, 547, (void *)0x800A5E74},
    {577, 964, (void *)0x800A5E80},
    {578, 589, (void *)0x800A5E28},
    {579, 661, (void *)0x800A5E80},
    {580, 1365, (void *)0x800A5E88},
    {581, 1402, (void *)0x800A5E28},
    {582, 574, (void *)0x800A6984},
    {583, 1135, (void *)0x800A5E84},
    {584, 544, (void *)0x800A60D0},
    {585, 689, (void *)0x800A5E2C},
    {586, 1308, (void *)0x800A5E80},
    {587, 1061, (void *)0x800A5E2C},
    {588, 1154, (void *)0x800A5E74},
    {589, 1430, (void *)0x800A5EA8},
    {590, 1292, (void *)0x800A5E88},
    {591, 1293, (void *)0x800A5E28},
    {592, 1294, (void *)0x800A5E28},
    {593, 1282, (void *)0x800A5E28},
    {594, 1158, (void *)0x800A5E68},
    {595, 1217, (void *)0x800A5E28},
    {596, 1374, (void *)0x800A5E78},
    {597, 1165, (void *)0x800A6314},
    {598, 1166, (void *)0x800A6204},
    {599, 1173, (void *)0x800A60D0},
    {600, 1181, (void *)0x800A61F4},
    {601, 1185, (void *)0x800A61F4},
    {602, 1193, (void *)0x800A60D0},
    {603, 1359, (void *)0x800A5E28},
    {604, 1177, (void *)0x800A5E74},
    {605, 1224, (void *)0x800A5E2C},
    {606, 1201, (void *)0x800A5E74},
    {607, 1499, (void *)0x800A6454},
    {608, 1225, (void *)0x800A5E58},
    {609, 1504, (void *)0x800A5E28},
    {610, 1512, (void *)0x800A5E28},
    {611, 1520, (void *)0x800A5E28},
    {612, 1528, (void *)0x800A5E28},
    {613, 681, (void *)0x800A5E28},
    {614, 1540, (void *)0x800A5E28},
    {615, 1544, (void *)0x800A5E28},
    {616, 1556, (void *)0x800A5E28},
    {617, 1564, (void *)(s32)func_800A6024},
    {618, 1572, (void *)0x800A5EE4},
    {619, 1619, (void *)0x800A6138},
    {620, 1621, (void *)0x800A62B8},
    {621, 1623, (void *)0x800A6424},
    {622, 1624, (void *)0x800A5E6C},
    {623, 1626, (void *)0x800A5E28},
    {624, 522, (void *)0x800A5E2C},
    {625, 524, (void *)0x800A5E2C},
    {626, 525, (void *)0x800A5EC0},
    {627, 535, (void *)0x800A5E2C},
    {628, 564, (void *)0x800A5E2C},
    {629, 590, (void *)0x800A5E2C},
    {630, 592, (void *)0x800A62C8},
    {631, 593, (void *)0x800A5E28},
    {632, 595, (void *)0x800A605C},
    {633, 624, (void *)0x800A5E28},
    {634, 667, (void *)0x800A5E28},
    {635, 672, (void *)0x800A5E28},
    {636, 697, (void *)0x800A5E28},
    {637, 701, (void *)0x800A5E28},
    {638, 658, (void *)0x800A5E28},
    {639, 702, (void *)0x800A634C},
    {640, 711, (void *)0x800A5E28},
    {641, 809, (void *)0x800A5E2C},
    {642, 810, (void *)0x800A5E28},
    {643, 826, (void *)0x800A5E28},
    {644, 830, (void *)0x800A5E28},
    {645, 874, (void *)0x800A5E28},
    {646, 875, (void *)0x800A5E28},
    {647, 876, (void *)0x800A6160},
    {648, 877, (void *)0x800A6DD0},
    {649, 937, (void *)0x800A5E28},
    {650, 1030, (void *)0x800A5E2C},
    {651, 1077, (void *)0x800A6068},
    {652, 1100, (void *)0x800A5E2C},
    {653, 1120, (void *)0x800A5E28},
    {654, 1121, (void *)0x800A5E28},
    {655, 1122, (void *)0x800A5E28},
    {656, 1123, (void *)0x800A5E28},
    {657, 1140, (void *)0x800A5E28},
    {658, 1150, (void *)0x800A5E28},
    {659, 1189, (void *)0x800A5E28},
    {660, 1197, (void *)0x800A5E28},
    {661, 1205, (void *)0x800A5E84},
    {662, 1209, (void *)0x800A5E2C},
    {663, 1235, (void *)0x800A5E28},
    {664, 1236, (void *)0x800A5E28},
    {665, 1241, (void *)0x800A5E2C},
    {666, 1245, (void *)0x800A6084},
    {667, 1249, (void *)0x800A5E2C},
    {668, 1261, (void *)0x800A5F1C},
    {669, 1273, (void *)0x800A5E28},
    {670, 1278, (void *)0x800A5E28},
    {671, 1300, (void *)0x800A5E28},
    {672, 1304, (void *)0x800A5E2C},
    {673, 1312, (void *)0x800A5E2C},
    {674, 1316, (void *)0x800A5E2C},
    {675, 1320, (void *)0x800A5E2C},
    {676, 1324, (void *)0x800A5E2C},
    {677, 1328, (void *)0x800A5E28},
    {678, 1332, (void *)0x800A5E28},
    {679, 1351, (void *)0x800A61F4},
    {680, 1352, (void *)0x800A5E2C},
    {681, 1353, (void *)0x800A5E28},
    {682, 1354, (void *)0x800A5E28},
    {683, 1355, (void *)0x800A5E28},
    {684, 1360, (void *)0x800A5E28},
    {685, 1386, (void *)0x800A5E74},
    {686, 1390, (void *)0x800A7460},
    {687, 1394, (void *)0x800A5E28},
    {688, 1398, (void *)0x800A5E80},
    {689, 1406, (void *)0x800A5E28},
    {690, 1410, (void *)0x800A5E28},
    {691, 1414, (void *)0x800A5E28},
    {692, 1418, (void *)0x800A5E28},
    {693, 1422, (void *)0x800A5E28},
    {694, 1426, (void *)0x800A5E28},
    {695, 1431, (void *)0x800A5E28},
    {696, 1435, (void *)0x800A5E28},
    {697, 1439, (void *)0x800A5E28},
    {698, 1443, (void *)0x800A5E28},
    {699, 1447, (void *)0x800A5E28},
    {700, 1451, (void *)0x800A5E80},
    {701, 1455, (void *)0x800A5E28},
    {702, 1459, (void *)0x800A5E84},
    {703, 1463, (void *)0x800A5E28},
    {704, 1467, (void *)0x800A5E28},
    {705, 1471, (void *)0x800A5F54},
    {706, 1475, (void *)0x800A5F54},
    {707, 1479, (void *)0x800A5E28},
    {708, 1483, (void *)0x800A5E28},
    {709, 1487, (void *)0x800A5E28},
    {710, 1491, (void *)0x800A5E2C},
    {711, 1495, (void *)0x800A5E68},
    {712, 1503, (void *)0x800A5E28},
    {713, 1508, (void *)0x800A5E28},
    {714, 1516, (void *)0x800A5E28},
    {715, 1524, (void *)0x800A5E28},
    {716, 1532, (void *)0x800A5E28},
    {717, 1536, (void *)0x800A5E28},
    {718, 1543, (void *)0x800A5E28},
    {719, 1552, (void *)0x800A5E28},
    {720, 1560, (void *)0x800A5E28},
    {721, 1568, (void *)(s32)func_800A6024},
    {722, 1588, (void *)0x800A5EE4},
    {723, 1620, (void *)0x800A6138},
    {724, 1622, (void *)0x800A62B8},
    {725, 1625, (void *)0x800A5EA0},
    {726, 1627, (void *)0x800A5E28},
    {727, 489, (void *)0x800A75B0},
    {728, 490, (void *)0x800A66B0},
    {729, 491, (void *)0x800A631C},
    {730, 1631, (void *)0x800A6654},
    {731, 1635, (void *)0x800A69CC},
    {732, 1639, (void *)0x800A6B44},
    {733, 1643, (void *)0x800A6418},
    {734, 1647, (void *)0x800A6184},
    {735, 1651, (void *)0x800A6160},
    {736, 1655, (void *)0x800A5F50},
    {737, 1659, (void *)0x800A5F58},
    {738, 1665, (void *)0x800A5F50},
    {739, 1669, (void *)0x800A5F50},
    {740, 1673, (void *)0x800A5F50},
    {741, 1697, (void *)0x800A5F50},
    {742, 1701, (void *)0x800A5F50},
    {743, 1705, (void *)0x800A5F50},
    {744, 1709, (void *)0x800A5F54},
    {745, 1713, (void *)0x800A5F54},
    {746, 1677, (void *)0x800A5F54},
    {747, 1690, (void *)0x800A5F54},
    {748, 1691, (void *)0x800A5F54},
    {749, 1692, (void *)0x800A5F54},
    {750, 1693, (void *)0x800A5F54},
    {0, 0, 0},
};
#endif
ScriptTimer D_8009A424 = {0, 0, func_800914C0, func_800914F0};
void (*D_8009A434[])() = {
    func_80091648, func_80091520, func_800915B0, func_800915FC,
    func_800916B4,
};
/* The script commands (func_800916E8), up to the first id 0. Most of their
   functions are the stage overlay's, at fixed addresses, and they take
   different arguments */
#if VERSION_US
ScriptCommand D_8009A448[] = {
    {800, (void *)0x800A5E50, (void *)0x800A5E04},
    {801, (void *)0x800A6360, (void *)0x800A6314},
    {802, (void *)0x800A5220, 0},
    {803, (void *)func_800878F0, (void *)func_80087918},
    {804, (void *)func_800878F0, (void *)func_80087918},
    {805, (void *)func_800878F0, (void *)func_80087918},
    {806, (void *)func_800878F0, (void *)func_80087918},
    {807, (void *)0x800A53D4, (void *)0x800A5404},
    {808, (void *)0x800A5120, (void *)0x800A50E8},
    {809, (void *)0x800A4FCC, (void *)0x800A4F94},
    {810, (void *)0x800A50C0, (void *)0x800A500C},
    {811, (void *)0x800A595C, (void *)0x800A5850},
    {812, 0, (void *)0x800A5D4C},
    {813, (void *)func_80083470, (void *)func_80082F84},
    {814, (void *)0x800A5270, (void *)0x800A5140},
    {815, (void *)0x800A50A4, (void *)0x800A5038},
    {816, (void *)0x800A50F4, 0},
    {817, (void *)0x800A5128, 0},
    {818, (void *)0x800A5160, 0},
    {819, (void *)0x800A5198, 0},
    {820, (void *)0x800A51D0, 0},
    {821, (void *)0x800A5208, 0},
    {822, (void *)0x800A5240, 0},
    {823, (void *)0x800A5278, 0},
    {824, (void *)0x800A52B0, 0},
    {825, (void *)0x800A52E8, 0},
    {826, (void *)func_80083930, (void *)func_800838BC},
    {827, (void *)0x800A5150, (void *)0x800A50DC},
    {828, (void *)0x800A4ED4, 0},
    {829, (void *)0x800A4EEC, (void *)0x800A4EB4},
    {830, (void *)0x800A4E8C, (void *)0x800A4E54},
    {831, (void *)0x800A5498, (void *)0x800A545C},
    {832, (void *)0x800A5A1C, (void *)0x800A59E0},
    {833, (void *)0x800A4E24, (void *)0x800A4E54},
    {834, (void *)0x800A4E24, (void *)0x800A4E54},
    {835, (void *)0x800A509C, 0},
    {836, 0, (void *)0x800A5044},
    {837, 0, (void *)0x800A5038},
    {838, (void *)0x800A62A8, 0},
    {839, (void *)0x800A53D4, 0},
    {840, 0, (void *)0x800A5288},
    {841, 0, (void *)0x800A4E28},
    {842, 0, (void *)0x800A503C},
    {843, 0, (void *)0x800A503C},
    {844, 0, (void *)0x800A503C},
    {845, 0, (void *)0x800A5680},
    {846, 0, (void *)0x800A5034},
    {847, 0, (void *)0x800A51C8},
    {848, (void *)0x800A5758, (void *)0x800A5644},
    {849, (void *)0x800A505C, 0},
    {850, 0, (void *)0x800A4EDC},
    {851, 0, (void *)0x800A4EDC},
    {852, (void *)0x800A6190, 0},
    {853, (void *)0x800A4E78, 0},
    {0, 0, 0},
    {0, 0, (void *)func_800917D8},
};
#elif VERSION_EU
ScriptCommand D_8009A448[] = {
    {800, (void *)0x800A6F8C, (void *)0x800A6F40},
    {801, (void *)0x800A749C, (void *)0x800A7450},
    {802, (void *)0x800A635C, 0},
    {803, (void *)func_800878F0, (void *)func_80087918},
    {804, (void *)func_800878F0, (void *)func_80087918},
    {805, (void *)func_800878F0, (void *)func_80087918},
    {806, (void *)func_800878F0, (void *)func_80087918},
    {807, (void *)0x800A6510, (void *)0x800A6540},
    {808, (void *)0x800A625C, (void *)0x800A6224},
    {809, (void *)0x800A6108, (void *)0x800A60D0},
    {810, (void *)0x800A61FC, (void *)0x800A6148},
    {811, (void *)0x800A6A98, (void *)0x800A698C},
    {812, 0, (void *)0x800A6E88},
    {813, (void *)func_80083470, (void *)func_80082F84},
    {814, (void *)0x800A63AC, (void *)0x800A627C},
    {815, (void *)0x800A61E0, (void *)0x800A6174},
    {816, (void *)0x800A6230, 0},
    {817, (void *)0x800A6264, 0},
    {818, (void *)0x800A629C, 0},
    {819, (void *)0x800A62D4, 0},
    {820, (void *)0x800A630C, 0},
    {821, (void *)0x800A6344, 0},
    {822, (void *)0x800A637C, 0},
    {823, (void *)0x800A63B4, 0},
    {824, (void *)0x800A63EC, 0},
    {825, (void *)0x800A6424, 0},
    {826, (void *)func_80083930, (void *)func_800838BC},
    {827, (void *)0x800A628C, (void *)0x800A6218},
    {828, (void *)0x800A6010, 0},
    {829, (void *)0x800A6028, (void *)0x800A5FF0},
    {830, (void *)0x800A5FC8, (void *)0x800A5F90},
    {831, (void *)0x800A65D4, (void *)0x800A6598},
    {832, (void *)0x800A6B58, (void *)0x800A6B1C},
    {833, (void *)0x800A5F60, (void *)0x800A5F90},
    {834, (void *)0x800A5F60, (void *)0x800A5F90},
    {835, (void *)0x800A61D8, 0},
    {836, 0, (void *)0x800A6180},
    {837, 0, (void *)0x800A6174},
    {838, (void *)0x800A73E4, 0},
    {839, (void *)0x800A6510, 0},
    {840, 0, (void *)0x800A63C4},
    {841, 0, (void *)0x800A5F64},
    {842, 0, (void *)0x800A6178},
    {843, 0, (void *)0x800A6178},
    {844, 0, (void *)0x800A6178},
    {845, 0, (void *)0x800A67BC},
    {846, 0, (void *)0x800A6170},
    {847, 0, (void *)0x800A6304},
    {848, (void *)0x800A6894, (void *)0x800A6780},
    {849, (void *)0x800A6198, 0},
    {850, 0, (void *)0x800A6018},
    {851, 0, (void *)0x800A6018},
    {852, (void *)0x800A72CC, 0},
    {853, (void *)0x800A5FB4, 0},
    {854, (void *)0x800A609C, 0},
    {855, (void *)0x800A639C, 0},
    {0, 0, 0},
    {0, 0, (void *)func_800917D8},
};
#endif
void (*D_8009A6E8)() = func_80091910;
void (*D_8009A6EC[])() = {
    func_80091A4C, func_80091854,
};
s32 D_8009A6F4[] = {
    2000, 3, 4, 6,
    9, 18,
};
FieldMap D_8009A70C = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    0,
    0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    func_80091B78,
    func_80091BC0,
    func_80091F4C,
    func_8009204C,
    func_80091B90,
    func_80091BB4,
    func_80091D3C,
};
s32 D_8009A768 = -1;
Point D_8009A76C[][8] = {
    {
        {0, 2048},
        {-2896, 1448},
        {-4096, 0},
        {-2896, -1448},
        {0, -2048},
        {2896, -1448},
        {4096, 0},
        {2896, 1448},
    },
    {
        {599, 3405},
        {-2048, 3368},
        {-3496, 1358},
        {-2896, -1448},
        {-600, -3405},
        {2048, -3368},
        {3495, -1358},
        {2896, 1448},
    },
    {
        {155, 2865},
        {-2676, 2606},
        {-3940, 818},
        {-2896, -1448},
        {-156, -2866},
        {2676, -2606},
        {3939, -819},
        {2896, 1448},
    },
    {
        {68, 2616},
        {-2799, 2254},
        {-4027, 569},
        {-2896, -1448},
        {-69, -2618},
        {2797, -2254},
        {4026, -571},
        {2896, 1448},
    },
    {
        {273, 3081},
        {-2509, 2911},
        {-3822, 1034},
        {-2896, -1448},
        {-274, -3082},
        {2509, -2911},
        {3821, -1035},
        {2896, 1448},
    },
    {
        {344, 3178},
        {-2409, 3047},
        {-3751, 1130},
        {-2896, -1448},
        {-345, -3179},
        {2409, -3047},
        {3750, -1132},
        {2896, 1448},
    },
    {
        {9, 2271},
        {-2882, 1764},
        {-4086, 224},
        {-2896, -1448},
        {-10, -2272},
        {2882, -1764},
        {4085, -225},
        {2896, 1448},
    },
};
u8 D_8009A92C[] = {
    0x00, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01,
};
s16 D_8009A934 = 0;
Point D_8009A938 = {0, 0};
u8 *D_8009A940 = NULL;
s32 D_8009A944 = 0;
Point FIELDSTG_tiles[5][6] = {{{0}}};
s32 D_8009AA38 = 0;
s32 D_8009AA3C = 0;
RECT D_8009AA40 = {0, 0, 0, 0};
#if VERSION_US
u16 D_8009AA48[] = {
    0x0000, 0x0000,
};
#elif VERSION_EU
u16 D_8009AA48[] = {
    0x0000, 0x4E49,
};
#endif
Box D_8009AA4C[20] = {{0}};
s32 D_8009AB8C = 0;
