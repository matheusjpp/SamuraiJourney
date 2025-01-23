#pragma once
#include "Enemy.h"

#define WOLF_SIZE_X 64.0f
#define WOLF_SIZE_Y 42.0f

namespace Entities {

	namespace Characters {

		class Wolf : public Enemy {
		private:

		public:
			Wolf(Math::CoordF pos = Math::CoordF(0.0f, 0.0f), ID id = ID::wolf);

			~Wolf();

			void update(float dt);

			void execute();

			void attack();

			void setTextures();

			void updateSprite(float dt);
			
		};

	}

}

