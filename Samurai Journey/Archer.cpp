#include "Archer.h"
#include "ArrowFactory.h"

namespace Entities {

	namespace Characters {

		Factories::ArrowFactory Archer::arrowFactory;

		Archer::Archer(Math::CoordF pos, List::EntitiesList* movingEntities, ID id) : pArrow(nullptr), arrowDelayTimer (0), movingDelayTimer (0),
			Enemy(pos, Math::CoordF(PLAYER_SIZE_X, PLAYER_SIZE_Y), id) {

			movEnt = movingEntities;

			setHP(PLAYER_HP);
			attackCooldown = ARCHER_ATTACK_CD;
			attackingTime = ARCHER_ATTACK_TIME;

			setTextures();
		}

		Archer::~Archer() {

		}

		void Archer::update(float dt) {
			incrementAttackTime(dt);
			isMoving = false;

			Player* nearestPlayer = getNearestPlayer();
			float playerDistance = fabs(position.x - nearestPlayer->getPosition().x);

			if (position.x > nearestPlayer->getPosition().x) isFacingLeft = false;
			else isFacingLeft = true;

			if (isAttacking) {
				movingDelayTimer += dt;
				if (movingDelayTimer >= MOVING_DELAY_TIME && !isDying) {
					if (playerDistance <= ARCHER_VISION) {
						if (position.x > nearestPlayer->getPosition().x) {
							position.x -= PLAYER_SPEED * dt / 3.0f;
							isFacingLeft = false;
							isMoving = true;
						}

						if (position.x < nearestPlayer->getPosition().x) {
							position.x += PLAYER_SPEED * dt / 3.0f;
							isFacingLeft = true;
							isMoving = true;
						}
					}
					movingDelayTimer = 0.0f;
				}
			}

			if (playerDistance <= ARCHER_ATTACK_DISTANCE && !isDying) {
				isMoving = false;
				attack();
			}

			velocity.y += GRAVITY * dt; // Incrementa velocidade vertical
			position.x += velocity.x * dt;
			position.y += velocity.y * dt;

			setCanJump(false);
			pCollision->notifyCollision(this, dt);
			updateSprite(dt);
			body->setPosition(sf::Vector2f(position.x, position.y));
		}

		void Archer::execute() {
			update(pGraphic->getDeltaTime());
			render();
		}

		const float Archer::getArrowDelayTimer() const{
			return arrowDelayTimer;
		}

		void Archer::setArrowDelayTimer(float aDelayT) {
			arrowDelayTimer = aDelayT;
		}

		float Archer::getMovingDelayTimer() {
			return movingDelayTimer;
		}

		void Archer::setMovingDelayTimer(float mDelayT) {
			movingDelayTimer = mDelayT;
		}

		void Archer::attack() {
			if (canAttack()) {
				isAttacking = true;
				arrowDelayTimer = 0.0f;
			}

			if (isAttacking) {
				arrowDelayTimer += pGraphic->getDeltaTime();
				if (arrowDelayTimer >= ARCHER_DELAY_TIME) {
					float positionx;
					if (isFacingLeft) {
						positionx = getPosition().x - getSize().x / 2 + 95;
					}
					else {
						positionx = getPosition().x - getSize().x / 2 - 65;
					}
					float positiony = getPosition().y - 25;

					pArrow = static_cast<Entities::Arrow*>(arrowFactory.FactoryMethod(Math::CoordF(positionx, positiony), false, false, nullptr, nullptr, ID::arrow));
					pArrow->setIsFacingLeft(!isFacingLeft);
						//new Arrow(Math::CoordF(positionx, positiony), !isFacingLeft);
					movEnt->addEntity(pArrow);
					arrowDelayTimer = 0.0f;
					isAttacking = false;
				}
			}
		}

		void Archer::setTextures() {
			sprite = new GraphicalElements::Animation(body, Math::CoordF(2, 2));

			sprite->addNewAnimation(GraphicalElements::Animation_ID::idle, "archer_idle.png", 8);
			sprite->addNewAnimation(GraphicalElements::Animation_ID::walk, "archer_walk.png", 10);
			sprite->addNewAnimation(GraphicalElements::Animation_ID::attack, "archer_attack.png", 21);
			sprite->addNewAnimation(GraphicalElements::Animation_ID::hurt, "archer_hurt.png", 4);
			sprite->addNewAnimation(GraphicalElements::Animation_ID::death, "archer_death.png", 11);

			body->setOrigin(size.x / 2 + 33, size.y / 2 + 65);
		}

		void Archer::updateSprite(float dt) {
			if (isDying) {
				deathTimer += dt;
				sprite->update(GraphicalElements::Animation_ID::death, !isFacingLeft, position, dt);
				if (deathTimer >= ARCHER_DEATH_TIME) isActive = false;
			}


			else if (isAttacking) {
				sprite->update(GraphicalElements::Animation_ID::attack, !isFacingLeft, position, dt);
			}

			else if (isHurting) {
				hurtingTimer += dt;
				sprite->update(GraphicalElements::Animation_ID::hurt, !isFacingLeft, position, dt);
				if (hurtingTimer >= ARCHER_HURT_TIME) { isHurting = false; hurtingTimer = 0; }
			}

			else if (isMoving) {
				sprite->update(GraphicalElements::Animation_ID::walk, !isFacingLeft, position, dt);
			}

			else {
				sprite->update(GraphicalElements::Animation_ID::idle, !isFacingLeft, position, dt);
			}
		}

	}

}