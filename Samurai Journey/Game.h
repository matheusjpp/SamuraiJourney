#pragma once
#include "EntitiesList.h"

class Game {
private:
	Managers::GraphicManager* pGraphic;
	Entities::Player p1;
	Entities::Enemy e1;
	List::EntitiesList entList;
public:
	Game();

	~Game();

	void execute();
};