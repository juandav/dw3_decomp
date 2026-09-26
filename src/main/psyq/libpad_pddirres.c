#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pddirres", _padInitDirPort);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pddirres", func_80021388);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pddirres", func_800213F0);

void func_800214E4(PadPort *port) {
    u_char cmd = port->cmd;

    port->cmd = 0;
    port->prevCmd = cmd;
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pddirres", func_800214F4);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pddirres", func_800215B0);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pddirres", func_8002182C);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pddirres", func_8002184C);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pddirres", func_8002195C);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pddirres", _dirFailAuto);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libpad_pddirres", func_80021CA8);

OBJECT_END();
