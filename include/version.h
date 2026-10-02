#ifndef VERSION_H
#define VERSION_H

/*
 * The version of the game being built. The Makefile passes exactly one
 * -DVERSION_<VERSION> (make VERSION=eu gives -DVERSION_EU); here every
 * version's macro becomes 0 or 1, so that code tests them with #if:
 *
 *     #if VERSION_EU
 *     #if VERSION_US || VERSION_EU
 *
 * never with #ifdef or defined(), which can't tell a version that is off
 * from a misspelt one (-Wundef warns about the misspelling in #if). A
 * condition names the versions it is for: the versions have no order.
 * A new version gets its line here and in the Makefile's VERSIONS.
 */
#if defined(VERSION_US) + defined(VERSION_EU) != 1
#error "build with exactly one of -DVERSION_US and -DVERSION_EU, as make VERSION=<version> does"
#endif

#ifndef VERSION_US
#define VERSION_US 0
#endif
#ifndef VERSION_EU
#define VERSION_EU 0
#endif

#endif /* VERSION_H */
