#pragma once
#include "Wolf.h"

#define DEMON_VISION 150.0f
#define DEMON_HP 100.0f

#define DEMON_ATTACK_CD 1.2f
#define DEMON_ATTACK2_CD 1.5f
#define DEMON_ATTACK_TIME 0.75f
#define DEMON_ATTACK2_TIME 1.05f 
#define DEMON_ATTACK_DISTANCE 100.0f

#define DEMON_SHOUT_TIME 2.55f
#define DEMON_HURT_TIME 0.6f
#define DEMON_DEATH_TIME 3.9f

namespace Entities {

	namespace Characters {

		class DemonSamurai : public Enemy {
		private:
			static int cont;
			static bool isLastBuffed;
			bool isShouting;
			float shoutTimer;

		public:
			DemonSamurai(Math::CoordF pos = Math::CoordF(0.0f, 0.0f), ID id = ID::demonsamurai);

			~DemonSamurai();

			void shout();

			void update(float dt);

			void execute();

			void attack();

			void setTextures();

			void updateSprite(float dt);
		};

	}

}