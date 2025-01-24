#pragma once
#include "Arrow.h"

#define JUMP 500.0f

namespace Entities {

	namespace Characters {

		class Character : public MovingEntity {
		protected:
			float hp;
			bool canJump;
			bool isAttacking;
			float attackCooldown;
			float attackingTime;
			float cooldownTimer;
			float attackTimer;

		public:
			Character(Math::CoordF pos = Math::CoordF(0, 0), Math::CoordF size = Math::CoordF(0, 0), ID id = ID::empty, float hp = 0);

			virtual ~Character();

			float getHP() const;

			void setHP(float HP);

			void jump();

			void setCanJump(bool canJ);

			bool getCanJump() const;

			virtual void update(float dt) = 0;

			virtual void execute() = 0;

			virtual void attack() = 0;

			bool canAttack() const;

			void incrementAttackTime(const float dt);

			bool getIsAttacking() const;

			virtual void setTextures() = 0;

			virtual void updateSprite(float dt) = 0;
		};


	}

}
