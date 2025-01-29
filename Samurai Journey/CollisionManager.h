#pragma once
#include "Mediator.h"

namespace Entities {
	namespace Characters {
		class Player;
	}
}

namespace Managers {

	namespace Collisions {

		class CollisionManager : public Mediator {
		private:
			List::EntitiesList* staticEntities;
			List::EntitiesList* movingEntities;

			static CollisionManager* pCollision;

			CollisionManager(List::EntitiesList* movingEntities = nullptr, List::EntitiesList* staticEntities = nullptr);

		public:
			~CollisionManager();

			static CollisionManager* getInstance();

			void setLists(List::EntitiesList& stEnt, List::EntitiesList& movEnt);

			void notifyCollision(Entities::MovingEntity* sender, float dt);

			void manageCollision(Entities::MovingEntity* sender, Entities::Entity* otherEntity, Math::CoordF intersection, float dt);

			void moveOnCollision(Entities::MovingEntity* sender, Entities::Entity* otherEntity, Math::CoordF intersection, float dt);
		};

	}

}
