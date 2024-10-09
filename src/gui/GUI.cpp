#include <game_engine/GameEngine.h>

GUI::GUI() :
    events(std::queue<GUIEvent>()),
    backend(Backend()),
    window(nullptr) {
    std::cout << "Hello GameEngine." << std::endl;
}

int GUI::start() {
    return main_window();
}

int GUI::main_window() {
    const auto builder = new game_engine::Window::Builder();
    window = create_window(
        builder
            ->size(400, 400)
            ->title("Game Engine1")
            ->standard_alone(false)
    );

    delete builder;

    backend.bind_window(window);
    return game_engine::Window::wait_for_exit();
}
