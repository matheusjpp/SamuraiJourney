#pragma once
#include "Entity.h"

namespace Entities {

	class Obstacle : public Entity {
	private:
		Math::CoordF position;
		Math::CoordF size;

	public:
		Obstacle(Math::CoordF pos = Math::CoordF(0, 0), Math::CoordF size = Math::CoordF(0, 0), ID id = ID::obstacle);

		~Obstacle();

		void update(float dt);

		//void initialize();
	};

}