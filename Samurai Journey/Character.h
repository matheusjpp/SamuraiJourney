#pragma once
#include "Arrow.h"

#define JUMP 500.0f

namespace Entities {

	namespace Characters {

		class Character : public MovingEntity {
		protected:
			float hp;
			bool canJump;
			bool isDying;
			bool isHurting;
			bool isAttacking;
			float attackCooldown;
			float attackingTime;
			float cooldownTimer;
			float attackTimer;
			float deathTimer;
			float hurtingTimer;
			float impactTimer;

		public:
			Character(Math::CoordF pos = Math::CoordF(0, 0), Math::CoordF size = Math::CoordF(0, 0), ID id = ID::empty, float hp = 0);

			virtual ~Character();

			float getHP() const;

			void setHP(float HP);

			const bool getIsDying() const;
			
			void setIsDying(bool isD);

			void setIsHurting(bool isH);

			void setIsAttacking(bool isAttack);

			void setAttackCooldown(float attackC);

			void setCooldownTimer(float cTimer);

			void setAttackTimer(float aTimer);

			void setDeathTimer(float dTimer);

			void setHurtingTimer(float hTimer);

			void setImpactTimer(float iTimer);

			virtual void receiveDamage(float damage);

			void jump();

			void setCanJump(bool canJ);

			bool getCanJump() const;

			bool getIsHurting();

			virtual void update(float dt) = 0;

			virtual void execute() = 0;

			virtual void attack() = 0;

			bool canAttack() const;

			void incrementAttackTime(const float dt);

			bool getIsAttacking() const;

			virtual void setTextures() = 0;

			virtual void updateSprite(float dt) = 0;

			const float getAttackCooldown() const;

			const float getCooldownTimer() const;

			const float getDeathTimer() const;

			const float getHurtingTimer() const;

			const float getImpactTimer() const;

			const float getAttackTimer() const;
		};


	}

}
