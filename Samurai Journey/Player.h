#pragma once
#include "Platform.h"

#define PLAYER_SIZE_X 64.0f
#define PLAYER_SIZE_Y 42.0f

#define PLAYER_SPEED  200.0f // Player Velocity
#define GRAVITY 500.0f 
#define JUMP 500.0f

#define PLAYER_HP 100.0f 
#define PLAYER_ATTACK_CD 0.2f
#define PLAYER_ATTACK_TIME 1.0f

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
			bool isDefending;
			bool isHealing;
			float healCooldown;

		public:
			Player(Math::CoordF pos = Math::CoordF(0, 0), bool isPlayer1 = true);

			~Player();

			bool getIsPlayer1() const;

			void update(float dt);

			void setTextures();
			
			void updateSprite(float dt);

			void execute();

			void attack();

			void defend();

			void stopDefending();

			bool getIsDefending();

			void usePotion();

			void centerCamera();
		};

	}

}