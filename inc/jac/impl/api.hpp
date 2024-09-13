#pragma once

#include "jac/impl/compiler.hpp"

#ifndef JACLIB_SHARED_LIB
    #define JAC_API
#else

    #if defined(MSVC_COMPILER)
        #ifdef JACLIB_BUILD_LIB
            #define JAC_API __declspec(dllexport)
        #else
            #define JAC_API __declspec(dllimport)
        #endif
    #endif
    
    #if defined(GCC_COMPILER) || defined(CLANG_COMPILER)
        #ifdef JACLIB_BUILD_LIB
            #define JAC_API __attribute__((visibility("default")))
        #else
            #define JAC_API
        #endif
    #endif

    #if defined(INTEL_COMPILER) || defined(UNKNOWN_COMPILER)
        #warning "Unsupported compiler, shared library may not compile."
        #define JAC_API
    #endif

#endif
