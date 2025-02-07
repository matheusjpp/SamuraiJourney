#pragma once
#include "CollisionManager.h"

#define ARROW_SIZE_X 15.0f
#define ARROW_SIZE_Y 10.0f

#define ARROW_GRAVITY 4.0f
#define ARROW_SPEED 300.0f
#define ARROW_AIR_RESISTANCE 100.0f

#define ARROW_MAXDAMAGE 20.0f
#define ARROW_MINDAMAGE 10.0f

namespace Entities {

	class Arrow : public MovingEntity {
	private:
		float initialX;
		float distanceTraveled;

	public:
		Arrow(Math::CoordF pos = Math::CoordF(0, 0), bool facingLeft = false, ID id = ID::arrow);

		~Arrow();
		
		const float getDamagePoints() const;

		const float getInitialX() const;

		void setInitialX(float iX);

		float getDistanceTraveled();

		void setDistanceTraveled(float dTravel);

		void update(float dt);

		void execute();

		void setTextures();

		void updateSprite(float dt);
	};

}