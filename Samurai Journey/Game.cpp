#include "Game.h"

Game::Game() : p1((100.0f, 100.0f), true) {
	pGraphic = Managers::GraphicManager::getInstance();
	
	
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
		p1.render();
		pGraphic->display();
		while (pGraphic->pollEvent(e)) {
			if (e.key.code == sf::Keyboard::Escape) { pGraphic->closeWindow(); }
		}
	}
}