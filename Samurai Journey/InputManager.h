#pragma once
#include "Subject.h"

// C�digo baseado no reposit�rio "Desert" de Matheus Burda
// Reposit�rio: https://github.com/MatheusBurda/Desert
// Licen�a: MIT
// 
// Conforme a licen�a MIT, este c�digo pode ser usado, modificado e distribu�do,
// desde que a atribui��o ao autor original seja mantida.

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