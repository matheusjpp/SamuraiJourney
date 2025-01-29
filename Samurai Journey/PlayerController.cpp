#include "PlayerController.h"
#include "PauseMenu.h"

namespace Managers {

	namespace KeyManagement {

		PlayerController::PlayerController(Entities::Characters::Player* pPlayer) : Observer(), pPlayer(pPlayer) {

			moveRight = sf::Keyboard::Unknown;
			moveLeft = sf::Keyboard::Unknown;
			attack = sf::Keyboard::Unknown;
			jump = sf::Keyboard::Unknown;
			defend = sf::Keyboard::Unknown;
			usePotion = sf::Keyboard::Unknown;
			pause = sf::Keyboard::Escape;

			if (pPlayer) { 
				if (pPlayer->getIsPlayer1()) {
					moveRight = sf::Keyboard::D;
					moveLeft = sf::Keyboard::A;
					jump = sf::Keyboard::W;
					attack = sf::Keyboard::Q;
					defend = sf::Keyboard::E;
					usePotion = sf::Keyboard::Z;
				}

				else {
					moveRight = sf::Keyboard::L;
					moveLeft = sf::Keyboard::J;
					jump = sf::Keyboard::I;
					attack = sf::Keyboard::U;
					defend = sf::Keyboard::O;
					usePotion = sf::Keyboard::N;
				}
			}
		}

		PlayerController::~PlayerController() {
			pPlayer = nullptr;
		}

		void PlayerController::notifyKeyPressed(sf::Keyboard::Key key) {
			if (pStateM->getCurrentState()->getID() == States::State_ID::archerlevel_singleplayer || 
				pStateM->getCurrentState()->getID() == States::State_ID::archerlevel_multiplayer || 
				pStateM->getCurrentState()->getID() == States::State_ID::bosslevel_singleplayer || 
				pStateM->getCurrentState()->getID() == States::State_ID::bosslevel_multiplayer) { 
				if (key == moveRight) {
					if (pPlayer->getCanMove()) {
						pPlayer->move(true);
					}
				}

				if (key == moveLeft) {
					if (pPlayer->getCanMove()) {
						pPlayer->move(false);
					}
				}

				if (key == jump) {
					if (pPlayer->getCanJump()) {
						pPlayer->jump();
					}
				}

				if (key == attack) {
					pPlayer->attack();
				}

				if (key == defend) {
					pPlayer->defend();
				}

				if (key == usePotion) {
					pPlayer->usePotion();
				}

				if (key == pause) {
					isActive = false;
					new Menu::PauseMenu(Math::CoordF(200, 200), "", 100, Managers::States::State_ID::pause_menu);
				}
			}
		}

		void PlayerController::notifyKeyReleased(sf::Keyboard::Key key) {
			if (key == moveRight && !sf::Keyboard::isKeyPressed(moveLeft)) {
				if (pPlayer->getCanMove()) {
					pPlayer->stopMoving();
				}
			}
			if (key == moveLeft && !sf::Keyboard::isKeyPressed(moveRight)) {
				if (pPlayer->getCanMove()) {
					pPlayer->stopMoving();
				}
			}

			if (key == defend) {
				pPlayer->stopDefending();
			}
		}

	}

}