/* the library calls _putchar without a prototype (no char conversion) */
#define _putchar _putchar_sdk
#include "psyq.h"
#undef _putchar

/* 4.3BSD-Tahoe _doprnt without stdio or floating point */

#define LONGINT 0x01
#define LONGDBL 0x02
#define SHORTINT 0x04
#define ALT 0x08
#define LADJUST 0x10
#define ZEROPAD 0x20
#define HEXPREFIX 0x40

#define BUF 40

#define __va_rounded_size(TYPE) (((sizeof(TYPE) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))
#define va_arg(AP, TYPE) (AP += __va_rounded_size(TYPE), *((TYPE *)(AP - __va_rounded_size(TYPE))))

#define todigit(c) ((c) - '0')
#define isascii(c) ((unsigned)(c) <= 0177)
#define isdigit(c) (D_800555C1[(u_char)(c)] & 4)

#define ARG()                                                                       \
    _ulong = flags & LONGINT ? va_arg(argp, long) :                                 \
             flags & SHORTINT ? va_arg(argp, short) : va_arg(argp, int);

void _putchar();
void *memchr();
int strlen();

int prnt(int fd, u_char *fmt0, char *argp) {
    u_char *fmt;
    int ch;
    int cnt;
    int n;
    char *t;
    u_long _ulong;
    int base;
    int dprec;
    int fieldsz;
    int flags;
    int fpprec;
    int prec;
    int realsz;
    int size;
    int width;
    char sign;
    char *digs;
    char buf[BUF];

    if (fmt0 == NULL) {
        return 0;
    }
    fmt = fmt0;
    digs = "0123456789abcdef";
    for (cnt = 0;; ++fmt) {
        if (!(ch = *fmt)) {
            _putchar_flash();
            return cnt;
        }
        if (ch != '%') {
            _putchar(ch);
            continue;
        }
        flags = 0;
        dprec = 0;
        fpprec = 0;
        width = 0;
        prec = -1;
        sign = '\0';

    rflag:
        switch (*++fmt) {
        case ' ':
            if (!sign) {
                sign = ' ';
            }
            goto rflag;
        case '#':
            flags |= ALT;
            goto rflag;
        case '*':
            if ((width = va_arg(argp, int)) >= 0) {
                goto rflag;
            }
            width = -width;
            /* FALLTHROUGH */
        case '-':
            flags |= LADJUST;
            goto rflag;
        case '+':
            sign = '+';
            goto rflag;
        case '.':
            if (*++fmt == '*') {
                n = va_arg(argp, int);
            } else {
                n = 0;
                while (isascii(*fmt) && isdigit(*fmt)) {
                    n = 10 * n + todigit(*fmt++);
                }
                --fmt;
            }
            prec = n < 0 ? -1 : n;
            goto rflag;
        case '0':
            flags |= ZEROPAD;
            goto rflag;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            n = 0;
            do {
                n = 10 * n + todigit(*fmt);
            } while (isascii(*++fmt) && isdigit(*fmt));
            width = n;
            --fmt;
            goto rflag;
        case 'L':
            flags |= LONGDBL;
            goto rflag;
        case 'h':
            flags |= SHORTINT;
            goto rflag;
        case 'l':
            flags |= LONGINT;
            goto rflag;
        case 'c':
            *(t = buf) = va_arg(argp, u_char);
            size = 1;
            sign = '\0';
            goto pforw;
        case 'D':
            flags |= LONGINT;
            /* FALLTHROUGH */
        case 'd':
        case 'i':
            ARG();
            if ((long)_ulong < 0) {
                _ulong = -_ulong;
                sign = '-';
            }
            base = 10;
            goto number;
        case 'n':
            if (flags & LONGINT) {
                *va_arg(argp, long *) = cnt;
            } else if (flags & SHORTINT) {
                *va_arg(argp, short *) = cnt;
            } else {
                *va_arg(argp, int *) = cnt;
            }
            break;
        case 'O':
            flags |= LONGINT;
            /* FALLTHROUGH */
        case 'o':
            ARG();
            base = 8;
            goto nosign;
        case 'p':
            _ulong = (u_long)va_arg(argp, void *);
            base = 16;
            goto nosign;
        case 's':
            if (!(t = va_arg(argp, char *))) {
                t = "(null)";
            }
            if (prec >= 0) {
                char *p;

                if (p = memchr(t, 0, prec)) {
                    size = p - t;
                    if (size > prec) {
                        size = prec;
                    }
                } else {
                    size = prec;
                }
            } else {
                size = strlen(t);
            }
            sign = '\0';
            goto pforw;
        case 'U':
            flags |= LONGINT;
            /* FALLTHROUGH */
        case 'u':
            ARG();
            base = 10;
            goto nosign;
        case 'X':
            digs = "0123456789ABCDEF";
            /* FALLTHROUGH */
        case 'x':
            ARG();
            base = 16;
            if (flags & ALT && _ulong != 0) {
                flags |= HEXPREFIX;
            }
        nosign:
            sign = '\0';
        number:
            if ((dprec = prec) >= 0) {
                flags &= ~ZEROPAD;
            }
            t = buf + BUF;
            if (_ulong != 0 || prec != 0) {
                do {
                    *--t = digs[_ulong % base];
                    _ulong /= base;
                } while (_ulong);
                digs = "0123456789abcdef";
                if (flags & ALT && base == 8 && *t != '0') {
                    *--t = '0';
                }
            }
            size = buf + BUF - t;
        pforw:
            fieldsz = size + fpprec;
            if (sign) {
                fieldsz++;
            }
            if (flags & HEXPREFIX) {
                fieldsz += 2;
            }
            realsz = dprec > fieldsz ? dprec : fieldsz;

            if ((flags & (LADJUST | ZEROPAD)) == 0 && width) {
                for (n = realsz; n < width; n++) {
                    _putchar(' ');
                }
            }
            if (sign) {
                _putchar(sign);
            }
            if (flags & HEXPREFIX) {
                _putchar('0');
                _putchar((char)*fmt);
            }
            if ((flags & (LADJUST | ZEROPAD)) == ZEROPAD) {
                for (n = realsz; n < width; n++) {
                    _putchar('0');
                }
            }
            for (n = fieldsz; n < dprec; n++) {
                _putchar('0');
            }
            n = size;
            while (--n >= 0) {
                _putchar(*t++);
            }
            while (--fpprec >= 0) {
                _putchar('0');
            }
            if (flags & LADJUST) {
                for (n = realsz; n < width; n++) {
                    _putchar(' ');
                }
            }
            cnt += width > realsz ? width : realsz;
            break;
        case '\0':
            _putchar_flash();
            return cnt;
        default:
            _putchar((char)*fmt);
            cnt++;
        }
    }
}

/* ASPSX padded the jump table at the end of the rodata as well */
__asm__(".section .rodata\n\t.align 4\n");

OBJECT_END();
