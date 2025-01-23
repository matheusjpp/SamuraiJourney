#pragma once
#include "Obstacle.h"

namespace Entities {

	namespace Obstacles {

		class Platform : public Obstacle {
		private:
			bool isFake;

		public:
			Platform(Math::CoordF pos = Math::CoordF(0, 0), Math::CoordF size = Math::CoordF(0, 0), bool isFake = false);

			~Platform();

			void update(float dt);

			void execute();

			void setTextures();

			void updateSprite(float dt);
		};


	}

}
