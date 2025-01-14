#include "Platform.h"

namespace Entities {

	namespace Obstacles {

		Platform::Platform(Math::CoordF pos, Math::CoordF size, ID id, bool isFake) : isFake(isFake), 
			Obstacle(Math::CoordF(pos), Math::CoordF(size), ID::platform) {

		}

		Platform::~Platform() {

		}

		void Platform::update(float dt) {

		}

	}

}