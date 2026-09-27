#include "psyq.h"

void *McrdGetGlobalStructure(void);
void _clr_card_event(void);
long _get_card_event_x(void);

long MemCardUnformat(long chan) {
    char buf[128];
    int i;

    if (((McrdGlobal *)McrdGetGlobalStructure())->unk0 != 0) {
        printf("Access Denied. : system busy\n");
        return -1;
    }
    for (i = 0; i < 128; i++) {
        buf[i] = -1;
    }
    for (i = 0; i < 15; i++) {
        _clr_card_event();
        func_8003D6A8();
        func_8003D698(chan, i, buf);
        if (_get_card_event_x() != 0) {
            return 0;
        }
    }
    return 1;
}

OBJECT_END();
