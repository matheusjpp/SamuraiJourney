#include "Wolf.h"

namespace Entities {

	namespace Characters {

		Wolf::Wolf(Math::CoordF pos, ID id) :
			Enemy(pos, Math::CoordF(WOLF_SIZE_X, WOLF_SIZE_Y), id) {
			
			setTextures();
		}

		Wolf::~Wolf() {

		}

		void Wolf::update(float dt) {
			
			position.y += PLAYER_SPEED * dt;
			isMoving = false;

			if (position.x > pPlayer->getPosition().x) {
				position.x -= WOLF_SPEED * dt / 3.0f;
				isFacingLeft = false;
				isMoving = true;
			}

			if (position.x < pPlayer->getPosition().x) {
				position.x += WOLF_SPEED * dt / 3.0f;
				isFacingLeft = true;
				isMoving = true;
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

		void Wolf::execute() {
			update(pGraphic->getDeltaTime());
			render();
		}

		void Wolf::attack() {

		}

		void Wolf::setTextures() {
			sprite = new GraphicalElements::Animation(body, Math::CoordF(4, 2));

			sprite->addNewAnimation(GraphicalElements::Animation_ID::idle, "wolf_idle.png", 6);
			sprite->addNewAnimation(GraphicalElements::Animation_ID::run, "wolf_run.png", 6);
			sprite->addNewAnimation(GraphicalElements::Animation_ID::jump, "wolf_jump.png", 3);
			sprite->addNewAnimation(GraphicalElements::Animation_ID::attack, "ATTACK 3.png", 5);

			body->setSize(sf::Vector2f(64.0f, 42.0f));
			body->setOrigin(size.x / 2, size.y / 2 + 9);
		}

		void Wolf::updateSprite(float dt) {
			if (!canJump) {
				sprite->update(GraphicalElements::Animation_ID::jump, isFacingLeft, position, dt);
			}

			else if (isMoving) {
				sprite->update(GraphicalElements::Animation_ID::attack, isFacingLeft, position, dt);
			}

			else {
				sprite->update(GraphicalElements::Animation_ID::idle, isFacingLeft, position, dt);
			}
		}

	}

}