#pragma once
#include "Platform.h"

#define PLAYER_SIZE_X 30.0f // SCREEN_WIDTH / 9.6
#define PLAYER_SIZE_Y 50.0f // SCREEN_HEIGHT / 5.1
#define PLAYER_SPEED  200.0f // Player Velocity

namespace Entities {

	namespace Characters {

		class Player : public Character {
		private:
			const bool isPlayer1;

		public:
			Player(Math::CoordF pos = Math::CoordF(0, 0), bool isPlayer1 = true);

			~Player();

			void update(float dt);

			//void initialize();

		};

	}

}