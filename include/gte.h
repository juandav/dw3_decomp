#ifndef GTE_H
#define GTE_H

/* The GTE instructions that C can't say, as the SDK's inline_c.h has them
   but with the real encodings in place of the ones DMPSX patches. */

/* the interpolation factor (IR0) */
#define gte_lddp(r0) __asm__ volatile(                                      \
    "mtc2 %0, $8"                                                           \
    :                                                                       \
    : "r"(r0))

/* an SVECTOR into IR1-IR3 */
#define gte_ldsv(r0) __asm__ volatile(                                      \
    "lhu $12, 0(%0);"                                                       \
    "lhu $13, 2(%0);"                                                       \
    "lhu $14, 4(%0);"                                                       \
    "mtc2 $12, $9;"                                                         \
    "mtc2 $13, $10;"                                                        \
    "mtc2 $14, $11"                                                         \
    :                                                                       \
    : "r"(r0)                                                               \
    : "$12", "$13", "$14")

/* IR1-IR3 = IR0 * IR1-IR3 >> 12 */
#define gte_gpf12() __asm__ volatile(                                       \
    "nop;"                                                                  \
    "nop;"                                                                  \
    ".word 0x4B98003D")

/* IR1-IR3 into an SVECTOR */
#define gte_stsv(r0) __asm__ volatile(                                      \
    "mfc2 $12, $9;"                                                         \
    "mfc2 $13, $10;"                                                        \
    "mfc2 $14, $11;"                                                        \
    "sh $12, 0(%0);"                                                        \
    "sh $13, 2(%0);"                                                        \
    "sh $14, 4(%0)"                                                         \
    :                                                                       \
    : "r"(r0)                                                               \
    : "$12", "$13", "$14", "memory")

#endif /* GTE_H */
