#pragma once
#include "CollisionManager.h"
#define JUMP 500.0f

namespace Entities {

	namespace Characters {

		class Character : public MovingEntity {
		protected:
			float hp;
			bool canJump;

		public:
			Character(Math::CoordF pos = Math::CoordF(0, 0), Math::CoordF size = Math::CoordF(0, 0), ID id = ID::empty, float hp = 0);

			virtual ~Character();

			void setHP(float HP);

			void jump();

			void setCanJump(bool canJ);

			bool getCanJump() const;

			virtual void update(float dt) = 0;

			virtual void execute() = 0;

			virtual void attack() = 0;

			virtual void setTextures() = 0;

			virtual void updateSprite(float dt) = 0;
		};


	}

}
