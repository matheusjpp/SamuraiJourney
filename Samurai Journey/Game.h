#pragma once
#include "Enemy.h"

class Game {
private:
	Managers::GraphicManager* pGraphic;
	Managers::Collisions::CollisionManager* pCollision;

	//Entities::Characters::Player p1;
	//Entities::Characters::Enemy e1;
	//Entities::Obstacles::Platform plat1;

	List::EntitiesList movingEntities;
	List::EntitiesList staticEntities;

public:
	Game();

	~Game();

	void execute();
};