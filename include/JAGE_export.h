
#ifndef JAGE_API_H
#define JAGE_API_H

#ifdef JAGE_STATIC_DEFINE
#  define JAGE_API
#  define JAGE_NO_EXPORT
#else
#  ifndef JAGE_API
#    ifdef JAGE_EXPORTS
        /* We are building this library */
#      define JAGE_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define JAGE_API __declspec(dllimport)
#    endif
#  endif

#  ifndef JAGE_NO_EXPORT
#    define JAGE_NO_EXPORT 
#  endif
#endif

#ifndef JAGE_DEPRECATED
#  define JAGE_DEPRECATED __declspec(deprecated)
#endif

#ifndef JAGE_DEPRECATED_EXPORT
#  define JAGE_DEPRECATED_EXPORT JAGE_API JAGE_DEPRECATED
#endif

#ifndef JAGE_DEPRECATED_NO_EXPORT
#  define JAGE_DEPRECATED_NO_EXPORT JAGE_NO_EXPORT JAGE_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef JAGE_NO_DEPRECATED
#    define JAGE_NO_DEPRECATED
#  endif
#endif

#endif /* JAGE_API_H */
