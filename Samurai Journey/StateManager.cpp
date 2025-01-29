#include "StateManager.h"

namespace Managers {

	namespace States {

		StateManager* StateManager::pStateM = StateManager::getInstance();
		GraphicManager* StateManager::pGraphic = GraphicManager::getInstance();

		StateManager::StateManager() : stateStack() {

		}

		StateManager::~StateManager() {
			while (!stateStack.empty())
				popState();
		}

		StateManager* StateManager::getInstance() {
			if (!pStateM)
				pStateM = new StateManager();

			return pStateM;
		}

		void StateManager::pushState(State* state) {
			if (!stateStack.empty()) {
				stateStack.top()->setIsActive(false);
			}

			if (state) {
				state->setIsActive(true);
				stateStack.push(state);
			}
		}

		void StateManager::popState() {
			if (!stateStack.empty()) {
				if (stateStack.top()) {
					delete stateStack.top();
					stateStack.top() = nullptr;
					stateStack.pop();
					if (!stateStack.empty())
						stateStack.top()->setIsActive(true);
				}
			}
		}

		void StateManager::popState(int quantity) {
			for (int i = 0; i < quantity; i++) {
				if (!stateStack.empty()) {
					if (stateStack.top()) {
						delete stateStack.top();
						stateStack.top() = nullptr;
						stateStack.pop();
						if (!stateStack.empty())
							stateStack.top()->setIsActive(false);
					}
				}
			}
		}

		void StateManager::renderState() {
			if (!stateStack.empty()) {
				stateStack.top()->render();
			}
		}

		void StateManager::executeState() {
			if (!stateStack.empty()) {
				stateStack.top()->execute(pGraphic->getDeltaTime());
			}
		}

		State* StateManager::getCurrentState() const {
			if (!stateStack.empty())
				return stateStack.top();
			return nullptr;
		}

		State* StateManager::getPreviousState() {
			States::State* s = stateStack.top();
			stateStack.pop();
			States::State* s2 = stateStack.top();
			stateStack.push(s);
			return s2;
		}

	}

}