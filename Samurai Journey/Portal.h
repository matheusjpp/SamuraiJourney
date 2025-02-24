#pragma once
#include "Fire.h"

namespace Entities {

	namespace Obstacles {

		class Portal : public Obstacle {
		private:
			bool canTeleport;
			bool isRequesting;
			bool right;
			bool rendered;

		public:
			Portal(Math::CoordF pos = Math::CoordF(0, 0), Math::CoordF size = Math::CoordF(200, 480), ID id = ID::portal);

			~Portal();

			void setCanTeleport(bool canTp);

			const bool getCanTeleport() const;

			void setTeleportRequest(bool tpReq);

			const bool getTeleportRequest() const;

			bool getIsRequesting();

			void update(float dt);

			void execute();

			void setTextures();

			void updateSprite(float dt);

			void setDirection(bool r);

			const bool getDirection() const;

			const bool getRendered() const;

			void setRendered(bool r);
		};

	}

}