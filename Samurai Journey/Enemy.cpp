#include "Enemy.h"

namespace Entities {

	namespace Characters {
		Enemy::Enemy(Math::CoordF pos, Math::CoordF size, ID id) :
			Character(pos, size, id), pPlayer1(nullptr) {
			
		}

		Enemy::~Enemy() {

		}

		void Enemy::setPlayers(Player* p1, Player* p2) {
			pPlayer1 = p1;
			if (p2) pPlayer2 = p2;
		}

		Player* Enemy::getNearestPlayer() {
			if (!pPlayer2 || !pPlayer2->getIsActive()) return pPlayer1;
			if (!pPlayer1->getIsActive()) return pPlayer2;

			Math::CoordF d1 = fabs(position.x - pPlayer1->getPosition().x);
			Math::CoordF d2 = fabs(position.x - pPlayer2->getPosition().x);
			return (d1.x > d2.x ? pPlayer2 : pPlayer1);
		}

	}

}