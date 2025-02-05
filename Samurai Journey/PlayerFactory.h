#pragma once
#include "ObstacleFactory.h"

namespace Entities {

	namespace Factories {

		class PlayerFactory : public EntityFactory {
		public:
			PlayerFactory();

			~PlayerFactory();

			Entities::Entity* FactoryMethod(Math::CoordF position, bool isPlayer1, bool isFake, List::EntitiesList* movingEntities, Levels::Level* level, ID id);
		};

	}

}