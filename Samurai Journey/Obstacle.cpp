#include "Obstacle.h"

namespace Entities {

	namespace Obstacles {

		Obstacle::Obstacle(Math::CoordF pos, Math::CoordF size, ID id, bool dangerous) : dangerous(dangerous),
			Entity(pos, size, id) {

		}

		Obstacle::~Obstacle() {

		}

		//void initialize() {}

	}

}