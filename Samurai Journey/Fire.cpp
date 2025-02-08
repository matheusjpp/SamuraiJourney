#include "Fire.h"

namespace Entities {

	namespace Obstacles {

		Fire::Fire(Math::CoordF pos, Math::CoordF size, ID id) : Obstacle(pos, size, id), fireDamage(FIRE_DAMAGE), cooldownTimer(0) {
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
			sprite = new GraphicalElements::Animation(body, Math::CoordF(2, 2));

			sprite->addNewAnimation(GraphicalElements::Animation_ID::bush, "fire.png", 12);
		}

		void Fire::updateSprite(float dt) {
			sprite->update(GraphicalElements::Animation_ID::bush, false, position, dt);
		}

		const int Fire::getFireDamage() {
			cooldownTimer += pGraphic->getDeltaTime();
			if (cooldownTimer >= FIRE_COOLDOWN) {
				cooldownTimer = 0;
				return fireDamage;
			}
			return 0;
		}

	}

}