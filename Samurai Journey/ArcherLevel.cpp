#include "ArcherLevel.h"

namespace Levels {

	ArcherLevel::ArcherLevel(bool isMultiplayer, Managers::States::State_ID id) :
		Level(isMultiplayer, id)
	{
		mapImage->setSize(sf::Vector2f(5480.0f, 1080.0f));
		mapSprite->addNewAnimation(GraphicalElements::Animation_ID::map1, "level1_map.png", 1);
		mapImage->setOrigin(0, 0);

		background.addLayer("bg_layer1.png", 0.04f); // Camada mais distante
		background.addLayer("bg_layer2.png", 0.075f);
		background.addLayer("bg_layer3.png", 0.15f); // Camada mais próxima

		pCollision->setLists(staticEntities, movingEntities);

		createMap("level1.tmj");
	}

	ArcherLevel::~ArcherLevel() {

	}

	void ArcherLevel::execute(float dt) {
		updateCamera(970); //definir limit
		cout << pPlayer1->getPosition().x << endl;
		background.execute(dt);
		mapSprite->update(GraphicalElements::Animation_ID::map1, false, (0, 0), dt);
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

	void ArcherLevel::verifyLevelEnd() {

	}

}