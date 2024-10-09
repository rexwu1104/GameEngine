#include <game_engine/gui/Window.h>
#include <game_engine/platform/full.h>

#include <iostream>
namespace game_engine {
    std::vector<void*> Window::handles;
    Window::Window(const Builder* builder) :
        width(builder->get_width()),
        height(builder->get_height()),
        standard_alone(builder->get_standard_alone()) {
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

    Window::Builder* Window::Builder::size(const int width, const int height) {
        this->_width = width;
        this->_height = height;
        return this;
    }

    Window::Builder* Window::Builder::title(const char *title) {
        this->_title = title;
        return this;
    }

    Window::Builder* Window::Builder::standard_alone(const bool standard_alone) {
        this->_standard_alone = standard_alone;
        return this;
    }

    Window::Builder *Window::Builder::drop_file(bool drop_file) {
        this->_drop_file = drop_file;
        return this;
    }

    Window* Window::Builder::build() const {
        std::cout << "Window::Builder::build()" << std::endl;
        return new WindowHandle(this);
    }
}