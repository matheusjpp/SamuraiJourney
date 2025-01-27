#include "Game.h"

Game::Game() : p1(Math::CoordF(400.0f, 300.0f), true) {

	/*

	// FOTO DO MAPA
	mapImage = new sf::RectangleShape();
	mapImage->setSize(sf::Vector2f(4320.0f, 1080.0f));

	mapSprite = new GraphicalElements::Animation(mapImage, Math::CoordF(1, 1));
	mapSprite->addNewAnimation(GraphicalElements::Animation_ID::map1, "level2_map.png", 1);
	mapImage->setOrigin(0, 0);
	//
	*/

	pGraphic = Managers::GraphicManager::getInstance();
	pCollision = Managers::Collisions::CollisionManager::getInstance();
	pEvent = Managers::KeyManagement::EventsManager::getInstance();
	
	Entities::Characters::Archer e1(Math::CoordF(400.0f, 300.0f), &movingEntities);
	//Entities::Characters::Wolf e2(Math::CoordF(150.0f, 300.0f));
	//Entities::Characters::DemonSamurai e3(Math::CoordF(220.0f, 300.0f));
	Entities::Obstacles::Platform plat1(Math::CoordF(270.0f, 800.0f), Math::CoordF(900.0f, 700.0f), false);
	Entities::Obstacles::Platform plat2(Math::CoordF(920.0f, 500.0f), Math::CoordF(400.0f, 300.0f), false);
	Entities::Obstacles::Platform plat3(Math::CoordF(100.0f, 300.0f), Math::CoordF(40.0f, 300.0f), false);
	plat2.mudarCor(sf::Color(255, 255, 255));
	plat3.mudarCor(sf::Color(255, 0, 0));

	pCollision->setLists(staticEntities, movingEntities);

	e1.setPlayer(&p1);
	//e2.setPlayer(&p1);
	//e3.setPlayer(&p1);

	movingEntities.addEntity(&p1);
	movingEntities.addEntity(&e1);
	//movingEntities.addEntity(&e2);
	//movingEntities.addEntity(&e3);
	staticEntities.addEntity(&plat1);
	staticEntities.addEntity(&plat2);
	staticEntities.addEntity(&plat3);
	
	/*
	level.createMap("mapa1.tmj");
	staticEntities = level.getList();
	pCollision->setLists(staticEntities, movingEntities);
	*/
	execute();
}

Game::~Game() {

}

void Game::execute() {
	while (pGraphic->isWindowOpen()) {
		if (sf::Event::KeyPressed == sf::Keyboard::Escape) {
			pGraphic->closeWindow();
		}

		pGraphic->updateDeltaTime();
		float dt = pGraphic->getDeltaTime();
		pGraphic->clear();
		//mapSprite->update(GraphicalElements::Animation_ID::map1, false, (0, 0), dt);
		movingEntities.execute(dt);
		staticEntities.execute(dt);
		//pGraphic->render(mapImage);
		pEvent->pollEvents();
		p1.centerCamera();
		pGraphic->display();
	}
}