#include "InputManager.h"

namespace Managers {

    namespace KeyManagement {

        // Inicializa o ponteiro estático
        InputManager* InputManager::pInput = nullptr;

        // Construtor privado
        InputManager::InputManager() {
    
        }

        // Destrutor
        InputManager::~InputManager() {
            observers.clear();
        }

        // Método para obter a instância única da classe
        InputManager* InputManager::getInstance() {
            if (pInput == nullptr) {
                pInput = new InputManager();
            }
            return pInput;
        }

        void InputManager::attachObserver(Observer* observer) {
            if (observer) {
                observers.push_back(observer);
            }
        }

        void InputManager::detachObserver(Observer* observer) {
            if (observer) {
                observers.remove(observer);
            }
        }

        void InputManager::notifyKeyPressed(sf::Keyboard::Key key) {
            for (auto& observer : observers) {
                if (observer)
                    observer->notifyKeyPressed(key);
            }
        }

        void InputManager::notifyKeyReleased(sf::Keyboard::Key key) {
            for (auto& observer : observers) {
                if (observer)
                    observer->notifyKeyReleased(key);
            }
        }

    }

}
