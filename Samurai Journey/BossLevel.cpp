#include "BossLevel.h"

namespace Levels {

	BossLevel::BossLevel(bool isMultiplayer, Managers::States::State_ID id) : 
		Level(isMultiplayer, id) 
	{
		mapImage->setSize(sf::Vector2f(4320.0f, 1080.0f));
		mapSprite->addNewAnimation(GraphicalElements::Animation_ID::map2, "level2_map.png", 1);
		mapImage->setOrigin(0, 0);

		background.addLayer("bg_layer1.png", 0.05f); // Camada mais distante
		background.addLayer("bg_layer2.png", 0.15f);
		background.addLayer("bg_layer3.png", 0.3f); // Camada mais próxima

		pCollision->setLists(staticEntities, movingEntities);

		createMap("level2.tmj");
	}

	BossLevel::~BossLevel() {

	}

	void BossLevel::render() {
		pGraphic->render(mapImage);
	}

	void BossLevel::execute(float dt) {
		background.execute(dt);
		mapSprite->update(GraphicalElements::Animation_ID::map2, false, (0, 0), dt);
		staticEntities.execute(dt);
		movingEntities.execute(dt);
		pPlayer1->changeObserverState(true);
		
		float cameraLimit = 960.0f; // empiricamente
		if (pPlayer1->getPosition().x >= cameraLimit && pPlayer1->getPosition().x <= mapImage->getSize().x - cameraLimit) {
			pPlayer1->centerCamera();
		}
		else if (pPlayer1->getPosition().x < mapImage->getSize().x / 2.0f)
			pGraphic->centerView(Math::CoordF(cameraLimit, pGraphic->getWindowSize().y / 2.0f)); //testar pGraphic->getWindowSize().y / 2.0f

		else
			pGraphic->centerView(Math::CoordF(mapImage->getSize().x - cameraLimit, pGraphic->getWindowSize().y / 2.0f));

		render();
	}

}