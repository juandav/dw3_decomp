#ifndef WFIGHTMN_H
#define WFIGHTMN_H

/* WFIGHTMN.PRO: the battle's sub-overlay. FIGHTSTG loads it (file 0x1FA)
   at STAGE_VRAM for a normal battle, and WFIGHTTS in its place for the
   battle test. */

#include "game.h"

/* The item a partner can equip that makes FIGHTSTG's func_8009B7A4 act on
   it at the start of the battle */
#define WFIGHTMN_ITEM 0x140

#endif /* WFIGHTMN_H */
