#pragma once
#include "ArcherLevel.h"

namespace Managers {

	namespace KeyManagement {

		class MenuController : public Observer {
		private:
			Menu::Menu* pMenu;
			sf::Keyboard::Key select;
			sf::Keyboard::Key escape;
			sf::Keyboard::Key up;
			sf::Keyboard::Key down;
			sf::Keyboard::Key right;
			sf::Keyboard::Key left;
		
		public:
			MenuController(Menu::Menu* menu);

			~MenuController();

			void notifyKeyPressed(const sf::Keyboard::Key key);

			void notifyKeyReleased(const sf::Keyboard::Key key);
		};
			
	}

}