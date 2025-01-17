#include "Observer.h"
#include "InputManager.h"

namespace Managers {

	namespace KeyManagement {

		Observer::Observer() {
			pInput = Managers::KeyManagement::InputManager::getInstance();
			pInput->attachObserver(this);
		}

		Observer::~Observer() {

		}

	}

}