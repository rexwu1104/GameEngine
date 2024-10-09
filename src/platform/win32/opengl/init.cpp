#include <GL/gl.h>
#include <iostream>
#include <game_engine/backend/opengl/init.h>

#if defined(_WIN32)
void* createGLContext(void* handle) {
    PIXELFORMATDESCRIPTOR pfd;
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 24;
    pfd.iLayerType = PFD_MAIN_PLANE;

    const HDC hdc = GetDC(static_cast<HWND>(handle));
    SetPixelFormat(hdc, ChoosePixelFormat(hdc, &pfd), &pfd);

    wglMakeCurrent(hdc, wglCreateContext(hdc));
    return hdc;
}

void* loadExtension(const char* name) {
    auto pointer = wglGetProcAddress(name);
    if (!pointer) {
        std::cerr << "Failed to load OpenGL extension function " << name << "!" << std::endl;
        exit(1);
    }

    return (void*)(pointer);
}
#elif defined(__APPLE__) && defined(__MACH__)

#else

#endif