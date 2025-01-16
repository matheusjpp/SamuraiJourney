#pragma once
#include "Observer.h"
namespace Managers {
    class InputManager
    {
    private:
        std::list<Observer*> observer;
        static InputManager* pInput;
        InputManager();
    public:
        static InputManager* getInstance();
        ~InputManager();
        void Attach(Observer* pObserver);//add observer
        void Detach(Observer* pObserver);//remove observer
        void handleKeyPressed(sf::Keyboard::Key key);
        void handleKeyReleased(sf::Keyboard::Key key);
    };
}