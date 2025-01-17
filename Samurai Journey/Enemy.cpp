#include "Enemy.h"

namespace Entities {

	namespace Characters {
		Enemy::Enemy(Math::CoordF pos):
			Character(pos, Math::CoordF(PLAYER_SIZE_X, PLAYER_SIZE_Y), ID::enemy), pPlayer(nullptr) {
			mudarCor(sf::Color(0, 0, 255));
		}

		Enemy::~Enemy() {

		}

		void Enemy::setPlayer(Player* p) {
			pPlayer = p;
		}

		void Enemy::update(float dt) {
		
			//position.y += PLAYER_SPEED * dt / 2.f;

			position.y += PLAYER_SPEED * dt;

			if (position.x > pPlayer->getPosition().x) {
				position.x -= PLAYER_SPEED * dt / 3.0f;
			}

			if (position.x < pPlayer->getPosition().x) {
				position.x += PLAYER_SPEED * dt / 3.0f;
			}

			pCollision->notifyCollision(this, dt);

			body->setPosition(sf::Vector2f(position.x, position.y));
		
		}

		void Enemy::execute() {
			update(pGraphic->getDeltaTime());
			render();
		}

		void Enemy::attack() {

		}

	}

}