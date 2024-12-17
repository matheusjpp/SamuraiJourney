#include "Game.h"

Game::Game() : p1((0.0f, 0.0f), true), e1 ((0.0f, 900.0f)) {
	pGraphic = Managers::GraphicManager::getInstance();
	e1.setPlayer(&p1);
	execute();
}

Game::~Game() {

}

void Game::execute() {
	sf::Event e;

	while (pGraphic->isWindowOpen()) {
		pGraphic->updateDeltaTime();
		pGraphic->clear();
		p1.update(pGraphic->getDeltaTime());
		e1.update(pGraphic->getDeltaTime());
		p1.render();
		e1.render();
		p1.getObs()->render();
		pGraphic->display();
		while (pGraphic->pollEvent(e)) {
			if (e.key.code == sf::Keyboard::Escape) { pGraphic->closeWindow(); }
		}
	}
}