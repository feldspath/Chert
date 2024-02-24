#pragma once

#ifdef CHERT_PLATFORM_WINDOWS
    #ifdef CHERT_BUILD_DLL
        #define CHERT_API __declspec(dllexport)
    #else
        #define CHERT_API __declspec(dllimport)
    #endif 
#else
    #error Chert only supports Windows...
#endif
