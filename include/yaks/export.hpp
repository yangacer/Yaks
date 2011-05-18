#ifndef YAKS_YAKS_EXPORT_H
#define YAKS_YAKS_EXPORT_H



#ifdef __GNUC__
#define EXPORT_SPEC  __attribute__ ((visibility("default")))
#define IMPORT_SPEC  __attribute__ ((visibility("hidden")))
#endif 

#ifdef __WIN32
#define EXPORT_SPEC __declspec(dllexport)
#define IMPORT_SPEC __declspec(dllimport)
#endif

#if !defined(EXPORT_SPEC) || !defined(IMPORT_SPEC)
#error Unkown compiler
#endif

#ifdef YAKS_MAKE_DLL
#warning Create shared yaks lib
#define YAKS_EXPORT EXPORT_SPEC //__declspec(dllexport)
#endif

#ifdef YAKS_STATIC
#warning Create static yaks lib
#define YAKS_EXPORT 
#endif


#ifdef YAKS_DLL
#warning Link with shared yaks lib (dll required)
#define YAKS_EXPORT IMPORT_SPEC //__declspec(dllimport)
#elif !defined(YAKS_STATIC) && !defined(YAKS_MAKE_DLL) 
#warning You must define YAKS_DLL when compile your code with dll version yaks lib.
#warning If you are using a static version, just ignore this warning.
#warning Link with static yaks lib
#define YAKS_EXPORT
#endif


#ifndef YAKS_EXPORT
#error export macro error: YAKS_EXPORT was not defined
#endif

#endif
