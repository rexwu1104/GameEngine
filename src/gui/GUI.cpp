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
            ->set_size(400, 400)
            ->set_title("Game Engine")
            ->set_standard_alone(true)
    );
    create_window(
        builder
            ->set_size(300, 400)
            ->set_title("Game Engine")
            ->set_standard_alone(false)
    );
    create_window(
        builder
            ->set_size(300, 200)
            ->set_title("Game Engine")
            ->set_standard_alone(true)
    );
    delete builder;
    return game_engine::Window::wait_for_exit();
}
