#include "Game.h"

Game::Game() {
	pGraphic = Managers::GraphicManager::getInstance();
	pEvent = Managers::KeyManagement::EventsManager::getInstance();
	pStateM = Managers::States::StateManager::getInstance();

	new Menu::ConcreteMenu(Math::CoordF(200, 200), "", 100, Managers::States::State_ID::main_menu);
	
	execute();
}

Game::~Game() {
	delete pEvent;
	delete pStateM;
}

void Game::execute() {
	/* Otimiza o jogo de alguma maneira desconhecida */
	new Levels::ArcherLevel(false, Managers::States::State_ID::archerlevel_singleplayer);
	pStateM->popState();
	/* */

	while (pGraphic->isWindowOpen()) {
		pGraphic->clear();
		pGraphic->updateDeltaTime();
		pEvent->pollEvents();
		if (pStateM->getCurrentState() != NULL) { pStateM->renderState(); pStateM->executeState(); }
		else pGraphic->closeWindow();
		pGraphic->display();
	}
}