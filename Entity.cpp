#include "Entity.h"

namespace Entities {

	Entity::Entity(Math::CoordF pos, Math::CoordF size, ID id) : Ente(id), position(pos), size(size) {

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