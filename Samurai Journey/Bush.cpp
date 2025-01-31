#include "Bush.h"

namespace Entities {

	namespace Obstacles {

		Bush::Bush(Math::CoordF pos, Math::CoordF size, ID id) : slowness(BUSH_SLOWNESS), Obstacle(pos, size, id) {
			setTextures();
		}

		Bush::~Bush() {

		}

		const float Bush::getSlowness() const {
			return slowness;
		}

		void Bush::update(float dt) {
			updateSprite(dt);
			body->setPosition(position.x, position.y);
		}

		void Bush::execute() {
			update(pGraphic->getDeltaTime());
			render();
		}

		void Bush::setTextures() {
			sprite = new GraphicalElements::Animation(body, Math::CoordF(2.2, 2.2));

			sprite->addNewAnimation(GraphicalElements::Animation_ID::bush, "bush.png", 1);
		}

		void Bush::updateSprite(float dt) {
			sprite->update(GraphicalElements::Animation_ID::bush, false, position, dt);
		}

	}

}