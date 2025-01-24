#pragma once
#include "DemonSamurai.h"

#define MOVING_DELAY_TIME 2.5f

#define ARCHER_VISION 800.0f
#define ARCHER_HP 100.0f
#define ARCHER_ATTACK_CD 2.0f
#define ARCHER_ATTACK_TIME 2.5f
#define ARCHER_ATTACK_DISTANCE 500.0f
#define ARROW_DELAY_TIME 2.0f

namespace Entities {

	namespace Characters {

		class Archer : public Enemy {
		private:
			Arrow* pArrow;
			List::EntitiesList* movEnt;
			float arrowDelayTimer;
			float movingDelayTimer;

		public:
			Archer(Math::CoordF pos = Math::CoordF(0.0f, 0.0f), List::EntitiesList* movingEntities = nullptr, ID id = ID::archer);

			~Archer();

			void update(float dt);

			void execute();

			void attack();

			void setTextures();

			void updateSprite(float dt);
		};


	}

}
