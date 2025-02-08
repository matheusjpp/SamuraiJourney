#pragma once
#include "EventsManager.h"

namespace Managers {

	namespace States {

		class StateManager;

		enum State_ID {
			empty = 0,
			main_menu = 1,
			newgame_menu = 2,
			singleplayer_menu = 3,
			multiplayer_menu = 4,
			archerlevel_singleplayer = 5,
			archerlevel_multiplayer = 6,
			bosslevel_singleplayer = 7,
			bosslevel_multiplayer = 8,
			pause_menu = 9,
			gameover_menu = 10,
			win_menu = 11,
			leaderboard_menu = 12
		};

		class State {
		protected:
			static StateManager* pStateM;
			bool isActive;
			State_ID stateID;
		
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