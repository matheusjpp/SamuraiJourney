#include "CollisionManager.h"

namespace Managers {
	
	namespace Collisions {

		CollisionManager::CollisionManager(List::EntitiesList* movingEntities, List::EntitiesList* staticEntities) : movingEntities(movingEntities), staticEntities(staticEntities) {

		}

		CollisionManager::~CollisionManager() {
			movingEntities = nullptr;
			staticEntities = nullptr;
		}

		void CollisionManager::notify(Entities::Entity* sender, float dt) {
			Entities::Entity* otherEntity = nullptr;
			
			Math::CoordF intersect;
			Math::CoordF centerDistance;

			List::List<Entities::Entity>::iterator itS = staticEntities->begin();

			/* Collision with non-moving entities */
			while (itS != staticEntities->end()) {
				otherEntity = (*itS);
				
				centerDistance.x = sender->getPosition().x - otherEntity->getPosition().x;
				centerDistance.y = sender->getPosition().y - otherEntity->getPosition().y;

				intersect.x = fabs(centerDistance.x) - (sender->getSize().x / 2.0f + otherEntity->getSize().x / 2.0f);
				intersect.y = fabs(centerDistance.y) - (sender->getSize().y / 2.0f + otherEntity->getSize().y / 2.0f);

				if (intersect.x < 0.0f && intersect.y < 0.0f) {
					manageCollisions(sender, otherEntity, intersect, dt);
				}

				++itS;
			}

			List::List<Entities::Entity>::iterator itM = movingEntities->begin();

			/* Collision with moving entities */
			while (itM != movingEntities->end()) {
				if (*itM != sender) {
					otherEntity = (*itM);

					centerDistance.x = sender->getPosition().x - otherEntity->getPosition().x;
					centerDistance.y = sender->getPosition().y - otherEntity->getPosition().y;
				
					intersect.x = fabs(centerDistance.x) - (sender->getSize().x / 2.0f + otherEntity->getSize().x / 2.0f);
					intersect.y = fabs(centerDistance.y) - (sender->getSize().y / 2.0f + otherEntity->getSize().y / 2.0f);

					if (intersect.x < 0.0f && intersect.y < 0.0f) {
						manageCollisions(sender, otherEntity, intersect, dt);
					}
				}
				++itM;
			}
		}

		void CollisionManager::manageCollisions(Entities::Entity* sender, Entities::Entity* otherEntity, Math::CoordF intersection, float dt) {

		}

	}

}