#include "Player.h"
#include "PlayerController.h"
#include "Level.h"

namespace Entities {

	namespace Characters {

		Player::Player(Math::CoordF pos, bool isPlayer1, Levels::Level* level) : isDefending(false), isHealing(false), isSlowed(false),
			healTimer(0), points(0), pLevel(level), speed(PLAYER_SPEED),
			Character(pos, Math::CoordF(PLAYER_SIZE_X, PLAYER_SIZE_Y), ID::player), isPlayer1(isPlayer1) 
		{
			setHP(PLAYER_HP);
			damagePoints = PLAYER_ATTACK_DAMAGE;
			attackCooldown = PLAYER_ATTACK_CD;
			attackingTime = PLAYER_ATTACK_TIME;

			pBush = new Obstacles::Bush(Math::CoordF(0,0), (Math::CoordF(0,0)));
			pControl = new Managers::KeyManagement::PlayerController(this);
			setTextures();
		}

		Player::~Player() {
			if (pControl) {
				pControl->setIsActive(false);
				pControl = nullptr;
			}
		}

		bool Player::getIsPlayer1() const {
			return isPlayer1;
		}

		void Player::update(float dt) {
			updateSprite(dt);
			incrementAttackTime(dt);
			speed = PLAYER_SPEED;
			if (!isDefending) {
				if (isMoving) {
					setSlowness();
					if (isFacingLeft) {
						setVelocityX(speed);
					}
					else {
						setVelocityX(-speed);
					}
				}
				else {
					setVelocityX(0);
				}
			}

			if (isAttacking) {
				impactTimer += dt;
				if (impactTimer >= PLAYER_IMPACT_TIME) {
					checkEnemiesInRange();
					impactTimer = 0;
				}
			}

			velocity.y += GRAVITY * dt;
			position.x += velocity.x * dt;
			position.y += velocity.y * dt;
			
			isSlowed = false;
			setCanJump(false);
			pCollision->notifyCollision(this, dt);
			body->setPosition(sf::Vector2f(position.x, position.y));
		}

		void Player::execute() {
			update(pGraphic->getDeltaTime());
			render();
		}

