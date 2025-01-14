#include "Obstacle.h"

namespace Entities {

	Obstacle::Obstacle(Math::CoordF pos, Math::CoordF size, ID id, bool dangerous) :
		Entity(Math::CoordF(pos), Math::CoordF(size), ID::obstacle) {

		mudarCor(sf::Color(0, 255, 0));
	}

	Obstacle::~Obstacle() {

	}

	void Obstacle::update(float dt) {

	}

	//void initialize() {}
}