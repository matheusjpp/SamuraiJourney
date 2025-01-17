#pragma once
#include "Platform.h"

#define PLAYER_SIZE_X 30.0f 
#define PLAYER_SIZE_Y 50.0f
#define PLAYER_SPEED  200.0f // Player Velocity
#define GRAVITY 500.0f 
#define JUMP 500.0f

namespace Managers {
	namespace KeyManagement {
		class PlayerController;
	}
}

namespace Entities {

	namespace Characters {

		class Player : public Character {
		private:
			Managers::KeyManagement::PlayerController* pControl;
			const bool isPlayer1;

		public:
			Player(Math::CoordF pos = Math::CoordF(0, 0), bool isPlayer1 = true);

			~Player();

			bool getIsPlayer1();

			void update(float dt);

			void execute();

			void run();

			void stopRunning();

			void attack();

			void defend();

			void usePotion();

		};

	}

}