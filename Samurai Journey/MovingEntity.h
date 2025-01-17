#pragma once
#include "EntitiesList.h"

namespace Managers {
	namespace Collisions {
		class CollisionManager;
	}
}


namespace Entities {

	class MovingEntity : public Entity {
	protected:
		static Managers::Collisions::CollisionManager* pCollision;
		Math::CoordF velocity;
		bool isFacingLeft;
		bool isMoving;
		bool canMove;

	public:
		MovingEntity(Math::CoordF pos = Math::CoordF(0, 0), Math::CoordF size = Math::CoordF(0, 0), ID id = ID::empty);

		virtual ~MovingEntity();

		void setCanMove(bool canMove);

		void setVelocityX(float velx);

		void setVelocityY(float vely);

		bool getCanMove() const;

		bool getIsFacingLeft() const;

		void move(bool left);

		void stopMoving();


		virtual void update(float dt) = 0;

	};

}