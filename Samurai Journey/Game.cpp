#include "Game.h"

Game::Game() {
	pGraphic = Managers::GraphicManager::getInstance();
	pEvent = Managers::KeyManagement::EventsManager::getInstance();
	pStateM = Managers::States::StateManager::getInstance();

	new Menu::MainMenu(Math::CoordF(200, 200), "", 100, Managers::States::State_ID::main_menu);
	
	execute();
}

Game::~Game() {
	delete pEvent;
	delete pStateM;
}

void Game::execute() {
	while (pGraphic->isWindowOpen()) {
		pGraphic->clear();
		pGraphic->updateDeltaTime();
		pStateM->executeState();
		pEvent->pollEvents();
		if (pStateM->getCurrentState() != NULL) pStateM->renderState();
		else pGraphic->closeWindow();
		pGraphic->display();
	}
}