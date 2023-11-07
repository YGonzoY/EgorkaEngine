#pragma once

#include "Keys.hpp"

namespace EgorkaEngine {

    class Input 
    {
    private:
        static bool keys_pressed[];
        static bool mouse_buttons_pressed[];


    public:
        static bool IsKeyPressed(const KeyCodes key_code);
        static void PressKey(const KeyCodes key_code);
        static void ReleaseKey(const KeyCodes key_code);

        static bool IsMouseButtonPressed(const MouseButton mouse_button);
        static void PressMouseButton(const MouseButton mouse_button);
        static void ReleaseMouseButton(const MouseButton mouse_button);
    };
}