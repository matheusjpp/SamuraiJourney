#include "Obstacle.h"

#define OBSTACLE_POSITION_X 0.0f
#define OBSTACLE_POSITION_Y 540.0f

#define OBSTACLE_SIZE_X 1080.0f
#define OBSTACLE_SIZE_Y 50.0f

namespace Entities {

	Obstacle::Obstacle(Math::CoordF pos, Math::CoordF size, ID id) :
		Entity(Math::CoordF(OBSTACLE_POSITION_X, OBSTACLE_POSITION_Y), Math::CoordF(OBSTACLE_SIZE_X, OBSTACLE_SIZE_Y), ID::obstacle) {

		mudarCor(sf::Color(0, 255, 0));
	}

	Obstacle::~Obstacle() {

	}

	void Obstacle::update(float dt) {

	}

	//void initialize() {}
}