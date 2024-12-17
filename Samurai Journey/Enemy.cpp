#include "Enemy.h"

namespace Entities {
	Enemy::Enemy(Math::CoordF pos):
		Entity(pos, Math::CoordF(PLAYER_SIZE_X, PLAYER_SIZE_Y), ID::enemy), pPlayer(nullptr) {
		mudarCor(sf::Color(0, 0, 255));
	}

	Enemy::~Enemy() {

	}

	void Enemy::setPlayer(Player* p) {
		pPlayer = p;
	}

	void Enemy::update(float dt) {
		
		if (position.y < pPlayer->getObs()->getPosition().y - 50.0f) {
			
			position.y += PLAYER_SPEED * dt / 2.f;
		}

		if (position.x > pPlayer->getPosition().x) {
			position.x -= PLAYER_SPEED * dt / 3.0f;
		}

		if (position.x < pPlayer->getPosition().x) {
			position.x += PLAYER_SPEED * dt / 3.0f;
		}

		body->setPosition(sf::Vector2f(position.x, position.y));
		
	}
}