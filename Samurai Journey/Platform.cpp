#include "Platform.h"

namespace Entities {

	namespace Obstacles {

		Platform::Platform(Math::CoordF pos, Math::CoordF size, bool isFake, ID id) : isFake(isFake),
			Obstacle(pos, size, id) {
			//body->setOrigin(0, 0);
		}

		Platform::~Platform() {

		}

		void Platform::update(float dt) {
	
		}

		void Platform::execute() {
			body->setPosition(sf::Vector2f(position.x, position.y));
			body->setFillColor(sf::Color(0, 0, 0, 0));
			render();
		}

		void Platform::setTextures() {

		}

		void Platform::setIsFake(bool isF) {
			isFake = isF;
		}

		void Platform::updateSprite(float dt) {

		}

		const bool Platform::getIsFake() {
			return isFake;
		}

	}

}