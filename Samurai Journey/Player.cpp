#include "Player.h"

namespace Entities {

	Player::Player(Math::CoordF pos, bool isPlayer1) :
	Entity(pos, Math::CoordF(PLAYER_SIZE_X, PLAYER_SIZE_Y), ID::player), isPlayer1(isPlayer1) {
		mudarCor(sf::Color(255, 0, 0));
	}

	Player::~Player() {

	}

	void Player::update(float dt) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			position.y -= PLAYER_SPEED*dt;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			position.y += PLAYER_SPEED*dt;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			position.x += PLAYER_SPEED*dt;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			position.x -= PLAYER_SPEED*dt;
		}
		body->setPosition(sf::Vector2f(position.x, position.y));
	}

	void Player::initialize() {
		exit(1);
	}


}