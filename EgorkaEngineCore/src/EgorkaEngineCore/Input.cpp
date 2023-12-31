#include "EgorkaEngineCore/Input.hpp"

namespace EgorkaEngine {
    bool Input::keys_pressed[static_cast<size_t>(KeyCodes::KEY_LAST) + 1] = {};
    bool Input::mouse_buttons_pressed[static_cast<size_t>(MouseButton::MOUSE_BUTTON_LAST) + 1] = {};
    bool Input::is_scrolled = false;
    double Input::scroll_zoom = 0;

    bool Input::IsKeyPressed(const KeyCodes key_code)
    {
        return keys_pressed[static_cast<size_t>(key_code)];
    }

    void Input::PressKey(const KeyCodes key_code)
    {
        keys_pressed[static_cast<size_t>(key_code)] = true;
    }

    void Input::ReleaseKey(const KeyCodes key_code)
    {
        keys_pressed[static_cast<size_t>(key_code)] = false;
    }

    bool Input::IsMouseButtonPressed(const MouseButton mouse_button)
    {
        return mouse_buttons_pressed[static_cast<size_t>(mouse_button)];
    }

    void Input::PressMouseButton(const MouseButton mouse_button)
    {
        mouse_buttons_pressed[static_cast<size_t>(mouse_button)] = true;
    }

    void Input::ReleaseMouseButton(const MouseButton mouse_button)
    {
        mouse_buttons_pressed[static_cast<size_t>(mouse_button)] = false;
    }

    void Input::Scroll(const double yoffset)
    {
        scroll_zoom += yoffset;
        is_scrolled = true;
    }

    void Input::StopScroll()
    {
        scroll_zoom = 0;
        is_scrolled = false;
    }

    bool Input::IsScrolled()
    {
        return is_scrolled;
    }

    double Input::ScrollZoom()
    {
        return scroll_zoom;
    }
}