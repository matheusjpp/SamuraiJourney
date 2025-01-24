#include "DemonSamurai.h"

namespace Entities {

	namespace Characters {

		int Entities::Characters::DemonSamurai::cont(0);
		bool Entities::Characters::DemonSamurai::isLastBuffed(false);

		DemonSamurai::DemonSamurai(Math::CoordF pos, ID id) : 
			Enemy(pos, Math::CoordF(PLAYER_SIZE_X, PLAYER_SIZE_Y), id) {
			cont++;

			setHP(DEMON_HP);
			attackCooldown = DEMON_ATTACK_CD;
			attackingTime = DEMON_ATTACK_TIME;

			setTextures();
		}

		DemonSamurai::~DemonSamurai() {
			cont--;
			if (cont == 0)
				isLastBuffed = false;
		}

		void DemonSamurai::update(float dt) {
			
			if (cont == 1 && !isLastBuffed) {
				isLastBuffed = true;
				attackCooldown = DEMON_ATTACK2_CD;
				attackingTime = DEMON_ATTACK2_TIME;
				setTextures();
				setHP(DEMON_HP * 2);
				//setDmg(dobro tbm)
				//dobra tudo
			}
			
			incrementAttackTime(dt);
			isMoving = false;

			float playerDistance = fabs(position.x - pPlayer->getPosition().x);
			
			if (playerDistance <= DEMON_VISION) {
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

			if (playerDistance <= DEMON_ATTACK_DISTANCE) {
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

		void DemonSamurai::execute() {
			update(pGraphic->getDeltaTime());
			render();
		}

		void DemonSamurai::attack() {
			if (canAttack()) {
				isAttacking = true;
			}
		}

		void DemonSamurai::setTextures() {
			sprite = new GraphicalElements::Animation(body, Math::CoordF(1.7, 1.7));

			if (!isLastBuffed) {
				sprite->addNewAnimation(GraphicalElements::Animation_ID::idle, "demon_idle.png", 6);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::run, "demon_run.png", 8);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::attack, "demon_attack.png", 5);
			}

			else {
				sprite->addNewAnimation(GraphicalElements::Animation_ID::idle2, "demon_idle2.png", 6);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::run2, "demon_run2.png", 8);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::attack2, "demon_attack2.png", 7);
			}
			
			body->setOrigin(size.x / 2 + 31, size.y / 2 + 63);
		}

		void DemonSamurai::updateSprite(float dt) {
			if (!isLastBuffed) {
				if (isAttacking) {
					sprite->update(GraphicalElements::Animation_ID::attack, !isFacingLeft, position, dt);
				}

				else if (isMoving) {
					sprite->update(GraphicalElements::Animation_ID::run, !isFacingLeft, position, dt);
				}

				else {
					sprite->update(GraphicalElements::Animation_ID::idle, !isFacingLeft, position, dt);
				}
			}

			else {
				if (isAttacking) {
					sprite->update(GraphicalElements::Animation_ID::attack2, !isFacingLeft, position, dt);
				}

				else if (isMoving) {
					sprite->update(GraphicalElements::Animation_ID::run2, !isFacingLeft, position, dt);
				}

				else {
					sprite->update(GraphicalElements::Animation_ID::idle2, !isFacingLeft, position, dt);
				}
			}
		}

	}

}