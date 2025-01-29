#pragma once
#include "MenuController.h"

class Game {
private:
	Managers::GraphicManager* pGraphic;
	Managers::KeyManagement::EventsManager* pEvent;
	Managers::States::StateManager* pStateM;

public:
	Game();

	~Game();

	void execute();
};