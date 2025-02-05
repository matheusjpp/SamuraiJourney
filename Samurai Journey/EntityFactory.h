#pragma once
#include "ConcreteMenu.h"

namespace Entities {

	namespace Factories {

		class EntityFactory {
		public:
			EntityFactory() = default;

			~EntityFactory() = default;

			virtual Entities::Entity* FactoryMethod(Math::CoordF position, bool isPlayer1, bool isFake, List::EntitiesList* movingEntities, Levels::Level* level, ID id) = 0;
		};

	}
}