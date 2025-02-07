#pragma once
#include "PlayerFactory.h"

namespace Entities {

	namespace Factories {

		class ArrowFactory : public EntityFactory {
		public:
			ArrowFactory();

			~ArrowFactory();

			Entities::Entity* FactoryMethod(Math::CoordF position, bool isPlayer1, bool isFake, List::EntitiesList* movingEntities, Levels::Level* level, ID id);

		};

	}

}

