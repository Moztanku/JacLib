#pragma once

// Detect the compiler being used
//  used to define the JAC_API macro but maybe will be used for other things
#if defined(_MSC_VER) && !defined(__llvm__) && !defined(__INTEL_COMPILER)
    #define MSVC_COMPILER
#elif defined(__GNUC__) && !defined(__clang__)
    #define GCC_COMPILER
#elif defined(__clang__)
    #define CLANG_COMPILER
#elif defined(__INTEL_COMPILER)
    #warning "Intel compiler not supported, let's hope it works"
    #define INTEL_COMPILER
#else
    #warning "Unknown compiler, let's hope it works"
    #define UNKNOWN_COMPILER
#endif
