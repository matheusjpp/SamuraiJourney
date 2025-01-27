#include "Platform.h"

namespace Entities {

	namespace Obstacles {

		Platform::Platform(Math::CoordF pos, Math::CoordF size, bool isFake) : isFake(isFake), 
			Obstacle(pos, size, ID::platform) {
			//body->setOrigin(0, 0);
		}

		Platform::~Platform() {

		}

		void Platform::update(float dt) {
	
		}

		void Platform::execute() {
			body->setPosition(sf::Vector2f(position.x, position.y));
			render();
		}

		void Platform::setTextures() {

		}

		void Platform::updateSprite(float dt) {

		}

	}

}