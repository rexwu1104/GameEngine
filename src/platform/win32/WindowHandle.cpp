#include <iostream>
#include <thread>
#include <string>
#include <game_engine/platform/win32/WindowHandle.h>

namespace game_engine {
    WindowHandle::WindowHandle(const Builder* builder): Window(builder), hWnd(nullptr) {
        const HINSTANCE hInstance = GetModuleHandle(nullptr);
        const std::string className = "Window_" + std::to_string(handles.size() - 1);
        std::cout << className << std::endl;

        WNDCLASS wc = {};
        wc.lpfnWndProc = OnMessage;
        wc.hInstance = hInstance;
        wc.lpszClassName = className.c_str();

        if (!RegisterClass(&wc)) {
            std::cerr << "RegisterClass failed!" << std::endl;
            exit(1);
        }

        set_hWnd(CreateWindowEx(
            0,
            className.c_str(),
            builder->get_title(),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, builder->get_width(), builder->get_height(),
            nullptr,
            nullptr,
            hInstance,
            nullptr));

        if (hWnd) {
            ShowWindow(hWnd, SW_SHOW);
        }
    }

    LRESULT CALLBACK WindowHandle::OnMessage(const HWND hwnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam) {
        switch (uMsg) {
            case WM_DESTROY:
                remove_window(hwnd);
            std::cout << "handles size: " << handles.size() << std::endl;
            if (is_empty())
                PostQuitMessage(0);
            return 0;
            default:
                return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    void WindowHandle::set_hWnd(const HWND hWnd) {
        this->hWnd = hWnd;
    }

    void* WindowHandle::get_handle() {
        return hWnd;
    }

    void Window::listen_global() {
        MSG msg = {};
        while (GetMessage(&msg, nullptr, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    int Window::error() {
        return GetLastError();
    }

}
