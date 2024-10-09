#ifndef BACKENDLOADER_H
#define BACKENDLOADER_H

#define Func(ret, func_name, ...) ret(*func_name)(__VA_ARGS__)
#define AssignFunc(func, symbol) (func = decltype(func)(symbol))
#define LoadFirstLibrary(libs, handle) for (int i=0; i<libs.size() && !handle; i++) { \
    if (handle = load(libs[i])) std::cout << "Load dll at " << libs[i] << std::endl; \
    }

#include <game_engine/platform/full.h>
#include <game_engine/gui/Window.h>

class Backend {
private:
    const std::vector<const char*> dlls = {
#if defined(OpenGL_ENABLE)
        "./libGameEngine_OpenGL_Backend_shared" EXT,
#endif
#if defined(Vulkan_ENABLE)
        "./libGameEngine_Vulkan_Backend_shared" EXT,
#endif
#if defined(Metal_ENABLE)
        "./libGameEngine_Metal_Backend_shared" EXT,
#endif
#if defined(DirectX_ENABLE)
        "./libGameEngine_DirectX_Backend_shared" EXT,
#endif
    };

    void* handle = nullptr;
public:
    /// create window with width and height
    Func(void, bind_window, game_engine::Window*);

private:
    void* load(const char* path) const;
    void* symbol(const char* name) const;
    int free() const;
public:
    Backend();

};

#endif
