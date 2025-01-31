#include "Character.h"

namespace Entities {

	namespace Characters {

		Character::Character(Math::CoordF pos, Math::CoordF size, ID id, float hp) : hp(1), canJump(false), isDying(false), isHurting(false),
			isAttacking(false), attackCooldown(0), attackingTime(0), attackTimer(0), cooldownTimer(0), deathTimer(0), hurtingTimer (0), impactTimer(0),
			MovingEntity(pos, size, id) 
		{

		}

		Character::~Character() {

		}

		float Character::getHP() const {
			return hp;
		}

		void Character::setHP(float HP) {
			hp = HP;
		}

		const bool Character::getIsDying() const {
			return isDying;
		}

		void Character::receiveDamage(float damage) {
			hp -= damage;
			isHurting = true;
			if (hp <= 0) {
				isHurting = false;
				isAttacking = false;
				canJump = false;
				canMove = false;
				isMoving = false;
				isDying = true;
			}
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

		bool Character::canAttack() const {
			return cooldownTimer > attackCooldown ? true : false;
		}

		void Character::incrementAttackTime(const float dt) {
			if (isAttacking) {
				cooldownTimer = 0;
				attackTimer += dt;
				if (attackTimer > attackingTime)
					isAttacking = false;
			} 
			else {
				cooldownTimer += dt;
				attackTimer = 0;
			}
		}

		bool Character::getIsAttacking() const {
			return isAttacking;
		}

	}

}