#include "MovingEntity.h"
#include "CollisionManager.h"

namespace Entities {

	Managers::Collisions::CollisionManager* MovingEntity::pCollision = Managers::Collisions::CollisionManager::getInstance();

	MovingEntity::MovingEntity(Math::CoordF pos, Math::CoordF size, ID id) : velocity(0), isMoving(false), canMove(true), isFacingLeft(false), damagePoints(0),
		Entity (pos, size, id) {
		
	}

	MovingEntity::~MovingEntity() {

	}

	void MovingEntity::setCanMove(bool canM) {
		canMove = canM;
	}

	void MovingEntity::setVelocityX(float velx) {
		velocity.x = velx;
	}

	void MovingEntity::setVelocityY(float vely) {
		velocity.y = vely;
	}

	bool MovingEntity::getCanMove() const {
		return canMove;
	}

	bool MovingEntity::getIsFacingLeft() const {
		return isFacingLeft;
	}

	bool MovingEntity::getIsMoving() {
		return isMoving;
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

	void MovingEntity::stopMoving() {
		isMoving = false;
	}

	const float MovingEntity::getDamagePoints() const {
		return damagePoints;
	}

}