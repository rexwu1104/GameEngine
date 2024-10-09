#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <windows.h>

#define LOAD_LIB(path) LoadLibraryA(path)
#define GET_SYMBOL(handle, name) (void*)GetProcAddress((HMODULE)handle, name)
#define UNLOAD_LIB(handle) FreeLibrary((HMODULE)handle)
#define EXT ".dll"

#endif
