#pragma once
#include "CollisionManager.h"

namespace Entities {

	namespace Characters {

		class Character : public MovingEntity {
		protected:
			float hp;
			bool canJump;
			bool isJumping;

		public:
			Character(Math::CoordF pos = Math::CoordF(0, 0), Math::CoordF size = Math::CoordF(0, 0), ID id = ID::empty, float hp = 0);

			virtual ~Character();

			void setHP(float HP);

			void jump();

			void setCanJump(bool canJ);

			bool getCanJump() const;

			bool getIsJumping() const;

			virtual void update(float dt) = 0;
		};


	}

}
