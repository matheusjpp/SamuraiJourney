#pragma once
#include "EntitiesList.h"

class Game {
private:
	Managers::GraphicManager* pGraphic;
	Entities::Characters::Player p1;
	Entities::Characters::Enemy e1;
	List::EntitiesList entList;
public:
	Game();

	~Game();

	void execute();
};