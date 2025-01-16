#include "InputManager.h"


namespace Managers {

    // Inicializa o ponteiro estático
    InputManager* InputManager::pInput = nullptr;

    // Construtor privado
    InputManager::InputManager() :observer() {}

    // Destrutor
    InputManager::~InputManager() {
        observer.clear();
    }

    // Método para obter a instância única da classe
    InputManager* InputManager::getInstance() {
        if (pInput == nullptr) {
            pInput = new InputManager();
        }
        return pInput;
    }

    // Método para adicionar um Observer
    void InputManager::Attach(Observer* pObserver) {
        if (pObserver != nullptr) {
            observer.push_back(pObserver);
        }
    }

    // Método para remover um Observer
    void InputManager::Detach(Observer* pObserver) {
        if (pObserver != nullptr) {
            observer.remove(pObserver);
        }
    }

    void InputManager::handleKeyPressed(sf::Keyboard::Key key) {
        if (!observer.empty()) {
            std::list<Observer*>::iterator it = observer.begin();
            while (it != observer.end()) {
                if (*it != nullptr) {
                    (*it)->notifyKeyPressed(key);
                }
                ++it;
            }
        }
    }


    void InputManager::handleKeyReleased(sf::Keyboard::Key key) {
        if (!observer.empty()) {
            std::list<Observer*>::iterator it = observer.begin();
            while (it != observer.end()) {
                if (*it != nullptr) {
                    (*it)->notifyKeyReleased(key);
                }
                ++it;
            }
        }
    }
}
