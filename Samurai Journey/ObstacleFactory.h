#pragma once
#include "EnemyFactory.h"

namespace Entities {

	namespace Factories {

		class ObstacleFactory : public EntityFactory {
		public:
			ObstacleFactory();

			~ObstacleFactory();

			Entities::Entity* FactoryMethod(Math::CoordF position, bool isPlayer1, bool isFake, List::EntitiesList* movingEntities, Levels::Level* level, ID id);

		};

	}

}