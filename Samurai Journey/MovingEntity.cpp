#include "MovingEntity.h"

namespace Entities {

	MovingEntity::MovingEntity(Math::CoordF pos, Math::CoordF size, ID id) : speed(0), isMoving(false), canMove(true), isFacingLeft(false),
		Entity (pos, size, id) {
		
	}

	MovingEntity::~MovingEntity() {

	}

	void MovingEntity::setCanMove(bool canM) {
		canMove = canM;
	}

	bool MovingEntity::getCanMove() const {
		return canMove;
	}

	bool MovingEntity::getIsFacingLeft() const {
		return isFacingLeft;
	}

	void MovingEntity::move(bool left) {
		if (canMove) {
			isMoving = true;

			if (left) {
				isFacingLeft = true;
			}
			
			else {
				isFacingLeft = false;
			}
		}
	}

	void MovingEntity::stop() {
		isMoving = false;
	}

}