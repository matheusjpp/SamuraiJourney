#pragma once
#include "Portal.h"

#define PLAYER_SIZE_X 64.0f
#define PLAYER_SIZE_Y 42.0f

#define PLAYER_SPEED 300.0f // Player Velocity
#define GRAVITY 700.0f
#define JUMP 700.0f

#define PLAYER_HP 100.0f
#define PLAYER_ATTACK_DAMAGE 50.0f
#define PLAYER_ATTACK_CD 0.2f
#define PLAYER_ATTACK_TIME 0.9f
#define PLAYER_ATTACK_RANGE 120.0f
#define PLAYER_ATTACK_RANGEHEIGHT 40.0f
#define PLAYER_IMPACT_TIME 0.7f

#define PLAYER_DEATH_TIME 1.35f
#define PLAYER_HURT_TIME 0.6f
#define PLAYER_HEAL_TIME 2.25f

namespace Managers {
	namespace KeyManagement {
		class PlayerController;
	}
}

namespace Levels {
	class Level;
}

namespace Entities {

	namespace Characters {

		class Player : public Character {
		private:
			Managers::KeyManagement::PlayerController* pControl;
			const bool isPlayer1;
			bool isDefending;
			bool isHealing;
			bool isSlowed;
			float healTimer;
			int points;
			Levels::Level* pLevel;
			Obstacles::Bush* pBush;
			float speed;

		public:
			Player(Math::CoordF pos = Math::CoordF(0, 0), bool isPlayer1 = true, Levels::Level* level= nullptr);

			~Player();

			bool getIsPlayer1() const;

			void update(float dt);

			void setTextures();
			
			void updateSprite(float dt);

			void execute();

			void attack();

			void defend();

			void stopDefending();

			bool getIsDefending();

			bool getIsHealing();

			const float getHealTimer() const;

			void usePotion();

			void centerCamera();

			void changeObserverState(bool active);

			void checkEnemiesInRange();

			void setPoints(int pPoints);

			void setIsActive(bool isAct);

			void setIsDefending(bool isDef);

			void setIsHealing(bool isHeal);

			void setHealTimer(float hTimer);

			void setSlowness();

			void setIsSlowed(bool isSl);

			const int getScorePoints() const;
		};

	}

}