#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <dlfcn.h>

#define LOAD_LIB(path) dlopen(path, RTLD_LAZY)
#define GET_SYMBOL(handle, name) dlsym(handle, name)
#define UNLOAD_LIB(handle) dlclose(handle)
#define EXT ".so"

#endif
