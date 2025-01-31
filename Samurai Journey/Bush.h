#pragma once
#include "Platform.h"

#define BUSH_SLOWNESS 0.5f

namespace Entities {

	namespace Obstacles {

		class Bush : public Obstacle {
		private:
			float slowness;

		public:
			Bush(Math::CoordF pos = Math::CoordF(0, 0), Math::CoordF size = Math::CoordF(300, 120), ID id = ID::bush);

			~Bush();

			const float getSlowness() const;

			void update(float dt);

			void execute();

			void setTextures();

			void updateSprite(float dt);
		};

	}

}