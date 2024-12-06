#include "Game.h"

Game::Game() : p1((300.0f, 300.0f), true) {
	pGraphic = Managers::GraphicManager::getInstance();
	
	
	execute();
}

Game::~Game() {

}

void Game::execute() {
	while (pGraphic->isWindowOpen()) {
		pGraphic->updateDeltaTime();
		pGraphic->clear();
		
		p1.render();
		p1.mudarCor(sf::Color{255, 255, 255});

		pGraphic->display();
	}
}