#pragma once
#include "PlayerController.h"

// Código baseado no repositório "Desert" de Matheus Burda
// Repositório: https://github.com/MatheusBurda/Desert
// Licença: MIT
// 
// Conforme a licença MIT, este código pode ser usado, modificado e distribuído,
// desde que a atribuição ao autor original seja mantida.

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