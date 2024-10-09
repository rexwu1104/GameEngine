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
    bool standard_alone = false;
public:
    class Builder {
    private:
        int _width = 0, _height = 0;
        const char* _title;
        bool _standard_alone;
        bool _drop_file;
    protected:
        friend class Window;
        friend class WindowHandle;
        int get_width() const { return _width; }
        int get_height() const { return _height; }
        const char* get_title() const { return _title; }
        bool get_standard_alone() const { return _standard_alone; }
        bool get_drop_file() const { return _drop_file; }
    public:
        Builder* size(int width, int height);
        Builder* title(const char* title);
        Builder* standard_alone(bool standard_alone);
        Builder* drop_file(bool drop_file);

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

    virtual void listen() = 0;
    static void listen_global();
    static int error();
};

}

extern "C" inline game_engine::Window* create_window(const game_engine::Window::Builder* builder) {
    return builder->build();
}

#endif
