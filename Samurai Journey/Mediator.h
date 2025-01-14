#pragma once
#include "EntitiesList.h"

namespace Managers {

	namespace Collisions {

		class Mediator	{
		public:
			virtual void notify(Entities::Entity* sender) = 0;
			virtual ~Mediator() = default;
		};

	}

}