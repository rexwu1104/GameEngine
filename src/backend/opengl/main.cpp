#include <GL/gl.h>
#include <game_engine/gui/Window.h>
#include <game_engine/backend/opengl/init.h>
#include <game_engine/utils/export.h>

extern "C" _export void bind_window(game_engine::Window* window) {
    auto p = createGLContext(window->get_handle());

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#   if defined(_WIN32)
    SwapBuffers(static_cast<HDC>(p));
#   endif
}
