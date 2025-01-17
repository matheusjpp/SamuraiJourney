#include "EventsManager.h"

namespace Managers {

    namespace KeyManagement {

        EventsManager* EventsManager::pEvent = nullptr;

        EventsManager::EventsManager() {
            pGraphic = GraphicManager::getInstance();
            pInput = InputManager::getInstance();
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