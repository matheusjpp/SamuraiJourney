#pragma once
#include "Enemy.h"

#define WOLF_SIZE_X 64.0f
#define WOLF_SIZE_Y 42.0f

#define WOLF_SPEED 350.0f

#define WOLF_VISION 300.0f
#define WOLF_HP 100.0f
#define WOLF_ATTACK_CD 0.8f
#define WOLF_ATTACK_TIME 0.6f
#define WOLF_ATTACK2_TIME 2.0f
#define WOLF_ATTACK_DISTANCE 100.0f
#define WOLF_ATTACK2_DISTANCE 200.0f

namespace Entities {

	namespace Characters {

		class Wolf : public Enemy {
		private:
			bool isFirstAttack;
			float firstAttackTimer;
			const float scaleFactor;

		public:
			Wolf(Math::CoordF pos = Math::CoordF(0.0f, 0.0f), ID id = ID::wolf);

			~Wolf();

			void update(float dt);

			void execute();

			void attack();

			void setTextures();

			void updateSprite(float dt);
		};

	}

}

