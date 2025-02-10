#include "EventsManager.h"

namespace Managers {

    namespace KeyManagement {

        EventsManager* EventsManager::pEvent = nullptr;
        GraphicManager* EventsManager::pGraphic = GraphicManager::getInstance();
        InputManager* EventsManager::pInput = InputManager::getInstance();

        EventsManager::EventsManager() {
           
        }

        EventsManager::~EventsManager() {
            pGraphic = nullptr;
            pInput = nullptr;
        }

        EventsManager* EventsManager::getInstance() {
            if (pEvent == nullptr) {
                pEvent = new EventsManager();
            }
            return pEvent;
        }

        void EventsManager::pollEvents() {
            sf::Event e;

            while (pGraphic->pollEvent(e)) {
                if (e.type == sf::Event::Closed) { pGraphic->closeWindow(); }
                if (e.type == sf::Event::KeyPressed) { pInput->notifyKeyPressed(e.key.code); }
                if (e.type == sf::Event::KeyReleased) { pInput->notifyKeyReleased(e.key.code); }
            }
        }

    }

}