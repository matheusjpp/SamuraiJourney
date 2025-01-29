#include "Observer.h"
#include "InputManager.h"
#include "StateManager.h"

namespace Managers {

	namespace KeyManagement {

		Observer::Observer() : isActive(false) {
			pInput = Managers::KeyManagement::InputManager::getInstance();
			pStateM = Managers::States::StateManager::getInstance();

			pInput->attachObserver(this);
		}

		Observer::~Observer() {

		}

		const bool Observer::getIsActive() const {
			return isActive;
		}

		void Observer::setIsActive(bool isA) {
			isActive = isA;
		}

	}

}