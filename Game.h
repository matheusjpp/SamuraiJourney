#pragma once
#include "Player.h"

class Game {
private:
	Managers::GraphicManager* pGraphic;
	Entities::Player p1;

public:
	Game();

	~Game();

	void execute();
};