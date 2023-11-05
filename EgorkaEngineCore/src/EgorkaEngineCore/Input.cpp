#include "EgorkaEngineCore/Input.hpp"

namespace EgorkaEngine {
    bool Input::m_keys_pressed[static_cast<size_t>(KeyCodes::KEY_LAST)] = {};

    bool Input::IsKeyPressed(const KeyCodes key_code)
    {
        return m_keys_pressed[static_cast<size_t>(key_code)];
    }

    void Input::PressKey(const KeyCodes key_code)
    {
        m_keys_pressed[static_cast<size_t>(key_code)] = true;
    }

    void Input::ReleaseKey(const KeyCodes key_code)
    {
        m_keys_pressed[static_cast<size_t>(key_code)] = false;
    }
}