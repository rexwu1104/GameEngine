#ifndef BACKENDLOADER_H
#define BACKENDLOADER_H

#define Func(ret, func_name, ...) ret(*func_name)(__VA_ARGS__)
#define AssignFunc(func, symbol) (func = decltype(func)(symbol))
#define LoadFirstLibrary(libs, handle) for (int i=0; i<libs.size() && !handle; i++) { \
    if (handle = load(libs[i])) std::cout << "Load dll at " << libs[i] << std::endl; \
    }

#if defined(_WIN32)
    #include <windows.h>
	#define LOAD_LIB(path) LoadLibrary(path)
    #define GET_SYMBOL(handle, name) GetProcAddress(handle, name)
	#define UNLOAD_LIB(path) FreeLibrary(path)
    #define HANDLE HMODULE
    #define SYMBOL FARPROC
    #define CODE BOOL
    #define EXT ".dll"
    #define PRE ""
#elif defined(__APPLE__) && defined(__MACH__)
    #include <dlfcn.h>
	#define LOAD_LIB(path) dlopen(path, RTLD_LAZY)
    #define GET_SYMBOL(handle, name) dlsym(handle, name)
    #define UNLOAD_LIB(path) dlclose(path)
    #define HANDLE void*
    #define SYMBOL void*
    #define CODE int
    #define EXT ".dylib"
    #define PRE "lib"
#elif defined(__linux__)
    #include <dlfcn.h>
	#define LOAD_LIB(path) dlopen(path, RTLD_LAZY)
    #define GET_SYMBOL(handle, name) dlsym(handle, name)
    #define UNLOAD_LIB(path) dlclose(path)
    #define HANDLE void*
    #define SYMBOL void*
    #define CODE int
    #define EXT ".so"
    #define PRE "lib"
#else
    #error "Unsupport Platform"
#endif
#include <game_engine/platform/Window.h>

class Backend {
private:
    const std::vector<const char*> dlls = {
#if defined(OpenGL_ENABLE)
        "./" PRE "GameEngine_OpenGL_Backend_shared" EXT,
#endif
#if defined(Vulkan_ENABLE)
        "./" PRE "GameEngine_Vulkan_Backend_shared" EXT,
#endif
#if defined(Metal_ENABLE)
        "./" PRE "GameEngine_Metal_Backend_shared" EXT,
#endif
#if defined(DirectX_ENABLE)
        "./" PRE "GameEngine_DirectX_Backend_shared" EXT,
#endif
    };

#if defined(_WIN32)
    HMODULE handle = nullptr;
#else
    void* handle = NULL;
#endif
public:
    /// create window with width and height
    Func(game_engine::Window*, new_window, int width, int height);

private:
    HANDLE load(const char* path) const;
    SYMBOL symbol(const char* name) const;
    CODE free() const;
public:
    Backend();

};

#endif
