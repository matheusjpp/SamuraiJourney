#include "BossLevel.h"

namespace Levels {

	BossLevel::BossLevel(bool isMultiplayer, Managers::States::State_ID id, int playerPoints, bool isLoaded) : pastPoints(playerPoints),
		Level(isMultiplayer, id) 
	{
		mapImage->setSize(sf::Vector2f(4320.0f, 1080.0f));
		mapSprite->addNewAnimation(GraphicalElements::Animation_ID::map2, "level2_map.png", 1);
		mapImage->setOrigin(0, 0);

		background.addLayer("bg_layer1.png", 0.04f); // Camada mais distante
		background.addLayer("bg_layer2.png", 0.075f);
		background.addLayer("bg_layer3.png", 0.15f); // Camada mais próxima

		pCollision->setLists(staticEntities, movingEntities);

		if (!isLoaded) {
			createLevel("level2.tmj");
			if (pastPoints > 0) {
				pPlayer1->setPoints(playerPoints);
			}
		}

		else {
			loadLevel("save.json");
		}
	}

	BossLevel::~BossLevel() {

	}

	void BossLevel::verifyLevelEnd() {
		if (!pPlayer1->getIsActive()) {
			if (isMultiplayer) {
				if (!pPlayer2->getIsActive()) {
					new Menu::ConcreteMenu(Math::CoordF(200, 200), "", 100, Managers::States::State_ID::gameover_menu, pPlayer1->getPlayerLevel());
				}
			}
			else {
				new Menu::ConcreteMenu(Math::CoordF(200, 200), "", 100, Managers::States::State_ID::gameover_menu, pPlayer1->getPlayerLevel());
			}
		}
		
		int enemiesCounter = 0;
		for (auto itM = (&movingEntities)->begin(); itM != (&movingEntities)->end(); ++itM) {
			if (*itM) {
				if (auto* enemy = dynamic_cast<Entities::Characters::Enemy*>(*itM)) {
					if (enemy->getIsActive()) {
						enemiesCounter++;
					}
				}
			}
		}

		if (enemiesCounter == 0) {
			new Menu::ConcreteMenu(Math::CoordF(200, 200), "", 100, Managers::States::State_ID::win_menu, pPlayer1->getPlayerLevel());
		}
	}

	void BossLevel::execute(float dt) {
		updateCamera(960.0f);
		background.execute(dt);
		mapSprite->update(GraphicalElements::Animation_ID::map2, false, (0, 0), dt);
		executePortal();
		movingEntities.execute(dt);
		staticEntities.execute(dt);
		
		if (pPlayer1->getIsDying()) {
			pPlayer1->changeObserverState(false);
		}
		else if (pPlayer1->getIsActive()) {
			if (pPlayer1->getPosition().y > 1080) pPlayer1->receiveDamage(pPlayer1->getHP());
			pPlayer1->changeObserverState(true);
		}

		if (isMultiplayer) {
			if (pPlayer2->getIsDying())
				pPlayer2->changeObserverState(false);
			else if (pPlayer2->getIsActive()) {
				if (pPlayer2->getPosition().y > 1080) pPlayer2->receiveDamage(pPlayer2->getHP());
				pPlayer2->changeObserverState(true);
			}
		}

		verifyLevelEnd();
		render();
	}

}