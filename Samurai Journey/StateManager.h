#pragma once
#include "State.h"

namespace Managers {

	namespace States {

		class StateManager {
		private:
			std::stack<State*> stateStack;
			static StateManager* pStateM;
			static GraphicManager* pGraphic;

			StateManager();

		public:
			~StateManager();

			static StateManager* getInstance();

			void pushState(State* state);

			void popState();

			void popState(int quantity);

			void renderState();

			void executeState();

			State* getCurrentState() const;

			State* getPreviousState();
		};

	}

}