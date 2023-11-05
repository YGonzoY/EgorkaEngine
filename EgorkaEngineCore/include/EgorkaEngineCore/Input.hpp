#pragma once

#include "Keys.hpp"

namespace EgorkaEngine {

    class Input 
    {
    private:
        static bool m_keys_pressed[static_cast<size_t>(KeyCodes::KEY_LAST)];

    public:
        static bool IsKeyPressed(const KeyCodes key_code);
        static void PressKey(const KeyCodes key_code);
        static void ReleaseKey(const KeyCodes key_code);
    };
}