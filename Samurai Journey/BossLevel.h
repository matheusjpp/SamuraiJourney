#pragma once
#include "Level.h"

namespace Levels {

	class BossLevel : public Level {
	
	public:
		BossLevel(bool isMultiplayer, Managers::States::State_ID id = Managers::States::State_ID::empty);

		~BossLevel();

		void render();

		void execute(float dt);
	};
	

}
