#include "EnemyFactory.h"

namespace Entities {

	namespace Factories {

		EnemyFactory::EnemyFactory() : EntityFactory() {

		}

		EnemyFactory::~EnemyFactory() {

		}

		Entities::Entity* EnemyFactory::FactoryMethod(Math::CoordF position, bool isPlayer1, bool isFake, List::EntitiesList* movingEntities, Levels::Level* level, ID id) {
            switch (id) {
                case ID::wolf: {
                    Entities::Characters::Wolf* pE = new Characters::Wolf(Math::CoordF(position));
                    if (pE) {
                        return dynamic_cast<Entities::Entity*>(pE);
                    }
                    break;
                }
                case ID::archer: {
                    Entities::Characters::Archer* pE = new Characters::Archer(Math::CoordF(position), movingEntities);
                    if (pE) {
                        return dynamic_cast<Entities::Entity*>(pE);
                    }
                    break;
                }
                case ID::demonsamurai: {
                    Entities::Characters::DemonSamurai* pE = new Characters::DemonSamurai(Math::CoordF(position));
                    if (pE) {
                        return dynamic_cast<Entities::Entity*>(pE);
                    }
                    break;
                }
            }      
		}
	}

}