#ifndef GUARD_CONFIG_H
#define GUARD_CONFIG_H

// In the Generation 3 games, Asserts were used in various debug builds.
// Ruby/Sapphire and Emerald do not have these asserts while Fire Red
// still has them in the ROM. This is because the developers forgot
// to define NDEBUG before release, however this has been changed as
// Ruby's actual debug build does not use the AGBPrint features.
#define NDEBUG

// To enable print debugging, comment out "#define NDEBUG". This allows
// the various AGBPrint functions to be used. (See include/gba/isagbprint.h).
// Some emulators support a debug console window: uncomment NoCashGBAPrint()
// and NoCashGBAPrintf() in libisagbprn.c to use no$gba's own proprietary
// printing system. Use NoCashGBAPrint() and NoCashGBAPrintf() like you
// would normally use AGBPrint() and AGBPrintf().

#define ENGLISH

//#ifdef ENGLISH
//#define UNITS_IMPERIAL
//#else
//#define UNITS_METRIC
//#endif
#define UNITS_METRIC

// Uncomment to fix some identified minor bugs
//#define BUGFIX

// Various undefined behavior bugs may or may not prevent compilation with
// newer compilers. So always fix them when using a modern compiler.
#if MODERN || defined(BUGFIX)
#ifndef UBFIX
#define UBFIX
#endif
#endif

// Kaisa's configuration
// General configuration
#define CONF_ALLOW_RUNNING_INDOORS TRUE

// % chance for a Wild Encounter to be a double battle (if able) for each wild area type (0 to 100).
#define CONF_DOUBLE_WILD_CHANCE_LAND       0
#define CONF_DOUBLE_WILD_CHANCE_WATER      0
#define CONF_DOUBLE_WILD_CHANCE_ROCKS      0
#define CONF_DOUBLE_WILD_CHANCE_FISHING    0
#define CONF_DOUBLE_WILD_CHANCE_DARK_GRASS 20

// Game start
#define CONF_FIRST_BATTLE_SPECIES  SPECIES_POOCHYENA
#define CONF_FIRST_BATTLE_LEVEL    4

#endif // GUARD_CONFIG_H
