#include "Portal.h"

namespace Entities {

	namespace Obstacles {

		Portal::Portal(Math::CoordF pos, Math::CoordF size, ID id) : canTeleport(false), isRequesting(false),
			Obstacle(pos, size, id)
		{
			setTextures();
		}

		Portal::~Portal() {

		}

		void Portal::setCanTeleport(bool canTp) {
			canTeleport = canTp;
		}

		const bool Portal::getCanTeleport() const {
			return canTeleport;
		}

		void Portal::setTeleportRequest(bool tpReq) {
			isRequesting = tpReq;
		}

		const bool Portal::getTeleportRequest() const {
			return isRequesting;
		}

		void Portal::update(float dt) {
			updateSprite(dt);
			body->setPosition(position.x, position.y);
		}

		void Portal::execute() {
			update(pGraphic->getDeltaTime());
			render();
		}

		void Portal::setTextures() {
			sprite = new GraphicalElements::Animation(body, Math::CoordF(7, 7));

			sprite->addNewAnimation(GraphicalElements::Animation_ID::portal, "portal.png", 8);
		}

		void Portal::updateSprite(float dt) {
			sprite->update(GraphicalElements::Animation_ID::portal, false, position, dt);
		}

	}

}