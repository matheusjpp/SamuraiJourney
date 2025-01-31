#pragma once
#include "Player.h"

namespace Entities {

	namespace Characters {

		class Enemy : public Character {
		protected:
			Player* pPlayer1;
			Player* pPlayer2;
			Math::CoordF p1distance;

		public:
			Enemy(Math::CoordF pos = Math::CoordF(0, 0), Math::CoordF size = Math::CoordF(0, 0), ID id = ID::empty);

			virtual ~Enemy();

			void setPlayers(Player* p1, Player* p2 = nullptr);

			Player* getNearestPlayer();

			virtual void update(float dt) = 0;

			virtual void execute() = 0;

			virtual void attack() = 0;

			virtual void setTextures() = 0;

			virtual void updateSprite(float dt) = 0;
		};

	}

}