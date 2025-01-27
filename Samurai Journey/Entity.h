#pragma once
#include "Animation.h"

namespace Entities {

	class Entity : public Ente {
	protected:
		Math::CoordF position;
		Math::CoordF size;
		GraphicalElements::Animation* sprite;
		bool isActive;

	public:
		Entity (Math::CoordF pos = Math::CoordF(0, 0), Math::CoordF size = Math::CoordF(0, 0), ID id = ID::empty);

		virtual ~Entity();

		void setPosition(Math::CoordF pos);

		Math::CoordF getPosition() const;

		Math::CoordF getSize() const;

		bool getIsActive();

		void setIsActive(bool isA);

		virtual void render();

		virtual void update(float dt) = 0;

		virtual void execute() = 0;

		virtual void setTextures() = 0;

		virtual void updateSprite(float dt) = 0;
	};

}