#pragma once
#include "EventsManager.h"

namespace Managers {

	namespace States {

		class StateManager;

		enum State_ID {
			empty = 0,
			main_menu
		};

		class State {
		protected:
			static StateManager* pStateM;
			bool isActive;
			State_ID id;
		
		public:
			State(State_ID id = empty);

			virtual ~State();

			const bool getIsActive() const;

			void setIsActive(bool isA);

			const State_ID getID() const;

			virtual void render() = 0;

			virtual void execute(float dt) = 0;
		};

	}

}