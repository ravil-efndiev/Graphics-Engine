#include "EventListener.hpp"

#include "Rvlglpch.hpp"

namespace rvl
{
    std::array<bool, 1032> EventListener::_keysPressed;
    std::array<int, 1032>  EventListener::_changeFrames;


    void EventListener::Init()
    {
        _keysPressed.fill(false);
    }

    void EventListener::Listen(const Event *event)
    {
        switch (event->GetCategory())
        {
            case EventCategory::WINDOW_EVENTS:
                ListenWindowEvents(event);
                break;
            case EventCategory::KEY_EVENTS:
                ListenKeyEvents(event);
                break;
            default:
                RVL_LOG_ERROR("invalid event category");
                RVL_DEBUG_BREAK;
        }
    }

    bool EventListener::GetKey(rvlKeycode_t keycode)
    {
        return _keysPressed[keycode];
    }

    void EventListener::ListenWindowEvents(const Event *event)
    {
        switch (event->GetType())
        {
            case EventType::WINDOW_RESIZE: {
                auto castedEvent = dynamic_cast<const WindowResizeEvent*>(event);
                RVL_ASSERT(castedEvent, "passed event instance does not have proper type")

                glViewport(0, 0, castedEvent->GetWidth(), castedEvent->GetHeight());
                break;
            }
            default: {
                RVL_LOG_ERROR("invalid event type for category");
                RVL_DEBUG_BREAK;
            }
        }   
    }

    void EventListener::ListenKeyEvents(const Event *event)
    {
        switch (event->GetType())
        {
            case EventType::KEY_PRESSED: {
                auto castedEvent = dynamic_cast<const KeyPressEvent*>(event);
                RVL_ASSERT(castedEvent, "passed event instance does not have proper type")
                
                _keysPressed[castedEvent->GetKeyCode()] = true;

                break;
            }
            case EventType::KEY_RELEASED: {
                auto castedEvent = dynamic_cast<const KeyReleaseEvent*>(event);
                RVL_ASSERT(castedEvent, "passed event instance does not have proper type")

                _keysPressed[castedEvent->GetKeyCode()] = false;

                break;
            }
            default: {
                RVL_LOG_ERROR("invalid event type for category");
                RVL_DEBUG_BREAK;
            }
        }   
    }
}
