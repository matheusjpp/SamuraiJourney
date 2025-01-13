#include "Game.h"

Game::Game() : p1((0.0f, 0.0f), true), e1 ((0.0f, 900.0f)) {
	pGraphic = Managers::GraphicManager::getInstance();
	e1.setPlayer(&p1);
	entList.addEntity(&p1);
	entList.addEntity(&e1);
	execute();
}

Game::~Game() {

}

void Game::execute() {
	sf::Event e;
	while (pGraphic->isWindowOpen()) {
		pGraphic->updateDeltaTime();
		float dt = pGraphic->getDeltaTime();
		pGraphic->clear();
		entList.execute(dt);
		p1.getObs()->render();
		pGraphic->display();
		while (pGraphic->pollEvent(e)) {
			if (e.key.code == sf::Keyboard::Escape) { pGraphic->closeWindow(); }
		}
	}
}