#pragma once
#include "InputManager.h"
namespace Managers {
    class EventsManager
    {
    private:
        GraphicManager* pGraphic;
        InputManager* pInput;
        static EventsManager* pEv;
        EventsManager();
    public:
        ~EventsManager();
        static EventsManager* getInstance();
        void pollEvents();
    };
}
