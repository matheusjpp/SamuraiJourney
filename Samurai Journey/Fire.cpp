#include "Fire.h"

namespace Entities {

	namespace Obstacles {

		Fire::Fire(Math::CoordF pos, Math::CoordF size, ID idfire) : Obstacle(pos, size, id), damage(FIRE_DAMAGE) {
			setTextures();
		}

		Fire::~Fire() {
		
		}

		void Fire::update(float dt) {
			updateSprite(dt);
			body->setPosition(position.x, position.y);
		}

		void Fire::execute() {
			update(pGraphic->getDeltaTime());
			render();
		}

		void Fire::setTextures() {
			sprite = new GraphicalElements::Animation(body, Math::CoordF(2.2, 2.2));

			sprite->addNewAnimation(GraphicalElements::Animation_ID::bush, "fire.png", 12);
		}

		void Fire::updateSprite(float dt) {
			sprite->update(GraphicalElements::Animation_ID::bush, false, position, dt);
		}

	}

}