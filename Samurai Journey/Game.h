#pragma once
#include "Level.h"

class Game {
private:
	Managers::GraphicManager* pGraphic;
	Managers::Collisions::CollisionManager* pCollision;
	Managers::KeyManagement::EventsManager* pEvent;
	Levels::Level level;
	List::EntitiesList movingEntities;
	List::EntitiesList staticEntities;

	Entities::Characters::Player p1;

	sf::RectangleShape* mapImage;
	GraphicalElements::Animation* mapSprite;

public:
	Game();

	~Game();

	void execute();
};