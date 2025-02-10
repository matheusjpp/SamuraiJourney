#pragma once
#include "Subject.h"

// Código baseado no repositório "Desert" de Matheus Burda
// Repositório: https://github.com/MatheusBurda/Desert
// Licença: MIT
// 
// Conforme a licença MIT, este código pode ser usado, modificado e distribuído,
// desde que a atribuição ao autor original seja mantida.

namespace Managers {

    namespace States {
        class StateManager;
    }

    namespace KeyManagement {

        class InputManager : public Subject { // ConcreteSubject
        private:
            static InputManager* pInput;
            InputManager();

        public:
            ~InputManager();

            static InputManager* getInstance();

            void attachObserver(Observer* observer);

            void detachObserver(Observer* observer);

            void notifyKeyPressed(sf::Keyboard::Key key);

            void notifyKeyReleased(sf::Keyboard::Key key);
        };

    }

}