#pragma once
#include "Entity.h"

namespace Entities {

	class MovingEntity : public Entity {
	protected:
		Math::CoordF speed;
		bool isFacingLeft;
		bool isMoving;
		bool canMove;

	public:
		MovingEntity(Math::CoordF pos = Math::CoordF(0, 0), Math::CoordF size = Math::CoordF(0, 0), ID id = ID::empty);

		virtual ~MovingEntity();

		void setCanMove(bool canMove);

		bool getCanMove() const;

		bool getIsFacingLeft() const;

		void move(bool left);

		void stop();

		virtual void update(float dt) = 0;

	};

}