#include "psyq.h"
#include <libgte.h>
#include <libgs.h>

void GsGetTimInfo(u_long *im, GsIMAGE *tim) {
    u_long *next;

    tim->pmode = *im;
    if ((tim->pmode >> 3) & 1) {
        im++;
        next = im + (*im >> 2);
        im++;
        tim->cx = ((u_short *)im)[0];
        tim->cy = ((u_short *)im)[1];
        im++;
        tim->cw = ((u_short *)im)[0];
        tim->ch = ((u_short *)im)[1];
        im++;
        tim->clut = im;
        next++;
        tim->px = ((u_short *)next)[0];
        tim->py = ((u_short *)next)[1];
        next++;
        tim->pw = ((u_short *)next)[0];
        tim->ph = ((u_short *)next)[1];
        next++;
        tim->pixel = next;
    } else {
        im += 2;
        tim->px = ((u_short *)im)[0];
        tim->py = ((u_short *)im)[1];
        im++;
        tim->pw = ((u_short *)im)[0];
        tim->ph = ((u_short *)im)[1];
        im++;
        tim->pixel = im;
    }
}

OBJECT_END();
