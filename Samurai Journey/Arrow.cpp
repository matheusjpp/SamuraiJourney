#include "Arrow.h"

namespace Entities {

	Arrow::Arrow(Math::CoordF pos, bool facingLeft, ID id) : damagePoints(ARROW_MAXDAMAGE), initialX(pos.x), distanceTraveled(0),
		MovingEntity(pos, Math::CoordF(ARROW_SIZE_X, ARROW_SIZE_Y), id) {
		isFacingLeft = facingLeft;

		setTextures();
	}

	Arrow::~Arrow() {
		
	}

	float Arrow::getDamagePoints() const {
		return damagePoints;
	}

	void Arrow::update(float dt) {
		if (isFacingLeft) {
			velocity.x -= ARROW_SPEED * dt;
		}
		else {
			velocity.x += ARROW_SPEED * dt;
		}

		velocity.y += ARROW_GRAVITY * dt; // Incrementa velocidade vertical
		position.x += velocity.x * dt;
		position.y += velocity.y * dt;

		distanceTraveled = fabs(initialX - position.x);
		damagePoints = max(ARROW_MINDAMAGE, ARROW_MAXDAMAGE - (distanceTraveled / 40.0f));

		pCollision->notifyCollision(this, dt);
		updateSprite(dt);
		body->setPosition(sf::Vector2f(position.x, position.y));

	}

	void Arrow::execute() {
		update(pGraphic->getDeltaTime());
		render();
	}

	void Arrow::setTextures() {
		sprite = new GraphicalElements::Animation(body, Math::CoordF(2, 2));

		sprite->addNewAnimation(GraphicalElements::Animation_ID::arrow, "arrow.png", 8);

		body->setOrigin(size.x / 2 + 24, size.y / 2 + 30);
	}

	void Arrow::updateSprite(float dt) {
		sprite->update(GraphicalElements::Animation_ID::arrow, isFacingLeft, position, dt);
	}

}