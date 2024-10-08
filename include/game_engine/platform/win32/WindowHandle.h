#ifndef WINDOWHANDLE_H
#define WINDOWHANDLE_H

#include <Windows.h>
#include <game_engine/platform/Window.h>

namespace game_engine {
    class WindowHandle final : public Window {
    private:
        HWND hWnd;

        static LRESULT CALLBACK OnMessage(HWND, UINT, WPARAM, LPARAM);

        void *get_handle() override;

        void set_hWnd(HWND hWnd);
    public:
        explicit WindowHandle(const Builder* builder);
    };
}

#endif