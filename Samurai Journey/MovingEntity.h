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
		float damagePoints;

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
		
		virtual const float getDamagePoints() const;

		virtual void update(float dt) = 0;

		virtual void execute() = 0;

		virtual void setTextures() = 0;

		virtual void updateSprite(float dt) = 0;
	};

}