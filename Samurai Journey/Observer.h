#pragma once
#include "Archer.h"

namespace Managers {

    namespace KeyManagement {
    
        class InputManager;

        class Observer {
        private:
            Managers::KeyManagement::InputManager* pInput;

        public:
            Observer();

            ~Observer();

            virtual void notifyKeyPressed(sf::Keyboard::Key key) = 0;

            virtual void notifyKeyReleased(sf::Keyboard::Key key) = 0;

        };

    }

}