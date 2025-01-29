 #include "Archer.h"

namespace Entities {

	namespace Characters {

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

			float playerDistance = fabs(position.x - pPlayer->getPosition().x);

			if (position.x > pPlayer->getPosition().x) isFacingLeft = false;
			else isFacingLeft = true;

			if (isAttacking) {
				movingDelayTimer += dt;
				if (movingDelayTimer >= MOVING_DELAY_TIME) {
					if (playerDistance <= ARCHER_VISION) {
						if (position.x > pPlayer->getPosition().x) {
							position.x -= PLAYER_SPEED * dt / 3.0f;
							isFacingLeft = false;
							isMoving = true;
						}

						if (position.x < pPlayer->getPosition().x) {
							position.x += PLAYER_SPEED * dt / 3.0f;
							isFacingLeft = true;
							isMoving = true;
						}
					}
					movingDelayTimer = 0.0f;
				}
			}

			if (playerDistance <= ARCHER_ATTACK_DISTANCE) {
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

		void Archer::attack() {
			if (canAttack()) {
				isAttacking = true;
				arrowDelayTimer = 0.0f;
			}

			if (isAttacking) {
				arrowDelayTimer += pGraphic->getDeltaTime();
				if (arrowDelayTimer >= ARROW_DELAY_TIME) {
					float positionx;
					if (isFacingLeft) {
						positionx = getPosition().x - getSize().x / 2 + 95;
					}
					else {
						positionx = getPosition().x - getSize().x / 2 - 65;
					}
					float positiony = getPosition().y - 25;

					pArrow = new Arrow(Math::CoordF(positionx, positiony), !isFacingLeft);
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

			body->setOrigin(size.x / 2 + 33, size.y / 2 + 65);
		}

		void Archer::updateSprite(float dt) {
			if (isAttacking) {
				sprite->update(GraphicalElements::Animation_ID::attack, !isFacingLeft, position, dt);
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