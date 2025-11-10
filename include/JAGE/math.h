#pragma once

#include "JAGE/core.h"

/**
 * 
 * 
 * MACRO FOR API EXPORT DEFINITIONS
 * 
 * 
 */
#ifdef _WIN32
#   ifdef JAGE_MATH_EXPORT
#       define JAGE_MATH_API __declspec(dllexport)
#   else
#       define JAGE_MATH_API __declspec(dllimport)
#   endif
#elif defined(__GNUC__) && __GNUC__ >= 4
#   define JAGE_MATH_API __attribute__((visibility("default")))
#else
#   define JAGE_MATH_API
#endif

namespace JAGE
{
    namespace Math
    {
        void JAGE_MATH_API translate();
    }
}
