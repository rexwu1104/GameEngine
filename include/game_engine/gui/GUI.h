#ifndef GUI_H
#define GUI_H

#include <queue>
#include <game_engine/gui/GUIEvent.h>
#include <game_engine/Backend.h>
#include <game_engine/platform/Window.h>

class GUI {
private:
    std::queue<GUIEvent> events;
    Backend backend;
    game_engine::Window *window;
public:
    GUI();

    int start();

private:
    int process_queue();

    int main_window();
};

#endif //GAMEENGINEGUI_H
