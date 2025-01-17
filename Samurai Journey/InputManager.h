#pragma once
#include "Subject.h"

namespace Managers {

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