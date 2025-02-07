#include "ArrowFactory.h"

namespace Entities {

    namespace Factories {

        ArrowFactory::ArrowFactory() {

        }

        ArrowFactory::~ArrowFactory() {

        }

        Entities::Entity* ArrowFactory::FactoryMethod(Math::CoordF position, bool isPlayer1, bool isFake, List::EntitiesList* movingEntities, Levels::Level* level, ID id) {
            switch (id) {
                case ID::arrow: {
                    Arrow* pE = new Arrow(Math::CoordF(position));
                    if (pE) {
                        return dynamic_cast<Entities::Entity*>(pE);
                    }
                    break;
                }
            }
        }

    }

}

