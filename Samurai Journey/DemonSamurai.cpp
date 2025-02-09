#include "DemonSamurai.h"

namespace Entities {

	namespace Characters {

		int Entities::Characters::DemonSamurai::cont(0);
		bool Entities::Characters::DemonSamurai::isLastBuffed(false);

		DemonSamurai::DemonSamurai(Math::CoordF pos, ID id) : isShouting(false), shoutTimer(0),
			Enemy(pos, Math::CoordF(PLAYER_SIZE_X, PLAYER_SIZE_Y), id) {
			cont++;

			setHP(DEMON_HP);
			attackCooldown = DEMON_ATTACK_CD;
			attackingTime = DEMON_ATTACK_TIME;
			damagePoints = DEMON_ATTACK_DAMAGE;

			setTextures();
		}

		DemonSamurai::~DemonSamurai() {
			
		}

		int DemonSamurai::getCont() {
			return cont;
		}

		bool DemonSamurai::getIsLastBuffed() {
			return isLastBuffed;
		}

		bool DemonSamurai::getIsShouting(){
			return isShouting;
		}

		const float DemonSamurai::getShoutTimer()const {
			return shoutTimer;
		}

		void DemonSamurai::shout() {
			damagePoints = DEMON_ATTACK_DAMAGE * 2;
			setHP(DEMON_HP * 2);
			isShouting = true;
			attackCooldown = DEMON_ATTACK2_CD;
			attackingTime = DEMON_ATTACK2_TIME;
		}

		void DemonSamurai::setCont(int c) {
			cont = c;
		}

		void DemonSamurai::setIsLastBuffed(bool isLb) {
			isLastBuffed = isLb;
		}	

		void DemonSamurai::setIsShouting(bool iSs) {
			isShouting = iSs;
		}

		void DemonSamurai::setShoutTimer(float sTimer) {
			shoutTimer = sTimer;
		}

		void DemonSamurai::update(float dt) {
			cout << cont << endl;
			updateSprite(dt);
			if (cont == 1 && !isLastBuffed) {
				shout();
			}
			
			incrementAttackTime(dt);
			isMoving = false;

			Player* nearestPlayer = getNearestPlayer();
			float playerDistance = fabs(position.x - nearestPlayer->getPosition().x);

			if (!isShouting) {
				if (playerDistance <= DEMON_VISION && !isDying) {
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

				if (playerDistance <= DEMON_ATTACK_DISTANCE && !isDying) {
					isMoving = false;
					attack();
				}
			}

			if (isAttacking) {
				impactTimer += dt;
				if (impactTimer >= DEMON_IMPACT_TIME) {
					if (pPlayer1) {
						if (pPlayer1->getIsActive()) {
							if (fabs(pPlayer1->getPosition().x - position.x) <= DEMON_ATTACK_RANGE && fabs(pPlayer1->getPosition().y - position.y) <= DEMON_ATTACK_RANGEHEIGHT)
								pPlayer1->receiveDamage(getDamagePoints());
						}
					}

					if (pPlayer2) {
						if (pPlayer2->getIsActive()) {
							if (fabs(pPlayer2->getPosition().x - position.x) <= DEMON_ATTACK_RANGE && fabs(pPlayer2->getPosition().y - position.y) <= DEMON_ATTACK_RANGEHEIGHT)
								pPlayer2->receiveDamage(getDamagePoints());
						}
					}
					impactTimer = 0;
				}
			}

			velocity.y += GRAVITY * dt; // Incrementa velocidade vertical
			position.x += velocity.x * dt;
			position.y += velocity.y * dt;

			setCanJump(false);
			pCollision->notifyCollision(this, dt);
			
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
				sprite->addNewAnimation(GraphicalElements::Animation_ID::hurt, "demon_hurt.png", 4);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::death, "demon_death.png", 26);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::shout, "demon_shout.png", 17);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::idle2, "demon_idle2.png", 6);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::run2, "demon_run2.png", 8);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::attack2, "demon_attack2.png", 7);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::hurt2, "demon_hurt2.png", 4);
			}
			
			body->setOrigin(size.x / 2 + 31, size.y / 2 + 63);
		}

		void DemonSamurai::updateSprite(float dt) {
			if (!isLastBuffed) {
				if (isShouting) {
					shoutTimer += dt;
					sprite->update(GraphicalElements::Animation_ID::shout, !isFacingLeft, position, dt);
					if (shoutTimer >= DEMON_SHOUT_TIME) { isShouting = false; isLastBuffed = true; }
				}

				else if (isDying) {
					deathTimer += dt;
					sprite->update(GraphicalElements::Animation_ID::death, !isFacingLeft, position, dt);
					if (deathTimer >= DEMON_DEATH_TIME) { cont--; isActive = false; }
				}

				else if (isAttacking) {
					sprite->update(GraphicalElements::Animation_ID::attack, !isFacingLeft, position, dt);
				}

				else if (isHurting) {
					hurtingTimer += dt;
					sprite->update(GraphicalElements::Animation_ID::hurt, !isFacingLeft, position, dt);
					if (hurtingTimer >= DEMON_HURT_TIME) { isHurting = false; hurtingTimer = 0; }
				}

				else if (isMoving) {
					sprite->update(GraphicalElements::Animation_ID::run, !isFacingLeft, position, dt);
				}

				else {
					sprite->update(GraphicalElements::Animation_ID::idle, !isFacingLeft, position, dt);
				}
			}

			else {
				if (isDying) {
					deathTimer += dt;
					sprite->update(GraphicalElements::Animation_ID::death, !isFacingLeft, position, dt);
					if (deathTimer >= DEMON_DEATH_TIME) isActive = false;
				}

				else if (isAttacking) {
					sprite->update(GraphicalElements::Animation_ID::attack2, !isFacingLeft, position, dt);
				}

				else if (isHurting) {
					hurtingTimer += dt;
					sprite->update(GraphicalElements::Animation_ID::hurt2, !isFacingLeft, position, dt);
					if (hurtingTimer >= DEMON_HURT_TIME) { isHurting = false; hurtingTimer = 0; }
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