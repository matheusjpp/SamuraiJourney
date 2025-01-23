#include "Game.h"

Game::Game()  {

	pGraphic = Managers::GraphicManager::getInstance();
	pCollision = Managers::Collisions::CollisionManager::getInstance();
	pEvent = Managers::KeyManagement::EventsManager::getInstance();

	Entities::Characters::Player p1(Math::CoordF(400.0f, 300.0f), true);
	Entities::Characters::Wolf w1(Math::CoordF(250.0f, 300.0f));
	Entities::Obstacles::Platform plat1(Math::CoordF(270.0f, 800.0f), Math::CoordF(900.0f, 700.0f), false);
	Entities::Obstacles::Platform plat2(Math::CoordF(920.0f, 500.0f), Math::CoordF(400.0f, 300.0f), false);
	Entities::Obstacles::Platform plat3(Math::CoordF(100.0f, 300.0f), Math::CoordF(40.0f, 300.0f), false);
	plat2.mudarCor(sf::Color(255, 255, 255));
	plat3.mudarCor(sf::Color(255, 0, 0));

	pCollision->setLists(staticEntities, movingEntities);

	w1.setPlayer(&p1);

	movingEntities.addEntity(&p1);
	movingEntities.addEntity(&w1);
	staticEntities.addEntity(&plat1);
	staticEntities.addEntity(&plat2);
	staticEntities.addEntity(&plat3);
	
	execute();
}

Game::~Game() {

}

void Game::execute() {
	sf::Event e;
	while (pGraphic->isWindowOpen()) {
		if (sf::Event::KeyPressed == sf::Keyboard::Escape) {
			pGraphic->closeWindow();
		}

		pGraphic->updateDeltaTime();
		float dt = pGraphic->getDeltaTime();
		pGraphic->clear();
		movingEntities.execute(dt);
		staticEntities.execute(dt);

		pEvent->pollEvents();

		pGraphic->display();
	}
}