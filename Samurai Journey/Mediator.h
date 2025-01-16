#pragma once
#include "MovingEntity.h"

namespace Managers {

	namespace Collisions {

		class Mediator	{
		public:
			virtual void notifyCollision(Entities::MovingEntity* sender, float dt) = 0;
			virtual ~Mediator() = default;
		};

	}

}