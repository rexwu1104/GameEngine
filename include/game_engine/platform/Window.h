#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <vector>

namespace game_engine {

class Window {
private:
    int width, height;
protected:
    static std::vector<void*> handles;
    bool standard_alone;
public:
    class Builder {
    private:
        int width = 0, height = 0;
        const char* title;
        bool standard_alone;
    protected:
        friend class Window;
        friend class WindowHandle;
        int get_width() const { return width; };
        int get_height() const { return height; };
        const char* get_title() const { return title; };
        bool get_standard_alone() const { return standard_alone; };
    public:
        Builder* set_size(int width, int height);
        Builder* set_title(const char* title);
        Builder* set_standard_alone(bool standard_alone);

        Window* build() const;
    };

    explicit Window(const Builder* builder);

    static int wait_for_exit() {
        listen_global();

        // std::cout << "handles closed" << std::endl;
        return error();
    }

    static bool is_empty();
    static void remove_window(void* handle);
    virtual void* get_handle() = 0;

    virtual ~Window() = default;

    static void listen_global();
    static int error();
};

}

extern "C" inline game_engine::Window* create_window(const game_engine::Window::Builder* builder) {
    return builder->build();
}

#endif
