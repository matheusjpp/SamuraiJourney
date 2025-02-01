#pragma once
#include "Enemy.h"

#define WOLF_SIZE_X 64.0f
#define WOLF_SIZE_Y 42.0f

#define WOLF_SPEED 350.0f
#define WOLF_VISION 250.0f
#define WOLF_HP 100.0f
#define WOLF_ATTACK_CD 1.0f

#define WOLF_ATTACK_DAMAGE 10.0f
#define WOLF_ATTACK2_DAMAGE 20.0f

#define WOLF_ATTACK_TIME 0.75f
#define WOLF_ATTACK2_TIME 1.8f

#define WOLF_ATTACK_DISTANCE 80.0f
#define WOLF_ATTACK2_DISTANCE 80.0f

#define WOLF_HURT_TIME 0.9f
#define WOLF_DEATH_TIME 1.2f

namespace Entities {

	namespace Characters {

		class Wolf : public Enemy {
		private:
			bool isFirstAttack;
			float firstAttackTimer;

		public:
			Wolf(Math::CoordF pos = Math::CoordF(0.0f, 0.0f), ID id = ID::wolf);

			~Wolf();

			void update(float dt);

			void execute();

			void attack();

			const float getDamagePoints() const;

			void setTextures();

			void updateSprite(float dt);
		};

	}

}

