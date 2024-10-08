#include <game_engine/platform/Window.h>
#if defined(_WIN32)
#include <game_engine/platform/win32/WindowHandle.h>
#elif defined(__APPLE__) && defined(__MACH__)
// macos
#else
// linux
#endif

#include <iostream>
namespace game_engine {
    std::vector<void*> Window::handles;
    Window::Window(const Builder* builder) :
        width(builder->get_width()),
        height(builder->get_height()) {
        handles.push_back(this);
    }

    bool Window::is_empty() {
        return handles.empty();
    }

    void Window::remove_window(void *handle) {
        const auto _handle = std::ranges::find(handles, handle, [](void *handle) { return static_cast<Window *>(handle)->get_handle(); });
        delete static_cast<Window *>(*_handle);
        handles.erase(_handle);
    }

    Window::Builder* Window::Builder::set_size(const int width, const int height) {
        this->width = width;
        this->height = height;
        return this;
    }

    Window::Builder* Window::Builder::set_title(const char *title) {
        this->title = title;
        return this;
    }

    Window::Builder* Window::Builder::set_standard_alone(const bool standard_alone) {
        this->standard_alone = standard_alone;
        return this;
    }

    Window* Window::Builder::build() const {
        std::cout << "Window::Builder::build()" << std::endl;
        return new WindowHandle(this);
    }
}