#include "EventsManager.h"

namespace Managers {

    EventsManager* EventsManager::pEv = nullptr;
    EventsManager::EventsManager() {
        pGraphic = GraphicManager::getInstance();
        pInput = InputManager::getInstance();
    }

    EventsManager::~EventsManager() {
        pGraphic = nullptr;
        pInput = nullptr;
    }

    EventsManager* EventsManager::getInstance() {
        if (pEv == nullptr) {
            pEv = new EventsManager();
        }
        return pEv;
    }
    void EventsManager::pollEvents() {
        sf::Event e;

        while (pGraphic->pollEvent(e)) {
            if (e.type == sf::Event::Closed) { pGraphic->closeWindow(); }
            if (e.type == sf::Event::KeyPressed) { pInput->handleKeyPressed(e.key.code); }
            if (e.type == sf::Event::KeyReleased) { pInput->handleKeyPressed(e.key.code); }
        }
    }

}
