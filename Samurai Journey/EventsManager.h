#pragma once
#include "PlayerController.h"

// C�digo baseado no reposit�rio "Desert" de Matheus Burda
// Reposit�rio: https://github.com/MatheusBurda/Desert
// Licen�a: MIT
// 
// Conforme a licen�a MIT, este c�digo pode ser usado, modificado e distribu�do,
// desde que a atribui��o ao autor original seja mantida.

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