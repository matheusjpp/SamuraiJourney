#include "ObstacleFactory.h"

namespace Entities {

	namespace Factories {

		ObstacleFactory::ObstacleFactory() {

		}

		ObstacleFactory::~ObstacleFactory() {

		}

		Entities::Entity* ObstacleFactory::FactoryMethod(Math::CoordF position, bool isPlayer1, bool isFake, List::EntitiesList* movingEntities, Levels::Level* level, ID id) {
            switch (id) {
                case ID::platform: {
                    Entities::Obstacles::Obstacle* pE = new Obstacles::Platform(Math::CoordF(position), Math::CoordF(10.0f, 10.0f), isFake);
                    if (pE) {
                        return dynamic_cast<Entities::Entity*>(pE);
                    }
                    break;
                }
                case ID::bush: {
                    Entities::Obstacles::Bush* pE = new Obstacles::Bush(Math::CoordF(position));
                    if (pE) {
                        return dynamic_cast<Entities::Entity*>(pE);
                    }
                    break;
                }
                case ID::fire: {
                    Entities::Obstacles::Fire* pE = new Obstacles::Fire(Math::CoordF(position));
                    if (pE) {
                        return dynamic_cast<Entities::Entity*>(pE);
                    }
                    break;
                }
                case ID::portal: {
                    Entities::Obstacles::Portal* pE = new Obstacles::Portal(Math::CoordF(position));
                    if (pE) {
                        return dynamic_cast<Entities::Entity*>(pE);
                    }
                }
            }
		}

	}

}