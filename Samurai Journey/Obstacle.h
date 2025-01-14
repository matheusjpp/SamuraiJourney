#pragma once
#include "Character.h"

namespace Entities {

	class Obstacle : public Entity {
	private:
		bool dangerous;

	public:
		Obstacle(Math::CoordF pos = Math::CoordF(0, 0), Math::CoordF size = Math::CoordF(0, 0), ID id = ID::obstacle, bool dangerous = false);

		~Obstacle();

		virtual void update(float dt) = 0;

		//void initialize();
	};

}