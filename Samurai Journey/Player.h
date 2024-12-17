#pragma once
#include "Obstacle.h"

#define PLAYER_SIZE_X 30.0f // SCREEN_WIDTH / 9.6
#define PLAYER_SIZE_Y 50.0f // SCREEN_HEIGHT / 5.1
#define PLAYER_SPEED  200.0f // Player Velocity

namespace Entities {

	class Player : public Entity {
	private:
		const bool isPlayer1;
		Obstacle* pObst;

	public:
		Player(Math::CoordF pos = Math::CoordF(0, 0), bool isPlayer1 = true);

		~Player();

		Obstacle* getObs() const;

		void update(float dt);

		//void initialize();

	};

}