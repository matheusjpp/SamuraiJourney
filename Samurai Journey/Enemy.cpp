#include "Enemy.h"

namespace Entities {

	namespace Characters {
		Enemy::Enemy(Math::CoordF pos, Math::CoordF size, ID id) :
			Character(pos, size, id), pPlayer(nullptr) {

		}

		Enemy::~Enemy() {

		}

		void Enemy::setPlayer(Player* p) {
			pPlayer = p;
		}

	}

}