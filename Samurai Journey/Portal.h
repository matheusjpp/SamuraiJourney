#pragma once
#include "Fire.h"

namespace Entities {

	namespace Obstacles {

		class Portal : public Obstacle {
		private:
			bool canTeleport;
			bool isRequesting;

		public:
			Portal(Math::CoordF pos = Math::CoordF(0, 0), Math::CoordF size = Math::CoordF(200, 480), ID id = ID::portal);

			~Portal();

			void setCanTeleport(bool canTp);

			const bool getCanTeleport() const;

			void setTeleportRequest(bool tpReq);

			const bool getTeleportRequest() const;

			void update(float dt);

			void execute();

			void setTextures();

			void updateSprite(float dt);
		};

	}

}