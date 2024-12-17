#include "Entity.h"

namespace Entities {

	Entity::Entity(Math::CoordF pos, Math::CoordF size, ID id) : Ente(id), position(pos), size(size) {
		body->setSize(sf::Vector2f(size.x, size.y));
		body->setPosition(sf::Vector2f(position.x, position.y));
	}

	Entity::~Entity() {

	}

	void Entity::setPosition(Math::CoordF pos) {
		position = pos;
	}

	Math::CoordF Entity::getPosition() const {
		return position;
	}

	ID Entity::getID() const {
		return id;
	}

	void Entity::render() {
		pGraphic->render(body);
	}

}