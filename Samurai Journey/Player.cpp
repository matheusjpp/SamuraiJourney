#include "Player.h"
#include "PlayerController.h"

namespace Entities {

	namespace Characters {

		Player::Player(Math::CoordF pos, bool isPlayer1) : isAttacking(false), attackCooldown(0), isDefending(false), isHealing(false), healCooldown(0),
			Character(pos, Math::CoordF(PLAYER_SIZE_X, PLAYER_SIZE_Y), ID::player), isPlayer1(isPlayer1) {
			
			pControl = new Managers::KeyManagement::PlayerController(this);
			setTextures();
		}

		Player::~Player() {

		}

		bool Player::getIsPlayer1() const {
			return isPlayer1;
		}

		void Player::update(float dt) {
			// Controle de movimento horizontal
			if (isMoving) {
				if (isFacingLeft) {
					setVelocityX(PLAYER_SPEED);
				}
				else {
					setVelocityX(-PLAYER_SPEED);
				}
			}
			else {
				setVelocityX(0);
			}

			if (isAttacking) {
				attackCooldown += dt;
				if (attackCooldown >= 1.0f) {
					isAttacking = false;
				}
			}

			if (isHealing) {
				healCooldown += dt;
				if (healCooldown >= 2.0f) {
					isHealing = false;
				}
			}

			velocity.y += GRAVITY * dt; // Incrementa velocidade vertical
			position.x += velocity.x * dt;
			position.y += velocity.y * dt;

			setCanJump(false);
			pCollision->notifyCollision(this, dt);
			updateSprite(dt);
			body->setPosition(sf::Vector2f(position.x, position.y));

			/*
			body->setOutlineColor(sf::Color(0, 0, 255));
			body->setOutlineThickness(1);
			*/
		}

		void Player::execute() {
			update(pGraphic->getDeltaTime());
			render();
		}

		void Player::setTextures() {
			sprite = new GraphicalElements::Animation(body, Math::CoordF(2, 2));

			if (isPlayer1) {
				sprite->addNewAnimation(GraphicalElements::Animation_ID::idle, "p1_idle.png", 10);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::walk, "p1_walk.png", 16);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::attack, "p1_attack.png", 6);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::airattack, "p1_airattack.png", 6);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::jump, "p1_jump.png", 3);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::fall, "p1_fall.png", 3);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::defend, "p1_defend.png", 6);
				sprite->addNewAnimation(GraphicalElements::Animation_ID::heal, "p1_heal.png", 15);
				
			}

			body->setOrigin(size.x / 2 + 17, size.y / 2 + 50);
		}

		void Player::updateSprite(float dt) {
			if (isDefending) {
				sprite->update(GraphicalElements::Animation_ID::defend, !isFacingLeft, position, dt);
			}

			else if (isHealing) {
				sprite->update(GraphicalElements::Animation_ID::heal, !isFacingLeft, position, dt);
			}

			else if (isAttacking) {
				if (!canJump) 
					sprite->update(GraphicalElements::Animation_ID::airattack, !isFacingLeft, position, dt);
				else 
					sprite->update(GraphicalElements::Animation_ID::attack, !isFacingLeft, position, dt);
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
			if (!isAttacking) {
				isAttacking = true;
				attackCooldown = 0.0f;
			}
			
		}

		void Player::defend() {
			if (canJump)
				isDefending = true;
		}

		void Player::stopDefending() {
			isDefending = false;
		}

		bool Player::getIsDefending() {
			return isDefending;
		}

		void Player::usePotion() {
			isHealing = true;
		}

	}

}