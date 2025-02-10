#include "MenuController.h"
#include "ArcherLevel.h"
#include "BossLevel.h"

namespace Managers {

	namespace KeyManagement {

		MenuController::MenuController(Menu::Menu* menu) : Observer(), pMenu(menu), alreadySaved(false) {
			select = sf::Keyboard::Enter;
			escape = sf::Keyboard::Escape;
			up = sf::Keyboard::Up;
			down = sf::Keyboard::Down;
			right = sf::Keyboard::Right;
			left = sf::Keyboard::Left;
			reset = sf::Keyboard::R;
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
							new Menu::ConcreteMenu(Math::CoordF(200, 200), "", 100, Managers::States::State_ID::newgame_menu);
							break;
						}
						case Menu::Buttons::Button_ID::exit: {
							pStateM->popState();
							break;
						}
						case Menu::Buttons::Button_ID::loadgame: {
							std::ifstream file("save.json");
							if (!file.is_open()) {
								std::cerr << "Erro ao abrir o salvamento" << std::endl;
								return;
							}

							json j;
							try {
								file >> j;
							}
							catch (const std::exception& e) {
								std::cerr << "Erro ao processar JSON: " << e.what() << std::endl;
								return;
							}

							if (j["GAME"] == Managers::States::State_ID::archerlevel_singleplayer) {
								new Levels::ArcherLevel(false, States::State_ID::archerlevel_singleplayer, true);
							}

							else if (j["GAME"] == Managers::States::State_ID::archerlevel_multiplayer) {
								new Levels::ArcherLevel(true, States::State_ID::archerlevel_multiplayer, true);
							}

							else if (j["GAME"] == Managers::States::State_ID::bosslevel_singleplayer) {
								new Levels::BossLevel(false, States::State_ID::bosslevel_singleplayer, 0, true);
							}
							else if (j["GAME"] == Managers::States::State_ID::bosslevel_multiplayer) {
								new Levels::BossLevel(true, States::State_ID::bosslevel_multiplayer, 0, true);
							}

							break;
						}

						case Menu::Buttons::Button_ID::leaderboard: {
							new Menu::ConcreteMenu(Math::CoordF(200, 200), "", 100, Managers::States::State_ID::leaderboard_menu);
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
			else if (pStateM->getCurrentState()->getID() == States::State_ID::newgame_menu) {
				 if (key == select) {
					 isActive = false;
					 switch (pMenu->getSelectedButtonID()) {
						 case Menu::Buttons::Button_ID::singleplayer: {
							 new Menu::ConcreteMenu(Math::CoordF(200, 200), "", 100, Managers::States::State_ID::singleplayer_menu);
							 break;
						 }
						 case Menu::Buttons::Button_ID::multiplayer: {
							 new Menu::ConcreteMenu(Math::CoordF(200, 200), "", 100, Managers::States::State_ID::multiplayer_menu);
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
							new Levels::ArcherLevel(false, States::State_ID::archerlevel_singleplayer);
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
							new Levels::ArcherLevel(true, States::State_ID::archerlevel_multiplayer);
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

			/* Leaderboard Menu Commands */
			else if (pStateM->getCurrentState()->getID() == States::State_ID::leaderboard_menu) {
				if (key == escape) {
					pStateM->popState();
				}

				else if (key == reset) {
					pMenu->resetLeaderboard();
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
						case Menu::Buttons::Button_ID::saveprogress: {
							
							if (auto* level = dynamic_cast<Levels::ArcherLevel*>(pStateM->getPreviousState())) {
								level->saveLevel("save.json");
							}
							else if (auto* level = dynamic_cast<Levels::BossLevel*>(pStateM->getPreviousState())) {
								level->saveLevel("save.json");
							}
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

			/* Game Over Menu Commands */
			else if (pStateM->getCurrentState()->getID() == States::State_ID::gameover_menu) {
				if (key == select) {
					isActive = false;
					switch (pMenu->getSelectedButtonID()) {
						case Menu::Buttons::Button_ID::savescore: {
							if (!alreadySaved) {
								pMenu->saveScore(pMenu->getPlayerName(), pMenu->getScore());
								alreadySaved = true;
							}
							break;
						}
						case Menu::Buttons::Button_ID::pauseexit: {
							while (pStateM->getCurrentState()->getID() != States::State_ID::main_menu)
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

				else if ((key >= sf::Keyboard::A && key <= sf::Keyboard::Z) ||
						(key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9)) {
						pMenu->appendCharacter(static_cast<char>(key) + 97); // Converte para minúscula
				}

				else if (key == sf::Keyboard::Backspace) {
					pMenu->removeLastCharacter();
				}
			}

			/* Win Menu Commands */
			else if (pStateM->getCurrentState()->getID() == States::State_ID::win_menu) {
				if (key == select) {
					isActive = false;
					switch (pMenu->getSelectedButtonID()) {
					case Menu::Buttons::Button_ID::savescore: {
						if (!alreadySaved) {
							pMenu->saveScore(pMenu->getPlayerName(), pMenu->getScore());
							alreadySaved = true;
						}
						break;
					}
					case Menu::Buttons::Button_ID::pauseexit: {
						while (pStateM->getCurrentState()->getID() != States::State_ID::main_menu)
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

				else if ((key >= sf::Keyboard::A && key <= sf::Keyboard::Z) ||
					(key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9)) {
					pMenu->appendCharacter(static_cast<char>(key) + 97); // Converte para minúscula
				}

				else if (key == sf::Keyboard::Backspace) {
					pMenu->removeLastCharacter();
				}
				}
		}

		void MenuController::notifyKeyReleased(const sf::Keyboard::Key key) {

		}

	}

}