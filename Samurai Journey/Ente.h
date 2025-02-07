#pragma once
#include "GraphicManager.h"

enum ID {
	empty = 0,
	player = 1,
	wolf = 2,
	archer = 3,
	demonsamurai = 4,
	arrow = 5,
	platform = 6,
	bush = 7,
	fire = 8,
	portal = 9
};

class Ente {
protected:
	ID id;
	sf::RectangleShape* body;

	static Managers::GraphicManager* pGraphic;

public:
	Ente(ID id = ID::empty);

	virtual ~Ente();

	void setID(ID id);

	ID getID() const;

	virtual void render() = 0;
};