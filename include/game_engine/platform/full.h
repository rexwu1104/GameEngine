#ifndef FULL_H
#define FULL_H

#if defined(_WIN32)
#   include <game_engine/platform/win32/constants.h>
#   include <game_engine/platform/win32/WindowHandle.h>
#elif defined(__APPLE__) && defined(__MACH__)
#   include <game_engine/platform/drawin/constants.h>
#elif defined(__linux__)
#   include <game_engine/platform/linux/constants.h>
#else
    #error "Unsupport Platform"
#endif

#endif
