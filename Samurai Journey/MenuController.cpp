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
			if (pStateM->getCurrentState()->getID() == States::State_ID::main_menu) {
				if (key == select) {
					isActive = false;
					switch (pMenu->getSelectedButtonID()) {
						case Menu::Buttons::Button_ID::newgame: {
							new Menu::MainMenu(Math::CoordF(200, 200), "", 100, Managers::States::State_ID::newgame_menu);
							break;
						}
						case Menu::Buttons::Button_ID::exit: {
							pStateM->popState();
							break;
						}
						// case load e leaderboard
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
			else if (pStateM->getCurrentState()->getID() == States::State_ID::newgame_menu) {
				 if (key == select) {
					 isActive = false;
					 switch (pMenu->getSelectedButtonID()) {
						 case Menu::Buttons::Button_ID::singleplayer: {
							 new Menu::MainMenu(Math::CoordF(200, 200), "", 100, Managers::States::State_ID::singleplayer_menu);
							 break;
						 }
						 case Menu::Buttons::Button_ID::multiplayer: {
							 new Menu::MainMenu(Math::CoordF(200, 200), "", 100, Managers::States::State_ID::multiplayer_menu);
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

				 else if (key == escape) {
					pStateM->popState();
				 }
			}

			/* Singleplayer Menu Commands */
			else if (pStateM->getCurrentState()->getID() == States::State_ID::singleplayer_menu) {
				if (key == select) {
					isActive = false;
					switch (pMenu->getSelectedButtonID()) {
						case Menu::Buttons::Button_ID::archersingle: {
							new Levels::ArcherLevel(false, States::State_ID::bosslevel_singleplayer);
							break;
						}
						case Menu::Buttons::Button_ID::bosssingle: {
							new Levels::BossLevel(false, States::State_ID::bosslevel_singleplayer);
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

				else if (key == escape) {
					pStateM->popState();
				}
			}

			/* Multiplayer Menu Commands */
			else if (pStateM->getCurrentState()->getID() == States::State_ID::multiplayer_menu) {
				if (key == select) {
					isActive = false;
					switch (pMenu->getSelectedButtonID()) {
						case Menu::Buttons::Button_ID::archermulti: {
							new Levels::ArcherLevel(true, States::State_ID::bosslevel_multiplayer);
							break;
						}
						case Menu::Buttons::Button_ID::bossmulti: {
							new Levels::BossLevel(true, States::State_ID::bosslevel_multiplayer);
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

				else if (key == escape) {
					pStateM->popState();
				}
			}

			/* Pause Menu Commands */
			else if (pStateM->getCurrentState()->getID() == States::State_ID::pause_menu) {
				if (key == select) {
					isActive = false;
					switch (pMenu->getSelectedButtonID()) {
						case Menu::Buttons::Button_ID::resumegame: {
							pStateM->popState();
							break;
						}
						case Menu::Buttons::Button_ID::pauseexit: {
							while (pStateM->getCurrentState()->getID() != States::State_ID::main_menu)
								pStateM->popState();
							break;
						}
						// case load
					}
				}

				else if (key == up) {
					pMenu->selectAbove();
				}

				else if (key == down) {
					pMenu->selectBelow();
				}

				else if (key == escape) {
					pStateM->popState();
				}
				}

			////

		}

		void MenuController::notifyKeyReleased(const sf::Keyboard::Key key) {

		}

	}

}