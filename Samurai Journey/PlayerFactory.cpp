#include "PlayerFactory.h"

namespace Entities {

	namespace Factories {

		PlayerFactory::PlayerFactory() {

		}

		PlayerFactory::~PlayerFactory() {

		}

        Entities::Entity* PlayerFactory::FactoryMethod(Math::CoordF position, bool isPlayer1, bool isFake, List::EntitiesList* movingEntities, Levels::Level* level, ID id) {
            switch (id) {
                case ID::player: {
                    Entities::Characters::Player* pE = new Characters::Player(Math::CoordF(position), isPlayer1, level);
                    if (pE) {
                        return dynamic_cast<Entities::Entity*>(pE);
                    }
                    break;
                }
            }
        }

	}

}