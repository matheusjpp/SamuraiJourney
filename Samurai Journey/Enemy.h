#pragma once
#include "Player.h"

namespace Entities {
	class Enemy : public Entity {
	private:
		Player* pPlayer;

	public:
		Enemy(Math::CoordF pos = Math::CoordF(0, 0));

		~Enemy();

		void setPlayer(Player* p);

		void update(float dt);
	};
}