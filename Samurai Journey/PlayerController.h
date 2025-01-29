#pragma once
#include "InputManager.h"

namespace Menu {
	class PauseMenu;
}

namespace Managers {

	namespace KeyManagement {

		class PlayerController : public Observer {
		private:
			Entities::Characters::Player* pPlayer;
			sf::Keyboard::Key moveRight;
			sf::Keyboard::Key moveLeft;
			sf::Keyboard::Key attack;
			sf::Keyboard::Key jump;
			sf::Keyboard::Key defend;
			sf::Keyboard::Key usePotion;
			sf::Keyboard::Key pause;
		
		public:
			PlayerController(Entities::Characters::Player* pPlayer = nullptr);
			
			~PlayerController();

			void notifyKeyPressed(sf::Keyboard::Key key);

			void notifyKeyReleased(sf::Keyboard::Key key);
		};

	}

}