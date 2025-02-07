#pragma once
#include "DemonSamurai.h"

#define MOVING_DELAY_TIME 2.5f

#define ARCHER_VISION 800.0f
#define ARCHER_HP 100.0f
#define ARCHER_DELAY_TIME 2.0f

#define ARCHER_ATTACK_CD 2.0f
#define ARCHER_ATTACK_TIME 3.15f
#define ARCHER_ATTACK_DISTANCE 500.0f

#define ARCHER_HURT_TIME 0.6f
#define ARCHER_DEATH_TIME 1.65f

namespace Entities {

	namespace Factories {
		class ArrowFactory;
	};


	namespace Characters {

		class Archer : public Enemy {
		private:
			Arrow* pArrow;
			List::EntitiesList* movEnt;
			float arrowDelayTimer;
			float movingDelayTimer;
			static Factories::ArrowFactory arrowFactory;

		public:
			Archer(Math::CoordF pos = Math::CoordF(0.0f, 0.0f), List::EntitiesList* movingEntities = nullptr, ID id = ID::archer);

			~Archer();

			void update(float dt);

			void execute();

			const float getArrowDelayTimer() const;

			void setArrowDelayTimer(float aDelayT);

			 float getMovingDelayTimer() ;

			 void setMovingDelayTimer(float mDelayT);

			void attack();

			void setTextures();

			void updateSprite(float dt);
		};


	}

}
