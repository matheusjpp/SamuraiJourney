#pragma once
#include "Mediator.h"

namespace Managers {

	namespace Collisions {

		class CollisionManager : public Mediator {
		private:
			List::EntitiesList* staticEntities;
			List::EntitiesList* movingEntities;

		public:
			CollisionManager(List::EntitiesList* movingEntities = nullptr, List::EntitiesList* staticEntities = nullptr);
			
			~CollisionManager();

			void notify(Entities::Entity* sender, float dt);

			void manageCollisions(Entities::Entity* sender, Entities::Entity* otherEntity, Math::CoordF intersection, float dt);
		};

	}

}
