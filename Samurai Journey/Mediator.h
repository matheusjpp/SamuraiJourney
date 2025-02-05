#pragma once
#include "MovingEntity.h"

namespace Managers {

	namespace Collisions {

		class Mediator	{
		protected:
			List::EntitiesList* staticEntities;
			List::EntitiesList* movingEntities;

		public:
			Mediator(List::EntitiesList* movingEntities, List::EntitiesList* staticEntities) : movingEntities(movingEntities), staticEntities(staticEntities) {}
			virtual void notifyCollision(Entities::MovingEntity* sender, float dt) = 0;
			virtual ~Mediator() { movingEntities = nullptr; staticEntities = nullptr; }
		};

	}

}