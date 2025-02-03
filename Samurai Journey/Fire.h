#pragma once
#include "Bush.h"

#define FIRE_DAMAGE 8.0f

namespace Entities {

	namespace Obstacles {

		class Fire : public Obstacle {
		private:
			float damage;

		public:
			Fire(Math::CoordF pos = Math::CoordF(0, 0), Math::CoordF size = Math::CoordF(50, 120), ID id = ID::fire);

			~Fire();

			void update(float dt);

			void execute();

			void setTextures();

			void updateSprite(float dt);
		};

	}

}