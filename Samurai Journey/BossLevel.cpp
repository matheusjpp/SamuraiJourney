#include "BossLevel.h"

namespace Levels {

	BossLevel::BossLevel(bool isMultiplayer, Managers::States::State_ID id, int playerPoints) :
		Level(isMultiplayer, id) 
	{
		mapImage->setSize(sf::Vector2f(4320.0f, 1080.0f));
		mapSprite->addNewAnimation(GraphicalElements::Animation_ID::map2, "level2_map.png", 1);
		mapImage->setOrigin(0, 0);

		background.addLayer("bg_layer1.png", 0.04f); // Camada mais distante
		background.addLayer("bg_layer2.png", 0.075f);
		background.addLayer("bg_layer3.png", 0.15f); // Camada mais próxima

		pCollision->setLists(staticEntities, movingEntities);

		createMap("level2.tmj");

		if (playerPoints > 0) {
			cout << "pontos nao tao sendo atribuidos" << endl;
			pPlayer1->setPoints(playerPoints);
		}
	}

	BossLevel::~BossLevel() {

	}

	void BossLevel::updateCamera() {
		float cameraLimit = 960.0f; // empiricamente
		if (pPlayer1->getIsActive()) {
			if (pPlayer1->getPosition().x >= cameraLimit && pPlayer1->getPosition().x <= mapImage->getSize().x - cameraLimit) {
				pPlayer1->centerCamera();
			}
			else if (pPlayer1->getPosition().x < mapImage->getSize().x / 2.0f) {
				pGraphic->centerView(Math::CoordF(cameraLimit, pGraphic->getWindowSize().y / 2.0f)); //testar pGraphic->getWindowSize().y / 2.0f
			}

			else {
				pGraphic->centerView(Math::CoordF(mapImage->getSize().x - cameraLimit, pGraphic->getWindowSize().y / 2.0f));
			}
		}

		else if (isMultiplayer && pPlayer2->getIsActive()) {
			if (pPlayer2->getPosition().x >= cameraLimit && pPlayer2->getPosition().x <= mapImage->getSize().x - cameraLimit) {
				pPlayer2->centerCamera();
			}
			else if (pPlayer2->getPosition().x < mapImage->getSize().x / 2.0f) {
				pGraphic->centerView(Math::CoordF(cameraLimit, pGraphic->getWindowSize().y / 2.0f)); //testar pGraphic->getWindowSize().y / 2.0f
			}
			else {
				pGraphic->centerView(Math::CoordF(mapImage->getSize().x - cameraLimit, pGraphic->getWindowSize().y / 2.0f));
			}
		}
	}

	void BossLevel::render() {
		pGraphic->render(mapImage);

		std::string hpStr = std::to_string(static_cast<int>(pPlayer1->getHP()));
		p1life->setText("Player 1's HP: " + hpStr);
		p1life->setTextPos(Math::CoordF(pGraphic->getCenterView().x - 930, 15));
		sf::Text shadow = p1life->getText();
		shadow.setFillColor(sf::Color(255, 255, 255, 80));
		shadow.move(1.f, 1.f);
		pGraphic->render(shadow);
		pGraphic->render(p1life->getText());

		if (isMultiplayer) {
			std::string hpStr2 = std::to_string(static_cast<int>(pPlayer2->getHP()));
			p2life->setText("Player 2's HP: " + hpStr2);
			p2life->setTextPos(Math::CoordF(pGraphic->getCenterView().x - 930, 65));
			sf::Text shadow2 = p2life->getText();
			shadow2.setFillColor(sf::Color(255, 255, 255, 80));
			shadow2.move(1.f, 1.f);
			pGraphic->render(shadow2);
			pGraphic->render(p2life->getText());
		}
	}

	void BossLevel::execute(float dt) {
		updateCamera();
		background.execute(dt);
		mapSprite->update(GraphicalElements::Animation_ID::map2, false, (0, 0), dt);
		staticEntities.execute(dt);
		movingEntities.execute(dt);
		
		if (pPlayer1->getIsDying()) {
			pPlayer1->changeObserverState(false);
		}
		else if (pPlayer1->getIsActive()) {
			pPlayer1->changeObserverState(true);
		}

		if (isMultiplayer) {
			if (pPlayer2->getIsDying())
				pPlayer2->changeObserverState(false);
			else if (pPlayer2->getIsActive())
				pPlayer2->changeObserverState(true);
		}

		render();
	}

}