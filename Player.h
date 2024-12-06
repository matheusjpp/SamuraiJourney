#pragma once
#include "Entity.h"

#define PLAYER_SIZE_X 200.0f // SCREEN_WIDTH / 9.6
#define PLAYER_SIZE_Y 200.0f // SCREEN_HEIGHT / 5.1

namespace Entities {

	class Player : public Entity {
	private:
		const bool isPlayer1;

	public:
		Player(Math::CoordF pos = Math::CoordF(0, 0), bool isPlayer1 = true);

		~Player();

		void update(float dt);

		void initialize();

	};

}