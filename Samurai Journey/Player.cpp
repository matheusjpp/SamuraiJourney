#include "Player.h"

namespace Entities {

	Player::Player(Math::CoordF pos, bool isPlayer1) :
	Entity(pos, Math::CoordF(PLAYER_SIZE_X, PLAYER_SIZE_Y), ID::player), isPlayer1(isPlayer1) {
		mudarCor(sf::Color(255, 0, 0));
		pObst = new Obstacle();
	}

	Player::~Player() {
		delete pObst;
	}

	Obstacle* Player::getObs() const {
		return pObst;
	}

	void Player::update(float dt) {
		if (position.y > pObst->getPosition().y - 60.0f) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				position.y -= 50;
			}
		}
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			position.y += PLAYER_SPEED*dt;
		}*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			position.x += PLAYER_SPEED*dt;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			position.x -= PLAYER_SPEED*dt;
		}
		body->setPosition(sf::Vector2f(position.x, position.y));
		
		if (position.y < pObst->getPosition().y - 50.0f) {
			position.y += PLAYER_SPEED * dt / 2.f;
		}
	}

	//void Player::initialize() {
		////exit(1);
	//}


}