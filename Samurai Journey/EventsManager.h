#pragma once
#include "InputManager.h"
namespace Managers {
    class EventsManager
    {
    private:
        GraphicManager* pGraphic;
        KeyManagement::InputManager* pInput;
        static EventsManager* pEvent;
        EventsManager();

    public:
        ~EventsManager();

        static EventsManager* getInstance();

        void pollEvents();
    };
}
