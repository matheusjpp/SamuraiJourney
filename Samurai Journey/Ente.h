#pragma once
#include "GraphicManager.h"

enum ID {
	empty = 0,
	player,
	wolf,
	archer,
	demonsamurai,
	arrow,
	platform,
	bush,
	fire
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

	void mudarCor(sf::Color);
	//virtual void execute(float dt) = 0;

};