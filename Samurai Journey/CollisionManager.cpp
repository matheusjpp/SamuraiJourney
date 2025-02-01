#include "CollisionManager.h"
#include "Player.h"
#include "Arrow.h"

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
					if ((*itM)->getIsActive()) {
						auto* enemy = dynamic_cast<Entities::Characters::Character*>(otherEntity);
						if (!enemy || !(enemy->getIsDying())) {
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
			}
		}

		void CollisionManager::manageCollision(Entities::MovingEntity* sender, Entities::Entity* otherEntity, Math::CoordF intersection, float dt) {
			/* Collision notified by a player */
			if (sender->getID() == ID::player) {
				if (otherEntity->getID() == ID::platform ||
					otherEntity->getID() == ID::wolf ||
					otherEntity->getID() == ID::archer ||
					otherEntity->getID() == ID::demonsamurai) {
					moveOnCollision(sender, otherEntity, intersection, dt);
				}

				else if (otherEntity->getID() == ID::bush) {
					if (auto* player = dynamic_cast<Entities::Characters::Player*>(sender)) {
						if (auto* bush = dynamic_cast<Entities::Obstacles::Bush*>(otherEntity)) {
							player->setIsSlowed(true);
						}
					}
				}

				else if (otherEntity->getID() == ID::arrow) {
					 if (auto* arrow = dynamic_cast<Entities::Arrow*>(otherEntity)) {
						if (arrow) {
						if (auto* player = dynamic_cast<Entities::Characters::Character*>(sender)) {
							player->receiveDamage(arrow->getDamagePoints());
						}
						}
					 }
				}
				// OBSTÁCULOS QUE DEBUFFAM
			}

			/* Collision notified by an enemy */ 
			else if (sender->getID() == ID::wolf || sender->getID() == ID::archer || sender->getID() == ID::demonsamurai) {
				moveOnCollision(sender, otherEntity, intersection, dt);
			}
			/*
			else if (sender->getID() == ID::demonsamurai) {
				moveOnCollision(sender, otherEntity, intersection, dt);
			}

			else if (sender->getID() == ID::archer) {
				moveOnCollision(sender, otherEntity, intersection, dt);
			}*/

			else if (sender->getID() == ID::arrow) {
				if (otherEntity->getID() == ID::player || otherEntity->getID() == ID::platform)
				sender->setIsActive(false);
			}
		}

		void CollisionManager::moveOnCollision(Entities::MovingEntity* sender, Entities::Entity* otherEntity, Math::CoordF intersection, float dt) {
			if (otherEntity->getID() == ID::bush || otherEntity->getID() == ID::fire) return;

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
						if (auto* player = dynamic_cast<Entities::Characters::Player*>(sender)) {
							if (player->getIsDefending())
								player->setCanJump(false);
						}
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