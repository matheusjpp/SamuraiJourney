#include "State.h"
#include "StateManager.h"

namespace Managers {

	namespace States {

		StateManager* State::pStateM = StateManager::getInstance();

		State::State(State_ID id) : isActive (false), stateID(id) {
			pStateM->pushState(this);
		}

		State::~State() {

		}

		const State_ID State::getID() const {
			return stateID;
		}

		const bool State::getIsActive() const {
			return isActive;
		}

		void State::setIsActive(bool isA) {
			isActive = isA;
		}

	}

}