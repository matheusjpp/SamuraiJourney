#include "MenuController.h"

namespace Managers {

	namespace KeyManagement {

		MenuController::MenuController(Menu::Menu* menu) : Observer(), pMenu(menu) {
			select = sf::Keyboard::Enter;
			escape = sf::Keyboard::Escape;
			up = sf::Keyboard::Up;
			down = sf::Keyboard::Down;
			right = sf::Keyboard::Right;
			left = sf::Keyboard::Left;
		}

		MenuController::~MenuController() {
			
		}

		void MenuController::notifyKeyPressed(const sf::Keyboard::Key key) {

			/* Main Menu Commands */
			if (pStateM->getCurrentState()->getID() == States::State_ID::main_menu && pStateM->getCurrentState()->getIsActive()) {
				if (key == select) {
					switch (pMenu->getSelectedButtonID()) {
						case Menu::Buttons::Button_ID::newgame: {
							new Levels::BossLevel();
							//States::Levels::TimeLevel* t = new States::Levels::TimeLevel(false);
							break;
						}
						case Menu::Buttons::Button_ID::exit: {
							pStateM->popState();
							break;
						}
					}
				}

				else if (key == up) {
					pMenu->selectAbove();
				}

				else if (key == down) {
					pMenu->selectBelow();
				}
			}

			/* New Game Menu Commands */
		}

		void MenuController::notifyKeyReleased(const sf::Keyboard::Key key) {

		}

	}

}