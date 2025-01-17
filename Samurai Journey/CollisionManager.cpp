#include "CollisionManager.h"
#include "Character.h"

namespace Managers {
	
	namespace Collisions {

		CollisionManager* CollisionManager::pCollision = nullptr;

		CollisionManager::CollisionManager(List::EntitiesList* movingEntities, List::EntitiesList* staticEntities) : movingEntities(movingEntities), staticEntities(staticEntities) {

		}

		CollisionManager::~CollisionManager() {
			movingEntities = nullptr;
			staticEntities = nullptr;
		}

		CollisionManager* CollisionManager::getInstance() {
			if (pCollision == nullptr) {
				pCollision = new CollisionManager();
			}
			return pCollision;
		}

		void CollisionManager::setLists(List::EntitiesList& stEnt, List::EntitiesList& movEnt) {
			staticEntities = &stEnt;
			movingEntities = &movEnt;

		}

		void CollisionManager::notifyCollision(Entities::MovingEntity* sender, float dt) {
			Entities::Entity* otherEntity = nullptr;
			
			Math::CoordF intersect;
			Math::CoordF centerDistance;

			/* Collision with non-moving entities */
			for (auto itS = staticEntities->begin(); itS != staticEntities->end(); ++itS) {
				otherEntity = (*itS);
				
				if (sender && otherEntity) {
					centerDistance.x = sender->getPosition().x - otherEntity->getPosition().x;
					centerDistance.y = sender->getPosition().y - otherEntity->getPosition().y;

					intersect.x = fabs(centerDistance.x) - (sender->getSize().x / 2.0f + otherEntity->getSize().x / 2.0f);
					intersect.y = fabs(centerDistance.y) - (sender->getSize().y / 2.0f + otherEntity->getSize().y / 2.0f);

					if (intersect.x < 0.0f && intersect.y < 0.0f) {
						manageCollision(sender, otherEntity, intersect, dt);
					}
				}
			}

			/* Collision with moving entities */
			for (auto itM = movingEntities->begin(); itM != movingEntities->end(); ++itM) {
				if (*itM != sender) {
					otherEntity = (*itM);

					if (sender && otherEntity) {
						centerDistance.x = sender->getPosition().x - otherEntity->getPosition().x;
						centerDistance.y = sender->getPosition().y - otherEntity->getPosition().y;

						intersect.x = fabs(centerDistance.x) - (sender->getSize().x / 2.0f + otherEntity->getSize().x / 2.0f);
						intersect.y = fabs(centerDistance.y) - (sender->getSize().y / 2.0f + otherEntity->getSize().y / 2.0f);

						if (intersect.x < 0.0f && intersect.y < 0.0f) {
							manageCollision(sender, otherEntity, intersect, dt);
						}
					}
				}
			}
		}

		void CollisionManager::manageCollision(Entities::MovingEntity* sender, Entities::Entity* otherEntity, Math::CoordF intersection, float dt) {
			/* Collision notified by a player */
			if (sender->getID() == ID::player) {
				if (otherEntity->getID() == ID::enemy) { // Collision with meelee enemy 
					//take damage (dependendo de como for feito o ataque do inimigo)
					moveOnCollision(sender, otherEntity, intersection, dt);
				}

				else if (otherEntity->getID() == ID::platform) { // Collision with platform
					moveOnCollision(sender, otherEntity, intersection, dt);
				}

				// else if (otherEntity->getID() == ID::projectile) so vai ter take damage e desativacao do projetil
			}

			/* Collision notified by an enemy */ //tem que fazer de cada um especificamente pq o id é sobrescrito nas classes especializadas, mas sempre vai ser isso
			else if (sender->getID() == ID::enemy) {
				moveOnCollision(sender, otherEntity, intersection, dt);
			}
		}

		void CollisionManager::moveOnCollision(Entities::MovingEntity* sender, Entities::Entity* otherEntity, Math::CoordF intersection, float dt) {
			Math::CoordF senderPos = sender->getPosition();
			Math::CoordF otherPos = otherEntity->getPosition();

			/* Collision on x direction */
			if (intersection.x > intersection.y) {
				if (senderPos.x < otherPos.x)
					senderPos.x += intersection.x;
				else
					senderPos.x -= intersection.x;

				sender->setPosition(senderPos);
				sender->setVelocityX(0.0f);
			}

			/* Collision on y direction */
			else {
				if (senderPos.y < otherPos.y) {
					senderPos.y += intersection.y;
					if (auto* character = dynamic_cast<Entities::Characters::Character*>(sender)) {
						character->setCanJump(true);
					}
				}
					
				else {
					senderPos.y -= intersection.y;
				}
					
				sender->setPosition(senderPos);
				sender->setVelocityY(0.0f);
			}
		}

	}

}