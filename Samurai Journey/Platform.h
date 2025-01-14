#pragma once
#include "CollisionManager.h"

namespace Entities {

	namespace Obstacles {

		class Platform : public Obstacle {
		private:
			bool isFake;

		public:
			Platform(Math::CoordF pos = Math::CoordF(0, 0), Math::CoordF size = Math::CoordF(0, 0), ID id = ID::platform, bool isFake = false);

			~Platform();

			void update(float dt);
		};


	}

}
