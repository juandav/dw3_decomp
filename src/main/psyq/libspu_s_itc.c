#include "psyq.h"

long func_8003A588(long event);

long SpuIsTransferCompleted(long flag) {
    long ret;

    if (D_8005B9B8 == 1 || D_8005BA5C == 1) {
        return 1;
    }
    ret = func_8003A588(D_8005B9B0);
    if (flag == 1) {
        while (ret == 0) {
            ret = func_8003A588(D_8005B9B0);
        }
        ret = 1;
        D_8005BA5C = ret;
    } else if (ret == 1) {
        D_8005BA5C = ret;
    }
    return ret;
}

OBJECT_END();
