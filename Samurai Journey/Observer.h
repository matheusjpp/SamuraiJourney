#pragma once
#include "Archer.h"

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

        class InputManager;

        class Observer {
        protected:
            Managers::KeyManagement::InputManager* pInput;
            States::StateManager* pStateM;
            bool isActive;

        public:
            Observer();

            ~Observer();

            const bool getIsActive() const;

            void setIsActive(bool isA);

            virtual void notifyKeyPressed(sf::Keyboard::Key key) = 0;

            virtual void notifyKeyReleased(sf::Keyboard::Key key) = 0;

        };

    }

}