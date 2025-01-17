#pragma once
#include "EventsManager.h"

class Game {
private:
	Managers::GraphicManager* pGraphic;
	Managers::Collisions::CollisionManager* pCollision;
	Managers::KeyManagement::EventsManager* pEvent;

	List::EntitiesList movingEntities;
	List::EntitiesList staticEntities;

public:
	Game();

	~Game();

	void execute();
};