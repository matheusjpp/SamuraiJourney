#pragma once
#include "CollisionManager.h"

#define ARROW_SIZE_X 15.0f
#define ARROW_SIZE_Y 10.0f

#define ARROW_GRAVITY 1.0f
#define ARROW_SPEED 100.0f

namespace Entities {

	class Arrow : public MovingEntity {
	private:
		//bool isActive;

	public:
		Arrow(Math::CoordF pos = Math::CoordF(0, 0), bool facingLeft = false, ID id = ID::arrow);

		~Arrow();
		
		void update(float dt);

		void execute();

		void setTextures();

		void updateSprite(float dt);
	};

}