		void Player::setTextures() {
			sprite = new GraphicalElements::Animation(body, Math::CoordF(2.5, 2.5));	

			if (isPlayer1) {
				sprite->addNewAnimation(GraphicalElements::Animation_ID::idle, "p1_idle.png", 10);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::walk, "p1_walk.png", 16);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::attack, "p1_attack.png", 6); 
				sprite->addNewAnimation(GraphicalElements::Animation_ID::airattack, "p1_airattack.png", 6);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::jump, "p1_jump.png", 3);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::fall, "p1_fall.png", 3);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::defend, "p1_defend.png", 6);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::heal, "p1_heal.png", 15);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::hurt, "p1_hurt.png", 4);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::death, "p1_death.png", 9);
			
			}

			else {
				sprite->addNewAnimation(GraphicalElements::Animation_ID::idle, "p2_idle.png", 10);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::walk, "p2_walk.png", 16);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::attack, "p2_attack.png", 6);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::airattack, "p2_airattack.png", 6);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::jump, "p2_jump.png", 3);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::fall, "p2_fall.png", 3);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::defend, "p2_defend.png", 6);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::heal, "p2_heal.png", 15);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::hurt, "p2_hurt.png", 4);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::death, "p2_death.png", 9);
			}

			body->setOrigin(size.x / 2 + 15, size.y / 2 + 52);
			
		}

		void Player::updateSprite(float dt) {
			if (isDying) {
				deathTimer += dt;
				sprite->update(GraphicalElements::Animation_ID::death, !isFacingLeft, position, dt);
				if (deathTimer >= PLAYER_DEATH_TIME) isActive = false;
			}

			else if (isAttacking) {
				if (!canJump)
					sprite->update(GraphicalElements::Animation_ID::airattack, !isFacingLeft, position, dt);
				else
					sprite->update(GraphicalElements::Animation_ID::attack, !isFacingLeft, position, dt);
			}

			else if (isHurting) {
				hurtingTimer += dt;
				sprite->update(GraphicalElements::Animation_ID::hurt, !isFacingLeft, position, dt);
				if (hurtingTimer >= PLAYER_HURT_TIME) { isHurting = false; hurtingTimer = 0; }
			}

			else if (isDefending) {
				sprite->update(GraphicalElements::Animation_ID::defend, !isFacingLeft, position, dt);
			}

			else if (isHealing) {
				healTimer += dt;
				sprite->update(GraphicalElements::Animation_ID::heal, !isFacingLeft, position, dt);
				if (healTimer >= PLAYER_HEAL_TIME) { isHealing = false; }
			}

			else if (isHurting) {
				sprite->update(GraphicalElements::Animation_ID::hurt, !isFacingLeft, position, dt);
			}

			else if (!canJump) {
				if (velocity.y < 0)
					sprite->update(GraphicalElements::Animation_ID::jump, !isFacingLeft, position, dt);
				else
					sprite->update(GraphicalElements::Animation_ID::fall, !isFacingLeft, position, dt);
			}

			else if (isMoving) {
				sprite->update(GraphicalElements::Animation_ID::walk, !isFacingLeft, position, dt);
			}

			else {
				sprite->update(GraphicalElements::Animation_ID::idle, !isFacingLeft, position, dt);
			}
		}

		void Player::attack() {
			if (canAttack()) {
				isAttacking = true;
			}
			
		}

		void Player::defend() {
			if (canJump && !isMoving)
				isDefending = true;
		}

		void Player::stopDefending() {
			isDefending = false;
		}

		bool Player::getIsDefending() {
			return isDefending;
		}

		bool Player::getIsHealing() {
			return isHealing;
		}

		const float Player::getHealTimer() const {
			return healTimer;
		}

		void Player::usePotion() {
			isHealing = true;
		}

		void Player::centerCamera() {
			pGraphic->centerView(Math::CoordF(position.x, pGraphic->getWindowSize().y / 2));	
		}

		void Player::changeObserverState(bool active) {
			pControl->setIsActive(active);
		}

		void Player::checkEnemiesInRange() {
			List::EntitiesList* list = pLevel->getEntitiesList();
			for (auto it = list->begin(); it != list->end(); ++it) {
				if (auto* enemy = dynamic_cast<Characters::Enemy*>(*it)) {
					if (enemy->getIsActive()) {
						if (enemy->getPosition().y > 1000) enemy->receiveDamage(enemy->getHP());
						
						float playerX = position.x;
						float playerY = position.y - PLAYER_ATTACK_RANGEHEIGHT;
						float enemyX = enemy->getPosition().x;
						float enemyY = enemy->getPosition().y;

						bool inRangeY = fabs(playerY - enemyY) <= PLAYER_ATTACK_RANGEHEIGHT;

						if (!isFacingLeft) {
							if ((playerX - enemyX <= PLAYER_ATTACK_RANGE) && (playerX > enemyX) && inRangeY)
								enemy->receiveDamage(getDamagePoints());
						}
						else
							if ((enemyX - playerX <= PLAYER_ATTACK_RANGE) && (enemyX > playerX) && inRangeY)
								enemy->receiveDamage(getDamagePoints());
					}
					else if (!enemy->getCounted()) {
						points += 100;
						enemy->setCounted(true);
					}
				}
			}
		}

		void Player::setPoints(int pPoints) {
			if (isPlayer1) {
				points += pPoints;
			}
		}

		void Player::setSlowness() {
			if (isSlowed)
				speed *= pBush->getSlowness();
		}

		void Player::setIsSlowed(bool isSl) {
			isSlowed = isSl;
		}

		const int Player::getScorePoints() const {
			return points;
		}

		void Player::setIsDefending(bool isDef) {
			isDefending = isDef;
		}

		void Player::setIsActive(bool isAct) {
			isActive = isAct;
		}

		void Player::setIsHealing(bool isHeal) {
			isHealing = isHeal;
		}

		void Player::setHealTimer(float hTimer) {
			healTimer = hTimer;
		}
			
	}

}