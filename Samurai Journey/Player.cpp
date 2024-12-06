#include "Player.h"

namespace Entities {

	Player::Player(Math::CoordF pos, bool isPlayer1) :
	Entity(pos, Math::CoordF(PLAYER_SIZE_X, PLAYER_SIZE_Y), ID::player), isPlayer1(isPlayer1) {

	}

	Player::~Player() {

	}

	void Player::update(float dt) {

	}

	void Player::initialize() {
		exit(1);
	}

}