#pragma once

#include "Keys.hpp"

#include <functional>
#include <array>


namespace EgorkaEngine
{
    enum class EventType
    {
        WindowResize = 0,
        WindowClose,

        KeyPressed,
        KeyReleased,

        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,

        Scrolled,
        StopedScroll,

        EventsCount
    };

    struct BaseEvent
    {
        virtual ~BaseEvent() = default;
        virtual EventType get_type() const = 0;
    };


    class EventDispatcher
    {
    private:
        std::array<std::function<void(BaseEvent&)>, static_cast<size_t>(EventType::EventsCount)> m_eventCallbacks;
    public:
        template<typename EventType>
        void add_event_listener(std::function<void(EventType&)> callback)
        {
            auto baseCallback = [func = std::move(callback)](BaseEvent& e)
            {
                if (e.get_type() == EventType::type)
                {
                    func(static_cast<EventType&>(e));
                }
            };
            m_eventCallbacks[static_cast<size_t>(EventType::type)] = std::move(baseCallback);
        }

        void dispatch(BaseEvent& event)
        {
            auto& callback = m_eventCallbacks[static_cast<size_t>(event.get_type())];
            if (callback)
            {
                callback(event);
            }
        }
    };


    struct EventMouseMoved : public BaseEvent
    {
        double x;
        double y;

        static const EventType type = EventType::MouseMoved;

        EventMouseMoved(const double new_x, const double new_y) : x(new_x), y(new_y) {}

        virtual EventType get_type() const override {return type;}
    };

    struct EventWindowResize : public BaseEvent
    {
        unsigned int width;
        unsigned int height;

        static const EventType type = EventType::WindowResize;

        EventWindowResize(const unsigned int new_width, const unsigned int new_height) : width(new_width), height(new_height) {}

        virtual EventType get_type() const override {return type;}
    };

    struct EventWindowClose : public BaseEvent
    {
        virtual EventType get_type() const override {return type;}

        static const EventType type = EventType::WindowClose;
    };

    struct EventKeyPressed : public BaseEvent
    {
        KeyCodes key_code;
        bool is_repeated;
        static const EventType type = EventType::KeyPressed;

        EventKeyPressed(KeyCodes code, const bool repeated) : key_code(code), is_repeated(repeated) {}

        virtual EventType get_type() const override
        {
            return type;
        }
    };

    struct EventKeyReleased : public BaseEvent
    {
        KeyCodes key_code;
        static const EventType type = EventType::KeyReleased;

        EventKeyReleased(KeyCodes code) : key_code(code){}

        virtual EventType get_type() const override
        {
            return type;
        }
    };

    struct EventMouseButtonPressed : public BaseEvent
    {
        MouseButton mouse_button;
        double x_pos;
        double y_pos;

        static const EventType type = EventType::MouseButtonPressed;


        EventMouseButtonPressed(const MouseButton mouse_button, const double x_pos, const double y_pos) : mouse_button(mouse_button), x_pos(x_pos), y_pos(y_pos){}

        virtual EventType get_type() const override
        {
            return type;
        }

    };

    struct EventMouseButtonReleased : public BaseEvent
    {
        MouseButton mouse_button;
        double x_pos;
        double y_pos;

        static const EventType type = EventType::MouseButtonReleased;

        EventMouseButtonReleased(const MouseButton mouse_button, const double x_pos, const double y_pos) : mouse_button(mouse_button), x_pos(x_pos), y_pos(y_pos){}

        virtual EventType get_type() const override
        {
            return type;
        }
    };

    struct EventScrolled : public BaseEvent
    {
        double xoffset;
        double yoffset;

        static const EventType type = EventType::Scrolled;

        EventScrolled(double _xoffset, double _yoffset) : xoffset(_xoffset), yoffset(_yoffset) {}

        virtual EventType get_type() const override
        {
            return type;
        }
    };
}