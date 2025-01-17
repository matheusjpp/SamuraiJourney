#pragma once
#include "PlayerController.h"

namespace Managers {

    namespace KeyManagement {

        class EventsManager {
        private:
            GraphicManager* pGraphic;
            InputManager* pInput;
            static EventsManager* pEvent;
            EventsManager();

        public:
            ~EventsManager();

            static EventsManager* getInstance();

            void pollEvents();
        };

    }

}