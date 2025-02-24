#include "Entity.h"

namespace Entities {

	Entity::Entity(Math::CoordF pos, Math::CoordF size, ID id) : Ente(id), position(pos), size(size), sprite(nullptr), isActive(true) {
		body->setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
		body->setSize(sf::Vector2f(size.x, size.y));
		body->setPosition(sf::Vector2f(pos.x, pos.y));
	}

	Entity::~Entity() {
		if (sprite) {
			delete sprite;
		}
	}

	void Entity::setPosition(Math::CoordF pos) {
		position = pos;
	}

	Math::CoordF Entity::getPosition() const {
		return position;
	}

	Math::CoordF Entity::getSize() const {
		return size;
	}

	void Entity::render() {
		pGraphic->render(body);
	}

	bool Entity::getIsActive() {
		return isActive;
	}

	void Entity::setIsActive(bool isA) {
		isActive = isA;
	}

}