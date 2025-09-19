#pragma once

#if defined(_WIN32)
#   if defined(JAGE_EXPORT)
#       define JAGE_API __declspec(dllexport)
#   else
#       define JAGE_API __declspec(dllimport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#   define JAGE_API __attribute__((visibility("default")))
#else
#   define JAGE_API
#endif

