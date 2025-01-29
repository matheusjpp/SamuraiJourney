#pragma once
#include "Level.h"

namespace Levels {

	class BossLevel : public Level {
	
	public:
		BossLevel();

		~BossLevel();

		void render();

		void execute(float dt);
	};
	

}
