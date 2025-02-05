#pragma once
#include "Mediator.h"

namespace Entities {
	class Arrow;
	namespace Characters {
		class Player;
	}
}

namespace Levels {
	class BossLevel;
}

namespace Managers {

	namespace States {
		class StateManager;
	}

	namespace Collisions {

		class CollisionManager : public Mediator {
		private:
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
