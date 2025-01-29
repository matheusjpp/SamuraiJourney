#pragma once
#include "Archer.h"

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