#pragma once
#include "Player.h"

namespace Entities {

	namespace Characters {

		class Enemy : public Character {
		protected:
			Player* pPlayer;

		public:
			Enemy(Math::CoordF pos = Math::CoordF(0, 0), Math::CoordF size = Math::CoordF(0, 0), ID id = ID::empty);

			virtual ~Enemy();

			void setPlayer(Player* p);

			virtual void update(float dt) = 0;

			virtual void execute() = 0;

			virtual void attack() = 0;

			virtual void setTextures() = 0;

			virtual void updateSprite(float dt) = 0;
		};

	}

}