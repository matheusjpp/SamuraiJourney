#include "Platform.h"

namespace Entities {

	namespace Obstacles {

		Platform::Platform(Math::CoordF pos, Math::CoordF size, bool isFake) : isFake(isFake), 
			Obstacle(pos, size, ID::platform) {
			mudarCor(sf::Color(0, 255, 0));
		}

		Platform::~Platform() {

		}

		void Platform::update(float dt) {
			body->setPosition(sf::Vector2f(position.x, position.y));
		}

	}

}