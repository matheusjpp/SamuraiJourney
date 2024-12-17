#pragma once
#include "Enemy.h"

class Game {
private:
	Managers::GraphicManager* pGraphic;
	Entities::Player p1;
	Entities::Enemy e1;

public:
	Game();

	~Game();

	void execute();
};