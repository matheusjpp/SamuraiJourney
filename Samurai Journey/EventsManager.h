#pragma once
#include "PlayerController.h"

namespace Managers {

    namespace KeyManagement {

        class EventsManager {
        private:
            static GraphicManager* pGraphic;
            static InputManager* pInput;
            static EventsManager* pEvent;
            EventsManager();

        public:
            ~EventsManager();

            static EventsManager* getInstance();

            void pollEvents();
        };

    }

}