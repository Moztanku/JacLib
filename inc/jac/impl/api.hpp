#pragma once

#include "jac/impl/compiler.hpp"

// Define the API macro to be used in the library
//  if compiled as static library, define as nothing
//  used for exporting symbols in shared library
#ifndef JAC_SHARED_LIB
    #define JAC_API
#else

    #if defined(MSVC_COMPILER)
        #ifdef JAC_BUILD_LIB
            #define JAC_API __declspec(dllexport)
        #else
            #define JAC_API __declspec(dllimport)
        #endif
    #endif
    
    #if defined(GCC_COMPILER) || defined(CLANG_COMPILER)
        #ifdef JAC_BUILD_LIB
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

// Used to define the implementation of a function as opposed to the declaration
//  mostly for convenience of grepping by either JAC_API or JAC_IMPL
//  used only in .cpp files, with JAC_API being in .hpp
#ifdef JAC_BUILD_LIB
    #define JAC_IMPL JAC_API
#else
    #define JAC_IMPL
#endif
