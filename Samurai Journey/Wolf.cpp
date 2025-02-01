#include "Wolf.h"

namespace Entities {

	namespace Characters {

		Wolf::Wolf(Math::CoordF pos, ID id) : isFirstAttack(true), firstAttackTimer(0),
			Enemy(pos, Math::CoordF(WOLF_SIZE_X, WOLF_SIZE_Y), id) {
			
			setHP(WOLF_HP);
			attackCooldown = WOLF_ATTACK_CD;
			attackingTime = WOLF_ATTACK2_TIME;

			setTextures();
		}

		Wolf::~Wolf() {

		}

		void Wolf::update(float dt) {
			updateSprite(dt);
			incrementAttackTime(dt);
			isMoving = false;
			
			Player* nearestPlayer = getNearestPlayer();

			if (nearestPlayer) {
				float playerDistance = fabs(position.x - nearestPlayer->getPosition().x);
				if (playerDistance <= WOLF_VISION) {
					if (isFirstAttack) {
						if (position.x > nearestPlayer->getPosition().x) {
							position.x -= WOLF_SPEED * dt / 2.0f;
							isFacingLeft = false;
							isMoving = true;
						}

						if (position.x < nearestPlayer->getPosition().x) {
							position.x += WOLF_SPEED * dt / 2.0f;
							isFacingLeft = true;
							isMoving = true;
						}
					}
					else {
						if (position.x > nearestPlayer->getPosition().x) {
							position.x -= WOLF_SPEED * 0.8 * dt / 3.0f;
							isFacingLeft = false;
							isMoving = true;
						}

						if (position.x < nearestPlayer->getPosition().x) {
							position.x += WOLF_SPEED * 0.8 * dt / 3.0f;
							isFacingLeft = true;
							isMoving = true;
						}
					}
				}

				if (isFirstAttack && playerDistance <= WOLF_ATTACK2_DISTANCE && fabs(pPlayer1->getPosition().y - position.y) <= fabs(pPlayer1->getSize().y - size.y)) {
					isMoving = false;
					attack();
				} 

				else if (playerDistance <= WOLF_ATTACK_DISTANCE && fabs(pPlayer1->getPosition().y - position.y) <= fabs(pPlayer1->getSize().y - size.y)) {
					isMoving = false;
					attack();
				}
			}

			velocity.y += GRAVITY * dt;
			position.x += velocity.x * dt;
			position.y += velocity.y * dt;

			setCanJump(false);
			pCollision->notifyCollision(this, dt);
			
			body->setPosition(sf::Vector2f(position.x, position.y));
		}

		void Wolf::execute() {
			update(pGraphic->getDeltaTime());
			render();
		}

		void Wolf::attack() {
			if (canAttack()) {
				isAttacking = true;
				
				if (isFirstAttack) {
					attackingTime = WOLF_ATTACK2_TIME;
				}

				else {
					attackingTime = WOLF_ATTACK_TIME;
				}
			}
		}

		const float Wolf::getDamagePoints() const {
			if (isFirstAttack)
				return WOLF_ATTACK2_DAMAGE;
			return WOLF_ATTACK_DAMAGE;
		}

		void Wolf::setTextures() {
			sprite = new GraphicalElements::Animation(body, Math::CoordF(4, 2));

			sprite->addNewAnimation(GraphicalElements::Animation_ID::idle, "wolf_idle.png", 6);
			sprite->addNewAnimation(GraphicalElements::Animation_ID::run, "wolf_run.png", 6);
			sprite->addNewAnimation(GraphicalElements::Animation_ID::jump, "wolf_jump.png", 3);
			sprite->addNewAnimation(GraphicalElements::Animation_ID::attack, "wolf_attack.png", 5);
			sprite->addNewAnimation(GraphicalElements::Animation_ID::attack2, "wolf_attack2.png", 12);
			sprite->addNewAnimation(GraphicalElements::Animation_ID::hurt, "wolf_hurt.png", 6);
			sprite->addNewAnimation(GraphicalElements::Animation_ID::death, "wolf_death.png", 8);

			body->setSize(sf::Vector2f(64.0f, 42.0f));
			body->setOrigin(size.x / 2, size.y / 2 + 9);
		}

		void Wolf::updateSprite(float dt) {
			const float scaleFactor = 1.2;
			float sizex = getSize().x;
			float sizey = getSize().y;

			if (isDying) {
				body->setSize(sf::Vector2f(scaleFactor * sizex, scaleFactor * sizey));
				body->setOrigin(size.x / 2 + 5, size.y / 2 + 14);
				deathTimer += dt;
				sprite->update(GraphicalElements::Animation_ID::death, isFacingLeft, position, dt);
				if (deathTimer >= WOLF_DEATH_TIME) isActive = false;
			}

			else if (isAttacking) {
				body->setSize(sf::Vector2f(scaleFactor * sizex, scaleFactor * sizey));
				body->setOrigin(size.x / 2 + 5, size.y / 2 + 14);
				attackTimer += dt;
				if (isAttacking) {
					body->setSize(sf::Vector2f(scaleFactor * sizex, scaleFactor * sizey));
					body->setOrigin(size.x / 2 + 5, size.y / 2 + 14);
					if (isFirstAttack) {
						firstAttackTimer += dt;
						sprite->update(GraphicalElements::Animation_ID::attack2, isFacingLeft, position, dt);
						if (firstAttackTimer >= WOLF_ATTACK2_TIME) {
							isFirstAttack = false;
						}
					}
					else {
						sprite->update(GraphicalElements::Animation_ID::attack, isFacingLeft, position, dt);
					}
				}
			}

			else if (isHurting) {
				body->setSize(sf::Vector2f(scaleFactor * sizex, scaleFactor * sizey));
				body->setOrigin(size.x / 2 + 5, size.y / 2 + 14);
				hurtingTimer += dt;
				sprite->update(GraphicalElements::Animation_ID::hurt, isFacingLeft, position, dt);
				if (hurtingTimer >= WOLF_HURT_TIME) { isHurting = false; hurtingTimer = 0; }
			}

			

			else if (!canJump) {
				body->setSize(sf::Vector2f(scaleFactor * sizex, scaleFactor * sizey));
				body->setOrigin(size.x / 2 + 5, size.y / 2 + 14);
				sprite->update(GraphicalElements::Animation_ID::jump, isFacingLeft, position, dt);
			}

			else if (isMoving) {
				body->setSize(sf::Vector2f(scaleFactor * sizex, scaleFactor * sizey));
				body->setOrigin(size.x / 2 + 5, size.y / 2 + 14);
				sprite->update(GraphicalElements::Animation_ID::run, isFacingLeft, position, dt);
			}

			else {
				body->setSize(sf::Vector2f(sizex, sizey));
				body->setOrigin(size.x / 2, size.y / 2 + 9);
				sprite->update(GraphicalElements::Animation_ID::idle, isFacingLeft, position, dt);
			}
		}

	}

}