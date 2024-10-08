#ifndef GUIEVENT_H
#define GUIEVENT_H

class GUIEvent {
    int type;
    union data {

    };
};

enum GUIEventType {
    Mouse = 0,
    KeyBoard
};

#endif //GUIEVENT_H
