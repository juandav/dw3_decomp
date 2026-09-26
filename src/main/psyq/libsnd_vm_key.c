#include "psyq.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_vm_key", _SsVmKeyOn);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_vm_key", _SsVmKeyOff);

INCLUDE_ASM("asm/main/nonmatchings/psyq/libsnd_vm_key", _SsVmSeKeyOn);

void _SsVmSeKeyOff(short vab, short prog, u_short note) {
    _SsVmKeyOff(0x21, vab, prog, note);
}

OBJECT_END();
