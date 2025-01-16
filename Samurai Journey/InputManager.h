#pragma once
#include "Observer.h"
namespace Managers {
    class InputManager
    {
    private:
        std::list<Observer> observer;
        static InputManager* pInput;
        InputManager();
    public:
        static InputManager* getInstance();
        ~InputManager();
        void Attach();
        void Detach();
        void notify();
    };
}