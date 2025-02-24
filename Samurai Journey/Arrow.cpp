#include "Arrow.h"

namespace Entities {

	Arrow::Arrow(Math::CoordF pos, bool facingLeft, ID id) : initialX(pos.x), distanceTraveled(0),
		MovingEntity(pos, Math::CoordF(ARROW_SIZE_X, ARROW_SIZE_Y), id) {
		isFacingLeft = facingLeft;
		damagePoints = ARROW_MAXDAMAGE;
		setTextures();
	}

	Arrow::~Arrow() {
		
	}

	float Arrow::getDistanceTraveled()  {
		return distanceTraveled;
	}

	const float Arrow::getInitialX() const {
		return initialX;
	}

	const float Arrow::getDamagePoints() const {
		return damagePoints;
	}

	void Arrow::update(float dt) {
		if (isFacingLeft) {
			velocity.x -= ARROW_SPEED;
		}
		else {
			velocity.x += ARROW_SPEED;
		}

		velocity.x *= exp(-ARROW_AIR_RESISTANCE * dt);
		velocity.y += ARROW_GRAVITY * dt; // Incrementa velocidade vertical
		
		position.x += velocity.x * dt;
		position.y += velocity.y * dt;

		distanceTraveled = fabs(initialX - position.x);
		damagePoints = max(ARROW_MINDAMAGE, ARROW_MAXDAMAGE - (ARROW_MAXDAMAGE - ARROW_MINDAMAGE) * (distanceTraveled / 500.0f));

		if (damagePoints == ARROW_MINDAMAGE) {
			velocity.y += ARROW_GRAVITY * 1.5 * dt;
		}

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

	void Arrow::setDistanceTraveled(float dTravel) {
		distanceTraveled = dTravel;
	}

	void Arrow::setInitialX(float iX) {
		initialX = iX;
	}

}