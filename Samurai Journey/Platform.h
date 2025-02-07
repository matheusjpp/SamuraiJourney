#pragma once
#include "Obstacle.h"

namespace Entities {

	namespace Obstacles {

		class Platform : public Obstacle {
		private:
			bool isFake;

		public:
			Platform(Math::CoordF pos = Math::CoordF(0, 0), Math::CoordF size = Math::CoordF(0, 0), bool isFake = false, ID id = ID::platform);

			~Platform();

			void update(float dt);

			const bool getIsFake();

			void setIsFake(bool isF);

			void execute();

			void setTextures();

			void updateSprite(float dt);
		};


	}

}