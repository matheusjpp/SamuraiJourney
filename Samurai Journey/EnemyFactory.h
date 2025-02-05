#pragma once
#include "EntityFactory.h"

namespace Entities {

	namespace Factories {

		class EnemyFactory : public EntityFactory {
		public:
			EnemyFactory();

			~EnemyFactory();

			Entities::Entity* FactoryMethod(Math::CoordF position, bool isPlayer1, bool isFake, List::EntitiesList* movingEntities, Levels::Level* level, ID id);

		};

	}

}