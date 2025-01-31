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
		background.addLayer("bg_layer3.png", 0.15f); // Camada mais pr�xima

		pCollision->setLists(staticEntities, movingEntities);

		createMap("level2.tmj");

		if (playerPoints > 0) {
			cout << "pontos nao tao sendo atribuidos" << endl;
			pPlayer1->setPoints(playerPoints);
		}
	}

	BossLevel::~BossLevel() {

	}

	void BossLevel::execute(float dt) {
		updateCamera(960.0f);
		background.execute(dt);
		mapSprite->update(GraphicalElements::Animation_ID::map2, false, (0, 0), dt);
		movingEntities.execute(dt);
		staticEntities.execute(dt);
		
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