#ifndef YAKS_YAKS_EXPORT_H
#define YAKS_YAKS_EXPORT_H

#include "yaks/version.hpp"

#ifdef __GNUC__
#define EXPORT_SPEC  //__attribute__ ((visibility("default")))
#define IMPORT_SPEC  //__attribute__ ((visibility("hidden")))
#endif 

#ifdef _WIN32
#define EXPORT_SPEC __declspec(dllexport)
#define IMPORT_SPEC __declspec(dllimport)
#pragma warning( disable: 4290 ) // exception specification non-implmented
#pragma warning( disable: 4251 ) // template export warning
#pragma warning( disable: 4996 ) // allow POSIX 
#endif

#if !defined(EXPORT_SPEC) || !defined(IMPORT_SPEC)
#error Unkown compiler
#endif

#ifdef YAKS_MAKE_DLL
#pragma message ("Create shared yaks lib with version "YAKS_VERSION_ )
#define YAKS_EXPORT EXPORT_SPEC //__declspec(dllexport)
#endif

#ifdef YAKS_STATIC
#pragma message ("Create static yaks lib with version "YAKS_VERSION_)
#define YAKS_EXPORT 
#endif


#ifdef YAKS_DLL
#pragma message ("Link with shared yaks lib " YAKS_VERSION_ "(dll required)")
#define YAKS_EXPORT IMPORT_SPEC //__declspec(dllimport)
#elif !defined(YAKS_STATIC) && !defined(YAKS_MAKE_DLL) 
#pragma message ("You must define YAKS_DLL when compile your code with dll version yaks lib.")
#pragma message ("If you are using a static version, just ignore this warning.")
#pragma message ("Link with static yaks lib " YAKS_VERSION_)
#define YAKS_EXPORT
#endif


#ifndef YAKS_EXPORT
#error export macro error: YAKS_EXPORT was not defined
#endif

#endif
