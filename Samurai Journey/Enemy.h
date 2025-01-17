#pragma once
#include "Player.h"

namespace Entities {

	namespace Characters {

		class Enemy : public Character {
		private:
			Player* pPlayer;

		public:
			Enemy(Math::CoordF pos = Math::CoordF(0, 0));

			~Enemy();

			void setPlayer(Player* p);

			void update(float dt);

			void attack();
		};

	}

}