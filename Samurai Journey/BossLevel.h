#pragma once
#include "Level.h"

namespace Levels {

	class BossLevel : public Level {
	private:

	public:
		BossLevel(bool isMultiplayer, Managers::States::State_ID id = Managers::States::State_ID::empty, int playerPoints = 0);

		~BossLevel();

		void verifyLevelEnd();

		void execute(float dt);
	};
	
}