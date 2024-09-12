#pragma once

#if defined(_MSC_VER) && !defined(__llvm__) && !defined(__INTEL_COMPILER)
    #define MSVC_COMPILER
#elif defined(__GNUC__) && !defined(__clang__)
    #define GCC_COMPILER
#elif defined(__clang__)
    #define CLANG_COMPILER
#elif defined(__INTEL_COMPILER)
    #define INTEL_COMPILER
#else
    #define UNKNOWN_COMPILER
#endif
