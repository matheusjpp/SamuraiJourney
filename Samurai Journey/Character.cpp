#include "Character.h"

namespace Entities {

	namespace Characters {

		Character::Character(Math::CoordF pos, Math::CoordF size, ID id, float hp) : hp(hp), canJump(false),
			MovingEntity(pos, size, id) {

		}

		Character::~Character() {

		}

		void Character::setHP(float HP) {
			hp = HP;
		}

		void Character::jump() {
			if (canJump) {
				canJump = false; 
				velocity.y -= JUMP;
			}
		}

		void Character::setCanJump(bool canJ) {
			canJump = canJ;
		}

		bool Character::getCanJump() const {
			return canJump;
		}

	}

}