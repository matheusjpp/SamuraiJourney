#pragma once
#include "Platform.h"

/* TAMANHO CERTO
#define PLAYER_SIZE_X 30.0f
#define PLAYER_SIZE_Y 40.0f
*/

#define PLAYER_SIZE_X 64.0f
#define PLAYER_SIZE_Y 42.0f

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
			bool isAttacking;
			float attackCooldown;
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

		};

	}

}